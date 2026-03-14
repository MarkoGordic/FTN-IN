# Relacioni model - Integritetna komponenta

## Uvod: Zašto su nam uopšte potrebna ograničenja?

Zamislimo da vodimo evidenciju studenata na fakultetu. Imamo lepu tabelu sa kolonama: broj indeksa, ime, prezime, ocena. Sve radi odlično - dok neko ne unese studenta sa ocenom 47. Ili dok dva studenta ne dobiju isti broj indeksa. Ili dok neko ne upiše radnika na projekat koji ne postoji.

Bez nekih pravila i kontrola, baza podataka bi brzo postala haos pun besmislenih podataka. Upravo tu na scenu stupa **integritetna komponenta** relacionog modela podataka. Ona definiše **skup tipova ograničenja** (uslova integriteta) koji služe za modeliranje ograničenja nad podacima u bazi podataka. Jednostavnije rečeno - to su pravila igre koja garantuju da podaci u bazi uvek imaju smisla.

Pre nego što zaronimo u detalje, hajde da se podsetimo gde se integritetna komponenta uklapa u širu sliku. Svaki model podataka ima tri komponente:

- **Strukturalna komponenta** - definiše "gradivne" elemente (obeležja, domene, torke, relacije, šeme). To je kostur naše baze.
- **Operacijska komponenta** - definiše operacije nad podacima (upitni jezici, DML, DDL). To su alati kojima radimo sa bazom.
- **Integritetna komponenta** - definiše ograničenja koja podaci moraju da zadovolje. To su pravila koja čuvaju bazu od nonsensa.

Sada, hajde da pažljivo razmotrimo svaki deo integritetne komponente.

---

## Karakteristike tipa ograničenja

Svaki tip ograničenja u relacionom modelu ima nekoliko bitnih karakteristika koje moramo razumeti. Možemo ih zamisliti kao "pasoš" jednog ograničenja - svaka stavka opisuje ko je ono i šta radi.

**Formalizam za zapisivanje (definicija)** - to je način na koji ograničenje zapisujemo. Svako ograničenje ima preciznu matematičku notaciju kojom se definiše.

**Pravilo za interpretaciju (validaciju)** - to je postupak kojim proveravamo da li su podaci u skladu sa ograničenjem. Kada SUBP primi novi podatak, on koristi ovo pravilo da proveri da li je sve u redu.

**Oblast definisanosti** - tip logičke strukture obeležja nad kojom se ograničenje definiše. Drugim rečima, gde u šemi BP definišemo ograničenje (nad jednom šemom relacije, nad više njih, ili čak van konteksta šeme relacije).

**Oblast interpretacije** - tip logičke strukture podataka nad kojom se ograničenje interpretira (proverava). Dakle, nad kojim konkretnim podacima se ograničenje proverava.

Pored toga, svaki tip ograničenja ima i:

- **Skup operacija** nad bazom podataka koje mogu dovesti do narušavanja ograničenja datog tipa (npr. dodavanje torke, brisanje torke, izmena podataka).
- **Skup mogućih akcija** kojima se obezbeđuje očuvanje validnosti baze podataka, pri pokušaju narušavanja ograničenja datog tipa. Ove akcije se definišu za svaku operaciju koja može dovesti do narušavanja ograničenja.

> [!IMPORTANT]
> Kontrola ograničenja implementiranih na nivou SUBP je **centralna** - ne može je zaobići ni jedan program ni korisnik. Korisnici nisu ni svesni da ograničenje postoji, dok ne pokušaju da ga naruše. U tom slučaju, SUBP ili izaziva grešku i prekida operaciju (prosleđujući korisničkom programu poruku o grešci), ili aktivnim mehanizmom automatski dovodi stanje baze u konzistentno stanje.

---

## Oblasti definisanosti u relacionom modelu

Ograničenja se razlikuju po tome gde se u strukturi baze podataka definišu. U relacionom modelu postoje tri oblasti definisanosti:

1. **Vanrelaciono ograničenje** - definiše se izvan konteksta šeme relacije. Na primer, ograničenje domena je vanrelaciono jer domen postoji nezavisno od bilo koje konkretne šeme relacije.

2. **Jednorelaciono (unutarrelaciono, lokalno) ograničenje** - definiše se nad tačno jednom šemom relacije. Na primer, ograničenje ključa u tabeli Radnik je lokalno jer se tiče samo te jedne tabele.

3. **Višerelaciono ograničenje** - definiše se nad skupom ili nizom šema relacija koji sadrži bar dva člana. Na primer, ograničenje referencijalnog integriteta povezuje dve tabele i zato je višerelaciono.

---

## Oblasti interpretacije u relacionom modelu

Pored oblasti definisanosti, ograničenja se razlikuju i po tome nad kojim tipom podataka se proveravaju. Postoje četiri oblasti interpretacije, od najuže do najšire:

1. **Ograničenje vrednosti** - interpretira se nad tačno jednom vrednošću nekog obeležja. Primer: "Ocena mora biti između 5 i 10."

2. **Ograničenje torke** - interpretira se nad jednom torkom bilo koje relacije. Primer: "Ako je zanimanje programer, onda mora imati poznat broj posedovanog jezika."

3. **Relaciono ograničenje** - interpretira se nad skupom torki bilo koje relacije. Primer: "Ne smeju postojati dve torke sa istom vrednošću matičnog broja."

4. **Međurelaciono ograničenje** - interpretira se nad barem dve, bilo koje relacije. Primer: "Radnik koji je angažovan na projektu mora postojati u tabeli radnika."

> [!NOTE]
> Napomena uz pojam "bilo koja relacija": to može biti jedna relacija iz baze podataka, ali i relacija koja je nastala primenom izraza relacione algebre nad jednom ili više drugih relacija - dakle **pogled** (view). Moguća je i primena operatora spajanja.

---

## Pregled tipova ograničenja

Pre nego što detaljno obradimo svaki tip, hajde da vidimo kompletnu listu tipova ograničenja u relacionom modelu podataka:

1. Ograničenje domena
2. Ograničenje vrednosti obeležja
3. Ograničenje torke
4. Integritet entiteta (ograničenje ključa)
5. Ograničenje jedinstvenosti vrednosti obeležja
6. Zavisnost sadržavanja
7. Ograničenje referencijalnog integriteta
8. Funkcionalna zavisnost

Svaki od ovih tipova ima specifičnu ulogu. Hajde da ih obradimo redom, počevši od najosnovnijeg.

---

## Ograničenje domena

### Šta je domen i zašto nam treba?

Domen je specifikacija skupa mogućih vrednosti koje neka obeležja mogu da dobiju. Zamislimo ga kao "kutiju" iz koje obeležje sme da uzme svoju vrednost. Obeležje "Ocena" sme da uzme vrednosti samo iz kutije koja sadrži brojeve od 5 do 10. Obeležje "Prezime" sme da bude samo tekst do 30 karaktera.

### Specifikacija domena

**Domen** se formalno zapisuje kao:

$$D(\text{id}(D), \text{Predef})$$

gde je:

- $D$ - naziv domena
- $\text{id}(D)$ - ograničenje (integritet) domena
- $\text{Predef}$ - predefinisana vrednost domena (default vrednost)

### Ograničenje domena

**Ograničenje domena** se detaljnije specifikuje kao:

$$\text{id}(D) = (\text{Tip}, \text{Dužina}, \text{Uslov})$$

gde je:

- **Tip** - tip podatka (primitivni domen) ili oznaka prethodno definisanog domena. Ovo je jedina **obavezna** komponenta specifikacije ograničenja domena.
- **Dužina** - dužina tipa podatka. Navodi se samo za tipove podataka (primitivne domene) koji to zahtevaju. Ne navodi se za domene čiji tip ne predstavlja primitivni domen.
- **Uslov** - logički uslov koji mora da ga zadovolji **svaka** vrednost iz skupa mogućih vrednosti domena.

Što se tiče predefinisane vrednosti (**Predef**) - ona mora da zadovolji ograničenja tipa, dužine i uslova.

### Interpretacija ograničenja domena

Ograničenje domena se može interpretirati za bilo koju vrednost - konstantu $d$. Oznaka te interpretacije je $\text{id}(D)(d)$, što čitamo kao: "da li vrednost $d$ zadovoljava ograničenje domena $D$?"

### Primeri specifikacije domena

Hajde da pogledamo konkretne primere. Simbol $\varepsilon$ označava da komponenta u specifikaciji nije zadata.

| Domen | Tip | Dužina | Uslov | Predef |
|-------|-----|--------|-------|--------|
| DPrezime | String | 30 | $\varepsilon$ | $\varepsilon$ |
| DDatum | Date | $\varepsilon$ | $d \geq$ '01.01.1900' | $\varepsilon$ |
| DOcena | Number | 2 | $d \geq 5 \land d \leq 10$ | $\varepsilon$ |
| DPozOcena | DOcena | $\varepsilon$ | $d \geq 6$ | 6 |

Primetimo nešto kod domena **DPozOcena** - njegov Tip nije primitivni domen (kao String ili Number), već prethodno definisani domen **DOcena**. To znači da DPozOcena "nasleđuje" ograničenja od DOcena (broj od 5 do 10), ali dodaje i svoje (mora biti barem 6). Njegova predefinisana vrednost je 6.

---

## Nula (nedostajuća, izostavljena) vrednost

Pre nego što nastavimo, moramo se upoznati sa jednim specijalnim konceptom koji prožima celu integritetnu komponentu.

**Nula vrednost** je specijalna vrednost koja se označava simbolom $\omega$ (ili ? u literaturi, ili **NULL** u SQL-u).

Nula vrednost može imati tri različita značenja:

1. **Nepoznata** - postojeća vrednost obeležja, ali trenutno nam nije poznata. Npr. radnik ima matični broj, ali ga nismo upisali.
2. **Nepostojeća** - vrednost obeležja ne postoji za dati entitet. Npr. broj faksa za osobu koja nema faks.
3. **Neinformativna** - vrednost obeležja nema smisla u datom kontekstu.

Skup mogućih vrednosti svih domena proširuje se nula vrednošću:

$$DOM \cup \{\omega\}$$

> [!WARNING]
> Nula vrednost **a priori zadovoljava svako ograničenje domena**. To je česta zamka na ispitu - studenti misle da NULL ne može proći ograničenje, ali može. Ograničenje domena se proverava samo za konkretne (ne-nula) vrednosti.

---

## Ograničenje vrednosti obeležja

### Specifikacija obeležja šeme relacije

Sada prelazimo sa domena na nivo obeležja unutar konkretne šeme relacije. Za svako obeležje $A$ u šemi relacije $N(R, O)$, gde $A \in R$, zadaje se specifikacija:

$$(\text{id}(N, A), \text{Predef})$$

gde je:

- $\text{id}(N, A)$ - ograničenje vrednosti obeležja $A$ u šemi relacije $N$
- $\text{Predef}$ - predefinisana vrednost obeležja

### Ograničenje vrednosti obeležja

**Ograničenje vrednosti obeležja** se definiše kao:

$$\text{id}(N, A) = (\text{Domen}, \text{Null})$$

gde je:

- **Domen** - oznaka (naziv) domena obeležja. Ovo je obavezna komponenta.
- **Null** $\in \{T, \bot\}$ - ograničenje nula vrednosti obeležja. Ovo je takođe obavezna komponenta.
  - $T$ - dozvola dodele nula vrednosti obeležju u relaciji nad $N$
  - $\bot$ - zabrana dodele nula vrednosti obeležju u relaciji nad $N$

Što se tiče predefinisane vrednosti (**Predef**): ako se navede na nivou obeležja, onda je on važeći. U protivnom, važeći je Predef odgovarajućeg domena, ili prvog sledećeg nasleđenog domena za koji je Predef definisan.

Interpretacija ograničenja vrednosti obeležja je moguća za bilo koju vrednost obeležja $d$, sa oznakom $\text{id}(N, A)(d)$.

---

## Ograničenje torke

Sada idemo korak šire - sa pojedinačnih vrednosti obeležja na nivo cele torke.

**Ograničenje torke** izražava ograničenja na moguće vrednosti unutar jedne torke. Zamislimo to ovako: svako obeležje ima svoja individualna ograničenja (domen, null), ali ponekad postoje i pravila koja povezuju vrednosti više obeležja unutar iste torke.

Formalno, za šemu relacije $N(R, O)$:

$$\text{id}(N) = \text{id}(R) = (\{\text{id}(N, A) \ | \ A \in R\}, \text{Uslov})$$

Ograničenje torke je, dakle, skup ograničenja vrednosti obeležja, kojem je pridodat **logički uslov** (Uslov). Taj uslov:

- mora da ga zadovolji **svaka torka** u relaciji
- može u ulozi operanda da sadrži bilo koje obeležje date šeme relacije

Interpretacija ograničenja torke je moguća za bilo koju torku nad skupom obeležja $R$, sa oznakom $\text{id}(N)(t)$.

### Primer ograničenja torke

Pogledajmo šemu relacije:

**Radnik({MBR, PRZ, IME, ZAN, BPJZ}, O)**

| Radnik | Domen | Null | Predef |
|--------|-------|------|--------|
| MBR | MBRD | $\bot$ | $\varepsilon$ |
| PRZ | PRZD | $\bot$ | $\varepsilon$ |
| IME | IMED | $\bot$ | $\varepsilon$ |
| BPJZ | BPJZD | $T$ | $\varepsilon$ |
| ZAN | ZAND | $\bot$ | $\varepsilon$ |

**Uslov:** $\text{ZAN} = \text{'prg'} \Rightarrow \text{BPJZ} \neq \omega$

Ovaj uslov kaže: "Ako je zanimanje radnika 'prg' (programer), onda broj posedovanih programskih jezika (BPJZ) ne sme biti nula vrednost." To ima smisla - ako neko tvrdi da je programer, mora znati bar nešto o broju jezika koje poznaje.

Domeni za ova obeležja su definisani ovako:

| Domen | Tip | Dužina | Uslov | Predef |
|-------|-----|--------|-------|--------|
| MBRD | Number | 4 | $d \geq 0$ | $\varepsilon$ |
| PRZD | String | 30 | $\varepsilon$ | $\varepsilon$ |
| IMED | String | 15 | $\varepsilon$ | $\varepsilon$ |
| BPJZD | Number | 2 | $d \geq 0$ | 0 |
| ZAND | String | 3 | $\varepsilon$ | $\varepsilon$ |

---

## Ključ šeme relacije

### Definicija ključa

Hajde sada da pređemo na jedan od najbitnijih koncepata u celom relacionom modelu. Zamislimo da imamo tabelu studenata. Kako da jednoznačno identifikujemo svakog studenta? Ime i prezime nisu dovoljni jer može biti više studenata sa istim imenom. Zato nam treba nešto jedinstveno - **ključ**.

**Ključ šeme relacije** je minimalni podskup skupa obeležja šeme relacije, na osnovu kojeg se jedinstveno može identifikovati svaka torka relacije nad datom šemom.

Formalno, $X$ je ključ ako važi:

1. $(\forall u, v \in r(R))(u[X] = v[X] \Rightarrow u = v)$ - ne postoje dve različite torke sa istom kombinacijom vrednosti ključnih obeležja
2. $(\nexists Y \subset X)$ za koje važi uslov 1. - ne postoji manji podskup od $X$ sa istom osobinom (minimalnost)

> [!IMPORTANT]
> Oba uslova su podjednako bitna. Prvi kaže da ključ mora **jedinstveno identifikovati** torku. Drugi kaže da ključ mora biti **minimalan** - ne smemo moći da izbacimo nijedno obeležje a da osobina jedinstvenosti ostane. Oblast interpretacije ključa je skup torki (relacija) nad datom šemom relacije.

### Šema relacije sa skupom ključeva

U određenim situacijama (u procesu projektovanja šeme BP) skup ograničenja šeme relacije zadaje se samo kao skup ključeva:

$$N(R, K)$$

Na primer, šema relacije:

**Radnik(R, K)**
- $R = \{MBR, IME, PRZ, DATR, POL, MESR, RBRE\}$
- $K = \{MBR, \ DATR+MESR+POL+RBRE\}$

Ovde vidimo da Radnik ima **dva** ključa. Jedan je samo MBR (matični broj), a drugi je kombinacija DATR+MESR+POL+RBRE (datum rođenja, mesto rođenja, pol, redni broj evidentiranja). Oba mogu jednoznačno identifikovati svakog radnika.

### Još primeri

- **Radnik({MBR, IME, PRZ, DATR}, {MBR})** - ključ je MBR
- **Projekat({SPR, NAP}, {SPR})** - ključ je SPR (šifra projekta)
- **Angažovanje({SPR, MBR, BRC}, {SPR+MBR})** - ključ je kombinacija SPR i MBR, jer se isti radnik na istom projektu može angažovati samo jednom

---

## Ograničenje ključa (integritet entiteta)

Sada formalizujemo ograničenje koje ključ nameće.

Za šemu relacije $N(R, K)$, ključ $X \in K$, $X \subseteq R$, **ograničenje ključa** se označava:

$$\text{Key}(N, X)$$

Ovo ograničenje kaže dve stvari:

1. Vrednosti ključnih obeležja moraju biti jedinstvene među svim torkama relacije.
2. **Za sva obeležja ključa, nula vrednosti su zabranjene:**

$$(\forall K_i \in K)(\forall A \in K_i)(\text{Null}(N, A) = \bot)$$

To znači da nijedno obeležje koje učestvuje u bilo kom ključu ne sme imati NULL vrednost. I to je logično - kako bismo identifikovali torku ako nam nedostaje deo "adrese"?

### Ekvivalentni i primarni ključ

Još nekoliko bitnih pojmova vezanih za ključ:

- Svaka šema relacije **mora posedovati najmanje jedan ključ** ($K \neq \emptyset$). Ovo proizilazi iz same definicije relacije (relacija je skup torki, a u skupu ne mogu postojati duplikati).

- **Ekvivalentni ključevi** - svi ključevi iz skupa ključeva $K$ su ekvivalentni. Bilo koji od njih može poslužiti za identifikaciju torke.

- **Primarni ključ** - jedan izabrani ključ od svih ekvivalentnih ključeva. Označava se $K_p(N)$. Svaka šema relacije treba da poseduje tačno jedan primarni ključ. On se koristi u ulozi **asocijativne (simboličke) adrese** za povezivanje podataka u relacijama.

> [!TIP]
> Na ispitu se često pita razlika između ključa i primarnog ključa. Zapamtite: ključeva može biti više (svi su ekvivalentni), ali primarni ključ je samo jedan - onaj koji smo izabrali da služi za povezivanje sa drugim relacijama.

---

## Ograničenje jedinstvenosti vrednosti obeležja

Ovo ograničenje je slično ograničenju ključa, ali ima jednu bitnu razliku.

**Ograničenje jedinstvenosti** (Uniqueness Constraint) za šemu relacije $N(R, O)$ se zapisuje:

$$\text{Unique}(N, X)$$

gde je $X$ skup obeležja, $X \subseteq R$.

Ovo ograničenje zahteva da **ne-nula kombinacija** vrednosti obeležja bude jedinstvena u relaciji nad $N(R, O)$.

Formalno:

$$(\forall u, v \in r(R))((\forall A \in X)(u[A] \neq \omega \land v[A] \neq \omega) \Rightarrow (u[X] = v[X] \Rightarrow u = v))$$

Oblast interpretacije je skup torki - relacija nad datom šemom $N(R, O)$.

Skup svih ograničenja jedinstvenosti u šemi $N(R, O)$ označavamo:

$$\text{Uniq} = \{\text{Unique}(N, X) \ | \ X \subseteq R\}$$

> [!WARNING]
> Razlika između ključa i Unique ograničenja: ključ **zabranjuje** nula vrednosti za sva svoja obeležja, dok Unique ograničenje **dozvoljava** nula vrednosti - ono proverava jedinstvenost samo za one torke gde su sve vrednosti u skupu $X$ različite od nule.

### Primer

Posmatramo šemu:

**Radnik({MBR, IME, PRZ, DATR, JMBG}, O)**

- $\text{Uniq} \subseteq O$
- $\text{Uniq} = \{\text{Unique}(\text{Radnik}, \text{JMBG})\}$

Ovo ograničenje $\text{Unique}(\text{Radnik}, \text{JMBG})$ zahteva da ako radnik poseduje ne-nula vrednost za JMBG, onda je ta vrednost jedinstvena u relaciji nad šemom Radnik. Ali ako za nekog radnika JMBG nije poznat (ima NULL vrednost), to je dozvoljeno - čak i više radnika može imati NULL za JMBG.

---

## Skup svih ograničenja šeme relacije

Kada šemu relacije treba implementirati u datom SUBP, njen kompletni skup ograničenja zadaje se kao **unija** tri komponente:

$$N(R, \ K \cup \text{Uniq} \cup \{\text{id}(R)\})$$

Dakle, skup ograničenja čine:
- skup ključeva ($K$)
- ograničenja jedinstvenosti ($\text{Uniq}$)
- ograničenje torke ($\text{id}(R)$)

### Primer

**Radnik({MBR, PRZ, IME, ZAN, BPJZ, JMBG}, $K \cup \text{Uniq} \cup \{\text{id}(R)\}$)**

- $K = \{MBR\}$
- $\text{Uniq} = \{\text{Unique}(\text{Radnik}, \text{JMBG})\}$
- $\text{id}(R)$ - prethodno zadat (u tabelarnom obliku, sa domenima, null ograničenjima, i uslovom torke)

---

## Zavisnost sadržavanja

### Motivacija

Do sada smo posmatrali ograničenja koja se tiču jedne šeme relacije. Ali šta ako želimo da izrazimo veze **između** dve šeme relacija? Na primer, želimo da kažemo: "Svaki radnik koji je angažovan na projektu mora postojati u tabeli radnika." Tu na scenu stupa zavisnost sadržavanja.

### Definicija

Date su šeme relacije $N_i(R_i, O_i)$ i $N_j(R_j, O_j)$. Dati su **domenski kompatibilni** nizovi obeležja:

$$X = (A_1, \ldots, A_n), \quad (\forall l \in \{1, \ldots, n\})(A_l \in R_i)$$
$$Y = (B_1, \ldots, B_n), \quad (\forall l \in \{1, \ldots, n\})(B_l \in R_j)$$
$$(\forall l \in \{1, \ldots, n\})(\text{dom}(A_l) \cong \text{dom}(B_l))$$

Domenski kompatibilni znači da odgovarajuća obeležja imaju kompatibilne domene.

**Zavisnost sadržavanja** se zapisuje:

$$N_i[X] \subseteq N_j[Y]$$

i važi ako je za bilo koje dve relacije $r(R_i, O_i)$ i $s(R_j, O_j)$ zadovoljeno:

$$(\forall u \in r)(\exists v \in s)(\forall l \in \{1, \ldots, n\})(u[A_l] = \omega \lor u[A_l] = v[B_l])$$

Drugim rečima: za svaku torku u relaciji $r$, ako vrednost obeležja $A_l$ nije NULL, onda mora postojati torka u relaciji $s$ koja ima tu istu vrednost za odgovarajuće obeležje $B_l$.

- **Oblast definisanosti**: niz od dve šeme relacije
- **Oblast interpretacije**: relacije nad šemama $N_i$ i $N_j$

### Primer sa jednim obeležjem

Date su relacije $r(N_i)$ i $s(N_j)$.

| r: A | B |
|------|---|
| a1 | b1 |
| a2 | b2 |

| s: B | C |
|------|---|
| b1 | c1 |
| b2 | c1 |
| b3 | c2 |

Važi zavisnost sadržavanja $N_i[B] \subseteq N_j[B]$, jer su vrednosti obeležja B u relaciji $r$ (b1 i b2) sadržane u vrednostima obeležja B u relaciji $s$ (b1, b2, b3).

### Primer sa dva obeležja

| r: A | B |
|------|---|
| a1 | b1 |
| a2 | $\omega$ |

| s: C | D |
|------|---|
| a1 | b1 |
| a2 | b2 |
| a3 | b2 |

Važi zavisnost sadržavanja $N_i[(A, B)] \subseteq N_j[(C, D)]$. Torka (a1, b1) iz $r$ ima odgovarajuću torku (a1, b1) u $s$. Torka (a2, $\omega$) iz $r$ ima nula vrednost za B, pa se ta komponenta ne proverava.

---

## Ograničenje referencijalnog integriteta

### Definicija

Sada stižemo do jednog od najpoznatijih i najčešće korišćenih ograničenja u praksi. **Ograničenje referencijalnog integriteta** je specijalan slučaj zavisnosti sadržavanja.

To je zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$, pri čemu je $Y$ **ključ** šeme relacije $N_j(R_j, K_j)$.

U ovom kontekstu:
- $N_i$ se naziva **referencirajuća šema relacije**
- $N_j$ se naziva **referencirana šema relacije**

Ono što ovo praktično znači: obeležja u referencirajućoj tabeli koja upućuju na drugu tabelu moraju sadržati vrednosti koje postoje kao ključ u referenciranoj tabeli (ili moraju biti NULL).

### Primer

Zamislimo bazu sa tri tabele: Radnik, Projekat i Angažovanje.

**Ograničenja referencijalnog integriteta:**

- $\text{Projekat}[\text{RUK}] \subseteq \text{Radnik}[\text{MBR}]$ - rukovodilac projekta mora biti postojeći radnik
- $\text{Angažovanje}[\text{MBR}] \subseteq \text{Radnik}[\text{MBR}]$ - angažovani radnik mora postojati u tabeli radnika
- $\text{Angažovanje}[\text{SPR}] \subseteq \text{Projekat}[\text{SPR}]$ - projekat na kome se radnik angažuje mora postojati

Podaci u tabelama:

**Radnik:**

| MBR | IME | PRZ | DATR |
|-----|-----|-----|------|
| 101 | Ana | Pap | 12.12.85. |
| 102 | Aca | Tot | 13.11.88. |
| 110 | Ivo | Ban | 01.01.79. |
| 111 | Olja | Kun | 06.05.81. |

**Projekat:**

| SPR | NAP | RUK |
|-----|-----|-----|
| 11 | X25 | 101 |
| 13 | Polaris | 101 |
| 14 | Univ.IS | 111 |

**Angažovanje:**

| MBR | SPR |
|-----|-----|
| 101 | 11 |
| 101 | 14 |
| 111 | 14 |

### Šta se dešava pri unosu i brisanju?

Hajde da razmotrimo nekoliko scenarija koji pokazuju kako ograničenje referencijalnog integriteta štiti konzistentnost podataka.

**Scenario 1: Unos novog projekta**

Želimo da unesemo novi projekat (SPR=15, NAP='P7', RUK=110). Proveravamo ograničenje $\text{Projekat}[\text{RUK}] \subseteq \text{Radnik}[\text{MBR}]$. Da li postoji radnik sa MBR=110? Da, to je Ivo Ban. Unos je dozvoljen.

A da smo pokušali da unesemo projekat sa RUK=210? Pošto ne postoji radnik sa MBR=210, SUBP bi odbio ovaj unos.

**Scenario 2: Angažovanje radnika na novom projektu**

Želimo da angažujemo radnika MBR=110 na projektu SPR=15. Proveravamo:
- $\text{Angažovanje}[\text{MBR}] \subseteq \text{Radnik}[\text{MBR}]$ - postoji li radnik 110? Da.
- $\text{Angažovanje}[\text{SPR}] \subseteq \text{Projekat}[\text{SPR}]$ - postoji li projekat 15? Da (upravo smo ga uneli).

Unos je dozvoljen.

**Scenario 3: Brisanje radnika**

Želimo da obrišemo radnika sa MBR=102 (Aca Tot). Da li ga bilo koji projekat referencira kao rukovodioca? Ne. Da li je angažovan na nekom projektu? Ne. Brisanje je dozvoljeno.

Ali da pokušamo da obrišemo radnika sa MBR=110 (Ivo Ban)? On je rukovodilac projekta 15 i angažovan je na projektu 15. Brisanje bi narušilo ograničenja referencijalnog integriteta. SUBP bi odbio ovo brisanje (ili bi primenio neku od korektivnih akcija - kaskadno brisanje, postavljanje na NULL, itd.).

> [!CAUTION]
> Na ispitu se često traži da studenti analiziraju šta se dešava pri unosu, brisanju ili izmeni podataka u kontekstu referencijalnog integriteta. Uvek razmišljajte u dva smera: (1) kad unosite u referencirajuću tabelu - proverite da li referencirana vrednost postoji, (2) kad brišete iz referencirane tabele - proverite da li neka referencirajuća tabela koristi tu vrednost.

---

## Funkcionalna zavisnost (FZ)

### Definicija

Sada ulazimo u oblast koja je fundamentalna za teoriju relacionih baza podataka. **Funkcionalna zavisnost** je izraz oblika:

$$f: X \rightarrow Y$$

gde su $X$ i $Y$ skupovi obeležja ($X, Y \subseteq U$), a $f$ je oznaka funkcionalne zavisnosti (koja se u notaciji često izostavlja).

**Semantika:** ako je poznata $X$ vrednost, poznata je i $Y$ vrednost. Ili drugačije rečeno: svakoj $X$ vrednosti odgovara samo jedna $Y$ vrednost.

Relacija $r$ zadovoljava FZ $X \rightarrow Y$ ako važi:

$$(\forall u, v \in r)(u[X] = v[X] \Rightarrow u[Y] = v[Y])$$

Ako dve torke imaju iste vrednosti za obeležja iz $X$, moraju imati iste vrednosti i za obeležja iz $Y$.

Oblast interpretacije je relacija $r(N)$ ili $r(U)$.

### Primer

Pogledajmo FZ $\text{MBR} \rightarrow \text{IME}$. Ovo znači: ako dve torke imaju istu vrednost za MBR, moraju imati istu vrednost i za IME. To ima smisla - jedan matični broj identifikuje jednog radnika koji ima jedno ime.

Skup FZ se označava sa $F$. Na primer:

$$F = \{MBR \rightarrow IME, \ MBR+MES+GOD \rightarrow BRC, \ldots\}$$

### Trivijalna funkcionalna zavisnost

**Trivijalna FZ** je svaka FZ koja je zadovoljena u **bilo kojoj** relaciji. To je svaka FZ $X \rightarrow Y$ za koju važi $Y \subseteq X$.

Primeri trivijalnih FZ:
- $MBR \rightarrow MBR$
- $MBR \rightarrow \emptyset$
- $AB \rightarrow A$

Ovo je logično - ako znamo vrednosti za $X$, onda svakako znamo i vrednosti za bilo koji podskup od $X$.

### Veliki primer sa tabelom Student

Hajde da pogledamo konkretan primer koji će nam pomoći da bolje razumemo funkcionalne zavisnosti.

Dat je skup obeležja $U$ sa sledećom semantikom:
- **BRI** - broj indeksa
- **IME** - ime studenta
- **PRZ** - prezime studenta
- **BPI** - broj položenih ispita
- **OZP** - oznaka predmeta
- **NAP** - naziv predmeta
- **NAS** - prezime nastavnika
- **OCE** - ocena na ispitu

Relacija Student:

| BRI | IME | PRZ | BPI | OZP | NAP | NAS | OCE |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 159 | Ivo | Ban | 13 | P1 | Mat | Han | 09 |
| 159 | Ivo | Ban | 13 | P2 | Fiz | Kun | 08 |
| 013 | Ana | Tot | 09 | P1 | Mat | Pap | 06 |
| 119 | Eva | Kon | 15 | P3 | Hem | Kiš | 07 |
| 159 | Ivo | Ban | 13 | P3 | Hem | Kiš | 10 |
| 119 | Eva | Kon | 15 | P1 | Mat | Han | 09 |
| 159 | Ivo | Ban | 13 | P4 | Mat | Car | 10 |
| 037 | Eva | Tot | 01 | P4 | Mat | Car | 10 |

Ova relacija **zadovoljava** sledeće FZ:

$$F = \{BRI \rightarrow IME+PRZ+BPI, \quad IME+PRZ \rightarrow BRI, \quad OZP \rightarrow NAP, \quad NAS \rightarrow OZP+NAP, \quad BRI+OZP \rightarrow OCE+NAS\}$$

Hajde da proverimo neke od njih:
- $BRI \rightarrow IME+PRZ+BPI$: student sa BRI=159 uvek ima IME=Ivo, PRZ=Ban, BPI=13. Student sa BRI=119 uvek ima IME=Eva, PRZ=Kon, BPI=15. Važi!
- $OZP \rightarrow NAP$: P1 je uvek Mat, P2 je uvek Fiz, P3 je uvek Hem, P4 je uvek Mat. Važi!
- $NAS \rightarrow OZP+NAP$: Han uvek predaje P1/Mat, Kun uvek predaje P2/Fiz, Kiš uvek predaje P3/Hem, Car uvek predaje P4/Mat. Važi!

Ova relacija **ne zadovoljava** FZ kao što su:
- $BRI \rightarrow OCE$ - student 159 ima ocene 09, 08, 10, 10 (različite ocene, a isti BRI)
- $OZP \rightarrow NAS$ - predmet P1 (Mat) predaju Han i Pap (različiti nastavnici)

> [!IMPORTANT]
> Način identifikacije važećih FZ: na osnovu odnosa i pravila poslovanja koji postoje u realnom sistemu. Ne gledamo samo podatke u tabeli (jer se oni menjaju), već razumemo logiku domena. Na primer, znamo da jedan broj indeksa pripada jednom studentu - to je pravilo realnog sistema.

---

## Logička posledica i implikacioni problem

### Logička posledica

FZ $f$ je **logička posledica** skupa FZ $F$ ako svaka relacija $r$ koja zadovoljava $F$, zadovoljava i $f$. Oznaka:

$$F \models f$$

Formalno:

$$(\forall r \in SAT(U))(r \models F \Rightarrow r \models f)$$

Skup FZ $F_2$ je logička posledica skupa FZ $F_1$ ako $(\forall f \in F_2)(F_1 \models f)$. Oznaka: $F_1 \models F_2$.

### Implikacioni problem

**Rešiti implikacioni problem** znači utvrditi da li važi $F \models f$ - da li je neka FZ logička posledica datog skupa FZ.

### Ekvivalentnost skupova FZ

Dva skupa FZ su **ekvivalentna** (oznaka $F_1 \equiv F_2$) ako važi:

$$F_1 \models F_2 \quad \land \quad F_2 \models F_1$$

---

## Zatvarač (zatvorenje) skupa FZ

**Zatvarač skupa FZ** (oznaka $F^+$) je skup koji sadrži sve logičke posledice od $F$:

$$F^+ = \{f \ | \ F \models f\}$$

Za svaki $F$ važi da $F \subseteq F^+$.

Korisne osobine:
- $F_1 \models F_2$ akko $F_2 \subseteq F_1^+$
- $F_1 \equiv F_2$ akko $F_1^+ = F_2^+$

---

## Armstrongova pravila izvođenja

Kako u praksi utvrđujemo da li je neka FZ logička posledica datog skupa? Koristimo **Armstrongova pravila izvođenja** - to su tri osnovna pravila koja nam omogućavaju da iz poznatih FZ izvodimo nove.

### Osnovna pravila

1. **Refleksivnost:** $Y \subseteq X \vdash X \rightarrow Y$

   Ako je $Y$ podskup od $X$, onda $X$ funkcionalno određuje $Y$. Ovo daje trivijalne FZ.

2. **Proširenje:** $X \rightarrow Y, \ W \subseteq V \vdash XV \rightarrow YW$

   Ako $X$ određuje $Y$, možemo obe strane proširiti - levu sa $V$, desnu sa $W$ (gde je $W \subseteq V$).

3. **Pseudotranzitivnost:** $X \rightarrow Y, \ YV \rightarrow Z \vdash XV \rightarrow Z$

   Ako $X$ određuje $Y$ i $YV$ određuje $Z$, onda $XV$ određuje $Z$.

### Izvedena pravila

Iz osnovnih pravila mogu se izvesti i sledeća korisna pravila:

4. **Uniranje desnih strana:** $X \rightarrow Y, \ X \rightarrow Z \vdash X \rightarrow YZ$

   Ako $X$ određuje $Y$ i $X$ određuje $Z$, onda $X$ određuje $YZ$.

5. **Dekompozicija desnih strana:** $X \rightarrow Y, \ V \subseteq Y \vdash X \rightarrow V$

   Ako $X$ određuje $Y$ i $V$ je podskup od $Y$, onda $X$ određuje $V$.

6. **Tranzitivnost:** $X \rightarrow Y, \ Y \rightarrow Z \vdash X \rightarrow Z$

   Ako $X$ određuje $Y$ i $Y$ određuje $Z$, onda $X$ određuje $Z$.

### Primer primene

Primena pravila dekompozicije i uniranja desnih strana:

$$\{BRI \rightarrow IME, \ BRI \rightarrow PRZ\} \equiv \{BRI \rightarrow IME+PRZ\}$$

> [!CAUTION]
> Proizvoljno dekomponovanje **levih** strana nije dozvoljeno! Na primer:
> $\{BRI+OZP \rightarrow OCE\} \neq \{BRI \rightarrow OCE, \ OZP \rightarrow OCE\}$
>
> Samo zato što kombinacija broja indeksa i oznake predmeta određuje ocenu, ne znači da broj indeksa sam po sebi određuje ocenu, niti da oznaka predmeta sama po sebi određuje ocenu.

### Osobine sistema Armstrongovih pravila

Sistem Armstrongovih pravila (refleksivnost, proširenje, pseudotranzitivnost) je:

- **Korektan (neprotivrečan)** - svaka FZ koja se izvede primenom AP iz nekog skupa FZ predstavlja logičku posledicu tog skupa FZ
- **Kompletan** - svaka logička posledica nekog skupa FZ može se izvesti primenom AP iz tog skupa
- **Neredundantan (minimalan)** - ne može se eliminisati kao suvišno ni jedno od tri pravila izvođenja, a da prethodna dva svojstva ostanu očuvana

### Primer dokazivanja

Dat je: $U = \{A, B, C, D, E, F, G, H\}$, $F = \{BG \rightarrow H, \ DF \rightarrow GH, \ CH \rightarrow DA, \ B \rightarrow E, \ D \rightarrow BA, \ AG \rightarrow CF\}$

**Pitanje 1: Da li važi $DA \rightarrow E$?**

Iz $D \rightarrow BA$ (dato) primenom dekompozicije dobijamo $D \rightarrow B$. Iz $B \rightarrow E$ (dato) i $D \rightarrow B$ primenom tranzitivnosti dobijamo $D \rightarrow E$. Iz $D \rightarrow E$ primenom proširenja sa $A$ dobijamo $DA \rightarrow E$. Dakle, $DA \rightarrow E$ važi.

**Pitanje 2: Da li važi $DG \rightarrow FH$?**

Iz $D \rightarrow BA$ primenom dekompozicije: $D \rightarrow A$, pa proširenjem sa $G$: $DG \rightarrow AG$. Iz $AG \rightarrow CF$ i $DG \rightarrow AG$ primenom tranzitivnosti: $DG \rightarrow CF$, pa dekompozicijom: $DG \rightarrow F$. Proširenjem $DG \rightarrow F$ sa $G$: $DG \rightarrow FG$. Iz $DF \rightarrow GH$ proširenjem sa $G$: $DFG \rightarrow GH$. Kombinovanjem: $DG \rightarrow F$, pa $DG \rightarrow FG$, pa pseudotranzitivnošću sa $DF \rightarrow GH$ dobijamo $DG \rightarrow GH$, dekompozicijom $DG \rightarrow H$. Unirenjem $DG \rightarrow F$ i $DG \rightarrow H$ dobijamo $DG \rightarrow FH$. Važi!

---

## Nepotpuna i tranzitivna FZ

### Nepotpuna FZ

FZ $X \rightarrow Y \in F$ je **nepotpuna** ako sadrži logički suvišno obeležje na levoj strani, tj.:

$$(\exists X' \subset X)(X' \rightarrow Y \in F^+)$$

**Primer:** $BRI+IME \rightarrow PRZ$ je nepotpuna, jer važi $BRI \rightarrow IME$ (ime se može saznati samo na osnovu broja indeksa), pa se FZ redukuje u $BRI \rightarrow PRZ$.

### Tranzitivna FZ

FZ $X \rightarrow Z$ je **tranzitivna** ako važi:
- $X \rightarrow Y \in F^+$
- $Y \rightarrow Z \in F^+$
- **Ne važi** $Y \rightarrow X \in F^+$

Uslov da ne važi $Y \rightarrow X$ je bitan jer bez njega bi svaka posledica mogla biti nazvana "tranzitivnom".

**Primer:** $NAS \rightarrow OZP$, $OZP \rightarrow NAP$, ali ne važi $OZP \rightarrow NAS$.

Dakle, $NAS \rightarrow NAP$ je tranzitivna FZ (i logički suvišna - saznaje se "preko" OZP).

---

## Ključ šeme relacije i funkcionalne zavisnosti

### Definicija ključa preko FZ

$X$ je ključ šeme relacije $(R, F)$ ako važi:

1. Iz $F$ sledi $X \rightarrow R$ (tj. $X \rightarrow R \in F^+$) - $X$ funkcionalno određuje sva obeležja
2. $X$ je minimalni skup obeležja sa osobinom 1: $(\nexists X' \subset X)(X' \rightarrow R \in F^+)$

### Zatvarač (zatvorenje) skupa obeležja

**Zatvarač skupa obeležja** $X$ u odnosu na skup FZ $F$ je skup svih obeležja koja funkcionalno zavise od $X$:

$$X_F^+ = \{A \in U \ | \ X \rightarrow A \in F^+\}$$

Ovo je jedan od najkorisnijih alata u praksi - umesto da pokušavamo da dokazujemo svaku FZ posebno, izračunamo zatvarač i vidimo šta sve zavisi od datog skupa obeležja.

### Algoritam za izračunavanje zatvarača $X_F^+$

Algoritam radi iterativno:

1. **Inicijalizacija:** $X_0 \leftarrow X$
2. **Iteracija:** $(\text{za } i \geq 0) \quad X_{i+1} \leftarrow X_i \cup \{A \in U \ | \ (\exists V \rightarrow W \in F)(V \subseteq X_i \land A \in W)\}$
3. **Zaustavljanje:** $(\text{za } n \geq 0)(X_{n+1} = X_n \Rightarrow X_F^+ = X_n)$

Drugim rečima: počinjemo od $X$, pa u svakom koraku dodajemo obeležja koja možemo odrediti na osnovu trenutnog skupa koristeći zavisnosti iz $F$. Kada se skup prestane širiti, dobili smo zatvarač.

### Primer izračunavanja zatvarača

Dat je: $F = \{BRI \rightarrow IME+PRZ+BPI, \ IME+PRZ \rightarrow BRI, \ OZP \rightarrow NAP, \ NAS \rightarrow OZP+NAP, \ BRI+OZP \rightarrow OCE+NAS\}$

Izračunajmo $(BRI+OZP)_F^+$:

- $X_0 = \{BRI, OZP\}$
- Iz $BRI \rightarrow IME+PRZ+BPI$: $BRI \subseteq X_0$, pa dodajemo $IME, PRZ, BPI$
- Iz $OZP \rightarrow NAP$: $OZP \subseteq X_0$, pa dodajemo $NAP$
- Iz $BRI+OZP \rightarrow OCE+NAS$: $\{BRI, OZP\} \subseteq X_0$, pa dodajemo $OCE, NAS$
- $X_1 = \{BRI, OZP, IME, PRZ, BPI, NAP, OCE, NAS\} = U$
- $X_2 = X_1$, pa se zaustavljamo.

Dakle $(BRI+OZP)_F^+ = U$, što znači da je $BRI+OZP$ kandidat za ključ (pod uslovom da je minimalan).

---

## Generisanje ključeva

### Generisanje jednog ključa

Polazi se od celog skupa obeležja $R$ i vrši se **redukcija** izbacivanjem obeležja:

1. $X \leftarrow R$
2. **Redukcija** $\text{Red}(X)$: $(\forall A \in X)(A \in (X \setminus \{A\})_F^+ \Rightarrow X \leftarrow X \setminus \{A\})$

Dakle, pokušavamo da izbacimo svako obeležje i proverimo da li ostatak još uvek određuje ceo $R$. Ako da - obeležje je suvišno i izbacujemo ga.

### Generisanje svih alternativnih ključeva

Polazi se od prvog generisanog ključa $X$, $K \leftarrow \{X\}$:

$$(\forall X \in K)(\forall V \rightarrow W \in F)(X \cap W \neq \emptyset \Rightarrow X_{\text{newk}} \leftarrow (X \setminus W) \cup V)$$

Zatim se vrši redukcija: $\text{Red}(X_{\text{newk}})$ i novi ključ se dodaje: $K \leftarrow K \cup \{\text{Red}(X_{\text{newk}})\}$

### Primer

Za $F = \{BRI \rightarrow IME+PRZ+BPI, \ IME+PRZ \rightarrow BRI, \ OZP \rightarrow NAP, \ NAS \rightarrow OZP+NAP, \ BRI+OZP \rightarrow OCE+NAS\}$

Šema relacije Student ima četiri ključa:

- $K_1 = BRI + NAS$
- $K_2 = IME + PRZ + NAS$
- $K_3 = BRI + OZP$
- $K_4 = IME + PRZ + OZP$

> [!IMPORTANT]
> Pojam ključa je **fundamentalan** za teoriju i praksu relacionog modela podataka. Ne projektuju se ostala ograničenja šeme BP dok se ne preciziraju ključevi svih šema relacija. To je uvek prvi korak.

---

## Projekcija skupa funkcionalnih zavisnosti

Ponekad radimo sa podskupom obeležja i treba nam samo deo funkcionalnih zavisnosti. Tu koristimo projekciju.

Dati su skup FZ $F$ i skup obeležja $X \subseteq U$. **Projekcija** $F|_X$ predstavlja skup svih funkcionalnih zavisnosti koje logički slede iz $F$, a definisane su u skupu obeležja $X$:

$$F|_X = \{V \rightarrow W \ | \ F \models V \rightarrow W \land VW \subseteq X\}$$

### Primer

$F = \{A \rightarrow B, \ B \rightarrow C, \ BE \rightarrow F, \ A \rightarrow D\}$

$F|_{ACDEF} = \{A \rightarrow C, \ AE \rightarrow F, \ A \rightarrow D, \ \text{sve trivijalne fz}\}$

Primetimo: $A \rightarrow B$ ne ulazi u projekciju jer $B \notin ACDEF$. Ali $A \rightarrow C$ ulazi jer važi $A \rightarrow B$ i $B \rightarrow C$ (tranzitivnost), pa $F \models A \rightarrow C$, i $AC \subseteq ACDEF$. Slično, $AE \rightarrow F$ ulazi jer $BE \rightarrow F$ i $A \rightarrow B$ daju $AE \rightarrow F$.

---

## Konzistentno stanje baze podataka

Da zaokružimo priču o integritetnoj komponenti, vratimo se na pitanje: čemu sve ovo služi?

Baza podataka $RBP = \{r_i \ | \ i \in \{1, \ldots, n\}\}$ nad šemom $(S, I)$ nalazi se u:

- **Formalno konzistentnom stanju** ako:
  - $(\forall r_i \in RBP)(r_i \text{ zadovoljava sva ograničenja odgovarajuće šeme } (R_i, O_i))$
  - $RBP$ zadovoljava sva međurelaciona ograničenja iskazana putem $I$

- **Suštinski konzistentnom stanju** ako:
  - se nalazi u formalno konzistentnom stanju **i**
  - predstavlja vernu sliku stanja realnog sistema

U praksi, nivo pojave grešaka u BP sveden je na ispod 2-3%. SUBP može da kontroliše **formalnu** konzistentnost (putem svih ograničenja koja smo opisali), dok suštinska konzistentnost zavisi od toga koliko verno podaci odražavaju stvarnost.

---

## Zadaci za vežbu

Na kraju, evo i nekoliko zadataka koji su dati za vežbu uz materijal, a koji pokrivaju ono što smo naučili.

### Šema baze za vežbu

- **radnik**({Mbr, Ime, Prz, Sef, Plt, God, Pre}, {Mbr})
- **projekat**({Spr, Ruk, Nap, Nar}, {Spr})
- **radproj**({Spr, Mbr, Brc}, {Spr + Mbr})

Ograničenja referencijalnog integriteta:
- radnik[Sef] $\subseteq$ radnik[Mbr]
- projekat[Ruk] $\subseteq$ radnik[Mbr]
- radproj[Mbr] $\subseteq$ radnik[Mbr]
- radproj[Spr] $\subseteq$ projekat[Spr]

### Zadaci za zatvarače

1. $U = \{A, B, C, D, E, F\}$, $F = \{AB \rightarrow AC, \ CD \rightarrow E, \ A \rightarrow B, \ AE \rightarrow F\}$. Izračunati $(AD)^+$.
2. $U = \{A, B, C, D, E, F, G\}$, $F = \{AB \rightarrow C, \ C \rightarrow A, \ BC \rightarrow D, \ ACD \rightarrow B, \ D \rightarrow EG, \ BE \rightarrow C, \ CG \rightarrow BD, \ CE \rightarrow AG\}$. Izračunati $(BD)^+$.
3. $U = \{A, B, C, D, E, I, J\}$, $F = \{A \rightarrow B, \ A \rightarrow C, \ A \rightarrow E, \ D \rightarrow C, \ E \rightarrow I, \ BI \rightarrow J\}$. Izračunati $(AI)^+$, $(DJ)^+$, $(BE)^+$.

### Zadaci za ključeve

1. $U = \{A, B, C, D, E\}$, $F = \{AB \rightarrow CDE, \ E \rightarrow A, \ CD \rightarrow B\}$
2. $U = \{A, B, C, D, E, F\}$, $F = \{AB \rightarrow C, \ C \rightarrow A, \ C \rightarrow D, \ AB \rightarrow E, \ AB \rightarrow F, \ E \rightarrow F\}$
3. $U = \{A, B, C, D, E, F, G, H\}$, $F = \{AB \rightarrow CE, \ C \rightarrow B, \ ED \rightarrow F, \ F \rightarrow G\}$

### Zadaci za dokazivanje logičkih posledica

1. $F = \{A \rightarrow B, \ B \rightarrow C, \ AC \rightarrow D, \ BD \rightarrow E, \ C \rightarrow E\}$. Dokazati: $F \models A \rightarrow D$, $F \models AD \rightarrow E$.
2. $F = \{A \rightarrow F, \ AB \rightarrow CE, \ AC \rightarrow D, \ EB \rightarrow D, \ D \rightarrow A, \ F \rightarrow AE\}$. Dokazati: $F \models AB \rightarrow D$.
3. $F = \{AB \rightarrow C, \ C \rightarrow A, \ BC \rightarrow D, \ ACD \rightarrow B, \ D \rightarrow EG, \ BE \rightarrow C\}$. Dokazati: $F \models CE \rightarrow B$, $F \models BD \rightarrow C$, i druge.

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

**P:** Šta je integritetna komponenta relacionog modela podataka?

**P:** Koje su tri komponente modela podataka?

**P:** Šta je formalizam za zapisivanje (definicija) tipa ograničenja?

**P:** Šta je pravilo za interpretaciju (validaciju) tipa ograničenja?

**P:** Šta je oblast definisanosti tipa ograničenja?

**P:** Šta je oblast interpretacije tipa ograničenja?

**P:** Šta je skup operacija nad bazom podataka u kontekstu tipa ograničenja?

**P:** Šta je skup mogućih akcija pri pokušaju narušavanja ograničenja?

**P:** Kako SUBP reaguje kada se pokuša narušavanje ograničenja?

**P:** Šta je vanrelaciono ograničenje?

**P:** Šta je jednorelaciono (unutarrelaciono, lokalno) ograničenje?

**P:** Šta je višerelaciono ograničenje?

**P:** Šta je ograničenje vrednosti (oblast interpretacije)?

**P:** Šta je ograničenje torke (oblast interpretacije)?

**P:** Šta je relaciono ograničenje (oblast interpretacije)?

**P:** Šta je međurelaciono ograničenje (oblast interpretacije)?

**P:** Nabroj sve tipove ograničenja u relacionom modelu podataka.

**P:** Kako se formalno zapisuje specifikacija domena?

**P:** Šta su komponente ograničenja domena $\text{id}(D)$?

**P:** Šta je Tip u specifikaciji ograničenja domena?

**P:** Šta je Dužina u specifikaciji ograničenja domena?

**P:** Šta je Uslov u specifikaciji ograničenja domena?

**P:** Šta je predefinisana vrednost (Predef) domena?

**P:** Koja je jedina obavezna komponenta specifikacije ograničenja domena?

**P:** Šta je nula (nedostajuća) vrednost?

**P:** Koji su mogući simboli za označavanje nula vrednosti?

**P:** Koja su tri moguća značenja nula vrednosti?

**P:** Kako se skup mogućih vrednosti domena proširuje nula vrednošću?

**P:** Da li nula vrednost zadovoljava ograničenje domena?

**P:** Kako se formalno zapisuje specifikacija obeležja šeme relacije?

**P:** Šta su komponente ograničenja vrednosti obeležja $\text{id}(N, A)$?

**P:** Šta znači $\text{Null} = T$?

**P:** Šta znači $\text{Null} = \bot$?

**P:** Šta je ograničenje torke i kako se formalno zapisuje?

**P:** Šta je Uslov u ograničenju torke?

**P:** Šta je ključ šeme relacije?

**P:** Koji su dva formalna uslova da $X$ bude ključ?

**P:** Šta znači "minimalnost" u definiciji ključa?

**P:** Šta je šema relacije oblika $N(R, K)$?

**P:** Kako se zapisuje ograničenje ključa (integritet entiteta)?

**P:** Zašto su za sva obeležja ključa nula vrednosti zabranjene?

**P:** Da li svaka šema relacije mora imati bar jedan ključ? Zašto?

**P:** Šta su ekvivalentni ključevi?

**P:** Šta je primarni ključ i kako se označava?

**P:** Za šta se primarni ključ koristi?

**P:** Šta je ograničenje jedinstvenosti (Unique)?

**P:** Kako se formalno zapisuje ograničenje jedinstvenosti?

**P:** Po čemu se razlikuje ograničenje jedinstvenosti od ograničenja ključa?

**P:** Šta je skup svih ograničenja jedinstvenosti u šemi relacije?

**P:** Kako se zapisuje kompletni skup ograničenja šeme relacije za implementaciju?

**P:** Šta je zavisnost sadržavanja?

**P:** Kako se formalno zapisuje zavisnost sadržavanja?

**P:** Šta znači "domenski kompatibilni" nizovi obeležja?

**P:** Koja je oblast definisanosti zavisnosti sadržavanja?

**P:** Koja je oblast interpretacije zavisnosti sadržavanja?

**P:** Šta je ograničenje referencijalnog integriteta?

**P:** Šta je referencirajuća šema relacije?

**P:** Šta je referencirana šema relacije?

**P:** Šta se dešava pri unosu torke u referencirajuću relaciju?

**P:** Šta se dešava pri brisanju torke iz referencirane relacije?

**P:** Šta je funkcionalna zavisnost?

**P:** Kako se formalno definiše da relacija zadovoljava FZ $X \rightarrow Y$?

**P:** Šta je semantika funkcionalne zavisnosti?

**P:** Šta je trivijalna funkcionalna zavisnost?

**P:** Navedi primere trivijalnih FZ.

**P:** Šta je logička posledica skupa FZ?

**P:** Šta je implikacioni problem?

**P:** Šta je ekvivalentnost dva skupa FZ?

**P:** Šta je zatvarač (zatvorenje) skupa FZ?

**P:** Kako se formalno definiše $F^+$?

**P:** Navedi tri osnovna Armstrongova pravila izvođenja.

**P:** Kako glasi pravilo refleksivnosti?

**P:** Kako glasi pravilo proširenja?

**P:** Kako glasi pravilo pseudotranzitivnosti?

**P:** Navedi tri izvedena pravila izvođenja.

**P:** Kako glasi pravilo uniranja desnih strana?

**P:** Kako glasi pravilo dekompozicije desnih strana?

**P:** Kako glasi pravilo tranzitivnosti?

**P:** Zašto nije dozvoljeno proizvoljno dekomponovanje levih strana FZ?

**P:** Koje su tri osobine sistema Armstrongovih pravila?

**P:** Šta znači da je sistem AP korektan?

**P:** Šta znači da je sistem AP kompletan?

**P:** Šta znači da je sistem AP neredundantan?

**P:** Šta je nepotpuna FZ?

**P:** Šta je tranzitivna FZ?

**P:** Koji uslov razlikuje tranzitivnu FZ od obične tranzitivne posledice?

**P:** Kako se definiše ključ šeme relacije pomoću FZ?

**P:** Šta je zatvarač (zatvorenje) skupa obeležja?

**P:** Kako se formalno definiše $X_F^+$?

**P:** Koji su koraci algoritma za izračunavanje zatvarača skupa obeležja?

**P:** Kako se generiše jedan ključ šeme relacije?

**P:** Šta je redukcija u kontekstu generisanja ključa?

**P:** Kako se generišu svi alternativni ključevi?

**P:** Šta je projekcija skupa FZ na skup obeležja?

**P:** Kako se formalno definiše $F|_X$?

**P:** Šta je formalno konzistentno stanje baze podataka?

**P:** Šta je suštinski konzistentno stanje baze podataka?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite razliku između oblasti definisanosti i oblasti interpretacije ograničenja. Dajte primer za svaku od četiri oblasti interpretacije.

**O:** Oblast definisanosti govori o tome gde u strukturi šeme BP se ograničenje definiše (vanrelaciono, jednorelaciono, višerelaciono), dok oblast interpretacije govori nad kojim tipom podataka se ograničenje proverava. Četiri oblasti interpretacije su: ograničenje vrednosti (proverava se nad jednom vrednošću, npr. "ocena između 5 i 10"), ograničenje torke (proverava se nad jednom torkom, npr. "ako je programer, mora imati poznat BPJZ"), relaciono ograničenje (proverava se nad skupom torki, npr. jedinstvenost ključa), i međurelaciono ograničenje (proverava se nad dve ili više relacija, npr. referencijalni integritet).

**P:** Objasnite razliku između ograničenja ključa i ograničenja jedinstvenosti (Unique). Dajte konkretan primer gde se ta razlika manifestuje.

**O:** Ključ zahteva jedinstvenost vrednosti i zabranjuje NULL za sva svoja obeležja. Ograničenje jedinstvenosti zahteva jedinstvenost samo za ne-nula vrednosti, a dozvoljava NULL. Na primer, u tabeli Radnik, MBR je ključ i mora biti jedinstven i ne-NULL. JMBG ima Unique ograničenje - ako je poznat, mora biti jedinstven, ali može biti NULL za radnike čiji JMBG još nije upisan.

**P:** Za dati skup FZ $F = \{A \rightarrow B, \ B \rightarrow C, \ AC \rightarrow D\}$, izračunajte zatvarač $(A)_F^+$ i objasnite svaki korak algoritma.

**O:** Počinjemo sa $X_0 = \{A\}$. Iz $A \rightarrow B$: $A \subseteq X_0$, pa dodajemo $B$, $X_1 = \{A, B\}$. Iz $B \rightarrow C$: $B \subseteq X_1$, pa dodajemo $C$, a iz $AC \rightarrow D$: $\{A, C\} \subseteq X_2 = \{A, B, C\}$, pa dodajemo $D$. Dobijamo $X_3 = \{A, B, C, D\}$. Nema više promena, pa je $(A)_F^+ = \{A, B, C, D\}$.

**P:** Šta je referencijalni integritet i zašto je poseban slučaj zavisnosti sadržavanja? Objasnite na primeru sa tabelama Radnik i Projekat.

**O:** Referencijalni integritet je zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$ gde je $Y$ ključ šeme $N_j$. Poseban je jer garantuje da referencirane vrednosti zaista identifikuju konkretne torke. Na primer, $\text{Projekat}[RUK] \subseteq \text{Radnik}[MBR]$ znači da rukovodilac projekta mora biti postojeći radnik (MBR je ključ relacije Radnik). Ovo sprečava situaciju da projekat referencira nepostojećeg radnika.

**P:** Objasnite zašto je proizvoljno dekomponovanje levih strana FZ nedozvoljeno. Ilustrujte primerom.

**O:** Iz $BRI+OZP \rightarrow OCE$ ne sledi da važe $BRI \rightarrow OCE$ i $OZP \rightarrow OCE$. U tabeli Student, kombinacija broja indeksa i oznake predmeta jednoznačno određuje ocenu (jedan student ima jednu ocenu na jednom predmetu). Ali sam broj indeksa ne određuje ocenu (student ima više ocena), niti sama oznaka predmeta ne određuje ocenu (na istom predmetu studenti imaju različite ocene). Dekompozicija je dozvoljena samo na desnoj strani.

**P:** Objasnite pojmove korektnosti, kompletnosti i neredundantnosti Armstrongovih pravila i zašto je svaki od tih pojmova bitan.

**O:** Korektnost znači da svaka FZ izvedena primenom AP predstavlja validnu logičku posledicu, pa ne možemo izvesti pogrešne zaključke. Kompletnost znači da se svaka logička posledica može izvesti primenom AP, pa nam ništa ne promakne. Neredundantnost znači da ne možemo izbaciti nijedno od tri pravila a da sistem ostane korektan i kompletan - sva tri su neophodna.

**P:** Na primeru šeme Radnik({MBR, PRZ, IME, ZAN, BPJZ}, O), objasnite kako se kombinuju ograničenje domena, ograničenje vrednosti obeležja i ograničenje torke.

**O:** Za obeležje ZAN, domen ZAND definiše da je tip String dužine 3. Ograničenje vrednosti kaže da je domen ZAND, a Null je $\bot$ (zabranjen). Za BPJZ, domen BPJZD definiše tip Number dužine 2, sa uslovom $d \geq 0$ i predefinisanom vrednošću 0, dok Null je $T$ (dozvoljen). Na nivou torke, uslov $ZAN = 'prg' \Rightarrow BPJZ \neq \omega$ povezuje vrednosti više obeležja - programer mora imati poznatu BPJZ vrednost. Ova tri nivoa ograničenja rade zajedno da obezbede kvalitet podataka.

**P:** Objasnite algoritam za generisanje jednog ključa i svih alternativnih ključeva. Zašto se polazi od celog skupa $R$?

**O:** Za generisanje jednog ključa polazimo od $R$ i pokušavamo da izbacujemo obeležja jedno po jedno - za svako obeležje proveravamo da li zatvarač ostatka i dalje pokriva ceo $R$. Ako da, obeležje je suvišno i izbacujemo ga. Polazimo od $R$ jer sigurno znamo da $R \rightarrow R$ važi, pa redukcijom dobijamo minimalni skup. Za alternativne ključeve, uzimamo pronađeni ključ i za svaku FZ $V \rightarrow W$ koja "seče" ključ, formiramo kandidata zamenom preseka sa $V$, pa ga redukujemo.

**P:** Šta je nula vrednost i zašto je bitna za integritetnu komponentu? Navedite sva tri značenja i objasnite kako nula vrednost utiče na ograničenje ključa i ograničenje jedinstvenosti.

**O:** Nula vrednost (NULL) je specijalna vrednost koja može značiti nepoznatu, nepostojeću ili neinformativnu vrednost. Za ograničenje ključa, nula vrednosti su strogo zabranjene za sva obeležja svih ključeva jer ključ mora jednoznačno identifikovati torku. Za ograničenje jedinstvenosti, nula vrednosti su dozvoljene - jedinstvenost se proverava samo za torke gde su sve vrednosti u datom skupu obeležja različite od NULL. Nula vrednost a priori zadovoljava svako ograničenje domena.

**P:** Šta je projekcija skupa FZ na skup obeležja? Zašto je korisna i kako se razlikuje od originalnog skupa FZ?

**O:** Projekcija $F|_X$ je skup svih FZ koje logički slede iz $F$, ali su definisane isključivo u okviru skupa obeležja $X$. Korisna je kada radimo sa podskupom obeležja (npr. nakon dekompozicije šeme relacije) i trebamo znati koja ograničenja važe nad tim podskupom. Razlikuje se od $F$ jer može sadržati FZ koje nisu direktno u $F$ ali su njihove logičke posledice, dok istovremeno isključuje sve FZ koje koriste obeležja van $X$.
