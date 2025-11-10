#include <cstdlib>
#include "kocka.hpp"

Kocka::Kocka(){
    vrednost = 1;
}

Kocka::Kocka(int broj){
    vrednost = broj;
}

Kocka::Kocka(const Kocka &kocka){
    vrednost = kocka.vrednost;
}

void Kocka::baci(){
    vrednost = rand() % (6 - 1 + 1) + 1;
}

int Kocka::getVrednost() const {
    return vrednost;
};
