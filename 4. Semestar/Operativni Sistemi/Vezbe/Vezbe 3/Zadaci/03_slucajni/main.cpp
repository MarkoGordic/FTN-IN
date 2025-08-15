#include <iostream>
#include <random>
#include <functional>
#include <chrono>

using namespace std;

/*
    Generisanje slučajnih brojeva je jako bitno za potrebe
    kriptografije, igara, i Monte Karlo simulacija. Računari
    su deterministički, te je nemoguće praviti __istinske__
    slučajne brojeve algoritmom.

    Umesto toga,  algoritmi uzimaju pravi nasumični broj
    'seed' koji je u prostijim slučajevima vreme, a u onima
    gde je bezbednost bitna prava 'entropija' odnosno, istinski
    nasumični brojevi dobijeni šumom na magistralnim linijama,
    ili čak raspadom radioaktivnih izotopa. Onda od tog početka
    prave sekvencu brojeva koja je takva da je jako, jako, jako
    teško predvideti sledeći broj na osnovu prethodnih bez
    seed-a.

    U C++-u generator slučajnosti je odvojen od toga kakve
    slučajne brojeve želimo. Tako da se prvo podešava generator
    slučajnosti kao takve, a onda se on koristi kroz distribuciju
    koja specificira koje osobine hoćemo da naši slučajni brojevi
    imaju.
*/

typedef chrono::high_resolution_clock hrc_t;
//Određujemo vreme preko ovoga: za sada ne razmišljajte puno
//O tome. Za par časova obradićemo tačno kako radi.
hrc_t::time_point start = hrc_t::now();

int main(){
    default_random_engine generator;
    //Generator slučajnosti
    hrc_t::duration d = hrc_t::now() - start;
    //Slučajan period vremena.
    generator.seed(d.count());
    //Uz pomoć toga, dobijamo seed vrednost tako da se
    //brojevi ne ponavljaju svaki put kada startujemo program
    //Ako uvek stavimo isti seed onda možemo uvek dobiti iste
    //Slučajne brojeve. To je ponekad tačno ono što želimo.
    uniform_int_distribution<int> dist(1, 6);
    //Raspodela koja se
    //1. Odnosi na cele brojeve (int)
    //2. Jednako je verovatan bilo koji broj  (uniform)
    //3. Ima raspon od 1 do 6, inkluzivno.
    cout << dist(generator) << endl;
    //Distribucija se može pozvati kao funkcija kada joj se
    //prosledi generator entropije.
    auto d6 = bind(dist, generator);
    //Lakše je da ne moramo stalno da prosleđujemo generator.
    //Tu nam pomaže bind. Bind-u prosledimo funkciju i neke njene
    //parametre, a on nam vrati novu funkciju koja poziva prvu
    //sa svim tim parametrima nameštenim. Tj, za funkciju f(x)
    //i neku vrednost 7, bind(f, 7) će vratiti funkciju g() koja
    //vraća vrednost f(7).
    cout << d6() << " " << d6() << endl;
    //Dva nasumična broja od 1-6. Tj. dve obične kockice.
    uniform_real_distribution<double> rdist(0, 1);
    //Distribucija može i nad realnim brojevima, kao ovde.
    auto dr = bind(rdist, generator);
    cout << dr() << " " << dr() << endl;
    normal_distribution<double> rn(0, 1);
    //Ovo je normalna distribucija. Tj. nije ista verovatnoća
    //za svaki broj, no verovatnoće variraju oko srednje vrednosti
    //ovde 0 tako da su vrednosti blizu nje verovatnije nego
    //daleko, a koliko je daleko određuje standardna devijacija
    //što je ovde 1. Ove verovatnoće formiraju čuvenu Gausovu
    //zvonastu krivu, i veliki broj prirodnih fenomena je tako
    //raspoređen.
    auto dn = bind(rn, generator);
    cout << dn() << " " << dn() << endl;
    return 0;
}
