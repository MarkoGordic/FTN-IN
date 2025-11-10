#ifndef PROFESOR_DEF
#define PROFESOR_DEF

#include "osoba.hpp"

class Profesor : public Osoba {
	protected:
		DinString predmet;

	public:
		Profesor() : Osoba(), predmet() {}
		Profesor(const DinString &i, const DinString &p, const DinString &pr) : Osoba(i, p), predmet(pr) {}
		Profesor(const Profesor& p) : Osoba((Osoba)p), predmet(p.predmet) {}

		void predstaviSe() const {
		    cout << "Profesor: ";
		    if (ime == "" && prezime == "")
                	cout << "x" << endl;
           	    else
                	cout << "Zovem se " << ime << " " << prezime << ", i predajem na predmetu " << predmet << "." << endl;
		}
};

#endif
