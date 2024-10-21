#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    float suma = 0;
    int n;

    cout << "n = ";
    cin >> n;

    for(int i = 1; i <= n; i++){
        suma += sqrt(i);
    }

    cout << "suma = " << fixed << setprecision(2) << suma << endl;

    return 0;
}