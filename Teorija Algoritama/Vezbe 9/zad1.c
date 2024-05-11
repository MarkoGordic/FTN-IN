#include <stdio.h>

#define N 3
#define M 3

int min(int x, int y, int z) {
    if (x < y)
        return (x < z) ? x : z;
    else
        return (y < z) ? y : z;
}

int najjeftinija_putanja(int matrica[N][M]){
    int cene[N][M];

    cene[0][0] = matrica[0][0];

    for(int k = 1; k < M; k++){
        cene[0][k] = matrica[0][k-1] + matrica[0][k];
    }

    for(int k = 1; k < N; k++){
        cene[k][0] = matrica[k-1][0] + matrica[k][0];
    }

    for(int k = 1; k < N; k++){
        for(int u = 1; u < M; u++){
            cene[k][u] = min(cene[k-1][u], cene[k][u-1], cene[k-1][u-1]) + matrica[k][u];
        }
    }

    return cene[N - 1][M - 1];
}

int main() {
    int matrica[N][M] = {
        {1, 2, 1},
        {1, 3, 5},
        {1, 2, 3}
    };

    printf("Najmanja cena za matricu je : %d.\n", najjeftinija_putanja(matrica));

    return 0;
}