#ifndef NIZ_HPP_INCLUDED
#define NIZ_HPP_INCLUDED

template <class T, int DUZINA>
class Niz {
private:
    T niz[DUZINA];
    int brEl;
public:
        Niz() { brEl=0; }
        ~Niz() {}

        int getBrEl() const { return brEl; }

        T operator[](int i) const { return niz[i]; } // citanje
        T& operator[](int i) { return niz[i]; }      // upis

        Niz<T,DUZINA>& operator=(const Niz<T,DUZINA>& n) {
            for (brEl = 0; brEl < n.brEl; brEl++){
                niz[brEl] = n.niz[brEl];
            }
            return *this;
        }

        void printNiz() const {
            for (int i = 0; i < brEl; i++)
                cout << "el[" << i << "] = " << niz[i] << endl;
        }

        bool insertNiz(const T& t) {
            if (brEl >= DUZINA)
                return false;
            niz[brEl++] = t;
            return true;
        }
};

template <class T, int DUZINA>
bool operator==(const Niz<T, DUZINA>& n1, const Niz<T, DUZINA>& n2) {
    if (n1.getBrEl() != n2.getBrEl())
        return false;
    for (int i = 0; i < n1.getBrEl(); i++){
        if (n1.niz[i] != n2.niz[i])
            return false;
    }
    return true;
}

template <class T, int DUZINA>
bool operator!=(const Niz<T, DUZINA>& n1, const Niz<T, DUZINA>& n2) {
    return n1==n2;
}

#endif // NIZ_HPP_INCLUDED
