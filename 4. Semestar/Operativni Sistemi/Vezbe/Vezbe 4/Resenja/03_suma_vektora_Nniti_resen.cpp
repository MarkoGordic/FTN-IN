/*Napraviti konkrentni program koji izračunava 
sumu svih elemenata vektora, koristeći funkciju f():

f(ci begin, ci end, double& zbir) pri cemu je 
ci typedef vector<double>::const_iterator

Podeliti racunanje sume na N delova tako svaka nit sabira
duzina vektora/broj niti elemenata vektora. 
*/
#include<iostream>
#include<vector>
#include<thread>

using namespace std;

typedef vector<double>::const_iterator ci;     //Pogledati resenje suma_vektora_sekvencijalno.cpp za objasnjenje const_iteratora i funkcije f.

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
// n - koliko niti treba pokrenuti
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem n niti (svaka nit treba da obradi jedan deo elemenata)
double sumiraj(vector<double> v, int n) {
   double zbir[n];                           
   ci begin = v.begin();                      //Iterator na pocetak vektora.
   ci end = begin + v.size()/n;               //Iterator na kraj prvog dela vektora. Vektor se deli na N delova, pri cemu je kraj prvog dela na begin + v.size()/n.
   thread t[n];                               //Niz od N niti (objekata niti). 

   for(int i = 0; i<n-1; ++i) {                  
      t[i] = thread(f, begin, end,  ref(zbir[i]));  //Svaka nit uzima pocetak i kraj svog dela vektora (iteratore) kao i jedan od zbirova iz niza zbirova.
      begin = end;                                  //Pocetak sledeceg dela vektora koji se obradjuje je kraj prethodnog dela.
      end += v.size()/n;                            //Kraj sledeceg dela vektora koji se obradjuje je kraj prethodnog dela + v.size()/n.
   }
   t[n-1] = thread(f, begin, v.end(),  ref(zbir[n-1]));     //Posebno izdvojen zadnji zbir (deo vektora). Ovo se radi iz razloga sto broj elemenata vektora ne mora biti deljiv
                                                            //sa brojem niti. Npr. 10/3, pa moramo da odvojimo i posebno obradimo zadnji deo vektora. U 10/3 verziji prve
                                                            //2 niti bi obradjivale po 3 elementa vektora a zadnja nit 4.
   for(int i = 0; i<n; ++i) {
      t[i].join();                                          //Cekanje niti main da se sve niti niza niti t zavrse.
   }
   
   double z = 0;
   for(int i = 0; i<n; ++i) {                            //Ispis pojedinacnih zbirova svih niti i spajanje konacnog zbira.
      cout << "zbir[" << i << "]= " << zbir[i] << endl;
      z += zbir[i];
   }
   return z;
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
   int n;

   cout << "Koliko niti da stvorim? ";        //Korisnicki unos kolicine niti (proizvoljan). Ne unositi vise niti nego sto ima elemenata vektora.
   cin >> n;

   zbir = sumiraj(v, n);

   cout << "Zbir vektora, koriscenjem " << n << " niti: " << zbir << endl;
}

int main() {
   testirajSumu();
   testirajNiti();

   return 0;
}
