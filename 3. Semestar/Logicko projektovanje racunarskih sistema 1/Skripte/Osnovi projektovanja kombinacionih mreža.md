# Osnovi projektovanja kombinacionih mreža

## Matematički aparat i osnovne definicije

### Bulova algebra
**Bulova algebra** je matematički sistem koji koristi logičke operacije na vrednostima iz skupa \( S \). Razlikuju se dva osnovna pristupa:

1. **Bulova algebra (matematički)**: Sistem definisan nad skupom \( S \), sa dve binarne operacije (operacije koje koriste dva argumenta) definisane nad elementima tog skupa.

2. **Bulova algebra (inžinjerski)**: Sistemi korišćeni u elektronici, gde skup \( S \) čini samo dve vrednosti: \( \{0, 1\} \). Nad ovim vrednostima se definišu operacije:
   - **Negacija (NOT)** - Obeležava se sa “-” i invertuje vrednost (0 postaje 1 i obrnuto).
   - **Disjunkcija (OR)** - Obeležava se sa “∨”, vraća 1 ako je barem jedan operand 1.
   - **Konjukcija (AND)** - Obeležava se sa “∧”, vraća 1 samo ako su oba operanda 1.

#### Primer operacija:
| Operacija | Definicija         | Primer    |
|-----------|---------------------|-----------|
| Disjunkcija (OR) | Vraća 1 ako je bilo koja vrednost 1 | \( 0 ∨ 1 = 1 \), \( 1 ∨ 1 = 1 \), \( 0 ∨ 0 = 0 \) |
| Negacija (NOT)   | Inverzuje vrednost              | \( -0 = 1 \), \( -1 = 0 \) |
| Konjukcija (AND) | Vraća 1 samo ako su obe vrednosti 1 | \( 1 ∧ 1 = 1 \), \( 0 ∧ 1 = 0 \) |

## Bulove (prekidačke) funkcije

### Definicija
**Bulova funkcija** je funkcija koja mapira vrednosti iz skupa \( B^n \) u \( B \), gde je \( B = \{0,1\} \). Na primer, za funkciju sa tri promenljive, postoji 8 mogućih kombinacija ulaznih vrednosti.

- **Slog**: Kombinacija vrednosti promenljivih za određeni unos (npr. \( (x_1, x_2, x_3) \) = (1, 0, 1)).
- **Indeks sloga**: Numerička vrednost dodeljena slogu na osnovu položaja i težine njegovih vrednosti.

---

## Broj bulovih funkcija

Broj svih mogućih kombinacija i funkcija raste eksponencijalno s obzirom na broj promenljivih \( n \). Za svaku kombinaciju \( n \)-promenljivih, postoji \( 2^{2^n} \) mogućih funkcija.

| Broj promenljivih \( n \) | Broj mogućih funkcija \( NBF \) |
|---------------------------|----------------------------------|
| 0                         | 2                                |
| 1                         | 4                                |
| 2                         | 16                               |
| 3                         | 256                              |
| 4                         | 65,536                           |
| 5                         | 4,294,967,296                    |

Ova eksponencijalna progresija pokazuje koliko se broj funkcija brzo povećava čak i sa malim povećanjem broja promenljivih.

## Zadavanje bulovih funkcija

Bulove funkcije se često predstavljaju putem **tablica istinitosti**, koje prikazuju sve moguće kombinacije ulaza i njihove odgovarajuće izlaze.

- **Indeksiranje slogova**: Slogovi se često označavaju prema vrednosti funkcije:
  - \( f_1 \): Slogovi gde funkcija ima vrednost 1.
  - \( f_0 \): Slogovi gde funkcija ima vrednost 0.
  - \( f_X \): Slogovi gde funkcija nije definisana ili ima "don't care" vrednosti.

### Primer tablice istinitosti za funkciju sa dva ulaza:
| \( i \) | \( x_1 \) | \( x_2 \) | \( f(i) \) |
|---------|-----------|-----------|------------|
| 0       | 0         | 0         | \( f(0) \) |
| 1       | 0         | 1         | \( f(1) \) |
| 2       | 1         | 0         | \( f(2) \) |
| 3       | 1         | 1         | \( f(3) \) |

## Karakteristične bulove funkcije

Bulove funkcije s malim brojem promenljivih se koriste kao osnovne gradivne jedinice za složenije logičke operacije.

| \( i \) | \( x \) | \( f(i) \) | Naziv funkcije |
|---------|---------|------------|----------------|
| 0       | 0       | 0          | Konstanta nula |
| 1       | 0       | 1          | Promenljiva \( x \) |
| 2       | 1       | 0          | Negacija \( x \) |
| 3       | 1       | 1          | Konstanta jedinica |

## Konstituente jedinice i nule

- **Konstituenta jedinice**: Funkcija koja ima vrednost jedan samo za određeni slog argumenta (takođe poznato kao "minterm").
- **Konstituenta nule**: Funkcija koja ima vrednost nula samo za određeni slog argumenta (takođe poznato kao "maxterm").

Ovi koncepti su ključni za predstavljanje funkcija u obliku disjunktivnih i konjuktivnih normalnih formi.

## Implikante i implicente

- **Implikanta**: Funkcija koja dobija vrednost nula gde god i funkcija \( f \) dobija nulu.
- **Implicenta**: Funkcija koja dobija vrednost jedan gde god funkcija \( f \) dobija jedan.

### Proste implikante i implicente
- **Prosta implikanta**: Najmanji elementarni proizvod promenljivih koji može predstavljati implikantu funkcije.
- **Prosta implicenta**: Najmanja elementarna suma promenljivih koja može predstavljati implicentu funkcije.

## Složene bulove funkcije

Složene bulove funkcije se grade kombinacijom osnovnih operacija nad elementarnim funkcijama, kao što su AND, OR, i NOT.

- **Funkcionalno potpuni sistem**: Sistem funkcija iz kojeg se može dobiti bilo koja druga bulova funkcija kroz kombinaciju operacija. Na primer, AND, OR i NOT funkcije čine funkcionalno potpuni sistem.

## Proizvod i suma

- **Elementarni proizvod (konjukcija)**: AND operacija između promenljivih.
- **Elementarna suma (disjunkcija)**: OR operacija između promenljivih.
- **Potpuni proizvod**: AND operacija koja uključuje sve promenljive (naziva se i minterm).
- **Potpuna suma**: OR operacija koja uključuje sve promenljive (naziva se i maxterm).

Ovi izrazi čine osnovu za disjunktivne i konjuktivne normalne forme.

## Savršene normalne forme

- **Savršena Disjunktivna Normalna Forma (SDNF)**: Predstavlja funkciju kao sumu minterma (sloga gde je izlaz 1).
- **Savršena Konjuktivna Normalna Forma (SKNF)**: Predstavlja funkciju kao proizvod maxterma (sloga gde je izlaz 0).

Savršene normalne forme omogućavaju jedinstvenu reprezentaciju bulovih funkcija i njihovu lakšu analizu i implementaciju u digitalnim kolima.