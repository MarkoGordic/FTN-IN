/*
Napraviti program koji prihvata proizvoljan broj linija
sa standardnog ulaza i zatim ih ispisuje u redosledu kojim su uneti.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> v; //STL vektor koja sadrzi linije unesene sa tastature
    string s; //privremena promenljiva za prihvat vrednosti unosene sa tastature
    cout<<"Unesite stringove (ctrl-d za kraj):"<<endl;
    //korisnik unosi red sa konzole. unos se vrsi dok se ne pritisne ENTER. Tada se unesena slova ubacuju u promenljivu s
    while(getline(cin,s)) { //petlja ce se izvrsavati dok se ne pritisne Ctrl+d (Tada funkcija getline vraca false)
        v.push_back(s); //vrednost unesena sa tastature se ubacuje na kraj STL kontejnera 
    }
    cout << "Uneti stringovi su: " << endl;
    //deklaracija iteratora koji pokazuje na element kontejnera
    //const_iterator ne moze da vrsi izmenu elementa na koji pokazuje
    //koristimo const_iterator jer je potrebno elemente samo ispisivati, a ne i menjati ih      
    vector<string>::const_iterator it;
    //iterator inicijalno pokazuje na prvi element u kontejneru i dalje u svakoj iteraciji 
    //iterator se pomera da pokazuje na naredni element. U petlji se ostaje dok se ne prodju svi elementi		
    for (it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl; //ispis sadrzaja elementa na koji iterator pokazuje u ovoj iteraciji
    }
}
