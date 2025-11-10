#ifndef EVIDENCIJALEKOVA_HPP_INCLUDED
#define EVIDENCIJALEKOVA_HPP_INCLUDED

#include "lek.hpp"
#include "list.hpp"

class EvidencijaLekova {
    private:
        DinString nazivApoteke;
        DinString datum;
        List<Lek> lekovi;

    public:
        EvidencijaLekova() : nazivApoteke("Gradska apoteka"), datum("01.01.2017.") {}

        bool dodajLek(long jkl, const char naziv[], int jedinicnaCena, int kolicina) {
            Lek lek(jkl, naziv, jedinicnaCena, kolicina);
            return lekovi.add(lekovi.size() + 1, lek);
        }

        bool dodajLek(const Lek& lek) {
            return lekovi.add(1, lek);
        }

        bool ukloniLek(int position){
            return lekovi.remove(position);
        }

        void sortirajLekove(){
            Lek l1, l2;

            for(int i = 1; i < lekovi.size(); i++) {

                for(int j = i + 1; j <= lekovi.size(); j++) {
                    lekovi.read(i, l1);
                    lekovi.read(j, l2);

                    if(l1.getVrednost() > l2.getVrednost()) {
                        lekovi.remove(i);
                        lekovi.add(i, l2);
                        lekovi.remove(j);
                        lekovi.add(j, l1);
                    }
                }
            }
        }

        friend ostream& operator<<(ostream& out, const EvidencijaLekova& evidencija) {
            out << endl << "********************************************************" << endl;
            out << "Naziv apoteke: " << evidencija.nazivApoteke<< " datum: " << evidencija.datum << endl;

            if(evidencija.lekovi.empty()){
                out << "Nema lekova u apoteci." << endl;
            }
            else {
                // 1. nacin
                // out << evidencija.lekovi;

                // 2. nacin
                Lek lek;

                for(int i = 1; i <= evidencija.lekovi.size(); i++){
                    evidencija.lekovi.read(i, lek);
                    out << lek << endl;
                }
            }

            out << "********************************************************" << endl << endl;
            return out;
        }
};

#endif // EVIDENCIJALEKOVA_HPP_INCLUDED
