#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_RACUNA 64
#define MAKS_IZNOS_RACUNA 90
#define PRAG_BRZE_USLUGE 12

typedef struct {
    int ukupanPrihod;     // racunovodja: ukupan prihod smene
    int najveciRacun;     // glavni kuvar: najveci racun u smeni
    int brojBrzihRacuna;  // sef sale: broj racuna ispod praga (kafe i kola)
} smenaIzvestaj;

smenaIzvestaj sekvencijalnaSmena() {
    int iznosiRacuna[BROJ_RACUNA];

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalni iznosi racuna: ");
#endif

    // generisanje iznosa svakog racuna te smene
    // istu logiku iskoristiti i u paralelnoj verziji programa
    for (int i = 0; i < BROJ_RACUNA; i++) {
        iznosiRacuna[i] = rand() % MAKS_IZNOS_RACUNA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", iznosiRacuna[i]);
#endif
    }
    printf("\n");

    // racunovodja sracunava ukupan prihod te smene
    int ukupanPrihod = 0;
    for (int i = 0; i < BROJ_RACUNA; i++)
        ukupanPrihod += iznosiRacuna[i];

    // glavni kuvar trazi najskupliji racun, da zna sta je hit jelo veceri
    int najveciRacun = 0;
    for (int i = 0; i < BROJ_RACUNA; i++)
        if (iznosiRacuna[i] > najveciRacun)
            najveciRacun = iznosiRacuna[i];

    // sef sale broji "brze racune" (kafa, kola, mali deserti) jer se za njih
    // gostima zaracunava manji procenat usluge
    int brojBrzihRacuna = 0;
    for (int i = 0; i < BROJ_RACUNA; i++)
        if (iznosiRacuna[i] < PRAG_BRZE_USLUGE)
            brojBrzihRacuna++;

    smenaIzvestaj iz;
    iz.ukupanPrihod = ukupanPrihod;
    iz.najveciRacun = najveciRacun;
    iz.brojBrzihRacuna = brojBrzihRacuna;
    return iz;
}

smenaIzvestaj paralelnaSmena() {
    int iznosiRacuna[BROJ_RACUNA];

    int ukupanPrihod = 0;
    int najveciRacun = 0;
    int brojBrzihRacuna = 0;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelni iznosi racuna: ");
#endif

    omp_set_num_threads(3);
    // TODO: otvoriti paralelni region; tacno tri niti (po jedna za svaki
    // izvestaj)

    // TODO: generisanje niza iznosiRacuna mora se obaviti SAMO JEDNOM,
    // ne ponovo u svakoj niti
    for (int i = 0; i < BROJ_RACUNA; i++) {
        // logika ista kao i u sekvencijalnom delu
        iznosiRacuna[i] = rand() % MAKS_IZNOS_RACUNA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", iznosiRacuna[i]);
#endif
    }
    printf("\n");

    // TODO: tri donje petlje (suma, maksimum, brojac) treba da se izvrsavaju
    // ISTOVREMENO, svaka u svojoj niti; tela petlji ostaviti identicna,
    // rasporeduje se samo struktura
    //
    // OGRANICENJE: NE koristiti #pragma omp for ni reduction; svaka petlja
    // se izvrsava u potpunosti u jednoj niti

    // racunovodja sracunava ukupan prihod te smene
    for (int i = 0; i < BROJ_RACUNA; i++)
        ukupanPrihod += iznosiRacuna[i];

    // glavni kuvar trazi najskupliji racun, da zna sta je hit jelo veceri
    for (int i = 0; i < BROJ_RACUNA; i++)
        if (iznosiRacuna[i] > najveciRacun)
            najveciRacun = iznosiRacuna[i];

    // sef sale broji "brze racune" (kafa, kola, mali deserti)
    for (int i = 0; i < BROJ_RACUNA; i++)
        if (iznosiRacuna[i] < PRAG_BRZE_USLUGE)
            brojBrzihRacuna++;

    smenaIzvestaj iz;
    iz.ukupanPrihod = ukupanPrihod;
    iz.najveciRacun = najveciRacun;
    iz.brojBrzihRacuna = brojBrzihRacuna;
    return iz;
}

int main() {

    time_t randVreme = time(0);

    srand(randVreme);
    smenaIzvestaj paralelniRez = paralelnaSmena();

    srand(randVreme);
    smenaIzvestaj sekvencijalniRez = sekvencijalnaSmena();

    printf("---- Paralelni rezultat ----\n");
    printf("Ukupan prihod smene: %d evra\n", paralelniRez.ukupanPrihod);
    printf("Najveci pojedinacni racun: %d evra\n", paralelniRez.najveciRacun);
    printf("Broj brzih racuna: %d\n\n", paralelniRez.brojBrzihRacuna);

    printf("---- Sekvencijalni rezultat ----\n");
    printf("Ukupan prihod smene: %d evra\n", sekvencijalniRez.ukupanPrihod);
    printf("Najveci pojedinacni racun: %d evra\n",
           sekvencijalniRez.najveciRacun);
    printf("Broj brzih racuna: %d\n\n", sekvencijalniRez.brojBrzihRacuna);

    return 0;
}
