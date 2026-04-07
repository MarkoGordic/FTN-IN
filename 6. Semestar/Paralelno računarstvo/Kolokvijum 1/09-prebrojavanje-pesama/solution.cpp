#include <iostream>
#include <vector>
#include <future>
#include <atomic>

int main() {
    size_t n;

    do {
        std::cout << "Unesite broj pesama: ";
        std::cin >> n;
    } while (n <= 4);

    std::vector<int> trajanja(n);
    std::cout << "Unesite trajanja (u sekundama): ";
    for (size_t i = 0; i < n; i++)
        std::cin >> trajanja[i];

    std::atomic<int> ukupnoTrajanje(0);

    const size_t brojNiti = 4;
    const size_t blok = n / brojNiti;
    size_t ostatak = n % brojNiti;
    size_t pocetak = 0, kraj;

    std::vector<std::future<int>> rezultati;

    for (size_t i = 0; i < brojNiti; i++) {
        auto prebroj = [&trajanja, &ukupnoTrajanje](size_t pocetak, size_t kraj) -> int {
            int dugih = 0;

            for (size_t j = pocetak; j <= kraj; j++) {
                if (trajanja[j] > 240)
                    dugih++;
                ukupnoTrajanje.fetch_add(trajanja[j]);
            }

            return dugih;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        rezultati.emplace_back(std::async(std::launch::async, prebroj, pocetak, kraj));
        pocetak = kraj + 1;
    }

    int ukupnoDugih = 0;
    for (auto& f : rezultati)
        ukupnoDugih += f.get();

    int sekunde = ukupnoTrajanje.load();
    std::cout << "\n--- Rezultati ---" << std::endl;
    std::cout << "Broj pesama duzih od 4 minuta: " << ukupnoDugih << std::endl;
    std::cout << "Ukupno trajanje: " << sekunde / 60 << " min " << sekunde % 60 << " sek" << std::endl;

    return 0;
}
