/*		
Napraviti konkurentni program koji modeluje klasu brojača. Interfejs klase sadrži sledeće metode: 

class Brojac {
   public:
      void inc();
      void dec();
      friend ostream& operator<<(ostream& , Brojac& );
};

Metode inc i dec povećavaću i smanjuju vrednost brojača respektivno. Operator << služi za ispis brojača na ekran.

Klasa treba da zaštiti konzistentnost brojača u datim metodama uz pomoć klasa mutex i unique_lock. 

Kreirati 1 globalni objekat brojača kome će pristupati 2 niti. 

Kreirati 2 niti pri čemu jedna nit poziva metodu uvećavanja brojača 1000000 puta a druga metodu smanjivanja brojača 1000000 puta. Na kraju programa ispisati konačnu vrednost brojača nakon uvećavanja i smanjivanja.
*/

#include <thread> 
#include <iostream> 
#include <mutex>

using namespace std;

const int ITERATIONS=100000000;

// Klasa u sebi sadrži podatke i obezbeđuje thread-safe pristup ovim podacima
// Dakle, međusobna isključivost je enkapsulirana u klasu, pozivalac operacija ne mora da vodi računa o međusobnoj isključivosti
class Brojac {
   mutex m; // Propusnica pripada klasi i obezbeđuje sprečavanje štetnog preplitanja pri vršenju operacija nad objektima klase 
   int broj; // Vrednost Brojaca
 public:
   Brojac() : broj(0) {} // Inicijalna vrednost je nula
   void inc() { unique_lock<mutex> l(m); ++broj; } // Operacija povećava Brojac, ali pre toga zaključava propusnicu i na taj način sprečava štetno preplitanje pri izmeni
   void dec() { unique_lock<mutex> l(m); --broj; }// Operacija smanjuje Brojac, ali pre toga zaključava propusnicu i na taj način sprečava štetno preplitanje pri izmeni
   friend ostream& operator<<(ostream& os, Brojac& b) { // Preklopljen operator za ispis objekta klase Brojac. Ispisuje se atribut "broj" iz objekta
      unique_lock<mutex> l(b.m); // Pre pristupa broju, zaključava se propusnica da bi se sprečilo štetno preplitanje
      os << b.broj <<endl;
      return os;
   }
};
Brojac br; // Da bi obe niti menjale isti Brojac, on je definisan kao globalna promenljiva

void inkrement() {
   // Specificirani broj puta se zatraži povećavanje Brojaca. Pozivalac ne vodi računa o štetnom preplitanju, to je odgovornost klase
   for(int i = 0; i < ITERATIONS; ++i) 
      br.inc();	
}

void dekrement() {
   for(int i = 0; i < ITERATIONS; ++i)  // Specificirani broj puta se zatraži smanjivanje Brojaca
      br.dec();
}

int main() {
   thread t1(inkrement);
   thread t2(dekrement);
   t1.join();
   t2.join();
   cout<<br<<endl; // Može ovako, pošto je operator za ispis za klasu Brojac preklopljen
}
