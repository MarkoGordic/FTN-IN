# Integritetna komponenta u relacionom modelu podataka

## Uvod - zašto nam trebaju ograničenja?

Zamislimo da imamo bazu podataka jednog fakulteta. U njoj čuvamo podatke o studentima, predmetima, ocenama. Sve radi savršeno - dok neko ne unese studenta bez matičnog broja. Ili ne upiše ocenu 15, što nema smisla. Ili ne obriše predmet na koji su studenti prijavljeni. Odjednom, naša baza postaje haos.

Upravo tu na scenu stupa **integritetna komponenta** relacionog modela podataka. Ona predstavlja skup pravila koja štite bazu od besmislenih, nekonzistentnih ili kontradiktornih podataka. Bez nje, baza bi bila kao rečnik bez pravopisa - svako piše šta hoće.

Hajde da se podsetimo gde se integritetna komponenta uklapa u širu sliku. Relacioni model podataka ima tri komponente:

- **Strukturalna komponenta** - definiše "gradivne blokove" (obeležja, domeni, torke, relacije, šeme)
- **Operacijska komponenta** - definiše operacije nad podacima (upiti, ažuriranje)
- **Integritetna komponenta** - definiše ograničenja nad podacima u bazi

**Integritetna komponenta** je, dakle, **skup tipova ograničenja (uslova integriteta)** koji služi za modeliranje ograničenja nad podacima u bazi podataka. Ona obezbeđuje da podaci u bazi uvek budu u konzistentnom stanju.

> [!IMPORTANT]
> Integritetna komponenta = skup tipova ograničenja (uslova integriteta), koji služi za modeliranje ograničenja nad podacima u bazi podataka.

---

## Karakteristike tipa ograničenja

Svako ograničenje u relacionom modelu ima jasno definisane karakteristike. Pre nego što uđemo u konkretne tipove ograničenja, hajde da razumemo šta svako ograničenje mora da ima "u ličnoj karti":

1. **Formalizam za zapisivanje (definicija)** - kako se ograničenje formalno zapisuje
2. **Pravilo za interpretaciju (validaciju)** - kako se proverava da li je ograničenje zadovoljeno
3. **Oblast definisanosti** - tip logičke strukture obeležja nad kojom se ograničenje definiše (nivo intenzije, tj. šeme)
4. **Oblast interpretacije** - tip logičke strukture podataka nad kojom se ograničenje interpretira (nivo ekstenzije, tj. konkretnih podataka)
5. **Skup operacija** koje mogu dovesti do narušavanja ograničenja datog tipa
6. **Skup mogućih akcija** kojima se obezbeđuje očuvanje validnosti baze podataka, pri pokušaju narušavanja ograničenja datog tipa - definiše se za svaku operaciju koja može dovesti do narušavanja

### Kako SUBP kontroliše ograničenja?

Kontrola ograničenja implementiranih na nivou SUBP-a je **centralna** - ne može je zaobići nijedan program ni korisnik. Korisnici obično nisu ni svesni da ograničenja postoje, sve dok ne pokušaju da ih naruše.

Kada neka operacija ažuriranja pokuša da naruši ograničenje, SUBP može reagovati na dva načina:

- **Izaziva grešku i prekida operaciju** - prosleđuje korisničkom programu poruku o grešci, a program obrađuje tu poruku i prosleđuje je korisniku
- **Aktivnim mehanizmom dovodi stanje BP u konzistentno** - automatski, nakon izvođenja kritične operacije za ograničenje

---

## Oblast definisanosti ograničenja

Oblast definisanosti govori nam **nad kojom strukturom šeme** se ograničenje definiše. Postoje tri nivoa:

### Vanrelaciono ograničenje
Definiše se **izvan konteksta šeme relacije**. Na primer, ograničenje domena je vanrelaciono - domen se definiše nezavisno od bilo koje šeme relacije.

### Jednorelaciono (unutarrelaciono, lokalno) ograničenje
Definiše se **nad tačno jednom šemom relacije**. Na primer, ograničenje ključa - definišemo ga unutar jedne konkretne šeme relacije.

### Višerelaciono ograničenje
Definiše se **nad skupom ili nizom šema relacija, koji sadrži bar dva člana**. Tipičan primer je zavisnost sadržavanja i referencijalni integritet - oni povezuju dve šeme relacija.

---

## Oblast interpretacije ograničenja

Dok oblast definisanosti govori gde se ograničenje *definiše* (na nivou šeme), oblast interpretacije govori nad čime se ograničenje *proverava* (na nivou konkretnih podataka). Postoje četiri nivoa:

| Oblast interpretacije | Interpretira se nad... |
|---|---|
| **Ograničenje vrednosti** | tačno jednom vrednošću nekog obeležja |
| **Ograničenje torke** | jednom torkom bilo koje relacije |
| **Relaciono ograničenje** | skupom torki bilo koje relacije |
| **Međurelaciono ograničenje** | barem dve, bilo koje relacije |

Napomena o izrazu "bilo koja relacija" - to može biti jedna relacija iz baze podataka, ili relacija koja je nastala primenom izraza relacione algebre nad jednom ili više drugih relacija (pogled). Moguća je i primena operatora spajanja.

> [!TIP]
> Na ispitu se često pita razlika između oblasti definisanosti i oblasti interpretacije. Ključ je u tome da je definisanost vezan za nivo šeme (intenzije), a interpretacija za nivo podataka (ekstenzije).

---

## Tipovi ograničenja u relacionom modelu

Sada dolazimo do srca cele priče. Relacioni model definiše sledeće tipove ograničenja:

1. Ograničenje domena
2. Ograničenje vrednosti obeležja
3. Ograničenje torke
4. Integritet entiteta (ograničenje ključa)
5. Ograničenje jedinstvenosti vrednosti obeležja
6. Zavisnost sadržavanja
7. Ograničenje referencijalnog integriteta
8. Funkcionalna zavisnost

Hajde da svaki od njih detaljno obradimo.

---

## Ograničenje domena

Domen je skup mogućih vrednosti koje neka obeležja mogu da dobiju. Zamislimo domen kao "kalup" koji kaže: "Ovde mogu da stanu samo vrednosti ovog oblika."

### Specifikacija domena

Domen se formalno specificira kao:

$$D(id(D), Predef)$$

gde je:
- $D$ - naziv domena
- $id(D)$ - ograničenje (integritet) domena
- $Predef$ - predefinisana vrednost domena (default vrednost)

### Ograničenje domena

Samo ograničenje domena ima oblik:

$$id(D) = (Tip, Dužina, Uslov)$$

gde je:
- $Tip$ - tip podatka (primitivni domen) ili oznaka prethodno definisanog domena
- $Dužina$ - dužina tipa podatka
- $Uslov$ - logički uslov koji mora da zadovolji svaka vrednost iz skupa mogućih vrednosti domena

Nekoliko pravila vezanih za komponente:

- **Tip** je jedina obavezna komponenta specifikacije ograničenja domena
- **Dužina** se navodi samo za tipove podataka (primitivne domene) koji to zahtevaju; ne navodi se za domene čiji tip ne predstavlja primitivni domen
- **Uslov** mora da ga zadovoljava svaka vrednost iz skupa mogućih vrednosti domena
- **Predef** mora da zadovolji ograničenja tipa, dužine i uslova

**Interpretacija ograničenja** je moguća za bilo koju vrednost (konstantu) $d$. Oznaka: $id(D)(d)$.

### Primeri specifikacije domena

Hajde da pogledamo konkretne primere. Simbol $\bot$ znači da komponenta u specifikaciji nije zadata:

| Domen | Specifikacija | Objašnjenje |
|---|---|---|
| $DPrezime$ | $(String, 30, \bot), \bot$ | String dužine 30, bez uslova, bez predefinisane vrednosti |
| $DDatum$ | $(Date, \bot, d \geq '01.01.1900'), \bot$ | Datum koji mora biti posle 1.1.1900. |
| $DOcena$ | $(Number, 2, d \geq 5 \land d \leq 10), \bot$ | Broj od 2 cifre, vrednost između 5 i 10 |
| $DPozOcena$ | $(DOcena, \bot, d \geq 6), 6$ | Nasleđuje domen DOcena, dodatni uslov $d \geq 6$, predefinisana vrednost je 6 |

Obratimo pažnju na poslednji primer - domen $DPozOcena$ se poziva na prethodno definisani domen $DOcena$. To znači da domeni mogu biti hijerarhijski organizovani.

> [!NOTE]
> Oblast definisanosti ograničenja domena je vanrelaciona - domen se definiše nezavisno od šeme relacije. Oblast interpretacije je ograničenje vrednosti - proverava se za svaku pojedinačnu vrednost.

---

## Nula (nedostajuća) vrednost

Pre nego što nastavimo sa ograničenjima obeležja, moramo da se upoznamo sa jednim posebnim konceptom - **nula vrednošću**.

**Nula vrednost** je specijalna vrednost koja se označava posebnim simbolom: $\omega$ (ili $?$ u literaturi, ili `NULL` u SQL-u).

Nula vrednost može imati tri značenja:

- **Nepoznata** - postojeća vrednost obeležja, ali trenutno nepoznata (npr. ne znamo broj telefona studenta, ali on sigurno ima telefon)
- **Nepostojeća** vrednost obeležja (npr. broj faksa za osobu koja nema faks)
- **Neinformativna** vrednost obeležja (npr. podatak koji za dati kontekst nema smisla)

Skup mogućih vrednosti svih domena se proširuje nula vrednošću:

$$DOM \cup \{\omega\}$$

Nula vrednost **a priori zadovoljava svako ograničenje domena**. To je logično - ako ne znamo vrednost, ne možemo ni reći da ona krši neko pravilo.

> [!WARNING]
> Studenti često mešaju NULL sa nulom (0) ili praznim stringom (""). NULL nije ni jedno ni drugo - to je specijalna oznaka za nedostajuću informaciju.

---

## Ograničenje vrednosti obeležja

Sada prelazimo na nivo konkretnog obeležja unutar šeme relacije. Svako obeležje $A$ u šemi relacije $N(R, O)$ ima svoju specifikaciju:

$$(id(N, A), Predef)$$

gde je:
- $id(N, A)$ - ograničenje vrednosti obeležja
- $Predef$ - predefinisana vrednost obeležja

### Ograničenje vrednosti obeležja

$$id(N, A) = (Domen, Null)$$

gde je:
- $Domen$ - oznaka (naziv) domena obeležja
- $Null \in \{T, \bot\}$ - ograničenje nula vrednosti obeležja:
  - $T$ - **dozvola** dodele nula vrednosti obeležju u $r(N)$
  - $\bot$ - **zabrana** dodele nula vrednosti obeležju u $r(N)$

Obe komponente ($Domen$ i $Null$) su **obavezne** u specifikaciji.

Za predefinisanu vrednost ($Predef$) važi: ako se navede, onda je on važeći; u protivnom, važeći je $Predef$ odgovarajućeg domena, ili prvog sledećeg nasleđenog domena za koji je $Predef$ definisan.

**Interpretacija ograničenja** je moguća za bilo koju vrednost obeležja $d$. Oznaka: $id(N, A)(d)$.

### Primer - specifikacija obeležja

Pogledajmo šemu relacije:

$$Radnik(\{MBR, PRZ, IME, ZAN, BPJZ\}, O)$$

Specifikacija obeležja data je u tabeli:

| Radnik | Domen | Null | Predef |
|---|---|---|---|
| MBR | MBRD | $\bot$ | $\bot$ |
| PRZ | PRZD | $\bot$ | $\bot$ |
| IME | IMED | $\bot$ | $\bot$ |
| BPJZ | BPJZD | $T$ | $\bot$ |
| ZAN | ZAND | $\bot$ | $\bot$ |

A domeni su definisani ovako:

| Domen | Tip | Dužina | Uslov | Predef |
|---|---|---|---|---|
| MBRD | Number | 4 | $d > 0$ | $\bot$ |
| PRZD | String | 30 | $\bot$ | $\bot$ |
| IMED | String | 15 | $\bot$ | $\bot$ |
| BPJZD | Number | 2 | $d > 0$ | 0 |
| ZAND | String | 3 | $\bot$ | $\bot$ |

Čitamo ovako: MBR (matični broj) je broj od 4 cifre, veći od 0, ne sme biti NULL. BPJZ (broj projekata za zanimanje) je broj od 2 cifre, veći od 0, ali sme biti NULL, sa predefinisanom vrednošću 0 iz domena.

---

## Ograničenje torke

Ograničenje torke ide korak dalje od ograničenja pojedinačnog obeležja - ono izražava **ograničenja na moguće vrednosti unutar jedne torke**. To znači da možemo postaviti pravilo koje povezuje vrednosti više obeležja unutar iste torke.

Formalno, za šemu relacije $N(R, O)$:

$$id(N) = id(R) = (\{id(N, A) \mid A \in R\}, Uslov)$$

Ograničenje torke je skup ograničenja vrednosti obeležja, kojem je pridodat **logički uslov** ($Uslov$):

- $Uslov$ je logički uslov koji svaka torka mora da zadovolji
- Može, u ulozi operanda, da sadrži bilo koje obeležje date šeme relacije
- **Interpretacija** je moguća za bilo koju torku nad skupom obeležja $R$: $id(N)(t)$

### Primer

Pogledajmo šemu relacije Radnik iz prethodnog primera. Uslov torke je:

$$ZAN = 'prg' \Rightarrow BPJZ \neq \omega$$

Ovo pravilo kaže: ako je zanimanje radnika 'prg' (programer), onda BPJZ (broj projekata za zanimanje) **ne sme** biti nula vrednost. Dakle, za programere moramo uvek znati broj projekata. Za ostala zanimanja taj podatak može biti nepoznat (NULL).

> [!IMPORTANT]
> Ograničenje torke obuhvata ograničenja svih obeležja plus logički uslov. Ono se proverava nad svakom torkom pojedinačno - ne nad celom relacijom.

---

## Skup svih ograničenja šeme relacije

Kada šemu relacije treba implementirati u datom SUBP-u, kompletan skup ograničenja zadaje se kao unija:

$$N(R, K \cup Uniq \cup \{id(R)\})$$

gde je:
- $K$ - skup ključeva
- $Uniq$ - skup ograničenja jedinstvenosti
- $\{id(R)\}$ - ograničenje torke

### Primer

$$Radnik(\{MBR, PRZ, IME, ZAN, BPJZ, JMBG\}, K \cup Uniq \cup \{id(R)\})$$

- $K = \{MBR\}$
- $Uniq = \{Unique(Radnik, JMBG)\}$
- $id(R)$ - prethodno zadat u tabelarnom obliku

---

## Ključ šeme relacije

Ključ je jedan od najbitnijih koncepata u celom relacionom modelu. On nam omogućava da jednoznačno identifikujemo svaku torku u relaciji - slično kao što JMBG jednoznačno identifikuje svaku osobu.

**Ključ šeme relacije** je **minimalni podskup skupa obeležja šeme relacije, na osnovu kojeg se jedinstveno može identifikovati svaka torka relacije nad datom šemom**.

Formalno, $X$ je ključ ako važi:

$$1^0 \quad (\forall u, v \in r(R))(u[X] = v[X] \Rightarrow u = v)$$

$$2^0 \quad (\nexists Y \subset X)(1^0)$$

Prvo pravilo ($1^0$) kaže: ako dve torke imaju iste vrednosti za obeležja ključa, onda su to iste torke. Drugo pravilo ($2^0$) kaže: ne postoji manji podskup od $X$ sa istom osobinom - ključ mora biti **minimalan**.

Oblast interpretacije ključa je skup torki (relacija) nad datom šemom relacije.

U određenim situacijama (u procesu projektovanja šeme BP), skup ograničenja šeme relacije zadaje se samo kao skup ključeva:

$$N(R, K)$$

### Primer

Šema relacije $Radnik(R, K)$:

- $R = \{MBR, IME, PRZ, DATR, POL, MESR, RBRE\}$
- $K = \{MBR, \; DATR + MESR + POL + RBRE\}$

Ova šema ima **dva ekvivalentna ključa**: $MBR$ sam za sebe, i kombinacija $DATR + MESR + POL + RBRE$. Svaki od njih može jednoznačno identifikovati radnika.

Još jedan primer sa više šema relacija:

- $Radnik(\{MBR, IME, PRZ, DATR\}, \{MBR\})$
- $Projekat(\{SPR, NAP\}, \{SPR\})$
- $Angažovanje(\{SPR, MBR, BRC\}, \{SPR + MBR\})$

Kod relacije Angažovanje, ključ je kombinacija $SPR + MBR$ - radnik se na istom projektu ne može angažovati više od jedanput.

---

## Ograničenje ključa (integritet entiteta)

Ograničenje ključa, poznato i kao **integritet entiteta**, uvodi dva pravila za šemu relacije $N(R, K)$:

Za ključ $X \in K$, $X \subseteq R$, označavamo:

$$Key(N, X)$$

Ovo ograničenje obezbeđuje dve stvari:

**Prvo**, svaka šema relacije mora posedovati **najmanje jedan ključ** ($K \neq \emptyset$). To direktno proizilazi iz definicije pojma relacije - pošto relacija ne može imati dve identične torke, uvek postoji bar neki podskup obeležja koji ih razlikuje.

**Drugo**, za sva obeležja ključa, nula vrednosti su **zabranjene**:

$$(\forall K_i \in K)(\forall A \in K_i)(Null(N, A) = \bot)$$

Ovo znači da nijednom obeležju koje pripada nekom ključu ne smemo dodeliti NULL. Logika je jasna - ako ključ treba da identifikuje torku, ne smemo dozvoliti da deo te identifikacije bude nepoznat.

### Primarni ključ

Pošto šema relacije može imati više ekvivalentnih ključeva, jedan od njih biramo kao **primarni ključ**:

- Oznaka: $K_p(N)$
- Svaka šema relacije treba da poseduje **tačno jedan** primarni ključ
- Koristi se u ulozi **asocijativne (simboličke) adrese** za povezivanje podataka u relacijama

> [!IMPORTANT]
> Integritet entiteta zahteva dve stvari: (1) svaka šema relacije mora imati bar jedan ključ, i (2) obeležja ključa nikada ne smeju imati NULL vrednost. Ovo se vrlo često pita na ispitu.

---

## Ograničenje jedinstvenosti vrednosti obeležja

Ograničenje jedinstvenosti (Uniqueness Constraint) je slično ograničenju ključa, ali sa jednom bitnom razlikom - **dozvoljava nula vrednosti**.

Za šemu relacije $N(R, O)$:

$$Unique(N, X)$$

gde je $X$ skup obeležja, $X \subseteq R$.

Ovo ograničenje zahteva da **ne-nula kombinacija vrednosti** obeležja bude jedinstvena u relaciji nad $N(R, O)$.

Formalno:

$$(\forall u, v \in r(R))((\forall A \in X)(u[A] \neq \omega \land v[A] \neq \omega) \Rightarrow (u[X] = v[X] \Rightarrow u = v))$$

Oblast interpretacije je skup torki (relacija) nad datom šemom $N(R, O)$.

Skup svih ograničenja jedinstvenosti u šemi $N(R, O)$:

$$Uniq = \{Unique(N, X) \mid X \subseteq R\}$$

### Primer

$$Radnik(\{MBR, IME, PRZ, DATR, JMBG\}, O)$$

$$Uniq \subseteq O$$

$$Uniq = \{Unique(Radnik, JMBG)\}$$

$Unique(Radnik, JMBG)$ zahteva da ako radnik poseduje ne-nula vrednost za JMBG, onda je ta vrednost jedinstvena u relaciji nad šemom Radnik. Ali - za razliku od ključa - JMBG sme biti NULL za neke radnike.

> [!WARNING]
> Ne mešajte ključ i ograničenje jedinstvenosti! Ključ zabranjuje NULL vrednosti za svoja obeležja, dok ograničenje jedinstvenosti to dozvoljava. Jedinstvenost se proverava samo za ne-nula vrednosti.

---

## Zavisnost sadržavanja

Sada prelazimo na ograničenja koja se protežu preko više relacija. **Zavisnost sadržavanja** je mehanizam koji kaže: "Vrednosti u jednoj relaciji moraju postojati i u drugoj."

Zamislimo to ovako: ako u tabeli Angažovanje imamo MBR = 101, onda radnik sa tim matičnim brojem mora postojati u tabeli Radnik. Ne možemo angažovati nepostojećeg radnika.

### Formalna definicija

Date su šeme relacije $N_i(R_i, O_i)$ i $N_j(R_j, O_j)$.

Dati su **domenski kompatibilni nizovi obeležja**:

$$X = (A_1, \ldots, A_n), \quad (\forall l \in \{1, \ldots, n\})(A_l \in R_i)$$

$$Y = (B_1, \ldots, B_n), \quad (\forall l \in \{1, \ldots, n\})(B_l \in R_j)$$

$$(\forall l \in \{1, \ldots, n\})(dom(A_l) \supseteq dom(B_l))$$

Oznaka (pravilo zapisivanja):

$$N_i[X] \subseteq N_j[Y]$$

Zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$ **važi** ako je za bilo koje dve relacije $r(R_i, O_i)$ i $s(R_j, O_j)$ zadovoljeno:

$$(\forall u \in r)(\exists v \in s)(\forall l \in \{1, \ldots, n\})(u[A_l] = \omega \lor u[A_l] = v[B_l])$$

Ovo znači: za svaku torku u referencirajućoj relaciji, ako njena vrednost za neko obeležje nije NULL, onda mora postojati torka u referenciranoj relaciji sa istom vrednošću.

**Oblast definisanosti** je niz od dve šeme relacije. **Oblast interpretacije** su relacije nad šemama $N_i$ i $N_j$.

### Primer 1 - jedno obeležje

Neka važi zavisnost sadržavanja $N_i[B] \subseteq N_j[B]$:

| r(Ni) - A | r(Ni) - B | | s(Nj) - B | s(Nj) - C |
|---|---|---|---|---|
| a1 | b1 | | b1 | c1 |
| a2 | b2 | | b2 | c1 |
| | | | b3 | c2 |

Proveravamo: sve vrednosti B iz relacije $r$ (b1, b2) moraju postojati u koloni B relacije $s$. Jeste - b1 i b2 postoje u $s$. Ograničenje je zadovoljeno.

### Primer 2 - niz obeležja

Neka važi zavisnost sadržavanja $N_i[(A, B)] \subseteq N_j[(C, D)]$:

| r(Ni) - A | r(Ni) - B | | s(Nj) - C | s(Nj) - D |
|---|---|---|---|---|
| a1 | b1 | | a1 | b1 |
| a2 | $\omega$ | | a2 | b2 |
| | | | a3 | b2 |

Za torku (a1, b1): oba obeležja su ne-nula, pa mora postojati (a1, b1) u $s$ - postoji. Za torku (a2, $\omega$): B je NULL, pa se ta vrednost ne proverava (uslov je automatski zadovoljen). Ograničenje važi.

---

## Ograničenje referencijalnog integriteta

Ograničenje referencijalnog integriteta je **specijalan slučaj zavisnosti sadržavanja**. Razlika je u tome što kod referencijalnog integriteta, niz obeležja $Y$ u referenciranoj relaciji mora biti **ključ** te relacije.

Formalno, zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$ postaje ograničenje referencijalnog integriteta kada je **$Y$ ključ šeme relacije $N_j(R_j, K_j)$**.

- $N_i$ je **referencirajuća** šema relacije (ona koja "pokazuje" na drugu)
- $N_j$ je **referencirana** šema relacije (ona na koju se pokazuje)

### Primer

Posmatrajmo tri šeme relacija:

- $Radnik(\{MBR, IME, PRZ, DATR\}, \{MBR\})$
- $Projekat(\{SPR, NAP, RUK\}, \{SPR\})$
- $Angažovanje(\{SPR, MBR, BRC\}, \{SPR + MBR\})$

Ograničenja referencijalnog integriteta:

- $Projekat[RUK] \subseteq Radnik[MBR]$ - rukovodilac projekta mora biti postojeći radnik
- $Angažovanje[MBR] \subseteq Radnik[MBR]$ - angažovani radnik mora postojati u tabeli Radnik
- $Angažovanje[SPR] \subseteq Projekat[SPR]$ - projekat na kome se radnik angažuje mora postojati

Konkretno stanje baze:

**Radnik:**

| MBR | IME | PRZ | DATR |
|---|---|---|---|
| 101 | Ana | Pap | 12.12.85. |
| 102 | Aca | Tot | 13.11.88. |
| 110 | Ivo | Ban | 01.01.79. |
| 111 | Olja | Kun | 06.05.81. |

**Projekat:**

| SPR | NAP | RUK |
|---|---|---|
| 11 | X25 | 101 |
| 13 | Polaris | 101 |
| 14 | Univ.IS | 111 |

**Angažovanje:**

| SPR | MBR |
|---|---|
| 11 | 101 |
| 14 | 101 |
| 14 | 111 |

### Šta se dešava pri ažuriranju?

Hajde da prođemo kroz tri operacije i vidimo kako referencijalni integritet reaguje:

**Unos novog projekta:** Želimo da dodamo projekat (15, P7, 110). Proveravamo $Projekat[RUK] \subseteq Radnik[MBR]$: da li radnik sa MBR=110 postoji? Da, to je Ivo Ban. Unos je dozvoljen.

**Angažovanje radnika na projektu:** Želimo da dodamo angažovanje (15, 110). Proveravamo dve zavisnosti: da li radnik MBR=110 postoji u Radnik? Da. Da li projekat SPR=15 postoji u Projekat? Da (upravo smo ga dodali). Unos je dozvoljen.

**Brisanje radnika:** Želimo da obrišemo radnika sa MBR=102 (Aca Tot). Da li je MBR=102 referenciran u Projekat.RUK? Ne. U Angažovanje.MBR? Ne. Brisanje je dozvoljeno.

Ali - ako pokušamo da obrišemo radnika sa MBR=110 (Ivo Ban), on je referenciran kao RUK u projektu 15 i u tabeli Angažovanje. SUBP će to sprečiti.

> [!CAUTION]
> Na ispitu se vrlo često traži da se za dato stanje baze proveri da li neka operacija (INSERT, DELETE, UPDATE) narušava referencijalni integritet. Uvek proverite sve zavisnosti sadržavanja!

---

## Funkcionalna zavisnost (FZ)

Funkcionalna zavisnost je ograničenje koje kaže: "Ako znam vrednost jednog skupa obeležja, znam i vrednost drugog." Ovo je temelj na kome se gradi cela teorija projektovanja baze podataka.

### Definicija

Funkcionalna zavisnost je izraz oblika:

$$f: X \rightarrow Y$$

gde su:
- $f$ - oznaka funkcionalne zavisnosti
- $X$ i $Y$ - podskupovi skupa obeležja $U$
- Oznaka $f$ se u notaciji često izostavlja

**Semantika:**
- Ako je poznata $X$ vrednost, poznata je i $Y$ vrednost
- Svakoj $X$ vrednosti odgovara samo jedna $Y$ vrednost

Relacija $r$ **zadovoljava** FZ $X \rightarrow Y$ ako važi:

$$(\forall u, v \in r)(u[X] = v[X] \Rightarrow u[Y] = v[Y])$$

Oblast interpretacije je relacija $r(N)$ ili $r(U)$.

### Primer

$MBR \rightarrow IME$ - ako dve torke imaju istu vrednost za MBR, moraju imati istu vrednost i za IME. To je logično - jedan matični broj pripada jednom radniku sa jednim imenom.

Skup FZ se označava sa $F$:

$$F = \{MBR \rightarrow IME, \; MBR + MES + GOD \rightarrow BRC, \ldots\}$$

### Trivijalna FZ

**Trivijalna FZ** je svaka FZ koja je zadovoljena u **bilo kojoj** relaciji. To je svaka FZ $X \rightarrow Y$, za koju važi $Y \subseteq X$.

Primeri trivijalnih FZ: $MBR \rightarrow MBR$, $MBR \rightarrow \emptyset$, $AB \rightarrow A$, ...

### Veliki primer - relacija Student

Pogledajmo relaciju sa sledećim obeležjima:
- $BRI$ - broj indeksa
- $IME$ - ime studenta
- $PRZ$ - prezime studenta
- $BPI$ - broj položenih ispita
- $OZP$ - oznaka predmeta
- $NAP$ - naziv predmeta
- $NAS$ - prezime nastavnika
- $OCE$ - ocena na ispitu

Konkretni podaci:

| BRI | IME | PRZ | BPI | OZP | NAP | NAS | OCE |
|---|---|---|---|---|---|---|---|
| 159 | Ivo | Ban | 13 | P1 | Mat | Han | 09 |
| 159 | Ivo | Ban | 13 | P2 | Fiz | Kun | 08 |
| 013 | Ana | Tot | 09 | P1 | Mat | Pap | 06 |
| 119 | Eva | Kon | 15 | P3 | Hem | Kiš | 07 |
| 159 | Ivo | Ban | 13 | P3 | Hem | Kiš | 10 |
| 119 | Eva | Kon | 15 | P1 | Mat | Han | 09 |
| 159 | Ivo | Ban | 13 | P4 | Mat | Car | 10 |
| 037 | Eva | Tot | 01 | P4 | Mat | Car | 10 |

Relacija Student **zadovoljava** sledeće FZ:

$$F = \{BRI \rightarrow IME + PRZ + BPI, \; IME + PRZ \rightarrow BRI, \; OZP \rightarrow NAP, \; NAS \rightarrow OZP + NAP, \; BRI + OZP \rightarrow OCE + NAS\}$$

Relacija Student **ne zadovoljava** sledeće FZ: $BRI \rightarrow OCE$, $OZP \rightarrow NAS$, ...

Na primer, $BRI \rightarrow OCE$ ne važi jer student 159 (Ivo Ban) ima različite ocene (09, 08, 10, 10) na različitim predmetima.

Način identifikacije važećih FZ: na osnovu odnosa i pravila poslovanja koji postoje u realnom sistemu.

> [!TIP]
> Kada proveravate da li FZ važi u nekoj relaciji, tražite kontraprimer: dve torke sa istom vrednošću na levoj strani, a različitom na desnoj. Ako nađete takav par, FZ ne važi.

---

## Logička posledica i implikacioni problem

Sada ulazimo u teorijski deo funkcionalne zavisnosti koji je neophodan za projektovanje baze.

### Logička posledica

FZ $f$ je **logička posledica** od skupa FZ $F$, oznaka $F \models f$, ako svaka relacija $r$ koja zadovoljava $F$ zadovoljava i $f$:

$$(\forall r \in SAT(U))(r \models F \Rightarrow r \models f)$$

Skup FZ $F_2$ je logička posledica od skupa FZ $F_1$, oznaka $F_1 \models F_2$, ako $(\forall f \in F_2)(F_1 \models f)$.

### Implikacioni problem

Rešiti implikacioni problem znači utvrditi da li važi $F \models f$ - da li neka FZ logički sledi iz datog skupa FZ.

### Ekvivalentnost skupova FZ

Oznaka: $F_1 \equiv F_2$ - važi ako $F_1 \models F_2$ i $F_2 \models F_1$.

---

## Zatvarač (zatvorenje) skupa FZ

**Zatvarač skupa FZ** (oznaka $F^+$) je skup koji sadrži **sve logičke posledice** od $F$:

$$F^+ = \{f \mid F \models f\}$$

Za svaki $F$ važi da $F \subseteq F^+$.

Veza sa implikacijom: $F_1 \models F_2$ akko $F_2^+ \subseteq F_1^+$.

Veza sa ekvivalentnošću: $F_1 \equiv F_2$ akko $F_1^+ = F_2^+$.

---

## Armstrongova pravila izvođenja

Armstrongova pravila su alat koji nam omogućava da iz poznatih FZ izvedemo nove. Ovo je ključno za rešavanje implikacionog problema.

### Osnovna pravila

1. **Refleksivnost:** $Y \subseteq X \Rightarrow X \rightarrow Y$

2. **Proširenje:** $X \rightarrow Y, \; W \subseteq V \Rightarrow XV \rightarrow YW$

3. **Pseudotranzitivnost:** $X \rightarrow Y, \; YV \rightarrow Z \Rightarrow XV \rightarrow Z$

### Izvedena pravila

Iz osnovnih pravila mogu se izvesti i dodatna korisna pravila:

4. **Uniranje desnih strana:** $X \rightarrow Y, \; X \rightarrow Z \Rightarrow X \rightarrow YZ$

5. **Dekompozicija desnih strana:** $X \rightarrow Y, \; V \subseteq Y \Rightarrow X \rightarrow V$

6. **Tranzitivnost:** $X \rightarrow Y, \; Y \rightarrow Z \Rightarrow X \rightarrow Z$

### Primer varijanti označavanja

Primena pravila dekompozicije i uniranja desnih strana:

$$\{BRI \rightarrow IME, \; BRI \rightarrow PRZ\} \equiv \{BRI \rightarrow IME + PRZ\}$$

Ali pažnja - **proizvoljno dekomponovanje levih strana nije dozvoljeno**:

$$\{BRI + OZP \rightarrow OCE\} \not\equiv \{BRI \rightarrow OCE, \; OZP \rightarrow OCE\}$$

> [!CAUTION]
> Ovo je jedna od najčešćih grešaka na ispitu! Desne strane FZ možemo slobodno spajati i razdvajati (uniranje i dekompozicija), ali **leve strane ne smemo proizvoljno razdvajati**. To što $AB \rightarrow C$ važi NE znači da važe $A \rightarrow C$ i $B \rightarrow C$.

### Svojstva Armstrongovih pravila

Sistem Armstrongovih pravila izvođenja (refleksivnost, proširenje, pseudotranzitivnost) je:

- **Korektan (neprotivrečan)** - svaka FZ koja se izvede primenom AP iz nekog skupa FZ predstavlja logičku posledicu tog skupa FZ
- **Kompletan** - svaka logička posledica nekog skupa FZ može se izvesti primenom AP iz tog skupa
- **Neredundantan (minimalan)** - ne može se eliminisati kao suvišno ni jedno od tri pravila izvođenja, a da prethodna dva svojstva ostanu očuvana

### Primer primene Armstrongovih pravila

Dati su: $U = \{A, B, C, D, E, F, G, H\}$, $F = \{BG \rightarrow H, \; DF \rightarrow GH, \; CH \rightarrow DA, \; B \rightarrow E, \; D \rightarrow BA, \; AG \rightarrow CF\}$

**Pitanje 1:** Da li važi $DA \rightarrow E$?

- Iz $D \rightarrow BA$ dekompozicijom dobijamo $D \rightarrow B$
- Iz $B \rightarrow E$ i $D \rightarrow B$ tranzitivnošću dobijamo $D \rightarrow E$
- Iz $D \rightarrow E$ proširenjem sa $A$ dobijamo $DA \rightarrow E$ (jer $D \subseteq DA$, pa refleksivnošću $DA \rightarrow D$, i tranzitivnošću $DA \rightarrow E$)
- Odgovor: **Da**, $DA \rightarrow E$ je logička posledica od $F$.

**Pitanje 2:** Da li važi $DG \rightarrow FH$?

- Iz $D \rightarrow BA$ dekompozicijom: $D \rightarrow B$
- Proširenjem sa $G$: $DG \rightarrow BG$
- Iz $BG \rightarrow H$ i $DG \rightarrow BG$ tranzitivnošću: $DG \rightarrow H$
- Iz $D \rightarrow BA$ dekompozicijom: $D \rightarrow A$, proširenjem: $DG \rightarrow AG$
- Iz $AG \rightarrow CF$ i $DG \rightarrow AG$ tranzitivnošću: $DG \rightarrow CF$, dekompozicijom: $DG \rightarrow F$
- Uniranjem: $DG \rightarrow FH$
- Odgovor: **Da**, $DG \rightarrow FH$ je logička posledica od $F$.

---

## Nepotpuna i tranzitivna FZ

### Nepotpuna FZ

FZ $X \rightarrow Y \in F$ je **nepotpuna** ako sadrži **logički suvišno obeležje na levoj strani**:

$$(\exists X' \subset X)(X' \rightarrow Y \in F^+)$$

**Primer:** $BRI + IME \rightarrow PRZ$ je nepotpuna, jer važi $BRI \rightarrow IME$, pa se ona redukuje u $BRI \rightarrow PRZ$.

### Tranzitivna FZ

FZ $X \rightarrow Z$ je **tranzitivna** ako važi:
- $X \rightarrow Y \in F^+$
- $Y \rightarrow Z \in F^+$
- $Y \rightarrow X \notin F^+$ (Y ne određuje X)

**Primer:** Važi $NAS \rightarrow OZP$ i $OZP \rightarrow NAP$, a ne važi $OZP \rightarrow NAS$. Dakle, $NAS \rightarrow NAP$ je tranzitivna i logički suvišna FZ.

---

## Ključ šeme relacije i funkcionalna zavisnost

Sada spajamo dva velika koncepta - ključ i FZ. Ovo je veoma moćan alat jer nam omogućava da formalno odredimo ključeve na osnovu datog skupa FZ.

$X$ je **ključ šeme relacije** $(R, F)$ ako važi:

$$1^0 \quad \text{iz } F \text{ sledi } X \rightarrow R \quad (X \rightarrow R \in F^+)$$

$$2^0 \quad X \text{ je minimalni skup obeležja sa osobinom } 1^0 \quad (\nexists X' \subset X)(X' \rightarrow R \in F^+)$$

Prvo pravilo kaže da $X$ funkcionalno određuje sva obeležja šeme. Drugo pravilo zahteva minimalnost.

---

## Zatvarač (zatvorenje) skupa obeležja

**Zatvarač skupa obeležja** je skup svih obeležja koja **funkcionalno zavise** od $X$:

$$X_F^+ = \{A \in U \mid X \rightarrow A \in F^+\}$$

### Algoritam za izračunavanje zatvarača $X_F^+$

Ovo je jedan od najčešće traženih algoritama na ispitu:

1. Polazimo od $X_0 = X$
2. U svakom koraku: $X_{i+1} = X_i \cup \{A \in U \mid (\exists V \rightarrow W \in F)(V \subseteq X_i \land A \in W)\}$
3. Zaustavljamo se kada $X_{n+1} = X_n$ (nema novih obeležja). Tada je $X_F^+ = X_n$.

Rečima: u svakoj iteraciji prolazimo kroz sve FZ iz $F$. Ako je leva strana neke FZ potpuno sadržana u trenutnom skupu, dodajemo sva obeležja sa desne strane. Ponavljamo dok se skup ne stabilizuje.

### Primer

Za $F = \{BRI \rightarrow IME + PRZ + BPI, \; IME + PRZ \rightarrow BRI, \; OZP \rightarrow NAP, \; NAS \rightarrow OZP + NAP, \; BRI + OZP \rightarrow OCE + NAS\}$

Izračunajmo $(BRI + OZP)_F^+$:

- $X_0 = \{BRI, OZP\}$
- Korak 1: $BRI \subseteq X_0 \Rightarrow$ dodaj IME, PRZ, BPI; $OZP \subseteq X_0 \Rightarrow$ dodaj NAP; $BRI + OZP \subseteq X_0 \Rightarrow$ dodaj OCE, NAS
- $X_1 = \{BRI, OZP, IME, PRZ, BPI, NAP, OCE, NAS\} = U$
- $X_2 = X_1$ - kraj algoritma

$(BRI + OZP)_F^+ = U$, što znači da $BRI + OZP$ funkcionalno određuje sva obeležja, pa je **kandidat za ključ**.

---

## Generisanje ključeva

### Generisanje jednog ključa

Postupak polazi od celokupnog skupa obeležja $R$ i vrši **redukciju** - izbacuje obeležja jedno po jedno i proverava zatvarač ostatka:

1. $X = R$
2. Redukcija $Red(X)$: za svako $A \in X$, ako $A \in (X \setminus \{A\})_F^+$, onda $X = X \setminus \{A\}$

Dakle, pokušavamo da izbacimo svako obeležje. Ako zatvarač skupa bez tog obeležja i dalje pokriva ceo $R$, onda to obeležje nije potrebno u ključu.

### Generisanje svih alternativnih ključeva

Polazi se od prvog generisanog ključa $X$, $K = \{X\}$:

Za svaki $X \in K$ i svaku $V \rightarrow W \in F$:

Ako $X \cap W \neq \emptyset$, onda $X_{newk} = (X \setminus W) \cup V$

Redukcija: $Red(X_{newk})$: $K = K \cup \{Red(X_{newk})\}$

### Primer - ključevi relacije Student

Za $F = \{BRI \rightarrow IME + PRZ + BPI, \; IME + PRZ \rightarrow BRI, \; OZP \rightarrow NAP, \; NAS \rightarrow OZP + NAP, \; BRI + OZP \rightarrow OCE + NAS\}$

Šema relacije Student ima **četiri ključa**:

- $K_1 = BRI + NAS$
- $K_2 = IME + PRZ + NAS$
- $K_3 = BRI + OZP$
- $K_4 = IME + PRZ + OZP$

Pojam ključa je **fundamentalan za teoriju i praksu** relacionog modela - ne projektuju se ostala ograničenja šeme BP dok se ne preciziraju ključevi svih šema relacija.

> [!IMPORTANT]
> Algoritam za izračunavanje zatvarača skupa obeležja i generisanje ključeva su među najčešćim zadacima na ispitu. Vežbajte ih dok ne postanu automatski!

---

## Projekcija skupa funkcionalnih zavisnosti

Poslednji koncept koji pokrivamo je projekcija skupa FZ na podskup obeležja.

Dati su skup FZ $F$ i skup obeležja $X \subseteq U$.

**Projekcija** $F|_X$ predstavlja skup svih funkcionalnih zavisnosti koje logički slede iz $F$, a **definisane su u skupu obeležja $X$**:

$$F|_X = \{V \rightarrow W \mid F \models V \rightarrow W \land VW \subseteq X\}$$

### Primer

$$F = \{A \rightarrow B, \; B \rightarrow C, \; BE \rightarrow F, \; A \rightarrow D\}$$

$$F|_{ACDEF} = \{A \rightarrow C, \; AE \rightarrow F, \; A \rightarrow D, \; \text{sve trivijalne FZ}\}$$

Primetimo: $A \rightarrow B$ nije u projekciji jer $B \notin ACDEF$. Ali $A \rightarrow C$ jeste (jer iz $A \rightarrow B$ i $B \rightarrow C$ sledi $A \rightarrow C$, a i $A$ i $C$ su u $ACDEF$).

---

## Zadaci za vežbu iz materijala

Za vežbanje celog gradiva, evo šema relacija koje se koriste u zadacima:

- $radnik(\{Mbr, Ime, Prz, Sef, Plt, God, Pre\}, \{Mbr\})$
- $projekat(\{Spr, Ruk, Nap, Nar\}, \{Spr\})$
- $radproj(\{Spr, Mbr, Brc\}, \{Spr + Mbr\})$

Sa sledećim ograničenjima referencijalnog integriteta:
- $radnik[Sef] \subseteq radnik[Mbr]$
- $projekat[Ruk] \subseteq radnik[Mbr]$
- $radproj[Mbr] \subseteq radnik[Mbr]$
- $radproj[Spr] \subseteq projekat[Spr]$

Primetimo da $radnik[Sef] \subseteq radnik[Mbr]$ znači da je šef svakog radnika takođe radnik iz iste tabele - to je takozvana **samoreferencirajuća** zavisnost sadržavanja.

---

## Rezime - svi tipovi ograničenja na jednom mestu

| Tip ograničenja | Oblast definisanosti | Oblast interpretacije |
|---|---|---|
| Ograničenje domena | Vanrelaciono | Ograničenje vrednosti |
| Ograničenje vrednosti obeležja | Jednorelaciono | Ograničenje vrednosti |
| Ograničenje torke | Jednorelaciono | Ograničenje torke |
| Integritet entiteta (ključ) | Jednorelaciono | Relaciono ograničenje |
| Ograničenje jedinstvenosti | Jednorelaciono | Relaciono ograničenje |
| Zavisnost sadržavanja | Višerelaciono | Međurelaciono ograničenje |
| Referencijalni integritet | Višerelaciono | Međurelaciono ograničenje |
| Funkcionalna zavisnost | Jednorelaciono | Relaciono ograničenje |

---

## 🎴 Brza pitanja (definicije i pojmovi)

**P:** Šta je integritetna komponenta relacionog modela podataka?

**P:** Navedi tri oblasti definisanosti ograničenja u relacionom modelu.

**P:** Šta je nula (NULL) vrednost i koja su njena moguća značenja?

**P:** Koja je formalna definicija ključa šeme relacije (oba uslova)?

**P:** Šta je ograničenje referencijalnog integriteta i po čemu se razlikuje od zavisnosti sadržavanja?

**P:** Šta je trivijalna funkcionalna zavisnost?

**P:** Navedi tri osnovna Armstrongova pravila izvođenja.

**P:** Šta je zatvarač (zatvorenje) skupa obeležja $X_F^+$?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite razliku između ograničenja ključa (integritet entiteta) i ograničenja jedinstvenosti vrednosti obeležja. Kada bismo koristili jedno, a kada drugo?

**O:** Ograničenje ključa ($Key(N, X)$) zahteva da kombinacija vrednosti obeležja ključa bude jedinstvena u relaciji i da **nijedno obeležje ključa ne sme imati NULL vrednost**. Ograničenje jedinstvenosti ($Unique(N, X)$) zahteva jedinstvenost samo za **ne-nula kombinacije** vrednosti - dakle, NULL vrednosti su dozvoljene. Na primer, MBR bi bio ključ (uvek mora biti poznat i jedinstven), dok bi JMBG mogao biti pod ograničenjem jedinstvenosti (jedinstven kad postoji, ali može biti nepoznat).

**P:** Dat je skup $U = \{A, B, C, D, E\}$ i $F = \{A \rightarrow BC, \; B \rightarrow D, \; CD \rightarrow E\}$. Izračunajte zatvarač skupa obeležja $(A)_F^+$ koristeći algoritam i odredite da li je $A$ ključ.

**O:** Polazimo od $X_0 = \{A\}$. U prvom koraku: $A \subseteq X_0$, pa dodajemo $B, C$ - dobijamo $X_1 = \{A, B, C\}$. U drugom koraku: $B \subseteq X_1$, dodajemo $D$ - $X_2 = \{A, B, C, D\}$. U trećem koraku: $CD \subseteq X_2$, dodajemo $E$ - $X_3 = \{A, B, C, D, E\} = U$. Pošto je $(A)_F^+ = U$ (ceo skup obeležja), a $A$ je jedno obeležje (ne može se dalje redukovati), $A$ jeste ključ šeme relacije.

**P:** Objasnite šta se dešava na nivou SUBP-a kada se pokuša operacija brisanja torke iz referencirane relacije, a ta torka je referencirana iz druge relacije. Dajte konkretan primer.

**O:** Ako pokušamo da obrišemo torku iz referencirane relacije čija je vrednost ključa prisutna u referencirajućoj relaciji, SUBP će to sprečiti jer bi se narušilo ograničenje referencijalnog integriteta. Na primer, ako imamo $Angažovanje[MBR] \subseteq Radnik[MBR]$ i pokušamo `DELETE FROM Radnik WHERE MBR = 110`, a u tabeli Angažovanje postoji torka sa MBR = 110, SUBP će izazvati grešku i prekinuti operaciju, ili će aktivnim mehanizmom (kaskadno brisanje, postavljanje na NULL) dovesti bazu u konzistentno stanje.

**P:** Zašto proizvoljno dekomponovanje levih strana funkcionalne zavisnosti nije dozvoljeno? Dajte konkretan kontrapimer.

**O:** Iz $X_1 X_2 \rightarrow Y$ ne sledi da važe $X_1 \rightarrow Y$ i $X_2 \rightarrow Y$ pojedinačno. Konkretan kontrapimer: u relaciji Student važi $BRI + OZP \rightarrow OCE$ (za datog studenta i predmet postoji tačno jedna ocena), ali ne važe ni $BRI \rightarrow OCE$ (student ima više ocena na različitim predmetima) ni $OZP \rightarrow OCE$ (na istom predmetu različiti studenti imaju različite ocene). Dekompozicija i uniranje se primenjuju samo na **desne strane** FZ.
