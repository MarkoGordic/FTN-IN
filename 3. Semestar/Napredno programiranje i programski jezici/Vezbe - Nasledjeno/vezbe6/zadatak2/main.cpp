#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "computer.hpp"
#include "application.hpp"
#include "androidapp.hpp"
#include "desktopapp.hpp"

int main()
{
    cout << "Computers" << endl << endl;
    Computer c1, c2(256, 16, "nvidia", "linuks"), c3(c1);
    cout << "C1: " << c1 << endl;
    cout << "C2: " << c2 << endl;
    cout << "C3: " << c3 << endl;



    cout << "Applications" << endl << endl;
    Application a1, a2("mjau mjau hrcak", 5624), a3(a1);
    cout << "A1: " << a1 << endl;
    cout << "Broj instanci: " << a1.getCount() << endl;
    // pokazivanje rada destruktora
    {
        Application a4;
        cout << "Broj instanci u bloku: " << a1.getCount() << endl;
    }
    cout << "Broj instanci nakon bloka: " << a1.getCount() << endl << endl;

    cout << "A2: " << a2 << endl;
    cout << "A3: " << a3 << endl;


    // broj instanci klase app se povecava sa svakom novom androidapp jer
    // androidapp opet poziva konstruktor od app i time povecava broj
    // instanci app klase
    cout << "Android Applications" << endl << endl;
    AndroidApp aa1, aa2(1.1, 1.6, 3476), aa3(aa1);

    cout << "AA1: " << aa1 << endl;
    cout << "Broj app instanci: " << a1.getCount() << endl;
    cout << "Broj android app instanci: " << aa1.getCount() << endl;
    // pokazivanje rada destruktora
    {
        AndroidApp a4;
        cout << "Broj app instanci u bloku: " << a1.getCount() << endl;
        cout << "Broj android app instanci u bloku: " << aa1.getCount() << endl;
    }
    cout << "Broj app instanci nakon bloka: " << a1.getCount() << endl;
    cout << "Broj android app instanci nakon bloka: " << a1.getCount() << endl << endl;

    cout << "AA2: " << aa2 << endl;
    cout << "AA3: " << aa3 << endl;



    cout << "Desktop Applications" << endl << endl;
    DesktopApp d1, d2(c1, c2, "python", 347), d3(d1);

    cout << "D1: " << d1 << endl;
    cout << "Broj app instanci: " << a1.getCount() << endl;
    cout << "Broj desktop app instanci: " << d1.getCount() << endl;
    // pokazivanje rada destruktora
    {
        DesktopApp d4;
        cout << "Broj app instanci u bloku: " << a1.getCount() << endl;
        cout << "Broj desktop app instanci: " << d1.getCount() << endl;
    }
    cout << "Broj app instanci nakon bloka: " << a1.getCount() << endl;
    cout << "Broj desktop app instanci nakon bloka: " << d1.getCount() << endl << endl;

    cout << "D2: " << d2 << endl;
    cout << "D3: " << d3 << endl;

    return 0;
}
