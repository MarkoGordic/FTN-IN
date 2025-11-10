#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

template <class SADRZAJ, int KAPACITET>
class Trezor {
private:
    SADRZAJ niz[KAPACITET];
    bool popunjenost[KAPACITET];
public:
    Trezor () {
        for (int i = 0; i < KAPACITET; i++) {
            popunjenost[i] = false;
        }
    }

    int getBrojPopunjenihSefova () const {
        int broj = 0;
        for (int i = 0; i < KAPACITET; i++) {
            if (popunjenost[i])
                broj++;
        }
        return broj;
    }

    int ubaciSadrzaj (const SADRZAJ& predmet) {
        for (int i = 0; i < KAPACITET; i++) {
            if (!popunjenost[i]) {
                niz[i] = predmet;
                popunjenost[i] = true;
                return i;
            }
        }
        return -1;
    }

    bool izbaciSadrzaj (int sef) {
        if (!popunjenost[sef] || sef >= KAPACITET) {
            return false;
        }
        popunjenost[sef] = false;
        return true;
    }
};

#endif // TREZOR_HPP_INCLUDED
