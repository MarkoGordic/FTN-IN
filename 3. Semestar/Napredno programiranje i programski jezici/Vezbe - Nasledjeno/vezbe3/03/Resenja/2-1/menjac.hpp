#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca { AUTOMATIK, MANUELNI };

class Menjac{
    private:
        TipMenjaca tip;
        int brojBrzina;

    public:
        Menjac(){ tip = MANUELNI; brojBrzina = 3;}
        Menjac(TipMenjaca t, int b) { tip = t; brojBrzina = b;}
        Menjac(const Menjac& m) { tip = m.tip; brojBrzina = m.brojBrzina;}

        void setBrojBrzina(int brzina){ brojBrzina = brzina; }
        void setTip(TipMenjaca t) { tip = t; }
        int getBrojBrzina() const { return brojBrzina;}
        TipMenjaca getTip() const { return tip;}

        friend void ispisiMenjac(const Menjac&); // prijateljska funkcija

};


#endif // MENJAC_HPP_INCLUDED
