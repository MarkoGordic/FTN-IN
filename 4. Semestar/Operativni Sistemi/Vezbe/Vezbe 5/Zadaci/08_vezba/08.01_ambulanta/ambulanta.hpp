#ifndef AMBULANTA_HPP_INCLUDED
#define AMBULANTA_HPP_INCLUDED

#include "student.hpp"

using namespace std;

class Studentska_ambulanta {
private:
    Student& student;
public:
    Studentska_ambulanta(Student& st, int muskih, int zenskih) : student(st) {
        // Prosiriti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira studenta u ambulanti kada student pokusava da udje u nju.
    // Ukoliko je ambulanta zauzeta, izvrsenje ove metode ce cekati da se ona oslobodi.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    //
    // Potrebno je pozvati metodu student.ceka kada student ne moze da stupi u ambulantu.
    // Potrebno je pozvati metodu student.ulazi kada student udje u ambulantu.
    void udji(int rbr, Pol p) {
        // Implementirati ...
    }

    // Metoda koju poziva nit koja simulira studenta u ambulanti nakon sto je student pregledan i izlazi iz nje.
    //
    // rbr - Redni broj studenta
    // p   - Pol studenta
    void izadji(int rbr, Pol p) {
        // Implementirati ...
    }
};

#endif // AMBULANTA_HPP_INCLUDED
