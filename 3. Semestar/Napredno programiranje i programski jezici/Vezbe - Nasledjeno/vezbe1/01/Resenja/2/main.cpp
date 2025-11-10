#include <iostream>
#include <cmath>

using namespace std;

double f(int n) {
    double rezultat = 0;

    for(int i = 1; i <= n; i++) {
        rezultat += sqrt(i);
    }


    // zaokruzivanje na 2 decimale
    rezultat = round(rezultat * 100);
    rezultat = rezultat / 100;

    return rezultat;
}

int main()
{
    int n;
    double rezultat;

    cout << "Unesite ceo pozitivan broj: ";
    cin >> n;

    if (n < 0) {
        cout << "Greska: Ocekuje se pozitivan broj";
        return 0;
    }

    rezultat = f(n);

    cout << "Vrednost izraza je: " << rezultat << endl;
    return 0;
}

