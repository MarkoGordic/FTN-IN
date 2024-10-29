#ifndef VREMENSKAMASINA_HPP_INCLUDED
#define VREMENSKAMASINA_HPP_INCLUDED

#include "Putnik.hpp"
#include <iostream>
using namespace std;

enum StatusMasine
{
    ISPRAVNA,
    POKVARENA,
    PRETESKA
};

class VremenskaMasina
{
private:
    int destinacija;
    int trajanje;
    StatusMasine status;
    bool ispravna;
    Putnik *putnik;

public:
    VremenskaMasina() : putnik(nullptr)
    {
        destinacija = 0;
        trajanje = 0;
        status = ISPRAVNA;
        ispravna = true;
    }

    VremenskaMasina(int destinacija, int trajanje, bool ispravna, StatusMasine status) : putnik(nullptr)
    {
        this->destinacija = destinacija;
        this->trajanje = trajanje;
        this->ispravna = ispravna;
        this->status = status;
    }

    void dodajPutnika(Putnik *noviPutnik)
    {
        putnik = noviPutnik;
        if (putnik->gettezinaPrtljaga() + putnik->gettezinaPutnika() > 200)
        {
            status = PRETESKA;
        }
    }

    void ukloniPutnika()
    {
        delete putnik;
        putnik = nullptr;
    }

    void azurirajStatus()
    {
        if (putnik != nullptr && putnik->gettezinaPrtljaga() + putnik->gettezinaPutnika() > 200)
        {
            status = PRETESKA;
        }
        else if (!ispravna)
        {
            status = POKVARENA;
        }
    }

    void popraviMasinu()
    {
        if (status == POKVARENA)
        {
            status = ISPRAVNA;
            ispravna = true;
        }
    }
    Putnik *getPutnik() const
    {
        return putnik;
    }

    void putuj()
    {
        if (status == ISPRAVNA && putnik != nullptr && putnik->gettezinaPrtljaga() + putnik->gettezinaPutnika() <= 200)
        {
            putnik->settrenutnaGodina(destinacija);
        }
        else if (status == PRETESKA)
        {
            cout << "Masina je preteska, nemoguce putovanje" << endl;
        }
        else if (status == POKVARENA)
        {
            cout << "Masina je pokvarena, neophodno je popraviti" << endl;
        }
    }

    void ispisiMasinu() const
    {
        cout << "====PODACI O MASINI====" << endl;
        cout << "Destinacija: " << destinacija << endl;
        cout << "Trajanje: " << trajanje << endl;
        cout << "Status masine: ";
        switch (status)
        {
        case ISPRAVNA:
            cout << "ISPRAVNA" << endl;
            break;
        case PRETESKA:
            cout << "PRETESKA" << endl;
            break;
        case POKVARENA:
            cout << "POKVARENA" << endl;
            break;
        default:
            cout << "GRESKA" << endl;
        }
        cout << "Ispravnost: " << (ispravna ? "ispravno" : "neispravno") << endl;
        if (putnik != nullptr)
        {
            cout << "Tezina putnika: " << putnik->gettezinaPutnika() << endl;
            cout << "Tezina prtljaga: " << putnik->gettezinaPrtljaga() << endl;
        }
        else
        {
            cout << "Nema putnika u masini." << endl;
        }
    }
};

#endif // VREMENSKAMASINA_HPP_INCLUDED
