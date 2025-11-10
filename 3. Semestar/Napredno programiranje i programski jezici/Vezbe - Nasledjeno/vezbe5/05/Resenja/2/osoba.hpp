#ifndef OSOBA_DEF
#define OSOBA_DEF

#include "dinstring.hpp"
#include <iostream>

using namespace std;

class Osoba
{
	private:
		DinString ime, prezime;

	public:
		Osoba(const char* s1 = "", const char* s2 = "") : ime(s1), prezime(s2) { }

		Osoba(const DinString& ds1, const DinString& ds2) :	ime(ds1), prezime(ds2) { }

		Osoba(const Osoba& osoba) : ime(osoba.ime), prezime(osoba.prezime) { }

		void predstaviSe() const
		{
			cout << "Zovem se " << ime << " " << prezime << "." << endl;
		}

};

#endif
