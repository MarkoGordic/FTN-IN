//Program koji racuna 
//apsolutnu vrednost unetog broja

/* Ovo je main funkcija
   koja ce samo pozvati abs funkciju
   i ispisati rezultat */
int main() {
  int res;
  res = abs(); // poziv funkcije
  printf("Apsolutna vrednost je %d", res);
}

//Funkcija koja racuna apsolutnu vrednost
int abs(int broj) {
  if(broj < 0)
    return 0 - broj; //negativan broj
  else
    return broj;     //pozitivan broj
}

