#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_RACUNA 64
#define MAKS_IZNOS_RACUNA 90
#define PRAG_BRZE_USLUGE 12

typedef struct {
    int ukupanPrihod;
    int najveciRacun;
    int brojBrzihRacuna;
} smenaIzvestaj;

smenaIzvestaj sekvencijalnaSmena() {
    int iznosiRacuna[BROJ_RACUNA];

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalni iznosi racuna: ");
#endif

    for (int i = 0; i < BROJ_RACUNA; i++) {
        iznosiRacuna[i] = rand() % MAKS_IZNOS_RACUNA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", iznosiRacuna[i]);
#endif
    }
    printf("\n");

    int ukupanPrihod = 0;
    for (int i = 0; i < BROJ_RACUNA; i++)
        ukupanPrihod += iznosiRacuna[i];

    int najveciRacun = 0;
    for (int i = 0; i < BROJ_RACUNA; i++)
        if (iznosiRacuna[i] > najveciRacun)
            najveciRacun = iznosiRacuna[i];

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

#pragma omp parallel
    {
// generisanje racuna obavlja samo jedna nit (blagajnica)
#pragma omp single
        {
            for (int i = 0; i < BROJ_RACUNA; i++) {
                iznosiRacuna[i] = rand() % MAKS_IZNOS_RACUNA + 1;

#ifdef STAMPAJ_INFORMACIJE
                printf("%d ", iznosiRacuna[i]);
#endif
            }
            printf("\n");
        }

// tri nezavisna izvestaja se prave istovremeno, svaki u svojoj niti
#pragma omp sections
        {
// racunovodja sracunava ukupan prihod
#pragma omp section
            {
                for (int i = 0; i < BROJ_RACUNA; i++)
                    ukupanPrihod += iznosiRacuna[i];
            }

// glavni kuvar trazi najveci racun
#pragma omp section
            {
                for (int i = 0; i < BROJ_RACUNA; i++)
                    if (iznosiRacuna[i] > najveciRacun)
                        najveciRacun = iznosiRacuna[i];
            }

// sef sale broji brze racune
#pragma omp section
            {
                for (int i = 0; i < BROJ_RACUNA; i++)
                    if (iznosiRacuna[i] < PRAG_BRZE_USLUGE)
                        brojBrzihRacuna++;
            }
        }
    } // kraj paralelnog regiona

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
