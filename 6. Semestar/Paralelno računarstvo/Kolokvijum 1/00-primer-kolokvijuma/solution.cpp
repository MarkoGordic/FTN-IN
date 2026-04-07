#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t n;

    do {
        std::cout << "Unesite broj elemenata niza: ";
        std::cin >> n;
    } while (n <= 4);

    std::vector<int> niz(n);
    std::cout << "Unesite elemente: ";
    for (size_t i = 0; i < n; i++)
        std::cin >> niz[i];

    std::atomic<int> suma(0);
    const size_t brojNiti = 4;
    std::vector<std::future<int>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        size_t pocetak = i * n / brojNiti;
        size_t kraj = (i + 1) * n / brojNiti;

        rezultati.emplace_back(std::async(std::launch::async,
            [&niz, &suma, pocetak, kraj]() -> int {
                int minimum = niz[pocetak];
                for (size_t j = pocetak; j < kraj; j++) {
                    if (niz[j] < minimum)
                        minimum = niz[j];
                    suma.fetch_add(niz[j]);
                }
                return minimum;
            }));
    }

    // Peta nit - ispis minimuma u obrnutom redosledu
    auto nitZaIspis = std::async(std::launch::async, [&rezultati]() {
        for (int i = 3; i >= 0; i--) {
            int val = rezultati[i].get();
            std::cout << "Minimum " << (i + 1) << ". cetvrtine: " << val << std::endl;
        }
    });

    std::cout << "\n--- Lokalni minimumi (obrnuti redosled) ---" << std::endl;
    nitZaIspis.get();

    std::cout << "\nSuma svih elemenata: " << suma.load() << std::endl;

    return 0;
}