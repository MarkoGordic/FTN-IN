// Napraviti konkurentni program koji modeluje kreditno poslovanje banke.
// Banka odobrava kredite u dinarima i u evrima.

// Klijent trazi kredit pozivanjem operacije uzmi_kredit(),
// kojoj prosledjuje svotu koju zeli da pozajmi od banke i valutu u kojoj zeli da pozajmi.
// Klijent neko vreme koristi pozajmljena sredstva, pa ih vrati banci
// pozivanjem operacije vrati_kredit().

// Banka inicijalno poseduje odredjene svote dinara i evra
// na dva razlicita racuna, koje pozajmljuje.
// Banka odobrava kredite dok ima sredstava.
// Kada vise nema sredstava, banka ceka da klijenti vrate
// prethodno odobrene kredite pre nego sto odobri sledeci kredit.
// Banka odobrava kredite u proizvoljnom redosledu.

// Banka tezi tome da klijent ciji je zahtev moguce ispunitini
// (postoje sredstva) ne ceka na kredit.

// Komentari su obavezni


// Obrisati main i implementaciju banke (ostaviti enum).


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

mutex term_m;

class Banka {
   int dsaldo, esaldo; //ukupno novca u banci na dinarskom, odnosno deviznom racunu
   mutex m; //propusnica za pristup deljenim resursima
   condition_variable dlikvidan, elikvidan; //redovi cekanja za uzimanje kredita u dinarima, odnosno u evrima
public:
   enum valute {DINAR = 0, EVRO}; //tipovi valuta
   Banka(int inicijalni_dsaldo, int inicijalni_esaldo)  //inicijalni saldo se prosledjuje spolja pri kreiranju objekta klase banka
      : dsaldo(inicijalni_dsaldo), esaldo(inicijalni_esaldo) {}
   int uzmi_kredit( int svota, valute valuta);
   int vrati_kredit(int svota, valute valuta);
};

int Banka::uzmi_kredit(int svota, valute valuta) { //parametar je svota i valuta u kojoj se uzima
   unique_lock<mutex> l(m); //trazimo propusnicu pre pristupa deljenim promenljivim
   int saldo; //lokalna promenljiva u koju cemo upisati ono sto treba da bude povratna vrednost funkcije
   if(valuta == DINAR) { //ako trazimo kredit u dinarima
      while(dsaldo<svota) //dok god nema trazene kolicine dinara na racunu banke, klijent mora da saceka
         dlikvidan.wait(l);
      dsaldo -= svota; //smanjujemo ukupnu kolicinu dinara u banci, jer se trazeni iznos daje klijentu
      saldo = dsaldo; //postavljanje povratne vrednosti
    } else { //ako je kredit trazen u evrima
      while(esaldo < svota) //dok god nema trazene kolicine evra na racunu banke, klijent mora da saceka
         elikvidan.wait(l);
      esaldo -= svota;//smanjujemo ukupnu kolicinu evra u banci, jer se trazeni iznos daje klijentu
      saldo = esaldo;//postavljanje povratne vrednosti
    }
   return saldo;
}

int Banka::vrati_kredit(int svota, valute valuta) { //parametar je svota koja se vraca i valuta u kojoj se vraca
   int saldo; //lokalna promenljiva u koju cemo upisati ono sto treba da bude povratna vrednost funkcije
   unique_lock<mutex> l(m);//trazimo propusnicu pre pristupa deljenim promenljivim
   if(valuta == DINAR) {//ako vracamo kredit u dinarima
      dsaldo += svota; //povecavamo ukupnu kolicinu dinara u banci, jer je klijent vratio novac u banku
      //javljamo svima koji cekaju dinare da se pojavila nova kolicina novca u banci.
	  //Novi saldo u banci je za neke klijente dovoljan da bi dobili kredit, a za neke je i dalje taj saldo premali
	  //Da se ne bi desilo da pozivom notify_one() probudimo nekog od klijenata kojima je i novi iznos salda i dalje premali
	  //(u toj varijanti bi program otisao u beskonacno cekanje, jer bi se probudjeni klijent vratio u cekanje zbog nedostatka novca
	  // a druge klijente niko ne bi probudio), budimo sve klijente. Medju njima ce MOZDA biti bar jedan koji ce moci da dobije kredit,
	  //a ostali ce ponovo otici u cekanje. 

      //Moguc je i scenario da niti jedan klijent nakon budjenja sa notify_all() ne bude mogao da zauzme dovoljno
      //sredstava (npr. ukoliko prva 2 klijenta koriste polovinu maksimalnog broja dinara u banci, a svi sledeci klijenti traze maksimalan broj dinara).
      //Tada vracanje jedne polovine dinara nece biti dovoljno niti jednom od klijenata u cekanju. Tek kad oba klijenta vrate svoje polovine
      //program ce moci da nastavi rad. Ovaj scenario je veoma specifican ali je moguc.
	   dlikvidan.notify_all();
      saldo = dsaldo;  //postavljanje povratne vrednosti
   } else { //ako je rec o evrima, sve se ponavlja analogno vracanju kredita u dinarima
      esaldo += svota;
      elikvidan.notify_all();
      saldo = esaldo;
   }
   return saldo;
}

string naziv_valute(Banka::valute valuta) {
   if(valuta == Banka::DINAR)  return "dinar";
   else                      return "evro";
}

void klijent(Banka& b, int svota, Banka::valute valuta, int rbk) {
   int saldo;
   {
   unique_lock<mutex> l(term_m);
   cout << "Klijent: " << rbk << " trazi na zajam " << svota
        << ", valuta: " << naziv_valute(valuta) << endl;
   }
   saldo = b.uzmi_kredit(svota, valuta);
   {
   unique_lock<mutex> l(term_m);
   cout << "Klijent: " << rbk << " dobio " << svota
        << ", u banci ostalo: " << saldo
        << ", valuta: " << naziv_valute(valuta) << endl;
   }
   // klijent koristi pozajmljeni novac
   this_thread::sleep_for(chrono::seconds(1));
   saldo = b.vrati_kredit(svota, valuta);
   unique_lock<mutex> l(term_m);
   cout << "Klijent: " << rbk << " vratio " << svota
        << ", u banci ostalo: " << saldo
        << ", valuta: " << naziv_valute(valuta) << endl;
}

const int DSVOTA = 30;
const int ESVOTA = 20;
const int DIN_KLIJENATA = 9;
const int EVR_KLIJENATA = 9;

int main() {
   Banka b{DSVOTA, ESVOTA};
   thread t[DIN_KLIJENATA];
   thread t1[EVR_KLIJENATA];

   vector<int> d_kolicine = {20, 5, 7, 13, 14, 4, 30, 6, 9};
   vector<int> e_kolicine = {10, 10, 5, 20, 6, 7, 15, 3, 12};

   for(int i = 0; i < DIN_KLIJENATA; i++)
      t[i] = thread(klijent, ref(b), d_kolicine[i], Banka::DINAR, i);
   for(int i = 0; i < EVR_KLIJENATA; i++)
      t1[i] = thread(klijent, ref(b), e_kolicine[i], Banka::EVRO,
                     DIN_KLIJENATA + i);
   for(int i = 0; i < DIN_KLIJENATA; i++)
      t[i].join();
   for(int i = 0; i < EVR_KLIJENATA; i++)
      t1[i].join();

   return 0;
}
