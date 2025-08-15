#include <functional>
#include <iostream>
using namespace std;


/*
    Sintaksa function<int(int)> znači da ova funkcija prima kao svoj
    parametar druge funkcije. Prosleđenu funkciju možemo da tretiramo apsolutno
    isto kao bilo koju drugu funkciju i da je, npr. pozovemo.
    function<int(int)> označava funkciju koja vraća integer vrednost i
    prima jedan integer parametar.
    function<int(int,double)> bi označavalo funkciju koja vraća int, ali prima
    2 parametra koja su int i double.
*/
int uradiNesto(int x,  function<int(int)> f){
    int y = f(x);
    return y;
}


/*
    Funkcija koja odgovara signaturi function<int(int)>
*/
int increment(int x){
    return x + 1;
}

int main(){
    int x = 5;
    int val = 7;
    cout << uradiNesto(x, increment) << endl;
    //Najprostiji tip pozivanja ovakve funkcije je da joj samo damo ime
    //postojeće funkcije kao parametar.
    cout << uradiNesto(x, [](int y) -> int {return y + 1;}) << endl;
    //Alternativa je nešto što se zove 'lambda izraz.' Razlog za ime je
    //oblik formalizma proračuna koji se zove lambda račun. U praksi
    //Lambda izrazi su literali funkcija, na način na koji je 3 literal int-a
    //Uglaste zagrade objašnjavamo kasnije (ali su obavezne), onda ide lista
    //parametara, kao da je u pitanju funkcija, te onda simbol ->, pa povratni
    //tip funkcije (ovde int) i onda u velikim zagradama telo funkcije.
    //Ovde je to jedan jedini red, ali može imati koliko god mi želimo.

    //cout << uradiNesto(x, [](auto y) -> auto {return y + 1;}) << endl;

    //Pošto naš kompajler zna koje tipove podataka očekuje, moguće je tražiti
    //od njega da pogodi koji tipovi nam trebaju tako što se umesto stvarnog
    //tipa stavi 'auto.' Ovo je poznato kao 'type inference'. Zašto zakomentarisano?
    //Zato što je za ovo kompajler tek pametan dovoljno u verziji C++ 2014
    //Koju vi možda nemate.

    cout << uradiNesto(x, [&val](int y) -> int {return y + val;}) << endl;

    //Uglaste zagrade imaju posebnu namenu: one služe za tkzv. 'capture.'
    //To znači da želimo da sa mesta gde definišemo našu lambdu koristimo neke
    //lokalno dostupne promenljive u telu lambde, gde god da ona na kraju bude
    //korišćena. Ova tehnika se zove klauzura i može da bude jako korisna.
    cout << uradiNesto(x, [&val](int y) -> int {val++;return y + val;}) << endl;
    cout << uradiNesto(x, [&val](int y) -> int {return y + val;}) << endl;
    //Budući da klauzura postoji kroz referencu, to znači da možemo da menjamo
    //stvari iz naše lambde.
    cout << uradiNesto(x, [val](int y) -> int {return y + val;}) << endl;
    //Klauzura može i bez reference, ali onda nema šanse da nešto izmenimo,
    //i za svaku lambdu se pravi kopija.

    return 0;
}
