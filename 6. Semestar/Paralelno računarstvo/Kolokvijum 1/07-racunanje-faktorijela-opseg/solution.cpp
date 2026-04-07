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

    const size_t brojNiti = 4;
    const size_t blok = N / brojNiti;
    size_t ostatak = N % brojNiti;
    size_t pocetak = 1, kraj;

    std::atomic<size_t> zbirBrojeva(0);
    std::vector<std::future<size_t>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto izracunaj = [&zbirBrojeva](size_t pocetak, size_t kraj) -> size_t {
            size_t proizvod = 1;

            for (size_t j = pocetak; j <= kraj; j++) {
                proizvod *= j;
                zbirBrojeva.fetch_add(j);
            }

            return proizvod;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, izracunaj, pocetak, kraj));
        pocetak = kraj + 1;
    }

    std::vector<size_t> parcijalniProizvodi;
    size_t ukupanFaktorijel = 1;

    // Peta nit - ispis u obrnutom redosledu
    auto nitZaIspis = std::async(std::launch::async, [&rezultati, &parcijalniProizvodi]() {
        for (size_t i = 1; i <= 4; i++) {
            size_t val = rezultati.at(4 - i).get();
            std::cout << "Parcijalni proizvod " << (4 - i + 1) << ". dela: " << val << std::endl;
            parcijalniProizvodi.emplace_back(val);
        }
    });

    std::cout << "\n--- Parcijalni proizvodi (obrnuti redosled) ---" << std::endl;
    nitZaIspis.get();

    for (auto& p : parcijalniProizvodi)
        ukupanFaktorijel *= p;

    std::cout << "\nUkupan faktorijel broja " << N << ": " << ukupanFaktorijel << std::endl;
    std::cout << "Zbir svih brojeva od 1 do " << N << ": " << zbirBrojeva.load() << std::endl;

    return 0;
}
