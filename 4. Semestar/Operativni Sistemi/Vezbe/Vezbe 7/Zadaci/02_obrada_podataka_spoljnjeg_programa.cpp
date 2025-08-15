/**
 * Napisati program koji na standardnom izlazu prikazuje predloge lozinki od 80
 * znakova koje sadrze u sebi string "caj".
 * 
 * Uz oslonac na `fork`, `wait` i `execv` sistemske pozive, pokrenuti program 
 * "/usr/bin/gpg" kao spoljasnji program sa parametrima {"--gen-random", 
 * "--armor", "1", "4000000"}. Spoljasnji program i roditelja povezati 
 * pajpovanjem tako da izlaz spoljasnjeg programa obradjuje roditeljski proces.
 * 
 * Spoljasnji program ce izgenerisati sekvencu od 4000000 nasumicnih znakova a
 * bez belih znakova
 * 
 * Obrada treba da se desava tako da roditelj uzima po 80 znakova i tretira ih
 * kao jednu lozinku. Potom ako u ucitanih 80 znakova pronadje string "caj", 
 * ispisuje lozinku na standardni izlaz.
 * 
 * NAPOMENA: moze se dosta jednostavno uraditi ako se odvoji bafer od 81-og 
 * znaka i na kraju postavi '\0' nakon ucitavanja 80 znakova
*/
#include <iostream>
#include <unistd.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"