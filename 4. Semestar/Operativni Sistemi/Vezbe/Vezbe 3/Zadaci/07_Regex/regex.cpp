/*
Regex je jedan pod-jezik koji služi da opisuje klase stringova koje zadovoljavaju neke uslove
sadržaja ili forme. Recimo možemo ovim jezikom definisati šablon

^\d{13}$
On nam kaže da pričamo o string-u koji počinje (odatle ^) te ima cifru (to je \d)
i to koja se ponavlja 13 puta ({13}) i onda se završava. Rečeno prirodnijim jezikom
"String koji se sastoji od tačno 13 cifara i ničeg drugog." Recimo JMBG. 

Jezik može da opisuje i stvari slobodnije forme, recimo:

(\S+)@uns\.ac\.rs

Ovo nam kaže da _negde_ u stringu (nema ^ i $ znakova da nas učvrste za kraj i početak
stringa) očekujemo neki karakter koji nije razmak (to je \S) ponovljen 1 ili više puta (+) 
i želimo da se ta grupa \S+ posebno tretira, zato je u zagradama. Posle toga sledi samo
@uns.ac.rs. Jedino se . koristi u posebnom značenju "bilo koji karakter" tako da, kada se
misli na stvarnu tačku, mora biti escape-ovana kroz \ simbol. Drugim rečima, ovaj šablon
opisuje sve UNS mail adrese i omogućava nam da ih nađemo i, čak, brzo ekstrahujemo 
korisničko ime: primetite zagrade. 

Zagrade se mogu koristiti i za šablone koje služe za modifikaciju stringova. Recimo
zamislite da hoćemo da izmenimo listu imena i prezimena oblika
Gorana Goranovic
Filip Filipovic
Petar Petrovic
u
Goranovic, G.
Filipovic, F.
Petrovic, P.

Samo nam trebaju dva šablona, jedan za selekciju stringa i jedan za modifikovanje

Šablon prvi: ([[:upper:]])[[:alpha:]]+ ([[:alpha:]]+)
Šablon drugi: $2, $1.

Prvi šablon kaže 'Jedno veliko slovo' (to je ovo [[:upper:]]. Da hoćemo samo engleski
mogli smo mnogo jednostavnije [A-Z] što znači sve od A do Z) koje želimo da zapamtimo za
kasnije, zato je u zagradama. To što smo ga prvog stavili u zagrade znači da je on grupa
za prepoznavanje 1. Onda sledi bilo koje slovo (to je ono [[:alpha:]]) 
ponovljeno jedan ili više puta (to je +). Zatim razmak (koji smo ovde otkucali kao običan
razmak), zatim bilo koje slovo ponovljeno više puta koje pamtimo kao grupu 2. 

Drugi šablon se samo oslanja na prvi i kaže: Rezultat druge grupe (prezime) pa zarez pa
razmak, pa rezultat prve grupe, pa tačka. 

Regex služi za validaciju i za izvlačenje podataka iz stringova i neverovatno
je moćan. Koristi se u praktično svakom programskom jeziku i naučiti ga je jako dobra 
investicija vremena. Čak većina editora, definitivno svaki programerski poseduje
podršku za pretragu kroz regexp-e. 

Mi se ovde nećemo baviti svim osobinama regexp-a jer nisu direktno vezana za OS, ali vam se
preporučuje:

https://regex101.com/

Što je interaktivna laboratorija i debager regularnih izraza neverovatne moći. Uz pomoć
toga možete vrlo brzo konstruisati izraz koji vama treba. Nema opciju za C++ direktno
ali to je OK, C++ poštuje strogo ECMAScript standard za regularne izraze koji je identičan
onom za JavaScript. 
*/
#include <string>
#include <iostream>
#include <regex>

using namespace std;

int main(){
    string s1a = "1234567890123";
    string s1b = "123456789012";
    string s2a("Sva pitanja saljite na pveljko@uns.ac.rs, ne veljkop@uns.ac.rs, samo prva adresa je tacna.");
    string s3a("Gorana Goranovic\nFilip Filipovic\nPetar Petrovic");
    
    auto const r1 = regex("^\\d{13}$"); //Moraju dupli znakovi zato što će da 
    //c++ vidi \d i pomisli da je to string escape sekvenca, te mora \\. 
    auto const r2 = regex("(\\S+)@uns\\.ac\\.rs");
    auto const r3 = regex("([[:upper:]])[[:alpha:]]+ ([[:alpha:]]+)");

    if(regex_match(s1a, r1)){ //Ova funkcija proverava da li dati string odgovara datom šablonu. 
        cout << "String " << s1a << " ima oblik JMBG-a." << endl;
    }else{
        cout << "String " << s1a << " nema oblik JMBG-a." << endl;
    }

    if(regex_match(s1b, r1)){
        cout << "String " << s1b << "ima oblik JMBG-a." << endl;
    }else{
        cout << "String " << s1b << "nema oblik JMBG-a." << endl;
    }

    smatch mr2; //smatch je objekat koji sadrži podatke o tome kako se neki string uklapa
    //u dati šablon, tj. gde je nađeno šta je nađeno. 
    while(regex_search(s2a, mr2, r2)){ //Proizvodi ga ova regex_search funkcija.
        cout << "Nasao mail " << mr2[1] << "@uns.ac.rs" << endl;
        s2a = mr2.suffix();//Moramo da skratimo string da ne bi stalno nalazili istu stvar.
    } 

    string out = regex_replace(s3a, r3, "$2, $1.");
    cout << out << endl;


}