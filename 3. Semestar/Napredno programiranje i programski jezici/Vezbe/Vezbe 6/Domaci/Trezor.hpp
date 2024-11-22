#ifndef TREZOR_HPP_INCLUDED
#define TREZOR_HPP_INCLUDED

template <class SADRZAJ,int KAPACITET>
class Trezor {
private:
    SADRZAJ* sefovi[KAPACITET];
public:
    Trezor() {
        for(int i = 0; i < KAPACITET; i++) {
            sefovi[i] = nullptr;
        }
    }

    int getBrojPopunjenihSefova() {
        int brojPopunjenihSefova = 0;
        for(int i = 0; i < KAPACITET; i++)
            if(sefovi[i] != nullptr)
                brojPopunjenihSefova++;
        
        return brojPopunjenihSefova;
    }

    int ubaciSadrzaj(const SADRZAJ& sadrzaj) {
        for(int i = 0; i < KAPACITET; i++) {
            if(sefovi[i] == nullptr) {
                sefovi[i] = new SADRZAJ(sadrzaj);
                return i;
            }
        }
        return -1;
    }

    bool izbaciSadrzaj(int sef) {
        if(sef < 0 || sef >= KAPACITET || sefovi[sef] == nullptr)
            return false;
        
        sefovi[sef] = nullptr;
        return true;
    }

};

#endif // TREZOR_HPP_INCLUDED