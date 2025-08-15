/*
Napraviti jednostavan program za prevodenje reci sa engleskog na srpski jezik.
Nakon unosa reci sa standardnog ulaza, ispisuje  se prevod ukoliko
unesena rec postoji u recniku.
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	//STL mapa za cuvanje parova {engleska rec, srpska rec} - kljuc u mapi su engleske reci, vrednosti su srpske reci   
	map<string, string> recnik; 

    recnik["black"] = "crna"; //ubacivanje u mapu para {black, crna}
    recnik["white"] = "bela";
    recnik["red"] = "crvena";

    string engleska_rec; //promenljiva u koju ce se upisati unesena rec sa konzole
    //korisnik unosi red sa konzole. unos se vrsi dok se ne pritisne ENTER. Tada se unesena slova ubacuju u promenljivu engleska_rec
    while (getline(cin, engleska_rec))  //petlja ce se izvrsavati dok se ne pritisne Ctrl+d (Tada funkcija getline vraca false)
        cout << "Prevod: " << recnik[engleska_rec] << endl; //u mapi se za uneseni kljuc (engleska_rec) pronalazi vrednost (odgovarajuca srpska rec) 
}
