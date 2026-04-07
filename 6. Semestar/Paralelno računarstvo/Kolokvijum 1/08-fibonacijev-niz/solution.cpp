#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t N;

    do {
        std::cout << "Unesite prirodan broj N: ";
        std::cin >> N;
    } while (N <= 8);

    std::atomic<int> brojParnih(0);

    const size_t brojNiti = 4;
    const size_t blok = N / brojNiti;
    size_t ostatak = N % brojNiti;
    size_t pocetak = 1, kraj;

    std::vector<std::future<std::vector<std::pair<size_t, uint64_t>>>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto obradi = [&brojParnih](size_t pocetak, size_t kraj) -> std::vector<std::pair<size_t, uint64_t>> {
            std::vector<std::pair<size_t, uint64_t>> fibBrojevi;

            for (size_t n = pocetak; n <= kraj; n++) {
                auto fibonacci = [] (auto self, size_t n) -> uint64_t {
                    if (n < 2) return n;
                    return self(self, n - 1) + self(self, n - 2);
                };

                uint64_t fib = fibonacci(fibonacci, n);
                
                fibBrojevi.emplace_back(n, fib);

                if (fib % 2 == 0)
                    brojParnih.fetch_add(1);
            }

            return fibBrojevi;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, obradi, pocetak, kraj));
        pocetak = kraj + 1;
    }

    // Peta nit - ispis u obrnutom redosledu
    auto nitZaIspis = std::async(std::launch::async, [&rezultati]() {
        for (size_t i = 1; i <= 4; i++) {
            auto fibBrojevi = rezultati.at(4 - i).get();

            std::cout << "Cetvrtina " << (4 - i + 1) << ":";
            for (auto par : fibBrojevi)
                std::cout << "  fib(" << par.first << ")=" << par.second;
            std::cout << std::endl;
        }
    });

    std::cout << "\n--- Fibonacijevi brojevi (obrnuti redosled cetvrtina) ---" << std::endl;
    nitZaIspis.get();

    std::cout << "\nBroj parnih Fibonacijevih brojeva: " << brojParnih.load() << std::endl;

    return 0;
}
