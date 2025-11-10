#ifndef OSOBA_DEF
#define OSOBA_DEF

#include "dinstring.hpp"

class Osoba {
	protected:
		DinString ime, prezime;

	public:
		Osoba() {}
		Osoba(const DinString &i, const DinString &p) : ime(i), prezime(p) {}
		Osoba(const Osoba &osoba) : ime(osoba.ime), prezime(osoba.prezime) {}

		virtual void predstaviSe() const {
		    cout << "Osoba: ";
		    if (ime == "" && prezime == "")
               	 cout << "x" << endl;
            	    else
               	 cout << "Zovem se " << ime << " " << prezime << "." << endl ;
		}
};

#endif
