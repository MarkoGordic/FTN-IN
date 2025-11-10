#ifndef KVADRAT_HPP_INCLUDED
#define KVADRAT_HPP_INCLUDED

class Kvadrat : public Pravougaonik {
public:
    Kvadrat () : Pravougaonik(2, 2) {}
    Kvadrat (double xx) : Pravougaonik(xx, xx) {}
    Kvadrat (const Kvadrat& k) : Pravougaonik((Pravougaonik)k) {}
};

#endif // KVADRAT_HPP_INCLUDED
