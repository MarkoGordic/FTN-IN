/**
 * Napisati C++ program koji cita podatke o uniformnim distribucijama iz ulazne datoteke i potom za
 * svaku distribuciju generise po 10 brojeva, racuna njihov prosek, i nalazi najmanji i najveci broj. 
 * 
 * U ulaznoj datoteci "distribucije.txt" se u svakom redu nalaze informacije o donjoj i gornjoj granici
 * intervala u kojem treba generisati brojeve a potom vrednost koju treba iskoristiti kao jezgro (seed)
 * za generisanje nasumicnih brojeva. Navedene vrednosti su odvojene dvotackom. Granice su razlomljeni
 * brojevi a jezgro je veoma velika celobrojna vrednost.
 * 
 * U izlaznoj datoteci "brojevi.csv" treba da se nalaze u jednom redu odvojeni zarezom prvo 10 
 * izgenerisanih brojeva a potom i prosek, najmanji element i najveci element.
 * 
 * Treba napraviti jednu nit koja ce samo citati ulazne podatke, jednu nit koja ce samo pisati gotove
 * brojeve u datoteku i 6 niti radnika koji ce na osnovu podataka iz ulazne datoteke generisati sve
 * neophodno za ispis u izlaznu datoteku.
*/
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <queue>
#include <sstream>

#define BROJ_GENERISANIH_BROJEVA 10
#define BROJ_RADNIKA 6

using namespace std;
using namespace chrono;

struct trio {
    double donja, gornja;
    long long jezgro;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    queue<T> granice;
    condition_variable podaci_spremni;
    bool kraj;
public:
    UlazniPodaci(): kraj(false) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T par_granica) {
        unique_lock<mutex> propusnica(podaci_mx);
        granice.push(par_granica);
        podaci_spremni.notify_one();
    }

    bool preuzmi(T &par_granica) {
        unique_lock<mutex> propusnica(podaci_mx);
        while (daLiCekamPodatke()) {
            podaci_spremni.wait(propusnica);
        }

        if (jeLiKraj()) {
            return false;  // signal pozivajucem okruzenju da nece vise biti podataka
        }

        par_granica = granice.front();
        granice.pop();
        return true;  // signal pozivajucem okruzenju da je podataka uspesno preuzet iz bafera
    }

    // Imamo jednu nit koja ce stvarati podatke u ovom baferu podataka, ona zna kada je kraj i dovoljno je da ona jednim pozivom ove metode objavi kraj za sve ostale
    void objaviKraj() {
        unique_lock<mutex> propusnica(podaci_mx);
        kraj = true;
        podaci_spremni.notify_all();  // za slucaj da postoje radnici koji cekaju na nove podatke, budjenje istih da ne cekaju ako nema vise podataka da se preuzme jer je kraj
    }

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        return granice.empty() && !kraj;
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        return granice.empty() && kraj;
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    queue<T> brojevi_za_ispis;
    condition_variable podaci_spremni;
    bool kraj;
    int br_stvaralaca_podataka;
public:
    IzlazniPodaci(): kraj(false), br_stvaralaca_podataka(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T brojevi) {
        unique_lock<mutex> propusnica(podaci_mx);
        brojevi_za_ispis.push(brojevi);
        podaci_spremni.notify_one();
    }

    bool preuzmi(T &brojevi) {
        unique_lock<mutex> propusnica(podaci_mx);
        while (daLiCekamPodatke()) {
            podaci_spremni.wait(propusnica);
        }

        if (jeLiKraj()) {
            return false;
        }

        brojevi = brojevi_za_ispis.front();
        brojevi_za_ispis.pop();
        return true;
    }

    /**
     * Ovu metodu pre pocetka svog rada treba da pozovu stvaraoci podataka ovog bafera.
    */
    void prijavaStvaraocaPodataka() {
        unique_lock<mutex> propusnica(podaci_mx);
        br_stvaralaca_podataka++;
    }

    /**
     * Ovu metodu na kraju svog rada treba da pozovu stvaraoci podataka ovog bafera.
    */
    void odjavaStvaraocaPodataka() {
        unique_lock<mutex> propusnica(podaci_mx);
        br_stvaralaca_podataka--;
        if (!br_stvaralaca_podataka) {  // kada se desi odjava, proveravamo da li je broj stvaralaca pao na nula; ako jeste, znaci da nece biti novih podataka vise te treba objaviti kraj i probuditi uspavane niti
            kraj = true;
            podaci_spremni.notify_one();  // na izlazu moze da ceka samo nit koja pise u datoteku (u ovom konkretnom slucaju), pa je ovde dovoljan notify_ONE()
        }
    }

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        return brojevi_za_ispis.empty() && !kraj;
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        return brojevi_za_ispis.empty() && kraj;
    }
};


/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne podatke spremne za ispis.
*/
void radnik(UlazniPodaci<struct trio> &ulaz, IzlazniPodaci<vector<double>> &izlaz) {
    izlaz.prijavaStvaraocaPodataka();  // radnik stvara podatke za izlazni bafer tako da se i prijavljuje kod njega kao stvaralac podataka

    struct trio par_granica;  // promenljiva u koju ce metoda UlazniPodaci::preuzmi() smestiti preuzet element iz kolekcije 
    vector<double> brojevi;

    while (ulaz.preuzmi(par_granica)) {  // metoda UlazniPodaci::preuzmi() vraca true samo kada uspesno preuzme podatak; u telo petlje ide logika obrade podataka
        uniform_real_distribution<double> distribucija(par_granica.donja, par_granica.gornja);  // inicijalizacija objekta distribucije potrebnog za generisanje brojeva
        default_random_engine eng;  // svaki radnik pravi svoj generator brojeva ...
        eng.seed(par_granica.jezgro);  // ... i posebno ga priprema za generisanje
        brojevi.clear();  // u svakoj iteraciji treba da ocistimo vektor
        brojevi.resize(BROJ_GENERISANIH_BROJEVA + 3);  // postavljamo kapacitet i velicinu na velicinu dovoljnu da sadrzi svih BROJ_GENERISANIH_BROJEVA brojeva + prosek + minimum + maksimum
        double minimum, maksimum, suma, broj;
        suma = minimum = maksimum = broj = distribucija(eng);
        brojevi[0] = broj;
        for (int i = 1; i < BROJ_GENERISANIH_BROJEVA; i++) {
            broj = distribucija(eng);
            if (minimum > broj) {
                minimum = broj;
            }
            if (maksimum < broj) {
                maksimum = broj;
            }
            suma += broj;
            brojevi[i] = broj;
        }
        brojevi[BROJ_GENERISANIH_BROJEVA+0] = suma/BROJ_GENERISANIH_BROJEVA;
        brojevi[BROJ_GENERISANIH_BROJEVA+1] = minimum;
        brojevi[BROJ_GENERISANIH_BROJEVA+2] = maksimum;

        izlaz.dodaj(brojevi);
    }

    izlaz.odjavaStvaraocaPodataka();  // radnik se odjavljuje; poslednji radnik koji se odjavi uzrokuje objavu kraja u izlaznom baferu
}

/**
 * Logika citaca_iz_datoteke - nit koja radi citanje iz ulazne datoteke i salje u ulaznu kolekciju za radnike
*/
void citacf(string ime_ulazne_dat, UlazniPodaci<struct trio> &ulaz) {
    ifstream ulazna_dat(ime_ulazne_dat);
    double donja_granica, gornja_granica;
    long long jezgro;
    string red_datoteke, broj;

    if(ulazna_dat.is_open()) {
		while(getline(ulazna_dat, red_datoteke)) {  // citanje datoteke red po red
			istringstream red_datoteke_tok(red_datoteke);
 
			if(getline(red_datoteke_tok, broj, ':'))  // citanje podataka odvojenih dvotackom
				donja_granica = stod(broj);  // parsiranje broja iz stringa
            else
                continue;  // ako ne procitamo donju granicu kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
 
			if(getline(red_datoteke_tok, broj, ':'))  // citanje podataka odvojenih dvotackom
				gornja_granica = stod(broj);  // parsiranje broja iz stringa
            else
                continue;  // ako ne procitamo gornju granicu kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
 
			if(getline(red_datoteke_tok, broj, ':'))  // citanje podataka odvojenih dvotackom
				jezgro = stoll(broj);  // parsiranje broja iz stringa
            else
                continue;  // ako ne procitamo gornju granicu kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
            
			ulaz.dodaj({donja_granica, gornja_granica, jezgro});  // slanje strukture sa dva polja double koristeci se {}, sto je dozvoljeno jer ova struktura odgovara definiciji pair<double, double>
		}

        ulazna_dat.close();
	} else
		cerr << "CITAC: Nisam mogao da otvorim datoteku za citanje!\n";

    ulaz.objaviKraj();  // citac je jedna jedina nit koja stvara podatke tako da je dovoljno da samo ona kada zavrsi posao objavi kraj
}

/**
 * Logika pisaca_u_datoteku - nit koja radi pisanje u izlaznu datoteku podataka dobijenih od radnika
*/
void pisacf(IzlazniPodaci<vector<double>> &izlaz, string ime_izlazne_dat) {
    ofstream izlazna_dat(ime_izlazne_dat);
    vector<double> brojevi;

    if (izlazna_dat.is_open()) {
        //--------------------------------- ovaj deo koda nije obavezan a dace zaglavlje CSV datoteci
        for (int i = 0; i < BROJ_GENERISANIH_BROJEVA; i++) {
            izlazna_dat << i+1 << ".,";
        }
        izlazna_dat << "prosek,minimum,maksimum" << endl;
        //-------------------------------------------------------------------------------------------

        while (izlaz.preuzmi(brojevi)) {
            for (int i = 0; i < brojevi.size()-1; i++) {
                izlazna_dat << brojevi[i] << ",";
            }
            izlazna_dat << brojevi[brojevi.size()-1] << endl;
        }

        izlazna_dat.close();
    } else
		cerr << "PISAC: Nisam mogao da otvorim datoteku za pisanje!\n";
}

int main() {
    UlazniPodaci<struct trio> ulazni_podaci;  // bafer podataka koje salje citac_iz_datoteke a obradjuju radnici
    IzlazniPodaci<vector<double>> izlazni_podaci;  // bafer podataka koje pripremaju radnici a ispisuju se u datoteku u pisacu_u_datoteku
    thread citac{citacf, "distribucije.txt", ref(ulazni_podaci)},  // stvaranje niti citaca_iz_datoteke
           pisac{pisacf, ref(izlazni_podaci), "brojevi.csv"},      // stvaranje niti pisaca_u_datoteku
           radnici[BROJ_RADNIKA];

    for (auto &nit: radnici)
        nit = thread(radnik, ref(ulazni_podaci), ref(izlazni_podaci));  // stvaranje niti radnika

    for (auto &nit: radnici)
        nit.join();
    citac.join();
    pisac.join();

    return 0;
}
