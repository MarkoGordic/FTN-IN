#ifndef KAMION_HPP_INCLUDED
#define KAMION_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

string tip_robe(bool zapaljivo)
{
    return zapaljivo ? "zapaljive" : "obicne";
}

class Kamion {
public:
    // rbr       - Redni broj kamiona
    // kolicina  - Kolicina robe koja se prevozi (u tonama)
    // zapaljivo - Ukazuje na to da li je roba koja se prevozi zapaljiva (takva roba ima prioritet pri istovaru!)
    void ceka(int rbr, int kolicina, bool zapaljivo) {
        cout << "Kamion broj: " << rbr << " ceka da se oslobodi rampa. Nosi " << kolicina << " T " << tip_robe(zapaljivo) << " robe." << endl;
    }

    // rbr       - Redni broj kamiona
    // kolicina  - Kolicina robe koja se prevozi (u tonama)
    // zapaljivo - Ukazuje na to da li je roba koja se prevozi zapaljiva (takva roba ima prioritet pri istovaru!)
    // rampa     - Indeks rampe na kojoj se obavlja istovar
    void istovara(int rbr, int kolicina, bool zapaljivo, int rampa) {
        cout << "Kamion broj: " << rbr << " istovara se na rampi " << rampa << ". Nosi " << kolicina << " T " << tip_robe(zapaljivo) << " robe." << endl;
    }

    // rbr       - Redni broj kamiona
    void odlazi(int rbr) {
        cout << "Kamion broj: " << rbr << " je zavrsio istovar i odlazi." << endl;
    }
};

#endif // KAMION_HPP_INCLUDED
