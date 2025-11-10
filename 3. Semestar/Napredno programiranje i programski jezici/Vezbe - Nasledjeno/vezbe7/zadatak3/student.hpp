#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

class Student : public Osoba {
private:
    int brojIndeksa;
public:
    Student () {    // mada je moglo i sa Student () : Osoba (), brojIndeksa(1); ali svakako se osoba po defaultu poziva
        brojIndeksa = 1;
    }
    Student (const DinString &i, const DinString &p, int bi) : Osoba(i, p), brojIndeksa(bi) {}
    Student (const Student &s) : Osoba(s), brojIndeksa(s.brojIndeksa) {} // ne mora Osoba((Osoba)s) jer ce se to kastovanje raditi po defaultu

    void predstaviSe () const {
        Osoba::predstaviSe();
        cout << "Moj broj indeksa je " << brojIndeksa << "." << endl;
    }
};


#endif // STUDENT_HPP_INCLUDED
