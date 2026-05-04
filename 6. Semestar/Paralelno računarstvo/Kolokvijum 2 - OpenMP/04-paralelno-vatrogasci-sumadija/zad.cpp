#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_INTERVENCIJA 47
#define ZELJENI_BROJ_EKIPA 6
#define MAKS_JACINA_POZARA 9
#define MINUTI_PO_JEDINICI_JACINE 12

// kategorizacija pozara: 1-3 manji, 4-6 srednji, 7-9 veliki
#define BROJ_KATEGORIJA 3

typedef struct {
    int histogram[BROJ_KATEGORIJA]; // [manji, srednji, veliki]
    int ukupnoMinuta;               // ukupno utroseno minuta intervencija
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

    // generisanje jacine svakog pozara koji se prijavi tokom sezone
    // istu logiku iskoristiti i u paralelnoj verziji programa
    for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
        jacinePozara[i] = rand() % MAKS_JACINA_POZARA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", jacinePozara[i]);
#endif
    }
    printf("\n");

    int histogram[BROJ_KATEGORIJA] = {0};
    int ukupnoMinuta = 0;

    // za svaki pozar: razvrstati ga u odgovarajucu kategoriju (manji/srednji/
    // veliki) i sracunati koliko je minuta utroseno na tu intervenciju;
    // vreme intervencije srazmerno je jacini pozara
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
    // TODO: otvoriti paralelni region; ZELJENI_BROJ_EKIPA niti

    // TODO: generisanje niza jacinePozara mora se obaviti SAMO JEDNOM,
    // ne ponovo u svakoj niti
    for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
        // logika ista kao i u sekvencijalnom delu
        jacinePozara[i] = rand() % MAKS_JACINA_POZARA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", jacinePozara[i]);
#endif
    }
    printf("\n");

    // TODO: paralelizovati ovu petlju vodeci racuna o sledecem:
    //
    // (1) iteracije nisu jednakog trajanja: jacina 1 traje
    //     1*MINUTI_PO_JEDINICI_JACINE = 12 min, jacina 9 traje 108 min;
    //     ravna (staticka) raspodela posla po nitima nije fer i ostavila
    //     bi neke niti besposlene a druge zatrpane - raspodela mora biti
    //     DINAMICKA
    //
    // (2) niz histogram je deljiva memorija u koju vise niti istovremeno
    //     upisuje; pojedinacni inkrement nad jednim elementom mora biti
    //     zasticen, ali zasticena celina mora biti najuza moguca - SAMO
    //     pojedinacni inkrement, NE ceo blok petlje (ne #pragma omp critical)
    //
    // (3) ukupnoMinuta se sumira efikasno, bez kriticne sekcije
    for (int i = 0; i < BROJ_INTERVENCIJA; i++) {
        int j = jacinePozara[i];
        int kategorija = kategorijaPozara(j);

        histogram[kategorija]++;
        ukupnoMinuta += j * MINUTI_PO_JEDINICI_JACINE;

#ifdef STAMPAJ_INFORMACIJE
        printf("Pozar %d: jacina %d, kategorija %d, utroseno %d min (ekipa %d)\n",
               i, j, kategorija, j * MINUTI_PO_JEDINICI_JACINE,
               omp_get_thread_num());
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
