#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

template<class SADRZAJ, int KAPACITET>
class Trezor {
private:
    SADRZAJ niz[KAPACITET];
    bool popunjenost[KAPACITET];
    int brojPopunjenih;
public:
    Trezor () {
        brojPopunjenih = 0;
        for (int i = 0; i < KAPACITET; i++)
            popunjenost[i] = false;
    }

    int getBrojPopunjenihSefova() {
        return brojPopunjenih;
    }

    int ubaciSadrzaj(const SADRZAJ& predmet) {
        for (int i = 0; i < KAPACITET; i++){
            if (!popunjenost[i]) {
                popunjenost[i] = true;
                index = i;
                niz[i] = predmet;
                brojPopunjenih++;
                return i;
            }
        }
        return -1;
    }

    bool izbaciSadrzaj(int sef) {
        if (popunjenost[sef] && sef < KAPACITET) {
            popunjenost[sef] = false;
            brojPopunjenih--;
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, const Trezor<SADRZAJ, KAPACITET>& t) {
        out << "Sadrzaj trezora: " << endl;
        for (int i = 0; i < KAPACITET; i++){
            if (t.popunjenost[i])
                out << t.niz[i] << endl;
            else
                out << "X" << endl;
        }
        return out;
    }
};

#endif // TREZOR_HPP_INCLUDED
