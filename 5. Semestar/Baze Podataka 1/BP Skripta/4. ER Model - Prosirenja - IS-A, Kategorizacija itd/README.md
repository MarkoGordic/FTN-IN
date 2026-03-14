# ER Model - Karakteristične strukture

## Uvod: Zašto nam trebaju "karakteristične strukture"?

Kada crtamo ER dijagrame, srećemo se sa raznim kombinacijama tipova entiteta i tipova poveznika, sa različitim kardinalitetima. E sad, zamislimo da smo projektanti baze podataka i da nam neko kaže: "Radnik može raditi na više projekata, a na svakom projektu može biti angažovano više radnika." Kako to predstaviti? Ili: "Svaki radnik je raspoređen na tačno jedno radno mesto." Kako to izgleda?

Umesto da se svaki put iznova lomimo, pametna stvar je da proučimo **tipične, karakteristične strukture** koje se ponavljaju u praksi. Ako ih jednom dobro razumemo, prepoznaćemo ih u svakom novom zadatku.

U nastavku ćemo analizirati semantiku karakterističnih struktura ER modela podataka. Fokusiraćemo se na mali broj osnovnih koncepata - **tip entiteta** i **tip poveznika** - i na krajnju jednostavnost njihove veze. Osnovna pažnja ide na analizu **kardinaliteta tipa poveznika**. Polazimo od karakteristične strukture, tumačimo kakav realni sistem ona opisuje, i proveravamo da li je ER struktura veran model nekog dela realnog sistema. Pošto je to preslikavanje jedan na jedan, važi i obratno - na osnovu poznavanja karakteristika dela realnog sistema, možemo izabrati odgovarajuću ER strukturu kao njegovu vernu sliku.

---

## 1. Strukture sa kardinalitetima grupe M : N

### Šta znači M : N?

Hajde da krenemo od najopštijeg slučaja. Kardinalitet tipa poveznika opisujemo sa $R(E_1(a_2, M) : E_2(a_1, N))$. Ovo se javlja kada u realnom sistemu **jedan entitet klase $E_1$ može biti u vezi sa $M$ (više od 1) entiteta klase $E_2$**, i obratno - jedan entitet klase $E_2$ može biti u vezi sa više entiteta klase $E_1$. Tada kažemo da između dva tipa entiteta ($E_1$ i $E_2$) u modelu važi odnos **više - prema - više**, što se označava i sa $M : N$.

Hajde to da prevedemo na živ primer. Zamislimo firmu u kojoj postoje **Radnici** i **Projekti**. Jedan radnik može raditi na više projekata, a na jednom projektu može biti angažovano više radnika. To je klasičan M : N odnos.

### Tri slučaja minimalnih kardinaliteta

Vrednosti minimalnih kardinaliteta definišu tri slučaja ovog odnosa. Hajde da ih prođemo jedan po jedan.

#### Slučaj 1: $a_1 = 0$ i $a_2 = 0$

Kada su oba minimalna kardinaliteta jednaka nuli, to znači da **u obe klase mogu postojati entiteti koji nisu povezani sa bilo kojim entitetom druge klase**. Međutim, i slučaj kada su svi entiteti posmatranih klasa međusobno povezani - nije zabranjen.

Prevedeno na naš primer sa radnicima i projektima: $a_1 = 0$ i $a_2 = 0$ znači da ne mora svaki radnik raditi na bar jednom projektu, i da mogu postojati projekti na kojima još, ili više, ne radi ni jedan radnik.

Pogledajmo konkretnu ekstenziju koja zadovoljava ova ograničenja:

| Radnik | Radi | Projekat |
|--------|------|----------|
| Ivo | (Ivo, Lido) | Lido |
| Ana | (Ivo, Faktura) | Faktura |
| Eva | (Ana, Skladištenje) | Skladištenje |
| Aco | (Ana, Lido) | Nabavka |

Vidimo da Eva i Aco nisu angažovani ni na jednom projektu, a projekat Nabavka nema nijednog radnika. I to je sasvim u redu za ovaj slučaj.

#### Slučaj 2: $a_1 = 1$ i $a_2 = 0$ (ili $a_1 = 0$ i $a_2 = 1$)

Ovde minimalni kardinaliteti ukazuju da **svi entiteti jedne od povezanih klasa** (recimo klase $E_1$) **moraju biti povezani sa bar jednim entitetom druge klase** (klase $E_2$). To dalje znači da je **egzistencija entiteta u jednoj klasi** ($E_1$) **uslovljena njihovom povezanošću sa entitetima u drugoj klasi** ($E_2$).

Za naš primer: ako je $a_1 = 1$ i $a_2 = 0$, reč je o realnom sistemu u kojem ne mora svaki radnik raditi na bar jednom projektu, ali na svakom projektu mora biti angažovan bar jedan radnik. To znači da se novi projekat ne može evidentirati ako nije određen bar jedan radnik da na njemu radi. Takođe, onog trenutka kada prestane angažman poslednjeg radnika na projektu, gasi se i projekat.

| Radnik | Radi | Projekat |
|--------|------|----------|
| Ivo | (Ivo, Lido) | Lido |
| Ana | (Ivo, Faktura) | Faktura |
| Eva | (Ana, Skladištenje) | Skladištenje |
| Aco | (Ana, Lido) | Nabavka |
|  | (Eva, Nabavka) |  |

Ovde vidimo da Aco nije angažovan ni na jednom projektu (to je dozvoljeno jer $a_2 = 0$), ali svaki projekat ima bar jednog radnika (jer $a_1 = 1$).

#### Slučaj 3: $a_1 = 1$ i $a_2 = 1$

Ovo je najstrože ograničenje: minimalni kardinaliteti ukazuju da **svaki entitet jedne klase mora biti povezan sa bar jednim entitetom druge klase**. Egzistencija entiteta u obe klase uslovljena je njihovom povezanošću sa bar jednim entitetom druge klase, što predstavlja izuzetno strogo ograničenje.

| Radnik | Radi | Projekat |
|--------|------|----------|
| Ivo | (Ivo, Lido) | Lido |
| Ana | (Ivo, Faktura) | Faktura |
| Eva | (Ana, Skladištenje) | Skladištenje |
| Aco | (Ana, Lido) | Nabavka |
|  | (Eva, Skladištenje) |  |
|  | (Aco, Nabavka) |  |

Ovde je svaki radnik angažovan na bar jednom projektu i svaki projekat ima bar jednog radnika.

> [!IMPORTANT]
> Kod M : N odnosa, razlika između tri slučaja leži isključivo u **minimalnim kardinalitetima** ($a_1$ i $a_2$). Maksimalni kardinaliteti su uvek M i N (veći od 1). Na ispitu obratite pažnju koji slučaj se traži - svaki od njih ima različitu semantiku u realnom sistemu.

---

## 2. Strukture sa kardinalitetima grupe N : 1

### Šta znači N : 1?

Prelazimo na sledeću veliku grupu. Slučaj $b_1 = N$ i $b_2 = 1$ opisuje situaciju u realnom sistemu kada **jedan entitet prve klase može biti povezan sa jednim entitetom druge klase**, a svaki **entitet druge klase može biti povezan sa više entiteta prve klase**. Ova situacija se naziva odnos **više - prema - jedan** i označava se sa $N : 1$.

Zamislimo sada radnike i radna mesta. Svaki radnik može biti raspoređen na jedno radno mesto, ali na jednom radnom mestu može biti raspoređeno više radnika. To je tipičan N : 1 odnos.

U zavisnosti od vrednosti parametara $a_1$ i $a_2$, razlikuju se **četiri slučaja** ovog odnosa.

### Slučaj 1: $R(E_1(0, 1) : E_2(0, N))$ - Oba minimalna jednaka nuli

Kardinalitet tipa poveznika $R(E_1(0, 1) : E_2(0, N))$ opisuje odnos između dve realne klase entiteta u kojem **svaki entitet klase $E_1$ može biti u vezi sa najviše jednim entitetom klase $E_2$**, dok **svaki entitet klase $E_2$ može biti povezan sa više entiteta klase $E_1$**, ali ne mora svaki entitet klase $E_2$ biti povezan sa bar jednim entitetom klase $E_1$.

**Primer 2.27.** Posmatrajmo tipove entiteta *Radnik* i *Radno_Mesto* sa tipom poveznika *Raspoređen*.

Kardinalitet: $Raspore\text{đ}en(Radnik(0, 1) : Radno\_Mesto(0, N))$

Ovo opisuje realnu situaciju u kojoj svaki radnik **može** biti raspoređen na jedno radno mesto, ali **ne mora** svaki radnik biti raspoređen. Naravno, na jedno radno mesto može biti raspoređeno više radnika, a mogu postojati i radna mesta bez raspoređenih radnika.

| Radnik | Raspoređen | Radno_Mesto |
|--------|-----------|-------------|
| Ivo | (Ivo, Projektant) | Projektant |
| Ana | (Ana, Projektant) | Programer |
| Eva | (Eva, Sekretarica) | Sekretarica |
| Aco |  | Direktor |

Vidimo: Aco nije raspoređen nigde, a radno mesto Programer i Direktor nemaju nijednog raspoređenog radnika. To je OK za ovaj slučaj.

### Slučaj 2: $R(E_1(1, 1) : E_2(0, N))$ - Leva strana obavezna

Kardinalitet: $Raspore\text{đ}en(Radnik(1, 1) : Radno\_Mesto(0, N))$

Ovo ukazuje da svaki radnik **mora** biti raspoređen na jedno i samo jedno radno mesto i da ne može postojati neraspoređen radnik.

| Radnik | Raspoređen | Radno_Mesto |
|--------|-----------|-------------|
| Ivo | (Ivo, Projektant) | Projektant |
| Ana | (Ana, Projektant) | Programer |
| Eva | (Eva, Sekretarica) | Sekretarica |
| Aco | (Aco, Projektant) | Direktor |

Sada je svaki radnik raspoređen na tačno jedno radno mesto, ali radno mesto Programer i Direktor i dalje mogu biti prazni (jer je $a_1 = 0$, tj. minimalni kardinalitet na strani Radno_Mesto je 0).

### Slučaj 3: $R(E_1(0, 1) : E_2(1, N))$ - Desna strana obavezna

Kardinalitet: $Raspore\text{đ}en(Radnik(0, 1) : Radno\_Mesto(1, N))$

Ovde mogu postojati neraspoređeni radnici, ali **ne može postojati prazno radno mesto** - na koje nije raspoređen bar jedan radnik.

| Radnik | Raspoređen | Radno_Mesto |
|--------|-----------|-------------|
| Ivo | (Ivo, Projektant) | Projektant |
| Ana | (Ana, Projektant) | Programer |
| Eva | (Eva, Sekretarica) | Sekretarica |
| Aco | (Aco, Projektant) | Direktor |
| Pera | (Pera, Direktor) |  |
| Mira |  |  |

Mira nije raspoređena (to je OK jer $a_2 = 0$), ali svako radno mesto ima bar jednog radnika.

### Slučaj 4: $R(E_1(1, 1) : E_2(1, N))$ - Obe strane obavezne

Kardinalitet: $Raspore\text{đ}en(Radnik(1, 1) : Radno\_Mesto(1, N))$

Ovo je najstrože: **svaki radnik mora biti raspoređen** na jedno i samo jedno radno mesto, i **svako radno mesto mora imati** bar jednog raspoređenog radnika.

| Radnik | Raspoređen | Radno_Mesto |
|--------|-----------|-------------|
| Ivo | (Ivo, Programer) | Projektant |
| Ana | (Ana, Projektant) | Programer |
| Eva | (Eva, Sekretarica) | Sekretarica |
| Aco | (Aco, Projektant) | Direktor |
| Pera | (Pera, Direktor) |  |
| Mira | (Mira, Direktor) |  |

Svaki radnik ima tačno jedno radno mesto, i nijedno radno mesto nije prazno.

> [!TIP]
> Lak način da zapamtite N : 1: pitajte se "Ko može imati samo jednog?" - to je strana sa kardinalitetom 1. U našem primeru, radnik može biti na samo jednom radnom mestu (1), ali na radnom mestu može biti više radnika (N).

---

## 3. Strukture sa kardinalitetima grupe 1 : 1

### Šta znači 1 : 1?

Sada dolazimo do posebnog slučaja. Kada je $b_1 = 1$ i $b_2 = 1$, opisujemo situaciju u realnom sistemu kada **jedan entitet prve klase može biti povezan sa jednim entitetom druge klase, i jedan entitet druge klase sa jednim entitetom prve klase**. Ova situacija se naziva odnos **jedan - prema - jedan** i označava sa $1 : 1$.

Zamislimo osiguravajuće društvo. Svaki radnik može (ali ne mora) biti osiguranik tog društva, i svaki osiguranik može (ali ne mora) biti radnik. To je 1 : 1 odnos.

U zavisnosti od vrednosti $a_1$ i $a_2$, razlikujemo **tri slučaja**.

### Slučaj 1: $R(E_1(0, 1) : E_2(0, 1))$ - Obe strane opcione

Tip poveznika sa kardinalitetom $R(E_1(0, 1) : E_2(0, 1))$ opisuje odnos između klasa entiteta $E_1$ i $E_2$, gde **svaki entitet jedne klase može biti povezan sa najviše jednim entitetom druge klase**.

**Primer 2.28.** Posmatraju se tipovi entiteta *Radnik*, *Osiguranik* i tip poveznika *Je*.

Kardinalitet: $Je(Radnik(0, 1) : Osiguranik(0, 1))$

Ovo opisuje realni sistem gde radnik može, a ne mora biti osiguranik preduzeća u kojem radi, i gde osiguranik može biti radnik, ali ne mora svaki osiguranik biti radnik (jer osiguranici mogu biti i ljudi van posmatranog kolektiva).

| Radnik | Je | Osiguranik |
|--------|-----|-----------|
| Ivo | (Ivo, Polisa2) | Polisa1 |
| Ana | (Ana, Polisa1) | Polisa2 |
| Eva | (Eva, Polisa3) | Polisa3 |
| Aco |  | Polisa4 |

Aco nije osiguranik (dozvoljeno jer $a_2 = 0$), a Polisa4 ne pripada nijednom radniku (dozvoljeno jer $a_1 = 0$).

### Slučaj 2: $R(E_1(1, 1) : E_2(0, 1))$ - Jedna strana obavezna

Kardinalitet: $Je(Radnik(1, 1) : Osiguranik(0, 1))$

Ovo bi značilo da u posmatranom osiguravajućem društvu važi pravilo poslovanja prema kojem **svaki radnik mora biti osiguranik**, ali da osiguranici mogu biti i ljudi van posmatranog kolektiva.

| Radnik | Je | Osiguranik |
|--------|-----|-----------|
| Ivo | (Ivo, Polisa2) | Polisa1 |
| Ana | (Ana, Polisa1) | Polisa2 |
| Eva | (Eva, Polisa3) | Polisa3 |
|  |  | Polisa4 |

Svaki radnik ima polisu, ali Polisa4 i dalje može postojati bez radnika.

### Slučaj 3: $R(E_1(1, 1) : E_2(1, 1))$ - Obe strane obavezne

Kardinalitet: $Je(Radnik(1, 1) : Osiguranik(1, 1))$

Ovo opisuje situaciju kada je **svaki entitet jedne klase povezan sa jednim i samo jednim entitetom druge klase**, i ukazuje na njihovu **uzajamnu egzistencijalnu povezanost**.

| Radnik | Je | Osiguranik |
|--------|-----|-----------|
| Ivo | (Ivo, Polisa2) | Polisa1 |
| Ana | (Ana, Polisa1) | Polisa2 |
| Eva | (Eva, Polisa3) | Polisa3 |
| Aco | (Aco, Polisa4) | Polisa4 |

Ovde osiguravajuće društvo osigurava samo svoje radnike. Međutim, treba napomenuti da se u praksi retko srećemo sa ovim slučajem, ali kada se sretne, primena tipa poveznika sa kardinalitetom $R(E_1(1, 1) : E_2(1, 1))$ je neophodna za veran opis realnog sistema.

> [!WARNING]
> Studenti često mešaju 1:1 sa N:1 na ispitu. Razlika: kod 1:1, **obe** strane imaju maksimalni kardinalitet 1. Kod N:1, jedna strana ima maksimalni kardinalitet N (više od 1), a druga 1. Pitajte se: "Da li na drugoj strani može biti povezano VIŠE entiteta?" Ako da, to je N:1, ne 1:1.

---

## 4. Rekurzivne veze

### Kada entitet ima vezu sam sa sobom

Do sada smo gledali veze između dva različita tipa entiteta. Ali šta ako tip entiteta treba da ima vezu **sam sa sobom**? Rekurzivni tip poveznika predstavlja model relacije u jednom skupu - relacije koja **povezuje entitete jedne klase**. U ER strukturi, isti tip entiteta reprezentuje i prvu i drugu klasu realnih entiteta, jer jedna od tih klasa, po pravilu, predstavlja podskup druge.

Pri tome, entiteti posmatrane klase igraju **različite uloge** u svom odnosu. Bez obzira na prividnu neobičnost ove strukture, ona služi za modeliranje veoma čestih situacija u realnim sistemima. Kardinaliteti ovog tipa poveznika mogu uzimati sve moguće vrednosti.

### Primer: Ko kome rukovodi?

**Primer 2.29.** Posmatra se tip entiteta *Radnik* i rekurzivni tip poveznika *Rukovodi* sa kardinalitetom:

$$Radnik(podre\text{đ}eni)(0, 1) : Radnik(rukovodi)(1, N)$$

Semantika ove strukture je: jedan rukovodni radnik rukovodi sa najmanje jednim podređenim radnikom, i svaki radnik ima najviše jednog direktnog rukovodioca. Fraza "najviše jedan" ukazuje da mogu postojati i radnici koji nemaju pretpostavljenih, što, u najmanju ruku, važi za direktora.

| Radnik (levo) | Rukovodi | Radnik (desno) |
|--------------|----------|----------------|
| Ana | (Ana, Eva) | Ana |
| Eva | (Ana, Aco) | Eva |
| Aco | (Eva, Ivo) | Aco |
| Ivo |  | Ivo |

Ana rukovodi Evom i Acom. Eva rukovodi Ivom. Aco i Ivo nemaju podređene. Ana nema rukovodioca (ona je direktor).

### Primer: Sastavnica proizvoda

Putem rekurzivnog tipa entiteta gradi se i **model sastavnice**. Zamislimo tip entiteta *Proizvod* i tip poveznika *Sastavnica* sa kardinalitetom:

$$Proizvod(0, N) : Proizvod(0, M)$$

Pošto i sklopovi i delovi predstavljaju proizvode, pojave tipa entiteta *Proizvod* sadrže podatke o: proizvodima, sklopovima i delovima. Tip poveznika *Sastavnica* povezuje svaki proizvod sa njegovim direktnim komponentama.

| Proizvod (levo) | Sastavnica | Proizvod (desno) |
|-----------------|-----------|------------------|
| 101 | (101, Motor) | 101 |
| Y45 | (101, Karoserija) | Y45 |
| Motor | (Motor, Klip) | Motor |
| Karoserija | (Y45, Motor) | Karoserija |
| Klip | (Y45, Karoserija) | Klip |

Proizvod 101 se sastoji od Motora i Karoserije. Motor sadrži Klip. Y45 se takođe sastoji od Motora i Karoserije. Vidimo da se isti deo (Motor) može pojaviti u više proizvoda.

> [!NOTE]
> Rekurzivne veze su česte u praksi: hijerarhija zaposlenih (ko kome odgovara), sastavnice proizvoda (šta se od čega sastoji), organizacione strukture (koje odeljenje pripada kojem). Uvek obratite pažnju na **uloge** koje entiteti igraju u vezi.

---

## 5. Tip poveznika reda većeg od dva

### Kada dva tipa entiteta nisu dovoljni

Do sada smo gledali binarne veze - između dva tipa entiteta. Ali tip poveznika može da poveže i **više od dva tipa entiteta**. Kardinalitet tipa poveznika reda $n$ (gde je $n > 2$) se određuje putem postupka koji predstavlja uopštenje postupka za određivanje kardinaliteta tipa poveznika reda $n = 2$.

Postoje **dva moguća pristupa** za određivanje kardinaliteta:

**Prvi pristup:** Postupak se ponavlja $n$ puta, za svaki od povezanih tipova entiteta jedanput. U postupku se posmatra jedan poveznik $(e_1, e_2, ..., e_{n-1})$ reda $n - 1$, gde je $e_i \in E_i$, i skup entiteta $E_n$ čiji entiteti nisu uključeni u poveznik reda $n - 1$. Zatim se određuje kardinalitet preslikavanja:

$$R_{1,...,n-1}(E_n(a_n, b_n))$$

Pri tome se identifikuju mogući kardinaliteti podskupova skupa $E_n$ povezanih sa posmatranim poveznikom $(e_1, e_2, ..., e_{n-1})$.

**Drugi pristup:** Postupak se ponovo ponavlja $n$ puta, za svaki od povezanih tipova entiteta jedanput. Pri tome se analizira skup poveznika $P = \{(e_1, e_2, ..., e_n) \mid e_i \in E_i\}$ posmatranog tipa $i$, za proizvoljan entitet $e_i \in E_i$, utvrđuje se u koliko $n$-torki skupa $P$ se $e_i$ može minimalno i maksimalno javiti kao komponenta. Na taj način se određuje broj mogućih pojavljivanja proizvoljnog entiteta $e_i \in E_i$ u poveznicima skupa $P$.

### Primer sa studentima, nastavnicima i predmetima

**Primer 2.30.** Posmatraju se tipovi entiteta *Student*, *Nastavnik* i *Predmet*. Između entiteta odgovarajućih klasa u realnom sistemu važe sledeći odnosi:

1. Student $s$ sluša predmet $p$ kod najviše jednog nastavnika $n$.
2. Ako nastavnik $n$ izvodi predmet $p$, izvodi ga za više studenata, mada ne mora ni za jednog.
3. Student $s$, kod nastavnika $n$, može slušati više predmeta, ali ne mora ni jedan.
4. Postoje nastavnici koji ne predaju ni jedan predmet bilo kom studentu.
5. Postoje studenti koji ne slušaju ni jedan predmet kod bilo kog nastavnika.
6. Ne postoje predmeti, koje ne predaje ni jedan nastavnik bilo kom studentu.
7. Jedan nastavnik može predavati više predmeta za više studenata.

Prema **prvom pristupu**, za definisanje kardinaliteta tipa poveznika *Izvođenje_Nastave* reda 3 koji povezuje tipove entiteta *Student*, *Predmet* i *Nastavnik*, bitni su odnosi 1, 2 i 3. Navedeni odnosi ukazuju da tip poveznika *Izvođenje_Nastave* poseduje sledeće kardinalitete, redom:

$$R_{np}(Nastavnik(0, 1)), \text{ odnosno } ((s, p) : n = (0, 1))$$
$$R_{np}(Student(0, N)), \text{ odnosno } ((n, p) : s = (0, 1))$$
$$R_{sn}(Predmet(0, N)), \text{ odnosno } ((s, n) : p = (0, N))$$

Na osnovu ovih kardinaliteta nacrtan je ER dijagram.

Za definisanje kardinaliteta tipa poveznika *Izvođenje_Nastave* prema **drugom pristupu**, odnos 1 je nebitan, a bitni su svi ostali navedeni odnosi. Saglasno tim odnosima, nacrtan je drugi ER dijagram. Ilustracije radi, prema odnosu 7, jedan nastavnik se može javiti kao komponenta više poveznika, a prema odnosu 4, postoje nastavnici koji se ne javljaju ni jedanput kao komponenta poveznika.

Konkretna ekstenzija:

| Student | Izvođenje_Nastave | Nastavnik |
|---------|------------------|-----------|
| Ana | (Ana, Baze_Podataka, Pera) | Pera |
| Aco | (Ana, Matematika1, Milan) | Milan |
| Ivo | (Aco, Baze_Podataka, Pera) | Laza |
| Eva | (Ana, Fizika, Pera) | Draga |
|  | (Ivo, Fizika, Draga) |  |

| Predmet |
|---------|
| Matematika1 |
| Matematika2 |
| Baze_Podataka |
| Fizika |

Uporedujući ER dijagrame prema prvom i drugom pristupu, zapažaju se različiti kardinaliteti tipa poveznika *Izvođenje_Nastave*, mada je ekstenzija u oba slučaja ista. Te razlike potiču od činjenice da:
- **prvi pristup** identifikuje koliko je entiteta skupa $E_n$ povezano sa jednim poveznikom $(e_1, e_2, ..., e_{n-1})$
- **drugi pristup** identifikuje koliko puta se neki entitet skupa $E_n$ javlja kao komponenta u skupu poveznika $P$

> [!CAUTION]
> Na ispitu se može tražiti da odredite kardinalitet poveznika višeg reda. Pažljivo pročitajte uslove i utvrdite koji pristup se koristi. Dva pristupa mogu dati **različite kardinalitete** za isti tip poveznika, ali im je ekstenzija ista!

---

## 6. Slabi tip entiteta

### Kada entitet ne može da živi sam

Do sada smo radili sa "jakim" tipovima entiteta koji imaju svoj ključ i mogu samostalno da postoje. Ali šta sa entitetima koji **zavise od nekog drugog entiteta za svoju identifikaciju i egzistenciju**?

Kardinalitet tipa poveznika predstavlja jedan od primera eksplicitnih ograničenja koja se zadaju u modelu entiteta i poveznika. Često se, u ER dijagramima, zadaju samo maksimalne vrednosti kardinaliteta, tada se koristi poseban postupak zadavanja **egzistencijalne zavisnosti**, odnosno ograničenje tipa $R(E_1(a_2, b_2) : E_2(1, b_1))$, koje ukazuje da u modelu, na nivou ekstenzije, **za svako $e_2$ iz $E_2$ postoji bar jedno $e_1$ iz $E_1$** takvo da su $e_1$ i $e_2$ međusobno povezani relacijom $R$.

Taj poseban postupak zadavanja egzistencijalne zavisnosti rešava se uvođenjem pojma **slabog tipa entiteta** i posebnog načina označavanja takvih tipova entiteta.

### Kako prepoznajemo slab tip entiteta?

**Slabi tip entiteta** se dijagramski označava na sledeći način:
- Naziv slabog tipa entiteta se upisuje u **dvostruki pravougaonik**
- Veliko slovo **E** se navodi uz ograničenje za egzistencijalnu zavisnost
- Poteg koji povezuje geometrijsku sliku za slabi tip entiteta sa geometrijskom slikom za odgovarajući tip poveznika se orijentiše ka slabom tipu entiteta

Tip poveznika koji povezuje neki slabi tip entiteta naziva se **slabim tipom poveznika**. Slabi tip poveznika nema odgovarajuću relaciju.

Tipovi entiteta koji nisu slabi, odnosno tip entiteta i tip poveznika koji povezuje samo egzistencijalno nezavisne tipove entiteta, nazivaju se **regularnim**.

**Primer 2.31.** Na ER dijagramu su nacrtani tipovi entiteta *Radno_Mesto*, *Radnik* i tip poveznika *Raspoređen*. Tip entiteta *Radnik* je **slab**. Činjenica da je tip entiteta *Radnik* označen kao slabi tip entiteta, interpretira se na sledeći način: **ne može postojati radnik** (u posmatranoj organizaciji), **a da nije raspoređen na neko radno mesto**.

### Ključ i identifikaciona zavisnost

**Ključ tipa entiteta** predstavlja jedno od ograničenja, ali se to ograničenje ne mora definisati za svaki tip entiteta u modelu entiteta i poveznika. Tip entiteta koji **ne poseduje ključ** - takođe se naziva slabim, a putem takvog tipa entiteta se definiše ograničenje pod nazivom **identifikaciona zavisnost**. Entiteti takvog skupa se ne mogu identifikovati putem vrednosti nekog svog obeležja, već putem svojih **povezanosti sa entitetima nekih drugih skupova**.

Treba napomenuti da identifikaciona zavisnost automatski povlači za sobom i egzistencijalnu zavisnost, ali da egzistencijalno zavisni tip entiteta ne mora biti i identifikaciono zavisan.

Identifikaciono zavisni tip entiteta se u dijagramima predstavlja veoma slično kao egzistencijalno zavisni tip entiteta. Jedina je razlika da se umesto oznake $E$ navodi oznaka $ID$.

### Ekstenzija slabog tipa entiteta

**Ekstenzija slabog tipa entiteta** naziva se slabom relacijom entiteta. Tabelarni prikaz ekstenzije slabog tipa entiteta sadrži i obeležje $I$, čije vrednosti, zajedno sa vrednostima nekog podskupa $V$ obeležja slabog tipa entiteta, jednoznačno određuju pojave slabog tipa entiteta.

Pošto slabi tip entiteta nema ključ, vrednosti skupa obeležja $I \cup V$ u ekstenziji igraju ulogu vrednosti ključa.

Neka je $W$ slabi tip entiteta sa skupom obeležja $\{A_1, ..., A_w\}$, a $R$ jedini regularni tip entiteta sa kojim je $W$ povezan, tako da između njih postoji samo jedan slabi tip poveznika. Ako je $K$ ključ tipa entiteta $R$, tada za obeležje $I$, čije vrednosti identifikuju pojave slabog tipa entiteta $W$, važi:

$$K \subset I \text{ i } I \setminus K \subseteq \{A_1, ..., A_w\}$$

Neka su $R_1, ..., R_k$ regularni tipovi entiteta sa ključevima $K_1, ..., K_k$ respektivno, i neka je $W$ sa njima povezan bilo direktno ili posredstvom drugih slabih tipova entiteta. Neka je $I_i$ unija identifikacionih obeležja slabih tipova entiteta između $R_i$ i $W$, za $i = 1, ..., k$. ($I_i$ može biti i prazan skup). Tada važi:

$$\bigcup_{i=1}^{k} K_i I_i \subset I \text{ i } I \setminus \bigcup_{i=1}^{k} K_i I_i \subseteq \{A_1, ..., A_w\}$$

### Primer: Radnik i Dete

**Primer 2.32.** Na ER dijagramu su nacrtana dva tipa entiteta *Radnik* i *Dete* i tip poveznika *R_D*. Tip entiteta *Dete* je **identifikaciono zavisan**. Oznaka za identifikacionu zavisnost je upisana u geometrijsku sliku tipa poveznika *R_D*.

Radnik ima obeležja: MBR, IME, PRZ, GOD. Identifikacioni ključ ($I$) za tip entiteta Dete je $I = \{MBR, IMD\}$, gde je MBR matični broj radnika-roditelja, a IMD ime deteta.

Pojave slabog, identifikaciono zavisnog tipa entiteta *Dete* su određene su matičnim brojem radnika svog roditelja i svojim imenom.

Konkretna ekstenzija:

**Radnik:**

| MBR | IME | PRZ | GOD |
|-----|-----|-----|-----|
| 88 | Eva | Pap | 1950 |
| 50 | Ivo | Ban | 1950 |
| 01 | Ana | Ras | 1961 |
| 81 | Ana | Tot | 1963 |

**Dete:**

| MBR | IMD | GRD |
|-----|-----|-----|
| 88 | Goran | 1975 |
| 88 | Ivana | 1970 |
| 01 | Olga | 1972 |
| 50 | Ana | 1972 |

Torke slabe relacije entiteta *Dete* sadrže vrednosti obeležja MBR kao svoje komponente, tako da je $I = \{MBR, IMD\}$.

### Hijerarhija slabih tipova entiteta

**Primer 2.33.** Moguće je imati i hijerarhiju slabih tipova entiteta, koji opisuje strukturu dela radne organizacije sa regularnim tipom entiteta u korenu stabla. Konkretna odeljenja se identifikuju putem ključa tipa entiteta *Preduzeće*, rednog broja sektora u preduzeću i rednog broja odeljenja u sektoru. Konkretan sektor se identifikuje putem ključa tipa entiteta *Preduzeće* i rednog broja sektora u preduzeću.

> [!IMPORTANT]
> Identifikaciona zavisnost automatski povlači egzistencijalnu zavisnost, ali NE važi obratno! Entitet može egzistencijalno zavisiti od drugog (ne može postojati bez njega), a da se ipak sam identifikuje putem svog ključa. Na ispitu obratite pažnju na razliku između oznake $E$ (egzistencijalna zavisnost) i $ID$ (identifikaciona zavisnost).

---

## Pregled svih struktura

Da bismo sve lepo sumirali, evo kompaktnog pregleda:

| Grupa | Maksimalni kard. | Opis | Broj slučajeva |
|-------|------------------|------|----------------|
| M : N | oba > 1 | više-prema-više | 3 slučaja ($a_1, a_2$ kombinacije) |
| N : 1 | jedan N, jedan 1 | više-prema-jedan | 4 slučaja |
| 1 : 1 | oba = 1 | jedan-prema-jedan | 3 slučaja |
| Rekurzivna | bilo koji | entitet sa samim sobom | razne kombinacije |
| Red > 2 | bilo koji | 3+ tipa entiteta | dva pristupa za kardinalitet |
| Slabi entitet | specifično | egzist./identif. zavisnost | E ili ID |

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

P: Šta opisuje kardinalitet tipa poveznika $R(E_1(a_2, M) : E_2(a_1, N))$?

P: Šta znači oznaka M : N u kontekstu odnosa između dva tipa entiteta?

P: Šta znači kada su minimalni kardinaliteti $a_1 = 0$ i $a_2 = 0$ kod M : N odnosa?

P: Šta znači kada su minimalni kardinaliteti $a_1 = 1$ i $a_2 = 0$ kod M : N odnosa?

P: Šta znači kada su minimalni kardinaliteti $a_1 = 1$ i $a_2 = 1$ kod M : N odnosa?

P: Koliko slučajeva se razlikuje kod struktura sa kardinalitetima grupe M : N?

P: Šta opisuje odnos N : 1?

P: Koje vrednosti imaju $b_1$ i $b_2$ kod struktura grupe N : 1?

P: Koliko slučajeva se razlikuje kod struktura sa kardinalitetima grupe N : 1?

P: Šta opisuje kardinalitet $R(E_1(0, 1) : E_2(0, N))$?

P: Šta opisuje kardinalitet $R(E_1(1, 1) : E_2(0, N))$?

P: Šta opisuje kardinalitet $R(E_1(0, 1) : E_2(1, N))$?

P: Šta opisuje kardinalitet $R(E_1(1, 1) : E_2(1, N))$?

P: Šta opisuje odnos 1 : 1?

P: Koje vrednosti imaju $b_1$ i $b_2$ kod struktura grupe 1 : 1?

P: Koliko slučajeva se razlikuje kod struktura sa kardinalitetima grupe 1 : 1?

P: Šta opisuje kardinalitet $R(E_1(0, 1) : E_2(0, 1))$?

P: Šta opisuje kardinalitet $R(E_1(1, 1) : E_2(0, 1))$?

P: Šta opisuje kardinalitet $R(E_1(1, 1) : E_2(1, 1))$?

P: Šta ukazuje uzajamna egzistencijalna povezanost kod 1:1 odnosa?

P: Šta je rekurzivni tip poveznika?

P: Koje uloge igraju entiteti u rekurzivnoj vezi?

P: Na šta ukazuje kardinalitet $Radnik(podređeni)(0, 1) : Radnik(rukovodi)(1, N)$?

P: Šta je model sastavnice i kako se gradi putem rekurzivnog tipa entiteta?

P: Šta je tip poveznika reda većeg od dva?

P: Koji su dva moguća pristupa za određivanje kardinaliteta tipa poveznika reda $n > 2$?

P: Šta je formula za kardinalitet preslikavanja u prvom pristupu kod tipa poveznika reda $n > 2$?

P: Kako se formula $R_{1,...,n-1}(E_n(a_n, b_n))$ tumači?

P: U čemu je razlika između prvog i drugog pristupa za određivanje kardinaliteta?

P: Šta je egzistencijalna zavisnost?

P: Šta je slabi tip entiteta?

P: Kako se dijagramski označava slabi tip entiteta?

P: Šta je slabi tip poveznika?

P: Šta su regularni tipovi entiteta?

P: Šta je identifikaciona zavisnost?

P: Kako se dijagramski označava identifikaciono zavisni tip entiteta?

P: Da li identifikaciona zavisnost automatski povlači egzistencijalnu zavisnost?

P: Da li egzistencijalno zavisni tip entiteta mora biti i identifikaciono zavisan?

P: Šta je ključ tipa entiteta u kontekstu slabog tipa entiteta?

P: Šta je ekstenzija slabog tipa entiteta?

P: Šta predstavlja skup obeležja $I$ kod slabog tipa entiteta?

P: Šta važi za relaciju $K \subset I$ i $I \setminus K \subseteq \{A_1, ..., A_w\}$?

P: Šta važi za formulu $\bigcup_{i=1}^{k} K_i I_i \subset I$?

P: Šta je oznaka $E$ u ER dijagramu?

P: Šta je oznaka $ID$ u ER dijagramu?

P: Kako se orijentiše poteg kod slabog tipa entiteta?

P: Šta je hijerarhija slabih tipova entiteta?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite razliku između tri slučaja minimalnih kardinaliteta kod M : N odnosa i navedite konkretan primer za svaki slučaj.
**O:** Kod M : N odnosa, razlika leži u minimalnim kardinalitetima $a_1$ i $a_2$. Kada su oba 0, entiteti u obe klase ne moraju biti povezani. Kada je jedan 1, a drugi 0, entiteti jedne klase moraju biti povezani sa bar jednim entitetom druge klase (egzistencijalna zavisnost jedne strane). Kada su oba 1, obe strane su obavezne - svaki entitet mora biti povezan sa bar jednim entitetom druge klase. Na primeru radnika i projekata: (0,0) znači da mogu postojati neangažovani radnici i prazni projekti; (1,0) znači da svaki projekat mora imati bar jednog radnika; (1,1) znači da je svaki radnik na bar jednom projektu i svaki projekat ima bar jednog radnika.

**P:** Koja je suštinska razlika između odnosa N:1 i 1:1? Ilustrujte primerom.
**O:** Kod N:1 odnosa, entiteti jedne klase mogu biti povezani sa samo jednim entitetom druge klase, ali entiteti te druge klase mogu biti povezani sa više entiteta prve klase. Kod 1:1, obe strane su ograničene na najviše jednu vezu. Primer: odnos Radnik-Radno_Mesto je N:1 jer više radnika može biti na istom radnom mestu, ali svaki radnik je na najviše jednom. Odnos Radnik-Osiguranik (u osiguravajućem društvu) je 1:1 jer svaki radnik ima najviše jednu polisu i svaka polisa pripada najviše jednom radniku.

**P:** Šta je rekurzivni tip poveznika i zašto se koristi? Navedite dva različita primera iz prakse.
**O:** Rekurzivni tip poveznika je veza koja povezuje entitete jedne iste klase, gde isti tip entiteta igra dve različite uloge. Koristi se za modeliranje hijerarhija i struktura unutar jednog skupa. Primer 1: tip entiteta Radnik sa vezom Rukovodi, gde radnik može biti i podređeni i rukovodilac. Primer 2: tip entiteta Proizvod sa vezom Sastavnica, gde proizvod može biti i sklop i komponenta drugog proizvoda.

**P:** Objasnite razliku između dva pristupa za određivanje kardinaliteta tipa poveznika reda većeg od dva.
**O:** Prvi pristup posmatra jedan poveznik reda $n-1$ i utvrđuje koliko entiteta tipa $E_n$ može biti povezano sa tim konkretnim poveznikom. Drugi pristup posmatra ceo skup poveznika i utvrđuje koliko puta se entitet tipa $E_i$ može pojaviti kao komponenta u tom skupu. Oba pristupa daju istu ekstenziju, ali mogu rezultirati različitim vrednostima kardinaliteta jer posmatraju povezanost iz različitih uglova.

**P:** Objasnite razliku između egzistencijalne zavisnosti i identifikacione zavisnosti slabog tipa entiteta.
**O:** Egzistencijalna zavisnost (oznaka $E$) znači da entitet slabog tipa ne može postojati bez veze sa entitetom regularnog tipa. Identifikaciona zavisnost (oznaka $ID$) znači da se entitet slabog tipa ne može identifikovati samostalno putem vrednosti svojih obeležja, već koristi ključ regularnog tipa entiteta kao deo svoje identifikacije. Identifikaciona zavisnost automatski povlači egzistencijalnu, ali ne važi obratno.

**P:** Na primeru tipova entiteta Radnik (MBR, IME, PRZ, GOD) i Dete (IMD, GRD), objasnite kako se formira identifikacioni ključ slabog tipa entiteta.
**O:** Dete je identifikaciono zavisan tip entiteta jer se ne može identifikovati samo po svom imenu (IMD) - više radnika može imati dete istog imena. Identifikacioni ključ Deteta je $I = \{MBR, IMD\}$, gde MBR dolazi iz ključa regularnog tipa entiteta Radnik, a IMD je obeležje samog slabog tipa. Prema formuli $K \subset I$ i $I \setminus K \subseteq \{A_1, ..., A_w\}$, ključ roditelja $K = \{MBR\}$ je podskup od $I$, a preostalo obeležje $IMD$ pripada skupu obeležja tipa Dete.

**P:** Zašto se kod tipa kardinaliteta $R(E_1(1,1) : E_2(1,1))$ kaže da je to izuzetno strogo ograničenje i u kojim situacijama se ono koristi?
**O:** Kardinalitet $(1,1):(1,1)$ zahteva da svaki entitet jedne klase bude povezan sa tačno jednim entitetom druge klase i obratno, što znači da su obe klase uzajamno egzistencijalno uslovljene. Ovo je strogo jer ne dozvoljava nijedan nepovezan entitet ni sa jedne strane. U praksi se retko sreće, ali je neophodno kada realni sistem zahteva potpunu i obaveznu korespodenciju, na primer kada osiguravajuće društvo osigurava isključivo svoje radnike i svaki radnik mora biti osiguran.

**P:** U primeru sa tipom poveznika Izvođenje_Nastave reda 3, objasnite kardinalitet $R_{np}(Nastavnik(0, 1))$ i šta on znači u kontekstu realnog sistema.
**O:** Kardinalitet $R_{np}(Nastavnik(0, 1))$ znači da za dati par (student $s$, predmet $p$) postoji najviše jedan nastavnik $n$ koji tom studentu predaje taj predmet, ali ne mora postojati nijedan (minimalni kardinalitet 0). U realnom sistemu to odgovara pravilu da student sluša predmet kod najviše jednog nastavnika, ali postoje kombinacije student-predmet za koje još nije definisan nastavnik.
