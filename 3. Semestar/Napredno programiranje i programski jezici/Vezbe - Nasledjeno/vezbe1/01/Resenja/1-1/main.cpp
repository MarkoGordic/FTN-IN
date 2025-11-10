
#include <iostream>
using namespace std;

int main()
{
    int pom, maksimum = 0;

    do {
        cout << "Unesite pozitivan broj ili 0 za kraj unosa: ";
        cin >> pom;

        if (pom == 0) {
            cout << "Kraj";
        }
        else if (pom < 0) {
            cout << "Greska: Uneli ste negativan broj.";
        }
        else {
            if (pom > maksimum)
                maksimum = pom;
        }
    } while(pom > 0); // ili while (pom != 0)

    if (maksimum > 0)
        cout << "Maksimum je: " << maksimum << endl;

    return 0;
}
