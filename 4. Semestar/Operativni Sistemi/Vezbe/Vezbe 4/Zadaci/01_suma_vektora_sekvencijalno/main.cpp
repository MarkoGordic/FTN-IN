/*
Napraviti sekvencijalni program koji izračunava sumu svih elemenata vektora, koristeći funkciju f():

typedef vector<double>::const_iterator ci;
void f(ci pocetak, ci kraj, double& zbir)

Funkcija f nalazi se u fajlu suma_vektora.h.

Pri tome, "ci" je definicija tipa koja služi tome da se kraće zapisuje tip vector<double>::const_iterator. Funkcija nema povratnu vrednost jer se rezultat prosleđuje kroz parametar "zbir".
*/

#include <iostream>
#include "suma_vektora.hpp"

using namespace std;

void testirajSumu() {
    vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double zbir;
    f(v.begin(), v.end(), zbir);

    cout << "Zbir vektora: " << zbir << endl;
}

int main() {
    testirajSumu();

    return 0;
}
