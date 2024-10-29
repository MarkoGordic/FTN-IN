#include <iostream>
#include "Putnik.hpp"
#include "VremenskaMasina.hpp"
#include "Laboratorija.hpp"
using namespace std;

void ispisiLaboratoriju(const Laboratorija& lab)
{
    cout << "Naziv laboratorije: " << lab.naziv << endl;
    lab.masina.ispisiMasinu();

    if (lab.masina.getPutnik() != nullptr)
    {
        cout << "Podaci o putniku:" << endl;
        lab.masina.getPutnik()->ispisi();
    }
    else
    {
        cout << "Nema putnika u vremenskoj masini." << endl;
    }
}

int main()
{
    Putnik p('A', 2024, 2023, 58, 5);
    p.ispisi();

    VremenskaMasina vm(2050, 5, true, ISPRAVNA);
    vm.dodajPutnika(&p);
    vm.ispisiMasinu();
    vm.putuj();

    Laboratorija lab('L', 2050, 5, ISPRAVNA, true);
    lab.pokreniEksperiment(p);
    ispisiLaboratoriju(lab);

    return 0;
}

