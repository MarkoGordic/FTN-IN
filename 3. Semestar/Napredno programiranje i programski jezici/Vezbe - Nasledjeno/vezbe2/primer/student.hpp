#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

// u hpp je deklaracija dok je implementacija biti u cpp fajlu
// uvek ide class ... {private: ... public: ...};

class Student{
private:
    double prosek;
    int zbirOcena, brojOcena, brojIndeksa;
public:
    Student();                              // konstruktor bez parametara
    Student(double, int, int, int);         // konstruktor sa parametrima
    Student(const Student& student);        // konstruktor kopije

    double getProsek() const;               // geteri imaju tip kao i polje
    void setProsek(double p);               // setri imaju tip void po konvenciji

    void upisiOcenu(int ocena);
};

#endif // STUDENT_HPP_INCLUDED
