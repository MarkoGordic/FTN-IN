/*
Napraviti konkurentni program  (koristeći funkciju f())
koji sabira korespodentne elemente kontejnera  a i b, 
a rezultat smešta u vektor zbir. 

typedef vector<double>::const_iterator ci; 
void f(ci a_begin, ci a_end, ci b_begin, vector<double>::iterator sum_begin); 
         
Program optimizovati za procesor sa 2 jezgra.
Napomene:
Podrazumeva se da su kontejneri a i b iste dužine.
Sabiranje korespodentnih elemenata je sabiranje matrica (vektora)
*/
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

typedef vector<double>::const_iterator ci;  //Pogledati resenje suma_vektora.cpp za objasnjenje const_iteratora.

//// suma_vektora.hpp
/*  Funkcija niti. Funkcija preuzima sledece parametre:
     1) ci a_begin -> iterator na pocetak dela vektora a
     2) ci a_end   -> iterator na kraj dela vektora a (dovoljan je samo jedan kraj)
     3) ci b_begin -> iterator na pocetak dela vektora b
     4) vector<double>::iterator sum_begin  -> iterator na pocetak dela vektora suma
     
     Ideja je da funkcija sabira korespodentne delove vektora a i b tj.  sum[sum_i] = a[a_i] + b[b_i],
     pri cemu sum_i = sum_begin, a_i = a_begin i b_i = b_begin. Svi iteratori se tokom sabiranja pomeraju,
     a samo se a_begin proverava da li je dosao do a_end (posto je dovoljno proveravati samo jednu granicu
     jer je kolicina elemenata ista u svakom vektoru).
*/
void f(ci a_begin, ci a_end, ci b_begin,      
       vector<double>::iterator sum_begin) {
    for(; a_begin != a_end;   ++a_begin, ++b_begin, ++sum_begin)
        *sum_begin = *a_begin + *b_begin;
}
//// KRAJ suma_vektora.hpp

//// niti.hpp
// v - vektor A čije elemente treba sumirati
// v - vektor B čije elemente treba sumirati
// povratna vrednost - suma korespondentnih elemenata vektora A i B, izračunata pozivanjem dve niti
vector<double> sumiraj(vector<double> a, vector<double> b) {
   vector<double> sum(a.size());                       //Vektor sume se incijalizuje kao prazan vektor duzine a.size().
   thread t1(f,  a.begin(), a.begin() + a.size()/2,    //Stvaranje niti t1. Nit t1 sabira korespodendne elemente vektora a i b od a.begin() do a.begin() + a.size()/2.
                 b.begin(), 
                 sum.begin()
   );
   thread t2(f,  a.begin() + a.size()/2,  a.end(),     //Stvaranje niti t2. Nit t2 sabira korespodendne elemente vektora a i b od a.begin() + a.size()/2 do a.end().
                 b.begin() + a.size()/2,
                 sum.begin() + a.size()/2
   );
   t1.join();
   t2.join();
   return sum;
}
//// KRAJ niti.hpp

void testirajSumu() {
   vector<double> a={1,2,3,4,5,6,7,8,9};
   vector<double> b={1,2,3,4,5,6,7,8,9};
   vector<double> sum(a.size());

   f(a.begin(), a.end(), b.begin(), sum.begin());

   cout << "Suma vektora pozivom funkcije f:" << endl;

   for (vector<double>::const_iterator it = sum.begin(); it != sum.end(); it++) {
      cout << *it << endl;
   }
}

void testirajNiti() {
   vector<double> a={1,2,3,4,5,6,7,8,9};
   vector<double> b={1,2,3,4,5,6,7,8,9};
   vector<double> sum;

   sum = sumiraj(a, b);

   cout << "Suma vektora, koriscenjem 2 niti: " << endl;

   for (vector<double>::const_iterator it = sum.begin(); it != sum.end(); it++) {
      cout << *it << endl;
   }
}

int main() {
   testirajSumu();
   testirajNiti();

   return 0;
}
