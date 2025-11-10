#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

class Pravougaonik {
    private:
        double a;
        double b;
    public:
        Pravougaonik(double aa = 1, double bb = 2){
            a = aa;
            b = bb;
        }

        double getA() const{
            return a;
        }

        double getB() const{
            return b;
        }

        double getO() const{
            return 2 * a + 2 * b;
        }

        double getP() const{
            return a * b;
        }
};

#endif // PRAVOUGAONIK_HPP_INCLUDED
