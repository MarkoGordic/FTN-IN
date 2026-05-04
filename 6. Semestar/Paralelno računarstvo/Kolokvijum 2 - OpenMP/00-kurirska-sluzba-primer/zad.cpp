#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define NELEM 100000000
#define NOTIMPLEMENTED vector<int>()
#define BROJ_PAKETA 29
#define ZELJENI_BROJ_KURIRA 8
#define MAKS_TEZINA_PAKETA 10
#define ZARADA_PO_PAKETU 100
#define DNEVNA_NORMA 3

typedef struct {
    int idKurira;
    int ukupnaZarada;
} ucinakKurira;

void isporuciPaket(int id, int tezina, int zarada) {
#ifdef STAMPAJ_INFORMACIJE
    printf("Kurir %d isporucuje paket od %d kilograma, od cega dobija %d "
           "dinara.\n",
           id, tezina, zarada);
#endif
}

ucinakKurira sekvencijalniKuriri() {
    // niz koji cuva informacije o tezinama
    int tezinePaketa[BROJ_PAKETA];

    // centralizovani zapisnik; niz koji cuva zaradu za svakog kurira
    int zaradaPoKuriru[ZELJENI_BROJ_KURIRA] = {0};

    // evidencija o tome da li je neki radnik prekoracio normu,
    // odnosno isporucio vise od 3 paketa
    int normaPaketaPoKuriru[ZELJENI_BROJ_KURIRA];
    for (int i = 0; i < ZELJENI_BROJ_KURIRA; i++)
        normaPaketaPoKuriru[i] = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Sekvencijalne tezine: ");
#endif

    // postavljanje tezine paketa, zaduzenje poslodavca
    for (int i = 0; i < BROJ_PAKETA; i++) {
        // ista logika za postavljanje tezine paketa i u paralelnom algoritmu
        // treba da bude iskoristena
        tezinePaketa[i] = rand() % MAKS_TEZINA_PAKETA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", tezinePaketa[i]);
        printf("\n");
#endif
    }

    // broj paketa dodeljen svakom od kurira; ukupan broj paketa deli se na broj
    // kurira i zaokruzuje na gornje celo prvih ovoliko paketa isporucuje prvi
    // kurir, sledecih toliko drugi i td.; poslednji kurir ce isporuciti manje
    // paketa, ukoliko broj paketa nije deljiv sa brojem kurira iskoristiti istu
    // racunicu i u paralelnom algoritmu
    int brojPaketaPoKuriru =
        (int)(((float)BROJ_PAKETA) / ((float)ZELJENI_BROJ_KURIRA) + 0.5);

    // isporucivanje paketa, zaduzenje kurira
    for (int i = 0; i < BROJ_PAKETA; i++) {
        // određivanje id-a trenutnog radnika
        int trenutniKurir = i / brojPaketaPoKuriru;

        normaPaketaPoKuriru[trenutniKurir]--;

        // svaki paket preko norme placen je duplo
        int zarada = ZARADA_PO_PAKETU * tezinePaketa[i];
        if (normaPaketaPoKuriru[trenutniKurir] < 0) {
            zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
            printf("Kurir %d radi prekovremeno, zarada skace na %d\n",
                   trenutniKurir, zarada);
#endif
        }
        // simulacija isporucivanja paketa; funkcija ne radi nista vazno, samo
        // ispisuje poruku ukoliko je definisan odgovarajuci makro
        isporuciPaket(trenutniKurir, tezinePaketa[i], zarada);

        // azuriranje zapisnika, odnosno odgovarajućeg polja u nizu
        zaradaPoKuriru[trenutniKurir] += zarada;

#ifdef STAMPAJ_INFORMACIJE
        printf("Kurir %d je zaradio %d od paketa %d, ukupno: %d\n",
               trenutniKurir, zarada, i, zaradaPoKuriru[trenutniKurir]);
        printf("\n\n");
#endif
    }

    ucinakKurira uk;

    // algoritam kojim se određuje ko je najvredniji kurir i koliko je posla
    // uradio zaduzenje poslodavca
    uk.ukupnaZarada = zaradaPoKuriru[0];
    uk.idKurira = 0;
    for (int i = 1; i < ZELJENI_BROJ_KURIRA; i++) {
        if (zaradaPoKuriru[i] > uk.ukupnaZarada) {
            uk.ukupnaZarada = zaradaPoKuriru[i];
            uk.idKurira = i;
        }
    }

    return uk;
}

ucinakKurira paralelniKuriri() {
    // iskoristiti ovaj broj u "schedule" klauzuli "omp for" direktive, na
    // sledeći način: schedule(static, brojPaketaPoKuriru) ovo se radi kako bi
    // raspodela posla po kuririma bila ista kao kod sekvencijalnog programa
    // kako bi resenja bila uporediva
    // niz koji cuva informacije o tezinama
    int brojPaketaPoKuriru =
        (int)(((float)BROJ_PAKETA) / ((float)ZELJENI_BROJ_KURIRA) + 0.5);

    // promenljiva koja se po potrebi azurira kako bi na kraju algoritma
    // sadrzala podatke o kuriru koji je najvise novca zaradio, ova
    // promenljiva je povratna vrednost funkcije
    ucinakKurira uk;
    uk.idKurira = -1;
    uk.ukupnaZarada = -1;

    int tezinePaketa[BROJ_PAKETA];

    // zabranjeno je koristiti nizove u paralelnoj implementaciji
    // za normu i zaradu po kuriru
    int zaradaPoKuriru = 0;
    int normaPaketaPoKuriru = DNEVNA_NORMA;

#ifdef STAMPAJ_INFORMACIJE
    printf("Paralelne tezine: ");
#endif
    omp_set_num_threads(ZELJENI_BROJ_KURIRA);
    // TODO: implementirati paralelni algoritam, ovde mozete poceti sa
    // paralelnim regionom

    // postavljanje tezine paketa, zaduzenje *jednog* kurira
    for (int i = 0; i < BROJ_PAKETA; i++) {
        // logika ista kao i u sekvencijalnom delu
        tezinePaketa[i] = rand() % MAKS_TEZINA_PAKETA + 1;

#ifdef STAMPAJ_INFORMACIJE
        printf("%d ", tezinePaketa[i]);
#endif
    }
    printf("\n");

    for (int i = 0; i < BROJ_PAKETA; i++) {
        // TODO: odrediti ID trenutnog kurira u paralelnoj implementaciji
        int trenutniKurir = -1;

        normaPaketaPoKuriru--;

        // svaki paket preko norme placen je duplo
        int zarada = ZARADA_PO_PAKETU * tezinePaketa[i];
        if (normaPaketaPoKuriru < 0) {
            zarada *= 2;
#ifdef STAMPAJ_INFORMACIJE
            printf("Kurir %d radi prekovremeno, zarada skace na %d\n",
                   trenutniKurir, zarada);
#endif
        }

        // simulacija isporucivanja paketa; funkcija ne radi nista
        // vazno, samo ispisuje poruku ukoliko je definisan odgovarajuci
        // makro
        isporuciPaket(trenutniKurir, tezinePaketa[i], zarada);

        // TODO: nakon isporuke, za trenutnog kurira azurirati zaradu

        // TODO: implementirati logiku cuvanja najvece zarada
        // i odgovarajuceg ID-a kurira koji je najvise zaradio
        // uzeti u obzir da ne dodje do trke do podataka

#ifdef STAMPAJ_INFORMACIJE
        printf("Kurir %d je zaradio %d od paketa %d, ukupno: %d\n",
               trenutniKurir, zarada, i, zaradaPoKuriru);
        printf("\n\n");
#endif
    }

    return uk;
}

int main() {

    time_t randVreme = time(0);

    srand(randVreme);
    ucinakKurira paralelniRez = paralelniKuriri();

    srand(randVreme);
    ucinakKurira sekvencijalniRez = sekvencijalniKuriri();

    printf("---- Paralelni rezultat ----\nKurir sa najvecom zaradom: "
           "%d\nUkupna zarada kurira: %d\n\n",
           paralelniRez.idKurira, paralelniRez.ukupnaZarada);
    printf("---- Sekvencijalni razultat ----\nKurir sa najvecom zaradom: "
           "%d\nUkupna zarada kurira: %d\n\n",
           sekvencijalniRez.idKurira, sekvencijalniRez.ukupnaZarada);

    return 0;
}