#include <stdio.h>

/* Ovo je jednostavan C program za testiranje blok komentara */

/* Ovo je
   viselinijski
   blok komentar
*/

int main(void) {
    int x = 5;
    int y = 10;
    int z;

    /* Jednostavan komentar */
    z = add(x, y);

    printf("Rezultat je: %d\n", z);

    /* komentar sa zvezdicama *** i jos teksta */

    /* komentar u sred koda */ x = 2000;

    printf("Rezultat nakon inkrementa: %d\n", z);

    /* Sada slede specijalni primeri iz zadatka */

    /* komentar * komentar */          // ovde samo do prvog */ je blok komentar
    nije_komentar();                   // ostatak linije je obican kod za lexer

    /* komentar **/                    // blok komentar se zavrsava ovde
    nije_komentar_opet();              // ostatak treba da bude obican kod

    return 0;
}
