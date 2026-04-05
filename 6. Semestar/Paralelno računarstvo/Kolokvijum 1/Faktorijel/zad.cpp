#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <future>

int main() {
    uint64_t n;

    do {
        std::cout << "Unesite prirodan broj N: ";
        std::cin >> n;
    } while (n <= 8);

    std::vector<std::future<size_t>> results;
    const size_t thread_count = 4;
    const size_t base = n / thread_count; // min broj elemenata u svakoj niti
    size_t remainder = n % 4; // ostatak elemenata za rasporedjivanje
    size_t start = 1, stop;
    std::atomic<size_t> total_sum(0);

    std::vector<size_t> partial_products;
    size_t total_sum_fac = 1;

    for(size_t i = 0; i < 4; i++) {
        auto calc = [&total_sum] (size_t start, size_t end) -> size_t {
            size_t sum = 1;
            
            for(size_t j = start; j <= end; j++) {
                sum *= j;
                total_sum.fetch_add(j);
            }

            return sum;
        };

        stop = start + base - 1;
        if(remainder) {
            stop++;
            remainder--;
        }

        results.emplace_back(std::async(std::launch::async, calc, start, stop));

        start = stop + 1;
    }

    auto fut = std::async(std::launch::async, [&results, &partial_products] () {
        for(size_t i = 1; i <= 4 ; i++){
            size_t val = results.at(4-i).get();
            std::cout << "Parcijalni proizvod " << 4 - i << " dela: " << val << std::endl;
            partial_products.emplace_back(val);
        }
    });

    fut.get(); // cekamo da zavrsi
    //            ovo je tu radi vezbe, u realnosti bi se nit iznad izvrsavala sinhrono
    
    for(auto& r : partial_products)
        total_sum_fac *= r;

    std::cout << "Ukupan faktorijel broja N: " << total_sum_fac << std::endl;
    std::cout << "Zbir svih brojeva: " << total_sum.load() << std::endl;
};