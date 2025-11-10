#include <iostream>
#include "DedaMraz.hpp"
using namespace std;

int NovogodisnjiPaketic::napravljeniNovogodisnjiPaketici = 0;

int main()
{
    Dete d1("Misa", DECAK, 6, true), d2("Jeca", DEVOJCICA, 7, true), d3("Laza", DECAK, 10, true), d4("Mica", DEVOJCICA, 2, true), d5(d4);
    d1.getNadimak();
    d1.getPol();
    d1.getUzrast();
    d1.getZasluzenNovogodisnjiPaketic();
    cout<<d1<<endl;

    NovogodisnjiPaketic np("autic na daljinsko upravljanje", d1, 5);
    cout << "napravljeni novogodisnji paketici: " << np.getNapravljeniNovogodisnjiPaketici() << endl;

    {
        NovogodisnjiPaketic np1("plisani meda", d4, 4);
        cout << "napravljeni novogodisnji paketici: " << np.getNapravljeniNovogodisnjiPaketici() << endl;
    }

    cout << "napravljeni novogodisnji paketici: " << np.getNapravljeniNovogodisnjiPaketici() << endl;

    DedaMraz dm;
    dm.dodaj("vozic", d1, 5, DECAK);
    dm.dodaj("barbika", d2, 4, DEVOJCICA);
    dm.dodaj("lego kockice", d3, 9, DECAK);
    dm.dodaj("bratz lutka", d4, 7, DEVOJCICA);
    dm.dodaj("dinosaurus", d1, 3, DECAK);
    dm.dodaj("plisani meda", d2, 6, DEVOJCICA);
    dm.dodaj("avioncic", d3, 8, DECAK);
    dm.dodaj("emotivna sovica", d4, 6, DEVOJCICA);
    dm.dodaj("autic", d1, 4, DECAK);
    dm.dodaj("kofercic sa sminkom", d2, 5, DEVOJCICA);
    dm.dodaj("motoric", d3, 7, DECAK);
    dm.ispisi();
    cout << "uspesno izbacivanje novogodisnjeg paketica: " << dm.izbaci(5) << endl;
    cout << "prosecan minimalan uzrast: " << dm.prosecanMinimalanUzrast() << endl;

    return 0;
}
