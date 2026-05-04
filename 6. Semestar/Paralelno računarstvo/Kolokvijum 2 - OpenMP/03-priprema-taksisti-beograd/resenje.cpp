#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define BROJ_VOZNJI 31
#define ZELJENI_BROJ_VOZACA 8
#define MAKS_RAZDALJINA 15
#define CENA_PO_KM 60
#define DNEVNA_NORMA 4

typedef struct {
    int idVozaca;
    int ukupnaZarada;
} ucinakVozaca;

void zavrsiVoznju(int id, int razdaljina, int zarada) {
#ifdef STAMPAJ_INFORMACIJE
    printf("Vozac %d je odvezao voznju od %d km, zarada: %d dinara.\n",
           id, razdaljina, zarada);
#endif
}

ucinakVozaca sekvencijalniVozaci() {
    int razdaljineVoznji[BROJ_VOZNJI];
    int zaradaPoVozacu[ZELJENI_BROJ_VOZACA] = {0};

    int normaVoznjiPoVozacu[ZELJENI_BROJ_VOZACA];
    for (int i = 0; i < ZELJENI_BROJ_VOZACA; i++)
        normaVoznjiPoVozacu[i] = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalne razdaljine: ");
#endif

    for (int i = 0; i < BROJ_VOZNJI; i++) {
        razdaljineVoznji[i] = rand() % MAKS_RAZDALJINA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", razdaljineVoznji[i]);
#endif
    }
    printf("\n");

    int brojVoznjiPoVozacu =
        (int)(((float)BROJ_VOZNJI) / ((float)ZELJENI_BROJ_VOZACA) + 0.5);

    for (int i = 0; i < BROJ_VOZNJI; i++) {
        int trenutniVozac = i / brojVoznjiPoVozacu;

        normaVoznjiPoVozacu[trenutniVozac]--;

        int zarada = CENA_PO_KM * razdaljineVoznji[i];
        if (normaVoznjiPoVozacu[trenutniVozac] < 0) {
            zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
            printf("Vozac %d radi prekovremeno, zarada skace na %d\n",
                   trenutniVozac, zarada);
#endif
        }

        zavrsiVoznju(trenutniVozac, razdaljineVoznji[i], zarada);

        zaradaPoVozacu[trenutniVozac] += zarada;

#ifdef STAMPAJ_INFORMACIJE
        printf("Vozac %d je za voznju %d zaradio %d, ukupno: %d\n",
               trenutniVozac, i, zarada, zaradaPoVozacu[trenutniVozac]);
#endif
    }
    printf("\n\n");

    ucinakVozaca uk;

    uk.ukupnaZarada = zaradaPoVozacu[0];
    uk.idVozaca = 0;
    for (int i = 1; i < ZELJENI_BROJ_VOZACA; i++) {
        if (zaradaPoVozacu[i] > uk.ukupnaZarada) {
            uk.ukupnaZarada = zaradaPoVozacu[i];
            uk.idVozaca = i;
        }
    }

    return uk;
}

ucinakVozaca paralelniVozaci() {
    int brojVoznjiPoVozacu =
        (int)(((float)BROJ_VOZNJI) / ((float)ZELJENI_BROJ_VOZACA) + 0.5);

    ucinakVozaca uk;
    uk.idVozaca = -1;
    uk.ukupnaZarada = -1;

    int razdaljineVoznji[BROJ_VOZNJI];

    int zaradaPoVozacu = 0;
    int normaVoznjiPoVozacu = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelne razdaljine: ");
#endif

    omp_set_num_threads(ZELJENI_BROJ_VOZACA);
#pragma omp parallel firstprivate(zaradaPoVozacu, normaVoznjiPoVozacu)
    {
// generisanje razdaljina obavlja samo jedna nit (dispecer)
#pragma omp single
        {
            for (int i = 0; i < BROJ_VOZNJI; i++) {
                razdaljineVoznji[i] = rand() % MAKS_RAZDALJINA + 1;

#ifdef STAMPAJ_INFORMACIJE
                printf("%d ", razdaljineVoznji[i]);
#endif
            }
            printf("\n");
        }

#pragma omp for schedule(static, brojVoznjiPoVozacu)
        for (int i = 0; i < BROJ_VOZNJI; i++) {
            // ID trenutnog vozaca odgovara ID-u niti
            int trenutniVozac = omp_get_thread_num();

            normaVoznjiPoVozacu--;

            int zarada = CENA_PO_KM * razdaljineVoznji[i];
            if (normaVoznjiPoVozacu < 0) {
                zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
                printf("Vozac %d radi prekovremeno, zarada skace na %d\n",
                       trenutniVozac, zarada);
#endif
            }

            zavrsiVoznju(trenutniVozac, razdaljineVoznji[i], zarada);

            zaradaPoVozacu += zarada;
#ifdef STAMPAJ_INFORMACIJE
            printf("Vozac %d je za voznju %d zaradio %d, ukupno: %d\n",
                   trenutniVozac, i, zarada, zaradaPoVozacu);
#endif

#pragma omp critical
            {
                if (zaradaPoVozacu > uk.ukupnaZarada) {
                    uk.ukupnaZarada = zaradaPoVozacu;
                    uk.idVozaca = omp_get_thread_num();
                }
            }
        }
    } // kraj paralelnog regiona
    printf("\n\n");

    return uk;
}

int main() {

    time_t randVreme = time(0);

    srand(randVreme);
    ucinakVozaca paralelniRez = paralelniVozaci();

    srand(randVreme);
    ucinakVozaca sekvencijalniRez = sekvencijalniVozaci();

    printf("---- Paralelni rezultat ----\nVozac sa najvecom zaradom: "
           "%d\nUkupna zarada vozaca: %d\n\n",
           paralelniRez.idVozaca, paralelniRez.ukupnaZarada);
    printf("---- Sekvencijalni rezultat ----\nVozac sa najvecom zaradom: "
           "%d\nUkupna zarada vozaca: %d\n\n",
           sekvencijalniRez.idVozaca, sekvencijalniRez.ukupnaZarada);

    return 0;
}
