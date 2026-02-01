![banner](./banner.png)

> [!WARNING]
> **DOKUMENT JE JOŠ UVEK U IZRADI I PODLOŽAN JE PROMENAMA.**
> Sadržaj se aktivno dopunjuje, ispravlja i unapređuje. Struktura, formulacije i primeri mogu biti izmenjeni bez prethodne najave. Dokument koristiti kao **radnu verziju** i uvek ga uporediti sa zvaničnim materijalima sa predavanja i vežbi.

## Autori
- **IN 37/2023:** _Marko Gordić_
- **IN 16/2023:** _Sanja Štetin_
- **IN 19/2023:** _Nikola Radosavljev_

**Predmetni profesor:** Slavica Kordić
**Asistent:** Miroslav Tomić 

## Napomene

> [!Caution]
> Skripta je napravljena na osnovu zvaničnih materijala sa predavanja i vežbi. Podložna je greškama. Preporučuje se da se koristi kao dodatak uz zvanične materijale.

> [!Important]
> Unutar skripte, određena pitanja će biti obeležena sa ✨. Ovo označava pitanja koja su istaknuta na predavanjima kao bitna za pripremu PZ.

> [!Tip]
> Bolje je boriti se i gubiti bitku nego nikada se ne izboriti. – Hegel

## Sadržaj

1. [Osnovni pojmovi](#1-osnovni-pojmovi)
2. [Koncepcija baza podataka](#2-koncepcija-bp)
3. [Model podataka](#3-model-podataka)
4. [ER model](#4-er-model)
5. [Relacioni model](#5-relacioni-model)
6. [Metode pristupa i organizacija datoteka](#6-metode-pristupa-i-organizacija-datoteka)
7. [Serijska i sekvencijalna organizacija datoteka](#7-serijska-i-sekvencijalna-organizacija-datoteka)
8. [Rasute organizacije datoteka](#8-rasute-organizacije-datoteka)

## 1. Osnovni pojmovi

### 1.1 Realni sistem

Realni sistem je egzistencija u realnom svetu, posmatrana kao deo tog sveta, koja ima jasno definisan cilj delovanja, raspolaže određenim resursima (činiocima), ostvaruje svoje ciljeve kroz procese, ima određenu strukturu i funkcioniše u interakciji sa okruženjem.

### 1.2 Primer realnog sistema

Primer **realnog sistema** je organizacija ili poslovni sistem koji postoji i funkcioniše u stvarnom svetu, nezavisno od informacionog sistema (npr. fakultet, banka, bolnica, preduzeće).

### 1.3 ✨ Informacioni sistem (IS) ✨

**Informacioni sistem (IS)** je model realnog sistema, realizovan dominantno softverskim sredstvima, koji predstavlja osnovnu infrastrukturu neophodnu za funkcionisanje savremene organizacije.

**Cilj informacionog sistema** je čuvanje i obezbeđivanje informacija o funkcionisanju realnih sistema, radi podrške poslovanju i donošenju odluka.

**Zadaci informacionog sistema** su:
- obuhvat (akvizicija) podataka
- skladištenje podataka
- prenos podataka
- prezentovanje podataka
- obrada podataka
- automatizacija upravljačkih funkcija u realnom sistemu

### 1.4 Primer informacionog sistema

Bankovne aplikacije (tekući račun, klijenti, transakcije...) 
Transport (red vožnje/letenja, rezervacija/kupovina karata...)
Telekomunikacije (podaci o pozivima, model mreže, telefonski računi...)
Medicina (podaci o pacijentima, istorija bolesti...)

### 1.5 Navesti činioce informacionog sistema

1. Računarsko komunikaciona i softverska infrastruktura
2. Baza ("skladište") podataka
3. Aplikacije (softverski paketi) za rad sa podacima
4. Projektna i korisnička dokumentacija
5. Krajnji korisnik
6. Tim za obezbeđenje eksploatacije i održavanja

### 1.6 ✨ Zašto smo prešli na baze? Koje su mane starih sistema? ✨

Stari sistemi su imali veliku redundantnost podataka, što je često dovodilo do **nekonzistentnosti**, **otežanog održavanja** i **problema pri istovremenom pristupu podacima**.

Baze podataka, posebno relacione, uvode centralizovano upravljanje podacima i mehanizme integriteta koji obezbeđuju konzistentnost i pouzdanost podataka.

### 1.7 ✨ Entitet ✨

**Entitet** je činilac (resurs) poslovanja u realnom sistemu koji je predmet posmatranja i o kome se u bazi podataka čuvaju informacije.

> [!Important]
> **Entitet** je **konkretan**, **pojedinačan objekat** iz realnog sveta koji posmatramo.

> [!Note]
> Primeri entiteta
> **Student - Jovana Minčić**
  Entitet koji predstavlja osobu upisanu na fakultet.
  **Predmet - Baze Podataka**
  Entitet koji predstavlja nastavni predmet na fakultetu.
  **Račun - #2025/017**
  Entitet koji predstavlja poslovni dokument.

Entitet predstavlja:
- svaku **jedinicu posmatranja** u realnom svetu
- realni objekat ili pojam koji ima **određene osobine (atribute)**
- skup karakteristika od kojih se **biraju samo one koje su relevantne** za dati informacioni sistem
- činilac (resurs) poslovanja koji postoji nezavisno i može se jednoznačno identifikovati


### 1.8 ✨ Klasa realnih entiteta ✨

**Klasa realnih entiteta** je skup sličnih entiteta, odnosno skup entiteta koji poseduju zajednička svojstva (osobine) relevantna za posmatrani informacioni sistem.

> [!Note]
> Primeri entiteta
> **Student**
  Klasa realnih entiteta koja obuhvata sve studente fakulteta.
  **Zaposleni**
  Klasa realnih entiteta koja obuhvata sve zaposlene u organizaciji.

Formalan zapis:
`E = { e_i | P(e_i) }`

gde:
- `e_i` predstavlja pojedinačni realni entitet
- `P(e_i)` predstavlja skup zajedničkih osobina koje entitet mora da poseduje da bi pripadao klasi

> [!Note]
> Primer
> **Realni entitet** je **Slavica Kordić**, a **klasa realnih entiteta** kojoj pripada je **profesor**.

> [!Note]
> Primer
> **Realni entitet** je **Petar Petrović Njegoš**, a **klasa realnih entiteta** kojoj pripada je **pesnik**.

### 1.9 ✨ Poveznik ✨

Entiteti realnog sistema nalaze se u međusobnim odnosima (vezama).

**Poveznik** predstavlja relaciju koja opisuje **odnos između dva ili više realnih entiteta**, odnosno odnos između entiteta ili već definisanih poveznika, u okviru posmatranog informacionog sistema.

### 1.10 ✨ Klasa poveznika ✨

**Klasa poveznika** je skup poveznika koji poseduju ista zajednička svojstva i opisuju isti tip odnosa između entiteta.

Formalan zapis:
`S = { (e1, …, em) | P(e1, …, em) }`

gde:
- `e1, …, em` predstavljaju entitete (ili poveznike) koji učestvuju u vezi
- `P(e1, …, em)` predstavlja skup zajedničkih osobina koje definišu tu klasu poveznika
 
### 1.11 Obeležje i vrste obeležja

**Obeležje (atribut)** je osobina klase realnih entiteta ili klase poveznika kojom se opisuju njihove karakteristike. Svako obeležje ima svoju semantiku i domen vrednosti koje može da poprimi. Primeri obeležja su: **matični broj**, **ime**, **prezime** i slično.

**Vrste obeležja**, prema mogućnosti dekomponovanja na celine nižeg reda, su:

1. **Elementarno obeležje**
   - ne može se dalje dekomponovati,
   - predstavlja atomičnu (elementarnu) vrednost,
   - primeri: *grad*, *ulica*, *broj*.

2. **Složeno obeležje**
   - može se dekomponovati na više jednostavnijih obeležja,
   - predstavlja složenu vrednost,
   - primer:
     ```text
     ADRESA = (grad, ulica, broj)
     ```

3. **Skupovno obeležje**
   - predstavlja skup vrednosti istog tipa,
   - jedno obeležje može imati više vrednosti,
   - primeri: *brojevi telefona*, *email adrese*.
 
### 1.12 ✨ Domen ✨

**Domen** je specifikacija skupa mogućih vrednosti jednog obeležja, zajedno sa definisanim dozvoljenim relacijama i operacijama nad tim skupom.
On reprezentuje skup svih vrednosti koje neko obeležje može da poprimi.

**Vrste domena** prema načinu nastanka su:

1. **Predefinisani (primitivni) domeni**
   Domeni koji su unapred definisani u okviru sistema za upravljanje bazom podataka
   (npr. ceo broj, realan broj, karakter, string).

2. **Korisnički definisani (izvedeni) domeni**
   Domeni koje definiše korisnik na osnovu predefinisanih domena, uz dodatna ograničenja
   (npr. domen *Ocena* sa vrednostima od 6 do 10).


### 1.13 Podatak

**Podatak** je uređena četvorka
`(Entitet, Obeležje, Vreme, Vrednost)`.

Semantičku komponentu podatka čine **entitet, obeležje i vreme**.
To znači da sama vrednost, bez informacije o tome *na šta se odnosi*, *koje je obeležje* i *u kom trenutku važi*, **ne predstavlja podatak**, jer nema kontekst.

Komponenta **vreme** može se izostaviti ukoliko se uvede konvencija da se podatak odnosi na trenutak u kojem se nad njim vrši manipulacija, ili ako se vreme modeluje kao posebno obeležje.

### 1.14 ✨ Tipa entiteta (TE) ✨

**Tip entiteta (TE)** je model klase realnih entiteta i definiše se svojim nazivom `N` i skupom obeležja `Q = {A1, …, An}`, gde je `Q` podskup skupa obeležja klase realnih entiteta.

Drugim rečima, tip entiteta opisuje **kakva vrsta stvari postoji u sistemu i koje podatke o njoj čuvamo**, bez navođenja konkretnih vrednosti.

> [!Note]
> Primer tipa entiteta
`Korisnik({UserID, Ime, Prezime, Email, TipPretplate})`

### 1.15 ✨ Pojava tipa entiteta (TE) ✨

**Pojava tipa entiteta** predstavlja model jednog realnog entiteta u informacionom sistemu.

Formalno, pojava tipa entiteta se definiše kao:
`p(N) = {(A1, a1), …, (An, an)}`

gde važi:

- `N` – naziv tipa entiteta
- `p(N)` – pojava tipa entiteta `N`, odnosno konkretna instanca tog tipa
- `Q = {A1, …, An}` – skup obeležja tipa entiteta
- `Ai` – i-to obeležje tipa entiteta
- `ai` – vrednost obeležja `Ai` za konkretnu pojavu
- `dom(Ai)` – domen obeležja `Ai`, tj. skup dozvoljenih vrednosti
- uslov `ai ∈ dom(Ai)` znači da svaka vrednost obeležja mora pripadati svom domenu

Ako se u skupu obeležja uvede redosled, pojava tipa entiteta može se posmatrati kao torka `(a1, …, an)`.

Tip entiteta formalno predstavlja skup svih svojih pojava:
`SP(N) = { p_i | P(p_i) }`

gde:

- `SP(N)` – skup pojava tipa entiteta `N`
- `p_i` – i-ta pojava tipa entiteta
- `P(p_i)` – uslov koji određuje da `p_i` predstavlja važeću pojavu tipa entiteta

Svaka pojava tipa entiteta predstavlja tačno jedan realni entitet.

> [!Note]
> Primer pojave tipa entiteta
> Tip entiteta – Osoba - `Osoba({Ime, Prezime, Uloga})`
> 
> **Jedna pojava tipa entiteta može biti:**
> `p(Osoba) = {(Ime, Slavica), (Prezime, Kordić), (Uloga, profesor)}`


### 1.16 ✨ Identifikator tipa entiteta (TE) ✨

**Identifikator tipa entiteta (TE)** je skup obeležja čija je uloga da obezbedi **jedinstvenu identifikaciju svake pojave tipa entiteta**.

**Identifikator pojave tipa entiteta** je konkretna vrednost identifikatora TE koja jednoznačno označava **najviše jednu pojavu tipa entiteta**. On predstavlja **jednu od četiri komponente podatka**.

Identifikator tipa entiteta može biti:

1. **Interni identifikator**
   - predstavlja podskup skupa obeležja tog tipa entiteta
   - formiran je od obeležja koja opisuju sam realni entitet
   - primer: za tip entiteta *Radnik* – `JMBG`

2. **Eksterni identifikator**
   - ne predstavlja podskup skupa obeležja tog tipa entiteta
   - veštački je uveden radi identifikacije pojava
   - primer: za tip entiteta *Radnik* – `id_radnika`


### 1.17 ✨ Ključa tipa entiteta (TE) ✨

> [!Caution]
> **Ovo pitanje sigurno dolazi kao prvo pitanje prilikom polaganja usmenog ispita!**

> [!Important]
> **Svaki ključ je identifikator, ali svaki identifikator nije ključ.**

✨ **Ključ tipa entiteta (TE)** je **minimalni interni identifikator** tipa entiteta.

Formalno, neka je dat tip entiteta `N` sa skupom obeležja `Q = {A1, …, An}`. Skup obeležja `X ⊆ Q` predstavlja **ključ** tipa entiteta ako važe sledeća svojstva:

- **Svojstvo jednoznačne identifikacije**
  Ne postoje dve pojave tipa entiteta `N` sa istom vrednošću skupa obeležja `X`, a svaka pojava tipa entiteta mora imati definisanu vrednost za sva obeležja iz skupa `X`.

- **Svojstvo minimalnosti**
  Ne postoji pravi podskup skupa `X` koji takođe zadovoljava svojstvo jednoznačne identifikacije.

Svaki tip entiteta poseduje **bar jedan ključ**.

Tip entiteta se formalno predstavlja kao uređena struktura:
`N(Q, C)`

gde:
- `N` predstavlja naziv tipa entiteta
- `Q` predstavlja skup obeležja tipa entiteta
- `C` predstavlja skup ograničenja tipa entiteta
- `K` predstavlja skup ključeva tipa entiteta, pri čemu važi `K ⊆ C`

Pošto skup ključeva pripada skupu ograničenja, skup `C` nikada nije prazan.

**Primarni ključ** je jedan izabrani ključ iz skupa ekvivalentnih ključeva TE, često se označava podvlačenjem.

### 1.18 ✨ Tip poveznika (TP) ✨

**Tip poveznika (TP)** povezuje dva ili više tipova entiteta (TE) ili prethodno definisanih tipova poveznika. On predstavlja model veza između realnih entiteta ili između veza u informacionom sistemu.

Tip poveznika se formalno predstavlja kao uređena struktura:
`N(N1, N2, …, Nm, Q, C)`

gde:
- `N` predstavlja naziv tipa poveznika
- `N1, N2, …, Nm` predstavljaju povezane tipove entiteta ili tipove poveznika
  (u ovom skupu isti tip može da se pojavi više puta)
- `Q` predstavlja skup obeležja tipa poveznika (može biti prazan skup)
- `C` predstavlja skup ograničenja tipa poveznika
- `K` predstavlja skup ključeva tipa poveznika, pri čemu važi `K ⊆ C`, zbog čega skup `C` nikada nije prazan

> [!Note]
> Primer tipa poveznika:
`Sluša(Student, Predmet, {Semestar}, C1)`

Tip poveznika formalno predstavlja skup svojih pojava:
`SP(N) = { (p1, …, pm) | P(p1, …, pm) }`

gde:
- `pi` predstavlja jednu pojavu tipa entiteta ili tipa poveznika
- `P(p1, …, pm)` predstavlja uslov koji definiše važeću pojavu tipa poveznika


### 1.19 Pojava tipa poveznika

**Pojava tipa poveznika** `N(N1, N2, …, Nm, {B1, …, Bk}, C)`
reprezentuje jedan konkretan poveznik u realnom sistemu.

Formalno, pojava tipa poveznika se predstavlja kao:
`p(N) = (p1, …, pm)(N) = { (B1, b1), …, (Bk, bk) }`

gde:
- `p1, …, pm` predstavljaju pojave povezanih tipova entiteta ili tipova poveznika
- `B1, …, Bk` predstavljaju obeležja tipa poveznika
- `b1, …, bk` predstavljaju vrednosti obeležja tipa poveznika

Pri tome važi:
- svako obeležje mora imati vrednost iz domena koji mu je pridružen
- skup svih pojava tipa poveznika mora zadovoljiti skup ograničenja `C`

### 1.20 ✨ Identifikator tipa poveznika (TP) ✨

**Identifikator tipa poveznika (TP)** je niz `(N1, N2, …, Nm)` ili neki njegov **neprazan podniz** i ima ulogu da obezbedi **jedinstvenu identifikaciju svake pojave tipa poveznika**.

**Identifikator pojave tipa poveznika** je niz `(p1, …, pm)` gde svaka komponenta predstavlja pojavu odgovarajućeg povezanog tipa. Ovim nizom se označava **najviše jedna pojava tipa poveznika**, odnosno određuje da li je dati niz pojava `(p1, …, pm)` u vezi ili nije.

### 1.21 Ključ tipa poveznika (TP)

**Ključ tipa poveznika (TP)** je skup obeležja `X`, izveden na osnovu ključeva povezanih tipova `(N1, N2, …, Nm)`. U praksi je to najčešće **podskup unije ključeva povezanih tipova**.

Neka je: `X = {A1, …, An}`

gde:
- `A1, …, An` predstavljaju obeležja izvedena iz ključeva povezanih tipova

Skup `X` predstavlja ključ tipa poveznika ako važe sledeća svojstva:

- **Svojstvo jedinstvene identifikacije**
  Ne postoje dve pojave tipa poveznika `N` sa istom vrednošću skupa obeležja `X`.

- **Svojstvo minimalnosti**
  Ne postoji pravi podskup skupa `X` koji takođe zadovoljava svojstvo jedinstvene identifikacije.


### 1.21 Definicija strukture podataka

**Struktura podataka** je orijentisani graf `G(V, ρ)`.

gde:
- skup `V` predstavlja **čvorove grafa**, gde svaki čvor odgovara nekom podatku ili grupi podataka i ima jasno definisano značenje odnosno semantiku
- skup `ρ` predstavlja **grane grafa**, koje opisuju veze između podataka, pri čemu svaka veza ima svoje značenje i pravac

Struktura podataka definiše **kako su podaci organizovani i kako su međusobno povezani**. Čvorovi predstavljaju same podatke, dok grane opisuju odnose između njih i način na koji se može kretati ili pristupati podacima.

Na ovaj način, struktura podataka omogućava da se podaci ne posmatraju kao izolovane vrednosti, već kao **povezana celina sa jasno definisanim značenjem i pravilima korišćenja**.

### 1.22 Vrste strukture podataka

**Vrste struktura podataka prema nivou apstrakcije pridružene semantike** su:
- **Logička struktura obeležja** – opisuje strukturu i značenje pojedinačnih obeležja
- **Logička struktura podataka** – opisuje logičke veze između podataka, nezavisno od načina njihovog fizičkog smeštanja
- **Fizička struktura podataka** – opisuje način na koji su podaci fizički organizovani i smešteni u memoriji ili na sekundarnim memorijskim medijima

**Vrste struktura podataka prema broju direktnih prethodnika i sledbenika čvora** su:
- **Linearna struktura podataka** – svaki čvor ima najviše jednog prethodnika i jednog sledbenika
- **Struktura tipa stabla** – čvor može imati jednog prethodnika i više sledbenika
- **Ciklična struktura podataka** – čvorovi su povezani tako da formiraju ciklus

### 1.23 Logička struktura obeležja

**Logička struktura obeležja (LSO)** je struktura definisana nad skupom **tipova entiteta (TE)**, **tipova poveznika (TP)** i njihovih obeležja. Ona predstavlja **model dela realnog sistema** i formalno se može opisati kao:
`M = (STE, RTE)`

gde:
- `STE` predstavlja **skup tipova** (tipova entiteta i tipova poveznika)
- `RTE` predstavlja **relaciju koja daje strukturu skupu STE** i modelira odnose koji postoje između realnih entiteta istih ili različitih klasa

Logička struktura obeležja je **najviši nivo apstrakcije**, jer opisuje *šta postoji u sistemu* i *kako je međusobno povezano*, bez ulaska u detalje implementacije.

### 1.24 Pristupi organizaciji LSO

Postoje dva osnovna pristupa organizaciji logičke strukture obeležja:

1. **Tipovi entiteta (TE) i tipovi poveznika (TP) su čvorovi**
   - `STE` sadrži skup svih TE i TP sistema
   - `RTE` sadrži grane koje prikazuju veze TP sa povezanim tipovima
   - simboli za TE i TP mogu, ali ne moraju, biti različiti
   - **ovaj pristup se koristi u praksi i na vežbama**

2. **Tipovi entiteta (TE) su čvorovi, a tipovi poveznika (TP) su grane** 
   - `STE` sadrži samo skup svih TE sistema
   - `RTE` sadrži grane koje predstavljaju TP i njihove veze sa povezanim tipovima
   - ovaj pristup dovodi do problema jer:
     - TP ne može imati sopstvena obeležja i ograničenja
     - TP ne može biti povezan sa drugim TP


### 1.25 Logička struktura podataka

**Logička struktura podataka (LSP)** definiše se pomoću posebne relacije nad skupom podataka, u granicama zadate **logičke strukture obeležja (LSO)**.

LSO predstavlja **kontekst i šemu** za LSP, odnosno određuje koje strukture podataka mogu postojati i kako su one logički povezane.

**Tip sloga** je linearna struktura skupa obeležja datog tipa entiteta (TE) i predstavlja opis *kako
jedan slog izgleda*, odnosno koja obeležja sadrži i kojim redosledom.

**Slog (N-torka)** je konkretna realizacija tipa sloga i predstavlja **jedan zapis u bazi podataka**, odnosno skup vrednosti obeležja koji opisuju **jednu pojavu tipa entiteta**.

Drugim rečima, slog je **jedan red u tabeli**, a svaka njegova kolona odgovara jednom obeležju.

> [!Note]
> Pojava tipa entiteta, posmatrana u okviru LSO, ekvivalentna je pojmu **sloga**.

**Datoteka** je kontekstna LSO i predstavlja strukturu podataka nad skupom pojava jednog tipa entiteta, odnosno skup slogova kojima kontekst određuje tip sloga.

**Šema baze podataka** je struktura definisana nad skupom tipova entiteta (TE) i tipova poveznika (TP).

**Baza podataka** je kontekstna LSO i predstavlja skup pojava tipova entiteta i tipova poveznika, definisanih nad TE i TP.

Logička struktura podataka se **vizuelno i fizički** može predstavljati:
- pomoću **grafova**
- pomoću **tabela**

### 1.26 Fizička struktura podataka

**Fizička struktura podataka (FSP)** predstavlja **logičku strukturu podataka (LSP)** smeštenu na memorijski medijum. Ona obuhvata podatke o **načinu fizičkog smeštanja, organizacije i pristupa** logičkoj strukturi podataka na datom medijumu.

## 2. Koncepcija BP

### 2.1 Klasična organizacija datoteka - nedostaci, posledice

Istorijski, IS su se čuvali na papirima, bez podrške računara. Nakon toga, IS su organizovani nad sistemima datoteka i sačinjavao ga je skup nezavisnih aplikacija, gde je svaka aplikacija imala svoje datoteke.

Dolazilo je do toga da podatke o istom entitetu imamo u više datoteka, i samim tim do nedostataka kao što su:
1. **nepovezanost aplikacija** (ručno prepisivanje istih ili sličnih podataka)
2. **redundantnost podataka** (višestruko memorisanje istih ili sličnih podataka)
3. **čvrste povezanosti između aplikacija i podataka** (program vodi računa o fizičkoj strukturi datoteke).

Posledice ovakve implementacije su **otežano održavanje IS-a** i **otežan dalji razvoj IS-a**.

### 2.2 Realna baza podataka

Relacione baze podataka imaju neke osnovne ideje:
- Da se svi podaci jednog IS integrišu u jednu veliku “datoteku” - bazu podataka
- Neredudantno memorisanje podataka
- Uvođenje softvera za podršku kreiranja i korišćenja BP – sistem za upravljanje bazom
podataka (SUBP)
- Transakcija obrada – ranije bila teška za implementaciju, sada to radi SUBP
- Višekorisnički konkurentni pristup
- Autorizacija korisnika

### 2.3 Tipovi baza podataka

> [!Note]
> NoSQL baze podataka obično ne dolaze na ispit.

Raspoznajemo nekoliko dominantnih paradigmi baza podataka:
1. Relacione baze podataka
2. NoSQL baze podataka
    - XML baze
    - Graf baze podataka
    - Binarne i JSON baze

### 2.4 Tipovi podataka prema strukturi

1. **Strukturirani podaci**
   Podaci za koje postoji jasno definisana šema koja precizno određuje njihov format, tipove i međusobne odnose.
   
2. **Polustrukturirani podaci**
   Podaci kod kojih se može definisati šema koja opisuje moguće elemente strukture, ali njihovo prisustvo nije obavezno. Struktura je fleksibilna i delimično definisana.
   Primeri: HTML, JSON, YAML.

3. **Nestrukturirani podaci**
   Podaci kod kojih ne postoji formalna šema koja definiše njihov format i organizaciju.
   Primer: email.


### 2.5 Namena SUBP/DBMS

**Sistem za upravljanje bazom podataka (SUBP)** omogućava efikasno i pouzdano formiranje, korišćenje i menjanje BP, aplikacije koriste i ažuriraju podatke koristeći isključivo SUBP.

On sadrži jezik za opis podataka (Data Definition Language - DDL), jezik za manipulisanje podacima (Data Manipulation Language - DML) i upitni jezik (Query Language - QL).

Jezgo SUBP omogućava:
- Obezbeđivanje fizičke organizacije podataka
- Rutine za upravljanje podacima
- Zaštita od neovlašćenog pristupa i uništavanja
- Obezbeđenje višekorisničkog rada
- Obezbeđivanje distribuirane organizacije BP
- Obezbeđivanje zadavanja šeme BP

### 2.6 Definicija šeme baze podataka

**Šema baze podataka** je logički opis (specifikacija) strukture baze, nezavisan od fizičkog načina memorisanja podataka.

Program koji koristi usluge SUBP šemu vidi kao logičku kategoriju, može da vidi samo nju i nad njom koristi LSP. Ne sme da vodi računa o FSP - zadatak SUBP je da preslikava LSP u FSP.

Uvođenjem šeme BP smanjuje se zavisnost programa i šeme BP od promena FSP. Takođe, smanjuje se redudantnost i uvode se nove uloge:
1. **Projektant baze podataka** koji definiše šemu BP
2. **Administrator baze podataka** koji upravlja aktivnostima SUBP, implementira i održava šemu BP

### 2.7 Definicija podšeme/eksterne šeme podataka

**Podšema baze podataka (eksterna šema)** je **logička struktura podataka (LSP)** definisana nad delom šeme BP, koja sadrži skup podataka **potreban i dovoljan za realizaciju jednog ili grupe sličnih transakcionih programa**.

Podšema se uvodi zato što je šema BP često složena i podložna promenama, pa **nije praktično da svi programi koriste kompletnu šemu**. Projektuje se u okviru procesa razvoja informacionog sistema.

Poželjno je da transakcioni programi pristupaju bazi podataka isključivo preko podšema. Preslikavanje podšeme u šemu BP idealno obavlja SUBP, ali u praksi to preslikavanje često realizuje sam transakcioni program.

Uvođenjem podšema ostvaruje se **logička i fizička nezavisnost programa od podataka**.

### 2.8 Definicija pogleda

**Pogled (view)** je **logička struktura podataka (LSP)** definisana nad **podšemom baze podataka**. On predstavlja **izabrani deo baze** i prikazuje podatke onako kako ih **vidi određeni program ili korisnik**, u skladu sa svojim potrebama i ovlašćenjima.

**Globalni pogled** je LSP definisan nad **celokupnom šemom BP** i predstavlja **potpunu logičku sliku stanja modelovanog sistema**.

### 2.9 Sistemi baza podataka

**Sistem baza podataka** u užem smislu obuhvata BP, SUBP, šemu BP, jezike i operacije za kreiranje, ažuriranje i korišćenje BP, sistemski softver i računare na kojima je BP kreirana. U širem smislu obuhvata više BP, više SUBP (homogen SUBP - više instanci istog SUBP, heterogen SUBP - više instanci različitih SUBP), sav prateći softver i hardver.

## 3. Model Podataka

### 3.1 ✨ Definicija modela podataka ✨

**Model podataka (MP)** je **matematička apstrakcija** pomoću koje se gradi **šema baze podataka (BP)**. On predstavlja:
- model baze podataka informacionog sistema (IS),
- pogled na strukture (model) posmatranog dela realnog sistema.

Model podataka se koristi za predstavljanje:
- šeme baze podataka realnog sistema,
- ograničenja u odnosima između podataka koji opisuju stanja realnog sistema,
- dinamike izmene stanja realnog sistema putem operacija nad podacima.

Model podataka čini **trojka (S, I, O)**, gde su:

- **S – strukturalna komponenta**
  Omogućava modeliranje **statičke strukture šeme baze podataka**, odnosno definiše osnovne gradivne elemente i njihove međusobne veze.

- **I – integritetna komponenta**
  Omogućava modeliranje **ograničenja nad podacima** u bazi podataka, čime se obezbeđuje njihova konzistentnost.

- **O – operacijska komponenta**
  Omogućava modeliranje **dinamike izmene stanja podataka**, odnosno definiše operacije kojima se podaci i šema baze podataka menjaju tokom vremena.

> [!Important]
> Model podataka predstavlja formalnu osnovu za projektovanje baze podataka i povezuje strukturu podataka, pravila integriteta i dozvoljene operacije u jedinstvenu celinu.


### 3.2 Nivoi apstrakcije

**Nivoi apstrakcije** su određeni modelom podataka i služe da razdvoje:
- **šta je definisano** (pravila, tipovi, šema),
- od toga **šta stvarno postoji u datom trenutku** (konkretne pojave i vrednosti).

U praksi se stalno koristi podela na:

1) **Nivo intenzije (konteksta)**
   - naziva se i **nivo tipa / nivo šeme**
   - jednostavno: **šta postoji i kako je definisano**
   - obuhvata definicije tipova (TE/TP), obeležja, domena, ograničenja, kardinaliteta, ključeva…

2) **Nivo ekstenzije (konkretizacije)**
   - naziva se i **nivo pojave tipa**
   - jednostavno: **stvarne vrednosti**, tj. **konkretni podaci koji trenutno postoje**
   - obuhvata skup pojava entiteta/poveznika (redove u tabelama, instance entiteta, veze koje su stvarno ostvarene)

> [!Important]
> Intenzija je “definicija sveta”, a ekstenzija je “trenutno stanje sveta”.

#### Primer: ER/EER pogled (entiteti i pojave)

Zamisli tip entiteta **Student**.

**Nivo intenzije (šta postoji i kako je definisano):**
- TE: `Student`
- obeležja: `MBR`, `IME`, `PRZ`, `DAT_ROD`
- domeni: `MBR: broj`, `IME: string`, …
- ključ: `MBR` (podvučeno u ER dijagramu)
- ograničenja: npr. `MBR` je jedinstven i obavezan, `DAT_ROD` ima smislen opseg, itd.

**Nivo ekstenzije (šta stvarno postoji sada):**
- konkretne pojave tipa `Student`, npr:
  - (MBR=101, IME=Ana, PRZ=Pap, DAT_ROD=2002-05-14)
  - (MBR=210, IME=Aca, PRZ=Tot, DAT_ROD=2001-11-03)

> [!Tip]
> Intenzija: “Student ima MBR, IME, PRZ…”
> Ekstenzija: “Ana (101) i Aca (210) su trenutno u bazi.”

### 3.3 Strukturalna komponenta MP

**Strukturalna komponenta** modela podataka predstavlja skup pojmova pomoću kojih se opisuje **statička struktura** posmatranog dela realnog sveta (ono *šta postoji* i *kako je strukturirano*).

Strukturalna komponenta MP obuhvata:

- **Koncept**
  Koncept je **apstraktna (i formalna) predstava** jedne klase pojmova kojima se modeluju delovi realnog sveta.

- **Primitivni (atomični) koncept**
  Primitivnom konceptu se **ne daje definicija** u okviru samog modela, jer predstavlja osnovni gradivni element. On se **ne može dekomponovati** na koncepte nižeg reda.

> [!Note]
> Primitivni koncepti su “osnovne cigle” modela podataka, dok se složeniji koncepti dobijaju njihovim kombinovanjem prema pravilima modela.

Pored toga, strukturalna komponenta sadrži:
- **skup primitivnih koncepata**, pri čemu je za svaki koncept dato:
  - skup njegovih osobina,
  - skup pravila korišćenja,
  - opis moguće semantike;
- **skup formalnih pravila** za kreiranje složenih koncepata
  (time se omogućava proširivanje inicijalno definisanog modela podataka);
- **skup unapred definisanih složenih koncepata**.

> [!Tip]
> Ako je model podataka dovoljno semantički bogat, on već nudi određene složene koncepte “spremne” za upotrebu, bez potrebe da ih korisnik svaki put formalno konstruiše.

### 3.4 ✨ Integritetna komponenta MP ✨

**Integritetna komponenta** modela podataka obuhvata sve što je potrebno da se u bazi podataka iskažu i kontrolišu **ograničenja**. 
Ograničenja se odnose na:
- moguće vrednosti obeležja i/ili
- moguće odnose između pojava povezanih tipova (npr. **ograničenje ključa**).

Integritetnu komponentu MP čini:

- **Skup tipova ograničenja**, pri čemu za svaki tip ograničenja postoje:
  - osobine tog tipa,
  - pravila za korišćenje,
  - opisana moguća semantika.

- **Skup formalnih pravila za izvođenje zaključaka** o važenju ograničenja.

- **Skup formalnih pravila za kreiranje novih tipova ograničenja**.

Provera važenja ograničenja može se realizovati:
- u **transakcionim programima**, ili
- u **specifikaciji šeme BP**, sa implementacijom u **SUBP**.

> [!Important]
> Teži se ka tome da se što veći broj ograničenja ugradi direktno u **šemu baze podataka** (da ih SUBP centralno kontroliše), dok se pojedina ograničenja po potrebi dodatno proveravaju i u transakcionim programima.

### 3.5 ✨ Operacijska komponenta MP ✨

Operacijska komponenta modela podataka omogućava modeliranje **dinamike izmene stanja**
u sistemu baze podataka. Predstavlja skup tipova operacija, sa:
- osobinama svakog tipa operacije,
- pravilima za korišćenje,
- opisanom mogućom semantikom.

Operacijska komponenta definiše sledeće grupe jezika/operacija:

- **Jezik za definiciju podataka (DDL – Data Definition Language)**
  Tipovi operacija za kreiranje i modifikaciju specifikacija:
  - šeme BP,
  - fizičke strukture BP,
  - prava pristupa i zaštite BP,
  - novih tipova operacija za upravljanje podacima.

- **Jezik za manipulisanje podacima (DML – Data Manipulation Language)**
  Tipovi operacija za **izmenu stanja BP** (npr. unos, izmena, brisanje podataka).

- **Upitni jezik (QL – Query Language)**
  Tipovi operacija za iskazivanje **upita nad BP** (pronalaženje/izdvajanje podataka).

Specifikacija svake operacije sadrži:
- **aktivnost** (akcija nad podacima u BP),
- **selekciju** (deo BP ili deo šeme BP nad kojim se aktivnost izvršava).

Operacijska komponenta može biti:

- **Proceduralna (navigaciona)**
  Definiše **šta i kako** treba da se uradi.
  Selekcija se vrši izborom **jednog objekta** iz BP.
  Prisutan je proceduralni pristup (petlje, uslovna grananja).

- **Specifikaciona (deklarativna)**
  Definiše **šta**, ali ne i **kako** treba da se uradi.
  Selekcija se vrši izborom iz **skupa objekata** iz BP.
  Neproceduralan pristup.

> [!Tip]
> Proceduralno: “idi red po red i uradi…”
> Deklarativno: “daj mi sve što zadovoljava uslov…”

### 3.6 Podela modela podataka

> [!Caution]
> Na ispitu se može tražiti samo **nabrajanje modela podataka** (bez ulaska u detalje).

Modeli podataka mogu biti, na primer:
- **Mrežni**
- **Hijerarhijski**
- **ER**
- **Relacioni**
- **Logički i verovatnosni logički modeli**
- **Objektno-orijentisani**
- **XML model**
- **Model ključ/vrednost**
- **Model zasnovan na grafovima**
- **Model zasnovan na dokumentima**
- **Model zasnovan na familijama kolona**
- **Model zasnovan na nizovima i matricama**
- ...

## 4. ER model

> [!Important]
> Potrebno je znati kako se **formalno čitaju ER dijagrami**, kao na prezentacijama – **ovo dolazi na test.**

### 4.1 Strukturalna komponenta ER modela

Strukturalnu komponentu **ER modela** čine **primitivni koncepti**:

- **Vrednost**
  Bilo koja konstanta iz bilo kog skupa.

- **Domen**
  Specifikacija skupa mogućih vrednosti obeležja, sa definisanim dozvoljenim relacijama i operacijama nad tim skupom.
  
    Domeni mogu biti:
  - **predefinisani** – ugrađeni u definiciju modela podataka i zavise od softverskog okruženja (npr. ℕ, ℝ, `integer`, `string`)
  - **korisnički definisani** – definišu se korišćenjem postojećih domena putem pravila za definisanje domena; mogu predstavljati skup atomičnih ili složenih podataka (npr. `DOCENA`)

- **Obeležje (atribut)**
  Osobina tipa entiteta ili tipa poveznika. Ako se na ER dijagramu za jedan tip entiteta vidi **više podvučenih obeležja**, to znači da **sva zajedno čine primarni ključ** tog tipa entiteta.


### 4.2 ER dijagrami

ER dijagrami su tehnika za predstavljanje **modela statičke strukture realnog sistema**. Njima se prikazuju **tipovi entiteta**, **tipovi poveznika**, njihove **međusobne veze**, kao i **obeležja** i njihovi **domeni**. Obeležja koja čine **primarni ključ** tipa entiteta u ER dijagramu se **podvlače**.

ER dijagrami mogu biti prikazani na različitim **nivoima detaljnosti**. 

Razlikuju se **nivo naziva tipova**, na kojem se prikazuju samo nazivi tipova entiteta i poveznika, i **nivo naziva obeležja i domena**, na kojem se dodatno prikazuju obeležja i pripadajući domeni.

U ER dijagramima je dozvoljeno postojanje **više tipova poveznika između istih tipova entiteta**, kao i definisanje **tipova poveznika koji povezuju n tipova entiteta** (n-arni tipovi poveznika).

Takođe, mogu se modelovati i **rekurzivni binarni tipovi poveznika**, u kojima isti tip entiteta učestvuje više puta u različitim ulogama.

### 4.3 ✨ Integritetna komponenta ER modela ✨

Integritetna komponenta ER modela podataka opisuje **ograničenja** koja moraju biti zadovoljena kako bi baza podataka bila **konzistentna**. 

Baza podataka se smatra konzistentnom ako su **svi podaci u njoj u skladu sa definisanim ograničenjima**, odnosno ako ni jedno pravilo integriteta nije narušeno.

Tipovi ograničenja u ER modelu podataka su:
- ograničenje domena,
- nula vrednost,
- ograničenje vrednosti obeležja,
- ograničenje pojave tipa,
- kardinalitet tipa poveznika,
- ograničenje ključa (integritet tipa) za tipove entiteta (TE) i tipove poveznika (TP).

### 4.3.1 Ograničenje domena

> [!Caution]
> **Ograničenje domena neće biti predmet ispitivanja.**

**Domen** predstavlja strukturu **D(id(D), Predef)**, gde je:
- **D** naziv domena,
- **id(D)** ograničenje domena,
- **Predef** predefinisana vrednost domena (nije obavezna).

Ograničenje domena se definiše primenom pravila za specificiranje korisnički definisanih domena.

Postoje sledeća pravila: pravila nasleđivanja, pravila tipa sloga, pravila tipa skupa i pravila tipa izbora. U okviru predmeta razmatraju se **pravila nasleđivanja**.

Ograničenje „nasleđenog“ domena ima oblik: **id(D) = (Tip, Dužina, Uslov)**

gde je:
- **Tip**: tip podatka (primitivni domen ili prethodno korisnički definisan domen) i jedina je obavezna komponenta specifikacije;
- **Dužina**: dužina tipa podatka i navodi se samo za primitive domene koji to zahtevaju;
- **Uslov**: logički uslov koji svaka vrednost domena mora da zadovolji;
- **Predef**: predefinisana vrednost koja se koristi ako se vrednost obeležja ne zada i mora zadovoljiti sva ograničenja tipa, dužine i uslova.

Oznaka **Δ** u primerima označava da odgovarajući uslov nije definisan. Interpretacija ograničenja moguća je za bilo koju konstantnu vrednost.

### 4.3.2 Nula vrednost

**Nula (nedostajuća) vrednost** je specijalna vrednost obeležja koja se označava sa **ω** (u praksi **NULL**). Ona označava da vrednost obeležja:
- nije poznata,
- ne postoji, ili
- nije informativna.

U određenim slučajevima postoji potreba da obeležje, umesto vrednosti iz domena, ima nula vrednost.

### 4.3.3 Ograničenje vrednosti obeležja

Specifikacija obeležja \( A ∈ Q \) datog tipa \( N \) ima oblik **(id(N, A), Predef)**, gde je:
- **id(N, A)** ograničenje vrednosti obeležja,
- **Predef** predefinisana vrednost obeležja.

Ograničenje vrednosti obeležja ima strukturu: **id(N, A) = (Domen, Null)** gde je:
- **Domen** oznaka pridruženog domena obeležja,
- **Null ∈ {T, ⊥}**, pri čemu:
  - **T** označava dozvolu dodele nula vrednosti,
  - **⊥** označava zabranu dodele nula vrednosti.

Komponente **Domen** i **Null** su obavezne. Predefinisana vrednost može biti navedena, a ako nije, važi predefinisana vrednost domena ili prvog sledećeg nasleđenog domena za koji je definisana. Narušavanje ovog ograničenja predstavlja pokušaj narušavanja konzistentnosti baze podataka.

Interpretacija ograničenja moguća je za bilo koju vrednost obeležja.

### 4.3.4 Ograničenje pojave tipa

**Ograničenje pojave tipa** definiše ograničenja nad mogućim vrednostima podataka unutar iste pojave tipa entiteta (TE) ili tipa poveznika (TP). Ono predstavlja skup ograničenja vrednosti obeležja kome je pridodat logički uslov.

Formalno, za tip \( N \) važi: **id(N) = ({id(N, A) \| A ∈ Q′}, Uslov)** , gde je:
- **Q′** prošireni skup obeležja tipa:
  - za TE važi \( Q′ = Q \),
  - za TP važi \( Q′ = Q ∪ K_p \), gde je \( K_p \) skup obeležja primarnog ključa TP,
- **Uslov** logički uslov koji svaka pojava tipa mora da zadovolji i može da sadrži bilo koje obeležje iz skupa \( Q′ \).

Interpretacija ograničenja pojave tipa moguća je za bilo koju pojavu tipa nad skupom obeležja nad kojim je ograničenje definisano.

### 4.4 ✨ Kardinalitet tipa poveznika ✨

Kardinalitet tipa poveznika (TP) prema povezanom tipu predstavlja se parom **(a, b)**, gde je:
- **a ∈ {0, 1}** minimalni kardinalitet,
- **b ∈ {1, N}**, pri čemu je **N ≥ 2**, maksimalni kardinalitet.

Kardinalitet se definiše **za svaki povezani tip** i ograničava u koliko pojava tipa poveznika može učestvovati **jedna, bilo koja pojava povezanog tipa** – minimalno **a** puta, a maksimalno **b** puta.

Na osnovu maksimalnih kardinaliteta razlikuju se tri opšte grupe tipova poveznika:
- **M : N** (više prema više),
- **N : 1** (više prema jedan),
- **1 : 1** (jedan prema jedan).

Grupa kardinaliteta ima direktan uticaj na način **formiranja ključa tipa poveznika**.

### 4.5 Integritet tipa poveznika

**Integritet tipa poveznika (TP)** predstavlja **ograničenje ključa** tipa poveznika. Identifikator TP čini **niz naziva povezanih tipova entiteta** ili njegov **neprazan podskup**, pri čemu **ključevi povezanih tipova entiteta ulaze u skup obeležja TP**.

> [!Important]
> Integritet tipa poveznika određuje **kako se formira ključ TP** na osnovu ključeva povezanih tipova entiteta.

#### Formiranje ključa tipa poveznika u zavisnosti od kardinaliteta

> [!Warning]
> Sledeća pravila **sigurno dolaze na testu**.

- **M : N (više prema više)**
  Ključ TP se formira **uniranjem ključeva oba povezana tipa**.
  *(formalno: K_TP = K₁ + K₂)*

- **N : 1 (više prema jedan)**
  Ključ sa strane **N** se **propagira ka strani 1**, a **ključ TP postaje ključ sa strane 1**.

- **1 : 1 (jedan prema jedan)**
  **Ne vrši se uniranje ključeva (!!!)**
  Oba ključa su **kandidati za ključ TP**, ali se posmatraju **zasebno**, a ne kao njihov zbir.
  *(formalno: K_TP = K₁ , K₂)*

> [!Caution]
> Kod **rekurzivnih tipova poveznika**, naročito onih sa **više obeležja u ključu**, često se javlja potreba za pažljivim razlikovanjem uloga istog tipa entiteta.
> 
> Ovakvi primeri se **često pojavljuju na testu** i zahtevaju posebno obraćanje pažnje.


### 4.6 Gerund

**Gerund (mešoviti tip)** je tip entiteta (TE) dobijen **transformacijom tipa poveznika (TP)**.

Do gerunda dolazi kada TP učestvuje kao **povezani tip u nekom drugom TP**. Zbog toga gerund ima **dvostruku ulogu**:
- prema nekim tipovima ponaša se kao **TP**,
- prema drugim tipovima ponaša se kao **TE**.

> [!Note]
> Gerund istovremeno ima osobine **entiteta i poveznika**, što ga čini posebnim konceptom ER modela.

Gerund se koristi u sledećim situacijama:
- kada **ne mogu proizvoljne kombinacije pojava** određenih tipova biti sadržane u pojavi posmatranog TP,
- kada **postoji pravilo** koje tačno određuje **koje kombinacije pojava** mogu biti sadržane u pojavi tog TP.

> [!Tip]
> Tipične primere upotrebe gerunda treba pogledati na slajdovima, jer se kroz njih najlakše uočava potreba za njegovim uvođenjem.

### 4.7 Agregacija

**Agregacija** obezbeđuje objedinjavanje složenijih ER struktura tako što se **cela ER struktura posmatra kao jedan tip entiteta (TE)**. Koristi se najčešće kada je šema složena, a određeni njen deo se želi posmatrati kao celina ili izdvojiti iz daljeg razmatranja.

> [!Important]
> Najjednostavniji primer agregacije je upravo **gerund**.

> [!Caution]
> Agregacija se **neće pojavljivati u zadacima**, ali je važno razumeti njenu ulogu u modelovanju složenih ER šema.

### 4.8 ✨ Slabi tip entiteta ✨

**Slabi tip entiteta (TE)** je tip entiteta čije su **pojave zavisne od pojava nekog drugog tipa entiteta**. Drugim rečima, pojava slabog TE ne može postojati samostalno bez odgovarajuće pojave nadređenog (regularnog) TE.

Postoje **dve vrste zavisnosti** slabih tipova entiteta:

**Egzistencijalna zavisnost** postoji između pojava dva tipa entiteta kada je **minimalni kardinalitet tipa poveznika jednak 1**. Ova vrsta zavisnosti **nema poseban grafički simbol** u ER dijagramima.

> [!Note]
> **Regularni tip entiteta** je tip entiteta koji **nije u egzistencijalnoj zavisnosti** od nekog drugog tipa entiteta.

**Identifikaciona zavisnost** predstavlja **poseban slučaj egzistencijalne zavisnosti**, kod kojeg su i **minimalni i maksimalni kardinalitet jednaki 1**.

Uvođenjem identifikacione zavisnosti vrši se podela tipova entiteta na:
- **neidentifikacione tipove entiteta** i
- **identifikacione tipove entiteta**.

Identifikaciona zavisnost slabog TE označava da se **svaka pojava zavisnog TE može identifikovati isključivo uz pomoć identifikatora nadređenog TE**.

> [!Important]
> Ključ slabog (identifikacionog) tipa entiteta formira se kao **kombinacija ključa nadređenog tipa entiteta i sopstvenih obeležja slabog TE**.

> [!Tip]
> Regularni tip entiteta može učestvovati kao **ID-zavisan povezani tip** u nekom drugom tipu poveznika.
> 
> ID-zavisan tip entiteta može učestvovati **i kao ID-zavisan i kao regularan tip entiteta** u više različitih tipova poveznika, u zavisnosti od konteksta modelovanja.

### 4.9 IS-A hijerarhija

**IS-A hijerarhija** je poseban koncept koji pripada **EER (proširenom) ER modelu**. Koristi se u situacijama kada određeni **podskup jedne klase** poseduje dodatna obeležja ili veze koje ga razlikuju od ostalih pojava te klase. U tom slučaju uvode se pojmovi **superklase (nadtipa)** i **potklase (podtipa)**, koji predstavljaju posebne vrste tipova entiteta ili poveznika.

IS-A hijerarhija je povezana sa postupcima **specijalizacije** i **generalizacije**. Specijalizacija se primenjuje kada superklasa sadrži prepoznatljive podskupove – potklase – koje imaju samo sebi svojstvena obeležja ili samo sebi svojstvene veze ka drugim tipovima entiteta ili poveznika. Ovaj koncept je karakterističan za **semantičke modele podataka**.

Uvođenje superklasa i potklasa ima sledeće ciljeve:
- da model statičke strukture realnog sistema bude **semantički bogatiji**,
- da se **izbegnu nula vrednosti u ekstenziji**, koje bi se pojavile kada bi se sve modelovalo jednim tipom entiteta,
- da se izbegne definisanje **tipova poveznika bez jasnog semantičkog smisla**.

Specijalizacija se vrši na osnovu vrednosti **klasifikacionih obeležja**. U tipu entiteta superklase zadržavaju se **primarni ključ i sva zajednička obeležja**, dok se u tipovima entiteta potklasa nalaze **samo specifična obeležja** karakteristična za dati podskup.

Navođenje **kardinaliteta ka superklasi** je obavezno i ima oblik **(a, b)**, dok se kardinalitet ka potklasama ne navodi, jer je uvek **(1, 1)**. Ako je **a = 1**, IS-A hijerarhija je **totalna**, a ako je **a = 0**, hijerarhija je **parcijalna**. Ako je **b = 1**, hijerarhija je **nepresečna**, dok je za **b = N** hijerarhija **presečna**.

Bitne karakteristike IS-A hijerarhije su:
- potklasa **nasleđuje osobine superklase**,
- **ključ svake potklase** je primarni ključ superklase (nasleđivanje ključeva), pri čemu potklase mogu imati i sopstvene ključeve koji se **ne uniraju** sa ključem superklase,
- postoji **identifikaciona zavisnost** svake potklase prema superklasi,
- potklasa može imati ulogu **superklase u nekoj drugoj IS-A hijerarhiji**,
- nad jednim tipom može se definisati **više različitih IS-A hijerarhija**, korišćenjem različitih kriterijuma specijalizacije.


### 4.10 Kategorizacija

**Kategorizacija** je poseban koncept u okviru **EER modela** i predstavlja **tip poveznika (TP)** koji je vezan za postupak **klasifikacije (tipizacije)**, karakterističan za semantičke modele podataka. U okviru kategorizacije uvodi se pojam **kategorije**, koja predstavlja poseban tip (entitet ili tip poveznika – gerund).

Kod kategorizacije, **jedan tip entiteta** se povezuje sa **više kategorija (najmanje dve)**, pri čemu **svaka pojava posmatranog tipa entiteta može pripadati najviše jednoj kategoriji**.

> [!Important]
> Između posmatranog tipa entiteta i kategorija **ne postoji identifikaciona zavisnost** – oni su međusobno **nezavisni**.

Postojanje **klasifikacionih obeležja kategorije** je opciono, odnosno ona **mogu, ali ne moraju** biti definisana.

Minimalni kardinalitet ka posmatranom tipu entiteta određuje **tip kategorizacije**:
- ako je **minimalni kardinalitet 0**, u pitanju je **parcijalna kategorizacija**,
- ako je **minimalni kardinalitet 1**, u pitanju je **totalna kategorizacija**.

Maksimalni kardinalitet ka posmatranom tipu entiteta je **uvek 1**, što znači da jedna pojava posmatranog tipa entiteta ne može pripadati više kategorija istovremeno.

> [!Tip]
> Moguće je imati, na primer, **parcijalnu–nepresečnu kategorizaciju**: neka tip entiteta *Zaposleni* ima kategorije *Stalni* i *Honorani*.
> 
> Nisu svi zaposleni nužno svrstani u neku kategoriju (parcijalna), a oni koji jesu mogu pripadati **najviše jednoj kategoriji** (nepresečna).

> [!Note]
> Kategorizacija se koristi kada je potrebno jasno razdvojiti pojave istog tipa entiteta na međusobno isključive klase, bez uvođenja zavisnosti u identifikaciji.

### 4.11 N-arni tip poveznika

**N-arni tip poveznika (TP)** je tip poveznika koji povezuje **više od dva druga tipa** entiteta ili poveznika. Drugim rečima, radi se o poveznicima čija je **n-arnost n ≥ 3**.

Za svaki od **n povezanih tipova**, za bilo koju izabranu pojavu tog tipa, određuje se:
- **minimalan broj** pojavljivanja u pojavama TP i
- **maksimalan broj** pojavljivanja u pojavama TP.

Na taj način se definiše u koliko pojava n-arnog tipa poveznika može učestvovati jedna, bilo koja pojava svakog od povezanih tipova.

> [!Note]
> N-arni tipovi poveznika koriste se kada se veza između više tipova **ne može korektno izraziti kombinacijom binarnih tipova poveznika** bez gubitka semantike.

> [!Tip]
> Nije potrebno znati **varijante dijagramskog označavanja** n-arnih tipova poveznika.