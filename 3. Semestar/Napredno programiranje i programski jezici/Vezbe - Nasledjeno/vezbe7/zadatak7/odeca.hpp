#ifndef ODECA_HPP_INCLUDED
#define ODECA_HPP_INCLUDED

enum Velicina {XS, S, M, L, XL};
enum Tip {MAJICA, PANTALONE};

class Odeca : public Proizvod {
private:
    Velicina velicina;
    Tip tipOdece;
    static int brojVelikeOdece;
public:
    Odeca (const char* ime, int c, Velicina v, Tip t) : Proizvod(c, ime), velicina(v), tipOdece(t) {
        if (v == XL || v == L)
            brojVelikeOdece++;
    }

    Odeca (const DinString& ime, int c, Velicina v, Tip t) : Proizvod(c, ime), velicina(v), tipOdece(t) {
        if (v == XL || v == L)
            brojVelikeOdece++;
    }

    ~Odeca () {
        if (velicina == XL || velicina == L)
            brojVelikeOdece--;
    }

    void izracunajPopust() {
        if (tipOdece == MAJICA && velicina == XS)
            cena = cena - cena * 0.6;
        else if (tipOdece == MAJICA)
            cena = cena - cena * 0.5;
        else
            cena = cena - cena * 0.33;
    }

    void ispisi() {
        Proizvod::ispisi();
        cout << "Tip odece: " << (tipOdece == MAJICA ? "MAJICA" : "PANTALONE") << endl << "Velicina: ";
        switch(velicina){
            case XS: cout << "XS" << endl; break;
            case S: cout << "S" << endl; break;
            case M: cout << "M" << endl; break;
            case L: cout << "L" << endl; break;
            case XL: cout << "XL" << endl; break;
        }
        cout << endl;
    }

    int getBrojVelikeOdece () const {
        return brojVelikeOdece;
    }
};

int Odeca::brojVelikeOdece = 0;

#endif // ODECA_HPP_INCLUDED
