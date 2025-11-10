#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca { AUTOMATIK, MANUELNI };

class Menjac
{
private:
    TipMenjaca tip;
    int brojBrzina;

public:
    Menjac()
    {
        tip = AUTOMATIK;
        brojBrzina = 5;
    }
    Menjac(TipMenjaca t, int b)
    {
        tip = t;
        if (!setBrojBrzina(b))
        {
            brojBrzina = 5;
        }
    }
    Menjac(const Menjac& m)
    {
        tip = m.tip;
        brojBrzina = m.brojBrzina;
    }

    bool setBrojBrzina(int b)
    {
        if (b == 5 || b == 6)
        {
            brojBrzina = b;
            return true;
        }
        return false;
    }

    void setTip(TipMenjaca t)
    {
        tip = t;
    }
    int getBrojBrzina() const
    {
        return brojBrzina;
    }
    TipMenjaca getTip() const
    {
        return tip;
    }

    friend void ispisiMenjac(const Menjac&); // prijateljska funkcija

};


#endif // MENJAC_HPP_INCLUDED
