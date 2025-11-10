#ifndef KOCKA_HPP_INCLUDED
#define KOCKA_HPP_INCLUDED

class Kocka{
private:
    int vrednost;
public:
    Kocka();
    Kocka(int broj);
    Kocka(const Kocka &kocka);

    void baci();
    int getVrednost() const;
};

#endif // KOCKA_HPP_INCLUDED
