#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;
using std::ref;
using std::string;
using std::thread;
using std::mutex;
using std::unique_lock;

void zdravo() {
    cout << "Zdravo Sveto!" << endl;
}

void zdravko_primer() {
    thread nit(zdravo);
    nit.join();
}

void visina_primer(thread &nit) {
    nit = thread([]()->void {
        int v;
        cout << "Unesite svoju visinu u [cm]: ";
        cin >> v;
        cout << "Vasa visina je " << v << "cm." << endl;
    });
    nit.detach();
}

void zbir(int a, int b, int &rez) {
    rez = a + b;
}

void argumenti_primer() {
    int rezultat = -420;
    thread nit(zbir, 2, 7, ref(rezultat));
    nit.join();
    cout << "Rezultat sabiranja: " << rezultat << endl;
}

#define ITER_NO 100000000
void trkanje_primer() {
    int brojac = 0;
    thread nit1([&brojac]() {for (int i = 0; i < ITER_NO; i++) brojac++;});
    thread nit2([&brojac]() {for (int i = 0; i < ITER_NO; i++) brojac--;});
    nit1.join();
    nit2.join();
    cout << brojac << endl;
}

void ekskluzivnost_primer() {
    int brojac = 0;
    mutex e;
    thread nit1([&brojac, &e]() {for (int i = 0; i < ITER_NO; i++) {e.lock(); brojac++; e.unlock();}});
    thread nit2([&brojac, &e]() {for (int i = 0; i < ITER_NO; i++) {e.lock(); brojac--; e.unlock();}});
    nit1.join();
    nit2.join();
    cout << brojac << endl;
}

mutex m;
void f() {  // napraviti 2 niti od funkcije f
   int * veliki_niz;
   try {
      m.lock();
      veliki_niz = new int[1000000000000];
      m.unlock();
   } catch (const bad_alloc& e) {
      cout << "Alokacija memorije neuspesna!: " << e.what() << endl;
   }
}

void propustenica_primer() {  // zaustaviti program sa Ctrl+C
    thread t1(f), t2(f);
    t1.join();
    t2.join();
}

int main() {
    thread nit;
    zdravko_primer();
    //visina_primer(nit);
    //argumenti_primer();
    //trkanje_primer();
    //ekskluzivnost_primer();
    //propustenica_primer();

    return 0;
}
