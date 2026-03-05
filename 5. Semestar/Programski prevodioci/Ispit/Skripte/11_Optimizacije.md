# Optimizacije

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta su optimizacije?

Optimizacije su izvršavanje različitih transformacija međukoda i ciljnog koda u cilju poboljšanja iskorišćenja resursa:

- Ubrzavanje izvršavanja
- Smanjivanje memorijskih zahteva
- Smanjivanje veličine koda
- Smanjivanje pristupanja disku

Čest usputni cilj je smanjivanje redundanse - ukloniti ponavljanja i suvišne stvari. Ponavljanja mogu biti namerna (programeri ih svesno pišu) ili moraju postojati jer to uslovljava priroda jezika visokog nivoa (nizovi, klase, apstrakcije). Ciljevi optimizacija mogu biti u koliziji - na primer, ubrzavanje izvršavanja može povećati veličinu koda.

Mnogi se slažu da bi bolji termin bio "poboljšanja" umesto "optimizacija" koda.

## Klasifikacija optimizacija

### Po tome ko ih vrši

- **Optimizacije međukoda** - zadužen prevodilac
- **Optimizacije ciljnog koda** - zadužen prevodilac
- **Optimizacije izvornog koda i izvršavanja** - zaduženi programeri (ručno ili alatima)

### Po zavisnosti od mašine

- **Mašinski nezavisne** - transformacije koje mogu dovesti do značajnih poboljšanja bez obzira na ciljni jezik (eliminisanje redundanse, na primer). Iako se smatraju mašinski nezavisnim, savremeni prevodioci nekada koriste znanja o ciljnoj arhitekturi.
- **Mašinski zavisne** - optimizacije koje zavise od konkretnog skupa instrukcija, registara, adresiranja memorije ciljne arhitekture.

## Analiza i transformacija

Optimizacije se sastoje iz dve komponente: analize i transformacije koda. Transformacije su: izbaci naredbu, zameni, promeni argumente... Da bismo znali koje transformacije primeniti i da li su te transformacije ispravne, vrše se određene analize i formalna dokazivanja "korektnosti" takvih postupaka.

## Bazni blokovi

Bazni ili osnovni blok (basic block - BB) je najduža sekvenca instrukcija sa jednom tačkom ulaza i jednom tačkom izlaza. Prilikom izvršavanja ulazi se u BB preko njegove prve instrukcije, a izlazi se iz BB bez zaustavljanja ili grananja osim u poslednjoj instrukciji.

Ključne osobine:

- Nema ulaska u BB osim na početku BB
- Nema izlaska iz BB osim na kraju BB
- BB ne sadrži skokove (grananje ili zaustavljanje) - osim eventualno u poslednjoj instrukciji
- Tok izvršavanja teče od prve do poslednje instrukcije bez zaustavljanja
- Postoji jedan početni BB
- Čvorovi sa return su završni

### Algoritam za određivanje baznih blokova

1. Prva instrukcija je početak bloka
2. Svaka instrukcija koja je cilj nekog skoka je početak bloka
3. Svaka instrukcija nakon skoka je početak bloka

### Primer

```
s = 0              -- BB1 (pravilo 1: prva instrukcija)
i = 0
L1: if i > 5 goto L2  -- BB2 (pravilo 2: cilj goto L1)
s = s + i           -- BB3 (pravilo 3: instrukcija nakon uslovnog skoka)
i = i + 1
goto L1
L2: ...             -- BB4 (pravilo 2: cilj goto L2)
```

### Složeniji primer

```
i = 1               -- BB1 (1)
L1: j = 1           -- BB2 (2: cilj goto L1)
L2: t1 = 10 * i     -- BB3 (2: cilj goto L2)
t2 = t1 + j
t3 = 4 * t2
t4 = t3 - 44
a[t4] = 0
j = j + 1
if j <= 10 goto L2
i = i + 1            -- BB4 (3: posle uslovnog skoka)
if i <= 10 goto L1
i = 1                -- BB5 (3: posle uslovnog skoka)
L3: t5 = i - 1       -- BB6 (2: cilj goto L3)
t6 = 44 * t5
a[t6] = 1
i = i + 1
if i <= 10 goto L3
```

Ovaj kod inicijalizuje 10x10 matricu na nule, a zatim dijagonalu postavlja na jedinice.

## Graf kontrole toka (CFG)

Control Flow Graph predstavlja još jednu međureprezentaciju. Čvorovi su bazni blokovi, a grane pokazuju moguće tokove izvršavanja. CFG se ne koristi isključivo za optimizaciju već i za druge aktivnosti (na primer, alokacija registara).

Zadaci koji se rešavaju pomoću CFG-a:

- Pronaći i analizirati ugnježdene petlje
- Utvrditi koja i kakva izračunavanja se vrše u petljama
- Utvrditi koji kod se često koristi
- Utvrditi koji kod je nedostižan

## Nivoi optimizacija

### Lokalne optimizacije

Primenjuju se u jednom baznom bloku. Najjednostavnije su, troši se malo resursa, algoritmi su jednostavni. Male promene, ali slaganjem više optimizacija jedne za drugom može se značajno poboljšati kod.

### Globalne (intraproceduralne) optimizacije

Posmatra se čitava funkcija, svi bazni blokovi. Primenjuju se iste optimizacije kao lokalne plus nove. Kod već spomenutih optimizacija pojavljuju se određeni problemi - na primer, kod propagacije kopije ili zajedničkog podizraza mora se obratiti pažnja na sve moguće putanje izvršavanja, uključujući putanje kroz petlje i grananja.

Izvršava se globalna analiza toka podataka (global dataflow analysis). Analiza se vrši nad grafom kontrole toka (CFG) - informacije se propagiraju duž ivica grafa, a rezultat se dobija iterativno do stabilnog stanja (fiksne tačke). Svakom čvoru (BB) pridružuju se ulazne i izlazne informacije, koje zavise od prethodnih čvorova. Na spajanjima putanja vrši se kombinovanje informacija. Postupak se ponavlja dok se rezultati ne menjaju.

### Interproceduralne optimizacije

Optimizacije na nivou celog programa (ili makar više funkcija). Najkomplikovanije i najskuplje, ali daju dobre rezultate. Zahtevaju informacije koje prelaze granice jedne funkcije, moraju uzeti u obzir sve moguće pozive i kontekste, i često se oslanjaju na aproksimacije.

## Lokalne optimizacije - tehnike

### Algebarske transformacije

Promena operacija, eliminisanje ili pojednostavljenje zasnovano na algebarskim identitetima:

```
x := x + 0       ->  (izbaci, nema efekta)
y := y * 1        ->  (izbaci, nema efekta)
x := x * 0        ->  x := 0
y := y ** 2        ->  y := y * y     (ako stepenovanje nije ugradjena instrukcija)
x := x * 8        ->  x := x << 3    (strength reduction - zamena skuplje
                                        operacije jeftinijom)
y := y * 2        ->  y := y + y     ->  y := y << 1
```

### Slaganje konstanti (constant folding)

Operacije koje uključuju samo konstante mogu se izračunati tokom prevođenja. Zamena izraza sa konstantama njihovim izračunatim vrednostima.

```
x := 3 + 2        ->  x := 5
```

### Eliminacija mrtvog koda (dead code elimination)

Kod koji se izvršava ali ne utiče na ostatak koda. Uglavnom nastaje kao posledica prevođenja i/ili nakon već izvršenih optimizacija. Često su to operacije dodele (move).

```
a := x + y              a := x + y
b := 3 + x              b := 3 + x
c := a              ->
d := b + a              d := b + a
```

Ako se `c` ne koristi u nastavku, odgovarajuća naredba se može ukloniti. Napomena: eliminacija mrtvog koda može biti i nepoželjna iz bezbednosnih razloga (security).

### Propagacija kopije (copy propagation)

Izbegavaju se promenljive koje samo čuvaju vrednosti drugih promenljivih. Korisno za naredne optimizacije.

```
a := x + y              a := x + y
b := 3 + x              b := 3 + x
c := a              ->
d := b + c              d := b + a
```

### Propagacija konstante (constant propagation)

Izbegavaju se promenljive koje čuvaju konstantne vrednosti.

```
a := x + y              a := x + y
b := 3 + x              b := 3 + x
c := 5              ->
d := b + c              d := b + 5
```

### Eliminacija zajedničkog podizraza (common subexpression elimination)

Izbegava se ponavljanje istog izračunavanja.

```
y := x * 2          ->  y := x * 2
return x * 2             return y

x := y + z          ->  x := y + z
...                      ...
m := y + z               m := x       (uz pretpostavku da se x, y, z
                                        nisu menjali izmedju)
```

### SSA oblik (Static Single Assignment)

Optimizacije su često jednostavnije ako je IR u SSA obliku. To je IR gde se jedna promenljiva pojavljuje samo jednom sa leve strane - nema dodela, postoji samo inicijalizacija. Kasnije dodele predstavljaju nove verzije promenljive.

```
Obican oblik:         SSA oblik:
y := 1                y := 1
y := 2                x := 2
x := y                z := x
```

Eliminiše se potreba za praćenjem promena. Možemo imati beskonačno promenljivih/registara (formiramo međukod). Komplikovanija realizacija, ali algoritmi za optimizacije mogu biti jednostavniji, efikasniji, nekad čak i jedino mogući ako je kod u ovom obliku.

## Kompletni primer primene lokalnih optimizacija

Polazni kod:

```
a := x ** 2
b := 3
c := x
d := c * c
e := b * 2
f := a + d
g := e * f
```

**Korak 1 - algebarske transformacije:**

```
a := x * x        (x**2 -> x*x)
b := 3
c := x
d := c * c
e := b << 1       (b*2 -> b<<1)
f := a + d
g := e * f
```

**Korak 2 - propagacije (kopije i konstante):**

```
a := x * x
b := 3
c := x
d := x * x        (c -> x)
e := 3 << 1       (b -> 3)
f := a + d
g := e * f
```

**Korak 3 - slaganje konstanti:**

```
a := x * x
b := 3
c := x
d := x * x
e := 6             (3 << 1 = 6)
f := a + d
g := e * f
```

**Korak 4 - eliminacija zajedničkog podizraza:**

```
a := x * x
b := 3
c := x
d := a             (x*x vec izracunato kao a)
e := 6
f := a + d
g := e * f
```

**Korak 5 - propagacije:**

```
a := x * x
b := 3
c := x
d := a
e := 6
f := a + a         (d -> a)
g := 6 * f         (e -> 6)
```

**Korak 6 - eliminacija mrtvog koda** (uz pretpostavku da se b, c, d, e ne koriste u nastavku):

```
a := x * x
f := a + a
g := 6 * f
```

Od 7 instrukcija ostale su 3.

### Primer 2

```
a := 1
b := 3
c := a + x
d := a * 3
e := b * 3
f := a + b
g := e - f
```

Primenom svih optimizacija (propagacija konstanti, slaganje, mrtav kod):

```
c := 1 + x
g := 5
```

(uz pretpostavku da se samo c, g, x koriste u nastavku)

## Važne napomene o optimizacijama

- Svaka optimizacija može biti i vrlo malo poboljšanje
- Često se dopunjuju - nakon primene jedne optimizacije omogućava se primena naredne
- Proces se često ponavlja - sve dok postoji mogućnost dalje optimizacije, ili do određenog trenutka radi ograničavanja vremena prevođenja
- Optimizacije se često primenjuju kao sekvenca prolaza (passes). Redosled može značajno uticati na krajnji rezultat
- Neke klasične lokalne optimizacije danas imaju manji efekat izolovano, ali su i dalje važne kao deo lanca optimizacija

## Nedostupan kod (unreachable code elimination)

Tok izvršavanja nikad ne stiže do određenog dela koda.

```
return x + y
z := x * y       -- nikad se ne izvrsava
...
```

Ako BB nema ulaz, ceo BB je nedostižan i može se ukloniti. Ne znači da je greška programera - često se pojavljuje nakon već izvršenih optimizacija, ili može biti posledica defanzivnog programiranja.

## Optimizacija petlji

Petlje su veoma česte konstrukcije u programima, neretko ugnježdene. Program puno vremena provodi u petljama, pa optimizacije petlji mogu biti vrlo značajne. Optimizuješ petlje - optimizovao si program.

### Loop-invariant code motion

Pomeranje koda koji se ne menja u petlji izvan petlje:

```
while (i <= length - 1)    ->    t = length - 1
    ...                          while (i <= t)
                                     ...
```

Pretpostavka je da je `length` nepromenljiv u telu petlje.

### Ostale optimizacije petlji

- **Loop inversion** - pretvaranje while u if + do/while (eliminacija jednog skoka po iteraciji)
- **Induction variables** - zamena induktivnih promenljivih jednostavnijim izrazima
- **Unrolling** - odmotavanje petlje (smanjuje overhead kontrole petlje)
- **Spajanje/razdvajanje petlji** - spajanje 2 petlje ili razdvajanje jedne na više (cache-friendly)
- **Auto-vectorization** - SIMD (single instruction multiple data) - obrada više podataka jednom instrukcijom

S obzirom da broj ponavljanja nije uvek poznat, dokazivanje prednosti pa čak ni valjanosti transformacija nije intuitivno.

## Interproceduralne optimizacije - pristupi

### Inline funkcije

Svaki poziv funkcije se zameni celom funkcijom uz odgovarajuće izmene za argumente i povratne vrednosti. Zatim se vrše globalne (intraproceduralne) optimizacije nad proširenim kodom.

Problemi: funkcije mogu biti nepoznate (pokazivač na funkciju), rekurzija. Inline može povećati veličinu koda (code bloat). Odluka o inline-ovanju je često heuristička. Inline nije optimizacija sama po sebi već pristup koji omogućava druge optimizacije.

### Grafovi poziva

Čvorovi su funkcije (F) i pozivi (CS - call site) koji odgovaraju svakom pozivu neke funkcije. Grana postoji ako u jednom pozivnom mestu CS postoji poziv funkcije F. Proširivanje analize korišćenjem ovog grafa i posmatranjem određenih konteksta za vrednosti. Algoritmi i analize se koriste i za druge stvari, ne nužno samo za prevođenje - na primer, uočavanje grešaka i sigurnosnih propusta u kodu.

## Optimizacije ciljnog koda

Mnoge navedene optimizacije se mogu primeniti i nad završnim asemblerskim kodom. Neke optimizacije su moguće tek nakon izbora instrukcija, jer ciljni kod omogućava uvid u konkretne registre, adresiranje memorije i specifične instrukcije arhitekture.

### Peephole optimizacije

Parcijalna optimizacija, "poslednja odbrana". Posmatraju se kratke sekvence uzastopnih naredbi i zamenjuju kraćim i bržim sekvencama. Sekvenca se posmatra kroz zamišljeni prorez (peephole) koji se pomera od početka ka kraju programa. Traže se pojave unapred zadatih slučajeva.

Tipični slučajevi:

**Suvišna poređenja** - ista poređenja, a između njih nije bilo promene status registra:

```
CMPU a, b
JEQ @false0
CMPU a, b          -- suvišno, izbaciti
JLEU @false1
```

**Suvišno zauzimanje registra** - registar se puni istom vrednošću, a u međuvremenu nije bilo izmene:

```
MOV $7, %1
ADDU %0, %1, %2
MOV $7, %1          -- suvišno, izbaciti
```

**Suvišno pisanje i čitanje** - uzastopno store i load iz istog registra i iste memorijske lokacije:

```
MOV %0, a
MOV a, %0            -- suvišno, izbaciti
```

**Nedostupne naredbe** - naredbe koje slede iza skoka, a nisu cilj nekog drugog skoka:

```
JEQ labela1
JNE labela2
MOV $12, %0          -- nedostupno, izbaciti
labela1:
...
```

**Skok na skok** - naredba skoka čiji je cilj naredba bezuslovnog skoka:

```
JEQ labela1          ->  JEQ labela2
...
labela1:
JMP labela2
```

## Međusobni uticaj optimizacija

Mnoge optimizacije su zapravo deo procesa i imaju međusobni uticaj sa procesima izbora instrukcija i alokacije registara. Važna pitanja:

- Da li prvo birati instrukcije pa alocirati registre ili obrnuto? Kada raditi optimizacije?
- Kako iskoristiti mogućnosti za paralelizaciju?
- Ako se izbor instrukcija vrši na nivou BB, često su male mogućnosti za paralelizaciju - treba nam šira analiza.
- Kako rezultati ostalih aktivnosti utiču na paralelizaciju? Na primer, smanjimo broj potrebnih registara u određenom delu, ali time izgubimo mogućnost paralelizacije tog dela koda.
- Ne postoji univerzalno optimalan redosled faza. Savremeni prevodioci koriste heuristike i iterativne pipeline-ove.

Koje optimizacije implementirati? Cilj je dobiti maksimum za minimalnu cenu, uzimajući u obzir kompleksnost implementacije i vreme kompajliranja. Odgovor je heuristika.

## GCC nivoi optimizacije

GCC podržava opcije za izvršavanje optimizacija: optimization levels, optimization flags i parametri (plus ciljna arhitektura).

### Nivoi

**-O0** (podrazumevano) - vreme prevođenja najbrže, debug omogućen u potpunosti. Kod je čitljiv i direktno mapiran na izvorni program. Česti pristupi memoriji, korišćenje steka umesto registara, dodatne instrukcije za kontrolu petlje.

**-O1** - cilj smanjiti veličinu koda i vreme izvršavanja, bez zahtevnih optimizacija. Uključuje: dead code elimination, constant propagation, move loop invariants, i druge.

**-O2** - dalje povećava performanse, ali i vreme prevođenja. Sve sa -O1 plus dodatne: common subexpression elimination after loops, peephole2, caller-saves, code hoisting, crossjumping...

**-O3** - dalje povećava performanse. Sve sa -O2 plus dodatne: loop interchange, loop unroll-and-jam, peel loops, ipa-cp-clone... Uključuje i auto-vektorizaciju (SIMD instrukcije).

**-Ofast** - sve sa -O3 plus dodatne, može prekršiti standarde jezika radi brzine.

**-Os** - cilj je smanjiti veličinu koda, ne povećavati brzinu izvršavanja. Pogodno za embedded sisteme i ograničene platforme.

**-Oz** - dalje smanjivanje veličine koda.

**-Og** - za debug, postoje neke optimizacije (-O1), ali debug je ispravan. Favorizuje debug mogućnosti.

### Primeri flag-ova

```
-fdce                       Dead code elimination na RTL nivou (-O1+)
-ftree-dce                  Dead code elimination na tree nivou (-O1+)
-frerun-cse-after-loop      CSE posle optimizacija petlji (-O2+)
-fpeephole / -fpeephole2    Peephole optimizacije (-O0 / -O2+)
-ftree-loop-distribution    Razdvajanje petlji (-O3)
```

### Primer: loop distribution (-O3)

```fortran
DO I = 1, N               DO I = 1, N
    A(I) = B(I) + C           A(I) = B(I) + C
    D(I) = E(I) * F  ->   ENDDO
ENDDO                      DO I = 1, N
                               D(I) = E(I) * F
                           ENDDO
```

Razdvajanje može poboljšati cache performanse i omogućiti dalju vektorizaciju.

### Parametri

GCC ima parametre za fino podešavanje, na primer:

- `max-inline-insns-single` - maksimalan broj instrukcija u funkciji za inline
- `max-inline-recursive-depth` - maksimalna dubina rekurzije za inline

### Praktično poređenje: ista funkcija na različitim nivoima

Za funkciju koja sumira elemente niza:

```c
int testFunction(int* input, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += input[i];
    }
    return sum;
}
```

**-O0**: koristi stek za sve promenljive, česti pristupi memoriji, dodatne instrukcije za indeksiranje - oko 20 instrukcija u petlji.

**-O1**: koristi registre umesto steka, eliminisane suvišne instrukcije, pointer aritmetika umesto indeksiranja - oko 10 instrukcija u petlji.

**-O2**: dodatne optimizacije, eliminisan epilog funkcije, korišćenje `xorl %eax, %eax` umesto `movl $0, %eax` za nuliranje - kompaktniji i brži kod.

**-O3**: vektorizacija pomoću SIMD registara i instrukcija (`pxor`, `movdqu`, `paddd`, `psrldq`). Obrađuje 4 elementa odjednom. Optimizuje za propusnost (što više podataka odjednom), ne nužno za latenciju (odziv). Duži kod ali brži za velike nizove.

**-Os**: kompaktan kod, slično kao -O1 ali sa naglaskom na veličinu. Pogodno za embedded sisteme.

**-Og**: slično kao -Os, favorizuje debug mogućnosti.

## Optimizacije izvornog koda i izvršavanja

Sa aspekta programera, u toku razvoja i nakon prevođenja. Podrazumeva određene analize:

### Statička analiza

Analiza koda bez izvršavanja programa. Mahom kvalitativna analiza:

- Coding standardi i usklađenost sa preporukama
- Detekcija paterna i sumnjivog koda
- Potencijalni runtime problemi
- Vizualizacije

Može otkriti greške koje se retko ili nikad ne manifestuju u testovima.

### Dinamička analiza

Analiza tokom izvršavanja programa. Mahom kvantitativna analiza:

- Brzina izvršavanja
- Korišćenje memorije i drugih resursa
- Code coverage (koliko je pokriveno testovima)
- Analiza sigurnosti (traženje propusta)
- Detekcija memory leak-a

Zavisi od konkretnih ulaza.

### Profajler (Profiler)

Alat koji obavlja analizu performansi. Prikuplja podatke prilikom izvršavanja - na primer, meri broj poziva funkcija i trajanje svakog poziva.

- **Trace** - niz zabeleženih događaja
- **Profile** - statistički obrađeni rezultati analize

Različite tehnike za dobijanje podataka: korišćenje prekida, ubacivanje koda u sistemske pozive (hook), modifikacija izvršnog oblika programa.

### GNU profiler (gprof)

```bash
gcc -g -pg -o program program.c
./program                # generise gmon.out
gprof program            # prikaz rezultata
```

Gprof prikazuje:

- **Flat profile** - ukupno vreme izvršavanja svake funkcije
- **Call graph** - vreme izvršavanja funkcija zajedno sa svim funkcijama koje je ona pozivala
- Broj izvršavanja svake linije koda

Kolone u rezultatima: `% time` (procenat ukupnog vremena provedenog u funkciji), `cumulative seconds` (kumulativno vreme), `self seconds` (vreme samo u funkciji), `calls` (broj poziva), `self ms/calls` (prosečno vreme po pozivu), `total ms/calls` (prosečno vreme uključujući pozvane funkcije), `name` (ime funkcije).

Najčešće usko grlo nije nužno funkcija sa najvećim ukupnim vremenom, već ona koja se često poziva.