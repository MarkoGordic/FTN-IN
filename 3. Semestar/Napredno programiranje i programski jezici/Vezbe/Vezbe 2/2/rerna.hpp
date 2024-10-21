#ifndef RERNA_HPP_INCLUDED
#define RERNA_HPP_INCLUDED

enum StanjeRerne {
    UKLJUCENA,
    ISKLJUCENA,
    POKVARENA
};

class Rerna{

private:
    int temperatura;
    StanjeRerne trenutnoStanje;

public:
    Rerna();
    bool ukljuci();
    bool iskljuci();
    bool pokvari();
    bool popravi();

    bool pojacajTemperaturu();
    bool smanjiTemperaturu();

    int getTemperatura() const;
    StanjeRerne getTrenutnoStanje() const;
};

#endif // RERNA_HPP_INCLUDED