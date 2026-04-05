#ifndef BANKA_H_INCLUDED
#define BANKA_H_INCLUDED

#include <mutex>
#include <condition_variable>

#include "valuta.h"
#include "kredit.h"

using namespace std;

class Banka {
private:
    Kredit& kredit;
    int dsaldo, esaldo; // Ukupno novca u banci na dinarskom, odnosno deviznom računu
    mutex m; // Propusnica za pristup deljenim resursima
    condition_variable dlikvidan, elikvidan; // Redovi čekanja za uzimanje kredita u dinarima, odnosno u evrima
public:

    Banka(Kredit& kr, int inicijalni_dsaldo, int inicijalni_esaldo)  // Inicijalni saldo se prosleđuje spolja pri kreiranju objekta klase banka
        : kredit(kr), dsaldo(inicijalni_dsaldo), esaldo(inicijalni_esaldo) {}

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent zatraži kredit od banke.
    // Ukoliko banka nema odgovarajuća sredstva kako bi omogućila kredit, metoda će blokirati dok se ta sredstva ne oslobode.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.ceka kada nema sredstava odgovarajuće valute da se odobri kredit.
    // Potrebno je pozvati metodu kredit.dobio kada se kredit realizuje.
    void uzmi_kredit(int rbr, int svota, Valuta valuta) {
        unique_lock<mutex> l(m); // Tražimo propusnicu pre pristupa deljenim promenljivima
        if (valuta == DINAR) { // Ako je traženi kredit u dinarima
            while (dsaldo < svota) { // Dok god nema tražene količine dinara na računu banke, klijent mora da sačeka
                kredit.ceka(rbr, svota, valuta);
                dlikvidan.wait(l);
            }
            dsaldo -= svota; // Smanjuje se ukupna količina dinara u banci, jer se traženi iznos daje klijentu
            kredit.dobio(rbr, svota, dsaldo, valuta);
        } else { // Ako je kredit tražen u evrima
            while (esaldo < svota) { // Dok god nema tražene količine evra na računu banke, klijent mora da sačeka
                kredit.ceka(rbr, svota, valuta);
                elikvidan.wait(l);
            }
            esaldo -= svota; // Smanjuje se ukupna količinu evra u banci, jer se traženi iznos daje klijentu
            kredit.dobio(rbr, svota, esaldo, valuta);
        }
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent vrati kredit koji je prethodno uzeo od banke.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.vratio kada je kredit vraćen.
    void vrati_kredit(int rbr, int svota, Valuta valuta) { // Parametar je svota koja se vraća i valuta u kojoj se vraća
        unique_lock<mutex> l(m); // Traži se propusnica pre pristupa deljenim promenljivama
        if (valuta == DINAR) {// Ako se vraća kredit u dinarima
            dsaldo += svota; // Povećava se ukupna količina dinara u banci, jer je klijent vratio novac
            // Svima koji čekaju kredit u dinarima, javlja se da se pojavila nova količina novca u banci.
            // Novi saldo u banci je za neke klijente dovoljan da bi dobili kredit, a za neke je i dalje taj saldo premali.
            // Ako bi se za notifikaciju koristila metods notify_one(), moglo bi se desiti da bude probuđen klijent kojem je i novi iznos salda i dalje premali.
            // U tom slučaju bi program ostao u beskonačnom čekanju, jer bi se probuđeni klijent vratio u čekanje zbog nedostatka novca
            // a druge klijente niko ne bi probudio. Da do toga ne bi došlo, notifikacija se obavlja metodom notify_all(). Pošto se bude sve niti, među njima će biti bar jedan koji će moci da dobije kredit, a ostali će ponovo otići u čekanje.
            kredit.vratio(rbr, svota, dsaldo, valuta);
            dlikvidan.notify_all();
        } else { // Ako je reč o evrima, sve se ponavlja analogno vraćanju kredita u dinarima
            esaldo += svota;
            kredit.vratio(rbr, svota, esaldo, valuta);
            elikvidan.notify_all();
        }
    }
};

#endif // BANKA_H_INCLUDED
