/*
    Ako zamislite jedinični kvadrat centriran oko koordinatnog početka i krug upisan
    u taj kvadrat. Verovatnoća da će nasumično odabrana tačka u okviru kvadrata 
    biti i u krugu, pod uslovom da je distribucija ravnomerna, je ravna odnosu njihovih 
    površina, tj, ravna je PI/4. Iskoristiti ovaj podataka da kroz Monte Karlo simulaciju
    izračunate vrednost broja PI tako što probate ovaj eksperiment veliki broj puta i vodite
    računa o tome koliko puta dobijete tačku u krugu, a koliko puta van kruga, te na kraju
    simulacije izračunate izmerenu verovatnoću i na osnovu nje, sračunate vrednost broja pi.
*/

#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <cmath>

using namespace std;

typedef chrono::high_resolution_clock hrc_t; 
hrc_t::time_point start = hrc_t::now();

bool uKrugu(double x, double y){
    return x*x + y*y <= 0.25; 
}

int main(){
    default_random_engine generator;
    hrc_t::duration d = hrc_t::now() - start;  
    generator.seed(d.count());
    uniform_real_distribution<double> dist(-0.5, 0.5);
    auto rd = bind(dist, generator);
    long da = 0;
    long ne = 0;
    for(int i = 0; i < 10000000;i++){
        double x = rd();
        double y = rd();
        if(uKrugu(x, y)){
            da++;
        }else{
            ne++;
        }
    }
    double ratio = (double)da / (double)(da + ne);
    ratio = ratio * 4;
    cout << ratio << endl;
    return 0;
}