#include <stdio.h>
#include <string.h>

int min(int x, int y, int z) {
    if (x <= y && x <= z) return x;
    if (y <= x && y <= z) return y;
    return z;
}

int broj_izmena(char* str1, char* str2){
    int n = strlen(str2); // Radule
    int m = strlen(str1); // Rasa
    int izmene[n][m];

    for(int i = 0; i < m; i++)
        izmene[0][i] = i;

    for(int j = 0; j < n; j++)
        izmene[j][0] = j;

    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(str1[j] == str2[i])
                izmene[i][j] = izmene[i-1][j-1];
            else {
                izmene[i][j] = min(izmene[i-1][j] + 1, izmene[i][j-1] + 1, izmene[i-1][j-1] + 1);
            }
        }
    }

    return izmene[n-1][m-1];
}

int main(){
    char ime1[15] = "Rasa\0";
    char ime2[15] = "Radule\0";

    printf("%s -> %s IZMENE = %d\n", ime1, ime2, broj_izmena(ime1, ime2));

    return 0;
}