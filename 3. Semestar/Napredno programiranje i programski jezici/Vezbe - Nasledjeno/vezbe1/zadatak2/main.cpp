#include <iostream>
#include <cmath>

using namespace std;

float izraz(int n){
    if (n < 0){
        return -1;
    }
    float broj = 0;
    for (int i = 0; i <= n; i++){
        broj += round(sqrt(i) * 100)/100;
    }
    return broj;
}

int main()
{
    int n = 0;
    cout << "Unesite broj: ";
    cin >> n;
    float resenje = izraz(n);
    if (resenje == -1){
        cout << "Greska!";
        return 1;
    }
    cout << "Vrednost izraza za " << n << " iznosi: " << resenje << endl;
    return 0;
}
