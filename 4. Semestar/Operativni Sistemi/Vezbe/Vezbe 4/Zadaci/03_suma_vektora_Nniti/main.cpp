/*
Napraviti konkurentni program koji izračunava sumu svih elemenata vektora, koristeći funkciju f():

typedef vector<double>::const_iterator ci;
void f(ci pocetak, ci kraj, double& zbir);

Funkcija f nalazi se u fajlu suma_vektora.h.

Pri tome, "ci" je definicija tipa koja služi tome da se kraće zapisuje tip vector<double>::const_iterator.
Funkcija nema povratnu vrednost jer se rezultat prosleđuje kroz parametar "zbir".

Potrebno je implementirati i funkciju sumiraj (fajl niti.h) koja treba da pokrene više niti i da svakoj niti prosledi jedan deo elemenata ulaznog vektora. Sve niti treba da koriste funkciju f kako bi izračunale sumu svog dela vektora.

Podeliti računanje sume na N delova tako da svaka nit dobije relativno jednak broj elemenata. Taj broj elemenata treba da bude jednak: broj_elemenata_ulaza / N. Poslednja nit može dobiti i nešto veći broj elemenata na obradu u slučaju da ova dva broja nisu deljiva. 
Na primer:

1. 12 elemenata ulaza i 4 niti
   12 / 4 = 3 -> 3 elementa ulaza se prosleđuju svakoj niti

2. 12 elemenata ulaza i 5 niti
   12 / 5 = 2 (celobrojno deljenje brojeva odbacuje deo broja iza decimalnog zareza)
   2 elementa se prosleđuju nitima 0, 1, 2 i 3. Nit broj 4 dobija preostala 4 elementa.
*/

#include <iostream>
#include "suma_vektora.hpp"
#include "niti.hpp"

using namespace std;

void testirajSumu() {
    vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double zbir;
    f(v.begin(), v.end(), zbir);

    cout << "Zbir vektora: " << zbir << endl;
}

void testirajNiti() {
    vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double zbir;
    int n;

    cout << "Koliko niti da stvorim? ";        //Korisnicki unos kolicine niti (proizvoljan). Ne unositi vise niti nego sto ima elemenata vektora.
    cin >> n;
    zbir = sumiraj(v, n);

    cout << "Zbir vektora, koriscenjem " << n << " niti: " << zbir << endl;
}

int main() {
    testirajSumu();
    // Otkomentarisati kada implementirate funkciju sumiraj:
    //testirajNiti();

    return 0;
}
