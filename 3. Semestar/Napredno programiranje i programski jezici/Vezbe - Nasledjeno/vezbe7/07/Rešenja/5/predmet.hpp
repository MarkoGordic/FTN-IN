#ifndef PREDMET_HPP_INCLUDED
#define PREDMET_HPP_INCLUDED

#include "kolokvijum.hpp"
#include "list.hpp"

class Predmet {
    private:
        DinString naziv;
        List<Test*> testovi;

    public:
        Predmet(const char* n = "") : naziv(n) {}
        Predmet(const Predmet& p) : naziv(p.naziv), testovi(p.testovi) {}

        void dodajTest(Test& t){
            testovi.add(testovi.size()+1, &t);
        }

        DinString getNaziv() const{
            return naziv;
        }


        bool polozio() const {
            Test* t;
            for (int i = 1; i <= testovi.size(); i++){
                testovi.read(i, t);
                if(! t -> polozio() )
                    return false;
            }

            if(getUkupniPoeni() > 55){
                return true;
            } else {
                return false;
            }
        }

        int getUkupniPoeni() const {
            Test* t;
            int poeni = 0;

            for (int i = 1; i <= testovi.size(); i++){
                testovi.read(i, t);
                poeni += t -> getPoeni();
            }

            return poeni;
        }

        void ispis() const {
            cout << "****************" << endl;
            cout << "Predmet: " << naziv << endl;

            if(testovi.size() == 0) {
                cout << endl << "Nema testova." << endl;
            }
            else {
                Test* t;
                cout << "Testovi: " << endl;
                for (int i = 1; i <= testovi.size(); i++){
                    testovi.read(i, t);
                    t -> ispis();
                }
            }
            cout << "****************" << endl;
        }
};

#endif // PREDMET_HPP_INCLUDED
