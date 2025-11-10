#include <iostream>

using namespace std;

int main()
{
    int velicina_unosa = 0, suma = 0;
    cout << "Unesite velicinu unosa: ";
    cin >> velicina_unosa;
    if (velicina_unosa <= 0)
    {
        cout << "Greska prilikom unosa!" << endl;
        return 1;
    }
    else
    {
        int broj = 0;
        for (int i = 0; i < velicina_unosa; i++)
        {
            cout << "Unesite " << i + 1 << ". broj: ";
            cin >> broj;
            suma += broj;
        }
        cout << "Ukupna suma je: " << suma << endl;
        return 0;
    }
}
