#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED

class Putnik
{
private:
    char inicijalIme;
    int godina;
    int trenutnaGodina;
    int tezinaPutnika;
    int tezinaPrtljaga;

public:
    Putnik()
    {
        inicijalIme = 'S';
        godina = 2024;
        trenutnaGodina = 2024;
        tezinaPutnika = 80;
        tezinaPrtljaga = 10;
    }
    
    Putnik(char inicijalIme, int godina, int trenutnaGodina, int tezinaPutnika, int tezinaPrtljaga)
    {

        this->inicijalIme = inicijalIme;
        this->godina = godina;
        this->trenutnaGodina = trenutnaGodina;
        this->tezinaPutnika = tezinaPutnika;
        this->tezinaPrtljaga = tezinaPrtljaga;
    }
    
    bool dodajTezinuPrtljaga(int tezina)
    {
        if (tezinaPrtljaga + tezina < 200)
        {
            tezinaPrtljaga += tezina;
            return true;
        }
        return false;
    }
    
    bool smanjiTezinuPrtljaga(int tezina)
    {
        if (tezinaPrtljaga - tezina >= 0)
        {
            tezinaPrtljaga = -tezina;
            return true;
        }
        return false;
    }
    
    void resetujPutnika()
    {
        inicijalIme = 'S';
        tezinaPutnika = 80;
        tezinaPrtljaga = 10;
    }
    
    char getInicijal() const
    {
        return inicijalIme;
    }

    int getGodina() const
    {
        return godina;
    }
    
    int gettrenutnaGodina() const
    {
        return trenutnaGodina;
    }
    
    int gettezinaPutnika() const
    {
        return tezinaPutnika;
    }
    
    int gettezinaPrtljaga() const
    {
        return tezinaPrtljaga;
    }
    
    void setInicijal(char s)
    {
        inicijalIme = s;
    }
    
    void setGodina(int g)
    {
        godina = g;
    }
    
    void settrenutnaGodina(int tr)
    {
        trenutnaGodina = tr;
    }
    
    void settezinaPutnika(int tp)
    {
        tezinaPutnika = tp;
    }
    
    void settezinaPrtljaga(int p)
    {
        tezinaPrtljaga = p;
    }
    
    void ispisi() const
    {
        std::cout << "====PODACI O PUTNIKU====" << std::endl;
        std::cout << "Inicijal imena putnika:" << inicijalIme << std::endl;
        std::cout << "Godina iz koje putnik dolazi:" << godina << std::endl;
        std::cout << "Trenutna godina u kojoj se putnik nalazi:" << trenutnaGodina << std::endl;
        std::cout << "Tezina putnika:" << tezinaPutnika << std::endl;
        std::cout << "Tezina prtljaga:" << tezinaPrtljaga << std::endl;
    }
};

#endif // PUTNIK_HPP_INCLUDED
