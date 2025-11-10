#ifndef KOLOKVIJUM_HPP_INCLUDED
#define KOLOKVIJUM_HPP_INCLUDED

class Kolokvijum : public Test {
public:
    Kolokvijum () : Test("", 0) {}

    Kolokvijum (const char ime[]) : Test(ime, rand()%25 + 1) {}

    int getPoeni() const {
        return osvojeniPoeni;
    }

    bool polozio () const {
        return (osvojeniPoeni > 12);
    }
};

#endif // KOLOKVIJUM_HPP_INCLUDED
