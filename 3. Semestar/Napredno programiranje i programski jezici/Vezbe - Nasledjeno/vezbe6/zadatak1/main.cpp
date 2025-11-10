#include <iostream>

using namespace std;

// add files recursively dodaje sve fajlove koje moze iz tog foldera gde je projekat

#include "dinstring.hpp"
#include "artikal.hpp"

int main()
{
    Artikal a1("Pivo", 100);
    cout << a1.get(); // ovde vrati 1 kao static hmmm
    cout << a1 << endl; // cudno ponasanje ovde jer static bude 2

    /*Artikal a2("Mleko", 90), a3(a1);
    cout << a2 << endl;
    cout << a3 << endl;

    // blok koji nam demonstrira rad destruktora
    {
        Artikal a4("Jaja", 20);
        cout << "Blok koda: " << a4 << endl;
    }

    Artikal a5("Hleb", 50);
    cout << "Nakon bloka koda: " << a5 << endl;*/

    return 0;
}

// destruktor se automatski poziva i on postoji cak po defaultu i
// sluzi za oslobadjanje memorije, dok konstruktor za zauzimanje memorije
