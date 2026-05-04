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
    // niz koji za svaku voznju cuva pređenu razdaljinu
    int razdaljineVoznji[BROJ_VOZNJI];

    // centralizovani zapisnik dispecera, zarada za svakog vozaca
    int zaradaPoVozacu[ZELJENI_BROJ_VOZACA] = {0};

    // koliko jos voznji pre nego sto vozac stigne svoju normu
    int normaVoznjiPoVozacu[ZELJENI_BROJ_VOZACA];
    for (int i = 0; i < ZELJENI_BROJ_VOZACA; i++)
        normaVoznjiPoVozacu[i] = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalne razdaljine: ");
#endif

    // generisanje razdaljine svake voznje (random vrednosti)
    // istu logiku iskoristiti i u paralelnoj verziji programa
    for (int i = 0; i < BROJ_VOZNJI; i++) {
        razdaljineVoznji[i] = rand() % MAKS_RAZDALJINA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", razdaljineVoznji[i]);
#endif
    }
    printf("\n");

    // raspodela posla po vozacima; ukupan broj voznji deli se brojem vozaca
    // i zaokruzuje na gornje celo; prvih ovoliko voznji odradjuje prvi vozac,
    // sledecih toliko drugi i tako redom; poslednji vozac moze imati manje
    // voznji ako broj nije deljiv; istu raspodelu mora koristiti i paralelni
    // algoritam
    int brojVoznjiPoVozacu =
        (int)(((float)BROJ_VOZNJI) / ((float)ZELJENI_BROJ_VOZACA) + 0.5);

    // izvrsavanje voznji i obracun zarade za svakog vozaca
    for (int i = 0; i < BROJ_VOZNJI; i++) {
        // odredjivanje ID-a vozaca koji preuzima trenutnu voznju
        int trenutniVozac = i / brojVoznjiPoVozacu;

        normaVoznjiPoVozacu[trenutniVozac]--;

        // svaka voznja preko norme placa se duplo (prekovremeni rad)
        int zarada = CENA_PO_KM * razdaljineVoznji[i];
        if (normaVoznjiPoVozacu[trenutniVozac] < 0) {
            zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
            printf("Vozac %d radi prekovremeno, zarada skace na %d\n",
                   trenutniVozac, zarada);
#endif
        }

        // simulacija voznje; funkcija samo ispisuje poruku ukoliko je
        // definisan odgovarajuci makro
        zavrsiVoznju(trenutniVozac, razdaljineVoznji[i], zarada);

        // azuriranje zapisnika dispecera
        zaradaPoVozacu[trenutniVozac] += zarada;

#ifdef STAMPAJ_INFORMACIJE
        printf("Vozac %d je za voznju %d zaradio %d, ukupno: %d\n",
               trenutniVozac, i, zarada, zaradaPoVozacu[trenutniVozac]);
#endif
    }
    printf("\n\n");

    ucinakVozaca uk;

    // odredjivanje vozaca sa najvecom zaradom dana
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
    // ovaj broj iskoristiti u "schedule" klauzuli "omp for" direktive na
    // sledeci nacin: schedule(static, brojVoznjiPoVozacu); ovim se osigurava
    // da raspodela voznji po vozacima bude ista kao u sekvencijalnoj verziji
    // i da rezultati budu uporedivi
    int brojVoznjiPoVozacu =
        (int)(((float)BROJ_VOZNJI) / ((float)ZELJENI_BROJ_VOZACA) + 0.5);

    // promenljiva u kojoj cuvamo informaciju o vozacu sa najvecom zaradom,
    // azurira se tokom rada algoritma; povratna vrednost funkcije
    ucinakVozaca uk;
    uk.idVozaca = -1;
    uk.ukupnaZarada = -1;

    int razdaljineVoznji[BROJ_VOZNJI];

    // zabranjeno je koristiti nizove u paralelnoj implementaciji
    // za normu i zaradu po vozacu
    int zaradaPoVozacu = 0;
    int normaVoznjiPoVozacu = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelne razdaljine: ");
#endif

    omp_set_num_threads(ZELJENI_BROJ_VOZACA);
    // TODO: implementirati paralelni algoritam, ovde mozete poceti sa
    // paralelnim regionom

    // generisanje razdaljine svake voznje, posao jedne niti (dispecer)
    for (int i = 0; i < BROJ_VOZNJI; i++) {
        // logika ista kao i u sekvencijalnom delu
        razdaljineVoznji[i] = rand() % MAKS_RAZDALJINA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", razdaljineVoznji[i]);
#endif
    }
    printf("\n");

    for (int i = 0; i < BROJ_VOZNJI; i++) {
        // TODO: odrediti ID trenutnog vozaca u paralelnoj implementaciji
        int trenutniVozac = -1;

        normaVoznjiPoVozacu--;

        // svaka voznja preko norme placa se duplo (prekovremeni rad)
        int zarada = CENA_PO_KM * razdaljineVoznji[i];
        if (normaVoznjiPoVozacu < 0) {
            zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
            printf("Vozac %d radi prekovremeno, zarada skace na %d\n",
                   trenutniVozac, zarada);
#endif
        }

        // simulacija voznje; funkcija samo ispisuje poruku ukoliko je
        // definisan odgovarajuci makro
        zavrsiVoznju(trenutniVozac, razdaljineVoznji[i], zarada);

        // TODO: nakon voznje, za trenutnog vozaca azurirati ukupnu dnevnu
        // zaradu

        // TODO: implementirati logiku cuvanja najvece zarade i ID-a vozaca
        // koji je tog dana najvise zaradio; obratiti paznju na trku za
        // podatke pri zajednickom azuriranju

#ifdef STAMPAJ_INFORMACIJE
        printf("Vozac %d je za voznju %d zaradio %d, ukupno: %d\n",
               trenutniVozac, i, zarada, zaradaPoVozacu);
#endif
    }
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
