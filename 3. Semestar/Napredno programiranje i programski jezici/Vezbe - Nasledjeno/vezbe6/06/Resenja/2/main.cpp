#include "androidApp.hpp"
#include "desktopApp.hpp"

int main()
{
    cout << "*** Testiranje klase Computer ***" << endl;
    Computer c, c1(2, 4, "1GB any", "WinXP"), c2(c1);

    cout << c << endl;
    cout << c1 << endl;
    cout << c2 << endl;


    cout << endl << endl;
    cout << "*** Testiranje klase Application ***" << endl;
    Application a, a1("Java", 30), a2(a1);

    cout << a << endl;
    cout << a1 << endl;
    cout << a2 << endl;
    cout << "Broj aplikacija: " << a.getCount() << endl;

    { // uloga destruktora
        Application a4(a);
        cout << a4 << endl;
        cout << "Broj aplikacija: " << a.getCount() << endl;
    }

    cout << "Broj aplikacija (nakon unistavanja jednog): " << a.getCount() << endl;
    // moze i a1.getCount(), a2.getCount()...



    cout << endl << endl;
    cout << "*** Testiranje klase AndroidApp ***" << endl;
    AndroidApp an, an1(8, 15, 23), an2(an1);

    cout << an << endl;
    cout << an1 << endl;
    cout << an2 << endl;
    cout << "Broj aplikacija: " << a.getCount() << endl;
    cout << "Broj android aplikacija: " << an.getCount() << endl;
    cout << endl;

    {
        AndroidApp an4(an);

        cout << an4 << endl;
        cout << "Broj aplikacija: " << a.getCount() << endl;
        cout << "Broj android aplikacija: " << an.getCount() << endl;
        cout << endl;
    }

    cout << "Broj aplikacija (nakon unistavanja jedne android): " << a.getCount() << endl;
    cout << "Broj android aplikacija (nakon unistavanja jedne android): " << an.getCount() << endl;
    cout << endl;



    cout << endl << endl;
    cout << "*** Testiranje klase DesktopApp ***" << endl;
    DesktopApp d, d1(c1, c, "Ruby", 36), d2(d1);

    cout << d << endl;
    cout << d1 << endl;
    cout << d2 << endl;
    cout << "Broj aplikacija: " << a.getCount() << endl;
    cout << "Broj desktop aplikacija: " << d.getCount() << endl;
    cout << endl;


    {
        DesktopApp d4(d);

        cout << d4 << endl;
        cout << "Broj aplikacija: " << a.getCount() << endl;
        cout << "Broj desktop aplikacija: " << d.getCount() << endl;
    }

    cout << "Broj aplikacija (nakon unistavanja jedne desktop): " << a.getCount() << endl;
    cout << "Broj desktop aplikacija  (nakon unistavanja jedne desktop): " << d.getCount() << endl;

    return 0;
}
