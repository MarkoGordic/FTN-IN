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

using namespace std;

class Parking {
	enum Stanje { SLOBODAN, ZAUZET };       //Stanja Parkinga. Parking ima 1 mesto.
	Stanje stanje;
	mutex m;                                //Muteks za zastitu pristupa deljenim resursima (stvaranje kriticne sekcije).
	public:
		Parking() : stanje(SLOBODAN) {}
		void udji();
		void izadji();
};

void Parking::udji() {                       //Funkcija koju pozivaju niti automobila na pocetku rada.                 
    while (true) {                           //Konstantna provera ispunjenosti uslova. Izrazito OPTERECUJE procesor 
        unique_lock<mutex> lock(m);          //(tzv. busy waiting). Izrazito NEOPTIMALAN nacin provere uslova.
        if (stanje == SLOBODAN) {     //Provera zauzetosti Parkinga. Tek ukoliko je slobodan petlja se napusta (break).
            stanje = ZAUZET;          //Zauzimanje Parkinga (promena stanja).
            break;
        }
    }                   
}

void Parking::izadji() {                     //Funkcija koju pozivaju niti automobila na kraju rada.
    unique_lock<mutex> l(m);
    stanje = SLOBODAN;                       //Bezuslvna promena stanja na slobodan. Ovo je izvodljivo jer automobil koji je 
}                                            //vec na Parkingu (izlazi) nema potrebe da pita da li je Parking zauzet jer on
                                             //sam zauzima taj Parking. Tj. Parking je SIGURNO zauzet.
                                             
mutex m;                                     //Mutex terminala.

void automobil(Parking& p, int rba) {
   p.udji();                        //Automobil pokusava da udje. Ukoliko je vec neko na Parkingu ulazi se u cekanje.
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " usao na Parking." << endl;  //Ispis ID-a niti automobila koji ulazi.
   }
    //Sleep automobila pri koriscenju Parkinga. Za to vreme svi ostali automobili cekaju, dok trenutni automobil ne izadje.
   this_thread::sleep_for(chrono::seconds(3));  
   p.izadji();                     //Automobil izlazi sa Parkinga. Notificira jednog od automobila koji cekaju da moze da udje.
   { unique_lock<mutex> l(m);    
      cout << "Automobil " << rba << " izasao sa Parkinga." << endl;  //Ispis ID-a niti automobila koji izlazi.
   }
}

const int automobila = 10;

int main() {
   Parking p;                           //Stvaranje JEDNOG Parkinga. Datom objektu ce pristupati sve niti preko reference.
   thread t[automobila];
   for(int i=0; i<automobila; i++)
      t[i] = thread(automobil, ref(p), i + 1);
   for(int i=0; i<automobila; i++)
      t[i].join();
    
    return 0;
}
