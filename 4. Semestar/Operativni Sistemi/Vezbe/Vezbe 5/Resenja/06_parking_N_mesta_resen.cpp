/*
    Definisati klasu Parking koja modeluje Parking prostor kapaciteta N mesta.
    Kapacitet Parkinga proslediti kao argument konstruktoru, pri instanciranju deljene promenljive.

	Klasa Parking ima operacije:
        void Parking::udji();
        void Parking::izadji();

	Automobili koji dolaze na Parking su predstavljeni nitima.
	Za ulazak na Parking, automobil poziva metodu udji().
	Za izlazak sa Parkinga, automobil poziva metodu izadji().
	Automobil se na Parkingu zadrzava od 1 do 3 sekunde.
    Pri ulasku, ukoliko su sva Parking mesta zauzeta, automobil mora da saceka da se neko Parking
    mesto oslobodi.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

using namespace std;

class Parking {
    mutex m;
    condition_variable slobodan;
    int slobodnih_mesta;                        //Broj slobodnih mesta. Slicno kao kod zadatka a_i_b_pre_c, ovde ce brojac
                                                //predstavljati stanje deljene promenljive (Parkinga).
  public:
    Parking(int N) : slobodnih_mesta(N) {}      //Na pocetku ima N slobodnih mesta na Parkingu (realniji scenario nego samo 1).
    void udji();
    void izadji();
};

void Parking::udji() {
    unique_lock<mutex> l(m);
    while (slobodnih_mesta == 0) {              //Dogod NEMA slobodnih mesta na parkignu svaki novi automobil mora da ceka.
        slobodan.wait(l);
    }
    --slobodnih_mesta;                          //Ukoliko je uspeo da udje na Parking, automobil smanjuje broj slobodnih mesta.
}

void Parking::izadji() {
    unique_lock<mutex> l(m);
    slobodan.notify_one();                      //Kada izlazi automobil povecava broj slobodnih mesta i notificira jednog od
    ++slobodnih_mesta;                          //automobila koji cekaju u redu.
}

mutex m;
void automobil(Parking& p, int rba, int sekundi_na_parkingu) {
   p.udji();
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " usao na Parking." << endl;
   }
   this_thread::sleep_for(chrono::seconds(sekundi_na_parkingu));
   p.izadji();
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " izasao sa Parkinga." << endl;
   }
}

const int automobila = 10;
const int KAPACITET = 3;

int main() {
   Parking p(KAPACITET);                //Parking ima na pocetku KAPACITET slobodnih mesta.
   thread t[automobila];
   default_random_engine dr;
   dr.seed(chrono::steady_clock::now().time_since_epoch().count());
   uniform_int_distribution<int> trajanje_zadrzavanja_na_parkingu(1, 3);
   for(int i=0; i<automobila; i++)
      t[i] = thread(automobil, ref(p), i + 1,  trajanje_zadrzavanja_na_parkingu(dr));  //Automobil se zadrzava izmedju 1 i 3 sekunde na Parkingu.
                                                                                       //Ovo se radi da ne bi svi ulazili i izlazili u ista vremena.
   for(int i=0; i<automobila; i++)
      t[i].join();
    
    return 0;
}

