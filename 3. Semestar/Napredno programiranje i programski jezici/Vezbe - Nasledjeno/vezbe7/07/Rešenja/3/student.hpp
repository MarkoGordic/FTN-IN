#ifndef STUDENT_DEF
#define STUDENT_DEF

#include "osoba.hpp"

class Student : public Osoba {
	protected:
		int brojIndeksa;

	public:
		Student() : Osoba(), brojIndeksa(0) {}
		Student(const DinString &i, const DinString &p, int bri) : Osoba(i, p), brojIndeksa(bri) {}
		Student(const Student& s) : Osoba((Osoba)s), brojIndeksa(s.brojIndeksa) {}

		void predstaviSe() const {
		    cout << "Student: ";
		    if (ime == "" && prezime == "")
               	 cout << "x" << endl;
           	    else
               	 cout << "Zovem se " << ime << " " << prezime << ", a broj mog indeksa je " << brojIndeksa << "." << endl;
		}
};

#endif
