#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

class Test {
protected:
    DinString naziv;
    int osvojeniPoeni;
public:
    Test () : naziv(), osvojeniPoeni(0) {}

    Test (const DinString& ime, int poeni) : naziv(ime), osvojeniPoeni(poeni) {}

    Test (const char *ime, int poeni) : naziv(ime), osvojeniPoeni(poeni) {}

    virtual int getPoeni () const = 0;
    virtual bool polozio () const = 0;

    friend ostream& operator<<(ostream& out, const Test& t) {
        out << "Test" << endl;
        out << "Naziv testa: " << t.naziv << endl;
        out << "Broj poena: " << t.osvojeniPoeni << endl;
        return out;
    }
};

#endif // TEST_HPP_INCLUDED
