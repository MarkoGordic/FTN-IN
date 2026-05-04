#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_GAJBI 41
#define ZELJENI_BROJ_BERBACA 5
#define MAKS_TEZINA_GAJBE 12
#define MAKS_OCENA_KVALITETA 5
#define BAZNA_CENA_PO_KG 80
#define PRAG_PREMIUM 4

typedef struct {
    int ukupanPrihod;
    int najvisaIsplata;
    int brojPremiumGajbi;
} dnevniIzvestaj;

dnevniIzvestaj sekvencijalniBerbaci() {
    int tezineGajbi[BROJ_GAJBI];
    int oceneGajbi[BROJ_GAJBI];

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalne tezine i ocene: ");
#endif

    for (int i = 0; i < BROJ_GAJBI; i++) {
        tezineGajbi[i] = rand() % MAKS_TEZINA_GAJBE + 1;
        oceneGajbi[i] = rand() % MAKS_OCENA_KVALITETA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("(%d kg, ocena %d) ", tezineGajbi[i], oceneGajbi[i]);
#endif
    }
    printf("\n");

    int ukupanPrihod = 0;
    int najvisaIsplata = 0;
    int brojPremiumGajbi = 0;

    for (int i = 0; i < BROJ_GAJBI; i++) {
        int isplata = tezineGajbi[i] * oceneGajbi[i] * BAZNA_CENA_PO_KG;

        ukupanPrihod += isplata;

        if (isplata > najvisaIsplata)
            najvisaIsplata = isplata;

        if (oceneGajbi[i] >= PRAG_PREMIUM)
            brojPremiumGajbi++;

#ifdef STAMPAJ_INFORMACIJE
        printf("Gajba %d: isplata %d, premium=%d\n", i, isplata,
               oceneGajbi[i] >= PRAG_PREMIUM ? 1 : 0);
#endif
    }
    printf("\n");

    dnevniIzvestaj iz;
    iz.ukupanPrihod = ukupanPrihod;
    iz.najvisaIsplata = najvisaIsplata;
    iz.brojPremiumGajbi = brojPremiumGajbi;
    return iz;
}

dnevniIzvestaj paralelniBerbaci() {
    int tezineGajbi[BROJ_GAJBI];
    int oceneGajbi[BROJ_GAJBI];

    int ukupanPrihod = 0;
    int najvisaIsplata = 0;
    int brojPremiumGajbi = 0;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelne tezine i ocene: ");
#endif

    omp_set_num_threads(ZELJENI_BROJ_BERBACA);

#pragma omp parallel
    {
// generisanje podataka obavlja samo jedna nit
#pragma omp single
        {
            for (int i = 0; i < BROJ_GAJBI; i++) {
                tezineGajbi[i] = rand() % MAKS_TEZINA_GAJBE + 1;
                oceneGajbi[i] = rand() % MAKS_OCENA_KVALITETA + 1;

#ifdef STAMPAJ_INFORMACIJE
                printf("(%d kg, ocena %d) ", tezineGajbi[i], oceneGajbi[i]);
#endif
            }
            printf("\n");
        }

// svaka nit obraduje svoj deo gajbi i doprinosi globalnim statistikama
// preko reduction klauzula (komutativne i asocijativne operacije)
#pragma omp for reduction(+:ukupanPrihod, brojPremiumGajbi)                    \
    reduction(max:najvisaIsplata)
        for (int i = 0; i < BROJ_GAJBI; i++) {
            int isplata = tezineGajbi[i] * oceneGajbi[i] * BAZNA_CENA_PO_KG;

            ukupanPrihod += isplata;

            if (isplata > najvisaIsplata)
                najvisaIsplata = isplata;

            if (oceneGajbi[i] >= PRAG_PREMIUM)
                brojPremiumGajbi++;

#ifdef STAMPAJ_INFORMACIJE
            printf("Gajba %d: isplata %d, premium=%d\n", i, isplata,
                   oceneGajbi[i] >= PRAG_PREMIUM ? 1 : 0);
#endif
        }
    } // kraj paralelnog regiona
    printf("\n");

    dnevniIzvestaj iz;
    iz.ukupanPrihod = ukupanPrihod;
    iz.najvisaIsplata = najvisaIsplata;
    iz.brojPremiumGajbi = brojPremiumGajbi;
    return iz;
}

int main() {

    time_t randVreme = time(0);

    srand(randVreme);
    dnevniIzvestaj paralelniRez = paralelniBerbaci();

    srand(randVreme);
    dnevniIzvestaj sekvencijalniRez = sekvencijalniBerbaci();

    printf("---- Paralelni rezultat ----\n");
    printf("Ukupan prihod: %d din\n", paralelniRez.ukupanPrihod);
    printf("Najvisa isplata za jednu gajbu: %d din\n",
           paralelniRez.najvisaIsplata);
    printf("Broj premium gajbi: %d\n\n", paralelniRez.brojPremiumGajbi);

    printf("---- Sekvencijalni rezultat ----\n");
    printf("Ukupan prihod: %d din\n", sekvencijalniRez.ukupanPrihod);
    printf("Najvisa isplata za jednu gajbu: %d din\n",
           sekvencijalniRez.najvisaIsplata);
    printf("Broj premium gajbi: %d\n\n", sekvencijalniRez.brojPremiumGajbi);

    return 0;
}
