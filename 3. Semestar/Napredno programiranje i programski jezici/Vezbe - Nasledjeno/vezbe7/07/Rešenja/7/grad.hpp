#ifndef GRAD_HPP_INCLUDED
#define GRAD_HPP_INCLUDED

#include "prodavnica.hpp"

class Grad {
private:
    DinString naziv;
    List<Prodavnica*> prodavnice;
public:
    Grad() : naziv("Novi Sad") {}
    Grad(const DinString& ds) : naziv(ds) {}

    void ispisiNajjeftinijuProdavnicu(){

        if (prodavnice.size() == 0){
            cout << "Nema prodavnica u gradu";
        } else {

            Prodavnica* najjeftinija;
            prodavnice.read(1,najjeftinija);
            Prodavnica* pom;
            for (int i = 2; i <= prodavnice.size(); i++){
                prodavnice.read(i,pom);
                if (pom->getProsecnaCena() < najjeftinija->getProsecnaCena()){
                    prodavnice.read(i,najjeftinija);
                }
            }

            cout << *najjeftinija << endl;

        }
    }

    bool dodajProdavnicu(Prodavnica& p){
        return prodavnice.add(1, &p);
    }


};

#endif // GRAD_HPP_INCLUDED

