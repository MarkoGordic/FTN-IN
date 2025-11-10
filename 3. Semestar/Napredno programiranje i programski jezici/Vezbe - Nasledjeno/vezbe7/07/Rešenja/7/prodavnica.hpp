#ifndef PRODAVNICA_HPP_INCLUDED
#define PRODAVNICA_HPP_INCLUDED

#include "proizvod.hpp"
#include "list.hpp"

class Prodavnica {
private:
    DinString naziv;
    List<Proizvod*> proizvodi;
public:
    Prodavnica(const DinString& n): naziv(n) { }
    bool dodajProizvod(Proizvod& novi){

        Proizvod* pom;
        for (int i = 1; i <= proizvodi.size(); i++){

            proizvodi.read(i, pom);
            if (pom->getNaziv() == novi.getNaziv()){
                return false;
            }
        }

        return proizvodi.add(1,&novi);

    }

    void obrisiProizvod(const DinString& naziv){
        Proizvod* pom;
        for (int i = 1; i <= proizvodi.size(); i++){

            proizvodi.read(i, pom);
            if (pom->getNaziv() == naziv){
                proizvodi.remove(i);
                break;
            }
        }
    }

    void obrisiProizvod(int i){
        proizvodi.remove(i);
    }

    void akcija(int cena){

        Proizvod* p;
        for(int i = 1; i <= proizvodi.size(); i++){

            proizvodi.read(i,p);
            if (p->getCena() < cena){
                p->izracunajPopust();
            }
        }

    }

    double getProsecnaCena() const {

        if(proizvodi.size() < 1){
            return 0;
        }
        double suma = 0;
        Proizvod* p = NULL;

        for (int i = 1; i <= proizvodi.size(); i++){
            proizvodi.read(i, p);
            suma += p->getCena();
        }

        return suma / proizvodi.size();
    }

    friend ostream& operator<<(ostream& os, const Prodavnica& p){
        os << p.naziv << endl << "Proizvodi:" << endl;
        Proizvod* pom;
        for (int i = 1; i <= p.proizvodi.size(); i++){

            p.proizvodi.read(i,pom);
            pom->ispisi();
            os << endl;
        }

        return os;
    }
};


#endif // PRODAVNICA_HPP_INCLUDED

