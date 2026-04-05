#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> min_n(const vector<int>& v, int n){
    vector<int> kopija(v);

    sort(kopija.begin(),kopija.end());
    vector<int> izlaz;
    vector<int>::const_iterator it;

    for(it = kopija.begin(); it != kopija.begin() + n; it++){
        izlaz.push_back(*it);
    }

    return izlaz;
}

int main() {
    vector<int> brojevi = {2, 4, 1, 6, 0, 9, 11, 23, 3, 15};
    vector<int> obradjen = min_n(brojevi, 4);

    for(int broj : obradjen)
        cout << broj << " ";

    return 0;
}