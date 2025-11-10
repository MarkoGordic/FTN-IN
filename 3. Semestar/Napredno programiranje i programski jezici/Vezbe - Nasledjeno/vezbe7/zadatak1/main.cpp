#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"

int main()
{
    cout << "List <int>" << endl;
    List <int> l1;
    l1.add(1, 10);
    l1.add(2, 20);
    l1.add(3, 30);
    cout << "After adding: " << l1 << endl;

    l1.remove(2);
    cout << "After deleting: " << l1 << endl;

    int pom;
    l1.read(1, pom); // moramo pom slati (po referenci) kako bismo procitali jer .read() vraca bool

    cout << "Reading 1. element: " << pom << endl;
    cout << "Empty before clear: " << l1.empty() << endl;

    l1.clear();
    cout << "Empty after clear: " << l1.empty() << endl;


    cout << endl << "List <DinString>" << endl;
    List <DinString> l2;
    cout << "Before adding: " << l2 << endl;
    l2.add(1, "Jedan");
    l2.add(1, "Dva");
    l2.add(1, "Tri");
    cout << "After adding: " << l2 << endl; // bice ispisano u obrnutom redosledu

    l2.remove(2);
    cout << "After deleting: " << l2 << endl;

    DinString pom2;
    l2.read(1, pom2);  // cout << niz[0]

    cout << "Reading 1. element: " << pom2 << endl;
    cout << "Empty before clear: " << l2.empty() << endl;

    l2.clear();
    cout << "Empty after clear: " << l2.empty() << endl;

    return 0;
}
