#ifndef AMBULANTA_HPP_INCLUDED
#define AMBULANTA_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "student.hpp"

using namespace std;

class Studentska_ambulanta {
private:
    Student& student;
    mutex m; //propusnica za pristup iskljucivom regionu
    int broj_mesta[2]; //broj slobodnih mesta u muskoj, odnosno zenskoj ambulanti
    condition_variable ambulanta_slobodna[2]; //redovi cekanja na musku, odnosno zensku ambulantu
public:
    Studentska_ambulanta(Student& st, int muskih, int zenskih) : student(st) {
        broj_mesta[0] = muskih;
        broj_mesta[1] = zenskih;
    } //inicijalno su sva mesta slobodna

    // Metoda koju poziva nit koja simulira studenta u ambulanti kada student pokusava da udje u nju.
    // Ukoliko je ambulanta zauzeta, izvrsenje ove metode ce cekati da se ona oslobodi.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    //
    // Potrebno je pozvati metodu student.ceka kada student ne moze da stupi u ambulantu.
    // Potrebno je pozvati metodu student.ulazi kada student udje u ambulantu.
    void udji(int rbr, Pol p) {
        unique_lock<mutex> l(m); //trazimo propusnicu pre pristupa iskljucivom regionu
        while (broj_mesta[p] == 0) { //dok god nema slobodnih mesta u odgovarajucoj ambulanti, student ceka
            student.ceka(rbr, p);
			ambulanta_slobodna[p].wait(l);
            
        }
        student.ulazi(rbr, p);
        broj_mesta[p]--; //kad udje u ambulantu, u njoj je jedno slobodno mesto manje
    }

    // Metoda koju poziva nit koja simulira studenta u ambulanti nakon sto je student pregledan i izlazi iz nje.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    void izadji(int rbr, Pol p) {
        unique_lock<mutex> l(m);//trazimo propusnicu pre pristupa iskljucivom regionu
        broj_mesta[p]++;//kad izadje iz ambulante, u njoj je jedno slobodno mesto manje
        ambulanta_slobodna[p].notify_one(); //javimo jednom od onih koji cekaju
    }
};

#endif // AMBULANTA_HPP_INCLUDED
