#ifndef KOORDINATOR_HPP_INCLUDED
#define KOORDINATOR_HPP_INCLUDED

using namespace std;

class Koordinator {
private:
    const int cekam_niti;     // Konstanta koja govori koliko niti se čeka na završetak pre nego što se aktivira poslednja.
public:
    Koordinator(int cn) : cekam_niti(cn) {
        // Proširiti po potrebi ...
    }

    // Metoda koju na svom KRAJU zovu niti (a i b) koje ne čekaju (izvršavaju se odmah).
    void zavrsio() {
        // Implementirati ...
    }

    // Metodu koju na svom POČETKU zovu niti (c) koje čekaju (ne izvršavaju se odmah).
    void cekam() {
        // Implementirati ...
    }
};

#endif // KOORDINATOR_HPP_INCLUDED
