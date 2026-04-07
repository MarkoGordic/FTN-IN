#include <iostream>
#include <vector>
#include <future>
#include <mutex>
#include <atomic>
#include <algorithm>

int main() {
    size_t brojElemenata;

    do {
        std::cout << "Unesite broj elemenata: ";
        std::cin >> brojElemenata;
    } while (brojElemenata < 4);

    std::vector<int> elementi(brojElemenata);
    std::cout << "Unesite elemente: ";
    for (size_t i = 0; i < brojElemenata; i++)
        std::cin >> elementi[i];

    std::vector<std::pair<int, uint64_t>> parovi;
    std::mutex mutexParova;
    std::atomic<int> vecihOdDeset(0);

    const size_t brojNiti = 3;
    const size_t blok = brojElemenata / brojNiti;
    size_t ostatak = brojElemenata % brojNiti;
    size_t pocetak = 0, kraj;

    std::vector<std::future<void>> niti;

    for (size_t i = 0; i < brojNiti; i++) {
        auto obradi = [&elementi, &parovi, &mutexParova, &vecihOdDeset](size_t pocetak, size_t kraj) {
            for (size_t j = pocetak; j <= kraj; j++) {
                uint64_t fakt = 1;
                for (int k = 2; k <= elementi[j]; k++)
                    fakt *= k;

                {
                    std::lock_guard<std::mutex> zakljucaj(mutexParova);
                    parovi.emplace_back(elementi[j], fakt);
                }

                if (elementi[j] > 10)
                    vecihOdDeset.fetch_add(1);
            }
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        niti.emplace_back(std::async(std::launch::async, obradi, pocetak, kraj));
        pocetak = kraj + 1;
    }

    auto nitZaIspis = std::async(std::launch::async, [&niti, &parovi, &vecihOdDeset]() {
        for (auto& f : niti)
            f.get();

        std::sort(parovi.begin(), parovi.end());

        std::cout << "\n--- Faktorijeli (sortirano) ---" << std::endl;
        for (auto& [broj, fakt] : parovi)
            std::cout << broj << "! = " << fakt << std::endl;

        std::cout << "\nBroj elemenata vecih od 10: " << vecihOdDeset.load() << std::endl;
    });

    nitZaIspis.get();

    return 0;
}
