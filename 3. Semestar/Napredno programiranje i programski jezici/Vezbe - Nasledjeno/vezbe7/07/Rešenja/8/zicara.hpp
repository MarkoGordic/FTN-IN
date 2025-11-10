#ifndef ZICARA_HPP_INCLUDED
#define ZICARA_HPP_INCLUDED

#include "putnik.hpp"
#include "list.hpp"

enum StanjeZicare { OTVORENA, ZATVORENA };

template <VrstaKarte SEZONA, int BROJ_SEDISTA, int INTERVAL>
class Zicara
{
private:
    List<Putnik*> putnici;
    StanjeZicare stanje;
    int ukupnoVoznji, ukupnoMinuta;
public:
    Zicara():stanje(ZATVORENA), ukupnoVoznji(0), ukupnoMinuta(0) {}

    void otvori()
    {
        stanje = OTVORENA;
        ukupnoVoznji = 0;
        ukupnoMinuta = 0;
    }

    void zatvori()
    {
        stanje = ZATVORENA;
        putnici.clear();
    }

    bool dodajPutnika(Putnik* p)
    {
        if(p->getVrstaKarte()!=SEZONA)
            return false;

        Putnik* pom;
        for(int i=1; i<=putnici.size(); i++)
        {
            putnici.read(i, pom);
            if(p->getMb()==pom->getMb())
                return false;
        }
        return putnici.add(putnici.size()+1, p);
    }

    int brojPutnika() const
    {
        return putnici.size();
    }

    bool preveziTuru()
    {
        if(stanje == ZATVORENA)
            return false;

        if(putnici.empty())
            return false;

        // ako je broj sedista zivare veci ili jednak broju putnika, to znaci da se ukupan broj voznji
        // povecava za onoliko koliko je putnika cekalo. Nakon prevozenja lista putnika koji cekaju ostaje
        // prazna
        if(BROJ_SEDISTA>=putnici.size()){
            ukupnoVoznji += putnici.size();
            putnici.clear();
        }
        // ako je broj sedista zivare manji od broja putnika, to znaci ne staju svi u zicaru
        // i moram izbaciti iz reda cekanja onoliko putnika koliko ih je stalo u zicaru
        // i uvecati ukupno voznji za svakog od njih.
        else{
            for(int i=0; i<BROJ_SEDISTA; i++){
                putnici.remove(1);
                ukupnoVoznji ++;
            }
        }

        ukupnoMinuta += INTERVAL;
        return true;
    }

    friend ostream& operator<<(ostream& os, const Zicara<SEZONA, BROJ_SEDISTA, INTERVAL>& z)
    {
        os << "Sezona: ";
        switch(SEZONA)
        {
        case(LETO):
            os<< "LETO"<<endl;
            break;
        case(SKI):
             os<<  "SKI"<<endl;
             break;
        case(SKI_OPENING):
             os<<  "SKI OPENING"<<endl;
             break;
        }
        os << "Broj sedista: " << BROJ_SEDISTA << endl;
        os << "Trajanje jedne voznje: " << INTERVAL << endl;
        os << "Stanje: " << (z.stanje == 1 ? "ZATVORENA" : "OTVORENA" )<< endl;
        os << "Ukupan broj voznji: " << z.ukupnoVoznji << endl;
        os << "Radno vreme(sati): " << z.getRadnoVremeUSatima() << endl;
        os << "Broj putnika u redu: " << z.putnici.size() << endl;

        if(z.putnici.size()>0)
        {
            os << "Lista putnika u redu:" << endl;
            Putnik *p;
            for(int i=1; i <= z.putnici.size(); i++)
            {
                z.putnici.read(i, p);
                os << *p << endl;
            }
        }

        return os;
    }

    double getRadnoVremeUSatima() const
    {
        return (double)ukupnoMinuta / 60;
    }

};

#endif // ZICARA_HPP_INCLUDED
