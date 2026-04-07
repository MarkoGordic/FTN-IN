#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <atomic>
#include <map>
#include <algorithm>

struct Narudzbina {
    std::string ime;
    std::string grad;
    int iznos;
};

int main() {
    size_t brojNarudzbina;
    std::cout << "Unesite broj narudzbina: ";
    std::cin >> brojNarudzbina;

    std::vector<Narudzbina> narudzbine(brojNarudzbina);
    for (size_t i = 0; i < brojNarudzbina; i++) {
        std::cout << (i + 1) << ". Ime: ";
        std::cin >> narudzbine[i].ime;
        std::cout << "   Grad: ";
        std::cin >> narudzbine[i].grad;
        std::cout << "   Iznos: ";
        std::cin >> narudzbine[i].iznos;
    }

    std::promise<Narudzbina> obecanjeNajskuplje;
    auto buducnostNajskuplje = obecanjeNajskuplje.get_future();

    std::map<std::string, int> iznosiPoGradu;
    std::mutex mutexGradova;
    std::atomic<int> sumaIznosa(0);

    // Nit 1: najskuplja narudzbina
    auto nitNajskuplja = std::async(std::launch::async,
        [&narudzbine, &obecanjeNajskuplje]() {
            auto it = std::max_element(narudzbine.begin(), narudzbine.end(),
                [](const Narudzbina& a, const Narudzbina& b) {
                    return a.iznos < b.iznos;
                });
            obecanjeNajskuplje.set_value(*it);
        });

    // Nit 2: grupisanje po gradu
    auto nitGrupisi = std::async(std::launch::async,
        [&narudzbine, &iznosiPoGradu, &mutexGradova]() {
            for (auto& n : narudzbine) {
                std::lock_guard<std::mutex> zakljucaj(mutexGradova);
                iznosiPoGradu[n.grad] += n.iznos;
            }
        });

    // Nit 3: suma iznosa
    auto nitSuma = std::async(std::launch::async,
        [&narudzbine, &sumaIznosa]() {
            for (auto& n : narudzbine)
                sumaIznosa.fetch_add(n.iznos);
        });

    nitNajskuplja.get();
    nitGrupisi.get();
    nitSuma.get();

    Narudzbina najskuplja = buducnostNajskuplje.get();

    std::vector<std::pair<int, std::string>> sortiraniGradovi;
    for (auto& [grad, iznos] : iznosiPoGradu)
        sortiraniGradovi.emplace_back(iznos, grad);

    std::sort(sortiraniGradovi.rbegin(), sortiraniGradovi.rend());

    std::cout << "\n--- Izvestaj ---" << std::endl;
    std::cout << "Najskuplja narudzbina: " << najskuplja.ime
              << " (" << najskuplja.grad << ") - " << najskuplja.iznos << " din" << std::endl;

    std::cout << "Ukupno po gradu:" << std::endl;
    for (auto& [iznos, grad] : sortiraniGradovi)
        std::cout << "  " << grad << ": " << iznos << " din" << std::endl;

    std::cout << "Prosecna vrednost narudzbine: "
              << static_cast<double>(sumaIznosa.load()) / brojNarudzbina << " din" << std::endl;

    return 0;
}
