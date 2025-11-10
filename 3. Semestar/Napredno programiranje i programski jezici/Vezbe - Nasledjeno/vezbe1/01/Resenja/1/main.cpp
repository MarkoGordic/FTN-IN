#include <iostream>
using namespace std;

int main()
{
    int n, pom, suma = 0;

    cout << "Koliko brojeva biste da saberete? ";
    cin >> n;

    if (n <= 0) {
        cout << "Greska: Morate uneti pozitivan broj" << endl;
    }
    else {
        for(int i = 0; i < n; i++){
            cout << "Unesite broj: ";
            cin >> pom;
            suma += pom;
            cout << "Trenutna suma je: " << suma << endl;
        }
        cout << "Konacna suma je: " << suma;
    }

    return 0;
}
