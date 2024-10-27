#ifndef LOVAC_HPP_INCLUDED
#define LOVAC_HPP_INCLUDED

#include <iostream>
using namespace std;

const string ORANGE = "\033[38;5;214m";
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string ITALIC = "\033[3m";

enum StatusLovca {
    SPREMAN,
    UMORAN,
    PORAZEN
};

class Lovac {
private:
    int iskustvo;
    int snaga;
    int uhvaceniDuhovi;
    StatusLovca status;

public:
    Lovac() {
        iskustvo = 0;
        snaga = 40;
        uhvaceniDuhovi = 0;
        status = SPREMAN;
    }

    Lovac(int iskustvo, int snaga, int uhvaceniDuhovi, StatusLovca status) {
        this->iskustvo = iskustvo;
        this->snaga = snaga;
        this->uhvaceniDuhovi = uhvaceniDuhovi;
        this->status = status;
    }

    bool dodajIskustvo(int poeni) {
        if (iskustvo + poeni > 50) {
            return false;
        }

        iskustvo += poeni;
        cout << "Lovac je stekao " << poeni << " poena iskustva!\n";

        return true;
    }

    bool smanjiSnagu(int vrednost) {
        snaga -= vrednost;
        if (snaga < 0) {
            snaga = 0;
            status = PORAZEN;
            cout << "Lovac je poražen! Igra je gotova.\n";
            exit(0);
        }

        if (snaga < 20) {
            status = UMORAN;
            cout << "Lovac je umoran.\n";
        }

        return true;
    }

    void uhvatiDuha() {
        uhvaceniDuhovi++;
        cout << "Lovac je uhvatio duha! Ukupno uhvacenih duhova: " << uhvaceniDuhovi << endl;

        if (uhvaceniDuhovi >= 4) {
            cout << "Lovac je uhvatio sve duhove! Lov je završen!\n";
            exit(0);
        }
    }

    void resetujLovca() {
        snaga = 50;
        iskustvo = 0;
        uhvaceniDuhovi = 0;
        status = SPREMAN;
        cout << "Lovac je resetovan.\n";
    }

    void ispisi() const {
        cout << "Snaga lovca: " << snaga << endl;
        cout << "Iskustvo: " << iskustvo << endl;
        cout << "Uhvaćeno duhova: " << uhvaceniDuhovi << endl;
        cout << "Status: ";

        switch (status) {
            case SPREMAN:
                cout << "SPREMAN" << endl;
                break;
            case UMORAN:
                cout << "UMORAN" << endl;
                break;
            case PORAZEN:
                cout << "PORAŽEN" << endl;
                break;
            default:
                cout << "NEPOZNAT" << endl;
        }
    }

    int getIskustvo() const { return iskustvo; }
    int getSnaga() const { return snaga; }
    int getUhvaceniDuhovi() const { return uhvaceniDuhovi; }
    StatusLovca getStatus() const { return status; }

    void setIskustvo(int iskustvo) { this->iskustvo = iskustvo; }
    void setSnaga(int snaga) { this->snaga = snaga; }
    void setUhvaceniDuhovi(int uhvaceniDuhovi) { this->uhvaceniDuhovi = uhvaceniDuhovi; }
    void setStatus(StatusLovca status) { this->status = status; }
};

#endif // LOVAC_HPP_INCLUDED
