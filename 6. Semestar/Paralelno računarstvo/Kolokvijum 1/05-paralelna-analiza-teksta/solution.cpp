#include <iostream>
#include <string>
#include <future>
#include <mutex>
#include <atomic>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

int main() {
    std::string tekst;
    std::cout << "Unesite tekst: ";
    std::getline(std::cin, tekst);

    std::map<char, int> frekvencijaKaraktera;
    std::mutex mutexFrekvencije;
    std::atomic<int> brojDugihReci(0);

    // Nit 1: broji samoglasnike
    auto nitSamoglasnici = std::async(std::launch::async, [&tekst]() -> int {
        int brojac = 0;
        std::string samoglasnici = "aeiouAEIOU";
        for (char c : tekst)
            if (samoglasnici.find(c) != std::string::npos)
                brojac++;
        return brojac;
    });

    // Nit 2: najduza rec
    auto nitNajduzaRec = std::async(std::launch::async, [&tekst]() -> std::string {
        std::istringstream tok(tekst);
        std::string rec, najduza;
        while (tok >> rec)
            if (rec.length() > najduza.length())
                najduza = rec;
        return najduza;
    });

    // Nit 3: frekvencija karaktera
    auto nitFrekvencija = std::async(std::launch::async,
        [&tekst, &frekvencijaKaraktera, &mutexFrekvencije]() {
            for (char c : tekst) {
                if (c != ' ') {
                    std::lock_guard<std::mutex> zakljucaj(mutexFrekvencije);
                    frekvencijaKaraktera[std::tolower(c)]++;
                }
            }
        });

    // Nit 4: reci duze od 4 karaktera
    auto nitDugeReci = std::async(std::launch::async, [&tekst, &brojDugihReci]() {
        std::istringstream tok(tekst);
        std::string rec;
        while (tok >> rec)
            if (rec.length() > 4)
                brojDugihReci.fetch_add(1);
    });

    int samoglasnika = nitSamoglasnici.get();
    std::string najduzaRec = nitNajduzaRec.get();
    nitFrekvencija.get();
    nitDugeReci.get();

    std::vector<std::pair<int, char>> sortiranaFrekvencija;
    for (auto& [karakter, broj] : frekvencijaKaraktera)
        sortiranaFrekvencija.emplace_back(broj, karakter);

    std::sort(sortiranaFrekvencija.rbegin(), sortiranaFrekvencija.rend());

    std::cout << "\n--- Analiza teksta ---" << std::endl;
    std::cout << "Broj samoglasnika: " << samoglasnika << std::endl;
    std::cout << "Najduza rec: " << najduzaRec
              << " (" << najduzaRec.length() << " karaktera)" << std::endl;

    std::cout << "Najcesci karakteri:" << std::endl;
    size_t granica = std::min((size_t)3, sortiranaFrekvencija.size());
    for (size_t i = 0; i < granica; i++)
        std::cout << "  '" << sortiranaFrekvencija[i].second
                  << "' - " << sortiranaFrekvencija[i].first << " puta" << std::endl;

    std::cout << "Broj reci duzih od 4 karaktera: " << brojDugihReci.load() << std::endl;

    return 0;
}
