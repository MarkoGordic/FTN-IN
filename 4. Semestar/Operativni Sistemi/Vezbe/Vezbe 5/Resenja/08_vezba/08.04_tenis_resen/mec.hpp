#ifndef MEC_HPP_INCLUDED
#define MEC_HPP_INCLUDED

#include <iostream>

using namespace std;

class Mec {
public:
    // rbr   - Redni broj meca
    // teren - Indeks terena na kojem mec treba da se odigra
    void ceka(int rbr, int teren) {
        cout << "Mec " << rbr << " mora da saceka posto je teren " << teren << " zauzet." << endl;
    }

    // rbr   - Redni broj meca
    // teren - Indeks terena na kojem mec treba da se odigra
    void pocinje(int rbr, int teren) {
        cout << "Mec " << rbr << " na terenu " << teren << " upravo pocinje." << endl;
    }

    // rbr   - Redni broj meca
    // p     - Podaci o mecu
    void zavrsen(int rbr, Podaci p) {
        duration<double, milli> cekao = p.pocetak - p.dosao;
        cout << "Mec " << rbr << " je zavrsen. Trajao je: " << p.trajanje.count() << " milisekundi. Takmicari su na pocetak meca cekali " << cekao.count() << " milisekundi. " << endl;
    }
};

#endif // MEC_HPP_INCLUDED
