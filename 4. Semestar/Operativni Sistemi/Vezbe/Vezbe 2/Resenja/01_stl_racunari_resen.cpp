/* Napisati program koji omogucuje evidenciju fakultetskih ucionica.
   Za svaku ucionicu potrebno je evidentirati naziv ucionice, kvadraturu i racunare
   koji se nalaze u ucionici. Za svaki racunar evidentiraju se podaci o hard disku i
   procesoru.

   U okviru main funkcije, definisati jednu ucionicu koja sadrzi dva racunara.
   Zatim je potrebno na konzolu ispisati podatke o svakom racunaru u ucionici.

*/

#include <iostream>
#include <string>
#include <list>

#define MAX 100

using namespace std;

//klasa modeluje Racunar za koji se evidentira naziv diska i naziv procesora
class Racunar {
    private:
        string HDD;
        string CPU;
    public:
        void setHDD(string d) {
            HDD = d;
        }
        string getHDD() {
            return HDD;
        }
        void setCPU(string p) {
            CPU = p;
        }
        string getCPU() {
            return CPU;
        }
};

//klasa modeluje ucionicu za koju se evidentira naziv, kvadratura i racunari koji se nalaze u ucionici
class Ucionica {
    private:
        string naziv;
        double kvadratura;
        //Racunar racunari[MAX]; //prva varijanta - racunari u ucionici predstavljeni nizom
        list<Racunar> racunari; //druga varijanta - racunari u ucionici su elementi STL kontejnera
    public:
        void setNaziv(string n) {
            naziv = n;
        }
        string getNaziv() {
            return naziv;
        }
        void setKvadratura(double kv) {
            kvadratura = kv;
        }
        double getKvadratura() {
            return kvadratura;
        }
        //sa nizom
        /*void dodajRacunarNa(Racunar r, int i) {
            racunari[i] = r;
        }
        Racunar preuzmiRacunarSa(int i) {
            return racunari[i];
        }*/
        void dodajRacunar(Racunar r) {
            racunari.push_back(r); //ubacivanje objekta klase racunar u STL kontejner
        }
        list<Racunar> getRacunari() {
            return racunari;
        }
};


int main()
{
    //kreiranje jednog objekta klase ucionica
    Ucionica u;
    u.setNaziv("MIA2-3");
    u.setKvadratura(100);

    //kreiranje dva objekta klase racunar
    Racunar r1;
    r1.setHDD("Seagate");
    r1.setCPU("Intel i5");
    Racunar r2;
    r2.setHDD("Western Digital");
    r2.setCPU("Intel i7");

    //prva varijanta - rad sa nizom
    /*u.dodajRacunarNa(r1,0);
    u.dodajRacunarNa(r2,1);

    for (int i = 0; i < 2; i++) {
        cout << "Procesor racunara[" << i << "]:" << u.preuzmiRacunarSa(i).getCPU() << endl;
        cout << "Disk racunara[" << i << "]:" << u.preuzmiRacunarSa(i).getHDD() << endl;
    }*/

    //druga varijanta - rad sa STL kontejnerom
    u.dodajRacunar(r1);
    u.dodajRacunar(r2);

    list<Racunar> racunari = u.getRacunari(); //preuzimanje liste svih racunara
    list<Racunar>::iterator it; //deklaracija iteratora na element STL kontejnera
    /*Iterator inicijalno pokazuje na prvi element kontejnera. Na kraju svake iteracije se pomeri na naredni element.
     U petlji se ostaje dok god se ne dodje do kraja kontejnera (metoda end() vraca iterator koji pokazuje
     "nakon" poslednjeg elementa). Posto elementi mogu biti na proizvoljnim memorijskim lokacijama,
     pri utvrdjivanju uslova izlaska iz petlje ne mozemo porediti operatorom "<", jer ako posmatramo dva elementa,
     element sa nizim indeksom u kontejneru moze biti na visoj adresi u memoriji.
    */
    int i = 0;
    for (it = racunari.begin(); it != racunari.end(); it++, i++) {
        cout << "Procesor racunara[" << i << "]:" << it->getCPU() << endl;
        cout << "Disk racunara[" << i << "]:" << it->getHDD() << endl; //ispis podataka o disku racunara na koji iterator pokazuje u ovoj iteraciji
    }
}

