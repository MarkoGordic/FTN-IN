#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t brojOcitavanja;

    do {
        std::cout << "Unesite broj ocitavanja: ";
        std::cin >> brojOcitavanja;
    } while (brojOcitavanja < 4);

    std::vector<int> ocitavanja(brojOcitavanja);
    std::cout << "Unesite ocitavanja: ";
    for (size_t i = 0; i < brojOcitavanja; i++)
        std::cin >> ocitavanja[i];

    std::atomic<int> brojParnih(0);

    const size_t brojNiti = 4;
    const size_t blok = brojOcitavanja / brojNiti;
    size_t ostatak = brojOcitavanja % brojNiti;
    size_t pocetak = 0, kraj;

    std::vector<std::future<int>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto nadjiMax = [&ocitavanja, &brojParnih](size_t pocetak, size_t kraj) -> int {
            int maksimum = ocitavanja[pocetak];

            for (size_t j = pocetak; j <= kraj; j++) {
                if (ocitavanja[j] > maksimum)
                    maksimum = ocitavanja[j];
                if (ocitavanja[j] % 2 == 0)
                    brojParnih.fetch_add(1);
            }

            return maksimum;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, nadjiMax, pocetak, kraj));
        pocetak = kraj + 1;
    }

    // Peta nit - ispis u obrnutom redosledu
    auto nitZaIspis = std::async(std::launch::async, [&rezultati]() {
        std::vector<int> maksimumi;
        for (size_t i = 1; i <= 4; i++) {
            int val = rezultati.at(4 - i).get();
            std::cout << "Cetvrtina " << (4 - i + 1) << ": " << val << std::endl;
            maksimumi.emplace_back(val);
        }
    });

    std::cout << "\n--- Lokalni maksimumi (obrnuti redosled) ---" << std::endl;
    nitZaIspis.get();

    std::cout << "\nUkupan broj parnih ocitavanja: " << brojParnih.load() << std::endl;

    return 0;
}
