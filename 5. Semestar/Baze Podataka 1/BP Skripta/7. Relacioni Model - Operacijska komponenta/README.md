# Relacioni model - Operacijska komponenta

## Uvod - Čemu služi operacijska komponenta?

Do sada smo upoznali strukturalnu komponentu relacionog modela - naučili smo šta su obeležja, domeni, torke, relacije, šeme relacija i šeme baza podataka. Upoznali smo i integritetnu komponentu - ograničenja koja čuvaju konzistentnost naših podataka. Ali šta vredi najlepše strukturirana baza podataka, ako ne možemo ništa da uradimo sa podacima u njoj?

Tu na scenu stupa **operacijska komponenta**. Zamislimo da smo napravili savršenu biblioteku - police su označene, knjige sortirane, katalog napisan. Ali ako nemamo pravila kako se knjige izdaju, vraćaju, pretražuju - biblioteka je beskorisna. Operacijska komponenta je upravo taj skup pravila koji nam omogućava da **radimo sa podacima** - da ih pretražujemo, menjamo, dodajemo i brišemo.

Hajde da krenemo redom i vidimo od čega se ova komponenta sastoji.

---

## Tri dela operacijske komponente

Operacijska komponenta relacionog modela podataka obuhvata tri vrste jezika, od kojih svaki ima svoju ulogu:

### 1. Jezik za manipulaciju podacima (DML - Data Manipulation Language)

**Jezik za manipulaciju podacima** definiše operacije za **ažuriranje relacija**. To su tri osnovne operacije:

- **Dodavanje nove torke (Add)** - unošenje novog reda u tabelu (npr. upis novog studenta)
- **Brisanje postojeće torke (Delete)** - uklanjanje reda iz tabele (npr. brisanje studenta koji je diplomirao)
- **Modifikacija podataka postojeće torke (Update)** - izmena vrednosti u postojećem redu (npr. promena adrese studenta)

Ove tri operacije pokrivaju sve moguće promene nad podacima. Svaka promena u realnom sistemu (novi zaposleni, otpušten radnik, promena plate) svodi se na jednu od ove tri operacije.

### 2. Jezik za definiciju podataka (DDL - Data Definition Language)

**Jezik za definiciju podataka** definiše operacije za **upravljanje šemom baze podataka**. Ovde spadaju operacije za kreiranje, brisanje i modifikovanje delova šeme baze podataka. Dok DML menja podatke u tabelama, DDL menja same tabele - njihovu strukturu.

### 3. Upitni jezik (QL - Query Language)

**Upitni jezik** definiše operacije za **izražavanje upita** nad jednom relacijom ili skupom relacija. Cilj upitnog jezika je pružanje podataka na uvid korisniku - mi postavljamo pitanje bazi, a ona nam vraća odgovor.

> [!IMPORTANT]
> Na ispitu se najčešće pitaju detalji o upitnom jeziku i operacijama relacione algebre. DML i DDL su bitni za razumevanje šire slike, ali fokus je na upitnom jeziku.

---

## Upitni jezik - detaljniji pogled

Hajde da se zadržimo na upitnom jeziku, jer on čini srce operacijske komponente sa teorijske strane.

**Upitni jezik** sačinjavaju:

- **Operatori** za izražavanje upita
- **Pravila za formiranje operanada** upita (izraza)
- **Pravila za primenu tih operatora**

Ako povučemo paralelu sa matematikom: operator je npr. sabiranje (+), operandi su brojevi (3 i 5), a pravilo primene kaže da se 3 + 5 izračunava tako što se sabiraju ta dva broja.

### Vrste teoretskih upitnih jezika u RMP

U relacionom modelu podataka postoje dve vrste teoretskih upitnih jezika:

1. **Relaciona algebra** - zasnovana na teoriji skupova i skupovnih operacija. Kod relacione algebre mi "govorimo" bazi podataka **kako** da dođe do rezultata - zadajemo niz operacija koje treba izvršiti.

2. **Relacioni račun** - zasnovan na predikatskom računu I reda. Postoje dve varijante:
   - **Relacioni račun nad torkama**
   - **Relacioni račun nad domenima**

   Kod relacionog računa mi bazi "govorimo" **šta** želimo da dobijemo, a ona sama pronalazi način da to uradi.

> [!NOTE]
> SQL (Structured Query Language), koji se koristi u praksi, zasnovan je na **relacionom računu nad torkama**. On je deklarativan - mi opisujemo šta želimo, a SUBP sam odlučuje kako da to izvrši. Osnovni oblik SQL upita je:
> ```sql
> SELECT <lista obeležja>
> FROM <lista relacija>
> WHERE <logički izraz>
> ```

Sada ćemo se fokusirati na **relacionu algebru** i njene operacije, jer one čine osnovu za razumevanje svih upitnih jezika.

---

## Operacije relacione algebre

Relaciona algebra definiše skup operacija nad relacijama. Rezultat svake operacije je nova relacija - to je jako bitna osobina jer nam omogućava da **kombinujemo operacije** i gradimo složene upite korak po korak.

Operacije delimo na:

- **Osnovne skupovne operacije**: unija, presek, razlika
- **Specijalizovane operacije**: selekcija, projekcija, prirodni spoj, Dekartov proizvod, theta spajanje

Hajde da ih prođemo jednu po jednu.

---

## Osnovne skupovne operacije nad relacijama

Pošto su relacije, po definiciji, skupovi torki, nad njima možemo primeniti standardne skupovne operacije. Bitno je da obe relacije moraju biti definisane nad **istim skupom obeležja** $R$ - inače operacije nemaju smisla (ne možemo sabirati jabuke i kruške).

### Unija

**Unija** dve relacije $r(R)$ i $s(R)$ daje novu relaciju koja sadrži sve torke koje se nalaze u $r$, u $s$, ili u obe relacije.

$$r(R) \cup s(R) = \{t \mid t \in r \lor t \in s\}$$

Gde je:
- $r(R)$ - prva relacija nad skupom obeležja $R$
- $s(R)$ - druga relacija nad istim skupom obeležja $R$
- $t$ - torka
- $\lor$ - logičko ILI

Unija je kao spajanje dva spiska gostiju za venčanje - na konačnom spisku su svi koji se pojavljuju na bar jednom od dva spiska, bez ponavljanja (jer relacija je skup, a u skupu nema duplikata).

### Presek

**Presek** dve relacije $r(R)$ i $s(R)$ daje novu relaciju koja sadrži samo one torke koje se nalaze i u $r$ i u $s$.

$$r(R) \cap s(R) = \{t \mid t \in r \land t \in s\}$$

Gde je:
- $\land$ - logičko I

Presek je kao pronalaženje zajedničkih prijatelja - samo oni koji su na oba spiska.

### Razlika

**Razlika** relacija $r(R)$ i $s(R)$ daje novu relaciju koja sadrži torke koje se nalaze u $r$, ali **ne** i u $s$.

$$r(R) - s(R) = \{t \mid t \in r \land t \notin s\}$$

Gde je:
- $\notin$ - ne pripada skupu

Razlika je kao spisak pozvanica bez onih koji su se izvinili - uzimamo originalni spisak i izbacujemo one koji su rekli da ne dolaze.

### Primer - skupovne operacije

Zamislimo da imamo dve relacije $r$ i $s$ nad istim skupom obeležja $\{A, B\}$:

**Relacija $r$:**

| A | B |
|---|---|
| a1 | b1 |
| a2 | b2 |

**Relacija $s$:**

| A | B |
|---|---|
| a1 | b1 |
| a3 | b3 |

Hajde da izračunamo sve tri operacije:

**Unija** $r \cup s$ - sve torke iz obe relacije (bez duplikata):

| A | B |
|---|---|
| a1 | b1 |
| a2 | b2 |
| a3 | b3 |

Torka (a1, b1) se pojavljuje u obe relacije, ali u uniji se piše samo jednom.

**Presek** $r \cap s$ - samo zajedničke torke:

| A | B |
|---|---|
| a1 | b1 |

Jedino torka (a1, b1) postoji u obe relacije.

**Razlika** $r - s$ - torke iz $r$ koje nisu u $s$:

| A | B |
|---|---|
| a2 | b2 |

Torka (a2, b2) postoji u $r$, ali ne postoji u $s$.

> [!TIP]
> Obratite pažnju da je razlika **neasocijativna** operacija - $r - s \neq s - r$. Da smo računali $s - r$, dobili bismo (a3, b3). Unija i presek su asocijativne i komutativne operacije.

---

## Selekcija

Prešli smo osnovne skupovne operacije. Sada prelazimo na specijalizovane operacije, koje su mnogo češće na ispitu. Prva od njih je **selekcija**.

Zamislimo da imamo tabelu sa podacima o radnicima i želimo da vidimo samo one čija je plata veća od 5000. Ne trebaju nam svi redovi tabele, već samo oni koji ispunjavaju određeni uslov. Upravo to radi selekcija.

**Selekcija** (torki iz relacije) omogućava **izbor torki** relacije po nekom kriterijumu. Formalno:

$$\sigma_F(r(R)) = \{t \in r \mid F(t)\}$$

Gde je:
- $\sigma$ (sigma) - operator selekcije
- $F$ - logička formula (uslov, kriterijum) po kojem se torke selektuju
- $r(R)$ - relacija nad skupom obeležja $R$
- $t$ - torka iz relacije $r$
- $F(t)$ - formula $F$ je tačna za torku $t$

Biće selektovane samo one torke za koje je formula $F$ tačna. Zahteva se formalno definisanje sintakse za zapisivanje selekcionih formula tipa $F$.

### Primer 1 - Jednostavna selekcija

Posmatra se relacija $r$ (radnici):

| MBR | IME | POL | SPR | PLT |
|-----|-----|-----|-----|-----|
| 101 | Ana | ž | 11 | 3400 |
| 102 | Aca | m | 14 | 4200 |
| 110 | Ivo | m | 11 | 7000 |
| 111 | Olja | ž | 11 | 7200 |

**Upit:** Prikazati radnike čija je plata veća od 5000.

Formula: $F ::= PLT > 5000$

$$\sigma_{PLT > 5000}(r)$$

Rezultat:

| MBR | IME | POL | SPR | PLT |
|-----|-----|-----|-----|-----|
| 110 | Ivo | m | 11 | 7000 |
| 111 | Olja | ž | 11 | 7200 |

Vidimo da su selektovane samo one torke kod kojih je vrednost obeležja PLT veća od 5000.

### Primer 2 - Složena selekcija (konjunkcija uslova)

**Upit:** Prikazati radnike čija je plata veća od 4000 **i** rade na projektu sa šifrom 11.

Formula: $F ::= PLT > 4000 \land SPR = 11$

$$\sigma_{PLT > 4000 \land SPR = 11}(r)$$

Rezultat:

| MBR | IME | POL | SPR | PLT |
|-----|-----|-----|-----|-----|
| 110 | Ivo | m | 11 | 7000 |
| 111 | Olja | ž | 11 | 7200 |

Ana (PLT=3400) ne zadovoljava uslov PLT > 4000. Aca (SPR=14) ne zadovoljava uslov SPR = 11. Samo Ivo i Olja zadovoljavaju oba uslova.

---

## Projekcija

Selekcija bira **redove** (torke) iz relacije. Ali šta ako ne želimo sve kolone? Šta ako iz tabele sa 10 kolona želimo da vidimo samo ime i prezime? Za to nam služi **projekcija**.

**Projekcija** (restrikcija) relacije omogućava **izdvajanje vrednosti pojedinih kolona** iz relacije - to je projektovanje relacije na podskup skupa obeležja.

Za $X \subseteq R$:

$$\pi_X(r(R)) = \{t[X] \mid t \in r(R)\}$$

Gde je:
- $\pi$ (pi) - operator projekcije
- $X$ - podskup skupa obeležja $R$ na koji projektujemo
- $r(R)$ - relacija nad skupom obeležja $R$
- $t[X]$ - restrikcija torke $t$ na skup obeležja $X$

Projekcija je kao da iz lične karte čitamo samo ime i datum rođenja, zanemarujući sve ostale podatke.

### Primer 1 - Jednostavna projekcija

Data je relacija $r$ nad skupom obeležja $\{P, A, L\}$, gde je $P$ - pilot, $A$ - tip aviona, $L$ - broj leta:

| P | A | L |
|---|---|---|
| Aca | 747 | 101 |
| Ivo | 737 | 101 |
| Aca | 747 | 102 |
| Ana | DC9 | 110 |

**Upit:** Prikazati pilote i tipove aviona na kojima lete.

$$\pi_{PA}(r(PAL))$$

Rezultat:

| P | A |
|---|---|
| Aca | 747 |
| Ivo | 737 |
| Ana | DC9 |

Primetimo da je Aca leteo na avionu 747 dva puta (letovi 101 i 102), ali u rezultatu projekcije imamo samo jedan red (Aca, 747). To je zato što je relacija skup - duplikati se eliminišu.

> [!WARNING]
> Česta greška na ispitu: studenti zaborave da projekcija **eliminiše duplikate**! Pošto je rezultat projekcije relacija, a relacija je skup, ne mogu postojati identične torke u rezultatu.

### Primer 2 - Kombinovanje selekcije i projekcije

Ovo je vrlo čest obrazac - prvo selektujemo torke po nekom uslovu, a zatim projektujemo rezultat na željene kolone.

Koristi se ista relacija radnika:

| MBR | IME | POL | SPR | PLT |
|-----|-----|-----|-----|-----|
| 101 | Ana | ž | 11 | 3400 |
| 102 | Aca | m | 14 | 4200 |
| 110 | Ivo | m | 11 | 7000 |
| 111 | Olja | ž | 11 | 7200 |

**Upit:** Prikazati matične brojeve i imena radnika čija plata je veća od 4000, a rade na projektu sa šifrom 11.

Formula: $F ::= PLT > 4000 \land SPR = 11$

$$\pi_{MBR+IME}(\sigma_F(r))$$

Postupak:
1. Prvo se primeni selekcija $\sigma_F(r)$ - biraju se torke gde je PLT > 4000 i SPR = 11 (Ivo i Olja)
2. Zatim se na rezultat primeni projekcija $\pi_{MBR+IME}$ - izdvajaju se samo kolone MBR i IME

Rezultat:

| MBR | IME |
|-----|-----|
| 110 | Ivo |
| 111 | Olja |

> [!TIP]
> Obratite pažnju na redosled operacija: selekcija se piše "unutra" (kao argument), a projekcija "spolja". Čita se iznutra ka spolja - prvo selektuj, pa projektuj. Zapis $\pi_{MBR+IME}(\sigma_F(r))$ znači: "Uzmi relaciju $r$, primeni selekciju $\sigma_F$, pa na rezultat primeni projekciju $\pi_{MBR+IME}$."

---

## Prirodni spoj

Do sada smo radili sa jednom relacijom. Ali u relacionoj bazi podataka podaci su raspoređeni u više relacija (tabela). Kako da povežemo podatke iz različitih tabela? Odgovor je **spajanje**.

Zamislimo da u jednoj tabeli imamo podatke o radnicima (matični broj, ime), a u drugoj podatke o angažovanjima na projektima (matični broj radnika, šifra projekta). Da bismo videli imena radnika i projekte na kojima rade, moramo da spojimo ove dve tabele po zajedničkom obeležju - matičnom broju.

**Prirodni spoj** (natural join) relacija je operacija **spajanja torki** različitih relacija **po osnovu istih vrednosti zajedničkih obeležja**.

Date su relacije $r(R)$ i $s(S)$:

$$r(R) \bowtie s(S) = \{t \in Tuple(R \cup S) \mid t[R] \in r \land t[S] \in s\}$$

Gde je:
- $\bowtie$ - operator prirodnog spoja
- $Tuple(R \cup S)$ - skup svih mogućih torki nad unijom skupova obeležja $R$ i $S$
- $t[R] \in r$ - restrikcija torke $t$ na obeležja iz $R$ mora biti torka u relaciji $r$
- $t[S] \in s$ - restrikcija torke $t$ na obeležja iz $S$ mora biti torka u relaciji $s$

Prirodni spoj automatski pronalazi zajednička obeležja i spaja torke koje imaju iste vrednosti za ta obeležja.

### Primer 1 - Osnovni prirodni spoj

Data je relacija $r$ nad $\{A, B, C\}$:

| A | B | C |
|---|---|---|
| a1 | b1 | c1 |
| a1 | b2 | c2 |
| a1 | b3 | c3 |

Data je relacija $s$ nad $\{B, C, D\}$:

| B | C | D |
|---|---|---|
| b1 | c1 | d1 |
| b1 | c1 | d2 |
| b3 | c3 | d3 |
| b4 | c2 | d2 |

Zajednička obeležja su $B$ i $C$. Prirodni spoj $r \bowtie s$ spaja torke kojima se poklapaju vrednosti za $B$ i za $C$:

| A | B | C | D |
|---|---|---|---|
| a1 | b1 | c1 | d1 |
| a1 | b1 | c1 | d2 |
| a1 | b3 | c3 | d3 |

Hajde da proverimo: torka (a1, b1, c1) iz $r$ se spaja sa torkama (b1, c1, d1) i (b1, c1, d2) iz $s$ jer se B=b1 i C=c1 poklapaju. Torka (a1, b3, c3) se spaja sa (b3, c3, d3). Torka (a1, b2, c2) iz $r$ nema parnjaka u $s$ (nema torke sa B=b2 i C=c2), pa se gubi. Slično, torka (b4, c2, d2) iz $s$ nema parnjaka u $r$.

### Primer 2 - Spoj bez zajedničkih obeležja (Dekartov proizvod)

Ako relacije $r(R)$ i $s(S)$ **nemaju zajednička obeležja** ($R \cap S = \emptyset$), onda se prirodni spoj svodi na **Dekartov proizvod** - svaka torka iz $r$ se kombinuje sa svakom torkom iz $s$.

Data je relacija $r$ nad $\{A, B\}$:

| A | B |
|---|---|
| a1 | b1 |
| a2 | b2 |

Data je relacija $s$ nad $\{C, D\}$:

| C | D |
|---|---|
| c1 | d1 |
| c2 | d2 |

Prirodni spoj (u ovom slučaju Dekartov proizvod) $r \bowtie s$:

| A | B | C | D |
|---|---|---|---|
| a1 | b1 | c1 | d1 |
| a1 | b1 | c2 | d2 |
| a2 | b2 | c1 | d1 |
| a2 | b2 | c2 | d2 |

Svaka od 2 torke iz $r$ kombinuje se sa svake 2 torke iz $s$, dajući ukupno $2 \times 2 = 4$ torke.

### Primer 3 - Praktičan primer sa radnicima i projektima

Ovo je primer bliži realnom korišćenju. Date su tri relacije:

**Radnik:**

| MBR | IME | POL | PLT |
|-----|-----|-----|-----|
| 101 | Ana | ž | 3400 |
| 102 | Aca | m | 4200 |
| 110 | Ivo | m | 7000 |
| 111 | Olja | ž | 7200 |

**Radproj** (angažovanje radnika na projektima):

| MBR | SPR |
|-----|-----|
| 101 | 11 |
| 101 | 14 |
| 102 | 14 |
| 110 | 13 |
| 110 | 11 |

**Projekat:**

| SPR | NAP |
|-----|-----|
| 11 | X25 |
| 13 | Polaris |
| 14 | Univ. IS |

#### Upit 1: Izlistati matične brojeve radnika, šifre i nazive projekata na kojima rade

$$Radproj \bowtie Projekat$$

Zajedničko obeležje je SPR. Rezultat:

| MBR | SPR | NAP |
|-----|-----|-----|
| 101 | 11 | X25 |
| 101 | 14 | Univ. IS |
| 102 | 14 | Univ. IS |
| 110 | 13 | Polaris |
| 110 | 11 | X25 |

#### Upit 2: Izlistati matične brojeve i imena radnika koji rade na projektu sa šifrom 11

Ovaj upit zahteva kombinovanje selekcije, projekcije i spoja. Postoje dva ekvivalentna načina da se ovo zapiše:

**Način 1** - Prvo selektujemo iz Radproj, pa spojimo sa Radnik:

$$\pi_{MBR+IME}(\sigma_{SPR = 11}(Radproj) \bowtie Radnik)$$

**Način 2** - Prvo spojimo Radproj sa Radnik, pa selektujemo:

$$\pi_{MBR+IME}(\sigma_{SPR = 11}(Radproj \bowtie Radnik))$$

Rezultat u oba slučaja:

| MBR | IME |
|-----|-----|
| 101 | Ana |
| 110 | Ivo |

> [!IMPORTANT]
> Oba zapisa daju isti rezultat, ali **prvi način je efikasniji** u praksi. Zašto? Zato što prvo sužavamo skup torki selekcijom (manje torki za spajanje), a tek onda radimo spoj. U drugom slučaju prvo spajamo sve torke (skupa operacija), pa tek onda filtriramo. Ovo je princip koji optimizatori upita u SUBP-ovima koriste svakodnevno.

---

## Dekartov proizvod

**Dekartov proizvod** relacija je operacija koja formira **sve moguće kombinacije** torki iz dve relacije. To je specijalan slučaj spajanja gde se ne traži poklapanje ni po jednom obeležju - uslov je $R \cap S = \emptyset$.

$$r(R) \times s(S) = \{t \in Tuple(R \cup S) \mid t[R] \in r \land t[S] \in s\}$$

Gde je:
- $\times$ - operator Dekartovog proizvoda
- Svaka torka iz $r$ se kombinuje sa svakom torkom iz $s$

Ako relacija $r$ ima $m$ torki, a relacija $s$ ima $n$ torki, rezultat Dekartovog proizvoda ima $m \times n$ torki. Ovo brzo eksplodira - dve tabele od po 1000 redova daju milion kombinacija.

Dekartov proizvod sam po sebi retko daje korisne rezultate. On je koristan kao međukorak, u kombinaciji sa selekcijom, što nas dovodi do sledeće operacije.

---

## Theta spajanje

Zamislimo sledeći problem: imamo red vožnje vozova Niš - Beograd i red vožnje Beograd - Novi Sad. Želimo da pronađemo sve moguće varijante putovanja od Niša do Novog Sada sa presedanjem u Beogradu. Uslov je da vreme dolaska u Beograd mora biti **pre** vremena polaska iz Beograda (logično, moramo stići pre nego što nam sledeći voz krene).

Za ovakve upite koristimo **theta spajanje** - to je selektovanje torki po nekom kriterijumu iz Dekartovog proizvoda relacija.

$$r(R) \bowtie_F s(S) = \sigma_F(r \times s)$$

Gde je:
- $\bowtie_F$ - operator theta spajanja sa formulom $F$
- $\sigma_F$ - selekcija po formuli $F$
- $r \times s$ - Dekartov proizvod relacija $r$ i $s$

Theta spajanje je, dakle, **Dekartov proizvod praćen selekcijom**. Prvo se naprave sve moguće kombinacije, a zatim se zadrže samo one koje zadovoljavaju uslov $F$.

### Primer - Red vožnje

Data je relacija $r$ - red vožnje Niš - Beograd:

| PNI | DBG |
|-----|-----|
| 06:00 | 09:00 |
| 08:00 | 10:30 |
| 13:00 | 16:00 |

Gde je PNI - polazak iz Niša, DBG - dolazak u Beograd.

Data je relacija $s$ - red vožnje Beograd - Novi Sad:

| PBG | DNS |
|-----|-----|
| 10:00 | 11:15 |
| 12:00 | 13:30 |

Gde je PBG - polazak iz Beograda, DNS - dolazak u Novi Sad.

**Upit:** Prikazati sve moguće varijante za putovanje od Niša do Novog Sada sa presedanjem u Beogradu.

Uslov: moramo stići u Beograd pre polaska voza za Novi Sad, tj. $DBG < PBG$.

$$r \bowtie_{DBG < PBG} s = \sigma_{DBG < PBG}(r \times s)$$

Prvo napravimo Dekartov proizvod (3 × 2 = 6 kombinacija), pa selektujemo one gde je $DBG < PBG$:

| PNI | DBG | PBG | DNS |
|-----|-----|-----|-----|
| 06:00 | 09:00 | 10:00 | 11:15 |
| 06:00 | 09:00 | 12:00 | 13:30 |
| 08:00 | 10:30 | 12:00 | 13:30 |

Prva varijanta: krenemo u 06:00 iz Niša, stignemo u 09:00 u Beograd, krenemo u 10:00 za Novi Sad, stignemo u 11:15. Druga varijanta: isti polazak, ali čekamo voz u 12:00. Treća varijanta: krenemo u 08:00 iz Niša, stignemo u 10:30, uhvatimo voz u 12:00. Voz od 13:00 iz Niša stiže u 16:00 - kasno za oba beogradska polaska, pa se te kombinacije eliminišu.

> [!NOTE]
> Razlika između **prirodnog spoja** i **theta spajanja**: prirodni spoj automatski spaja po jednakosti zajedničkih obeležja. Theta spajanje koristi **proizvoljnu formulu** $F$ za spajanje - to može biti $<$, $>$, $\leq$, $\neq$, ili bilo koji drugi logički uslov.

---

## Pregled svih operacija relacione algebre

Hajde da napravimo sažet pregled svih operacija koje smo prošli, sa formalnim zapisima:

| Operacija | Oznaka | Formalna definicija |
|-----------|--------|---------------------|
| Unija | $r \cup s$ | $\{t \mid t \in r \lor t \in s\}$ |
| Presek | $r \cap s$ | $\{t \mid t \in r \land t \in s\}$ |
| Razlika | $r - s$ | $\{t \mid t \in r \land t \notin s\}$ |
| Selekcija | $\sigma_F(r)$ | $\{t \in r \mid F(t)\}$ |
| Projekcija | $\pi_X(r)$ | $\{t[X] \mid t \in r\}$ |
| Prirodni spoj | $r \bowtie s$ | $\{t \in Tuple(R \cup S) \mid t[R] \in r \land t[S] \in s\}$ |
| Dekartov proizvod | $r \times s$ | $\{t \in Tuple(R \cup S) \mid t[R] \in r \land t[S] \in s\}$, $R \cap S = \emptyset$ |
| Theta spajanje | $r \bowtie_F s$ | $\sigma_F(r \times s)$ |

> [!IMPORTANT]
> Rezultat svake operacije je **relacija**. To znači da rezultat jedne operacije može biti operand (ulaz) druge operacije. Upravo ovo svojstvo nam omogućava da gradimo složene izraze relacione algebre, kombinovanjem operacija - baš kao što u matematici možemo pisati $f(g(x))$.

---

## Kombinovanje operacija - zadaci za vežbu

Na kraju, da vidimo kako se operacije kombinuju u praksi. Date su sledeće relacije sa svojim šemama i ograničenjima:

- **radnik**(\{Mbr, Ime, Prz, Sef, Plt, God, Pre\}, \{Mbr\})
- **projekat**(\{Spr, Ruk, Nap, Nar\}, \{Spr\})
- **radproj**(\{Spr, Mbr, Brc\}, \{Spr + Mbr\})

Sa zavisnostima sadržavanja:
- radnik[Sef] $\subseteq$ radnik[Mbr]
- projekat[Ruk] $\subseteq$ radnik[Mbr]
- radproj[Mbr] $\subseteq$ radnik[Mbr]
- radproj[Spr] $\subseteq$ projekat[Spr]

Evo nekih primera upita koje bismo mogli zapisati koristeći operacije relacione algebre:

1. **Prikazati šifre i nazive projekata na kojima radi Ivan Tasić.**
   $\pi_{Spr+Nap}(\sigma_{Ime='Ivan' \land Prz='Tasić'}(radnik) \bowtie radproj \bowtie projekat)$

2. **Prikazati matične brojeve radnika koji rade na projektu sa šifrom 10 ili rade 5 sati.**
   $\pi_{Mbr}(\sigma_{Spr=10 \lor Brc=5}(radproj))$

3. **Prikazati projekte na kojima rade radnici čija je plata veća od 2500.**
   $\pi_{Spr+Nap}(\sigma_{Plt>2500}(radnik) \bowtie radproj \bowtie projekat)$

4. **Prikazati radnike kojima je šef radnik sa MBR=10, ili zarađuju više od 2600.**
   $\pi_{Mbr+Ime+Prz}(\sigma_{Sef=10 \lor Plt>2600}(radnik))$

5. **Prikazati podatke o projektima na kojima ne radi nijedan radnik.**
   $projekat - \pi_{Spr+Ruk+Nap+Nar}(projekat \bowtie radproj)$

   Ovde koristimo razliku: od svih projekata oduzimamo one koji se pojavljuju u spoju sa radproj (tj. one na kojima neko radi).

6. **Prikazati podatke o radnicima koji ne rade na projektu sa šifrom P1.**
   $radnik - (radnik \bowtie \sigma_{Spr='P1'}(radproj))$

7. **Prikazati radnike koji nisu rukovodioci projekata.**
   $\pi_{Mbr+Ime+Prz}(radnik) - \pi_{Ruk+Ime+Prz}(\rho_{Ruk/Mbr}(radnik) \bowtie projekat)$

8. **Prikazati projekte na kojima radi šef radnika sa MBR=2001.**
   Prvo pronađemo šefa: $\pi_{Sef}(\sigma_{Mbr=2001}(radnik))$, zatim projekte tog šefa.

9. **Prikazati sve projekte na kojima rade oni radnici koji rade na projektu sa nazivom "Univerzitetski IS".**
   Prvo pronađemo radnike na tom projektu, pa zatim sve projekte tih radnika.

10. **Prikazati radnike koji rade na projektu sa nazivom "Nabavka".**
    $\pi_{Mbr+Ime+Prz}(radnik \bowtie radproj \bowtie \sigma_{Nap='Nabavka'}(projekat))$

11. **Prikazati radnike koji na projektu "Prodaja" rade više od 10 sati nedeljno.**
    $\pi_{Ime+Prz}(radnik \bowtie \sigma_{Brc>10}(radproj) \bowtie \sigma_{Nap='Prodaja'}(projekat))$

12. **Prikazati projekte kojima rukovodi radnik Milan Perić.**
    $\pi_{Spr+Nap}(\rho_{Ruk/Mbr}(\sigma_{Ime='Milan' \land Prz='Perić'}(radnik)) \bowtie projekat)$

> [!CAUTION]
> Na ispitu, obratite pažnju na to da li upit traži podatke o entitetima koji **jesu** u nekom skupu ili koji **nisu**. Kada se traže oni koji "nisu" (npr. "ne rade na projektu X"), obično se koristi operacija **razlike**. Ovo je čest izvor grešaka.

---

## Veza sa SQL-om

Na kraju, da povežemo teoriju sa praksom. SQL, koji se koristi u realnim SUBP-ovima, zasnovan je na relacionom računu nad torkama (ne na relacionoj algebri), ali između njih postoji direktna veza. Svaki izraz relacione algebre može se prevesti u SQL i obrnuto.

Na primer, izraz:

$$\pi_{IME+PRZ+BIP}(\sigma_{BIP > 5}(Fakultet \bowtie Projektant))$$

U SQL-u se može zapisati na dva načina:

```sql
SELECT IME, PRZ, BIP
FROM Fakultet, Projektant
WHERE BIP > 5 AND Fakultet.SFK = Projektant.SFK
```

ili korišćenjem eksplicitnog spajanja:

```sql
SELECT IME, PRZ, BIP
FROM Fakultet NATURAL JOIN Projektant
WHERE BIP > 5
```

Oba zapisa daju isti rezultat. SQL ključna reč `NATURAL JOIN` odgovara operatoru prirodnog spoja ($\bowtie$), `WHERE` odgovara selekciji ($\sigma$), a `SELECT` sa listom obeležja odgovara projekciji ($\pi$).

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

**P:** Šta je operacijska komponenta relacionog modela podataka?

**P:** Koja su tri dela (jezika) operacijske komponente?

**P:** Šta je jezik za manipulaciju podacima (DML)?

**P:** Koje tri operacije obuhvata DML?

**P:** Šta radi operacija dodavanja torke (Add)?

**P:** Šta radi operacija brisanja torke (Delete)?

**P:** Šta radi operacija modifikacije torke (Update)?

**P:** Šta je jezik za definiciju podataka (DDL)?

**P:** Šta obuhvataju operacije DDL-a?

**P:** Šta je upitni jezik (QL)?

**P:** Od čega se sastoji upitni jezik?

**P:** Koje su dve vrste teoretskih upitnih jezika u relacionom modelu?

**P:** Na čemu je zasnovana relaciona algebra?

**P:** Na čemu je zasnovan relacioni račun?

**P:** Koje su dve varijante relacionog računa?

**P:** Na čemu je zasnovan SQL?

**P:** Koji je osnovni oblik SQL naredbe za upite?

**P:** Koje su tri osnovne skupovne operacije nad relacijama?

**P:** Kako glasi formalna definicija unije relacija?

**P:** Kako glasi formalna definicija preseka relacija?

**P:** Kako glasi formalna definicija razlike relacija?

**P:** Koji je uslov za primenu skupovnih operacija na dve relacije?

**P:** Da li je razlika relacija komutativna operacija?

**P:** Šta je selekcija torki iz relacije?

**P:** Kako glasi formalna definicija selekcije?

**P:** Šta predstavlja simbol $\sigma$ u selekciji?

**P:** Šta je formula $F$ u selekciji?

**P:** Šta je projekcija (restrikcija) relacije?

**P:** Kako glasi formalna definicija projekcije?

**P:** Šta predstavlja simbol $\pi$ u projekciji?

**P:** Šta se dešava sa duplikatima pri projekciji?

**P:** Kako se kombinuju selekcija i projekcija?

**P:** Šta je prirodni spoj relacija?

**P:** Kako glasi formalna definicija prirodnog spoja?

**P:** Po čemu se vrši spajanje torki kod prirodnog spoja?

**P:** Šta se dešava sa torkama koje nemaju parnjaka u drugoj relaciji pri prirodnom spoju?

**P:** Šta je Dekartov proizvod relacija?

**P:** Kako glasi formalna definicija Dekartovog proizvoda?

**P:** Koliko torki ima rezultat Dekartovog proizvoda ako prva relacija ima $m$, a druga $n$ torki?

**P:** Šta je theta spajanje relacija?

**P:** Kako glasi formalna definicija theta spajanja?

**P:** Koja je veza između theta spajanja i Dekartovog proizvoda?

**P:** Koja je razlika između prirodnog spoja i theta spajanja?

**P:** Šta se dešava kada relacije u prirodnom spoju nemaju zajednička obeležja?

**P:** Koja je ključna osobina svih operacija relacione algebre u pogledu tipa rezultata?

**P:** Zašto je bitno da rezultat operacije relacione algebre bude relacija?

**P:** Kako se u SQL-u izražava selekcija?

**P:** Kako se u SQL-u izražava projekcija?

**P:** Kako se u SQL-u izražava prirodni spoj?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite strukturu operacijske komponente relacionog modela podataka i ulogu svakog njenog dela.

**O:** Operacijska komponenta se sastoji od tri dela: (1) jezik za manipulaciju podacima (DML) - operacije za ažuriranje relacija (dodavanje, brisanje, modifikacija torki); (2) jezik za definiciju podataka (DDL) - operacije za upravljanje šemom baze podataka (kreiranje, brisanje, modifikovanje delova šeme); (3) upitni jezik (QL) - operacije za izražavanje upita nad relacijama i pružanje podataka na uvid korisniku. DML menja podatke, DDL menja strukturu, a QL čita podatke.

**P:** Koja je razlika između relacione algebre i relacionog računa kao teoretskih upitnih jezika?

**O:** Relaciona algebra je zasnovana na teoriji skupova i skupovnih operacija, i ona opisuje **kako** doći do rezultata (proceduralan pristup - zadaje se niz operacija). Relacioni račun je zasnovan na predikatskom računu I reda i opisuje **šta** želimo da dobijemo (deklarativan pristup). SQL je zasnovan na relacionom računu nad torkama, ali oba pristupa imaju istu izražajnu moć - svaki upit koji se može izraziti jednim, može se izraziti i drugim.

**P:** Data je relacija Radnik sa torkama (101, Ana, 3400), (102, Aca, 4200), (110, Ivo, 7000). Zapišite izraz relacione algebre koji prikazuje imena radnika sa platom većom od 4000 i pokažite rezultat korak po korak.

**O:** Izraz: $\pi_{IME}(\sigma_{PLT>4000}(Radnik))$. Korak 1 - selekcija $\sigma_{PLT>4000}$: biramo torke gde je PLT > 4000, ostaju (102, Aca, 4200) i (110, Ivo, 7000). Korak 2 - projekcija $\pi_{IME}$: iz preostalih torki izdvajamo samo kolonu IME. Rezultat sadrži: Aca, Ivo.

**P:** Objasnite razliku između prirodnog spoja i theta spajanja, uz konkretan primer kada bismo koristili svako od njih.

**O:** Prirodni spoj automatski spaja torke po jednakosti vrednosti zajedničkih obeležja (npr. spajanje tabele Radnik i Radproj po MBR). Theta spajanje koristi proizvoljnu formulu za uslov spajanja, koja ne mora biti jednakost (npr. spajanje redova vožnje gde je vreme dolaska manje od vremena polaska: $DBG < PBG$). Theta spajanje se formalno definiše kao selekcija nad Dekartovim proizvodom: $r \bowtie_F s = \sigma_F(r \times s)$.

**P:** Zašto je bitno da rezultat svake operacije relacione algebre bude relacija? Kako to utiče na mogućnost izražavanja upita?

**O:** Ovo svojstvo se naziva **zatvorenost** relacione algebre - rezultat operacije je istog tipa kao operandi. Zahvaljujući tome, rezultat jedne operacije može biti ulaz (operand) druge operacije. To nam omogućava kompoziciju operacija i gradnju složenih izraza, npr. $\pi_{IME}(\sigma_{PLT>4000}(Radnik \bowtie Radproj))$, gde se rezultat spoja prosleđuje selekciji, pa projekciji.

**P:** Objasnite kako biste zapisali upit "Prikazati radnike koji ne rade ni na jednom projektu" koristeći operacije relacione algebre. Koja operacija je ključna i zašto?

**O:** Ključna operacija je **razlika**. Pristup: iz skupa svih radnika oduzimamo one koji se pojavljuju u spoju sa tabelom angažovanja. Izraz: $Radnik - (Radnik \bowtie Radproj)$, uz eventualnu projekciju pre razlike da se osigura isti skup obeležja. Razlika je jedini način da u relacionoj algebri izrazimo negaciju ("oni koji nisu", "oni koji ne rade").

**P:** Pokažite na primeru red vožnje Niš-Beograd-Novi Sad kako theta spajanje koristi Dekartov proizvod. Zašto sam Dekartov proizvod nije dovoljan?

**O:** Dekartov proizvod formira sve moguće kombinacije polazaka (6 kombinacija za 3 × 2). Međutim, mnoge kombinacije su besmislene (npr. dolazak u BG u 16:00, a polazak za NS u 10:00). Theta spajanje dodaje uslov $DBG < PBG$ koji eliminiše nemoguće kombinacije, ostavljajući samo 3 smislena itinerera. Sam Dekartov proizvod bez selekcije retko daje korisne rezultate.

**P:** Koje su tri skupovne operacije nad relacijama i koji je preduslov za njihovu primenu? Ilustrujte primerom.

**O:** To su unija ($r \cup s$), presek ($r \cap s$) i razlika ($r - s$). Preduslov je da obe relacije moraju biti nad **istim skupom obeležja** $R$ - inače operacije nisu definisane. Na primer, za $r = \{(a1,b1), (a2,b2)\}$ i $s = \{(a1,b1), (a3,b3)\}$: unija daje tri torke, presek daje jednu torku (a1,b1), razlika $r-s$ daje (a2,b2).

**P:** Zašto projekcija eliminiše duplikate i kako to može uticati na broj torki u rezultatu?

**O:** Projekcija eliminiše duplikate jer je rezultat projekcije relacija, a relacija je po definiciji **skup** torki - u skupu ne mogu postojati identični elementi. Kada projektujemo na manji skup obeležja, torke koje su bile različite mogu postati identične (jer su se razlikovale samo po obeležjima koja smo izbacili). Broj torki u rezultatu je uvek manji ili jednak broju torki u polaznoj relaciji.
