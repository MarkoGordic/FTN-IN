#ifndef RERNA_HPP_INCLUDED
#define RERNA_HPP_INCLUDED

#define MIN_TEMPERATURA 0
#define MAX_TEMPERATURA 220
#define KORAK 20

enum StanjeRerne {ISKLJUCENA, UKLJUCENA, POKVARENA};

class Rerna {
private:
    StanjeRerne trenutnoStanje;
    int temperatura;

public:
    Rerna();

    bool ukljuci();
    bool iskljuci();
    bool pokvari();
    bool popravi();

    bool pojacajTemperaturu();
    bool smanjiTemperaturu();
    StanjeRerne getTrenutnoStanje() const;

    int getTemperatura() const;
};

#endif // RERNA_HPP_INCLUDED
