#ifndef ZAGLAVLJE_H_INCLUDED
#define ZAGLAVLJE_H_INCLUDED

#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;

class Kocka{
    private:
        int vrednost;
    public:
        // konstruktor bez parametara
        Kocka();

        // konstruktor sa parametrima
        Kocka(int);

        // konstruktor sa parametrima sa podrazumevanim vrednostima
        // Kocka(int i=1);
        // ako koristimo njega ne pise se prazan konstruktor

        // konstruktor kopije
        // const oznacava da je parametar READ-ONLY - moze samo da se procita, ali ne moze da se menja
        // zato sto se preuzima po referenci, dobijamo bas taj objekat, a ne kopiju, potrebno je da ga oznacimo
        // kao READ-ONLY zato sto bi sve promene bile vidljive spolja
        Kocka(const Kocka &);

        void baci();
        // kada se const nadje posle zaglavlja metode ta metoda je oznacena da je READ-ONLY,
        // to znaci da ona moze samo da procita promenljive klase, ne moze da ih menja
        int getVrednost() const;
};

#endif // ZAGLAVLJE_H_INCLUDED
