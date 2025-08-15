#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class Nesto{
    public:
        Nesto(){
            cout << "Konstruktor klase Nesto na adresi " << this << endl;
        }
        ~Nesto(){
            cout << "Destruktor klase Nesto na adresi " << this << endl;
        }
        void akcija(){
            cout << "Neka akcija klase Nesto na adresi " << this << endl;
        }
};


struct Struktura{
        Nesto* goli;
        unique_ptr<Nesto> pametan;
        shared_ptr<Nesto> deljen;
};

int main(){
    cout << "Program pocinje" << endl;
    /*
        Ovaj primer demonstrira rad sa običnim pokazivačem na kojim ste navikli.
        Problem sa takvim pokazivačem jeste da morate da pamtite da ga obrišete, prvo
        i drugo, on može biti smešten bilo gde, u bilo koju lokaciju, bilo kada u
        bilo kom broju primera što može da dovede do toga da se obriše na više mesta
        (greška), ne obriše nigde (greška), ili koristi mnogo pošto je obrisan
        (naročito loša greška).

        Zbog toga se upotreba ovakvih, 'golih' pokazivača više ne preporučuje u
        produkcionom kodu.
    */
    cout << "Primer #1: 'Go' pointer" << endl;
    {
        Struktura s;
        {
            Nesto* n = new Nesto();
            s.goli = n;
            n->akcija();
            s.goli->akcija();
            delete n;
        }
        s.goli->akcija();//Ovaj kod, zastrašujuće, __neće izazvati grešku.__
        //Uprkos tome što je ovo pokazivač na nekorišćenu memoriju, podaci su
        //ostali i kod će se izvršiti. Možda. Ako je neko alocirao tu memoriju u međuvremenu
        //greške će biti. Ovo je užasan problem za debagovanje.
    }

    cout << "Primer #2: Jedinstveni pointer" << endl;
    /*
        Jedinstveni pokazivači, sa druge strane, nude mnoga poboljšanja. Prvo, jedinstveni su
        to znači da ne možete ni slučajno da ih kopirate. Jedinstvenost je garantovana i
        pokušaj konstruktora kopiranja ili operatora dodele izaziva grešku.

        Jedino što možete da uradite sa jedinstvenim pokazivačem jeste da ga pomerite, tj.
        da prestane da važi na jednom mestu i počne da važi na drugom. Zašto ovako?
        Zato što tako memorija ostaje uvek u poznatoj nadležnosti: nikad se neće desiti da
        ne znate čija je to memorija. Ovo je, takođe, način da vam, npr. funkcija vrati memoriju
        i da bude jasno da je vaš posao, kada dobijete tu memoriju, da je počistite.

        Još bolje, jedinstven pokazivač zna kada izađe iz opsega, tj, iz funkcije ili bloka u
        kome je generisan. Čim se to desi, on dealocira svoju memoriju istog trenutka.
        To znači da možete da se opustite oko delete operatora. Biće pozvan mesto vas,
        kada god vam je potreban.

        Veliku većinu vremena, pokazivači koje želite su baš ovakvi, jedinstveni
        pokazivači.
    */
    {
        Struktura s;
        {
            unique_ptr<Nesto> n(new Nesto());
            n->akcija();
            s.pametan = move(n);//Ovim se koriste takozvani konstruktori pomeranja
            //Da se n __premesti__ u s.pametan. To znači da n više ne postoji, efektno
            //i da je kontrola prebacena u s.pametan.
            s.pametan->akcija();
        }
        s.pametan->akcija();//Za razliku od prvog primera, ovo i treba da radi. Tek kada
        //s izađe iz opsega će destruktor biti pozvan, budući da je kontrola nad resursom
        //alociranim gore u liniji 80 prebačena u ruke strukture. Ovo je mala razdaljina
        //ovde u primeru, ali u ozbiljnom programu, to prebacivanje može ići bilo gde.
    }
    cout << "Primer #3: Deljen pointer" << endl;
    /*
        Deljeni pokazivači su kao i pametni sa jednom razlikom: mogu se kopirati slobodno,
        ali svaki pamti da je kopija i na centralnom mestu se broji koliko referenci ima
        na datu memoriju. Kako koji shared_ptr izlazi iz svog opsega, poziva svoj
        destruktor koji smanjuje globalni brojač referenci za 1. Kada on dostigne vrednot 0
        Dealocira se i memorija na koju pokazivač pokazuje.

        To znači da možete imati dva pokazivača na neku memoriju i osloboditi je tek kada su
        oba izbačena iz opsega. Ovo je jako moćan alat.
    */
    {
        Struktura s;
        {
            auto n = make_shared<Nesto>();//Parametri 'make_shared' su ono što bi išlo u
            //konstruktor klase 'Nesto.' Pozivanjem ovoga broj referenci je sada 1.
            s.deljen = n; //Kopira se ovde. Broj referenci je sada 2.
            n->akcija();
            s.deljen->akcija();
        } //Ovde se broj referenci smanjuje na 1, jer je 'n' izašao iz opsega.
        s.deljen->akcija();
    }//Destruktor se poziva tek ovde jer je broj referenci tek ovde 0 izlaskom iz opsega
    //s, što izbacuje iz opsega sve njene elemente uključujući i 'deljen.'

    cout << "Gotov program." << endl;
    return 0;
}
