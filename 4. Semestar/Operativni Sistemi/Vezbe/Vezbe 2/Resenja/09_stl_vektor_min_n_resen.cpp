/*Napraviti funkciju:
		vector<int> min_n(const vector<int>& v,	int n);
		Ova funkcija vraca vektor koji sadrzi n najmanjih
		elemenata iz vektora v.
		Podrazumeva se: v.size()>=n
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//prvi parametar je vektor u kojem trazimo najmanje elemente. Drugi parametar je koliko najmanjih elemenata preuzimamo
vector<int> min_n(const vector<int>& v, int n) {
    //n najmanjih brojeva cemo naci tako sto cemo najpre sortirati vektor u rastucem redosledu, pa vratiti prvih n elemenata
    vector<int> v_copy = v; //v je const, pa pravimo kopiju
	sort(v_copy.begin(), v_copy.end()); //sortiramo kopiju ulaznog vektora
	//vratimo prvih n elemenata iz sortiranog vektora
	vector<int> ret_val; //vektor koji je rezultat funkcije
    ret_val.resize(n); //alociramo n mesta
    //funkcija iz zaglavlja algorithm koja kopira elemenate vektora v_copy u vektor ret_val, pocevsi od prvog do n-tog elementa vektora v_copy
    copy(v_copy.begin(),v_copy.begin() + n, ret_val.begin());
	return ret_val;
}

int main() {
	vector<int> brojevi = {5, 9, 12, 7, 3, 1, 28, 16}; //konstruisanje vektora i istovremeno ubacivanje elemenata
	vector<int> najmanji_brojevi = min_n(brojevi, 5); //pronalazenje 5 najmanjih brojeva
	vector<int>::iterator it;
	for (it = najmanji_brojevi.begin(); it != najmanji_brojevi.end(); it++) //iteriranje kroz ceo vektor c
		cout << *it << " "; //ispis elementa na kojeg iterator pokazuje u ovoj iteraciji
}
	
