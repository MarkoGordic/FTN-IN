#ifndef NOVOGODISNJIPAKETIC_HPP_INCLUDED
#define NOVOGODISNJIPAKETIC_HPP_INCLUDED

#include "Paketic.hpp"

using namespace std;

class NovogodisnjiPaketic : public Paketic {
    private:
        int minimalanUzrast;
        static int napravljeniNovogodisnjiPaketici;

    public:
        NovogodisnjiPaketic() : Paketic(), minimalanUzrast(2) { ++napravljeniNovogodisnjiPaketici; }
        NovogodisnjiPaketic(const DinString& o, const Dete& d, int mu) : Paketic(o, d), minimalanUzrast(mu) { ++napravljeniNovogodisnjiPaketici; }

        ~NovogodisnjiPaketic() {
            if(status == NAPRAVLJEN)
                --napravljeniNovogodisnjiPaketici;
        }

        int getMinimalanUzrast() const { return minimalanUzrast; }
        int getNapravljeniNovogodisnjiPaketici() const { return napravljeniNovogodisnjiPaketici; }

        bool isporuci() {
            if(spakuj() && namenjen.getZasluzenNovogodisnjiPaketic()) {
                status = ISPORUCEN;
                cout << "Novogodisnji paketic ce uskoro biti isporucen. Primalac je " << namenjen.getNadimak() << "." << endl;
                return true;
            }

            cout << "Novogodisnji paketic ne moze biti isporucen!" << endl;
            return false;
        }

        void ispisi() const {
            cout << "\n-------------------------------------------" << endl;
            cout << "opis: " << opis << endl;
            cout << "namenjen:\n" << namenjen;

            switch(status) {
                case NAPRAVLJEN:
                    cout << "status: napravljen" << endl;
                    break;
                case SPAKOVAN:
                    cout << "status: spakovan" << endl;
                    break;
                case ISPORUCEN:
                    cout << "status: isporucen" << endl;
                    break;
                default:
                    cout << "status: nepoznat" << endl;
            }

            cout << "minimalan uzrast: " << minimalanUzrast << endl;
            cout << "-------------------------------------------" << endl;
        }
};

#endif // NOVOGODISNJIPAKETIC_HPP_INCLUDED
