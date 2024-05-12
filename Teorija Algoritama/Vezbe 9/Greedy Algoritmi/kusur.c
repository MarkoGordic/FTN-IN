/*
Спремајући се за пут у Египат, Милош је читао о новчаном систему у древном Египту.
Открио је да су постојале само новчанице у вредности d⋅10k за за свако d из скупа {1,2,5},
и за сваки ненегативан цео број k, тј. новчанице у вредности {1,2,5,10,20,50,100,200,500,…}.
Размишљајући о овоме, Милош се запитао колико је најмање новчаница потребно да се исплати нека сума V?
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long int stepen;
    int prva_cifra;
} Novcanica;

Novcanica prvaCifra(long long broj){
    broj = abs(broj);
    int stepen = 1;

    while(broj >= 10) {
        broj /= 10;
        stepen = stepen * 10;
    }

    Novcanica novcanica;
    novcanica.stepen = stepen;
    novcanica.prva_cifra = broj;
    return novcanica;
}

int main(){
    long long int V;
    int brojac = 0;
    printf("Unesite V: ");
    scanf("%lld", &V);

    while(V != 0){
        Novcanica novcanica = prvaCifra(V);
        printf("Procesuiram broj %lld, cifru %d i stepen %lld!\n", V, novcanica.prva_cifra, novcanica.stepen);
        if(novcanica.prva_cifra == 0){
            return 0;
        }

        if(novcanica.prva_cifra >= 5){
            V = V - (5 * novcanica.stepen);
            brojac++;
        } else if(novcanica.prva_cifra >= 2){
            brojac = brojac + (novcanica.prva_cifra / 2);
            V = V - ((2 * novcanica.stepen) * (novcanica.prva_cifra / 2));
        } else {
            V = V - novcanica.stepen;
            brojac++;
        }
    }

    printf("Minimalan broj novcanica je : %d.\n", brojac);

    return 0;
}