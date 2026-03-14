# ER Model - Integritetna komponenta

## Uvod: Zašto nam trebaju ograničenja?

Zamislimo da pravimo bazu podataka za jedan fakultet. Definisali smo tipove entiteta (Student, Nastavnik, Predmet), njihova obeležja i tipove poveznika između njih. Sjajno - imamo strukturu! Ali šta ako neko pokuša da upiše studenta sa ocenom 15? Ili da radniku dodeli matični broj koji već postoji? Ili da obriše katedru na kojoj još postoje nastavnici?

Struktura sama po sebi nije dovoljna. Potrebna su nam **pravila** koja čuvaju smisao i ispravnost podataka u bazi. Tu na scenu stupa **integritetna komponenta** ER modela podataka.

ER model entiteta i poveznika je prevashodno namenjen za predstavljanje konceptualne šeme i pruža relativno dobre mogućnosti za definisanje ograničenja. Ta ograničenja se u modelu izražavaju, uglavnom, eksplicitno. Hajde da prođemo kroz svako od njih.

> [!IMPORTANT]
> Integritetna komponenta ER modela obuhvata sledeće tipove ograničenja:
> 1. **Ograničenje domena**
> 2. **Ograničenje vrednosti obeležja**
> 3. **Ograničenje pojave tipa**
> 4. **Kardinalitet tipa poveznika**
> 5. **Ograničenje ključa (integritet tipa)** - za tip entiteta i tip poveznika

Svako od ovih ograničenja pokriva drugi aspekt podataka - od najnižeg nivoa (koje vrednosti smeju da postoje) do najvišeg (kako su entiteti međusobno povezani). Idemo redom.

---

## 1. Ograničenje domena (Integritet domena)

### Šta je integritet domena i zašto je bitan?

**Integritet domena** predstavlja ograničenje koje je svojstveno praktično svim modelima podataka. To je najosnovniji nivo zaštite - kontroliše koje vrednosti uopšte mogu da postoje u bazi.

U opštem slučaju, integritet ili ograničenje domena je trojka:

$$(\text{Tip podatka}, \text{Dužina podatka}, \text{Uslov})$$

- **Tip podatka** definiše vrstu znakova putem kojih se izražava vrednost obeležja. Ovo je jedina obavezna komponenta.
- **Dužina podatka** izražava putem maksimalnog broja znakova koji mogu biti upotrebljeni za izražavanje vrednosti obeležja. Tip i dužina podatka ograničavaju vrednosti obeležja na tip i broj znakova.
- **Uslov** - treća, opciona komponenta ograničenja domena. Može biti regularni izraz ili funkcija.

Zamislimo to ovako: ako kažemo da je neko obeležje tipa INTEGER sa dužinom 2, to znači da može primiti samo celobrojne vrednosti sa najviše dve cifre. Domen definiše "kutiju" u koju stavljamo vrednosti, a ta kutija ima jasno definisan oblik i veličinu.

### Specifikacija domena - formalna struktura

Domen se formalno specificira kao:

$$D(\text{id}(D), \text{Predef})$$

gde je:
- $D$ - naziv domena
- $\text{id}(D)$ - ograničenje domena
- $\text{Predef}$ - predefinisana (podrazumevana) vrednost domena

Ograničenje domena $\text{id}(D)$ definiše se primenom pravila za specificiranje korisnički definisanog domena. Postoje razna pravila (pravilo nasleđivanja, pravilo tipa sloga, pravilo tipa skupa, pravilo tipa izbora), ali mi ćemo se fokusirati na **pravilo nasleđivanja**, jer se ono najčešće koristi.

### Pravilo nasleđivanja

Kod pravila nasleđivanja, ograničenje "nasleđenog" domena ima strukturu:

$$\text{id}(D) = (\text{Tip}, \text{Dužina}, \text{Uslov})$$

- **Tip** - tip podatka, tj. oznaka primitivnog domena ili oznaka prethodno korisnički definisanog domena. Ovo je jedina obavezna komponenta specifikacije. Nasleđuju se sva ograničenja, relacije i operacije definisane nad izabranim tipom.
- **Dužina** - navodi se samo za tipove podataka (primitivne domene) koji to zahtevaju.
- **Uslov** - logički uslov koji svaka vrednost domena mora da zadovolji. U ER modelu mora biti definisana sintaksa za zadavanje logičkih uslova.
- **Predef** - predefinisana vrednost. Mora da zadovolji ograničenja tipa, dužine i uslova.

### Standardni tipovi podataka (Primer 2.19)

Jedno standardno ograničenje domena može predstavljati sledeći skup tipova podataka sa dužinama:

| Tip podatka | Značenje dužine |
|---|---|
| **INTEGER** (broj cifara) | Celobrojne vrednosti sa zadatim brojem cifara |
| **REAL** (broj cifara ispred zareza, broj cifara iza zareza) | Realne vrednosti sa zadatom preciznošću |
| **CHARACTER** (broj znakova) | Znakovne vrednosti sa zadatom dužinom |
| **LOGICAL** | Logička promenljiva iz skupa $\{T, \bot\}$ |
| **DATE** | Datumska vrednost |

Pogledajmo kako to izgleda na konkretnim primerima.

**Primer:** Domen obeležja OCE (ocena)

Pridruživanje $\text{dom}(OCE)$ standardnog ograničenja $INTEGER(2)$ ukazuje da važi:

$$\text{dom}(OCE) = \{0, 1, \ldots, 99\}$$

Dakle, sa tipom INTEGER i dužinom 2 cifre, obeležje OCE može da primi bilo koji ceo broj od 0 do 99.

**Primer:** Domen obeležja IME

Pridruživanje $\text{dom}(IME)$ standardnog ograničenja $CHARACTER(10)$ ukazuje da $\text{dom}(IME)$ može pripadati bilo koji niz od 10 znakova.

**Primer iz prezentacije:**

| Domen | Specifikacija |
|---|---|
| DPREZIME | $((String, 30, -), -)$ |
| DDATUM | $((Date, -, d \geq '01.01.1900'), -)$ |
| DOCENA | $((Number, 2, d \geq 5 \land d \leq 10), -)$ |
| DPOZOCENA | $((DOCENA, -, d \geq 6), 6)$ |

Obratimo pažnju na DPOZOCENA - ovaj domen **nasleđuje** domen DOCENA (koji je korisnički definisan), ali dodaje novi uslov ($d \geq 6$) i postavlja podrazumevanu vrednost na 6. To je pravilo nasleđivanja na delu!

### Regularni izrazi kao uslov domena

Standardna ograničenja domena često nisu dovoljno precizna. Zato se uvodi i uslov, kao treća, opciona komponenta ograničenja domena. Uslov može biti **regularni izraz** ili **funkcija**.

Postoje **prosti** i **složeni** regularni izrazi.

#### Prosti regularni izrazi

Prosti regularni izrazi se definišu s obzirom na neke konstante. Neka je $k$ konstanta iz domena pridruženog obeležju $A$, a $\theta$ operator poređenja iz skupa $\{<, >, \leq, \geq, \neq, =\}$. Tada proste regularne izraze predstavljaju:

- $(\theta k)$ - Izraz $(\theta k)$ ukazuje da sve vrednosti pridružene obeležju $A$ moraju biti u relaciji $\theta$ sa konstantom $k$.
- $(k_1, k_2, \ldots, k_n)$ - Izraz $(k_1, k_2, \ldots, k_n)$ ukazuje da obeležje $A$ sme uzimati vrednosti iz skupa $\{k_1, k_2, \ldots, k_n\}$.

**Primer 2.20:** Pridruživanje $\text{dom}(OCE)$ sledeće trojke sa prostim regularnim izrazom $(INTEGER, (2), <11)$ ukazuje da obeležje OCE može uzeti vrednost iz skupa $\{0, 1, \ldots, 10\}$.

Pridruživanje $\text{dom}(OCE)$ trojke sa prostim regularnim izrazom $(INTEGER, (2), (6, 7, \ldots, 10))$ ograničava vrednosti tog obeležja na uobičajeni opseg pozitivnih ocena.

Do istog rezultata se dolazi i pridruživanjem $\text{dom}(OCE)$ sledeće trojke sa **složenim** regularnim izrazom: $(INTEGER, (2), > 5 \land < 11)$.

#### Složeni regularni izrazi

Složeni regularni izrazi se komponuju od drugih regularnih izraza (prostih ili složenih) njihovim povezivanjem putem logičkih operatora $\land$ (i), $\lor$ (ili) i $\neg$ (ne).

### Funkcije kao ograničenje domena

Za izražavanje ograničenja nad domenima nekih obeležja nisu dovoljni ni regularni izrazi. Tada se koriste funkcije, čije argumente predstavljaju neka obeležja, ili se koriste algoritmi.

**Primer 2.21:** Posmatraju se obeležja $KOL$ (količina artikla), $JED\_CEN$ (jedinična cena artikla) i $IZNOS$. Ograničenje da $\text{dom}(IZNOS)$ sme sadržati samo vrednosti dobijene množenjem elemenata $\text{dom}(KOL)$ sa elementima iz $\text{dom}(JED\_CEN)$, može se izraziti putem funkcije:

$$iznos = kol \times jed\_cen$$

**Primer 2.21 (nastavak):** Posmatraju se obeležja $REGIJA$ i $PTT\_BROJ$. Ograničenje da u regiji "Vojvodina" svi poštanski brojevi počinju cifrom 2, može se izraziti putem sledećeg algoritma:

```
AKO JE REGIJA = "Vojvodina" TADA
    PTT_BROJ = "2*"
INAČE
KRAJ AKO.
```

Pri tome, znak `*` predstavlja zamenu za niz bilo kojih znakova.

> [!TIP]
> Na ispitu se često traži da objasnite razliku između prostih i složenih regularnih izraza. Zapamtite: prosti koriste jedan operator poređenja ili nabrajaju konkretne vrednosti, dok složeni kombinuju više izraza pomoću logičkih operatora ($\land$, $\lor$, $\neg$).

---

## 2. Nula vrednost

Pre nego što pređemo na ograničenje vrednosti obeležja, moramo se upoznati sa jednim specifičnim konceptom - **nula vrednošću**.

**Nula vrednost** predstavlja specijalno ograničenje domena. Putem tog ograničenja se specificira da li obeležje može imati nedefinisanu vrednost. Sama nula vrednost ima najčešće jedno od sledeća dva značenja:

1. **Postojeća, ali nepoznata vrednost** - vrednost postoji u realnom svetu, ali nam nije poznata u trenutku unosa.
2. **Neprimereno svojstvo** - obeležje nema smisla za dati entitet.

Bitno je naglasiti da nula vrednost ne predstavlja broj 0 niti specijalnu vrednost čije značenje se, najčešće, interpretira na jedan od navedena dva načina.

**Primer 2.22:** Posmatra se obeležje $K\_TEL$ (broj kućnog telefona). Za neke ljude obeležje predstavlja neprimereno svojstvo, jer telefon kod kuće nemaju, te se za evidentiranje njihovog broja telefona koristi nula vrednost sa odgovarajućom interpretacijom značenja. Drugi ljudi imaju telefon, ali je njegov broj, u trenutku evidentiranja, nepoznat. Tada se ponovo koristi nula vrednost, ali sada u drugom značenju.

> [!WARNING]
> Česta greška studenata: Nula vrednost NIJE nula (broj 0)! To je oznaka da vrednost **nedostaje** - bilo zato što je nepoznata, bilo zato što ne postoji za dati entitet.

---

## 3. Ograničenje vrednosti obeležja

Sada prelazimo na sledeći nivo - ograničenja koja se definišu za svako pojedinačno obeležje unutar nekog tipa.

**Specifikacija obeležja** $A \in Q$ datog tipa $N$ ima strukturu:

$$(\text{id}(N, A), \text{Predef})$$

gde je:
- $\text{id}(N, A)$ - ograničenje vrednosti obeležja
- $\text{Predef}$ - predefinisana vrednost obeležja

**Ograničenje vrednosti obeležja** $\text{id}(N, A)$ definiše se za svako obeležje tipa i ima strukturu:

$$\text{id}(N, A) = (\text{Domen}, \text{Null})$$

gde je:
- **Domen** - oznaka (naziv) pridruženog domena obeležja. Obavezna komponenta.
- **Null** $\in \{T, \bot\}$ - obavezna komponenta:
  - $T$ - **dozvola** dodele nula vrednosti obeležju unutar $N$
  - $\bot$ - **zabrana** dodele nula vrednosti obeležju unutar $N$

Ako se $\text{Predef}$ navede, onda je on važeći. U protivnom, važeći je $\text{Predef}$ odgovarajućeg domena, ili prvog sledećeg nasleđenog domena za koji je $\text{Predef}$ definisan.

Interpretacija ograničenja je moguća za bilo koju vrednost obeležja.

Ovo je, praktično, spoj domena i dozvole za nula vrednost. Svako obeležje mora imati pridružen domen i mora biti jasno definisano da li sme primiti nula vrednost ili ne.

---

## 4. Ograničenje pojave tipa

Dok ograničenje vrednosti obeležja kontroliše svako obeležje pojedinačno, **ograničenje pojave tipa** ide korak dalje - definiše ograničenja na moguće vrednosti podataka **unutar iste pojave** tipa entiteta ili tipa poveznika.

Formalno, za tip $N$:

$$\text{id}(N) = (\{\text{id}(N, A) \mid A \in Q'\}, \text{Uslov})$$

gde je:
- $Q'$ - **prošireni skup obeležja** tipa:
  - Za tip entiteta: $Q' = Q$ (isti kao osnovni skup obeležja)
  - Za tip poveznika: $Q' = Q \cup K_p$, gde je $K_p$ skup obeležja primarnog ključa TP
- **Uslov** - logički uslov koji **svaka pojava tipa** mora da zadovolji. Može, u ulozi operanda, da sadrži bilo koje obeležje proširenog skupa obeležja datog tipa.

Ograničenje pojave tipa, dakle, predstavlja skup ograničenja vrednosti obeležja, kojem je pridodat logički uslov. Interpretacija ograničenja pojave tipa je moguća za bilo koju pojavu tipa nad skupom obeležja, nad kojim je definisano.

### Konkretan primer

Pogledajmo tip entiteta Radnik:

$$Radnik(\{MBR, PRZ, IME, ZAN, BPJZ\}, \{MBR\})$$

**Ograničenje vrednosti obeležja:**

| Obeležje | Domen | Null | Predef |
|---|---|---|---|
| MBR | DMBR | $\bot$ | - |
| PRZ | DPRZ | $\bot$ | - |
| IME | DIME | $\bot$ | - |
| ZAN | DZAN | $\bot$ | - |
| BPJZ | DBPJZ | $T$ | - |

**Uslov pojave tipa:**

$$ZAN = 'prg' \Rightarrow BPJZ \neq \bot$$

Ovaj uslov znači: ako je zanimanje radnika 'prg' (programer), onda broj programskog jezika (BPJZ) ne sme biti nula vrednost. To ima savršen smisao - ako je neko programer, moramo znati koji programski jezik koristi!

**Specifikacija domena:**

| Domen | Tip | Dužina | Uslov | Predef |
|---|---|---|---|---|
| DMBR | Number | 4 | $d \geq 1$ | - |
| DPRZ | String | 30 | - | - |
| DIME | String | 15 | - | - |
| DZAN | String | 3 | - | - |
| DBPJZ | Number | 2 | $d \geq 0$ | 0 |

Obratimo pažnju na to kako se ograničenja nadograđuju: domen definiše tip i opseg, ograničenje vrednosti dodaje kontrolu nula vrednosti, a ograničenje pojave tipa dodaje uslov koji povezuje više obeležja zajedno.

> [!IMPORTANT]
> Razlika između tri nivoa ograničenja:
> - **Ograničenje domena** - kontroliše koji TIP i OPSEG vrednosti postoji (npr. ceo broj od 1 do 9999)
> - **Ograničenje vrednosti obeležja** - povezuje obeležje sa domenom i definiše da li sme biti NULL
> - **Ograničenje pojave tipa** - definiše MEĐUSOBNE ZAVISNOSTI obeležja unutar iste pojave (npr. ako je X, onda mora Y)

---

## 5. Kardinalnost tipa poveznika

Sada prelazimo na jedno od najbitnijih ograničenja u ER modelu - **kardinalnost tipa poveznika**. Ovo ograničenje opisuje prirodu odnosa između entiteta povezanih klasa.

### Motivacija

Zamislimo sledeću situaciju: imamo radnike i radna mesta. Znamo da su oni u vezi (radnik je raspoređen na radno mesto). Ali koliko radnih mesta jedan radnik može imati? Da li svaki radnik mora imati radno mesto? Da li na jednom radnom mestu mora raditi bar jedan radnik? Upravo na ova pitanja odgovara kardinalnost.

### Formalna definicija

Posmatra se binarna relacija $R$ između skupova pojava dva tipa entiteta $E_1$ i $E_2$. Ova relacija se može predstaviti putem dva preslikavanja:

$$R_1 : E_1 \rightarrow \mathcal{P}(E_2) \quad \text{i} \quad R_2 : E_2 \rightarrow \mathcal{P}(E_1)$$

gde je $\mathcal{P}(E)$ partitivni skup skupa $E$ (skup svih podskupova).

- $R_1$ je uloga entiteta iz skupa $E_1$, a $R_2$ je uloga entiteta iz skupa $E_2$ u njihovoj vezi, opisanoj relacijom $R$.

Za svako od ovih preslikavanja se definiše **minimalni** i **maksimalni kardinalitet**. Pojam kardinaliteta preslikavanja se odnosi na brojnost (kardinalitet) elemenata partitivnog skupa u koji se preslikava jedan element skupa originala.

Minimalni i maksimalni kardinalitet jednog preslikavanja, recimo $R_1$, određuje se identifikacijom minimalne i maksimalne brojnosti podskupa skupa $E_2$ u koji se može preslikati neki (bilo koji) element skupa $E_1$.

**Kardinalitet preslikavanja** $R_1$ se označava sa:

$$R_1(E_1(a_2, b_2))$$

gde je $a_2$ minimalni, a $b_2$ maksimalni kardinalitet.

**Kardinalitet relacije** $R$, odnosno tipa poveznika $R$, se označava sa:

$$R(E_1(a_1, b_1) : E_2(a_2, b_2))$$

### Kardinalitet tipa poveznika - formalna definicija (prezentacija)

**Kardinalitet TP prema povezanom tipu** je par:

$$(a, b)$$

gde je:
- $a \in \{0, 1\}$ - **minimalni kardinalitet**
- $b \in \{1, N\}$, $N \geq 2$ - **maksimalni kardinalitet**

Ovaj par ograničava u koliko pojava tipa poveznika može učestvovati jedna, bilo koja pojava povezanog tipa - **minimalno** ($a$) i **maksimalno** ($b$). Definiše se za svaki povezani tip.

### Značenje parametara $a$ i $b$

Parametrima $a$ i $b$ se najčešće dodeljuju sledeće karakteristične vrednosti:

**Parametar $a$ (minimalni kardinalitet):**

- $a = 0$ - element skupa originala se može preslikati u prazan skup. To znači da pojava povezanog tipa **ne mora** učestvovati ni u jednoj pojavi tipa poveznika.
- $a = 1$ - element skupa originala se preslikava u neprazan podskup. To znači da pojava povezanog tipa **mora** učestvovati u bar jednoj pojavi tipa poveznika.

**Parametar $b$ (maksimalni kardinalitet):**

- $b = 1$ - slika svakog originala nije veća od 1. Pojava se može povezati sa **najviše jednom** pojavom drugog tipa.
- $b = N$ (ili $M$), gde je $1 < N, M \leq |E|$ - pojava se može povezati sa **više** pojava drugog tipa.

### Totalno i parcijalno preslikavanje

Ove vrednosti parametara definišu dva važna koncepta:

**Totalno preslikavanje** ($a = 1$): Ako je $a_2 = 1$, odgovarajuće preslikavanje se naziva **totalnim**, jer svaki original preslikava u neprazan podskup. Drugim rečima, u realnom sistemu svaki entitet prve klase entiteta je sa barem jednim entitetom druge klase povezan.

Slučaj $a_2 = 1$ se naziva **egzistencijalnim ograničenjem**, jer se može tumačiti i na sledeći način: da bi $e_1$ pripadao $E_1$, mora biti povezan sa barem jednim $e_2$ iz $E_2$.

**Parcijalno preslikavanje** ($a = 0$): Preslikavanje $R_1$ je **parcijalno**, ako je $a_2 = 0$. Drugim rečima, u realnom sistemu može postojati bar jedan entitet klase $E_1$ koji nije povezan ni sa jednim entitetom klase $E_2$, tada je $a_2 = 0$.

### Prethođenje i sleđenje

Minimalnom kardinalitetu $a = 1$ se može dati i semantička interpretacija da on ukazuje na **prethođenje i sleđenje**. Naime, ako je $R_1(E_2(1, b_2))$, to ukazuje da prvo mora postojati neki entitet $e_2$ u $E_2$, da bi entitet $e_1$, koji je sa njim u vezi, mogao biti uključen u skup $E_1$. Znači, ako je $a_2 = 1$, postojanje entiteta $e_2$ iz skupa $E_2$ mora prethoditi nastanku entiteta $e_1$ iz $E_1$.

> [!TIP]
> Razmišljajte o minimalnom kardinalitetu ovako:
> - $a = 0$ → "može, ali ne mora" biti u vezi
> - $a = 1$ → "mora" biti u vezi (egzistencijalno ograničenje)
>
> A o maksimalnom:
> - $b = 1$ → "sa najviše jednim"
> - $b = N$ → "sa više"

### Tri opšte grupe maksimalnih kardinaliteta

S obzirom na maksimalne vrednosti kardinaliteta, tipovi poveznika se mogu podeliti u tri grupe:

#### Grupa M:N (više prema više)

Najopštiji slučaj. Jedan entitet klase $E_1$ može biti u vezi sa $M$ ($>1$) entiteta klase $E_2$ i obratno.

**Primer:** Radnik Radi na Projektu sa kardinalitetom $(0, M) : (0, N)$

- Radnik može raditi na više projekata (ili ni na jednom)
- Na projektu može raditi više radnika (ili nijedan)

Vrednosti minimalnih kardinaliteta definišu tri slučaja ovog odnosa:

1. **Slučaj $a_1 = 0$ i $a_2 = 0$** - minimalni kardinaliteti ukazuju da u obe klase mogu postojati entiteti koji nisu povezani sa bilo kojim entitetom druge klase. Međutim, i slučaj kada su svi entiteti posmatranih klasa međusobno povezani, nije zabranjen.

2. **Slučaj $a_1 = 1$ i $a_2 = 0$ (ili $a_1 = 0$ i $a_2 = 1$)** - minimalni kardinaliteti ukazuju da svi entiteti jedne od povezanih klasa (recimo klase $E_1$) moraju biti povezani sa bar jednim entitetom druge klase (klase $E_2$). To dalje znači da je egzistencija entiteta u jednoj klasi ($E_1$) uslovljena njihovom povezanošću sa entitetima u drugoj klasi ($E_2$).

3. **Slučaj $a_1 = 1$ i $a_2 = 1$** - minimalni kardinaliteti ukazuju da svaki entitet jedne klase mora biti povezan sa bar jednim entitetom druge klase. Egzistencija entiteta u obe klase uslovljena je njihovom povezanošću sa bar jednim entitetom druge klase, što predstavlja izuzetno strogo ograničenje.

**Konkretni primeri iz materijala:**

| Kardinalitet | Semantika |
|---|---|
| $(0,M) : (0,N)$ | Radnik može raditi na 0 ili više projekata; projekat može imati 0 ili više radnika |
| $(1,M) : (0,N)$ | Radnik mora raditi na bar 1 projektu; projekat može imati 0 ili više radnika |
| $(1,M) : (1,N)$ | Radnik mora raditi na bar 1 projektu; projekat mora imati bar 1 radnika |

#### Grupa N:1 (više prema jedan)

Jedan entitet klase $E_1$ može biti u vezi sa **najviše jednim** entitetom klase $E_2$, ali jedan entitet klase $E_2$ može biti u vezi sa **više** entiteta klase $E_1$.

**Primer:** Radnik Raspoređen na Radno_Mesto

| Kardinalitet | Semantika |
|---|---|
| $(0,1) : (0,N)$ | Radnik može biti raspoređen na 0 ili 1 radno mesto; na radnom mestu može biti 0 ili više radnika |
| $(1,1) : (0,N)$ | Radnik mora biti raspoređen na tačno 1 radno mesto; na radnom mestu može biti 0 ili više radnika |
| $(0,1) : (1,N)$ | Radnik može biti raspoređen na 0 ili 1 radno mesto; na radnom mestu mora biti bar 1 radnik |
| $(1,1) : (1,N)$ | Radnik mora biti raspoređen na tačno 1 radno mesto; na radnom mestu mora biti bar 1 radnik |

> [!NOTE]
> Primer 2.23 iz materijala: U slučaju modela sa slike gde su Radnik i Radno_Mesto povezani tipom poveznika Raspoređen, može se zahtevati da:
> - jedan radnik može biti raspoređen na najviše jedno radno mesto,
> - na jedno radno mesto može biti raspoređeno više radnika i
> - na jedno radno mesto ne mora biti raspoređen nijedan radnik.

#### Grupa 1:1 (jedan prema jedan)

Jedan entitet klase $E_1$ može biti u vezi sa **najviše jednim** entitetom klase $E_2$ i obratno.

**Primer:** Radnik Ima PolisaOsiguranja

| Kardinalitet | Semantika |
|---|---|
| $(0,1) : (0,1)$ | Radnik može imati 0 ili 1 polisu; polisa može pripadati 0 ili 1 radniku |
| $(1,1) : (0,1)$ | Radnik mora imati tačno 1 polisu; polisa može pripadati 0 ili 1 radniku |
| $(1,1) : (1,1)$ | Radnik mora imati tačno 1 polisu; polisa mora pripadati tačno 1 radniku |

---

## 6. Predstavljanje kardinaliteta u ER dijagramima

U dijagramima entiteta i poveznika kardinalitet tipa poveznika se predstavlja navođenjem ili para $(a_1, b_1)$ i $(a_2, b_2)$ ili samo maksimalnih vrednosti kardinaliteta $b_1$ i $b_2$ uz grafičku predstavu odgovarajućeg tipa entiteta.

### Dva postupka navođenja kardinaliteta

Postoje dva postupka navođenja kardinaliteta u ER dijagramima.

**Prvi postupak:** Par $(a_i, b_i)$ se upisuje uz tip entiteta $N_i$, dok se na slici 2.8 prikazan ER dijagram sa kardinalitetima dobijenim upisivanjem dvojki $(a_i, b_i)$ uz tip entiteta $E_j$, gde je $i \neq j$.

**Drugi postupak:** Par $(a_1, b_1)$ se navodi na potegu uz tip entiteta $E_2$, a par $(a_2, b_2)$ se navodi na potegu uz tip entiteta $E_1$. Semantika ovog postupka predstavljanja je da se jedna pojava tipa entiteta $E_1$ javlja, kao prva komponenta u skupu pojava tipa poveznika minimalno $a_2$ i maksimalno $b_2$ puta, a da se jedna pojava tipa entiteta $E_2$ javlja, kao druga komponenta u skupu pojava tipa poveznika minimalno $a_1$ i maksimalno $b_1$ puta.

Teško je reći da bilo koji od opisanih postupaka predstavljanja kardinaliteta tipa poveznika u ER dijagramima ima prednost nad drugim. Na jugoslovenskom informatičkom prostoru je u široj upotrebi drugi postupak, tj. par $(a_i, b_i)$ se upisuje uz tip entiteta $N_i$ predstavljanja kardinaliteta tipa poveznika i to je jedini razlog što će se, u daljem tekstu, koristiti taj postupak.

**Primer 2.24:** Oba slučaja, opisan je isti realni sistem, u kome:
- radnik mora biti raspoređen na tačno jedno radno mesto i
- na jedno radno mesto može biti raspoređeno više radnika, ali mogu postojati radna mesta na koja nije niko raspoređen.

Na Slici 2.7 kardinaliteti su prikazani tako da se $(a_i, b_i)$ upisuje uz tip entiteta $N_i$:

- Uz Radnik stoji $(0, N)$ - jer sa strane Radnika, jedna pojava Radno_Mesto može imati 0 do N radnika
- Uz Radno_Mesto stoji $(1, 1)$ - jer sa strane Radno_Mesto, jedan radnik mora imati tačno 1 radno mesto

Na Slici 2.8 kardinaliteti su prikazani drugim postupkom - $(a_i, b_i)$ uz tip entiteta $E_j$ (obrnuto):

- Uz Radnik stoji $(1, 1)$
- Uz Radno_Mesto stoji $(0, N)$

### Geometrijski simboli (Primer 2.25)

Neki put se u ER dijagramima parovi $(a, b)$ predstavljaju putem specijalnih geometrijskih simbola:

- Minimalni kardinalitet $a = 0$ se predstavlja putem isprekidanog potega između tipa entiteta i tipa poveznika, a $a = 1$ se predstavlja punom linijom.
- Maksimalni kardinalitet $b = N$ se predstavlja račvanjem dela potege uz geometrijsku predstavu tipa entiteta, a $b = 1$ potegom koji nema račvu na svom kraju.

> [!CAUTION]
> Na ispitu se često pojavljuje pitanje o dva postupka navođenja kardinaliteta. Ključna razlika:
> - **Prvi postupak:** $(a_i, b_i)$ se piše uz tip entiteta $E_j$ (drugi tip, na suprotnu stranu!)
> - **Drugi postupak (naš):** $(a_i, b_i)$ se piše uz tip entiteta $N_i$ (isti tip, na svoju stranu)
>
> U našem okruženju koristimo drugi postupak.

---

## 7. Integritet tipa (Ograničenje ključa)

Poslednji deo integritetne komponente je **integritet tipa** - ograničenje ključa za tipove entiteta i tipove poveznika.

### Integritet tipa entiteta

Za tip entiteta, integritet se obezbeđuje putem **ključa**. Ključ je minimalni skup obeležja koji jednoznačno identifikuje svaku pojavu tipa entiteta. Svaki tip entiteta mora posedovati bar jedan ključ.

### Integritet tipa poveznika

Integritet tipa poveznika je tesno vezan za kardinalitete. **Identifikator tipa poveznika** predstavlja niz naziva povezanih tipova $(N_1, N_2, \ldots, N_m)$, ili neki neprazan podniz niza $(N_1, N_2, \ldots, N_m)$.

**Ključ tipa poveznika** se izvodi na osnovu ključeva povezanih tipova. Neka je $K_i$ ključ tipa $N_i$. Ključ tipa poveznika je vrlo često, ali ne uvek, pravi ili nepravi podskup unije ključeva $K_1 \cup \ldots \cup K_m$.

Tri opšte grupe maksimalnih kardinaliteta direktno utiču na formiranje ključeva tipa poveznika:

#### Grupa M:N

Identifikator (ključ) TP se formira od ključeva **oba** povezana tipa.

**Primer:** TP Radi(Radnik, Projekat) sa kardinalitetom $(0,M) : (0,N)$
- Identifikator TP: (Radnik, Projekat)
- $K_p = Mbr + Spr$ (ključ Radnika + ključ Projekta)

#### Grupa N:1

Identifikator (ključ) TP se formira od ključa onog tipa koji ima maksimalni kardinalitet 1.

**Primer:** TP Raspoređen(Radnik, Radno_mesto) sa kardinalitetom $(0,1) : (0,N)$
- Identifikator TP: (Radnik)
- $K_p = Mbr$ (samo ključ Radnika, jer radnik može biti na najviše jednom radnom mestu)

#### Grupa 1:1

Identifikator (ključ) TP može biti ključ **bilo kog** od dva povezana tipa (oba su kandidati).

**Primer:** TP JeOsiguran(Radnik, PolisaOsiguranja) sa kardinalitetom $(0,1) : (0,1)$
- Identifikator TP: (Radnik) **i** (PolisaOsiguranja) - oba su validni identifikatori
- $K_1 = MBR$ i $K_2 = BrPol$

#### Rekurzivni TP - grupa M:N

Kod rekurzivnog tipa poveznika, isti tip entiteta se javlja u obe uloge, pa se obeležja ključa moraju **preimenovati** da bi se razlikovala.

**Primer:** TP Sastoji_se(Deo, Deo) sa kardinalitetom $(0,M) : (0,N)$
- Identifikator TP: (Deo(Ima komponente), Deo(Je komponenta za))
- $K_p = DeID + DeIDkom$ - gde je $DeIDkom$ preimenovano obeležje $DeID$ sa semantikom: DeID sa ulogom komponente ugradnje

> [!IMPORTANT]
> Zapamtite pravilo za formiranje ključa TP:
> - **M:N** → ključ = unija ključeva OBA povezana tipa
> - **N:1** → ključ = ključ tipa sa strane "1" (koji ima $b = 1$)
> - **1:1** → ključ = ključ BILO KOG od dva povezana tipa

---

## 8. Karakteristične strukture ER modela podataka

U narednom tekstu je analizirana semantika jednog broja karakterističnih struktura ER modela podataka. S obzirom na mali broj osnovnih koncepata (tip entiteta i tip poveznika) i na krajnju jednostavnost njihove veze, osnovna pažnja u narednoj analizi je poklonjena semantici kardinaliteta tipa poveznika.

U analizi se polazi od karakteristične strukture, a zatim se interpretira kakav treba da bude realni sistem, pa da posmatrana ER struktura bude veran model nekog njegovog dela. Pošto je opisano preslikavanje jedan na jedan, to znači da važi i obratno. Na osnovu poznavanja karakteristika dela realnog sistema, može se izabrati odgovarajuća ER struktura, kao njegova verna slika.

### Strukture sa kardinalitetima grupe M:N

Najopštiji slučaj kardinaliteta tipa poveznika opisuje se sa:

$$R(E_1(a_2, M) : E_2(a_1, N))$$

što se javlja kada u realnom sistemu jedan entitet klase $E_1$ može biti u vezi sa $M$ ($>1$) entiteta klase $E_2$ i kada isto važi i obratno. Tada se kaže da između dva tipa entiteta ($E_1$ i $E_2$) u modelu važi odnos više-prema-više, što se označava i sa $M:N$.

Vrednosti minimalnih kardinaliteta definišu sledeće tri slučajeve ovog odnosa:

1. **$a_1 = 0$ i $a_2 = 0$** - oba minimalna kardinaliteta ukazuju da u obe klase mogu postojati entiteti koji nisu povezani sa bilo kojim entitetom druge klase. Međutim, i slučaj kada su svi entiteti posmatranih klasa međusobno povezani nije zabranjen.

2. **$a_1 = 1$ i $a_2 = 0$ ili $a_1 = 0$ i $a_2 = 1$** - minimalni kardinaliteti ukazuju da svi entiteti jedne od povezanih klasa (recimo klase $E_1$) moraju biti povezani sa bar jednim entitetom druge klase (klase $E_2$). To dalje znači da je egzistencija entiteta u jednoj klasi ($E_1$) uslovljena njihovom povezanošću sa entitetima u drugoj klasi ($E_2$).

3. **$a_1 = 1$ i $a_2 = 1$** - minimalni kardinaliteti ukazuju da svaki entitet jedne klase mora biti povezan sa bar jednim entitetom druge klase. Egzistencija entiteta u obe klase uslovljena je njihovom povezanošću sa bar jednim entitetom druge klase, što predstavlja izuzetno strogo ograničenje.

**Primer 2.26:** U svojstvu primera odnosa $R(E_1(a_2, M) : E_2(a_1, N))$ mogu se posmatrati tipovi entiteta Radnik, Projekat i tip poveznika Radi. Maksimalni kardinaliteti tipa poveznika Radi su $M$ i $N$, što znači da više radnika može raditi na više projekata i obratno.

---

## Rezime

Integritetna komponenta ER modela je slojevita - svaki nivo ograničenja doprinosi ukupnom kvalitetu podataka:

1. **Ograničenje domena** kaže: "Ove vrednosti uopšte mogu da postoje" (tip, dužina, uslov)
2. **Nula vrednost** kaže: "Da li sme da bude prazno?"
3. **Ograničenje vrednosti obeležja** kaže: "Ovo obeležje koristi ovaj domen i sme/ne sme biti NULL"
4. **Ograničenje pojave tipa** kaže: "Unutar jedne pojave, ova obeležja moraju biti u ovom odnosu"
5. **Kardinalitet tipa poveznika** kaže: "Ovako su entiteti međusobno povezani - koliko minimalno i maksimalno"
6. **Integritet tipa** kaže: "Ovako se jednoznačno identifikuje svaka pojava"

Zajedno, ova ograničenja čine podatke smislenim, konzistentnim i pouzdanim.

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

**Opšte o integritetnoj komponenti:**

P: Koje tipove ograničenja obuhvata integritetna komponenta ER modela podataka?

P: Koji je cilj integritetne komponente ER modela?

**Ograničenje domena:**

P: Šta predstavlja integritet domena?

P: Koja je struktura (trojka) ograničenja domena u opštem slučaju?

P: Šta definiše tip podatka u okviru ograničenja domena?

P: Šta izražava dužina podatka u okviru ograničenja domena?

P: Šta predstavlja uslov kao treća komponenta ograničenja domena?

P: Kako se formalno specificira domen?

P: Šta je $D$, šta je $\text{id}(D)$, a šta $\text{Predef}$ u specifikaciji domena $D(\text{id}(D), \text{Predef})$?

P: Kako izgleda ograničenje domena primenom pravila nasleđivanja?

P: Šta je Tip u strukturi $\text{id}(D) = (\text{Tip}, \text{Dužina}, \text{Uslov})$ i da li je obavezan?

P: Kada se navodi Dužina u ograničenju domena?

P: Šta je Predef i koji uslov mora da zadovolji?

P: Navedite standardne tipove podataka sa njihovim značenjima dužina.

P: Šta znači tip podatka LOGICAL i koje vrednosti prima?

P: Šta znači $\text{dom}(OCE) = \{0, 1, \ldots, 99\}$ za ograničenje $INTEGER(2)$?

P: Šta znači pridruživanje $\text{dom}(IME)$ ograničenja $CHARACTER(10)$?

P: Šta su prosti regularni izrazi?

P: Koje dve forme mogu imati prosti regularni izrazi?

P: Šta znači izraz $(\theta k)$ u prostom regularnom izrazu?

P: Šta znači izraz $(k_1, k_2, \ldots, k_n)$ u prostom regularnom izrazu?

P: Šta su složeni regularni izrazi i kako se formiraju?

P: Koji logički operatori se koriste za formiranje složenih regularnih izraza?

P: Kako se izražava ograničenje domena kada regularni izrazi nisu dovoljni?

P: Kako izgleda ograničenje $iznos = kol \times jed\_cen$ i šta predstavlja?

P: Kako se algoritmom može izraziti ograničenje za obeležja REGIJA i PTT_BROJ?

P: Objasnite primer domena DPOZOCENA koji nasleđuje DOCENA.

**Nula vrednost:**

P: Šta je nula vrednost?

P: Koja su dva najčešća značenja nula vrednosti?

P: Da li je nula vrednost isto što i broj 0?

P: Objasnite primer obeležja K_TEL i nula vrednosti.

**Ograničenje vrednosti obeležja:**

P: Kako se formalno specificira obeležje u okviru tipa?

P: Šta je $\text{id}(N, A)$ i kakvu strukturu ima?

P: Šta predstavlja komponenta Domen u ograničenju vrednosti obeležja?

P: Šta znači $\text{Null} = T$ a šta $\text{Null} = \bot$?

P: Da li su Domen i Null obavezne komponente specifikacije obeležja?

P: Kako se određuje predefinisana vrednost obeležja ako nije eksplicitno navedena?

**Ograničenje pojave tipa:**

P: Šta definiše ograničenje pojave tipa?

P: Kako izgleda formalna definicija ograničenja pojave tipa?

P: Šta je $Q'$ (prošireni skup obeležja) za tip entiteta, a šta za tip poveznika?

P: Šta predstavlja Uslov u ograničenju pojave tipa?

P: Objasnite primer ograničenja pojave tipa Radnik sa uslovom $ZAN = 'prg' \Rightarrow BPJZ \neq \bot$.

P: Koja je razlika između ograničenja domena, ograničenja vrednosti obeležja i ograničenja pojave tipa?

**Kardinalitet tipa poveznika:**

P: Šta je kardinalitet tipa poveznika?

P: Kako se formalno definiše kardinalitet TP prema povezanom tipu?

P: Koje vrednosti može uzeti minimalni kardinalitet $a$?

P: Koje vrednosti može uzeti maksimalni kardinalitet $b$?

P: Šta znači $a = 0$ za pojavu povezanog tipa?

P: Šta znači $a = 1$ za pojavu povezanog tipa?

P: Šta znači $b = 1$ za pojavu povezanog tipa?

P: Šta znači $b = N$ za pojavu povezanog tipa?

P: Šta je totalno preslikavanje?

P: Šta je parcijalno preslikavanje?

P: Šta je egzistencijalno ograničenje?

P: Šta označava pojam prethođenja i sleđenja u kontekstu kardinaliteta?

P: Kako se formalno označava kardinalitet preslikavanja $R_1$?

P: Kako se formalno označava kardinalitet relacije $R$?

P: Koje su tri opšte grupe maksimalnih kardinaliteta?

P: Opišite semantiku grupe M:N.

P: Opišite semantiku grupe N:1.

P: Opišite semantiku grupe 1:1.

P: Koja tri slučaja minimalnih kardinaliteta postoje za grupu M:N?

P: Šta znači kardinalitet $(1,1) : (0,N)$ za vezu Radnik-Raspoređen-Radno_Mesto?

P: Šta znači kardinalitet $(0,M) : (0,N)$ za vezu Radnik-Radi-Projekat?

**Predstavljanje kardinaliteta u ER dijagramima:**

P: Koji su dva postupka navođenja kardinaliteta u ER dijagramima?

P: Kako funkcioniše prvi postupak navođenja kardinaliteta?

P: Kako funkcioniše drugi postupak navođenja kardinaliteta?

P: Koji postupak se koristi na jugoslovenskom informatičkom prostoru?

P: Kako se geometrijskim simbolima predstavlja minimalni kardinalitet $a = 0$ i $a = 1$?

P: Kako se geometrijskim simbolima predstavlja maksimalni kardinalitet $b = 1$ i $b = N$?

**Integritet tipa (ograničenje ključa):**

P: Šta je integritet tipa entiteta?

P: Šta je identifikator tipa poveznika?

P: Kako se formira ključ TP za grupu M:N?

P: Kako se formira ključ TP za grupu N:1?

P: Kako se formira ključ TP za grupu 1:1?

P: Kako se rešava problem ključa kod rekurzivnog tipa poveznika?

P: Dajte primer ključa TP Radi za grupu M:N.

P: Dajte primer ključa TP Raspoređen za grupu N:1.

P: Dajte primer ključa TP JeOsiguran za grupu 1:1.

P: Šta znači preimenovanje obeležja kod rekurzivnog TP Sastoji_se?

**Karakteristične strukture:**

P: Čime se bavi analiza karakterističnih struktura ER modela?

P: Kako se opisuje najopštiji slučaj kardinaliteta tipa poveznika (M:N)?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite hijerarhiju tri nivoa ograničenja: ograničenje domena, ograničenje vrednosti obeležja i ograničenje pojave tipa. Kako se nadograđuju jedno na drugo?

**O:** Ograničenje domena definiše koji tip i opseg vrednosti uopšte može postojati (npr. INTEGER, dužina 2, od 5 do 10). Ograničenje vrednosti obeležja povezuje konkretno obeležje sa domenom i dodatno definiše da li obeležje sme primiti nula vrednost (Null = T ili $\bot$). Ograničenje pojave tipa ide najdalje - obuhvata sva ograničenja vrednosti obeležja, ali im dodaje logički uslov koji povezuje više obeležja unutar iste pojave (npr. ako je zanimanje "programer", onda broj programskog jezika ne sme biti NULL).

**P:** Za domen DPOZOCENA koji nasleđuje DOCENA, objasnite kako pravilo nasleđivanja funkcioniše i koje su vrednosti dozvoljene.

**O:** DOCENA je definisan kao $((Number, 2, d \geq 5 \land d \leq 10), -)$, dakle dozvoljava vrednosti od 5 do 10. DPOZOCENA nasleđuje DOCENA i dodaje novi uslov $d \geq 6$, sa predefinisanom vrednošću 6. Efektivno, DPOZOCENA dozvoljava vrednosti $\{6, 7, 8, 9, 10\}$ jer se kombinuju ograničenja nasleđenog domena ($5 \leq d \leq 10$) sa novim uslovom ($d \geq 6$), i podrazumevana vrednost je 6.

**P:** Objasnite razliku između totalnog i parcijalnog preslikavanja. Dajte primer za svaki slučaj.

**O:** Totalno preslikavanje nastaje kada je minimalni kardinalitet $a = 1$, što znači da svaki entitet jedne klase mora biti povezan sa bar jednim entitetom druge klase. Primer: Radnik mora biti raspoređen na tačno jedno radno mesto - kardinalitet $(1,1)$. Parcijalno preslikavanje nastaje kada je $a = 0$, što znači da entitet ne mora biti u vezi ni sa jednim entitetom druge klase. Primer: na radnom mestu ne mora biti raspoređen nijedan radnik - kardinalitet $(0,N)$.

**P:** Kako maksimalni kardinaliteti utiču na formiranje ključa tipa poveznika? Objasnite za svaku od tri grupe.

**O:** Za grupu M:N, ključ TP se formira kao unija ključeva oba povezana tipa (npr. $Mbr + Spr$), jer jedan entitet može biti u vezi sa više entiteta drugog tipa. Za grupu N:1, ključ TP je ključ onog tipa koji ima $b = 1$ (npr. samo $Mbr$), jer taj entitet može biti u vezi sa najviše jednim entitetom drugog tipa. Za grupu 1:1, oba povezana tipa su kandidati za ključ TP (npr. i $MBR$ i $BrPol$), jer oba imaju $b = 1$.

**P:** Šta je egzistencijalno ograničenje i kako je povezano sa pojmom prethođenja i sleđenja?

**O:** Egzistencijalno ograničenje nastaje kada je minimalni kardinalitet $a = 1$, što znači da pojava jednog tipa ne može postojati bez veze sa pojavom drugog tipa. Ovo implicira prethođenje i sleđenje: entitet $e_2$ iz $E_2$ mora postojati pre nego što entitet $e_1$ iz $E_1$ može biti kreiran. Na primer, radno mesto mora postojati pre nego što se radnik može rasporediti na njega.

**P:** Objasnite dva postupka navođenja kardinaliteta u ER dijagramima na primeru veze Radnik-Raspoređen-Radno_Mesto sa kardinalitetom $(1,1) : (0,N)$.

**O:** Kod prvog postupka, par $(a_i, b_i)$ se upisuje uz tip entiteta $E_j$ (suprotni), pa bi uz Radnik pisalo $(0,N)$ a uz Radno_Mesto $(1,1)$. Kod drugog postupka (koji koristimo), par $(a_i, b_i)$ se upisuje uz sam tip entiteta $N_i$, pa uz Radnik piše $(1,1)$ (jer jedan radnik mora biti raspoređen na tačno jedno radno mesto), a uz Radno_Mesto piše $(0,N)$ (jer na jednom radnom mestu može biti 0 do N radnika).

**P:** Objasnite razliku između prostih i složenih regularnih izraza i dajte primer za svaki.

**O:** Prosti regularni izrazi koriste jedan operator poređenja sa konstantom (npr. $(<11)$ - vrednost mora biti manja od 11) ili nabrajaju dozvoljene vrednosti (npr. $(6, 7, 8, 9, 10)$). Složeni regularni izrazi nastaju kombinovanjem prostih ili drugih složenih izraza pomoću logičkih operatora $\land$, $\lor$ i $\neg$. Primer složenog: $(> 5 \land < 11)$, koji ograničava opseg na vrednosti strogo veće od 5 i strogo manje od 11.

**P:** Zamislite tip entiteta Student(BRI, IME, PRZ, GOD_STUDIJA, PROSEK). Definišite ograničenja domena za svako obeležje i napišite smisleno ograničenje pojave tipa.

**O:** Domeni bi mogli biti: DBRI = (Number, 4, $d \geq 1$), DIME = (String, 20, -), DPRZ = (String, 30, -), DGOD = (Number, 1, $d \geq 1 \land d \leq 4$), DPROSEK = (Number, 4, $d \geq 5.00 \land d \leq 10.00$). Smisleno ograničenje pojave tipa bi moglo biti: $GOD\_STUDIJA = 1 \Rightarrow PROSEK = \bot$ (student na prvoj godini još nema prosek, jer mora prvo da polaže ispite).

**P:** Objasnite tri slučaja minimalnih kardinaliteta za grupu M:N na primeru veze Radnik-Radi-Projekat.

**O:** Slučaj $a_1 = 0, a_2 = 0$: mogu postojati radnici koji ne rade ni na jednom projektu i projekti na kojima ne radi nijedan radnik. Slučaj $a_1 = 1, a_2 = 0$ (ili obrnuto): svi radnici moraju raditi na bar jednom projektu, ali mogu postojati projekti bez radnika (ili obrnuto). Slučaj $a_1 = 1, a_2 = 1$: svaki radnik mora raditi na bar jednom projektu i svaki projekat mora imati bar jednog radnika - ovo je najstrože ograničenje.
