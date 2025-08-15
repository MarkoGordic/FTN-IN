// Napraviti konkurentni program koji modeluje kreditno poslovanje banke. Banka odobrava kredite u dinarima i u evrima.
//
// Klijent traži kredit pozivanjem operacije uzmi_kredit(), kojoj prosleđuje svotu koju želi da pozajmi od banke i valutu u kojoj želi da pozajmi. Klijent neko vreme koristi pozajmljena sredstva, pa ih vrati banci pozivanjem operacije vrati_kredit().
//
// Banka inicijalno poseduje određene svote dinara i evra koje pozajmljuje. Banka odobrava kredite dok god ima sredstava. Kada više nema sredstava, banka čeka da klijenti vrate prethodno odobrene kredite pre nego što odobri sledeći kredit. Banka odobrava kredite u proizvoljnom redosledu.
//
// Banka teži tome da klijent čiji je zahtev moguće ispuniti (postoje sredstva) ne čeka na kredit.
//
// Implementirati oznacene metode u klasi Banka u fajlu banka.h

#include <thread>
#include <vector>

#include "valuta.hpp"
#include "banka.hpp"
#include "kredit.hpp"

using namespace std;

void klijent(Banka& b, int svota, Valuta valuta, int rbk) {
   b.uzmi_kredit(rbk, svota, valuta);
   // Klijent koristi pozajmljeni novac:
   this_thread::sleep_for(chrono::seconds(1));
   b.vrati_kredit(rbk, svota, valuta);
}

const int DSVOTA = 30;
const int ESVOTA = 20;
const int DIN_KLIJENATA = 9;
const int EUR_KLIJENATA = 9;

void testirajSve() {
    Kredit k;
    Banka b{k, DSVOTA, ESVOTA};
    thread t[DIN_KLIJENATA];
    thread t1[EUR_KLIJENATA];

    vector<int> d_kolicine = {20, 5, 7, 13, 14, 4, 30, 6, 9};
    vector<int> e_kolicine = {10, 10, 5, 20, 6, 7, 15, 3, 12};

    for(int i = 0; i < DIN_KLIJENATA; i++)
        t[i] = thread(klijent, ref(b), d_kolicine[i], Valuta::DINAR, i);
    for(int i = 0; i < EUR_KLIJENATA; i++)
        t1[i] = thread(klijent, ref(b), e_kolicine[i], Valuta::EURO, DIN_KLIJENATA + i);

    for(int i = 0; i < DIN_KLIJENATA; i++)
        t[i].join();
    for(int i = 0; i < EUR_KLIJENATA; i++)
        t1[i].join();
}

int main() {
    testirajSve();

    return 0;
}
