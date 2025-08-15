#include <iostream>
#include <functional>
#include <vector> 

using namespace std;

/*
    Napraviti funkciju koja sortira dati vektor int-ova koristeći
    za određivanje da li je neki element manji ili veći od drugog
    prosleđenu funkciju. Demonstrirati ovo kroz lambda izraz. 

    Bonus zadaci:
    1. Implementirati ovo da radi sa bilo kojim tipom kroz
    šablone. 
    2. Implementirati ovo kroz quicksort algoritam. 
*/

template<class T> void quicksort(vector<T>& v, int lo, int hi, function<int(T,T)> cmp){
    if(lo >= hi) return;
    int pivot = lo + (hi - lo) / 2;
    T temp;
    int storeLoc = lo;
    temp = v[pivot];
    v[pivot] = v[hi];
    v[hi] = temp;

    for(int i = lo; i < hi;i++){
        if(cmp(v[i], v[hi]) < 0){
            temp = v[storeLoc];
            v[storeLoc] = v[i];
            v[i] = temp;
            storeLoc++;
        }
    }
    temp = v[storeLoc];
    v[storeLoc] = v[hi];
    v[hi] = temp;
    quicksort<T>(v, lo, storeLoc - 1, cmp);
    quicksort<T>(v, storeLoc + 1, hi, cmp);
    return;
}

template<class T> void quicksort(vector<T>& v, function<int(T,T)> cmp){
    quicksort<T>(v, 0, v.size() - 1, cmp);
}

int main(){
    vector<int> v;
    v.push_back(3);v.push_back(1);v.push_back(4);
    v.push_back(1);v.push_back(5);v.push_back(9);
    v.push_back(2);v.push_back(6);v.push_back(7);
    quicksort<int>(ref(v), [](int a, int b) -> int {
        if(a > b){
            return 1;
        }else if(a == b){
            return 0;
        }else{
            return -1;
        }
    });
    for(int i = 0; i < v.size();i++){
        cout << v[i] << endl;
    }   
}