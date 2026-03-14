# Referencijalni integritet

## Kako se podaci u tabelama povezuju?

Zamislimo sledeću situaciju: imamo bazu podataka fakulteta u kojoj postoje tabele `Radnik`, `Projekat` i `Angažovanje`. Radnici se angažuju na projektima i to beležimo u tabeli `Angažovanje`. Ali, šta se dešava ako neko pokuša da angažuje radnika koji ne postoji u tabeli `Radnik`? Ili da obriše radnika koji rukovodi aktivnim projektom? Dobili bismo bazu punu "siročića" - podataka koji referenciraju nešto što ne postoji. Baza bi prestala da bude verna slika realnosti.

Upravo taj problem rešava **referencijalni integritet** - jedno od najvažnijih ograničenja u relacionom modelu podataka. Ali pre nego što dođemo do njega, moramo razumeti širi kontekst - integritetnu komponentu relacionog modela i pojam zavisnosti sadržavanja.

---

## Integritetna komponenta relacionog modela

Relacioni model podataka ima tri komponente: strukturalnu (kako se podaci organizuju), operacijsku (kako se njima manipuliše) i **integritetnu** (kako se obezbeđuje ispravnost podataka).

**Integritetna komponenta** definiše se putem **tipova ograničenja**. Svaki tip ograničenja ima svoje karakteristike:

- **Formalizam za zapisivanje (definicija)** - kako se ograničenje formalno beleži.
- **Pravilo za interpretaciju (validaciju)** - kako se proverava da li je ograničenje zadovoljeno.
- **Oblast definisanosti** - tip logičke strukture obeležja nad kojom se ograničenje definiše.
- **Oblast interpretacije** - tip logičke strukture podataka nad kojom se ograničenje interpretira (proverava).
- **Skup operacija** koje mogu dovesti do narušavanja ograničenja datog tipa.
- **Skup mogućih akcija** kojima se obezbeđuje očuvanje validnosti baze podataka pri pokušaju narušavanja.

> [!IMPORTANT]
> Kontrola ograničenja implementiranih na nivou SUBP je **centralna** - ne može je zaobići nijedan program ili korisnik. Korisnici najčešće nisu ni svesni postojanja ograničenja dok ne dođe do pokušaja narušavanja. Kada se to desi, SUBP izaziva grešku i prekida operaciju, ili aktivnim mehanizmom automatski dovodi stanje baze u konzistentno.

### Oblasti definisanosti ograničenja

Prema oblasti definisanosti, ograničenja u relacionom modelu mogu biti:

- **Vanrelaciono ograničenje** - definiše se izvan konteksta šeme relacije.
- **Jednorelaciono (unutarrelaciono, lokalno) ograničenje** - definiše se nad tačno jednom šemom relacije.
- **Višerelaciono ograničenje** - definiše se nad skupom ili nizom šema relacija koji sadrži bar dva člana.

### Oblasti interpretacije ograničenja

Prema oblasti interpretacije, ograničenja mogu biti:

- **Ograničenje vrednosti** - interpretira se nad tačno jednom vrednošću nekog obeležja.
- **Ograničenje torke** - interpretira se nad jednom torkom bilo koje relacije.
- **Relaciono ograničenje** - interpretira se nad skupom torki bilo koje relacije.
- **Međurelaciono ograničenje** - interpretira se nad barem dve bilo koje relacije.

Napomena: "bilo koja relacija" ovde znači ili jedna relacija iz baze podataka, ili relacija nastala primenom izraza relacione algebre nad jednom ili više drugih relacija (pogled).

### Tipovi ograničenja u relacionom modelu

Hajde da nabrojimo kompletnu listu tipova ograničenja u relacionom modelu podataka, jer referencijalni integritet je samo jedan od njih:

1. Ograničenje domena
2. Ograničenje vrednosti obeležja
3. Ograničenje torke
4. **Integritet entiteta (ograničenje ključa)**
5. Ograničenje jedinstvenosti vrednosti obeležja
6. **Zavisnost sadržavanja**
7. **Ograničenje referencijalnog integriteta**
8. Funkcionalna zavisnost

Nas posebno zanimaju stavke 4, 6 i 7, jer referencijalni integritet direktno gradi na pojmovima ključa i zavisnosti sadržavanja.

---

## Ograničenje ključa (integritet entiteta)

Pre nego što pređemo na referencijalni integritet, moramo se podsetiti šta je ključ, jer je on temelj na kojem sve stoji.

**Ključ šeme relacije** je minimalni podskup skupa obeležja šeme relacije na osnovu kojeg se jedinstveno može identifikovati svaka torka relacije nad datom šemom.

Formalno, $X$ je ključ ako važi:

$$1^0: \quad (\forall u, v \in r(R))(u[X] = v[X] \Rightarrow u = v)$$

$$2^0: \quad (\nexists Y \subset X)(1^0)$$

Prvo pravilo ($1^0$) kaže: ako dve torke imaju iste vrednosti za obeležja ključa, onda su to iste torke. Drugo pravilo ($2^0$) kaže: ne postoji nijedan pravi podskup od $X$ koji bi imao tu istu osobinu - ključ je minimalan.

Oblast interpretacije ograničenja ključa je skup torki (relacija) nad datom šemom relacije.

### Oznaka ograničenja ključa

Za šemu relacije $N(R, K)$, ključ $X \in K$, $X \subseteq R$, ograničenje ključa se označava kao:

$$Key(N, X)$$

### Svojstva ključa

- Svaka šema relacije **mora** posedovati najmanje jedan ključ ($K \neq \emptyset$). Ovo proizilazi iz same definicije relacije.
- Za sva obeležja ključa, nula vrednosti su **zabranjene**: $(\forall K_i \in K)(\forall A \in K_i)(Null(N, A) = \bot)$
- Svi ključevi skupa ključeva $K$ su **ekvivalentni ključevi**.
- **Primarni ključ** ($K_p(N)$) je jedan izabrani ključ od svih ekvivalentnih. Svaka šema relacije treba da poseduje tačno jedan primarni ključ.
- Primarni ključ se koristi u ulozi **asocijativne (simboličke) adrese** za povezivanje podataka u relacijama.

> [!NOTE]
> Upravo ova poslednja osobina primarnog ključa - da služi kao simbolička adresa - je razlog zašto je ključ toliko bitan za referencijalni integritet. Kada jedna tabela želi da "pokaže" na red u drugoj tabeli, ona to radi tako što čuva vrednost primarnog ključa te druge tabele.

**Primer:** Pogledajmo tri šeme relacija:

- `Radnik({MBR, IME, PRZ, DATR}, {MBR})` - ključ je MBR (matični broj)
- `Projekat({SPR, NAP}, {SPR})` - ključ je SPR (šifra projekta)
- `Angažovanje({SPR, MBR, BRC}, {SPR+MBR})` - ključ je složen: SPR+MBR

---

## Zavisnost sadržavanja

Sada dolazimo do koncepta koji je direktan preduslov za razumevanje referencijalnog integriteta. **Zavisnost sadržavanja** je ograničenje koje kaže da se vrednosti iz jednog skupa obeležja jedne relacije moraju nalaziti među vrednostima odgovarajućeg skupa obeležja druge relacije.

### Formalna definicija

Date su šeme relacije $N_i(R_i, O_i)$ i $N_j(R_j, O_j)$. Dati su **domenski kompatibilni** nizovi obeležja:

$$X = (A_1, \ldots, A_n), \quad (\forall l \in \{1, \ldots, n\})(A_l \in R_i)$$

$$Y = (B_1, \ldots, B_n), \quad (\forall l \in \{1, \ldots, n\})(B_l \in R_j)$$

$$(\forall l \in \{1, \ldots, n\})(dom(A_l) \subseteq dom(B_l))$$

Ovo znači: nizovi $X$ i $Y$ imaju isti broj obeležja, svako obeležje iz $X$ pripada šemi $N_i$, svako iz $Y$ pripada šemi $N_j$, i odgovarajući parovi obeležja imaju kompatibilne domene (skup mogućih vrednosti obeležja iz $X$ je podskup skupa mogućih vrednosti obeležja iz $Y$).

**Oznaka (pravilo zapisivanja):**

$$N_i[X] \subseteq N_j[Y]$$

Ovo čitamo: "projekcija relacije nad $N_i$ na obeležja $X$ je sadržana u projekciji relacije nad $N_j$ na obeležja $Y$".

### Pravilo interpretacije

Zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$ važi ako je za bilo koje dve relacije $r(R_i, O_i)$ i $s(R_j, O_j)$ zadovoljeno:

$$(\forall u \in r)(\exists v \in s)(\forall l \in \{1, \ldots, n\})(u[A_l] = \omega \lor u[A_l] = v[B_l])$$

Drugim rečima: za svaku torku $u$ u relaciji $r$, mora postojati torka $v$ u relaciji $s$ takva da se vrednosti odgovarajućih obeležja poklapaju (osim ako je vrednost u $u$ nula vrednost $\omega$).

**Oblast definisanosti:** niz od dve šeme relacije.

**Oblast interpretacije:** relacije nad šemama $N_i$ i $N_j$.

### Primer zavisnosti sadržavanja - jedno obeležje

Date su relacije $r(N_i)$ i $s(N_j)$. Važi zavisnost sadržavanja $N_i[B] \subseteq N_j[B]$.

| r: A  | B  |
|-------|----|
| a1    | b1 |
| a2    | b2 |

| s: B  | C  |
|-------|----|
| b1    | c1 |
| b2    | c1 |
| b3    | c2 |

Vidimo da su sve vrednosti obeležja $B$ u relaciji $r$ (b1 i b2) sadržane među vrednostima obeležja $B$ u relaciji $s$ (b1, b2, b3). Zavisnost sadržavanja je zadovoljena.

### Primer zavisnosti sadržavanja - više obeležja

Date su relacije $r(N_i)$ i $s(N_j)$. Važi zavisnost sadržavanja $N_i[(A, B)] \subseteq N_j[(C, D)]$.

| r: A  | B  |
|-------|----|
| a1    | b1 |
| a2    | ω  |

| s: C  | D  |
|-------|----|
| a1    | b1 |
| a2    | b2 |
| a3    | b2 |

Par $(a1, b1)$ iz $r$ se nalazi u $s$ kao $(a1, b1)$ - poklapaju se. Za torku $(a2, \omega)$ - pošto je vrednost za $B$ nula vrednost $\omega$, ograničenje je automatski zadovoljeno.

---

## Ograničenje referencijalnog integriteta

Evo nas konačno na centralnom pojmu. **Ograničenje referencijalnog integriteta** je poseban slučaj zavisnosti sadržavanja.

> [!IMPORTANT]
> **Definicija:** Ograničenje referencijalnog integriteta je zavisnost sadržavanja $N_i[X] \subseteq N_j[Y]$, pri čemu je $Y$ **ključ** šeme relacije $N_j(R_j, K_j)$.
>
> - $N_i$ se naziva **referencirajuća šema relacije** (ona koja "pokazuje" na drugu tabelu)
> - $N_j$ se naziva **referencirana šema relacije** (ona na koju se "pokazuje")

Ovo je ključna razlika u odnosu na opštu zavisnost sadržavanja: kod referencijalnog integriteta, obeležja na koja se referenciramo ($Y$) moraju biti ključ. To ima duboki smisao - mi ne referenciramo bilo kakve podatke, nego referenciramo konkretne, jedinstveno identifikovane entitete.

Ako razmišljamo u terminima svakodnevnog života: referencijalni integritet je kao sistem ličnih karata. Svaki građanin ima jedinstven JMBG (to je ključ). Kada na nekom dokumentu napišemo JMBG osobe, referenciramo tačno jednu, konkretnu osobu. Referencijalni integritet garantuje da ta osoba stvarno postoji u "tabeli građana".

### Prostiranje ključa i strani ključ

U relacionom modelu podataka, povezivanje podataka se ostvaruje putem **prostiranja ključa** - uvođenja pojma **stranog ključa** i ograničenja referencijalnog integriteta. Ovo je suštinski drugačiji pristup od ranijih modela podataka (mrežni i hijerarhijski model) koji su koristili fizičke adrese i pokazivače.

Kod relacionog modela, transakcioni program ne vodi računa o pretvaranju simboličke adrese u relativnu adresu - to je posao SUBP-a. Ovo obezbeđuje nezavisnost programa od podataka, što je jedan od osnovnih zahteva relacionog modela.

---

## Primer referencijalnog integriteta

Pogledajmo konkretan primer sa tri relacije: `Radnik`, `Projekat` i `Angažovanje`.

**Šeme relacija:**

- `Radnik({MBR, IME, PRZ, DATR}, {MBR})`
- `Projekat({SPR, NAP, RUK}, {SPR})`
- `Angažovanje({SPR, MBR, BRC}, {SPR+MBR})`

**Ograničenja referencijalnog integriteta:**

$$Projekat[RUK] \subseteq Radnik[MBR]$$

$$Angažovanje[MBR] \subseteq Radnik[MBR]$$

$$Angažovanje[SPR] \subseteq Projekat[SPR]$$

Hajde da "prevedemo" ova ograničenja na svakodnevni jezik:

1. **Projekat[RUK] ⊆ Radnik[MBR]** - Rukovodilac projekta (RUK) mora biti neki postojeći radnik. Ne možeš postaviti za rukovodioca nekoga ko nije zaposlen.
2. **Angažovanje[MBR] ⊆ Radnik[MBR]** - Radnik angažovan na projektu mora postojati u tabeli radnika. Ne možeš angažovati "duh" radnika.
3. **Angažovanje[SPR] ⊆ Projekat[SPR]** - Projekat na kojem se neko angažuje mora postojati. Ne možeš raditi na projektu koji nije registrovan.

> [!TIP]
> Obratite pažnju na to koja šema je **referencirajuća**, a koja **referencirana**. Referencirajuća je uvek ona koja "pokazuje" - u ovom slučaju `Projekat` i `Angažovanje` pokazuju na `Radnik`, a `Angažovanje` pokazuje i na `Projekat`.

### Konkretni podaci

Pogledajmo kako izgleda popunjeno stanje baze:

**Radnik:**

| MBR | IME  | PRZ | DATR       |
|-----|------|-----|------------|
| 101 | Ana  | Pap | 12.12.85.  |
| 102 | Aca  | Tot | 13.11.88.  |
| 110 | Ivo  | Ban | 01.01.79.  |
| 111 | Olja | Kun | 06.05.81.  |

**Projekat:**

| SPR | NAP      | RUK |
|-----|----------|-----|
| 11  | X25      | 101 |
| 13  | Polaris  | 101 |
| 14  | Univ.IS  | 111 |

**Angažovanje:**

| MBR | SPR |
|-----|-----|
| 101 | 11  |
| 101 | 14  |
| 111 | 14  |

Proveravamo ograničenja: svaka vrednost RUK u tabeli Projekat (101, 101, 111) postoji kao MBR u tabeli Radnik. Svaka vrednost MBR u Angažovanju (101, 101, 111) postoji u Radniku. Svaka vrednost SPR u Angažovanju (11, 14, 14) postoji u Projektu. Baza je u konzistentnom stanju.

---

## Operacije koje mogu narušiti referencijalni integritet

Sad dolazimo do praktično najvažnijeg dela za razumevanje - šta se dešava kada pokušamo da izmenimo podatke? Koje operacije mogu da "pokvare" referencijalni integritet?

### Unos nove torke (INSERT)

#### Unos u referencirajuću relaciju

Kada unosimo novu torku u referencirajuću relaciju, moramo proveriti da li referencirana vrednost postoji.

**Primer - unos novog projekta:**

Imamo ograničenje $Projekat[RUK] \subseteq Radnik[MBR]$. Želimo da unesemo novi projekat:

| SPR | NAP | RUK |
|-----|-----|-----|
| 15  | P7  | 110 |

Proveravamo: da li MBR = 110 postoji u tabeli Radnik? Da, radnik Ivo Ban ima MBR = 110. Unos je dozvoljen, referencijalni integritet ostaje očuvan.

Ali šta ako pokušamo uneti projekat sa RUK = 210, a radnik sa tim matičnim brojem ne postoji? SUBP bi **odbio** taj unos i prijavio grešku.

#### Unos u referenciranu relaciju

Kada unosimo novu torku u referenciranu relaciju (npr. novog radnika u tabelu `Radnik`), to **nikada ne može** narušiti referencijalni integritet. Dodajemo novi entitet na koji niko još ne referencira - nema problema.

### Angažovanje radnika na projektu (INSERT u Angažovanje)

Ovo je primer gde imamo **dva** ograničenja referencijalnog integriteta istovremeno:

$$Angažovanje[MBR] \subseteq Radnik[MBR]$$

$$Angažovanje[SPR] \subseteq Projekat[SPR]$$

Kada unosimo novu torku u Angažovanje, moramo proveriti **oba** ograničenja: da li radnik sa datim MBR postoji u tabeli Radnik, **i** da li projekat sa datim SPR postoji u tabeli Projekat.

**Primer:** Želimo uneti angažovanje radnika 110 na projektu 15.

| MBR | SPR |
|-----|-----|
| 110 | 15  |

Proveravamo: MBR = 110 postoji u Radniku (Ivo Ban) - OK. SPR = 15 postoji u Projektu (prethodno smo ga uneli kao projekat P7) - OK. Unos je dozvoljen.

### Brisanje torke (DELETE)

#### Brisanje iz referencirane relacije

Ovo je operacija koja može izazvati probleme. Kada brišemo torku iz referencirane relacije, moramo proveriti da li neko na nju referencira.

**Primer - brisanje radnika:**

Imamo ograničenje $Projekat[RUK] \subseteq Radnik[MBR]$.

Pokušavamo: `DELETE FROM Radnik WHERE MBR = 102`

Radnik Aca Tot (MBR = 102) - da li neko referencira ovog radnika? Pogledamo tabelu Projekat - nijedan projekat nema RUK = 102. Pogledamo Angažovanje - nijedna torka nema MBR = 102. Brisanje je bezbedno.

Pokušavamo: `DELETE FROM Radnik WHERE MBR = 110`

Radnik Ivo Ban (MBR = 110) - da li neko referencira ovog radnika? Projekat sa SPR = 15 ima RUK = 110, i postoje angažovanja sa MBR = 110. Brisanje bi **narušilo** referencijalni integritet! SUBP neće dozvoliti ovo brisanje (ili će primeniti neku od definisanih akcija - kaskadno brisanje, postavljanje na NULL, itd.).

#### Brisanje iz referencirajuće relacije

Brisanje torke iz referencirajuće relacije (npr. brisanje angažovanja iz tabele `Angažovanje`) **nikada ne može** narušiti referencijalni integritet. Mi samo uklanjamo referencu - na referenciranu tabelu to nema nikakav uticaj.

### Modifikacija (UPDATE)

Modifikacija vrednosti ključa u referenciranoj relaciji ili modifikacija vrednosti stranog ključa u referencirajućoj relaciji - obe mogu potencijalno narušiti referencijalni integritet. Logika je ista kao za INSERT i DELETE: ako menjaš vrednost stranog ključa, nova vrednost mora postojati u referenciranoj tabeli; ako menjaš vrednost primarnog ključa, niko ne sme referencirati staru vrednost.

> [!WARNING]
> Česta greška na ispitu: studenti zaborave da i **UPDATE** može narušiti referencijalni integritet. Ako promenimo MBR radnika sa 110 na 999, a na tog radnika referencira projekat (RUK = 110), to je isto kao da smo ga obrisali - referencijalni integritet je narušen.

---

## Sumarni pregled kritičnih operacija

Da sažmemo koja operacija na kojoj relaciji može narušiti referencijalni integritet:

| Operacija | Referencirajuća relacija ($N_i$) | Referencirana relacija ($N_j$) |
|-----------|----------------------------------|-------------------------------|
| INSERT    | Može narušiti (nova ref. vrednost mora postojati) | Ne može narušiti |
| DELETE    | Ne može narušiti | Može narušiti (neko može referencirati obrisanu torku) |
| UPDATE stranog/primarnog ključa | Može narušiti | Može narušiti |

---

## Konzistentno stanje baze podataka

Baza podataka $RBP = \{r_i \mid i \in \{1, \ldots, n\}\}$ nad šemom $(S, I)$ nalazi se u **formalno konzistentnom stanju** ako:

1. Svaka relacija $r_i$ zadovoljava sva ograničenja odgovarajuće šeme $(R_i, O_i)$.
2. $RBP$ zadovoljava sva **međurelaciona ograničenja** iskazana putem $I$.

Baza je u **suštinski konzistentnom stanju** ako se nalazi u formalno konzistentnom stanju i predstavlja vernu sliku stanja realnog sistema. U praksi, nivo pojave grešaka u bazi sveden je na ispod 2-3%. SUBP može da kontroliše samo formalnu konzistentnost.

> [!IMPORTANT]
> **Međurelaciona ograničenja** (skup $I$ u relacionoj šemi baze podataka) su upravo ta ograničenja referencijalnog integriteta! Ona se definišu nad parom šema relacija i čuvaju se u šemi baze podataka, odvojeno od ograničenja pojedinačnih šema relacija.

---

## Relaciona šema baze podataka

Da bismo videli gde se ograničenja referencijalnog integriteta "uklapaju" u celu sliku, pogledajmo strukturu **relacione šeme baze podataka**.

Relaciona šema BP je (imenovani) par:

$$(S, I)$$

gde je:

- $S$ - skup šema relacija: $S = \{(R_i, O_i) \mid i \in \{1, \ldots, n\}\}$
- $I$ - skup **međurelacionih ograničenja** (ograničenja referencijalnog integriteta)

**Primer:**

$S = \{Radnik, Projekat, Angažovanje\}$

$I = \{$ "radnik ne može biti angažovan na projektu, ako nije zaposlen"; "na projektu ne može biti angažovan nijedan radnik, dok projekat ne bude registrovan" $\}$

Ova dva ograničenja iz skupa $I$ su upravo ograničenja referencijalnog integriteta: $Angažovanje[MBR] \subseteq Radnik[MBR]$ i $Angažovanje[SPR] \subseteq Projekat[SPR]$.

---

## Implementacija u SQL-u (FOREIGN KEY)

U praksi, ograničenje referencijalnog integriteta implementira se putem **FOREIGN KEY** (strani ključ) ograničenja u SQL-u. Pogledajmo kako to izgleda na našem primeru.

### Kreiranje tabele Radnik

```sql
CREATE TABLE radnik (
    Mbr integer NOT NULL,
    Ime varchar(20) NOT NULL,
    Prz varchar(25) NOT NULL,
    Sef integer,
    Plt decimal(10, 2),
    Pre decimal(6, 2),
    God date NOT NULL,
    CONSTRAINT radnik_PK PRIMARY KEY (Mbr),
    CONSTRAINT radnik_FK FOREIGN KEY (Sef) REFERENCES Radnik (Mbr),
    CONSTRAINT radnik_CH CHECK (Plt > 500)
);
```

Obratite pažnju na liniju `CONSTRAINT radnik_FK FOREIGN KEY (Sef) REFERENCES Radnik (Mbr)`. Ovo je ograničenje referencijalnog integriteta koje kaže: $Radnik[Sef] \subseteq Radnik[Mbr]$. Šef svakog radnika mora biti neki postojeći radnik. Ovo je primer **autoreferencijalnog** ograničenja - tabela referencira samu sebe!

Takođe, primetite da je `Sef integer` bez NOT NULL. To znači da je $Null(Radnik, Sef) = \top$ - dozvoljeno je da radnik nema šefa (direktor firme, na primer). U zapisu relacionog modela: $Null(Radnik, Sef) = T$.

### Kreiranje tabele Projekat

```sql
CREATE TABLE projekat (
    Spr integer NOT NULL,
    Ruk integer NOT NULL,
    Nap varchar(30),
    Nar varchar(30),
    CONSTRAINT projekat_PK PRIMARY KEY (Spr),
    CONSTRAINT projekat_FK FOREIGN KEY (Ruk) REFERENCES Radnik (Mbr),
    CONSTRAINT projekat_UK UNIQUE (Nap)
);
```

Ovde imamo: $Projekat[Ruk] \subseteq Radnik[Mbr]$ i $Null(Projekat, Ruk) = \bot$ (RUK ne sme biti NULL - svaki projekat mora imati rukovodioca).

### Kreiranje tabele Radproj (Angažovanje)

```sql
CREATE TABLE radproj (
    Spr integer NOT NULL,
    Mbr integer NOT NULL,
    Brc integer NOT NULL,
    CONSTRAINT radproj_PK PRIMARY KEY (Spr, Mbr),
    CONSTRAINT radproj_rad_FK FOREIGN KEY (Mbr) REFERENCES radnik(Mbr),
    CONSTRAINT radproj_prj_FK FOREIGN KEY (Spr) REFERENCES projekat(Spr)
);
```

Ovde vidimo dva ograničenja referencijalnog integriteta:

- $Radproj[Mbr] \subseteq Radnik[Mbr]$
- $Radproj[Spr] \subseteq Projekat[Spr]$

Primarni ključ je složen: `PRIMARY KEY (Spr, Mbr)` - isti radnik na istom projektu ne može biti angažovan dva puta.

### Kompletna specifikacija relacionog modela

Za naš primer, kompletna specifikacija u notaciji relacionog modela izgleda ovako:

- `Radnik({Mbr, Ime, Prz, Sef, Plt, God, Pre}, {Mbr})`
- `Projekat({Spr, Nap, Nar, Ruk}, {Spr})`
- `Radproj({Spr, Mbr, Brc}, {Spr + Mbr})`
- $Radproj[Mbr] \subseteq Radnik[Mbr]$
- $Radproj[Spr] \subseteq Projekat[Spr]$
- $Projekat[Ruk] \subseteq Radnik[Mbr]$
- $Null(Projekat, Ruk) = \bot$
- $Radnik[Sef] \subseteq Radnik[Mbr]$
- $Null(Radnik, Sef) = \top$

> [!TIP]
> Na ispitu vas mogu pitati da napišete kompletnu specifikaciju relacionog modela za neki primer. Ne zaboravite da pored šema relacija i ključeva navedete i sva ograničenja referencijalnog integriteta, kao i ograničenja nula vrednosti za obeležja stranih ključeva!

---

## Povezivanje podataka u relacionom modelu

Hajde da se vratimo korak unazad i razumemo *zašto* je referencijalni integritet uopšte nastao. Relacioni model je razvijen 1970-ih godina (Codd, E. F., 1970) sa ciljem da otkloni nedostatke ranijih modela - mrežnog i hijerarhijskog.

Kod ranijih modela, povezivanje podataka se radilo putem fizičkih adresa - pokazivača, lanaca slogova, hijerarhijskog redosleda. Program je morao znati kako su podaci fizički organizovani. To je stvaralo čvrstu povezanost programa i fizičke strukture podataka.

Relacioni model je uveo potpuno drugačiji pristup - **asocijativno adresiranje**. Svaki podatak u bazi pronalazi se na osnovu naziva relacije, zadatih obeležja i vrednosti ključa. Povezivanje podataka se obavlja putem **prostiranja ključa** - vrednost primarnog ključa jedne relacije se pojavljuje kao strani ključ u drugoj relaciji.

SUBP vodi računa o transformaciji simboličke adrese u relativnu adresu. Program ne mora da zna ništa o fizičkoj organizaciji. To je suština nezavisnosti programa od podataka.

> [!NOTE]
> Dva su načina prostiranja ključa u relacionom modelu: (1) uvođenje stranog ključa direktno u postojeću relaciju i (2) kreiranje posebne tabele sa prostiranjem ključeva (kao što je tabela Angažovanje). U oba slučaja, transakcioni program ne vodi računa o pretvaranju simboličke u relativnu adresu.

---

## 12 principa relacionog modela i integritet

Vredi pomenuti da je Codd 1990. godine definisao 12 principa (pravila) relacionog modela podataka. Za temu referencijalnog integriteta posebno su relevantna dva:

**Rule 2 (Guaranteed Access Rule):** Svi podaci moraju biti dostupni bez dvosmislenosti. Svaka pojedinačna skalarna vrednost u bazi podataka mora biti logički adresibilna navođenjem imena tabele, imena kolone i vrednosti primarnog ključa reda.

**Rule 10 (Integrity Independence):** Ograničenja integriteta moraju biti specifikovana odvojeno od aplikacionih programa i čuvana u katalogu. Mora biti moguće menjati takva ograničenja bez nepotrebnog uticaja na postojeće aplikacije.

Ovo znači da se ograničenja referencijalnog integriteta definišu na nivou baze podataka (putem DDL naredbi), a ne u aplikacionom kodu. Time se obezbeđuje centralna kontrola i konzistentnost.

---

## Ograničenje jedinstvenosti (Uniqueness Constraint)

Pored ograničenja ključa, postoji još jedno srodno ograničenje koje vredi poznavati jer se ponekad koristi u kombinaciji sa referencijalnim integritetom.

**Ograničenje jedinstvenosti** vrednosti obeležja šeme relacije $N(R, O)$:

$$Unique(N, X)$$

gde je $X \subseteq R$ skup obeležja. Ovo zahteva da **ne-nula** kombinacija vrednosti obeležja bude jedinstvena u relaciji.

Formalno:

$$(\forall u, v \in r(R))((\forall A \in X)(u[A] \neq \omega \land v[A] \neq \omega) \Rightarrow (u[X] = v[X] \Rightarrow u = v))$$

Razlika u odnosu na ograničenje ključa: ograničenje jedinstvenosti **dozvoljava** nula vrednosti (dok ključ ne dozvoljava).

**Primer:** `Radnik({MBR, IME, PRZ, DATR, JMBG}, O)`, gde je $Unique(Radnik, JMBG)$ - ako radnik poseduje ne-nula vrednost za JMBG, onda je ta vrednost jedinstvena. Ali radnik može imati JMBG = NULL.

U SQL-u, to se implementira kao `CONSTRAINT projekat_UK UNIQUE (Nap)` - videli smo to u primeru za tabelu Projekat, gde naziv projekta mora biti jedinstven.

---

## Zadaci za vežbu - relacioni model

Na kraju, evo kompletne specifikacije relacionog modela koja se koristi kroz vežbe i zadatke:

- `radnik({Mbr, Ime, Prz, Sef, Plt, God, Pre}, {Mbr})`
- `projekat({Spr, Ruk, Nap, Nar}, {Spr})`
- `radproj({Spr, Mbr, Brc}, {Spr + Mbr})`
- $radnik[Sef] \subseteq radnik[Mbr]$
- $projekat[Ruk] \subseteq radnik[Mbr]$
- $radproj[Mbr] \subseteq radnik[Mbr]$
- $radproj[Spr] \subseteq projekat[Spr]$

> [!CAUTION]
> Na ispitu se često traži da pored šema relacija napišete i kompletna ograničenja referencijalnog integriteta. Nemojte zaboraviti autorefererencijalno ograničenje $radnik[Sef] \subseteq radnik[Mbr]$ - to je najčešća greška!

---

## 🎴 Brza pitanja (definicije i pojmovi)

**P:** Šta je ograničenje referencijalnog integriteta?

**P:** Kako se naziva šema relacije koja "pokazuje" na drugu tabelu putem stranog ključa?

**P:** Kako se naziva šema relacije na čiji ključ se referencira?

**P:** Šta je zavisnost sadržavanja i kako se formalno zapisuje?

**P:** Po čemu se ograničenje referencijalnog integriteta razlikuje od opšte zavisnosti sadržavanja?

**P:** Šta je primarni ključ i zašto se koristi u ulozi asocijativne adrese?

**P:** Koje tri operacije ažuriranja postoje u relacionom modelu i koje od njih mogu narušiti referencijalni integritet?

**P:** Šta je ograničenje jedinstvenosti i po čemu se razlikuje od ograničenja ključa?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite na primeru baze podataka sa tabelama Radnik, Projekat i Angažovanje koja ograničenja referencijalnog integriteta postoje i šta svako od njih znači u kontekstu realnog sistema.

**O:** U toj bazi postoje četiri ograničenja referencijalnog integriteta: $Projekat[RUK] \subseteq Radnik[MBR]$ (rukovodilac projekta mora biti postojeći radnik), $Angažovanje[MBR] \subseteq Radnik[MBR]$ (angažovani radnik mora postojati), $Angažovanje[SPR] \subseteq Projekat[SPR]$ (projekat angažovanja mora biti registrovan) i $Radnik[Sef] \subseteq Radnik[Mbr]$ (šef mora biti postojeći radnik, s tim da je dozvoljeno da obeležje Sef ima nula vrednost). Poslednje ograničenje je autoreferencijalno jer tabela Radnik referencira samu sebe.

**P:** Zašto operacija INSERT u referenciranu relaciju ne može narušiti referencijalni integritet, a DELETE iz referencirane relacije može? Ilustrujte primerom.

**O:** INSERT u referenciranu relaciju (npr. dodavanje novog radnika) samo dodaje novi entitet na koji niko još ne referencira, pa ne može nastati nekonzistentnost. DELETE iz referencirane relacije (npr. brisanje radnika) može narušiti integritet jer na obrisanu torku mogu referencirati torke iz drugih tabela. Na primer, ako obrišemo radnika sa MBR = 110 koji je rukovodilac projekta (RUK = 110 u tabeli Projekat), projekat bi referencirao nepostojećeg radnika.

**P:** Napišite SQL naredbe za kreiranje tabele `faze_projekta` sa ključem (Spr + Sfp) i ograničenjima referencijalnog integriteta: $faze\_projekta[Spr] \subseteq projekat[Spr]$ i $faze\_projekta[Rukfp] \subseteq radnik[Mbr]$.

**O:** Naredba bi glasila: `CREATE TABLE faze_projekta (Spr integer NOT NULL, Sfp integer NOT NULL, Rukfp integer, Nafp varchar2(20), Datp date, CONSTRAINT faze_projekta_PK PRIMARY KEY (Spr, Sfp), CONSTRAINT faze_projekta_fk1 FOREIGN KEY (Spr) REFERENCES projekat(Spr), CONSTRAINT faze_projekta_fk2 FOREIGN KEY (Rukfp) REFERENCES radnik(Mbr), CONSTRAINT faze_projekta_uk UNIQUE(Nafp));` Obeležja Spr i Sfp su NOT NULL jer su deo primarnog ključa, dok Rukfp dozvoljava nula vrednost.

**P:** Objasnite razliku između formalne i suštinske konzistentnosti baze podataka i ulogu ograničenja referencijalnog integriteta u održavanju konzistentnosti.

**O:** Baza je u formalno konzistentnom stanju ako svaka relacija zadovoljava sva ograničenja svoje šeme i ako su zadovoljena sva međurelaciona ograničenja (uključujući referencijalni integritet). Baza je u suštinski konzistentnom stanju ako je formalno konzistentna i verno predstavlja stanje realnog sistema. SUBP može automatski kontrolisati samo formalnu konzistentnost, dok se suštinska konzistentnost ne može potpuno automatizovati. U praksi, nivo pojave grešaka u bazi svodi se na ispod 2-3%.
