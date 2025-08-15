// Definisati klasu Parking koja modeluje Parking prostor kapaciteta N mesta. Kapacitet Parkinga proslediti kao argument konstruktoru klase Parking.
//
// Ova klasa ima operacije: udji() i izadji().
//
// Automobili koji dolaze na Parking su predstavljeni programskim nitima. Za ulazak na Parking, automobil poziva metodu udji(). Za izlazak sa Parkinga, automobil poziva metodu izadji().
//
// Automobil se na Parkingu zadržava od 1 do 3 sekunde. Pri ulasku, ukoliko je Parking zauzet, automobil mora da sačeka da se neko parking mesto oslobodi.
//
// Implementirati označene metode u klasi Parking u fajlu parking.h

#include <thread>
#include <random>

#include "parking.hpp"

using namespace std;

const int KAPACITET = 3;

void automobil(Parking& p, int rba, int sekundi_na_parkingu) {
    p.udji(rba);
    this_thread::sleep_for(chrono::seconds(sekundi_na_parkingu));
    p.izadji(rba);
}

const int automobila = 10;

int main() {
    Automobil a;
    Parking p(a, KAPACITET);
    thread t[automobila];
    default_random_engine dr;
    dr.seed(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> trajanje_zadrzavanja_na_parkingu(1, 3);
    for(int i = 0; i < automobila; i++)
        t[i] = thread(automobil, ref(p), i + 1, trajanje_zadrzavanja_na_parkingu(dr));
    for(int i = 0; i < automobila; i++)
        t[i].join();

    return 0;
}
