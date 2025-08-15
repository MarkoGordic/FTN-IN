/*
    Definisati klasu Parking koja modeluje Parking prostor kapaciteta jednog mesta.
    Ova klasa ima operacije:
        void Parking::udji();
        void Parking::izadji();

    Automobili koji dolaze na Parking su predstavljeni nitima.
				Za ulazak na Parking, automobil poziva metodu udji().
				Za izlazak sa Parkinga, automobil poziva metodu izadji().
				Automobil se na Parkingu zadrzava 3 sekunde.
    Pri ulasku, ukoliko je Parking zauzet, automobil mora da saceka da se Parking oslobodi.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Parking {
    enum Stanje { SLOBODAN, ZAUZET };        //Enumeracija koja predstavlja tip stanja Parkinga.
    Stanje stanje;                           //Promenljva koja sadrzi trenutno stanje Parkinga.
    mutex m;                                 //Mutex i uslovna promenljiva neophodni za uslovnu sinhronizaciju.
    condition_variable slobodan;
  public:
    Parking() : stanje(SLOBODAN) {}          //Parking je na pocetku SLOBODAN.
    void udji();
    void izadji();
};

void Parking::udji() {                       //Funkcija koju pozivaju niti automobila na pocetku rada.
    unique_lock<mutex> l(m);
    while (stanje == ZAUZET) {               //Provera uslova. MORA while. Ukoliko je Parking zauzet nit mora
        slobodan.wait(l);                    //da ceka da se oslobodi. NEMA busy waitinga tj. konstantne provere ispunjenosti
    }                                        //uslova. Provera se vrsi samo po notifikaciji od druge niti.
                                             //OPTIMALNO iskoriscenje procesora.
    stanje = ZAUZET;                         //Zauzimanje Parkinga (promena stanja).
}

void Parking::izadji() {                     //Funkcija koju pozivaju niti automobila na kraju rada.
    unique_lock<mutex> l(m);
    stanje = SLOBODAN;                       //Bezuslvna promena stanja na slobodan.
    slobodan.notify_one();                   //Notifikacija jedne od niti koje cekaju na promenu stanja, kako bi mogle uci na
}                                            //Parking.

mutex m;

void automobil(Parking& p, int rba) {
   p.udji();
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " usao na Parking." << endl;
   }
   this_thread::sleep_for(chrono::seconds(3));
   p.izadji();
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " izasao sa Parkinga." << endl;
   }
}

const int automobila = 10;

int main() {
   Parking p;
   thread t[automobila];
   for(int i = 0; i < automobila; i++)
      t[i] = thread(automobil, ref(p), i + 1);
   for(int i = 0; i < automobila; i++)
      t[i].join();
    
    return 0;
}

