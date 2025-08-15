/**
 * Program koji racuna sumu korena nenegativnih brojeva iz kolekcije brojeva.
*/
#include <iostream>
#include <sched.h>
#include <sys/wait.h>  // za opciju SIGCHLD

#define VELICINA_STEKA (1024*1024)  // odvajanje bar 1MB za stek decjeg procesa 


int brojevi(void* argumenti) {
    int *niz = (int*) argumenti;  // posto nam memorijski blok argumenata sadrzi 2 cela broja, mozemo ga gledati kao niz i tako raspakovati
    
    int a = niz[0];  // preuzimanje prvog argumenta
    int b = niz[1];  // preuzimanje drugog argumenta

    std::cout << a << " " << b << std::endl;

    return 0;
}


int main() {
    char *stek = new char[VELICINA_STEKA];  // alokacija memorijskog bloka za stek
    char *argumenti = new char[sizeof(int)*2];  // alokacija memorijskog bloka za argumente
    
    // pod pretpostavkom da pakujemo 2 promenljive tipa int u blok, u naredne 2 linije je 
    // inicijalizacija promenljivih na brojeve 1 i 2 tim redom 
    argumenti[0] = 1;
    argumenti[4] = 2;

    pid_t dete = clone(&brojevi, stek+VELICINA_STEKA, CLONE_VM|SIGCHLD, argumenti);  // saljemo adresu poslednjeg bajta steka jer se stek koristi unazad!

    wait(nullptr);  // cekanje na decji proces

    std::cout << "Klonirani proces gotov." << std::endl;

    // SVA DINAMICKI ZAUZETA MEMORIJA SE MORA OSLOBODITI!
    delete[] argumenti;
    delete[] stek;

    return 0;
}