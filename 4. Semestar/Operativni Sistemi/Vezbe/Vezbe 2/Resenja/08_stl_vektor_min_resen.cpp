/* Napraviti funkciju:
				vector<int> min(const vector<int>& a, const vector<int>& b);
				Ova funkcija vraca vektor koji sadrzi minimume korespodentnih elemenata vetora a i b.
				Npr: r[0]=min(a[0],b[0]), r[1]=...
				Podrazumeva se: a.size()==b.size()
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//parametri su vektori a i b (po referenci) a rezultat je novi vektor ciji elementi predstavljaju manji od korespodentnih elemenata a i b vektora
vector<int> min(const vector<int>& a, const vector<int>& b) {
    vector<int> ret_val; //povratna vrednost funkcije. Inicijalno je prazan ovaj vektor

    vector<int>::const_iterator ita;
    vector<int>::const_iterator itb;
    //prolazimo redom kroz sve elemente vektora a i b
    //(u svakoj iteraciji "ita" pokazuje na trenutni element u vektoru "a", a "itb" na njegov korespodentni element u vektoru "b")
    for (ita = a.begin(), itb = b.begin(); ita != a.end(); ita++, itb++) {
        ret_val.push_back(min(*ita,*itb)); //u rezultat se ubacuje manji od dva korespodentna elementa (funkcija min iz zaglavlja algorithm vraca manji od 2 prosledjena elementa)
    }
	return ret_val;
}

int main() {
	vector<int> a = {5, 9, 12, 7, 3, 1, 28, 16}; //konstruisanje vektora i istovremeno ubacivanje elemenata
	vector<int> b = {7, 3, 6, 12, 9, 5, 42, 8};
	vector<int> c = min(a, b); //vector c je rezultat funkcije min, kojoj se prosledjuju vektori a i b
	vector<int>::iterator it;
	for (it = c.begin(); it != c.end(); it++) //iteriranje kroz ceo vektor c
		cout << *it << " "; //ispis elementa na kojeg iterator pokazuje u ovoj iteraciji
}
