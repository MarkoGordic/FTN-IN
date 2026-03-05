# Formalni jezici i automati

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Motivacija: od prirodnog do formalnog jezika

Prirodni jezik ima sledeću strukturu: postoji skup slova (azbuka, alfabet), skup reči građenih nad azbukom, i skup rečenica građenih nad skupom reči. Reči prate pravila leksike, rečenice prate pravila sintakse, a značenje rečenica prate pravila semantike. Na primer:

- "Danas pada kiša." - ispravno
- "Danas će padati kiša." - ispravno
- "Je danas oni padala." - sintaksno neispravno
- "Juče će padati kiša." - semantički upitno

Rečnik je skup reči koje se nalaze u jeziku, a skup pravila za prirodni jezik praktično predstavlja pravila konverzacije. Pravila prirodnih jezika nisu jednostavna i teže se formalno opisuju.

Formalni jezici nam omogućavaju da na formalan način opisujemo jezike i istražujemo njihove osobine, i da utvrdimo da li su neki jezici posebno zanimljivi ili korisni. Dva osnovna alata za rad sa formalnim jezicima su gramatike i automati.

## Osnovni pojmovi

**Azbuka** (alfabet) Sigma - konačan, neprazan skup simbola. Važno: azbuka ne mora biti sačinjena od "slova" u klasičnom smislu. Simboli mogu biti karakteri, tokeni, ili bilo šta drugo.

**Reč** (string) w - konačan niz simbola iz azbuke.

**Prazna reč** epsilon (ili lambda) - reč dužine 0.

Postoji analogija sa kompajlerima: na jednom nivou karakteri formiraju reči (leksička analiza), a na drugom nivou reči (tokeni) formiraju rečenice (sintaksna analiza).

### Stepen alfabeta

N-ti stepen alfabeta je skup svih reči dužine n. Za alfabet Sigma = {0, 1}:

```
Sigma   = {0, 1}         -- simboli

Sigma^0 = {epsilon}      -- nije prazan skup! Sadrzi praznu rec
Sigma^1 = {0, 1}         -- reci duzine 1
Sigma^2 = {00, 01, 10, 11}
Sigma^3 = {000, 001, 010, 011, 100, 101, 110, 111}
...
```

Važno pitanje: u čemu je razlika između alfabeta i prvog stepena alfabeta? Alfabet je skup simbola, a prvi stepen je skup reči dužine 1. Formalno su to različiti objekti, ali praktično imaju iste elemente. Nulti stepen sadrži samo praznu reč - nije prazan skup.

### Klinijeva zvezda i pozitivno zatvorenje

Klinijeva zvezda (Kleene star) je skup svih reči nad alfabetom, uključujući praznu reč:

```
Sigma* = Sigma^0 U Sigma^1 U Sigma^2 ... = U(i>=0) Sigma^i
```

Pozitivno zatvorenje isključuje praznu reč:

```
Sigma+ = Sigma^1 U Sigma^2 ... = U(i>=1) Sigma^i = Sigma* \ {epsilon}
```

Za Sigma = {0, 1}:

```
Sigma* = {epsilon, 0, 1, 00, 01, 10, 11, ..., 1100101, ...}
Sigma+ = {0, 1, 00, 01, 10, 11, ..., 1100101, ...}
```

Obratiti pažnju: reči su konačni nizovi simbola, ali skup svih reči (Sigma*) je beskonačan.

## Definicija jezika

Neka je Sigma neka azbuka. Svaki podskup L skupa Sigma* zovemo jezik nad Sigma.

```
L je podskup od Sigma*
```

Primetiti:

- Ne spominju se nikakva pravila ili gramatike u definiciji.
- Jezik je definisan kao rečnik (skup reči), a ne preko nekih svojih pravila.
- Nad jednom azbukom možemo imati više jezika. Koliko? Koliko podskupova ima Sigma*? Beskonačno mnogo (partitivni skup beskonačnog skupa).

### Primeri jezika

Za Sigma = {0, 1}:

```
L1 = prazan skup                            -- prazan jezik
L2 = {epsilon}                               -- jezik sa samo praznom reci
L3 = Sigma*                                  -- svi moguci stringovi
L4 = {0}                                     -- samo jedna rec
L5 = {epsilon, 101, 111111}                  -- konacno mnogo reci
L6 = {1, 11, 111, 1111, ...}                -- beskonacno, samo jedinice
L7 = {01, 0001, 0101, 01111001, ...}         -- beskonacno
```

Za Sigma = {a, b}:

```
L1 = {aaa, ab, baba}                         -- konacan jezik
L2 = {a, aa, aaa, aaaa, ...}                 -- samo slova a, 1 ili vise
L3 = {a, b, aabbb, aaab, aabb, ...}          -- ?
L4 = {epsilon, a, b, aabbb, aaab, aabb, ...} -- ?
L5 = {epsilon, abba, bbba, baaab, ab, ...}   -- ?
```

Konačan skup reči možemo jednostavno zapisati navođenjem svih reči. Ali za beskonačan skup reči - da li možda postoji neko pravilo? Da li se nekako formalno mogu opisati takvi jezici?

### Operacije nad jezicima

Nad jezicima se uvodi operacija konkatenacije - spajanje dva jezika gde novi jezik sadrži sve reči nastale konkatenacijom reči iz pojedinačnih jezika.

Intuitivni primer:

```
temp = 5
{jezik naredbe dodele} = {jezik identifikatora}{jezik dodele}{jezik literala}
```

Gde će se ovde negde pojaviti nešto što liči na + ili *? U ponavljanju identifikatora (identifikator je slovo iza koga sledi 0 ili više slova/cifara) i u definiciji literala.

## Gramatike i automati - dva pristupa

**Gramatike** - pravila na osnovu kojih se grade reči/stringovi. Gramatika je mehanizam za generisanje. Generiše sve reči koje pripadaju jeziku.

**Automati** - prihvataju ili ne prihvataju određenu reč kao reč nekog jezika. Automat je mehanizam za prepoznavanje. Zapravo su apstraktne mašine, matematičke konstrukcije, modeli računanja, ali imaju zgodnu vizuelnu reprezentaciju.

## Gramatike

### Formalna definicija

Gramatika je uređena četvorka G = (Sigma, N, P, S) gde je:

- **Sigma** - skup terminala (simbola)
- **N** - skup neterminala (pojmova)
- **P** - skup pravila izvođenja (produkcija)
- **S** - početni pojam

Ograničenja: Sigma, N, P su neprazni, konačni skupovi. Sigma i N su disjunktni (Sigma presek N = prazan skup). P je skup pravila u obliku (Sigma U N)* N (Sigma U N)* -> (Sigma U N)* - sa leve strane mora postojati bar jedan neterminal.

### Primeri gramatika

**Primer 1** - regularna gramatika:

```
S0 -> aS1
S1 -> aS1
S1 -> bS1
S1 -> epsilon
```

Ova gramatika generiše jezik: reči koje počinju sa `a` i zatim imaju proizvoljan broj `a` i `b` simbola (uključujući nulu).

**Primer 2** - kontekstno slobodna gramatika:

```
S -> aSa
S -> bSb
S -> a
S -> b
S -> epsilon
```

Ova gramatika generiše palindrome nad azbukom {a, b}.

### Šta pravila praktično omogućavaju?

- Pravila pre svega ukazuju na konkatenaciju (redosled).
- Više pravila za isti pojam praktično omogućava uniju (alternative).
- Često su rekurzivna, čime se praktično omogućava ponavljanje.
- Pravila bez rekurzije praktično omogućavaju zaustavljanje rekurzije.
- Prazna reč praktično i između ostalog omogućava zaustavljanje rekurzije/ponavljanja.

## Deterministički konačni automat (DKA/DFA)

### Formalna definicija

Deterministički konačni automat je uređena petorka A = (S, Sigma, sigma, s0, F) gde je:

- **S** - skup stanja
- **Sigma** - alfabet (ulazni simboli)
- **sigma** - funkcija prelaza, sigma: S x Sigma -> S
- **s0** - inicijalno stanje
- **F** - skup završnih (finalnih) stanja

Ključno: funkcija prelaza je totalna funkcija koja za svako stanje i svaki ulazni simbol vraća tačno jedno stanje. Zato je automat deterministički.

### Primer DKA

Automat koji prepoznaje reči nad azbukom {a, b} koje počinju sa `a`:

```
Stanja: S = {s0, s1}
Alfabet: Sigma = {a, b}
Inicijalno stanje: s0
Završna stanja: F = {s1}

Funkcija prelaza:
sigma(s0, a) = s1
sigma(s1, a) = s1
sigma(s1, b) = s1
sigma(s0, b) = ?      -- nema prelaz, greška
```

Vizuelno: s0 --a--> ((s1)) sa petljom a,b na s1 (dvostruki krug označava finalno stanje, strelica ka s0 označava inicijalno stanje).

Rad automata: čita se ulazni string simbol po simbol, od inicijalnog stanja se prate prelazi. Na kraju se proverava: da li za određenu reč (string) završavamo u finalnom stanju?

Ne mogu se svi formalni jezici predstaviti konačnim automatima. Regularni jezici se mogu predstaviti konačnim automatima. Postoje i druge klase jezika.

### Primeri: koji jezik prihvata automat?

**Primer 1:** Automat nad azbukom {0, 1} koji prihvata reči koje imaju podstring `01`.

**Primer 2:** Automat nad azbukom {0, 1} koji prihvata reči koje imaju podstring `000`.

**Primer 3:** Automat nad azbukom {0, 1} koji prihvata reči sa neparnim brojem simbola `1`.

### Kombinovanje automata

Od postojećih automata možemo praviti nove koji proveravaju složenije uslove:

- da li ima neparan broj `1` **i** ima podniz `000`
- da li ima neparan broj `1` **ili** ima podniz `000`
- da li ima neparan broj `1` **i nema** podniz `000`
- da li ima paran broj `1` **i** ima podniz `000`

Ključno pitanje: da li imamo sistematičan način da kombinujemo automate za bilo koje jezike? Odgovor je da. Ne možemo ih nadovezati (jer se ulaz čita simbol po simbol), ali možemo ih pustiti paralelno da se izvršavaju, pamteći stanja oba automata. Novi automat ima stanja koja su parovi stanja originalnih automata, a razlika između operacija (presek, unija, razlika) je samo u tome koji parovi stanja su finalna stanja novog automata.

Iz perspektive kompajlera, ovo je korisno jer nam omogućava da kombinujemo jednostavne skenere u složenije.

### Minimizacija automata

Da li imamo sistematičan način da pojednostavimo automat? Tražimo ekvivalentan automat (prepoznaje isti jezik) sa manje stanja. Postupak se zove minimizacija i svodi se na potragu za suvišnim stanjima - nedostižna stanja (do kojih se nikada ne može doći) i ekvivalentna stanja (koja se ponašaju identično).

## Nedeterministički konačni automat (NKA/NFA)

### Razlika između DKA i NKA

Kod **determinističkog** automata, jednoznačno je određena promena stanja za svaki ulazni simbol. Funkcija prelaza uvek vraća jedno stanje: sigma: S x Sigma -> S.

Kod **nedeterminističkog** automata, iz jednog stanja na osnovu istog simbola može se preći u više različitih stanja. Funkcija prelaza vraća podskup stanja: sigma: S x Sigma -> P(S), gde je P(S) partitivni skup od S.

### Ekvivalentnost DKA i NKA

Tvrđenje: Za svaki NKA postoji odgovarajući DKA. Prihvataju iste jezike. Postoje algoritmi za pretvaranje NKA u DKA.

Zašto ih razmatramo ako su ekvivalentni? Zato što je NKA često jednostavniji za konstruisanje (manji broj stanja, intuitivniji), a DKA je jednostavniji za implementaciju (deterministički, nema nedeterminizma).

### Epsilon-NKA

Epsilon-NKA je proširenje NKA u kome postoje prelazi za epsilon (praznu reč). Ovi prelazi se izvršavaju i bez čitanja ulaznih simbola.

Funkcija prelaza: sigma: S x (Sigma U {epsilon}) -> P(S)

Primer: regularni izraz `a(bba|bb)*b` se može prirodno predstaviti epsilon-NKA automatom.

Tvrđenje: Za svaki epsilon-NKA postoji odgovarajući NKA. Prihvataju iste jezike. Postoje algoritmi za pretvaranje.

### Poređenje svih vrsta konačnih automata

| Automat | Funkcija prelaza | Determinizam |
|---------|------------------|--------------|
| DKA | sigma: S x Sigma -> S | Potpuno deterministički |
| NKA | sigma: S x Sigma -> P(S) | Nedeterministički |
| epsilon-NKA | sigma: S x (Sigma U {epsilon}) -> P(S) | Nedeterministički + epsilon prelazi |

Sva tri tipa prepoznaju istu klasu jezika - regularne jezike.

## Od regularnog izraza do automata

### Ključna tvrđenja

- Regularni izrazi definišu regularne jezike.
- Za svaki regularan jezik postoji konačni automat koji ga prepoznaje.
- Postoji sistematičan način da kreiramo automat na osnovu regularnog izraza.

### Konstrukcija automata za osnovne regularne izraze

```
L(prazan)  = prazan skup              -- automat bez finalnih stanja
L(epsilon) = {epsilon}                 -- automat sa s0 koje je i finalno
L(a)       = {a}                       -- s0 --a--> s1 (finalno)
L(r1|r2)   = L(r1) U L(r2)            -- unija automata
L(r1.r2)   = L(r1)L(r2)               -- konkatenacija automata
L(r1*)     = L(r1)*                    -- Klinijeva zvezda automata
```

### Kompletna automatizacija

Imamo postupke (algoritme) za:

1. **Kombinovanje automata** (unija, presek, razlika)
2. **Regularni izraz -> epsilon-NKA** (Tompsonova konstrukcija)
3. **epsilon-NKA -> NKA** (eliminacija epsilon prelaza)
4. **NKA -> DKA** (konstrukcija podskupova)
5. **Minimizacija DKA** (eliminacija suvišnih stanja)

Ovo znači kompletnu automatizaciju procesa: od regularnog izraza do minimalnog determinističkog konačnog automata. Upravo ovo radi flex - od regularnih izraza automatski generiše skener.

### Implementacija automata

Kako bismo implementirali prepoznavanje da li zadata reč pripada jeziku nekog automata? Pseudokod:

```
if a
    next
    while a and not eof
        next
        if b
            next
            if EOF
                OK
            else
                ERROR
        else
            ERROR
else
    ERROR
```

Sa obradom grešaka (nastavak čitanja do kraja ulaza):

```
if ERROR
    while not eof
        next
```

Ali mi nemamo, na primer, automat za leksiku. Da li postoji neki sistematičan način da dobijemo automat? Da - upravo je to put: regularni izraz -> automat -> implementacija (flex).

## Hijerarhija Čomskog

Noam Chomsky je klasifikovao formalne jezike u hijerarhiju sa četiri nivoa:

| Tip | Naziv | Gramatika | Automat |
|-----|-------|-----------|---------|
| Tip 3 | Regularni jezici | Regularne gramatike (A -> a, A -> aB) | Konačni automati (DFA) |
| Tip 2 | Kontekstno slobodni jezici | Kontekstno slobodne gramatike (A -> alpha) | Potisni automati (PDA) |
| Tip 1 | Kontekstno zavisni jezici | Kontekstno zavisne gramatike (alphaAbeta -> alphagammabeta) | Linearno ograničeni automati |
| Tip 0 | Rekurzivno nabrojivi jezici | Gramatike bez restrikcija (alpha -> gamma) | Tjuringove mašine |

Hijerarhija je inkluzivna: T3 je podskup od T2, T2 je podskup od T1, T1 je podskup od T0.

Za kompajlere je najvažnije: gramatike za opis leksike programskog jezika su znatno jednostavnije nego gramatike za opis sintakse. Leksika velikog broja programskih jezika predstavlja regularan jezik (Tip 3). Velik deo sintakse programskih jezika predstavlja kontekstno slobodan jezik (Tip 2).

### Primeri jezika po klasama

```
Regularni (Tip 3):   L = {a^n * b^m | n,m >= 1}
Kontekstno slobodni: L = {a^n * b^n | n >= 1}
                     L = {a^n * b^m * c^(n+m) | n,m >= 1}
Kontekstno zavisni:  L = {a^n * b^n * c^n | n >= 1}
                     L = {a^n * b^m * c^(n*m) | n,m >= 1}
```

Primetimo razliku: regularni jezici ne mogu da "broje" (ne mogu da obezbede jednake količine različitih simbola), kontekstno slobodni mogu da broje jedan parametar (pomoću steka), a kontekstno zavisni mogu da broje više parametara.

## Potisni automati (PDA)

### Formalna definicija

Deterministički potisni automat je uređena šestorka A = (S, Sigma, Gamma, sigma, s0, F) gde je:

- **S** - skup stanja
- **Sigma** - alfabet (ulazni simboli)
- **Gamma** - alfabet steka
- **sigma** - funkcija prelaza: S x (Sigma U {_}) x Gamma -> S x {N, R} x Gamma*
- **s0** - inicijalno stanje
- **F** - skup završnih stanja

Razlika u odnosu na konačni automat je što PDA ima stek (memoriju). Funkcija prelaza sigma(s, a, A) = (p, x, w) znači: automat se prebacuje iz stanja s u stanje p, glava za čitanje se ili pomera (x = R) ili ne pomera (x = N), i simbol A na vrhu steka se menja stringom w.

Prihvatanje reči: reč je prihvaćena ako je automat u finalnom stanju i/ili je stek prazan.

Zašto postoji posebna azbuka za stek? Zato što simboli na steku ne moraju odgovarati ulaznim simbolima - stek se koristi kao pomoćna memorija.

### Primer: balansirane zagrade

Balansirane zagrade su primer konstrukta koji nam je potreban za programske jezike i koji ne može da se opiše regularnom gramatikom.

**Gramatika za balansirane zagrade:**

```
S -> epsilon | SS | (S)
```

- Drugo pravilo: spoj dva dela koji su balansirani i sam je balansiran
- Treće pravilo: balansirani izraz u zagradama je opet balansiran
- Prvo pravilo: zaustavi rekurziju

Na primer: `(()(()()()))` je ispravno balansiran.

**PDA za balansirane zagrade:**

Ideja je jednostavna:

- Kad pročitamo `(` - stavimo na stek
- Kad pročitamo `)` - sklonimo sa steka
- Kad obradimo poslednji simbol - stek je prazan znači da su zagrade balansirane

Formalno:

```
A = (Sigma, Gamma, S, sigma, s0)
Sigma = { (, ) }
Gamma = { $, A }
S = {s}
s0 = s

Funkcija prelaza:
s ( $  -> s R $A     -- na pocetku, dodaj A na stek iznad $
s ( A  -> s R AA     -- dodaj jos jedno A na stek
s ) A  -> s R e      -- ukloni A sa steka (e = epsilon)
s ) $  -> s N e      -- odbacivanje: stek prazan pre kraja (vise desnih)
s _ $  -> s N e      -- prihvatanje: string gotov, stek prazan
s _ A  -> s N A      -- odbacivanje: string gotov ali stek nije prazan (vise levih)
```

### Veza između PDA i CFG

PDA su u opštem slučaju nezavisni od kontekstno slobodnih gramatika - to su jednostavno apstraktne mašine. Ali, ispostavlja se da potisni automati prepoznaju upravo kontekstno slobodne jezike.

Tvrđenje: Jezik je kontekstno nezavisan akko postoji PDA koji prihvata taj jezik.

Postoji postupak kako se na osnovu gramatike može generisati potisni automat. Ovaj postupak uključuje transformaciju gramatike u određeni oblik tako da se jednostavno i direktno dobiju potrebni skupovi za PDA. Upravo ovo radi bison - od kontekstno slobodne gramatike automatski generiše parser (koji interno simulira potisni automat).

## Tjuringova mašina

Na vrhu hijerarhije Čomskog je Tjuringova mašina - najopštija mašina. Linearno ograničen prostor na traci daje kontekstno zavisne jezike. Tjuringove mašine sa jednom ili više traka su ekvivalentne (broj traka ne povećava izražajnu moć).

Univerzalna Tjuringova mašina prima kao ulaz i mašinu i podatke - ovo je konceptualna osnova za računar i Von Nojmanovu arhitekturu (instrukcije + podaci).

Halting problem je fundamentalni rezultat koji kaže da ne postoji opšti algoritam koji može za proizvoljnu Tjuringovu mašinu i ulaz da odredi da li će se izvršavanje zaustaviti.

## Rezime: veza sa kompajlerima

| Faza kompajlera | Formalni jezik | Gramatika | Automat | Alat |
|-----------------|----------------|-----------|---------|------|
| Leksička analiza | Regularni (Tip 3) | Regularna (A -> a, A -> aB) | Konačni automat (DFA) | Flex |
| Sintaksna analiza | Kontekstno slobodni (Tip 2) | CFG (A -> alpha) | Potisni automat (PDA) | Bison |

Regularni jezici su dovoljni za realizaciju leksičke analize, a kontekstno slobodni jezici pokrivaju velik deo sintakse programskih jezika.