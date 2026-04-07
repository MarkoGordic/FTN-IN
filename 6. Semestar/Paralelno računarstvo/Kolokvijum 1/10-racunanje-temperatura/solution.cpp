#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t n;

    do {
        std::cout << "Unesite broj dana: ";
        std::cin >> n;
    } while (n <= 4);

    std::vector<int> temperature(n);
    std::cout << "Unesite temperature: ";
    for (size_t i = 0; i < n; i++)
        std::cin >> temperature[i];

    std::atomic<int> zbirTemperatura(0);

    const size_t brojNiti = 4;
    const size_t blok = n / brojNiti;
    size_t ostatak = n % brojNiti;
    size_t pocetak = 0, kraj;

    std::vector<std::future<int>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto prebroj = [&temperature, &zbirTemperatura](size_t pocetak, size_t kraj) -> int {
            int hladnih = 0;

            for (size_t j = pocetak; j <= kraj; j++) {
                if (temperature[j] < 0)
                    hladnih++;
                zbirTemperatura.fetch_add(temperature[j]);
            }

            return hladnih;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, prebroj, pocetak, kraj));
        pocetak = kraj + 1;
    }

    int ukupnoHladnih = 0;
    for (auto& f : rezultati)
        ukupnoHladnih += f.get();

    std::cout << "\n--- Rezultati ---" << std::endl;
    std::cout << "Broj dana sa temperaturom ispod nule: " << ukupnoHladnih << std::endl;
    std::cout << "Prosecna temperatura: "
              << static_cast<double>(zbirTemperatura.load()) / n << " stepeni" << std::endl;

    return 0;
}
