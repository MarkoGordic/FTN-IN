// Definisati klasu Parking koja modeluje Parking prostor kapaciteta jednog mesta.
// Ova klasa ima operacije: udji() i izadji().
//
// Automobili koji dolaze na Parking su predstavljeni programskim nitima. Za ulazak na Parking, automobil poziva metodu udji(). Za izlazak sa Parkinga, automobil poziva metodu izadji().
//
// Automobil se na Parkingu zadržava 3 sekunde. Pri ulasku, ukoliko je Parking zauzet, automobil mora da sačeka da se Parking oslobodi.
//
// Implementirati označene metode u klasi Parking u fajlu parking.h

#include <thread>

#include "parking.hpp"

using namespace std;

void automobil(Parking& p, int rba) {
    p.udji(rba);
    this_thread::sleep_for(chrono::seconds(3));
    p.izadji(rba);
}

const int automobila = 10;

int main() {
    Automobil a;
    Parking p(a);
    thread t[automobila];
    for(int i = 0; i < automobila; i++)
        t[i] = thread(automobil, ref(p), i + 1);
    for(int i = 0; i < automobila; i++)
        t[i].join();
    
    return 0;
}
