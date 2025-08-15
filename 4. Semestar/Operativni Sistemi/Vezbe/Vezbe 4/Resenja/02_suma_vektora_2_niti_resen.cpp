/*Napraviti konkrentni program koji izračunava 
sumu svih elemenata vektora, koristeći funkciju f():

f(ci begin, ci end, double& zbir) pri cemu je 
ci typedef vector<double>::const_iterator

Podeliti racunanje sume na 2 dela tako da prvu polovinu vektora
sumira prva nit, a drugu polovinu druga nit.

Napomena: ovakva optimizacija sumiranja je znacajna kada se radi
na dvojezgarnom procesoru za vektore velike duzine.
*/

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

typedef vector<double>::const_iterator ci;          //Pogledati resenje suma_vektora_sekvencijalno.cpp za objasnjenje const_iteratora i funkcije f.

//// suma_vektora.hpp
/*
Funkcija sabiranja elemenata vektora. 

pocetak - iterator na prvi element koji se uzima u obzir pri računanju sume
kraj - iterator iza poslednjeg elementa koji se uzima u obzir pri računanju sume
zbir - parameter kroz koji funkcija treba da vrati izračunatu sumu
*/
void f(ci begin, ci end, double& zbir) {       
    zbir=0;                                    
    for(; begin != end; ++begin)                       //Prolazak kroz ceo vektor. Iteratori se mogu koristiti kao brojaci u for petlji.
        zbir += *begin;                                //Pristup elementu na koji pokazuje iterator begin, tj. dodavanje datog elementa na ukupan zbir.
}
//// KRAJ suma_vektora.hpp

//// niti.hpp
// v - vektor čije elemente treba sumirati
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem 2 niti (svaka treba da obradi jednu polovinu elemenata)
double sumiraj(vector<double> v) {
   double zbir1, zbir2;
   ci polovina = v.begin() + v.size()/2;            //Odredjivanje iteratora (pokazivaca) na sredinu vektora. Sredina se nalazi na v.begin() + polovina duzine vektora.
   thread t1(f,  v.begin(), polovina,  ref(zbir1)); //Stvaranje i pokretanje niti t1. Nit t1 sabira prvu polovinu vektora, tj. od iteratora v.begin() do iteratora polovina.
   thread t2(f,  polovina,  v.end(),   ref(zbir2)); //Stvaranje i pokretanje niti t2. Nit t2 sabira drugu polovinu vektora, tj. od iteratora polovina do iteratora v.end().
   t1.join();
   t2.join();
   return zbir1+zbir2;
}
//// KRAJ niti.hpp

void testirajSumu() {
    vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double zbir;
    f(v.begin(), v.end(), zbir);

    cout << "Zbir vektora: " << zbir << endl;
}

void testirajNiti() {
    vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double zbir;
    zbir = sumiraj(v);

    cout << "Zbir vektora, koriscenjem 2 niti: " << zbir << endl;
}

int main() {
    testirajSumu();
    testirajNiti();

    return 0;
}
