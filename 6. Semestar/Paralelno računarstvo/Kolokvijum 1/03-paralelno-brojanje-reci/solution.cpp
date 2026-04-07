#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

int main() {
    std::string putanja;
    std::cout << "Unesite putanju do datoteke: ";
    std::cin >> putanja;

    std::ifstream datoteka(putanja);
    if (!datoteka.is_open()) {
        std::cout << "Greska pri otvaranju datoteke." << std::endl;
        return 1;
    }

    std::vector<std::string> redovi;
    std::string red;
    while (std::getline(datoteka, red))
        redovi.emplace_back(red);
    datoteka.close();

    size_t ukupnoRedova = redovi.size();
    std::cout << "Ucitano " << ukupnoRedova << " redova, delim na 4 dela..." << std::endl;

    std::map<std::string, int> globalnaFrekvencija;
    std::mutex mutexMape;

    const size_t brojNiti = 4;
    const size_t blok = ukupnoRedova / brojNiti;
    size_t ostatak = ukupnoRedova % brojNiti;
    size_t pocetak = 0, kraj;

    std::vector<std::future<void>> niti;

    for (size_t i = 0; i < brojNiti; i++) {
        auto obradi = [&redovi, &globalnaFrekvencija, &mutexMape](size_t pocetak, size_t kraj, size_t redniBroj) {
            std::map<std::string, int> lokalnaMapa;

            for (size_t j = pocetak; j <= kraj; j++) {
                std::istringstream tok(redovi[j]);
                std::string rec;
                while (tok >> rec) {
                    std::string ociscena;
                    for (char c : rec)
                        if (std::isalpha(c))
                            ociscena += std::tolower(c);

                    if (!ociscena.empty())
                        lokalnaMapa[ociscena]++;
                }
            }

            {
                std::lock_guard<std::mutex> zakljucaj(mutexMape);
                for (auto& [rec, broj] : lokalnaMapa)
                    globalnaFrekvencija[rec] += broj;
            }

            std::cout << "Nit " << redniBroj << ": obradila redove "
                      << (pocetak + 1) << "-" << (kraj + 1) << std::endl;
        };

        kraj = pocetak + blok - 1;
        if (ostatak) {
            kraj++;
            ostatak--;
        }

        niti.emplace_back(std::async(std::launch::async, obradi, pocetak, kraj, i + 1));
        pocetak = kraj + 1;
    }

    auto nitZaIspis = std::async(std::launch::async, [&niti, &globalnaFrekvencija]() {
        for (auto& f : niti)
            f.get();

        std::vector<std::pair<int, std::string>> sortirano;
        for (auto& [rec, broj] : globalnaFrekvencija)
            sortirano.emplace_back(broj, rec);

        std::sort(sortirano.rbegin(), sortirano.rend());

        std::cout << "\n--- 5 najcescih reci ---" << std::endl;
        size_t granica = std::min((size_t)5, sortirano.size());
        for (size_t i = 0; i < granica; i++)
            std::cout << (i + 1) << ". \"" << sortirano[i].second
                      << "\" - " << sortirano[i].first << " puta" << std::endl;
    });

    nitZaIspis.get();

    return 0;
}
