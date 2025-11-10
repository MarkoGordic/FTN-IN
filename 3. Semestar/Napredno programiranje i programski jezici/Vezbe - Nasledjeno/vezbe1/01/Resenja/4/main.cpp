#include <iostream>
using namespace std;

enum VrstaSortiranja {RASTUCE, OPADAJUCE};

void unosElemenata(int *niz, int duzina){
    cout << "Unesite elemente niza" << endl;
	
    for(int i = 0; i < duzina; i++){
        cout << "\tniz[" << i << "] = ";
        cin >> niz[i];
    }
    cout << endl;
}

void stampaj(int *niz, int duzina){
    for(int i = 0; i < duzina; i++){
         cout << "\tniz[" << i << "] = " << niz[i] << endl;
    }
    cout << endl;
}

void sortiraj(int *niz, int duzina, VrstaSortiranja vrstaSortiranja){
    int temp;

    switch (vrstaSortiranja){
        case RASTUCE:
            for(int i = 0; i < duzina - 1; i++) {
                //trazi se najmanji u "desnom" delu niza
                int minIndeks = i;
                for(int j = i + 1; j < duzina; j++){
                    if(niz[j] < niz[minIndeks]){
                        minIndeks = j;
                    }
                }

                //ako je pronadjen - zamene se i time se u "levom" delu formira sortirani deo niza
                if (minIndeks != i) {
                    temp = *(niz + i);
                    *(niz + i) = *(niz + minIndeks);
                    *(niz + minIndeks) = temp;
                }
            }
            break;
        case OPADAJUCE:
            for(int i = 0; i < duzina - 1; i++){
                //trazi se najveci u "desnom" delu niza
                int maxIndeks = i;
                for(int j = i + 1; j < duzina; j++){
                    if(niz[j] > niz[maxIndeks]){
                        maxIndeks = j;
                    }
                }
                if (maxIndeks != i) {
                    temp = *(niz + i);
                    *(niz + i) = *(niz + maxIndeks);
                    *(niz + maxIndeks) = temp;
                }
            }
            break;
    }
}

int main()
{
    int duzina;

    cout << "Unesite duzinu niza -> ";
    cin >> duzina;
    cout << endl;

    if(duzina <= 0){
        cout << "Greska: Duzina niza mora biti pozitivna vrednost.";
        return 0;
    }

    // dinamicka alokacija memorije niza promenjivih tipa 'int' duzine 'duzina'
    int *niz = new int[duzina];

    if(niz == NULL){
        cout << "Racunar nema dovoljno memorije!" << endl;
        return 0;
    }

    unosElemenata(niz,duzina);

    cout << "Niz pre sortiranja" << endl;
    stampaj(niz, duzina);

    cout << endl << "Niz posle rastuceg sortiranja" << endl;
    sortiraj(niz, duzina, RASTUCE);
    stampaj(niz, duzina);

    cout << endl << "Niz posle opadajuceg sortiranja" << endl;
    sortiraj(niz, duzina, OPADAJUCE);
    stampaj(niz, duzina);

    // oslobadjanje dinamicki alocirane memorije
    delete[] niz;

    return 0;
}
