#ifndef DEDAMRAZ_HPP_INCLUDED
#define DEDAMRAZ_HPP_INCLUDED

#include "list.hpp"
#include "NovogodisnjiPaketic.hpp"

class DedaMraz {
    private:
        List<NovogodisnjiPaketic> novogodisnjiPaketici;

    public:
        DedaMraz() : novogodisnjiPaketici() {}

        bool dodaj(const DinString& o, const Dete& d, int mu, Pol p) {
            NovogodisnjiPaketic novi(o, d, mu);
            novi.isporuci();

            NovogodisnjiPaketic np;
            int brojac = 0;

            if(novogodisnjiPaketici.empty()) {
                if(novogodisnjiPaketici.add(1, novi)) {
                    return true;
                }
            } else {
                for(int i = 1; i <= novogodisnjiPaketici.size(); i++) {
                    novogodisnjiPaketici.read(i, np);

                    if(np.getNamenjen().getPol() == p)
                        brojac++;
                }

                if(brojac < 5)
                    return novogodisnjiPaketici.add(novogodisnjiPaketici.size()+1, novi);
            }

            return false;
        }

        bool izbaci(int prihvatljiveGodine) {
            NovogodisnjiPaketic np;

            for(int i = 1; i <= novogodisnjiPaketici.size(); i++) {
                novogodisnjiPaketici.read(i, np);

                if(np.getMinimalanUzrast() < prihvatljiveGodine) {
                    return novogodisnjiPaketici.remove(i);
                }
            }

            return false;
        }

        double prosecanMinimalanUzrast() {
            double prosek = 0;
            NovogodisnjiPaketic np;

            for(int i = 1; i <= novogodisnjiPaketici.size(); i++) {
                novogodisnjiPaketici.read(i, np);
                prosek += np.getMinimalanUzrast();
            }

            return prosek / novogodisnjiPaketici.size();
        }

        void ispisi() const {
            cout << "********************** DEDA MRAZ **********************" << endl;

            if(novogodisnjiPaketici.empty()) {
                cout << "Nema novogodisnjih paketica!" << endl;
            } else {
                NovogodisnjiPaketic np;

                for(int i = 1; i <= novogodisnjiPaketici.size(); i++) {
                    novogodisnjiPaketici.read(i, np);
                    np.ispisi();
                }
            }

            cout << "*******************************************************" << endl;
        }
};

#endif // DEDAMRAZ_HPP_INCLUDED
