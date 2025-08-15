#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

void prvo_ja_primer() {
	mutex m;
    bool prvi = false;
    condition_variable prvi_prosao;

    thread nit1([&m, &prvi, &prvi_prosao] {
        unique_lock<mutex> l(m);
        while (!prvi) {
            prvi_prosao.wait(l);
        }
        cout << "Sacekali smo prvog!" << endl;
    }), nit2([&m, &prvi, &prvi_prosao] {
        unique_lock<mutex> l(m);
        prvi = true;
        cout << "Prvi zavrsio." << endl;
        l.unlock();
        prvi_prosao.notify_one();
    });

    nit1.join();
    nit2.join();
}

int main() {
    prvo_ja_primer();

    return 0;
}
