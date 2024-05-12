#include <stdio.h>
#include <math.h>

//      brojilac
//      --------
//      imenilac

int nzd(int a, int b){
    if(b == 0)
        return a;

    return nzd(b, a % b);
}

void ispisiEgipatskiRazlomak(int imenilac, int brojilac){
    while(brojilac != 0){
        int x = ceil((double)imenilac/brojilac);
        printf("1/%d + ", x);

        brojilac = brojilac * x - imenilac;
        imenilac = imenilac * x;

        int NZD = nzd(brojilac, imenilac);
        brojilac /= NZD;
        imenilac /= NZD;
    }

    printf("\b\b \n");
}

int main(){
    int imenilac = 14, brojilac = 6;

    printf("Egipatski razlomak za %d/%d je : ", brojilac, imenilac);
    ispisiEgipatskiRazlomak(imenilac, brojilac);
    return 0;
}