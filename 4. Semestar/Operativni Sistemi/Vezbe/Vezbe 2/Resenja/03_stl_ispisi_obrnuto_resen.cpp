/*
Napraviti program koji prihvata proizvoljan broj linija
sa standardnog ulaza i zatim ih ispisuje u obrnutom
redosledu (poslednja prihvacena linija se ispisuje
prva).
	*/
#include<iostream>
#include<vector>
using namespace std;

typedef vector<string> V; //krace ime za vector<string>, u kodu koristimo alias V

//iterator koji pokazuje na element kontejnera
//const_iterator ne moze da vrsi izmenu elementa na koji pokazuje
//koristimo const_iterator jer je potrebno elemente samo ispisivati, a ne i menjati ih
//pravimo const_reverse_iterator koji se pomera unazad (inkrementiranjem iteratora prelazi se na prethodni, a ne sledeci element)
typedef vector<string>::const_reverse_iterator Vcri;  //krace ime za vector<string>::const_reverse_iterator, u kodu koristimo alias Vcri

int main() {
   V v; //STL vektor koja sadrzi linije unesene sa tastature
   string s; //privremena promenljiva za prihvat vrednosti unosene sa tastature
   cout << "Unesite stringove (ctrl-d za kraj)" << endl;
   //korisnik unosi red sa konzole. unos se vrsi dok se ne pritisne ENTER. Tada se unesena slova ubacuju u promenljivu s
   while(getline(cin,s)) { //petlja ce se izvrsavati dok se ne pritisne Ctrl+d (Tada funkcija getline vraca false)
	v.push_back(s); //vrednost unesena sa tastature se ubacuje na kraj STL kontejnera 
   }   
    
   cout << "Uneti stringovi u obrnutom redosledu:" << endl;
   //iterator inicijalno pokazuje na poslednji element u kontejneru (metoda rbegin() vraca iterator na poslednji element)
   //u svakoj iteraciji iterator se pomera da pokazuje na prethodni element. U petlji se ostaje dok se ne prodju svi elementi 
   //tj. dok se ne prodje prvi element (metoda rend() vraca iterator na lokaciju pre prvog elementa)
   for(Vcri i = v.rbegin(); i != v.rend(); ++i) 
     cout << *i << endl; //ispis sadrzaja elementa na koji iterator pokazuje u ovoj iteraciji
}
