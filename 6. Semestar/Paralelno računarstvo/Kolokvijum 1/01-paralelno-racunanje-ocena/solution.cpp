#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t brojStudenata;

    do {
        std::cout << "Unesite broj studenata: ";
        std::cin >> brojStudenata;
    } while (brojStudenata < 3);

    std::vector<int> ocene(brojStudenata);
    std::cout << "Unesite ocene: ";
    for (size_t i = 0; i < brojStudenata; i++)
        std::cin >> ocene[i];

    const size_t brojNiti = 3;
    const size_t blok = brojStudenata / brojNiti;
    size_t ostatak = brojStudenata % brojNiti;
    size_t pocetak = 0, kraj;

    std::atomic<int> sumaOcena(0);
    std::vector<std::future<std::pair<int, int>>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto obradi = [&ocene, &sumaOcena](size_t pocetak, size_t kraj) -> std::pair<int, int> {
            int palih = 0, desetki = 0;

            for (size_t j = pocetak; j <= kraj; j++) {
                if (ocene[j] == 5) palih++;
                if (ocene[j] == 10) desetki++;
                sumaOcena.fetch_add(ocene[j]);
            }

            return {palih, desetki};
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, obradi, pocetak, kraj));
        pocetak = kraj + 1;
    }

    auto nitZaIspis = std::async(std::launch::async, [&rezultati, &sumaOcena, brojStudenata]() {
        int ukupnoPalih = 0, ukupnoDesetki = 0;

        for (auto& f : rezultati) {
            auto [palih, desetki] = f.get();
            ukupnoPalih += palih;
            ukupnoDesetki += desetki;
        }

        std::cout << "\n--- Rezultati obrade ---" << std::endl;
        std::cout << "Broj palih studenata: " << ukupnoPalih << std::endl;
        std::cout << "Broj studenata sa ocenom 10: " << ukupnoDesetki << std::endl;
        std::cout << "Prosecna ocena: "
                  << static_cast<double>(sumaOcena.load()) / brojStudenata << std::endl;
    });

    nitZaIspis.get();

    return 0;
}
