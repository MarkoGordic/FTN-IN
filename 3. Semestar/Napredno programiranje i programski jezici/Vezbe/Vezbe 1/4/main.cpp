#include <iostream>
using namespace std;

int main(){
    int n;
    cout << "Unesite ceo pozitivan broj n: ";
    cin >> n;

    if(n <= 0){
        cout << "Uneti broj nije pozitivan." << endl;
        return 1;
    }

    int a = 0, b = 1, c;
    for(int i = 0; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }

    cout << "Fibonacijev broj na poziciji " << n << " je: " << a << endl;

    return 0;
}