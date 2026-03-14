# Integritetna komponenta ER modela

## Uvod - zašto nam trebaju ograničenja?

Zamislimo da pravimo bazu podataka za fakultet. Strukturalnom komponentom ER modela opisali smo *šta postoji* u našem sistemu - tipove entiteta (Student, Predmet, Nastavnik), tipove poveznika (Sluša, Predaje) i njihova obeležja. Ali samo struktura nije dovoljna. Hajde da razmislimo - šta sprečava nekoga da unese ocenu 47 za studenta? Ili da upiše radnika koji nije raspoređen ni na jedno radno mesto, a naš sistem zahteva da svaki radnik mora negde da radi? Ništa - ako nemamo ograničenja.

Tu nastupa **integritetna komponenta ER modela podataka**. Ona nam daje mehanizme da precizno definišemo *pravila igre* - šta je dozvoljeno, a šta nije u našoj bazi podataka. Bez nje, baza bi bila kao grad bez saobraćajnih pravila - haos.

ER model, s obzirom na to da je prevashodno namenjen za predstavljanje konceptualne šeme, poseduje relativno dobre mogućnosti za definisanje ograničenja. U modelu se ta ograničenja izražavaju, uglavnom, eksplicitno. Hajde da vidimo koja ograničenja spadaju u integritetnu komponentu.

> [!IMPORTANT]
> Integritetna komponenta ER modela obuhvata tri osnovne vrste ograničenja:
> 1. **Integritet domena** - ograničenja nad vrednostima koje obeležja mogu da prime
> 2. **Kardinalitet tipa poveznika** - sa svojim brojnim varijantama i semantičkim interpretacijama
> 3. **Slabi tip entiteta** - entiteti čija egzistencija zavisi od drugih entiteta

---

## 1. Integritet domena

### 1.1 Šta je integritet domena i zašto je bitan?

Zamislimo da imamo obeležje *Ocena* kod studenta. Bez ikakvih ograničenja, neko bi mogao upisati ocenu 150, ili čak uneti tekst "odličan" umesto broja. To nema smisla - ocena na fakultetu može biti samo ceo broj od 5 do 10.

**Integritet domena** predstavlja ograničenje koje svojstveno praktično svim modelima podataka. On nam omogućava da precizno definišemo šta su dozvoljene vrednosti za svako obeležje.

U opštem slučaju, **integritet ili ograničenje domena je trojka**:

$$(\text{tip podatka}, \text{dužina podatka}, \text{uslov})$$

Hajde da razjasnimo svaku od ove tri komponente:

- **Tip podatka** - definiše vrstu znakova, putem kojih se izražava vrednost obeležja. Tip podatka je standardno programsko-jezičko ograničenje i predstavlja obavezni deo ograničenja domena.
- **Dužina podatka** - izražava se putem maksimalnog broja znakova, koji mogu biti upotrebljeni za izražavanje vrednosti obeležja. Koristi se za tipove podataka koji to zahtevaju (npr. za CHARACTER se navodi maksimalni broj znakova, za REAL se navodi broj cifara ispred i iza zareza).
- **Uslov** - treća, opciona, komponenta ograničenja domena. Uslov može biti regularni izraz ili funkcija.

Prema tome, tip i dužina podatka ograničavaju vrednosti obeležja na tip i broj znakova.

### 1.2 Standardni tipovi podataka

Jedno standardno ograničenje domena može predstavljati sledeći skup tipova podataka sa dužinama:

| Tip podatka | Dužina | Opis |
|-------------|--------|------|
| **INTEGER** | broj cifara | Celi brojevi |
| **REAL** | broj cifara ispred zareza, broj cifara iza zareza | Realni brojevi |
| **CHARACTER** | broj znakova | Znakovni nizovi |
| **LOGICAL** | - | Logički tip (T, ⊥) |
| **DATE** | - | Datumski tip |

Tip podatka "logical" ukazuje da je reč o logičkoj promenljivoj, koja uzima vrednosti iz skupa $\{T, \perp\}$ (tačno ili netačno).

### 1.3 Pridruživanje domena obeležjima - konkretni primeri

Pogledajmo sada kako se domen pridružuje konkretnim obeležjima. Zapisujemo to kao $dom(OBELEŽJE)$.

**Primer 2.19.** Pridruživanje $dom(OCE)$ standardnog ograničenja $INTEGER(2)$, ukazuje da važi:

$$dom(OCE) = \{0, 1, ..., 99\}$$

Ovo znači da obeležje OCE (ocena) može primiti bilo koji dvocifreni ceo broj. Ali, vidimo da je ovo previše široko - ocena 47 nema smisla!

Pridruživanje $dom(IME)$ standardnog ograničenja $CHARACTER(10)$, ukazuje da $dom(IME)$ može pripadati bilo koji niz od 10 znakova.

### 1.4 Prosti i složeni regularni izrazi - preciziranje ograničenja

Standardna ograničenja domena, kao što smo videli, često nisu dovoljno precizna. Zato se uvodi uslov, kao treća, opciona komponenta ograničenja domena. Uslov može biti **regularni izraz** ili **funkcija**. Postoje prosti i složeni regularni izrazi.

#### Prosti regularni izrazi

Prosti regularni izrazi se definišu s obzirom na neke konstante. Te konstante moraju zadovoljiti standardno ograničenje domena.

Neka je $k$ konstanta iz domena pridruženog obeležju $A$, a $\theta$ operator poređenja iz skupa $\{<, >, \leq, \geq, \neq, =\}$. Tada proste regularne izraze predstavljaju $(\theta k)$ i $(k_1, k_2, ..., k_n)$.

- Izraz $(\theta k)$ ukazuje da sve vrednosti pridružene obeležju $A$ moraju biti u relaciji $\theta$ sa konstantom $k$
- Izraz $(k_1, k_2, ..., k_n)$ ukazuje da obeležje $A$ sme uzimati vrednosti iz skupa $\{k_1, k_2, ..., k_n\}$

**Primer 2.20.** Pridruživanje $dom(OCE)$ sledeće trojke sa prostim regularnim izrazom:

$$(INTEGER, (2), <11)$$

ukazuje da obeležje $OCE$ može uzeti vrednost iz skupa $\{0, 1, ..., 10\}$.

Pridruživanje $dom(OCE)$ trojke sa prostim regularnim izrazom:

$$(INTEGER, (2), (6, 7, ..., 10))$$

ograničava vrednosti tog obeležja na uobičajeni opseg pozitivnih ocena.

Do istog rezultata se dolazi i pridruživanjem $dom(OCE)$ sledeće trojke sa **složenim regularnim izrazom**:

$$(INTEGER, (2), > 5 \wedge < 11)$$

#### Složeni regularni izrazi

**Složeni regularni izrazi** se komponuju od drugih regularnih izraza (prostih ili složenih) njihovim povezivanjem putem logičkih operatora $\wedge$ (i), $\vee$ (ili) i $\neg$ (negacija).

> [!TIP]
> Za ispit je bitno znati razliku: prosti regularni izrazi koriste jedan operator poređenja ili nabrajanje vrednosti, dok složeni kombinuju više uslova logičkim operatorima.

### 1.5 Ograničenja putem funkcija i algoritama

Za izražavanje ograničenja nad domenima nekih obeležja nisu dovoljni ni regularni izrazi. Tada se koriste **funkcije**, čije argumente predstavljaju neka obeležja, ili se koriste **algoritmi**.

**Primer 2.21.** Posmatraju se obeležja $KOL$ (količina artikla), $JED\_CEN$ (jedinična cena artikla) i $IZNOS$. Ograničenje da $dom(IZNOS)$ sme sadržati samo vrednosti dobijene množenjem elementa $dom(KOL)$ sa elementima iz $dom(JED\_CEN)$, može se izraziti putem funkcije:

$$iznos = kol \times jed\_cen$$

Ovo je primer kada jedno obeležje zavisi od vrednosti drugih obeležja i ta zavisnost se izražava funkcijom.

**Primer sa algoritmom:** Posmatraju se obeležja $REGIJA$ i $PTT\_BROJ$. Ograničenje da u regiji "Vojvodina" svi poštanski brojevi počinju cifrom 2, može se izraziti sledećim algoritmom:

```
AKO JE REGIJA = "Vojvodina" TADA
    PTT_BROJ = "2*"
INAČE
KRAJ AKO.
```

Pri tome, znak * predstavlja zamenu za niz bilo kojih znakova - odnosno, reč je o džoker znaku (wildcard). Dakle, ako je regija Vojvodina, poštanski broj mora početi dvojkom, a ostale cifre mogu biti bilo šta.

### 1.6 Nula vrednost

Pre nego što pređemo na kardinalitet, moramo da se upoznamo sa jednim posebnim konceptom - **nula vrednošću**.

**Nula vrednost** predstavlja specijalnu vrednost obeležja. Putem tog ograničenja se specificira da li obeležje može imati nedefinisanu vrednost. Sama nula vrednost ima najčešće jedno od sledeća dva značenja:

- **postojeća, ali nepoznata vrednost** - vrednost postoji u realnosti, ali je ne znamo
- **neprimereno svojstvo** - dati podatak nema smisla za taj entitet

**Primer 2.22.** Posmatrajmo obeležje $K\_TEL$ (broj kućnog telefona). Za neke ljude to obeležje predstavlja neprimereno svojstvo, jer telefon kod kuće nemaju, te se za evidentiranje njihovog broja telefona koristi nula vrednost sa odgovarajućom interpretacijom značenja. Drugi ljudi imaju telefon, ali je njegov broj, u trenutku evidentiranja, nepoznat. Tada se ponovo koristi nula vrednost, ali sada u drugom značenju.

Bitno je naglasiti da nula vrednost ne predstavlja broj 0 već specijalnu vrednost, čije značenje se, najčešće, interpretira na jedan od navedena dva načina.

> [!WARNING]
> Česta greška studenata: Nula vrednost (NULL) **nije isto** što i broj 0 ili prazan string "". To je posebna oznaka koja govori "vrednost nedostaje" ili "vrednost nije primenljiva".

---

## 2. Kardinalitet tipa poveznika

### 2.1 Šta je kardinalitet i zašto je bitan?

Kada definišemo strukturu baze, ne zanima nas samo *šta* je povezano, nego i *koliko*. Da li jedan radnik može raditi na više projekata, ili samo na jednom? Da li na jednom radnom mestu mora biti raspoređen bar jedan radnik, ili može da bude i prazno? Odgovore na ova pitanja daje **kardinalitet tipa poveznika**.

Često se od modela realnog sistema i modela baze podataka informacionog sistema zahteva da pruži informaciju ne samo o vezama između klasa entiteta već i o prirodi odnosa između entiteta povezanih klasa.

U modelu realnog sistema, informaciju o prirodi odnosa između entiteta povezanih klasa daje takozvani **kardinalitet tipa poveznika** $R$ odnosno kardinalitet odgovarajuće relacije $R$.

### 2.2 Formalna definicija kardinaliteta

Posmatrajmo binarnu relaciju $R$ između skupova pojava dva tipa entiteta $E_1$ i $E_2$. Ova relacija se može predstaviti putem dva preslikavanja:

$$R_1: E_1 \rightarrow \mathcal{P}(E_2) \quad \text{i} \quad R_2: E_2 \rightarrow \mathcal{P}(E_1)$$

gde je $\mathcal{P}(E)$ partitivni skup skupa $E$.

Preslikavanjima $R_1$ i $R_2$ se može dati sledeća semantička interpretacija:

- $R_1$ je uloga entiteta iz skupa $E_1$, a $R_2$ je uloga entiteta iz skupa $E_2$ u njihovoj vezi, opisanoj relacijom $R$.

Za svako od ovih preslikavanja se definiše **minimalni** i **maksimalni kardinalitet**.

**Pojam kardinaliteta preslikavanja** se odnosi na brojnost (kardinalitet) elementa partitivnog skupa u koji se preslikava jedan element skupa originala.

Minimalni i maksimalni kardinalitet jednog preslikavanja, recimo $R_1$, određuje se identifikacijom minimalne i maksimalne brojnosti podskupa skupa $E_2$ u koji se može preslikati neki (bilo koji) element skupa $E_1$. Kardinalitet preslikavanja $R_1$ se označava sa:

$$R_1(E_2(a_2, b_2))$$

gde je $a_2$ minimalni, a $b_2$ maksimalni kardinalitet.

Kardinalitet relacije $R$, odnosno tipa poveznika $R$, se označava sa:

$$R(E_1(a_1, b_1) : E_2(a_2, b_2))$$

> [!IMPORTANT]
> **Ključna definicija:** Kardinalitet tipa poveznika je par $(a, b)$ gde je:
> - $a \in \{0, 1\}$ - **minimalni kardinalitet**
> - $b \in \{1, N\}$, $N \geq 2$ - **maksimalni kardinalitet**
>
> Ograničava u koliko pojava tipa poveznika može učestvovati jedna, bilo koja pojava povezanog tipa - **minimalno** $(a)$ i **maksimalno** $(b)$.

### 2.3 Značenje minimalnog kardinaliteta (a)

Parametrima $a$ i $b$ se najčešće dodeljuju sledeće karakteristične vrednosti:

**Minimalni kardinalitet $a$:**

- Parametru $a$ se dodeljuje vrednost **0**, ako se bar jedan element skupa originala preslikava u prazan skup, inače mu se dodeljuje vrednost **1**.

Šta to znači u praksi?

- **$a = 0$** - znači da ne mora svaki entitet klase $E_1$ biti povezan sa bar jednim entitetom klase $E_2$. Preslikavanje $R_1$ je **parcijalno** - u realnom sistemu može postojati bar jedan entitet klase $E_1$ koji nije povezan ni sa jednim entitetom klase $E_2$.

- **$a = 1$** - odgovarajuće preslikavanje se naziva **totalnim**, jer se svaki original preslikava u neprazan podskup. Drugim rečima, u realnom sistemu svaki entitet prve klase mora biti povezan sa bar jednim entitetom druge klase. Slučaj $a_2 = 1$ se naziva **egzistencijalnim ograničenjem**, jer se može tumačiti na sledeći način: da bi $e_1$ pripadao $E_1$, mora biti povezan sa bar jednim $e_2$ iz $E_2$.

> [!CAUTION]
> Minimalnom kardinalitetu $a = 1$ se može dati i semantička interpretacija da on ukazuje na **prethođenje i sleđenje**. Naime, ako je $R_1(E_2(1, b_2))$, to ukazuje da prvo mora postojati neki entitet $e_2$ u $E_2$, da bi entitet $e_1$, koji je sa njim u vezi, mogao biti uključen u skup $E_1$. Znači, ako je $a_2 = 1$, postojanje entiteta $e_2$ iz skupa $E_2$ mora prethoditi nastanku entiteta $e_1$ iz $E_1$.

### 2.4 Značenje maksimalnog kardinaliteta (b)

**Maksimalni kardinalitet $b$:**

- Parametru $b$ se dodeljuje vrednost **1**, ako kardinalitet slike svakog originala nije veći od 1, inače mu se dodeljuje vrednost $N$ ili $M$, gde je $1 < N, M \leq |E|$.

U praksi:

- Ako je $b_2 = 1$, preslikavanje $R_1: E_1 \rightarrow \mathcal{P}(E_2)$ se transformiše u preslikavanje $R: E_1 \rightarrow E_2$. To znači da se svaki entitet klase $E_1$ može povezati sa **najviše jednim** entitetom klase $E_2$, ali ne mora ni sa jednim.

- Kardinalitet $b_2 = 1$ ukazuje da svaki entitet klase $E_1$ može biti povezan sa najviše jednim entitetom klase $E_2$. Kardinalitet $b_2 = N$ ukazuje da može, ali ne mora, postojati bar jedan entitet klase $E_1$ koji je povezan sa više od jednog entiteta klase $E_2$.

### 2.5 Pojam kardinaliteta - objašnjenje na primeru

**Primer 2.23.** U slučaju modela dela realnog sistema prikazanog na slikama 2.5 i 2.6, može se zahtevati da apstraktni model ukaže da:

- jedan radnik može biti raspoređen na najviše jedno radno mesto,
- na jedno radno mesto može biti raspoređeno više radnika i
- na jedno radno mesto ne mora biti raspoređen nijedan radnik.

Hajde da to prevedemo u formalni zapis. Tip poveznika *Raspoređen* povezuje tipove entiteta *Radnik* i *Radno_Mesto*:

- Kardinalitet uz Radnik: **(0, N)** ili **(1, 1)** - zavisi od toga da li svaki radnik mora biti raspoređen
- Kardinalitet uz Radno_Mesto: **(0, N)** - na jedno radno mesto može biti raspoređeno 0 ili više radnika

### 2.6 Tri grupe kardinaliteta

S obzirom na maksimalne vrednosti kardinaliteta, tipovi poveznika se mogu podeliti u **tri grupe**:

| Grupa | Oznaka | Opis | Primer |
|-------|--------|------|--------|
| **Više prema više** | $M : N$ | Entitet jedne klase može biti povezan sa više entiteta druge klase i obrnuto | Radnik radi na više projekata, projekat ima više radnika |
| **Više prema jedan** | $N : 1$ | Entitet jedne klase može biti povezan sa najviše jednim entitetom druge klase | Radnik raspoređen na jedno radno mesto |
| **Jedan prema jedan** | $1 : 1$ | Entitet svake klase može biti povezan sa najviše jednim entitetom druge klase | Radnik ima jednu polisu osiguranja |

Ova podela je izuzetno bitna jer direktno utiče na formiranje ključeva tipa poveznika (o čemu ćemo govoriti u okviru integriteta tipa poveznika).

---

## 3. Predstavljanje kardinaliteta u ER dijagramima

### 3.1 Dva postupka navođenja kardinaliteta

U dijagramima entiteta i poveznika kardinalitet tipa poveznika se predstavlja navođenjem ili parova $(a_1, b_1)$ i $(a_2, b_2)$ ili samo maksimalnih vrednosti kardinaliteta $b_1$ i $b_2$ uz grafičku predstavu odgovarajućeg tipa entiteta.

Postoje **dva postupka** navođenja kardinaliteta u ER dijagramima:

**Prvi postupak:** Par $(a_1, b_1)$ se navodi na potegu uz tip entiteta $E_1$, a par $(a_2, b_2)$ se navodi na potegu uz tip entiteta $E_2$. Smisao ovog postupka navođenja kardinaliteta je da se minimalna i maksimalna brojnost podskupova, recimo, skupa entiteta $E_2$, u koje se može preslikati jedan element skupa entiteta $E_1$, javlja kao prva komponenta u skupu pojava tipa poveznika minimalno $a_2$ i maksimalno $b_2$ puta, a da se jedna pojava entiteta $E_2$ javlja kao druga komponenta u skupu pojava tipa poveznika minimalno $a_1$ i maksimalno $b_1$ puta.

**Drugi postupak:** Par $(a_1, b_1)$ se navodi na potegu uz tip entiteta $E_2$, a par $(a_2, b_2)$ se navodi na potegu uz tip entiteta $E_1$. Semantika ovog postupka predstavljanja je da se jedna pojava tipa entiteta $E_1$ javlja, kao prva komponenta u skupu pojava tipa poveznika minimalno $a_2$ i maksimalno $b_2$ puta, a da se jedna pojava entiteta $E_2$ javlja kao druga komponenta u skupu pojava tipa poveznika minimalno $a_1$ i maksimalno $b_1$ puta.

> [!NOTE]
> U jugoslovenskom informatičkom prostoru je u široj upotrebi **drugi postupak** (par $(a_1, b_1)$ se upisuje uz tip entiteta $N_i$) predstavljanja kardinaliteta tipa poveznika i to je jedini razlog što će se, u daljem tekstu, koristiti taj postupak.

### 3.2 Geometrijska predstava kardinaliteta

Neki put se u ER dijagramima parovi $(a, b)$ predstavljaju putem specijalnih geometrijskih simbola:

- **Minimalni kardinalitet $a = 0$** se predstavlja putem isprekidanog potega između tipa entiteta i tipa poveznika
- **Minimalni kardinalitet $a = 1$** se predstavlja punom linijom
- **Maksimalni kardinalitet $b = N$** se predstavlja račvanjem dela potega uz geometrijsku predstavu tipa entiteta, a $b = 1$ potegom koji nema račvu na svom kraju

**Primer 2.24.** Na slici 2.7 prikazan je ER dijagram sa kardinalitetima dobijenim upisivanjem dvojki $(a_i, b_i)$ uz tip entiteta $N_i$. Oba slučaja opisuju isti realni sistem, u kojem:

- radnik mora biti raspoređen na tačno jedno radno mesto i
- na jedno radno mesto može biti raspoređeno više radnika, ali mogu postojati radna mesta na koja nije niko raspoređen.

Slika 2.7 prikazuje: Radnik --(0,N)--> Raspoređen --(1,1)--> Radno_Mesto

Slika 2.8 prikazuje isti odnos ali sa zamenjenim stranama: Radnik --(1,1)--> Raspoređen --(0,N)--> Radno_Mesto

Teško je reći da bilo koji od opisanih postupaka predstavljanja kardinaliteta u ER dijagramima ima prednost nad drugim. Primena jednog, a ne drugog zavisi od ukusa i navika projektanta.

---

## 4. Karakteristične strukture ER modela podataka

Sada kada razumemo kardinalitete, hajde da pogledamo kako oni oblikuju ceo model. Analiza se polazi od karakteristične strukture, a zatim se interpretira kakav treba da bude veran model nekog njegovog dela. Pošto je opisano preslikavanje jedan na jedan, to znači da važi i obratno - na osnovu poznavanja karakteristika dela realnog sistema, može se izabrati odgovarajuća ER struktura, kao njegova verna slika.

### 4.1 Strukture sa kardinalitetima grupe $M : N$

Najopštiji slučaj kardinaliteta tipa poveznika opisuje se sa $R(E_1(a_2, M) : E_2(a_1, N))$, što se javlja kada, u realnom sistemu, jedan entitet klase $E_1$ može biti u vezi sa $M$ ($M > 1$) entiteta klase $E_2$ i kada isto važi i obratno. Tada se kaže da između dva tipa entiteta ($E_1$ i $E_2$) u modelu važi odnos **više - prema - više**, što se označava sa $M : N$.

Vrednosti minimalnih kardinaliteta definišu sledeće tri slučaja ovog odnosa:

#### Slučaj $a_1 = 0$ i $a_2 = 0$

Kada su oba minimalna kardinaliteta jednaka nuli, to znači da u obe klase mogu postojati entiteti koji nisu povezani sa bilo kojim entitetom druge klase. Međutim, i slučaj kada su svi entiteti posmatranih klasa međusobno povezani, nije zabranjen.

#### Slučaj $a_1 = 1$ i $a_2 = 0$ (ili $a_1 = 0$ i $a_2 = 1$)

Kada minimalni kardinaliteti ukazuju da svi entiteti jedne od povezanih klasa (recimo klase $E_1$) moraju biti povezani sa bar jednim entitetom druge klase (klase $E_2$). To dalje znači da je egzistencija entiteta u jednoj klasi ($E_1$) uslovljena njihovom povezanošću sa entitetima u drugoj klasi ($E_2$).

#### Slučaj $a_1 = 1$ i $a_2 = 1$

Kada su oba minimalna kardinaliteta jednaka jedinici, to znači da svaki entitet jedne klase mora biti povezan sa bar jednim entitetom druge klase. Egzistencija entiteta u obe klase uslovljena je njihovom povezanošću sa bar jednim entitetom druge klase, što predstavlja izuzetno strogo ograničenje.

**Primer 2.26.** U svojstvu primera odnosa $R(E_1(a_2, M) : E_2(a_1, N))$ mogu se posmatrati tipovi entiteta *Radnik*, *Projekat* i tip poveznika *Radi*. Maksimalni kardinaliteti tipa poveznika *Radi* su $M$ i $N$ ($M, N > 1$), što znači da jedan radnik može raditi na više projekata i da na jednom projektu može raditi više radnika.

> [!TIP]
> Na ispitu se često traži da se za dati opis realnog sistema odredi grupa kardinaliteta. Ključno pitanje je uvek: "Koliko **maksimalno** entiteta jedne klase može biti povezano sa jednim entitetom druge klase?" Ako je odgovor "više" sa obe strane, to je grupa $M : N$.

---

## 5. Ograničenje domena - formalna specifikacija (sa slajdova)

Sada ćemo pregledati formalniju specifikaciju ograničenja, kako je data u predavanjima, jer se to direktno pita na ispitu.

### 5.1 Specifikacija domena

**Specifikacija domena** je struktura:

$$D(id(D), Predef)$$

gde je:
- $D$ - naziv domena
- $id(D)$ - ograničenje domena
- $Predef$ - predefinisana vrednost domena (default)

### 5.2 Ograničenje domena $id(D)$ - pravilo nasleđivanja

Ograničenje domena se definiše primenom izabranog pravila za specificiranje korisnički definisanog domena. Ključni slučaj je **pravilo nasleđivanja**, gde je ograničenje "nasleđenog" domena struktura:

$$id(D) = (Tip, Dužina, Uslov)$$

- **Tip** - tip podatka (oznaka primitivnog domena ili prethodno korisnički definisanog domena). Jedina **obavezna** komponenta specifikacije. Nasleđuju se sva ograničenja, relacije i operacije definisane nad izabranim tipom.
- **Dužina** - dužina tipa podatka. Navodi se samo za tipove podataka (primitivne domene) koji to zahtevaju.
- **Uslov** - logički uslov koji svaka vrednost domena mora da zadovolji. U modelu podataka mora biti definisana sintaksa za zadavanje logičkih uslova.

### 5.3 Interpretacija integriteta domena - primeri

Pogledajmo konkretne primere specifikacije domena:

| Domen | Tip | Dužina | Uslov | Predef | Interpretacija |
|-------|-----|--------|-------|--------|----------------|
| DPREZIME | String | 30 | - | - | Niz do 30 znakova |
| DDATUM | Date | - | $d \geq$ '01.01.1900' | - | Datum ne stariji od 1900. |
| DOCENA | Number | 2 | $d \geq 5 \wedge d \leq 10$ | - | Ocena od 5 do 10 |
| DPOZOCENA | DOCENA | - | $d \geq 6$ | 6 | Pozitivna ocena (6-10), default 6 |

Obratimo pažnju na poslednji red: domen DPOZOCENA **nasleđuje** domen DOCENA i dodaje mu dodatno ograničenje ($d \geq 6$). To znači da DPOZOCENA automatski nasleđuje sve osobine domena DOCENA (dvocifreni broj od 5 do 10), ali dodaje i uslov da vrednost mora biti bar 6. Rezultat: dozvoljene vrednosti su $\{6, 7, 8, 9, 10\}$.

### 5.4 Nula vrednost - formalno

U formalnom smislu, nekada se javlja potreba da obeležje, umesto vrednosti iz domena, poprimi vrednost $\perp$ (nula vrednost - NULL). Njeno značenje može biti:

- **nepoznata vrednost** - vrednost postoji ali nam nije poznata
- **nepostojeća vrednost** - obeležje nema smisla za dati entitet
- **neinformativna vrednost** - vrednost nema informativni sadržaj

---

## 6. Ograničenje vrednosti obeležja

### 6.1 Specifikacija obeležja

Za obeležje $A \in Q$ datog tipa $N$, specifikacija je struktura:

$$(id(N, A), Predef)$$

gde je $id(N, A)$ ograničenje vrednosti obeležja, a $Predef$ predefinisana vrednost obeležja.

### 6.2 Ograničenje vrednosti obeležja $id(N, A)$

Ograničenje vrednosti obeležja se definiše za svako obeležje tipa i ima sledeću strukturu:

$$id(N, A) = (Domen, Null)$$

- **Domen** - oznaka (naziv) pridruženog domena obeležja
- **Null** $\in \{T, \perp\}$:
  - $T$ - dozvola dodele nula vrednosti obeležju unutar $N$
  - $\perp$ - zabrana dodele nula vrednosti obeležju unutar $N$

Obe komponente, Domen i Null, su **obavezne** komponente specifikacije.

Za Predef važi: ako se navede, onda je on važeći; u protivnom, važeći je Predef odgovarajućeg Domena, ili prvog sledećeg nasleđenog domena za koji je Predef definisan.

---

## 7. Ograničenje pojave tipa

### 7.1 Definicija

**Ograničenje pojave tipa** definiše ograničenja na moguće vrednosti podataka unutar iste pojave tipa entiteta ili tipa poveznika. Predstavlja skup ograničenja vrednosti obeležja, kojem je pridodat logički uslov.

Formalno, za tip $N$:

$$id(N) = (\{id(N, A) \mid A \in Q'\}, Uslov)$$

gde je:
- $Q'$ - prošireni skup obeležja tipa. Za tip entiteta je $Q' = Q$, a za tip poveznika je $Q' = Q \cup K_p$, gde je $K_p$ skup obeležja primarnog ključa tipa poveznika.
- **Uslov** - logički uslov koji svaka pojava tipa mora da zadovolji. Može, u ulozi operanda, da sadrži bilo koje obeležje proširenog skupa obeležja datog tipa.

### 7.2 Konkretan primer

Pogledajmo kompletnu specifikaciju ograničenja pojave tipa za tip entiteta Radnik:

**Radnik**({MBR, PRZ, IME, ZAN, BPJZ}, {MBR})

| Obeležje | Domen | Null | Predef |
|----------|-------|------|--------|
| MBR | DMBR | $\perp$ | - |
| PRZ | DPRZ | $\perp$ | - |
| IME | DIME | $\perp$ | - |
| ZAN | DZAN | $\perp$ | - |
| BPJZ | DBPJZ | T | - |

**Uslov:** $ZAN = \text{'prg'} \Rightarrow BPJZ \neq \perp$

Ovaj uslov kaže: ako je zanimanje radnika 'prg' (programer), onda mu broj poena za jezike znanja ne sme biti nula vrednost - mora biti poznat.

A domeni su definisani ovako:

| Domen | Tip | Dužina | Uslov | Predef |
|-------|-----|--------|-------|--------|
| DMBR | Number | 4 | $d \geq 1$ | - |
| DPRZ | String | 30 | - | - |
| DIME | String | 15 | - | - |
| DZAN | String | 3 | - | - |
| DBPJZ | Number | 2 | $d \geq 0$ | 0 |

> [!IMPORTANT]
> Na ispitu se često traži da se za dati tip entiteta napiše kompletna specifikacija ograničenja pojave tipa - uključujući tabelu obeležja sa domenima, Null vrednostima i predefinisanim vrednostima, tabelu domena, i logički uslov. Vežbajte ovo na različitim primerima!

---

## 8. Integritet tipa

### 8.1 Integritet tipa entiteta

**Integritet tipa entiteta** predstavlja ograničenje ključa. Svaki tip entiteta mora imati bar jedan ključ - minimalni interni identifikator koji jednoznačno identifikuje svaku pojavu.

### 8.2 Integritet tipa poveznika

**Integritet tipa poveznika** definiše se na osnovu niza naziva povezanih tipova, ili njegovog nepraznog podniza, i predstavlja ograničenje ključa tipa poveznika.

Ključ tipa poveznika se izvodi na osnovu ključeva povezanih tipova. Grupa kardinaliteta direktno određuje kako se formira ključ:

#### Grupa $M : N$ (više prema više)

Identifikator (ključ) tipa poveznika čini **unija ključeva oba povezana tipa**.

**Primer:** Tip poveznika Radi između Radnik i Projekat sa kardinalitetima $(0, M)$ i $(0, N)$:
- Identifikator TP Radi: (Radnik, Projekat)
- Primarni ključ: $K_p = Mbr + Spr$ (ključ Radnika + ključ Projekta)

#### Grupa $N : 1$ (više prema jedan)

Identifikator tipa poveznika čini **ključ tipa sa strane "više"** (strana koja ima maksimalni kardinalitet 1).

**Primer:** Tip poveznika Raspoređen između Radnik i Radno_Mesto sa kardinalitetima $(0, 1)$ i $(0, N)$:
- Identifikator TP Raspoređen: (Radnik)
- Primarni ključ: $K_p = Mbr$ (samo ključ Radnika)

Zašto? Jer svaki radnik može biti raspoređen na najviše jedno radno mesto, pa je Mbr dovoljan da jednoznačno identifikuje svaku pojavu tipa poveznika.

#### Grupa $1 : 1$ (jedan prema jedan)

Postoje **dva ekvivalentna ključa** - ključ bilo kog od dva povezana tipa može biti identifikator.

**Primer:** Tip poveznika JeOsiguran između Radnik i PolisaOsiguranja sa kardinalitetima $(0, 1)$ i $(0, 1)$:
- Identifikator TP JeOsiguran: (Radnik) **i** (PolisaOsiguranja)
- Ključevi: $K_1 = MBR$ i $K_2 = BrPol$ - oba su validni ključevi

#### Rekurzivni tip poveznika - grupa $M : N$

Kada je tip poveznika rekurzivan (povezuje isti tip entiteta sa samim sobom), identifikator se formira od ključa istog tipa entiteta, ali se jedno od obeležja mora **preimenovati** da bi se razlikovale uloge.

**Primer:** Tip poveznika Sastoji_se nad tipom entiteta Deo sa kardinalitetima $(0, M)$ i $(0, N)$:
- Identifikator: (Deo(Ima komponente), Deo(Je komponenta za))
- Primarni ključ: $K_p = DeID + DeIDkom$
- $DeIDkom$ je preimenovano obeležje $DeID$ - semantika: $DeID$ sa ulogom komponente ugradnje

> [!WARNING]
> Kod rekurzivnih tipova poveznika grupe $M:N$, obavezno je preimenovanje jednog od ključeva da bi se razlikovale dve uloge istog tipa entiteta u povezniku!

---

## 9. Pregled svih vrsta ograničenja - rezime

Da bismo zaokružili priču, hajde da sve ograničenja integritetne komponente ER modela sagledamo na jednom mestu:

| Vrsta ograničenja | Šta ograničava | Struktura |
|-------------------|----------------|-----------|
| **Ograničenje domena** | Skup dozvoljenih vrednosti za domen | $D(id(D), Predef)$, gde $id(D) = (Tip, Dužina, Uslov)$ |
| **Ograničenje vrednosti obeležja** | Domen i Null svojstvo obeležja | $id(N, A) = (Domen, Null)$ |
| **Ograničenje pojave tipa** | Vrednosti unutar jedne pojave | $id(N) = (\{id(N,A) \mid A \in Q'\}, Uslov)$ |
| **Kardinalitet TP** | Brojnost učešća pojava u povezniku | Par $(a, b)$, gde $a \in \{0,1\}$, $b \in \{1, N\}$ |
| **Integritet tipa (ključ)** | Jednoznačna identifikacija pojava | Ključ TE i ključ TP (zavisi od grupe kardinaliteta) |

---

## 🎴 Brza pitanja (definicije i pojmovi)

**P:** Šta je integritet domena i od kojih komponenti se sastoji trojka ograničenja domena?

**P:** Koje su tri vrste ograničenja u integritetnoj komponenti ER modela podataka?

**P:** Šta je nula vrednost i koja su njena dva najčešća značenja?

**P:** Šta je kardinalitet tipa poveznika i u kom obliku se zapisuje?

**P:** Šta označava minimalni kardinalitet $a = 1$ (egzistencijalno ograničenje)?

**P:** Koje su tri grupe maksimalnih kardinaliteta tipa poveznika?

**P:** Šta je ograničenje pojave tipa i čime se razlikuje prošireni skup obeležja $Q'$ za tip entiteta od tipa poveznika?

**P:** Kako se formira ključ tipa poveznika za grupu kardinaliteta $M : N$?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite razliku između prostih i složenih regularnih izraza za izražavanje ograničenja domena. Navedite primere za oba slučaja.

**O:** Prosti regularni izrazi koriste jedan operator poređenja $\theta$ iz skupa $\{<, >, \leq, \geq, \neq, =\}$ sa konstantom $k$ u obliku $(\theta k)$, ili nabrajanje dozvoljenih vrednosti u obliku $(k_1, k_2, ..., k_n)$. Na primer, $(< 11)$ ili $(6, 7, 8, 9, 10)$ za ocenu. Složeni regularni izrazi kombinuju proste (ili druge složene) izraze putem logičkih operatora $\wedge$, $\vee$ i $\neg$. Na primer, $> 5 \wedge < 11$ je složeni izraz koji ograničava ocenu na opseg 6-10 kombinovanjem dva prosta uslova.

**P:** Za tip poveznika Raspoređen između tipova entiteta Radnik (ključ MBR) i Radno_Mesto (ključ ORM), sa kardinalitetima (1,1) uz Radnik i (0,N) uz Radno_Mesto, odredite ključ tipa poveznika i obrazložite zašto.

**O:** Ovo je grupa kardinaliteta $N : 1$ (više prema jedan), jer uz Radnik stoji maksimalni kardinalitet 1 (svaki radnik raspoređen na tačno jedno radno mesto), a uz Radno_Mesto stoji $N$ (na jedno radno mesto može više radnika). Ključ tipa poveznika je $K_p = MBR$ - samo ključ sa strane "jedan" (Radnik), jer svaki radnik učestvuje u najviše jednoj pojavi ovog poveznika, pa je MBR dovoljan za jednoznačnu identifikaciju svake pojave tipa poveznika Raspoređen.

**P:** Data je specifikacija domena DOCENA kao (Number, 2, $d \geq 5 \wedge d \leq 10$). Nad njim se definiše domen DPOZOCENA sa dodatnim uslovom $d \geq 6$ i predefinisanom vrednošću 6. Koji je skup dozvoljenih vrednosti za DPOZOCENA i zašto?

**O:** Domen DPOZOCENA nasleđuje sve osobine domena DOCENA, dakle dvocifreni broj sa uslovom $d \geq 5 \wedge d \leq 10$. Tome se dodaje dodatni uslov $d \geq 6$. Kombinovanjem ovih uslova (presek), dobijamo: $d \geq 6 \wedge d \leq 10$, pa je skup dozvoljenih vrednosti $\{6, 7, 8, 9, 10\}$. Predefinisana vrednost je 6, što znači da ako se ne navede konkretna ocena, automatski se dodeljuje vrednost 6.

**P:** Objasnite šta se dešava sa ključem tipa poveznika kod rekurzivnog tipa poveznika grupe $M:N$ i zašto je potrebno preimenovanje obeležja.

**O:** Kod rekurzivnog tipa poveznika, isti tip entiteta se pojavljuje u dve različite uloge. Na primer, tip entiteta Deo u tipu poveznika Sastoji_se ima uloge "Ima komponente" i "Je komponenta za". Pošto je ključ Deo-a isti (DeID), ne mogu obe pojave u ključu tipa poveznika koristiti isto ime obeležja. Zato se jedno od njih preimenovuje - nastaje $K_p = DeID + DeIDkom$, gde DeIDkom nosi semantiku "identifikator dela koji je komponenta ugradnje". Bez preimenovanja, ne bismo mogli razlikovati koja pojava Deo-a igra koju ulogu u konkretnoj pojavi tipa poveznika.

**P:** Napišite kompletnu specifikaciju ograničenja vrednosti obeležja za tip entiteta Student(BRI, IME, PRZ, GOD_STUD), ako znamo da je BRI ključ, godina studija može biti od 1 do 6, a sva obeležja su obavezna.

**O:** Ograničenja vrednosti obeležja: BRI - (DBRI, $\perp$), IME - (DIME, $\perp$), PRZ - (DPRZ, $\perp$), GOD_STUD - (DGOD, $\perp$). Sva imaju $Null = \perp$ jer su obavezna. Domeni: DBRI - (Number, 5, $d \geq 1$), DIME - (String, 20, -), DPRZ - (String, 30, -), DGOD - (Number, 1, $d \geq 1 \wedge d \leq 6$). Domen DGOD koristi složeni regularni izraz koji kombinuje dva uslova logičkim "i" ($\wedge$) da ograniči godinu studija na opseg od 1 do 6.
