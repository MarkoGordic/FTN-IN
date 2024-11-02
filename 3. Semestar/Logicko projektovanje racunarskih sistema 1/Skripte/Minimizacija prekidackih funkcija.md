# Minimizacija prekidačkih funkcija

## Uvod

- **Minimizacija Bulovih funkcija**: Osnovni zadatak u projektovanju kombinacionih mreža. Glavni cilj je smanjiti broj korišćenih logičkih kola (elementarnih operacija), bez promene izlazne funkcije mreže.
- **Inženjerski cilj**: Pronalaženje najjednostavnije funkcije smanjuje troškove, zahteva manje komponenata, i poboljšava performanse sistema. Korišćenjem funkcija s minimalnim brojem operacija, dizajn postaje efikasniji i praktičniji za implementaciju.

## Motivacija

- **Efikasnost**: U digitalnim kolima, optimizacija je neophodna zbog ograničenih resursa i visokih troškova. Manji broj komponenti znači niže troškove i povećanu pouzdanost.
- **Ušteda energije**: Manje operacija smanjuje energetsku potrošnju, što je važno u energetskom dizajnu.
- **Funkcionalno potpuni sistemi**: Minimizacija se izvodi unutar funkcionalno potpunog sistema, što znači da korišćenjem samo osnovnih operacija (najčešće konjunkcije, disjunkcije i negacije) možemo ostvariti sve logičke funkcije.

### Primer osnovnih logičkih operacija
1. **Negacija (NOT)**: Inverzija ulaznog signala (0 postaje 1, a 1 postaje 0).
2. **Konjunkcija (AND)**: Vraća "1" samo kada su svi ulazi "1"; ako je barem jedan ulaz "0", izlaz je "0".
3. **Disjunkcija (OR)**: Vraća "1" kada je barem jedan ulaz "1"; kada su svi ulazi "0", izlaz je "0".

## Primer minimizacije funkcije sa četiri promenljive

### Kako izgleda funkcija
- Funkcija \( f_1 \) je zadana skupom vrednosti na kojima funkcija dobija 1: \( f_1 = (5, 6, 9, 10, 13, 14) \). Ovo znači da funkcija treba vratiti 1 za vrednosti ulaznih promenljivih koje odgovaraju indeksima 5, 6, 9, 10, 13, i 14.
  
### Načini zapisa funkcije
1. **Dezignacija u disjunktivnoj formi (DNF)**: Reprezentacija funkcije kroz OR operacije nad mintermima (proizvodi u kojima funkcija dobija vrednost 1).
2. **Alternativne metode**: Različiti načini predstavljanja funkcije zavisno od potrebe za optimizacijom, kao i korišćenja XOR operacije ili drugih kompleksnijih operacija kada su relacije među promenljivima složenije.

## Minimizacija pomoću Karnoovih mapa (Karnaugh maps)

### Osnovne karakteristike Karnoove mape
- **Karnoova mapa** je vizuelni alat za minimizaciju Bulovih funkcija. To je dvodimenzionalna tablica koja prikazuje sve moguće vrednosti promenljivih funkcije.
- Svaka ćelija predstavlja jedan slog funkcije, a broj ćelija je jednak broju mogućih kombinacija vrednosti ulaza (npr., funkcija sa četiri promenljive ima 16 ćelija).
- **Unos vrednosti 1**: Ćelije u koje se upisuje vrednost 1 označavaju kombinacije za koje funkcija dobija vrednost 1, dok se ćelije sa 0 obično ostavljaju prazne.

### Grupisanje ćelija pomoću logičkih suseda
- **Logički susedi** su ćelije koje se razlikuju samo u jednoj promenljivoj. Susedi omogućavaju grupisanje susednih ćelija u Karnoovoj mapi, što rezultira pojednostavljenim izrazima.
- **Gray kod** se koristi u Karnoovim mapama jer omogućava da se susedne ćelije razlikuju samo po jednoj promenljivoj, što olakšava grupisanje.

### Primer minimizacije pomoću Karnoove mape
- Na primer, za funkciju \( f_1 = (5, 6, 9, 10, 13, 14) \):
  - Unosimo vrednosti 1 u ćelije koje odgovaraju indeksima 5, 6, 9, 10, 13, i 14.
  - Grupisanje ćelija u što veće blokove (npr. parovi, četvorke) omogućava eliminisanje redundantnih promenljivih, čime se minimizira izraz.
  - Rezultat je **minimalna disjunktivna normalna forma (DNF)**, koja koristi minimalan broj proizvoda.

## Analitički metod minimizacije Bulovih funkcija (Quine-McCluskey metod)

1. **Quine-McCluskey metod** je sistematičan, matematički pristup za minimizaciju Bulovih funkcija. To je formalna metoda koja garantuje jedinstveno minimalno rešenje.
2. **Koraci metode**:
   - **Pronalaženje kompletnog skupa prostih implikanti**: Prosti implikanti su najjednostavniji oblici izraza funkcije koji sadrže sve informacije neophodne za definisanje funkcije.
   - **Odabir minimalnog skupa prostih implikanti**: Odabir onih implikanti koji omogućavaju minimalnu disjunktivnu normalnu formu (DNF) funkcije.

### Proces minimizacije - Primer funkcije
- Funkcija \( f_1(X_1, X_2, X_3, X_4) = (0, 3, 5, 7, 11, 13, 15) \).
  - **Prvi prolaz kroz tabelu**: Grupisanje svih slogova sa vrednošću 1 prema broju promenljivih koje su jednako 1.
  - **Dalje objedinjavanje**: Grupisanje se nastavlja sve dok se ne dobije minimalna količina izraza, čime se ostvaruje konačna minimalna forma funkcije.

## Gray kod

### Osnovne karakteristike Gray koda
- **Gray kod** je specifična binarna numeracija u kojoj se dva uzastopna broja razlikuju samo u jednoj binarnoj cifri. To znači da se samo jedan bit menja pri prelasku s jedne vrednosti na sledeću, što minimizira greške.
- Gray kod je pogodan za primenu u uređajima kao što su enkoderi i brojači gde je potrebno osigurati tačan prelaz između stanja.
- **Nije težinski kod**: Nema numeričke težine u binarnim ciframa.

### Gray kod - Tabela
| Binarni kod | Gray kod | Razlika u bitovima |
|-------------|----------|--------------------|
| 0000        | 0000     | 0                  |
| 0001        | 0001     | 1                  |
| 0010        | 0011     | 1                  |
| 0011        | 0010     | 1                  |
| 0100        | 0110     | 1                  |
| ...         | ...      | ...                |

### Primena Gray koda u minimizaciji
- Gray kod olakšava identifikovanje susednih ćelija u Karnoovim mapama, jer omogućava vizuelno prepoznavanje ćelija koje se razlikuju u samo jednoj promenljivoj.
- Korišćenje Gray koda olakšava grupisanje i pojednostavljivanje izraza, smanjujući broj potrebnih operacija.

## Završni izrazi minimizacije

1. **Minimalna disjunktivna normalna forma (MDNF)**: Predstavlja sumu minimalnih proizvoda. To je izraz sa najmanjim brojem OR operacija među konjukcijama, gde svaki proizvod pokriva minimum slogova sa vrednošću 1.
2. **Minimalna konjuktivna normalna forma (MKNF)**: Predstavlja proizvod minimalnih suma. MKNF koristi najmanji broj AND operacija među disjunkcijama, gde svaka suma pokriva minimum slogova sa vrednošću 0.
3. **XOR operacija**: Koristi se u slučajevima gde su relacije među promenljivima složenije. XOR funkcija vraća 1 kada su ulazi različiti i koristi se u posebnim situacijama kada jednostavne operacije AND i OR ne mogu u potpunosti minimizovati funkciju.

## Zaključak

- **Efikasnost** minimizacije smanjuje kompleksnost logičkih kola i omogućava jednostavniji dizajn.
- **Karnoove mape** i **Quine-McCluskey metod** predstavljaju ključne tehnike za sistematsku minimizaciju funkcija.
- **Gray kod** doprinosi vizuelnoj identifikaciji susednih ćelija i pomaže u grupisanju tokom minimizacije.
- **Minimalne forme (MDNF i MKNF)** obezbeđuju da logički izraz koristi najmanji mogući broj operacija, što poboljšava performanse i smanjuje resurse potrebne za implementaciju u digitalnim sistemima.