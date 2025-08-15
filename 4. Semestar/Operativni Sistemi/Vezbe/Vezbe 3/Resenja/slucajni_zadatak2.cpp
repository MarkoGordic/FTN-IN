/*
    Koristeći konzolu i nasumično generisane slučajne brojeve
    po normalnoj distribuciji, vizuelizovati Gausovu krivu
    koristeći zvezdice. Gausova kriva po X osi ima moguće
    vrednosti koje su generisane, a po Y osi koliko su vrednosti
    u tom delu X ose zastupljene, procentualno, u svim
    generisanim vrednostima. Za opseg Y uzmite od 0 do
    najveće izmerene vrednosti od svih Y vrednosti,
    dok za X uzmite plus-minus 2.5 standardne devijacije
    od srednje vrednosti. Veličina uzorka slučajnih vrednosti,
    tj. koliko da generišete pre nego probate neka vam je
    8192. 
    
    Gausova kriva za srednju vrednost 5
    i standardnu devijaciju 2 izlgeda otprilike ovako ako se
    posmatra rotirano za 90 stepeni, kao u zadatku pod A:
    0-1: *
    1-2: ****
    2-3: *********
    3-4: ***************
    4-5: ******************
    5-6: *******************
    6-7: ***************
    7-8: ********
    8-9: ****
    9-10: *
    Gausova kriva za srednju vrednost 0 i SD 1, nacrtana
    uspravno izgleda otprilike ovako:
                                        * *                                     
                                     *  ***                                     
                                     * ***** *                                  
                                  *  **********                                 
                                  *  ********** *                               
                              ***************** *                               
                            * *******************                               
                            *********************                               
                           ************************ **                          
                          ****************************                          
                         *******************************                        
                       * *******************************                        
                      ********************************** *                      
                    * ********************************** *                      
                    ****************************************                    
                    ******************************************                  
                 * *******************************************                  
                ************************************************                
                **************************************************              
            *******************************************************             
            **********************************************************          
       * * ************************************************************         
   *  ********************************************************************      
   **************************************************************************   
********************************************************************************
    Odabrati jedan: 
    A) (Lakše) Prikazati Gausovu krivu rotiranu za 90 stepeni.
    B) (Teže) Prikazati je normalno
*/
#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <cmath>

using namespace std;

typedef chrono::high_resolution_clock hrc_t; 
hrc_t::time_point start = hrc_t::now();

const int CW = 80;
const int CH = 25;
const double M = 0;
const double SD = 1;

char screen[CW][CH];

void clear(){
    for(int i = 0; i < CW; i++){
        for(int j = 0;j < CH; j++){
            screen[i][j] = ' ';
        }
    }
}

void printScreen(){
    for(int j = CH - 1;j >= 0; j--)
    {
        for(int i = 0; i < CW; i++){
            cout << screen[i][j];
        }
        cout << endl;
    }
}

void drawBin(int col, int val){
    if(val > CH){
        val = CH;
    }
    for(int i = 0;i < val;i++){
        screen[col][i] = '*';
    }
}

int main(){
    clear();
    default_random_engine generator;
    hrc_t::duration d = hrc_t::now() - start;  
    generator.seed(d.count());
    normal_distribution<double> rn(M, SD);
    auto dn = bind(rn, generator);
    double sample[8192];
    for(int i = 0; i < 8192;i++){
        sample[i] = dn();
    }
    int bins = CW; 
    int bincounts[CW] = {0};
    double binvals[CW] = {0.0};
    double binwidth = (5 * SD) / bins; 
    int totalCount = 0;
    for(int i = 0; i < bins; i++){
        int count = 0;
        double lo = (M - 2.5 * SD) + i*binwidth;
        double hi = (M - 2.5 * SD) + (i+1)*binwidth;
        for(int j = 0; j < 8192;j++){
            if(sample[j] >= lo && sample[j] < hi){
                totalCount++;
                count++;
            }
        }
        bincounts[i] = count;
    }
    double maxval = 0.0;
    for(int i = 0; i < bins;i++){
        double vald = (double)bincounts[i] / (double)totalCount;
        binvals[i] = vald;
        if(vald > maxval){
            maxval = vald;
        }
    }
    for(int i = 0; i < bins;i++){
        binvals[i] = binvals[i] / maxval;
        int val = (int)round(binvals[i] * CH);
        drawBin(i, val);
    }
    printScreen();
    return 0;
}