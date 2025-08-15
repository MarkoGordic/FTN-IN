/**
 * Program koji racuna sumu korena nenegativnih brojeva iz vektora brojeva.
*/
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cmath>

#define BROJ_ELEMENATA 1e7


std::vector<double> generisi_ulazne_podatke();


int main() {
    pid_t detetov_pid;
    int id_deljene_memorije = 0, i, j;
    double suma1=0, *suma2 = nullptr;
    std::vector<double> brojevi = generisi_ulazne_podatke();

    id_deljene_memorije = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT | 0660);
    suma2 = (double*)shmat(id_deljene_memorije, nullptr, 0);

    *suma2 = 0;

    detetov_pid = fork();

    if (detetov_pid == -1) {
        std::cerr << "Neuspesno stvaranje novog procesa. Program nastavlja uz oslonac na jednu nit." << std::endl;
        for (double broj : brojevi) {
            if (broj>=0) 
                suma1 += sqrt(broj);
        }
    } else if (detetov_pid == 0) {
        std::cout << "Proces dete krece." << std::endl;

        for (i = 0; i < BROJ_ELEMENATA/2; i++) {
            if (brojevi[i]>=0) {
                *suma2 += sqrt(brojevi[i]);
            }
        }
        std::cout << "Proces dete gotov." << std::endl;

        return 0;
    } else {
        std::cout << "Roditelj nastavlja sa radom." << std::endl;

        for (j = BROJ_ELEMENATA/2; j < BROJ_ELEMENATA; j++) {
            if (brojevi[j]>=0) {
                suma1 += sqrt(brojevi[j]);
            }
        }

        std::cout << "Roditelj gotov sa svojim delom posla." << std::endl;
    }

    int status;
    wait(&status);

    std::cout << "Suma korena je " <<  suma1 + *suma2 << std::endl;

    shmdt(suma2);  // oslobađanje deljene memorije
    shmctl(id_deljene_memorije, IPC_RMID, nullptr);  // brisanje deljene memorije

    return 0;
}


std::vector<double> generisi_ulazne_podatke() {
    std::default_random_engine generator;

    //generator.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    /*
    Linija ispod ovog komentara ima fiksirano seme radi lakseg testiranja koda.
    U slucaju zelje da vrednosti budu nasumicne, otkomentarisati liniju pre a
    zakomentarisati liniju nakon ovog komentara.
    */
    generator.seed(1992);

    std::uniform_real_distribution<double> manje_od_milion(-1e6, 1e6);
    std::vector<double> brojevi(BROJ_ELEMENATA);  // pravljenje vektora unapred poznate velicine

    for (int i = 0; i < BROJ_ELEMENATA; i++) {
        brojevi[i] = manje_od_milion(generator);
    }

    return brojevi;
}