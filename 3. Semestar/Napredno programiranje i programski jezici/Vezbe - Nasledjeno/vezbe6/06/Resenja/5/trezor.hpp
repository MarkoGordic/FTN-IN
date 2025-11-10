#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

template <class SADRZAJ, int KAPACITET>
class Trezor {
    private:
        SADRZAJ sefovi[KAPACITET]; // ubacuju se predmeti
        bool popunjenost[KAPACITET]; // pomocni niz za praæenje popunjenosti sefa

    public:
        Trezor() {
            for(int i = 0; i < KAPACITET; i++) {
                popunjenost[i] = false;
            }
        }

        int getBrojPopunjenihSefova() {
            int n = 0;

            for(int i = 0; i < KAPACITET; i++) {
                if(popunjenost[i]) {
                    n++;
                }
            }

            return n;
        }

        int ubaciSadrzaj(const SADRZAJ& sadrzaj) {
            for(int i = 0; i < KAPACITET; i++) {
                if(!popunjenost[i]) {
                    popunjenost[i] = true;
                    sefovi[i] = sadrzaj;
                    return i;
                }
            }

            return -1;
        }

        bool izbaciSadrzaj(int sef) {
            if(popunjenost[sef]) {
                popunjenost[sef] = false;
                return true;
            }

            return false;
        }
};


#endif // TREZOR_HPP_INCLUDED
