#ifndef TELEFON_HPP_INCLUDED
#define TELEFON_HPP_INCLUDED

class Telefon {
protected:
    DinString broj;
public:
    Telefon () : broj ("000000") {}

    Telefon (const DinString& br) : broj (br) {}

    bool pozovi (const DinString& br) {
        if (broj == br) {
            return false;
        }
        return true;
    }
};

#endif // TELEFON_HPP_INCLUDED
