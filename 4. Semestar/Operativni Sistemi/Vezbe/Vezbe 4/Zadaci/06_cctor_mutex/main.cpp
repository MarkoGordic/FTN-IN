/*
Data je klasa Brojac.
U main funkciji napraviti objekat klase Brojac. Ispis vrednosti Brojaca radi posebna nit.
Napraviti nit koja vrši ispis i proslediti joj Brojac.
*/

class Brojac {
   mutex m; //propusnica pripada klasi i obezbedjuje sprecavanje stetnog preplitanja pri vrsenju operacija nad objektima klase
   int broj; //vrednost Brojaca
 public:
   Brojac() : broj(0) {} //inicijalno je Brojac nula
   void inc();//operacija povecava Brojac, ali pre toga zakljucava propusnicu i na taj nacin sprecava stetno preplitanja pri izmeni Brojaca
   void dec();//operacija smanjuje Brojac, ali pre toga zakljucava propusnicu i na taj nacin sprecava stetno preplitanja pri izmeni Brojaca
   friend ostream& operator<<(ostream& os, Brojac& b);
};
