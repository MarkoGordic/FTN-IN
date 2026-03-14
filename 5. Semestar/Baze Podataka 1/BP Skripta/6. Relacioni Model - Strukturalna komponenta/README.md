# Relacioni model podataka - Strukturalna komponenta

## Odakle dolazi relacioni model i zašto nam treba?

Pre nego što uđemo u samu strukturalnu komponentu, hajde da razumemo kontekst. Zamislimo da je početak 1970-ih godina. Programeri koji rade sa bazama podataka koriste mrežne i hijerarhijske modele - sisteme u kojima su programi čvrsto povezani sa fizičkom strukturom podataka na disku. Ako bi se promenio način kako se podaci čuvaju, morali biste da menjate i programe. Svaki program je morao da zna gde su slogovi fizički smešteni, kako su povezani pokazivačima, kojim redosledom se čitaju... Pravi košmar za održavanje.

Tada se pojavljuje **Edgar F. Codd** sa čuvenim radom iz 1970. godine: *"A Relational Model of Data for Large Shared Data Banks"* (Communications of the ACM 13(6): 377-387). Codd je imao jasan cilj - otkloniti sve te nedostatke starih modela:

- **Čvrsta povezanost logičkih i fizičkih aspekata** - programi su bili zavisni od toga kako su podaci fizički organizovani
- **Strukturalna kompleksnost** - mrežni i hijerarhijski modeli su bili komplikovani za razumevanje
- **Navigacioni jezici** - za pristup podacima morali ste "navigirati" kroz strukture pokazivačima

Codd je insistirao na tome da model podataka mora imati čvrste **matematičke osnove**. Relacioni model se zato oslanja na **teoriju skupova i relacija**, kao i na **predikatski račun I reda**. Nisu to bile prazne akademske ambicije - ova matematička pozadina je omogućila da se precizno definiše šta model može, šta sme, i kako se podaci mogu pretraživati.

### Ključni zahtev: nezavisnost programa od podataka

Kod starijih modela, fizički aspekti baze podataka bili su ugrađeni direktno u programe: raspodela slogova po zonama, fizički redosled i logičko grupisanje slogova, transformacija vrednosti ključa u adresu, lanci slogova sa pokazivačima, hijerarhijski redosled slogova, postupci zaštite podataka...

Coddovo rešenje: **potpuno odvajanje prezentacionog od formata memorisanja**. Relacija kao skup n-torki postaje osnovna struktura, a njen apstraktni opis - **šema relacije** - izgleda ovako:

$$N(R, C)$$

gde je:
- $N$ - naziv šeme relacije
- $R$ - skup obeležja (atributa)
- $C$ - skup ograničenja, pri čemu je $K \subseteq C$ - obavezno zadat, neprazan skup ključeva

U početnim fazama projektovanja, šema relacije se često posmatra kao:

$$N(R, K)$$

---

## Tri komponente svakog modela podataka

Svaki model podataka, pa i relacioni, ima tri komponente. Zamislimo ih kao tri stuba na kojima stoji celokupna zgrada baze podataka:

1. **Strukturalna komponenta** - definiše "gradivne elemente" modela. To su primitivni i složeni koncepti kojima opisujemo strukturu podataka. Služi za modeliranje logičke strukture obeležja (LSO) kao statičke strukture sistema, tj. šeme baze podataka.

2. **Operacijska komponenta** - definiše jezike za rad sa podacima: upitni jezik (QL), jezik za manipulisanje podacima (DML), jezik za definiciju podataka (DDL). Služi za modeliranje dinamike izmene stanja.

3. **Integritetna komponenta** - definiše skup tipova ograničenja (uslova integriteta). Služi za modeliranje ograničenja nad podacima u bazi podataka.

> [!IMPORTANT]
> Na ispitu se često traži da nabrojite i objasnite sve tri komponente modela podataka. Zapamtite: strukturalna = šta gradimo, operacijska = šta možemo da radimo, integritetna = koja pravila moramo da poštujemo.

Svaka od ovih komponenti postoji na **dva nivoa apstrakcije**:

- **Nivo intenzije (konteksta)** - nivo tipa, opisuje logičku strukturu obeležja, tj. šeme
- **Nivo ekstenzije (konkretizacije)** - nivo pojave tipa, opisuje logičku strukturu podataka, tj. konkretne vrednosti

Ovo razlikovanje je izuzetno bitno i provlači se kroz celu priču o strukturalnoj komponenti, pa hajde da ga odmah ilustrujemo. Zamislimo studentsku službu. **Intenzija** bi bila opis "postoji tabela Studenti koja ima kolone BRI, IME, PRZ, BPI" - to je šema koja se retko menja. **Ekstenzija** bi bile konkretne vrednosti u toj tabeli - podaci o Ivi, Ani, Evi - oni se menjaju svaki dan.

---

## Strukturalna komponenta - veliki pregled

Sada ulazimo u srce teme. Strukturalna komponenta nam daje sve koncepte koje koristimo da opišemo kako su podaci organizovani u relacionom modelu. Hajde da krenemo od najjednostavnijih pojmova i postepeno gradimo ka složenijim.

### Primitivni koncepti

**Primitivni koncepti** su osnovni gradivni blokovi od kojih se sve ostalo konstruiše. U relacionom modelu podataka (RMP) postoje tri primitivna koncepta:

1. **Obeležje (Atribut)** - reprezentuje osobinu (svojstvo) klase entiteta ili poveznika u realnom sistemu. Na primer, ako govorimo o studentima, obeležja bi bila: BRI (broj indeksa), IME, PRZ (prezime), BPI (broj položenih ispita)...

2. **Domen** - specifikacija skupa mogućih vrednosti koje neka obeležja mogu da dobiju. Na primer, domen za ocenu bi bio skup {5, 6, 7, 8, 9, 10}, domen za pol bi bio {m, ž}.

3. **Pravilo pridruživanja domena obeležjima** - svakom obeležju se obavezno pridružuje tačno jedan domen. Ovo je kao pravilo: ne možete imati obeležje "u vazduhu" - ono mora imati definisan skup mogućih vrednosti.

> [!TIP]
> Zamislite obeležje kao etiketu na fioci, a domen kao opis toga šta sme da stoji u toj fioci. Obeležje IME ima domen koji kaže "ovde mogu biti stringovi do 30 karaktera". Obeležje OCE (ocena) ima domen koji kaže "ovde može biti broj od 5 do 10".

Ovi primitivni koncepti se dalje dele prema nivou apstrakcije:

- **Primitivni koncepti nivoa intenzije**: domen i obeležje (opisuju strukturu)
- **Primitivni koncept nivoa ekstenzije**: vrednost (konkretni podatak)

Svi ostali (složeni) koncepti strukturalne komponente nastaju **kombinovanjem primitivnih koncepata** prema definisanim pravilima relacionog modela.

---

### Kompletna hijerarhija koncepata

Hajde da sada pogledamo celokupnu sliku - sve koncepte strukturalne komponente RMP, podeljene po nivoima:

| Nivo intenzije (šema) | Nivo ekstenzije (podaci) |
|---|---|
| Domen | Vrednost |
| Obeležje | Podatak |
| Skup obeležja | Torka (N-torka) |
| Šema relacije | Relacija |
| Šema baze podataka | Baza podataka |

Ova tabela je mapa našeg putovanja. Svaki red predstavlja par: kako se nešto opisuje (intenzija) i kako to izgleda kada se popuni konkretnim podacima (ekstenzija). Krenućemo redom, od torke (jer domen, obeležje i vrednost smo već objasnili), pa sve do baze podataka.

> [!IMPORTANT]
> Ova tabela sa pet parova (intenzija-ekstenzija) je klasično ispitno pitanje. Morate je znati napamet i umeti da objasnite svaki par.

---

## Torka - osnovna jedinica podataka

### Definicija torke

Hajde da zamislimo konkretnog studenta - Anu, sa brojem indeksa 101, ženskog pola, koja radi na projektu sa šifrom 1100, pod nazivom "Univerzitetski IS". Svi ti podaci zajedno, vezani za jednu osobu, čine jednu **torku**.

**Torka** reprezentuje jednu pojavu entiteta ili poveznika. Pomoću torke se svakom obeležju, iz nekog skupa obeležja, dodeljuje konkretna vrednost iz skupa mogućih vrednosti definisanog domenom.

Formalno, za:
- $U = \{A_1, \ldots, A_n\}$ - skup obeležja
- $DOM = \bigcup_{i=1}^{n} dom(A_i)$ - skup svih mogućih vrednosti

**Torka** predstavlja preslikavanje:

$$t : U \rightarrow DOM, \quad (\forall A_i \in U)(t(A_i) \in dom(A_i))$$

Ovo nam kaže: torka je funkcija koja svakom obeležju iz skupa $U$ dodeljuje jednu vrednost, i ta vrednost mora biti iz domena tog obeležja.

### Primer torke

Neka je $U = \{MBR, IME, POL, SPR, NAP\}$.

Torka $t_1$ definisana je na sledeći način:
- $t_1(MBR) = 101$
- $t_1(IME) = Ana$
- $t_1(POL) = ž$
- $t_1(SPR) = 1100$
- $t_1(NAP) = Univerzitetski\ IS$

Torka $t_1$ se može prikazati i kao **skup podataka** (parova obeležje-vrednost):

$$t_1 = \{(MBR, 101), (IME, Ana), (POL, ž), (SPR, 1100), (NAP, Univerzitetski\ IS)\}$$

Slično, druga torka:

$$t_2 = \{(MBR, 210), (IME, Aca), (POL, m), (SPR, 0105), (NAP, Polaris)\}$$

> [!NOTE]
> Primetite da je torka po definiciji **skup** uređenih parova (obeležje, vrednost). To znači da redosled parova unutar torke nije bitan - torka $\{(MBR, 101), (IME, Ana)\}$ je isto što i $\{(IME, Ana), (MBR, 101)\}$.

---

### Restrikcija torke

Ponekad nas ne zanimaju svi podaci iz torke, već samo neki. Na primer, od svih podataka o Aci, zanima nas samo matični broj i ime. Za to služi **restrikcija** (skraćenje) torke.

**Restrikcija torke** $t$ na skup obeležja $X \subseteq U$ (oznaka: $t[X]$) svakom obeležju iz skupa $X$ pridružuje onu vrednost koju je imala polazna torka $t$.

Formalno:

$$X \subseteq U, \quad t: U \rightarrow DOM$$
$$t[X]: X \rightarrow DOM$$
$$(\forall A \in X)(t[X](A) = t(A))$$

### Primer restrikcije

Imamo torku:

$$t_2 = \{(MBR, 210), (IME, Aca), (POL, m), (SPR, 0105), (NAP, Polaris)\}$$

Neka je $X = MBR + IME$ (zapis $MBR + IME$ je skraćena notacija za skup $\{MBR, IME\}$).

Tada je restrikcija:

$$t_2[X] = \{(MBR, 210), (IME, Aca)\}$$

Jednostavno smo "odsekli" sve kolone koje nas ne zanimaju i zadržali samo MBR i IME sa njihovim originalnim vrednostima.

> [!TIP]
> Restrikcija torke se može zamisliti kao skrivanje kolona u Excel tabeli. Imate red sa svim podacima o nekom radniku, ali sakrijete sve kolone osim matičnog broja i imena - to je restrikcija.

---

## Relacija - skup torki

### Definicija relacije

Zamislimo da u firmi imamo više zaposlenih. Svaki od njih je opisan jednom torkom. Kada sve te torke skupimo zajedno, dobijamo **relaciju**.

**Relacija** nad skupom obeležja $U$ predstavlja konačan skup torki. Ona reprezentuje skup realnih entiteta ili poveznika.

Formalno:

$$r(U) \subseteq \{t \mid t: U \rightarrow DOM\}, \quad |r| \in \mathbb{N}_0$$

Izraz $\{t \mid t: U \rightarrow DOM\}$ je skup svih mogućih torki nad skupom obeležja $U$ i naziva se **Tuple(U)**.

Dakle, relacija je konačan podskup skupa svih mogućih torki. Kardinalnost relacije (broj torki) je prirodan broj ili nula.

### Primer relacije

Neka je $U = \{MBR, IME, POL, SPR, NAP\}$.

$$r_1(U) = \{t_1, t_2\}$$

gde su:
- $t_1 = \{(MBR, 101), (IME, Ana), (POL, ž), (SPR, 1100), (NAP, Univerzitetski\ IS)\}$
- $t_2 = \{(MBR, 210), (IME, Aca), (POL, m), (SPR, 0105), (NAP, Polaris)\}$

### Još jedan primer

Neka je $R = \{A, B, C\}$ sa domenima $dom(A) = \{a_1, a_2\}$, $dom(B) = \{b_1, b_2\}$, $dom(C) = \{c_1, c_2\}$.

Definišimo tri torke:
- $t_1 = \{(A, a_1), (B, b_1), (C, c_1)\}$
- $t_2 = \{(A, a_2), (B, b_2), (C, c_2)\}$
- $t_3 = \{(A, a_1), (B, b_1), (C, c_2)\}$

Relacija: $r(R) = \{t_1, t_2, t_3\}$

---

### Svojstva relacije

Relacija ima nekoliko bitnih svojstava koja je razlikuju od "obične tabele":

1. **U relaciji se ne mogu pojaviti dve identične torke.** Ako bi se pojavile dve iste, to je onda ista torka samo dva puta prikazana - a relacija je skup, i skupovi ne dozvoljavaju duplikate.

2. **Poredak obeležja (kolona) ne utiče na informacije** koje relacija nosi - nebitan je. Tabela sa kolonama (MBR, IME, POL) i tabela sa kolonama (IME, MBR, POL) nose iste informacije.

3. **Poredak torki u relaciji ne utiče na informacije** koje relacija nosi - nebitan je. Nema "prvog" ili "poslednjeg" reda - svi su ravnopravni.

### Tabelarna reprezentacija

Uobičajeni način prikazivanja relacije je pomoću **tabele**:
- Relacija = kompletan sadržaj tabele (kratko: tabela)
- Šema relacije = opis tabele (definicija tabele)

| MBR | IME | POL | SPR | NAP |
|-----|-----|-----|------|-----|
| 101 | Ana | ž | 1100 | Univerzitetski IS |
| 210 | Aca | m | 0105 | Polaris |

Svaki red tabele je jedna torka. Svaka kolona odgovara jednom obeležju.

> [!WARNING]
> Česta greška na ispitu: studenti poistovećuju relaciju sa tabelom. Relacija je matematički koncept (skup torki), a tabela je samo njen uobičajeni vizuelni prikaz. Razlika: u tabeli može biti bitan redosled redova i kolona, dok u relaciji nikada nije.

---

## Strukturalna jednostavnost relacionog modela

Hajde da napravimo kratak izlet i razumemo zašto je Codd izabrao baš ovakvu strukturu. Koncept **relacije** je osnova reprezentacije logičkih struktura podataka u RMP i ima nekoliko prednosti:

- Ne sadrži nikakve informacije o fizičkoj organizaciji podataka
- Predstavlja "prirodnu" upotrebu jednog od fundamentalnih matematičkih koncepata
- Relacija je "homogena" i "uniformna" struktura, lako razumljiva korisnicima

### Asocijativno adresiranje (selekcija podataka)

Kod starijih modela, da biste pronašli podatak, koristili ste fizičke adrese (relativne ili apsolutne), pozicioniranje upotrebom indikatora ili pozicioniranje putem odnosa između podataka.

Kod relacionog modela koristi se **asocijativno adresiranje** - isključiva upotreba simboličkih adresa, vrlo često vrednosti ključa. Svaki podatak u bazi podataka pronalazi se na osnovu: **naziva relacije, zadatih obeležja i vrednosti ključa**. Skup torki sa zajedničkom osobinom selektira se na uniforman način - zadavanjem istog logičkog uslova. SUBP (sistem za upravljanje bazom podataka) vodi računa o transformaciji simboličke u relativnu adresu.

### Povezivanje podataka prostiranjem ključa

Kod starijih modela, povezivanje podataka vršilo se pomoću fizičkih adresa u funkciji pokazivača i fizičkim pozicioniranjem logički susednih podataka - o čemu je svaki transakcioni program morao da vodi računa.

Kod relacionog modela koristi se upotreba **simboličkih adresa - prenetih vrednosti ključa**. Rešenje se ostvaruje:
- **Prostiranjem ključa** - uvođenjem pojma stranog ključa i ograničenja referencijalnog integriteta
- **Kreiranjem posebne tabele sa prostiranjem ključeva**

U oba slučaja, transakcioni program ne vodi računa o pretvaranju simboličke u relativnu adresu.

### Primer asocijativnog adresiranja i prostiranja ključa

Pogledajmo dve tabele:

**Fakultet:**

| SFK | NAZ | BIP |
|-----|-----|-----|
| FIL | Filozofski | 1 |
| PMF | Matematički | 7 |
| ETF | Elektrotehnički | 9 |
| EKF | Ekonomski | 4 |
| MAF | Mašinski | 7 |

**Projektant:**

| MBR | IME | PRZ | SFK |
|-----|-----|-----|-----|
| M3 | Iva | Ban | PMF |
| M1 | Ana | Tot | MAF |
| M4 | Ana | Ras | FIL |
| M8 | Aca | Pap | ETF |
| M6 | Iva | Ban | EKF |
| M5 | Eva | Tot | ETF |

Kolona SFK u tabeli Projektant je **preneta vrednost ključa** iz tabele Fakultet. Ovo je primer prostiranja ključa - podaci se povezuju logički, putem zajedničkih vrednosti, a ne fizičkim pokazivačima.

---

## Šema relacije

### Definicija šeme relacije

Sada prelazimo na nivo intenzije. Dok je relacija konkretan skup torki (podataka), **šema relacije** je njen apstraktni opis - govori nam kakva relacija može da postoji, ali ne sadrži konkretne podatke.

**Šema relacije** je imenovani par:

$$N(R, O)$$

gde je:
- $N$ - naziv šeme relacije (može biti izostavljen)
- $R$ - skup obeležja šeme relacije
- $O$ - skup ograničenja šeme relacije

**Pojava nad šemom relacije** $(R, O)$ je bilo koja relacija $r(R)$ takva da zadovoljava sva ograničenja iz skupa $O$.

Zamislimo to kao šablon i dokument. Šema relacije je šablon ("Ovde piše ime, ovde prezime, ovde JMBG, i svi moraju biti popunjeni"), a pojava je konkretan popunjeni dokument koji poštuje ta pravila.

### Primer šeme relacije i njenih pojava

Data je šema relacije:

$$Letovi(\{P, A, L\}, O)$$

gde je $O = \{"Pilot\ može\ da\ leti\ samo\ na\ jednom\ tipu\ aviona"\}$

Pogledajmo dve kandidat-relacije i proverimo da li su validne pojave nad ovom šemom:

**Let1:**

| P | A | L |
|---|---|---|
| Pop | 747 | 101 |
| Pop | 747 | 102 |
| Ana | 737 | 103 |

**Let2:**

| P | A | L |
|---|---|---|
| Pop | 747 | 101 |
| Pop | 737 | 102 |
| Ana | 737 | 103 |

Let1 **jeste** validna pojava - pilot Pop leti samo na tipu 747, a pilot Ana samo na 737. Ograničenje je zadovoljeno.

Let2 **nije** validna pojava - pilot Pop leti i na 747 i na 737. Ograničenje je narušeno!

> [!CAUTION]
> Na ispitu se često daje šema relacije sa ograničenjima i traži da se proveri da li je neka relacija validna pojava. Uvek proverite svako ograničenje za svaku torku - jedna jedina torka koja krši pravilo čini celu relaciju nevalidnom.

---

## Relaciona šema baze podataka

### Definicija

Realna baza podataka ne sadrži samo jednu tabelu, već više njih. Skup svih šema relacija zajedno sa pravilima koja važe između njih čini **relacionu šemu baze podataka**.

**Relaciona šema baze podataka** je (imenovani) par:

$$(S, I)$$

gde je:
- $S$ - skup šema relacija: $S = \{(R_i, O_i) \mid i \in \{1, \ldots, n\}\}$
- $I$ - skup međurelacionih ograničenja (pravila koja važe između različitih relacija)

### Primer

Zadate su šeme relacija:

**Radnik**$(\{MBR, IME, PRZ, DATR\}, O_1)$

$O_1$: "Ne postoje dva radnika sa istom vrednošću za MBR. Svaki radnik poseduje vrednost za MBR."

**Projekat**$(\{SPR, NAP\}, O_2)$

$O_2$: "Ne postoje dva projekta sa istom vrednošću za SPR. Svaki projekat poseduje vrednost za SPR."

**Angažovanje**$(\{SPR, MBR, BRC\}, O_3)$

$O_3$: "Ne može se isti radnik na istom projektu angažovati više od jedanput. Pri angažovanju, vrednosti za MBR i SPR su uvek poznate."

Skup šema relacija: $S = \{Radnik, Projekat, Angažovanje\}$

Međurelaciona ograničenja:

$I = \{$
"radnik ne može biti angažovan na projektu, ako nije zaposlen";
"na projektu ne može biti angažovan ni jedan radnik, dok projekat ne bude registrovan"
$\}$

Par $(S, I)$ predstavlja jednu relacionu šemu baze podataka.

> [!NOTE]
> Primetite razliku: ograničenja u $O_i$ su **unutarrelaciona** (važe unutar jedne tabele), dok su ograničenja u $I$ **međurelaciona** (važe između tabela). Na primer, "MBR mora biti jedinstven" je unutarrelaciono, a "ne možeš angažovati radnika koji ne postoji" je međurelaciono.

---

## Relaciona baza podataka

### Definicija

Ako je šema baze podataka šablon, onda je **relaciona baza podataka** konkretan popunjeni formulare - jedna pojava nad tom šemom.

**Relaciona baza podataka** je jedna pojava nad zadatom relacionom šemom baze podataka $(S, I)$:

$$s: S \rightarrow \{r_i \mid i \in \{1, \ldots, n\}\}, \quad (\forall i)\ s(R_i, O_i) = r_i$$

Ovo znači: svakoj šemi relacije iz skupa $S$ odgovara jedna njena pojava (konkretna relacija), i skup tih relacija $s$ mora da zadovoljava sva međurelaciona ograničenja iz skupa $I$.

### Primer

Za naš skup šema $S = \{Radnik, Projekat, Angažovanje\}$, relaciona baza podataka $RBP = \{radnik, projekat, angažovanje\}$ bi izgledala:

**radnik:**

| MBR | IME | PRZ | DATR |
|-----|-----|-----|------|
| 101 | Ana | Pap | 12.12.65. |
| 102 | Aca | Tot | 13.11.48. |
| 110 | Ivo | Ban | 01.01.49. |
| 111 | Olja | Kun | 06.05.71. |

**projekat:**

| SPR | NAP |
|-----|-----|
| 11 | X25 |
| 13 | Polaris |
| 14 | Univ. IS |

**angažovanje:**

| MBR | SPR |
|-----|-----|
| 101 | 11 |
| 101 | 14 |
| 102 | 14 |

---

### Odnos šema BP i BP

Baza podataka **reprezentuje jedno stanje realnog sistema**. Ona se ažurira jer promene stanja realnog sistema treba da prate odgovarajuće promene podataka u bazi.

Evo kako izgledaju dva nivoa:

- **Nivo intenzije** (šema BP): $(\{(R_1, O_1), \ldots, (R_n, O_n)\}, I)$ - **statička**, sporo promenljiva kategorija sistema BP
- **Nivo ekstenzije** (relaciona BP): $\{r_1(R_1), \ldots, r_n(R_n)\}$ - **dinamička**, stalno promenljiva kategorija sistema BP

Zamislimo to ovako: struktura tabela (koje kolone postoje, koja pravila važe) se menja retko - možda jednom godišnje se doda nova kolona. Ali podaci u tabelama se menjaju svakodnevno - dodaju se novi radnici, menjaju im se plate, brišu se stari projekti.

> [!IMPORTANT]
> Šema BP je statička kategorija (menja se retko), a baza podataka je dinamička kategorija (menja se stalno). Ovo je česta tema na ispitu.

---

## Konzistentno stanje baze podataka

### Formalna i suštinska konzistentnost

Kada radimo sa bazom podataka, moramo se zapitati: da li su podaci u njoj ispravni? Postoje dva nivoa "ispravnosti":

**Baza podataka** $RBP = \{r_i \mid i \in \{1, \ldots, n\}\}$ nad šemom $(S, I)$ nalazi se u:

1. **Formalno konzistentnom stanju** ako:
   - $(\forall r_i \in RBP)(r_i\ zadovoljava\ sva\ ograničenja\ odgovarajuće\ šeme\ (R_i, O_i))$
   - $RBP$ zadovoljava sva međurelaciona ograničenja iskazana putem $I$

2. **Suštinski konzistentnom stanju** ako:
   - Se nalazi u formalno konzistentnom stanju **i**
   - Predstavlja **vernu sliku stanja realnog sistema**

Hajde da ovo objasnimo kroz primer. Zamislimo bazu podataka za fakultet. Ako u tabeli Radnik ne postoje dva radnika sa istim MBR - formalna konzistentnost je zadovoljena. Ali ako je radnik Ivo Ban stvarno promenio prezime u Jović pre mesec dana, a u bazi još stoji Ban - baza nije suštinski konzistentna jer ne odražava realno stanje.

U praksi, nivo pojave grešaka u bazama podataka sveden je na ispod **2-3%**. SUBP može da kontroliše samo **formalnu konzistentnost** (proverava da li su ograničenja zadovoljena), ali ne može da zna da li podaci zaista odgovaraju realnom svetu - to je odgovornost korisnika i poslovnih procesa.

> [!WARNING]
> Razlika između formalne i suštinske konzistentnosti je omiljena tema na usmenom ispitu. SUBP kontroliše samo formalnu - za suštinsku su odgovorni ljudi i procesi.

---

## 12 principa relacionog modela podataka

Codd je 1990. godine objavio delo *"The Relational Model for Data Base Management: Version 2"* (Addison Wesley) u kome je definisao 12 pravila (principa) kojima sistem mora da udovolji da bi se smatrao relacionim SUBP (RDBMS). Hajde da ih prođemo:

### Pravilo 0: Kvalifikacija sistema
Da bi se sistem kvalifikovao kao RDBMS, mora koristiti svoje relacione mogućnosti (isključivo) za upravljanje bazom podataka.

### Pravilo 1: Pravilo informacija
Sve informacije u bazi podataka moraju biti reprezentovane na jedan i samo jedan način - vrednostima u kolonama redova tabela.

### Pravilo 2: Pravilo garantovanog pristupa
Svaki podatak mora biti dostupan bez dvosmislenosti. Svaka pojedinačna skalarna vrednost mora biti logički adresabilna navođenjem: naziva tabele, naziva kolone i vrednosti primarnog ključa.

### Pravilo 3: Sistematsko tretiranje nula vrednosti
SUBP mora dozvoliti da svako polje ostane null (prazno). Mora podržavati reprezentaciju "nedostajuće informacije" koja je sistematska, različita od svih regularnih vrednosti i nezavisna od tipa podatka.

### Pravilo 4: Aktivan online katalog zasnovan na relacionom modelu
Sistem mora podržavati online relacioni katalog kome ovlašćeni korisnici mogu pristupiti istim upitnim jezikom kojim pristupaju podacima.

### Pravilo 5: Pravilo sveobuhvatnog podjezika za podatke
Sistem mora podržavati bar jedan relacioni jezik koji ima linearnu sintaksu, može se koristiti interaktivno i unutar aplikacija, i podržava: operacije definicije podataka, operacije manipulacije podacima, bezbednost i ograničenja integriteta, operacije upravljanja transakcijama (begin, commit, rollback).

### Pravilo 6: Pravilo ažuriranja pogleda
Svi pogledi koji su teoretski ažurabilni moraju biti ažurabilni od strane sistema.

### Pravilo 7: Unos, ažuriranje i brisanje visokog nivoa
Sistem mora podržavati operatore za unos, ažuriranje i brisanje nad skupovima podataka (set-at-a-time), ne samo nad pojedinačnim redovima.

### Pravilo 8: Fizička nezavisnost podataka
Promene na fizičkom nivou (način skladištenja podataka) ne smeju zahtevati promenu aplikacija.

### Pravilo 9: Logička nezavisnost podataka
Promene na logičkom nivou (tabele, kolone, redovi) ne smeju zahtevati promenu aplikacija. Logička nezavisnost je teže ostvariva od fizičke.

### Pravilo 10: Nezavisnost integriteta
Ograničenja integriteta moraju biti specifikovana odvojeno od aplikativnih programa i smeštena u katalog.

### Pravilo 11: Nezavisnost distribucije
Distribucija delova baze podataka na različite lokacije treba da bude nevidljiva korisnicima.

### Pravilo 12: Pravilo nesubverzije
Ako relacioni sistem ima jezik niskog nivoa (rad sa pojedinačnim zapisima), taj jezik se ne sme koristiti za zaobilaženje pravila i ograničenja integriteta.

> [!TIP]
> Ne morate pamtiti svih 12 pravila napamet sa tačnim engleskim nazivima, ali trebate razumeti suštinu svakoga. Posebno su bitna pravila 1, 2, 3, 8, 9 i 12 jer se najčešće pitaju.

---

## Primer iz materijala: Fakultet i šema relacije

Da zaokružimo priču, pogledajmo kako se šema relacije koristi u praksi.

Šema relacije:

$$Fakultet(\{SFK, NAZ, BIP\}, \{SFK\})$$

Ovo nam kaže: relacija Fakultet ima tri obeležja (SFK - šifra fakulteta, NAZ - naziv, BIP - broj ispitnih predmeta) i jedan ključ (SFK).

Pojava (relacija):

$$r(Fakultet) = \{(PMF, Matematički, 7), (EKF, Ekonomski, 4), (ETF, Elektrotehnički, 9), (MAF, Mašinski, 7)\}$$

Šta bi se desilo ako pokušamo da unesemo novu torku $(EKF, Elektronski, 8)$? Ova torka bi **narušila ograničenje ključa** jer već postoji torka sa vrednošću $SFK = EKF$. SUBP bi odbio ovaj unos i prijavio grešku.

---

## Kratka rekapitulacija

Prešli smo dugačak put. Hajde da se podsetimo šta smo naučili:

Krenuli smo od motivacije - zašto je relacioni model nastao i koje probleme rešava. Upoznali smo se sa tri komponente modela podataka, sa posebnim fokusom na strukturalnu. Naučili smo primitivne koncepte (obeležje, domen, pravilo pridruživanja), pa smo gradili ka složenijim: torka, restrikcija torke, relacija sa njenim svojstvima, šema relacije, relaciona šema baze podataka, i konačno sama relaciona baza podataka. Razumeli smo razliku između nivoa intenzije i ekstenzije, između formalne i suštinske konzistentnosti. I na kraju, prošli smo kroz Coddovih 12 principa relacionog modela.

Svi ovi koncepti su međusobno povezani i grade jednu koherentnu celinu - od najjednostavnijeg pojma (vrednost) do najsloženijeg (baza podataka), sve je izgrađeno kombinovanjem prostijih delova po strogo definisanim pravilima.

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

P: Šta je obeležje (atribut) u relacionom modelu?

P: Šta je domen u relacionom modelu?

P: Kako glasi pravilo pridruživanja domena obeležjima?

P: Koji su primitivni koncepti nivoa intenzije?

P: Koji je primitivni koncept nivoa ekstenzije?

P: Kako nastaju složeni koncepti strukturalne komponente RMP?

P: Nabrojte svih pet koncepata nivoa intenzije u strukturalnoj komponenti RMP.

P: Nabrojte svih pet koncepata nivoa ekstenzije u strukturalnoj komponenti RMP.

P: Šta je torka?

P: Kako glasi formalna definicija torke?

P: Šta je $DOM$ u definiciji torke?

P: Šta je $Tuple(U)$?

P: Šta je restrikcija torke i kako se označava?

P: Kako glasi formalna definicija restrikcije torke?

P: Šta je relacija nad skupom obeležja $U$?

P: Kako glasi formalna definicija relacije?

P: Zašto u relaciji ne mogu postojati dve identične torke?

P: Da li je poredak obeležja (kolona) bitan u relaciji?

P: Da li je poredak torki u relaciji bitan?

P: Šta u tabelarnom prikazu odgovara relaciji, a šta šemi relacije?

P: Šta je šema relacije i kako se formalno zapisuje?

P: Šta je $N$, $R$, i $O$ u zapisu $N(R, O)$?

P: Šta je pojava nad šemom relacije?

P: Kako se šema relacije zapisuje u početnim fazama projektovanja?

P: Šta je $K$ u zapisu $N(R, K)$?

P: Šta je relaciona šema baze podataka?

P: Kako se formalno zapisuje relaciona šema baze podataka?

P: Šta je $S$, a šta $I$ u paru $(S, I)$?

P: Šta su međurelaciona ograničenja?

P: Šta je relaciona baza podataka?

P: Kako glasi formalna definicija relacione baze podataka?

P: Šta reprezentuje baza podataka u smislu realnog sistema?

P: Šta je nivo intenzije?

P: Šta je nivo ekstenzije?

P: Da li je šema BP statička ili dinamička kategorija?

P: Da li je relaciona BP statička ili dinamička kategorija?

P: Kada je baza podataka u formalno konzistentnom stanju?

P: Kada je baza podataka u suštinski konzistentnom stanju?

P: Koji nivo konzistentnosti može kontrolisati SUBP?

P: Na koliko procenata je u praksi sveden nivo pojave grešaka u BP?

P: Ko je Edgar F. Codd i koji je njegov značaj za relacioni model?

P: Koje su matematičke osnove relacionog modela podataka?

P: Koji su nedostaci mrežnog i hijerarhijskog modela?

P: Šta je asocijativno adresiranje?

P: Na osnovu čega se pronalazi svaki podatak u BP u relacionom modelu?

P: Šta je prostiranje ključa?

P: Šta je strukturalna komponenta modela podataka?

P: Šta je operacijska komponenta modela podataka?

P: Šta je integritetna komponenta modela podataka?

P: Nabrojte tri komponente modela podataka.

P: Šta je Pravilo 0 iz 12 principa RMP?

P: Šta kaže Pravilo 1 (pravilo informacija) iz 12 principa RMP?

P: Šta kaže Pravilo 2 (pravilo garantovanog pristupa)?

P: Šta kaže Pravilo 3 (sistematsko tretiranje nula vrednosti)?

P: Šta kaže Pravilo 8 (fizička nezavisnost podataka)?

P: Šta kaže Pravilo 9 (logička nezavisnost podataka)?

P: Šta kaže Pravilo 12 (pravilo nesubverzije)?

P: Kakva je razlika između relacije i tabele?

P: Šta znači zapis $N(R, C)$ i šta je $C$?

P: Šta znači da je $K \subseteq C$ i da je $K$ neprazan?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite kako se koncepti strukturalne komponente RMP grade od primitivnih ka složenim, navodeći oba nivoa apstrakcije.

**O:** Strukturalna komponenta ima dva nivoa: intenzije i ekstenzije. Na nivou intenzije, primitivni koncepti su domen i obeležje, a od njih se grade složeni: skup obeležja, šema relacije i šema baze podataka. Na nivou ekstenzije, primitivni koncept je vrednost, od koje se grade: podatak, torka, relacija i baza podataka. Složeni koncepti nastaju kombinovanjem primitivnih prema pravilima RMP.

**P:** Dati su $U = \{A, B, C\}$, $dom(A) = \{1, 2\}$, $dom(B) = \{x, y\}$, $dom(C) = \{p, q\}$ i torka $t = \{(A,1), (B,x), (C,q)\}$. Izračunajte $t[\{A, C\}]$.

**O:** Restrikcija torke $t$ na skup obeležja $\{A, C\}$ se dobija tako što se zadrže samo parovi za obeležja A i C sa njihovim originalnim vrednostima. Rezultat je: $t[\{A, C\}] = \{(A, 1), (C, q)\}$.

**P:** Objasnite razliku između formalne i suštinske konzistentnosti baze podataka i navedite ko je odgovoran za svaku.

**O:** Formalna konzistentnost znači da su sva ograničenja šema relacija i sva međurelaciona ograničenja zadovoljena - za nju je odgovoran SUBP koji automatski proverava pravila. Suštinska konzistentnost zahteva da baza, pored formalne konzistentnosti, bude i verna slika realnog sistema - za nju su odgovorni korisnici i poslovni procesi, jer SUBP ne može znati da li podaci odgovaraju stvarnosti.

**P:** Objasnite koncept asocijativnog adresiranja u RMP i uporedite ga sa pristupom kod starijih modela podataka.

**O:** Kod starijih modela, pristup podacima zahtevao je upotrebu fizičkih adresa i navigaciju kroz strukture pokazivačima. U relacionom modelu koristi se asocijativno adresiranje - svaki podatak se pronalazi isključivo na osnovu naziva relacije, zadatih obeležja i vrednosti ključa. SUBP automatski prevodi ovu simboličku adresu u fizičku, čime se postiže nezavisnost programa od fizičke organizacije podataka.

**P:** Zašto je šema BP statička kategorija, a relaciona BP dinamička? Ilustrujte primerom.

**O:** Šema BP opisuje strukturu tabela i ograničenja i menja se retko (npr. jednom godišnje kad se doda nova kolona). Relaciona BP sadrži konkretne podatke koji se menjaju stalno (svakodnevno se dodaju, menjaju ili brišu zapisi). Na primer, šema relacije Radnik(MBR, IME, PRZ) ostaje ista godinama, ali podaci u njoj se menjaju čim se zaposli novi radnik.

**P:** Data je šema $Letovi(\{P, A, L\}, O)$ gde $O$ kaže "Pilot može da leti samo na jednom tipu aviona". Da li relacija $\{(Pop, 747, 101), (Pop, DC9, 102), (Ana, 737, 103)\}$ predstavlja validnu pojavu? Obrazložite.

**O:** Ova relacija nije validna pojava nad datom šemom. Pilot Pop se pojavljuje u dve torke sa različitim tipovima aviona (747 i DC9), čime se narušava ograničenje da pilot može leteti samo na jednom tipu aviona. Da bi relacija bila validna pojava, svaki pilot bi morao imati isti tip aviona u svim torkama.

**P:** Objasnite razliku između unutarrelacionih i međurelacionih ograničenja na konkretnom primeru.

**O:** Unutarrelaciona ograničenja (skup $O_i$) važe unutar jedne šeme relacije, npr. "ne postoje dva radnika sa istim MBR" je ograničenje šeme Radnik. Međurelaciona ograničenja (skup $I$) važe između različitih šema, npr. "radnik ne može biti angažovan na projektu ako nije zaposlen" je ograničenje koje povezuje šeme Angažovanje i Radnik. Prva proveravaju jednu tabelu, druga proveravaju odnos između tabela.

**P:** Šta je Coddovo Pravilo 2 (garantovani pristup) i kako se ono manifestuje u praksi?

**O:** Pravilo 2 kaže da svaki podatak mora biti dostupan bez dvosmislenosti, navođenjem tri stvari: naziva tabele, naziva kolone i vrednosti primarnog ključa. U praksi, to znači da ako znamo da tražimo IME iz tabele Radnik gde je MBR=101, postoji tačno jedan podatak koji se može dobiti. Ovo je osnova asocijativnog adresiranja.

**P:** Objasnite zašto redosled torki i redosled obeležja nemaju uticaj na informacioni sadržaj relacije.

**O:** Relacija je definisana kao skup torki, a u teoriji skupova redosled elemenata je nebitan - skup $\{a, b\}$ je isti kao $\{b, a\}$. Slično, svaka torka je preslikavanje iz skupa obeležja u skup vrednosti, pa je nebitno kojim redom su obeležja navedena - torka $\{(A, 1), (B, 2)\}$ nosi istu informaciju kao $\{(B, 2), (A, 1)\}$. Ovo je razlika između matematičkog koncepta relacije i njene tabelarne reprezentacije gde redosled može izgledati bitan.
