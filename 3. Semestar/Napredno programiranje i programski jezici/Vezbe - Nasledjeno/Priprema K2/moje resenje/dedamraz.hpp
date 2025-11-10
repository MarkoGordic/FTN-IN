#ifndef DEDAMRAZ_HPP_INCLUDED
#define DEDAMRAZ_HPP_INCLUDED

class DedaMraz {
private:
    List <NovogodisnjiPaketic> novogodisnjiPaketici;
public:
    DedaMraz () {
        novogodisnjiPaketici.clear();
    }

    bool dodaj (const DinString& o, const Dete& d, int uzrast, Pol p) {
        NovogodisnjiPaketic paket(o, d, uzrast);
        paket.isporuci();
        if (novogodisnjiPaketici.empty())
            return novogodisnjiPaketici.add(1, paket);

        int brojac = 0;
        for (int i = 1; i <= novogodisnjiPaketici.size(); i++) {
            NovogodisnjiPaketic temp;
            novogodisnjiPaketici.read(i, temp);
            if (temp.getNamenjen().getPol() == p)
                brojac++;
        }
        if (brojac < 5)
            return novogodisnjiPaketici.add(novogodisnjiPaketici.size() + 1, paket);
        return false;
    }

    bool izbaci (int uzrast) {
        for (int i = 1; i <= novogodisnjiPaketici.size(); i++){
            NovogodisnjiPaketic temp;
            novogodisnjiPaketici.read(i, temp);
            if (temp.getMinimalanUzrast() < uzrast) {
                return novogodisnjiPaketici.remove(i);
            }
        }
        return false;
    }

    double prosecanMinimalanUzrast () const {
        double suma = 0;
        NovogodisnjiPaketic temp;
        for (int i = 1; i <= novogodisnjiPaketici.size(); i++){
            novogodisnjiPaketici.read(i, temp);
            suma += temp.getMinimalanUzrast();
        }
        return suma / novogodisnjiPaketici.size();
    }

    void ispis () const {
        if (novogodisnjiPaketici.empty()) {
            cout << "Prazna lista!" << endl;
            return;
        }
        cout << "DEDA MRAZ" << endl;
        NovogodisnjiPaketic temp;
        for (int i = 1; i <= novogodisnjiPaketici.size(); i++){
            novogodisnjiPaketici.read(i, temp);
            temp.ispisi();
            cout << endl;
        }
    }
};

#endif // DEDAMRAZ_HPP_INCLUDED
