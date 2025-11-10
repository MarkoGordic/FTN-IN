#ifndef NIZ_HPP_INCLUDED
#define NIZ_HPP_INCLUDED

// zasto koristimo genericke klase?
// kako bismo mogli praviti vise klasa Niz koje su razlicite duzine
// i koje imaju razliciti tip niza unutar sebe

// i sto je slozenija klasa -> vise izmena konkretizacije
// sto znaci da je ovo idealna situacija da koristimo genericke

template <class TIP, int DUZINA>
class Niz{
private:
    TIP niz[DUZINA];
    bool popunjenost[DUZINA];
    int brojElemenata;
public:
    Niz () {
        for (int i = 0; i < DUZINA; i++) {
            popunjenost[i] = false;
        }
        brojElemenata = 0;
    }

    bool Unesi (const TIP& vrednost, int indeks) {
        if (brojElemenata < DUZINA) {
            if (popunjenost[indeks]) {
                return false;
            }
            niz[indeks] = vrednost;
            popunjenost[indeks] = true;
            brojElemenata++;
            return true;
        }
        return false;
    }

    void ispisi() {
        if (brojElemenata == 0) {
            cout << "Prazan niz!" << endl;
            return;

        }

        for (int i = 0; i < DUZINA; i++) {
            cout << "niz[" << i << "]: ";
            if (popunjenost[i])
                cout << niz[i] << endl;
            else
                cout << "x" << endl;
        }
    }
};

#endif // NIZ_HPP_INCLUDED
