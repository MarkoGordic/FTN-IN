// Napraviti konkurentni program koji modeluje rad studentske ambulante pri sistematskom pregledu.
// Ambulanta ima operacije udji i izadji.
// Studenti i studentkinje pozivaju operaciju udji prilikom ulaska u ambulantu i izadji prilikom izlaska iz nje.
// Svaki student se u ambulanti zadrzava slucajan interval koji traje od 1 do 3 sekunde.
//
// Ambulanta prima studente i studentkinje u odvojene prostorije. Kapacitet muskih i zenskih mesta je odredjen parametrima konstruktora klase Studentska_ambulanta. Studenti koji nailaze na slobodna mesta u ambulanti mogu direktno da udju u nju.
// Ukoliko je kapacitet prostorije popunjen studenti cekaju na slobodna mesta u datoj prostoriji.
//
// Napomena: Indeks studenta je redni broj niti student pri stvaranju.
//
// Implementirati oznacene metode klase Studentska_ambulanta u fajlu ambulanta.h

#include <thread>

#include "ambulanta.hpp"

using namespace std;
using namespace chrono;

void student(Studentska_ambulanta& sa, int index_studenta, Pol p) {
   sa.udji(index_studenta, p);
   this_thread::sleep_for(seconds(1 + index_studenta % 3));
   sa.izadji(index_studenta, p);
}

const int M_MESTA = 1;
const int Z_MESTA = 2;

const int M_STUDENATA = 3;
const int Z_STUDENATA = 5;

void testirajSve() {
    Student st;
    Studentska_ambulanta sa(st, M_MESTA, Z_MESTA);
    thread t[M_STUDENATA + Z_STUDENATA];

    for(int i = 0; i < M_STUDENATA; i++)
        t[i] = thread(student, ref(sa), i, Pol::MUSKI);

    for(int i = 0; i < Z_STUDENATA; i++)
        t[M_STUDENATA + i] = thread(student, ref(sa), M_STUDENATA + i, Pol::ZENSKI);

    for(int i = 0; i < M_STUDENATA + Z_STUDENATA; i++)
        t[i].join();
}

int main() {
    testirajSve();

    return 0;
}
