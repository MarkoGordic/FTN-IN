#include <iostream>
#include <cstdint>
#include <vector>
#include <future>

uint64_t fibo(uint64_t n
    // Parametri
) {
    /* Implementirati:
        - dodati neophodne parametre funkcije
        - funkciju koja računa n-ti element fibonačijevog niza
    */
    if( n <= 2)
        return 1;
    auto f1 = std::async(std::launch::async,fibo,n-1);
    auto f2 = std::async(std::launch::async,fibo,n-2);
    return f1.get()+f2.get();
}
int main(int argc, char * argv[]) {

    const uint64_t N = 11;
    /* Implementirat:
        - Poziv fukncije koja rekurzivno racuna n-ti element fibonacijevog niza
    */
    auto f = std::async(std::launch::async,fibo,N);
    /* Implementirat:
        - Ispisati rezultat
    */
    std::cout<< N<< "-ti element fibonacijevog niza je "<< f.get()<<std::endl;
}

