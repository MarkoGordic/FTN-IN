#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

class Student {
private:
    Predmet predmet1;
    Predmet predmet2;
public:
    Student (const Predmet& p1, const Predmet& p2) : predmet1(p1), predmet2(p2) {}

    void ispis () const {
        predmet1.ispis();
        predmet2.ispis();
        cout << "Vise poena je osvojio iz predmeta: " << (predmet1.getUkupniPoeni() > predmet2.getUkupniPoeni() ? predmet1.getNaziv() : predmet2.getNaziv()) << endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
