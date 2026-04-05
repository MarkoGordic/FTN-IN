/*
Napraviti funkciju:
	
vector<int> min_n(const vector<int>& v,	int n);

Ova funkcija vraća vektor koji sadrži n najmanjih elemenata iz vektora v.
Podrazumeva se: v.size()>=n
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Prvi parametar je vektor u kojem tražimo najmanje elemente. Drugi parametar je koliko najmanjih elemenata preuzimamo:
vector<int> min_n(const vector<int>& v, int n) {
    // n najmanjih brojeva ćemo naći tako što ćemo najpre sortirati vektor u rastućem redosledu, pa vratiti prvih 5 elemenata
    vector<int> v_copy = v; // v je const, pa pravimo kopiju jer ne možemo da menjamo const vektor ali možemo kopiju
	sort(v_copy.begin(), v_copy.end()); // Sortiramo kopiju ulaznog vektora
	
	// Vratimo prvih n elemenata iz sortiranog vektora:
	vector<int> ret_val; // Vektor koji je rezultat funkcije
    ret_val.resize(n); // Alociramo n mesta za vektor ret_val (menjamo mu veličinu)
    // Kopiramo prvih n brojeva iz sortiranog u povratni vektor. Ovo je moglo i preko iteratora i preko običnog brojača:
    for (int i = 0; i < n; i++)
    	ret_val[i] = v_copy[i];
    
	return ret_val;
}

int main() {
	vector<int> brojevi = {5, 9, 12, 7, 3, 1, 28, 16}; // Konstruisanje vektora i istovremeno ubacivanje elemenata
	vector<int> najmanji_brojevi = min_n(brojevi, 5); // Pronalazenje 5 najmanjih brojeva
	vector<int>::iterator it;
	for (it = najmanji_brojevi.begin(); it != najmanji_brojevi.end(); it++) // Iteriranje kroz ceo vektor c
		cout << *it << " "; // Ispis elementa na kojeg iterator pokazuje u ovoj iteraciji
}
