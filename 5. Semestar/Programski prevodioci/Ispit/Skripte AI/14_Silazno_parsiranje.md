# Silazno parsiranje

## Parsiranje - podsetnik

Parseru stiže niz tokena. Izvodi se sintaksna struktura programa - transformiše se običan string u sintaksni model. Cilj je dokazati da se ulazni program može izvesti na osnovu pravila gramatike jezika. Na osnovu pravila izvođenja se gradi stablo parsiranja, često implicitno.

## Dva pristupa parsiranju

### Uzlazno parsiranje (bottom-up)

Pokušavamo da od ulaznog niza simbola redukcijom dobijemo početni pojam. Akcije: desna strana pravila se zamenjuje levom. Stablo parsiranja se gradi od listova prema vrhu. Primer: bison koristi LALR(1) - uzlazno parsiranje sa jednim preduvidnim (LA) tokenom.

### Silazno parsiranje (top-down)

Pokušavamo da od početnog pojma izvedemo ulazni niz simbola prateći pravila produkcije. Akcije: leva strana pravila se zamenjuje desnom. Stablo parsiranja se gradi od vrha prema listovima.

Primer izvođenja za `num + num + num` sa gramatikom `E -> E + num | num`:

```
E
=> E + num
=> E + num + num
=> num + num + num
```

Različiti podskupovi kontekstno-slobodnih gramatika zahtevaju različite tehnike parsiranja.

## Princip silaznog parsiranja

1. Kreće se od početnog neterminala, kreira se vrh stabla
2. U svakom koraku se bira čvor u trenutno izgrađenom stablu koji predstavlja neki neterminal
3. Za njega se bira pravilo i razvija podstablo koje odgovara tom pravilu
4. Ponavlja se sve dok:
   - se ne dođe do listova (terminali, tokeni) čiji niz odgovara ulaznom nizu - OK, ili
   - dok se ne otkrije problem: parser nije dobro odlučio prilikom odabira pravila - vraćanje unazad (backtrack), ili sve opcije su isprobane - greška

### Algoritam silaznog parsiranja (pseudokod)

```
root <- node for the start symbol, S;
focus <- root;
push(null);
word <- NextWord();

while (true) do;
    if (focus is a nonterminal) then begin;
        pick next rule to expand focus (A -> b1, b2, ..., bn);
        build nodes for b1, b2, ..., bn as children of focus;
        push(bn, bn-1, ..., b2);
        focus <- b1;
    end;

    else if (word matches focus) then begin;
        word <- NextWord();
        focus <- pop();
    end;

    else if (word = eof and focus = null)
        then accept the input and return root;
        else backtrack;
end;
```

### Primer sa backtracking-om

Za gramatiku:

```
1. E -> E + T
2. E -> T
3. T -> T * num
4. T -> num
```

I ulaz `num + num * num`:

```
E
(2) T
(3) T * num
(4) num * num
    error / backtrack

E
(2) T
(4) num
    error / backtrack

E
(1) E + T
(2) T + T
(4) num + T
(3) num + T * num
(4) num + num * num
    ok
```

### Backtracking

Kada parser otkrije grešku:

- Fokus (obradu) vratiti na roditeljski čvor
- Izbaciti generisano podstablo
- Ako je ostalo neisprobanih pravila za neterminal koji se obrađuje - izabrati novo
- Ako nije ostalo neisprobanih pravila - povratak na nivo iznad
- Ako su iscrpljene sve mogućnosti (vrh koji odgovara početnom pojmu i sva njegova pravila) - ulazni string nije validan

Obratiti pažnju: mora se rekonstruisati i obrađeni deo ulaznog stringa - prilikom uklanjanja podstabla sve terminale treba "vraćati" kao deo ulaznog stringa.

### Heuristika za izbor pravila

Kad u jednom momentu posmatramo jedan neterminal A za koji postoji više pravila, mora postojati heuristika za izbor pravila. Mogućnosti:

- Prvo pravilo koje se pojavljuje u gramatici
- "Najkraće/najduže" pravilo
- Slučajni izbor
- Nešto drugo

Dobra heuristika je ona sa kojom bismo postigli što manje vraćanja unazad. Ako bismo svaki put izabrali tačno ono pravilo koje treba - idealno, direktno parsiranje, bez vraćanja.

## Problem leve rekurzije

Ako je algoritam "probaj pravila redom kako se pojavljuju u gramatici":

```
1. E -> E + T
2. E -> T
3. T -> T * num
4. T -> num

Ulaz: num + num * num

E
(1) E + T
(1) E + T
(1) E + T
...
```

Nikad se ne generiše terminal - ne može se uporediti sa prvim tokenom (num). Leva rekurzija je problem za silazno parsiranje.

### Eliminacija leve rekurzije

Opšti postupak transformacije:

```
Levo rekurzivno:       Desno rekurzivno (ekvivalentno):
A -> Aa | b            A -> bR
                       R -> aR | e
```

Oba oblika generišu isti jezik: `baaa...a` (b praćeno nula ili više a).

### Primer: eliminacija leve rekurzije za aritmetičke izraze

Originalna gramatika (levo rekurzivna):

```
E -> E + T | T
T -> T * num | num
```

Transformisana gramatika (desno rekurzivna):

```
E  -> T E'
E' -> + T E' | e

T  -> num T'
T' -> * num T' | e
```

### Primer: lista promenljivih

```
Levo rekurzivno:                Desno rekurzivno:
var_list -> variable            var_list  -> variable var_list1
          | var_list variable   var_list1 -> variable var_list1
                                            | e
```

Ovde je alfa == beta (oba su `variable`), ali postupak je isti.

### Indirektna leva rekurzija

U prethodnim primerima postoji direktna leva rekurzija. Lako se uočava i ručno se može ukloniti. Može postojati i indirektna leva rekurzija - kroz više pravila se pojavljuje lanac:

```
a -> b
b -> g
g -> a d
```

Izvođenje: `a ->* a d` - indirektna leva rekurzija.

Postupak za eliminaciju:

1. Pronaći sve indirektne leve rekurzije
2. Zameniti ih direktnim levim rekurzijama (supstitucijom)
3. Zameniti direktne leve rekurzije desnim

## Prediktivno parsiranje (LL parsiranje)

### Prediktivna gramatika

Kontekstno-slobodna gramatika gde silazno parsiranje sa najlevljim izvođenjem uvek bira ispravno pravilo koristeći k preduvidnih (LA) terminala. Na osnovu narednih ulaznih tokena se određuje koje pravilo će se birati za nastavak - backtrack-free parsiranje.

Oznaka: **LL(k)** - čita se sleva nadesno (L), gradi najlevlje izvođenje (L), koristi k preduvidnih tokena.

**LL(1)** - koristi samo 1 preduvidni token. Za gramatiku:

```
1. E  -> T E'
2. E' -> + T E' | - T E' | e
3. T  -> num T'
4. T' -> * num T' | / num T' | e
```

Ako vidim da dolazi `+`, znam koje pravilo da biram za E'.

## FIRST skup

Za svaki neterminal alfa se određuje skup FIRST(alfa) koji sadrži sve terminale koji se mogu pojaviti na početku prilikom izvođenja alfa. Elementi FIRST skupa za tokene, praznu reč i eof su oni sami.

### Algoritam za FIRST

Za svaki neterminal X:

- Ako postoji izvođenje X ->* e, dodati e u FIRST(X)
- Za pravilo X -> Y1 Y2 ... Yk: sve simbole iz FIRST(Y1) dodati u FIRST(X)
- Ako postoji izvođenje Y1 ->* e, onda sve simbole iz FIRST(Y2) dodati u FIRST(X)
- Ukoliko je potrebno, isti postupak primenjivati na Y2, ..., Yk

Za niz simbola s, FIRST(s) je unija skupova svih FIRST skupova simbola sa desne strane, od prvog simbola do simbola čiji FIRST skup ne sadrži praznu reč. Prazna reč pripada skupu FIRST(s) ako ona pripada svakom simbolu sa desne strane.

### Primeri FIRST skupova

**Primer 1: statement**

```
statement        -> if_statement | return_statement
if_statement     -> "if" "(" rel_exp ")" statement
return_statement -> "return" num_exp ";"

FIRST(statement)        = { if, return }
FIRST(if_statement)     = { if }
FIRST(return_statement) = { return }
```

**Primer 2: aritmetički izrazi**

```
E  -> T E'
E' -> + T E' | - T E' | e
T  -> num T'
T' -> * num T' | / num T' | e

FIRST(e)          = { e }
FIRST(num)        = { num }
FIRST(/ num T')   = { / }
FIRST(* num T')   = { * }
FIRST(T')         = { /, *, e }
FIRST(T)          = { num }
FIRST(- T E')     = { - }
FIRST(+ T E')     = { + }
FIRST(E')         = { -, +, e }
FIRST(E)          = { num }
```

## FOLLOW skup

Problem sa FIRST skupom nastaje kod prazne reči (e) - njen skup ne sadrži nijedan terminal. Da bismo mogli da razlikujemo sintaksne greške od "nastavka" uvodi se skup FOLLOW.

Za svaki simbol alfa se određuje skup FOLLOW(alfa) koji sadrži sve terminale koji mogu da se pojave neposredno nakon izvođenja alfa.

### Algoritam za FOLLOW

Za svaki neterminal X:

- Ako je X početni pojam gramatike, dodati eof u FOLLOW(X)
- Za svako pravilo u kome se X pojavljuje sa desne strane:
  - Y -> aXb: dodati FIRST(b) \ {e} u FOLLOW(X). Ako e postoji u FIRST(b), dodati FOLLOW(Y) u FOLLOW(X).
  - Y -> aX (X na poslednjem mestu): dodati FOLLOW(Y) u FOLLOW(X).

### Primer FOLLOW skupova

```
E  -> T E'
E' -> + T E' | - T E' | e
T  -> num T'
T' -> * num T' | / num T' | e

FOLLOW(E)  = { eof }
FOLLOW(E') = { eof }
FOLLOW(T)  = { +, -, eof }
FOLLOW(T') = { +, -, eof }
```

### Korišćenje FIRST i FOLLOW za parsiranje

Za ulaz `3 + 5`:

1. Kreće se od E. Samo jedno pravilo, nema odlučivanja.
2. T - samo jedno pravilo. 3 se prepoznaje kao num.
3. T' - odluka: `* num T'`, `/ num T'` ili e?
   - LA je `+`
   - `+` ne pripada FIRST(T') = {/, *, e}
   - `+` pripada FOLLOW(T') = {+, -, eof}
   - Pošto je `+` u FOLLOW(T'), to znači da T' treba da izabere e pravilo (nastavak, ne greška)
4. Nastavljamo sa E' - LA je `+`, pripada FIRST(+ T E') - biramo pravilo `+ T E'`

Drugi primeri:

- Da je ulaz `3 * 5`: LA je `*`, pripada FIRST(* num T') - biramo pravilo za množenje
- Da je ulaz `3 5`: `num` ne pripada FOLLOW(T') - sintaksna greška
- Da je ulaz `3`: LA je eof, pripada FOLLOW(T') - biramo e, kraj, OK

### Oporavak od grešaka

Sledbenički skup (FOLLOW) olakšava i oporavak od grešaka u toku kompajliranja (panic mode error-recovery). Omogućava da se nakon otkrivanja pogrešnog simbola ignorišu simboli u ulaznom nizu između pogrešnog simbola i simbola koji pripada sledbeničkom skupu (sinhronizacioni skup).

## FIRST+ skup

Generalizacija FIRST skupa koja objedinjuje FIRST i FOLLOW:

```
FIRST+(a -> b) = FIRST(b),                    ako FIRST(b) ne sadrzi e
FIRST+(a -> b) = FIRST(b) U FOLLOW(a),        u suprotnom
```

Za gramatiku sa pravilima `a -> b1 | b2 | ... | bn`:

Gramatika je prediktivna (backtrack-free) ako su FIRST+ skupovi disjunktni:

```
FIRST+(a -> bi) ∩ FIRST+(a -> bj) = prazno,   za svako i != j
```

## Leva faktorizacija

Kada više pravila za isti neterminal počinju istim simbolom, FIRST+ skupovi nisu disjunktni:

```
A -> xb1 | xb2 | ... | xbn | g1 | g2 | ... | gm
```

Rešenje - izdvajanje zajedničkog dela i uvođenje novog neterminala:

```
A -> xB | g1 | g2 | ... | gm
B -> b1 | b2 | ... | bn
```

Time se dobijaju disjunktni FIRST+ skupovi.

## Uklanjanje leve rekurzije + leva faktorizacija

Ovo su alati za eventualno postizanje gramatike gde nema potrebe za vraćanjem unazad. Međutim, nemamo algoritam za utvrđivanje da li postoji backtrack-free gramatika za proizvoljan kontekstno-slobodan jezik.

## Rekurzivni silazni parser (Recursive Descent)

Skup rekurzivnih funkcija - za svaki neterminal postoji odgovarajuća funkcija. Svaka od ovih funkcija prepoznaje odgovarajući neterminal u ulaznom tekstu.

Algoritam:

- Izvršavanje počinje od prvog, početnog, neterminala
- Svaka funkcija na osnovu FIRST+ skupa odlučuje o pravilu
- Za izabrano pravilo: ako je terminal - upoređivanje sa LA i pomeranje; ako je neterminal - poziv odgovarajuće funkcije

### Primer implementacije

Za gramatiku:

```
E  -> T E'
E' -> + T E' | - T E' | e
T  -> num T'
T' -> * num T' | / num T' | e
```

```
Main()
    LA = nextToken()
    if (E())
        if LA == eof
            success
        else
            try error recovery

E()
    if (T())
        return Eprim()
    else
        return false

Eprim()
    if (LA = + OR -)
        LA = nextToken
        if (T())
            return Eprim()
        else
            return false
    else
        if (LA = eof)
            return true
        else
            report Syntax error
            return false
```

Ovo je okvir za ručno generisanje RD parsera - programer piše funkcije za svaki pojam u gramatici. Jednostavno i pogodno za manje složene gramatike.

## Tabelarni parser

Moguće je kreirati i parser generator. Na osnovu gramatike se kreira tabela:

- Redovi su neterminali
- Kolone su terminali
- Za svaki element tabele se upiše pravilo koje odgovara situaciji kad je odgovarajući terminal LA

### Algoritam za kreiranje tabele

```
build FIRST, FOLLOW, and FIRST+ sets;

for each nonterminal A do;
    for each terminal w do;
        Table[A, w] <- error;
    end;

    for each production p of the form A -> b do;
        for each terminal w in FIRST+(A -> b) do;
            Table[A, w] <- p;
        end;

        if eof in FIRST+(A -> b)
            then Table[A, eof] <- p;
    end;
end;
```

### Algoritam za tabelarno parsiranje

```
word <- NextWord();
push eof onto Stack;
push the start symbol, S, onto Stack;
focus <- top of Stack;

loop forever;
    if (focus = eof and word = eof)
        then report success and exit the loop;

    else if (focus in T or focus = eof) then begin;
        if focus matches word then begin;
            pop Stack;
            word <- NextWord();
        end;
        else report an error looking for symbol at top of stack;
    end;

    else begin; /* focus is a nonterminal */
        if Table[focus, word] is A -> B1 B2 ... Bk then begin;
            pop Stack;
            for i <- k to 1 by -1 do;
                if (Bi != e)
                    then push Bi onto Stack;
            end;
        end;
        else report an error expanding focus;
    end;

    focus <- top of Stack;
end;
```

## Rezime

Ciljevi za silazno parsiranje:

- Nema dvosmislenosti u gramatici
- Nema leve rekurzije
- Ima jednoznačne početne skupove (disjunktni FIRST+)

Većina konstrukata u programskim jezicima se može izraziti prediktivnim gramatikama. Silazno parsiranje se često koristi za ručno pisane parsere, sa eventualno dodatnim modifikacijama za specijalne slučajeve.

Najveća mana je to što ne sme da ima levu rekurziju, a ona je za mnoge stvari prirodnija.

## Od LL(1) ka PEG

CPython je prešao sa LL(1) parsera na PEG (Parsing Expression Grammar) parser - pogledati PEP 617. PEG parseri nemaju ograničenja LL(1) parsera (leva rekurzija, leva faktorizacija), ali koriste memoizaciju i potencijalno troše više memorije.