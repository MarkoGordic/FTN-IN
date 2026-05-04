#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_INTERVENCIJA 47
#define ZELJENI_BROJ_EKIPA 6
#define MAKS_JACINA_POZARA 9
#define MINUTI_PO_JEDINICI_JACINE 12

#define BROJ_KATEGORIJA 3

typedef struct {
    int histogram[BROJ_KATEGORIJA];
    int ukupnoMinuta;
} sezonskiIzvestaj;

int kategorijaPozara(int jacina) {
    if (jacina <= 3) return 0;
    if (jacina <= 6) return 1;
    return 2;
}

sezonskiIzvestaj sekvencijalnaSezona() {
    int jacinePozara[BROJ_INTERVENCIJA];

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalne jacine pozara: ");
#endif

    for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
        jacinePozara[i] = rand() % MAKS_JACINA_POZARA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", jacinePozara[i]);
#endif
    }
    printf("\n");

    int histogram[BROJ_KATEGORIJA] = {0};
    int ukupnoMinuta = 0;

    for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
        int j = jacinePozara[i];
        int kategorija = kategorijaPozara(j);

        histogram[kategorija]++;
        ukupnoMinuta += j * MINUTI_PO_JEDINICI_JACINE;

#ifdef STAMPAJ_INFORMACIJE
        printf("Pozar %d: jacina %d, kategorija %d, utroseno %d min\n", i, j,
               kategorija, j * MINUTI_PO_JEDINICI_JACINE);
#endif
    }
    printf("\n");

    sezonskiIzvestaj iz;
    iz.histogram[0] = histogram[0];
    iz.histogram[1] = histogram[1];
    iz.histogram[2] = histogram[2];
    iz.ukupnoMinuta = ukupnoMinuta;
    return iz;
}

sezonskiIzvestaj paralelnaSezona() {
    int jacinePozara[BROJ_INTERVENCIJA];

    int histogram[BROJ_KATEGORIJA] = {0};
    int ukupnoMinuta = 0;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelne jacine pozara: ");
#endif

    omp_set_num_threads(ZELJENI_BROJ_EKIPA);

#pragma omp parallel
    {
// generisanje jacina obavlja samo jedna nit (dispecer)
#pragma omp single
        {
            for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
                jacinePozara[i] = rand() % MAKS_JACINA_POZARA + 1;

#ifdef STAMPAJ_INFORMACIJE
                printf("%d ", jacinePozara[i]);
#endif
            }
            printf("\n");
        }

// dinamicka raspodela jer su intervencije nejednakog trajanja;
// reduction za ukupnoMinuta, atomic za pojedinacne inkremente histograma
#pragma omp for schedule(dynamic, 1) reduction(+:ukupnoMinuta)
        for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
            int j = jacinePozara[i];
            int kategorija = kategorijaPozara(j);

#pragma omp atomic
            histogram[kategorija]++;

            ukupnoMinuta += j * MINUTI_PO_JEDINICI_JACINE;

#ifdef STAMPAJ_INFORMACIJE
            printf("Pozar %d: jacina %d, kategorija %d, utroseno %d min (ekipa %d)\n",
                   i, j, kategorija, j * MINUTI_PO_JEDINICI_JACINE,
                   omp_get_thread_num());
#endif
        }
    } // kraj paralelnog regiona
    printf("\n");

    sezonskiIzvestaj iz;
    iz.histogram[0] = histogram[0];
    iz.histogram[1] = histogram[1];
    iz.histogram[2] = histogram[2];
    iz.ukupnoMinuta = ukupnoMinuta;
    return iz;
}

int main() {

    time_t randVreme = time(0);

    srand(randVreme);
    sezonskiIzvestaj paralelniRez = paralelnaSezona();

    srand(randVreme);
    sezonskiIzvestaj sekvencijalniRez = sekvencijalnaSezona();

    printf("---- Paralelni rezultat ----\n");
    printf("Manji pozari: %d, srednji: %d, veliki: %d\n",
           paralelniRez.histogram[0], paralelniRez.histogram[1],
           paralelniRez.histogram[2]);
    printf("Ukupno utroseno: %d min\n\n", paralelniRez.ukupnoMinuta);

    printf("---- Sekvencijalni rezultat ----\n");
    printf("Manji pozari: %d, srednji: %d, veliki: %d\n",
           sekvencijalniRez.histogram[0], sekvencijalniRez.histogram[1],
           sekvencijalniRez.histogram[2]);
    printf("Ukupno utroseno: %d min\n\n", sekvencijalniRez.ukupnoMinuta);

    return 0;
}
