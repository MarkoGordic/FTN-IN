# Sintaksna stabla

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Dva osnovna stabla

Postoje dva osnovna stabla u kontekstu prevođenja:

- **Konkretno sintaksno stablo** (stablo parsiranja, parse tree) - struktura koja odgovara gramatičkoj strukturi ulaznog stringa
- **Apstraktno sintaksno stablo** (AST) - pojednostavljena verzija koja čuva suštinsku strukturu programa

## Stablo parsiranja

Stablo parsiranja je struktura podataka koja odgovara gramatičkoj strukturi ulaznog stringa. Čitajući listove stabla s leva na desno dobijamo polazni string.

### Primer

Za gramatiku sličnu miniC-u:

```
assignment_stmt -> ID ASSIGN num_exp SC
num_exp         -> exp
num_exp         -> num_exp PLUS exp
num_exp         -> num_exp MINUS exp
exp             -> NUM
exp             -> ID
```

I ulazni string `a = b + 3;` koji daje niz tokena `w = ID ASSIGN ID PLUS NUM SC`, stablo parsiranja izgleda ovako:

```
            assignment_stmt
           /    |       |    \
         ID  ASSIGN  num_exp  SC
                    /   |   \
               num_exp PLUS  exp
                  |           |
                 exp         NUM
                  |
                 ID
```

Koren stabla je početni pojam (`assignment_stmt`), unutrašnji čvorovi su neterminali, a listovi su terminali (tokeni). Čitajući listove s leva na desno dobijamo: ID ASSIGN ID PLUS NUM SC - upravo polazni niz tokena.

### Parsiranje i stablo

Parsiranje praktično formira stablo parsiranja. Drugim rečima, parsiranje je proces pronalaženja stabla parsiranja:

- **Top-down parsiranje** - gradi stablo od korena ka listovima
- **Bottom-up parsiranje** - gradi stablo od listova ka korenu

U prevodiocu stablo parsiranja može postojati eksplicitno ili implicitno. Važno: stablo parsiranja (konkretno sintaksno stablo) nije isto što i apstraktno sintaksno stablo.

## Izvođenja

Nekad, prilikom izvođenja, možemo krenuti različitim "putevima". Posmatrajmo sledeću gramatiku:

```
E -> num
E -> E + E
```

Za string `5 + 3 + 1` (w = num + num + num) postoje različita izvođenja.

### Leftmost derivation (najlevlje izvođenje)

Izvođenje u kom se uvek primenjuje pravilo na prvi pojam sa leve strane:

```
E
=> E + E
=> num + E
=> num + E + E
=> num + num + E
=> num + num + num
```

### Rightmost derivation (najdešnje izvođenje)

Izvođenje u kom se uvek primenjuje pravilo na prvi pojam sa desne strane:

```
E
=> E + E
=> E + num
=> E + E + num
=> E + num + num
=> num + num + num
```

### Ni levo ni desno izvođenje

Postoje izvođenja koja ne prate ni jednu od ove dve heuristike:

```
E
=> E + E
=> E + num
=> E + E + num
=> num + E + num
=> num + num + num
```

### Veza izvođenja i stabla

Različita izvođenja mogu dati različita stabla parsiranja. Zapravo, u stablu ne postoji informacija o redosledu primene pravila - stablo samo prikazuje strukturu. Na slikama se redosled modeluje grafički (spuštanjem listova), ali stablo suštinski nema tu informaciju.

Ako svaki string ima jedinstveno stablo parsiranja, onda svaki string ima i jedinstveno najlevlje izvođenje i jedinstveno najdešnje izvođenje.

## Asocijativnost

Stablo parsiranja utiče na asocijativnost operacija. Za izraz `5 + 3 + 1` dva različita stabla daju:

- `num + (num + num)` - desna asocijativnost: operand 3 je preuzet od strane desnog + operatora, rezultat je `5 + (3 + 1)`
- `(num + num) + num` - leva asocijativnost: operand 3 je preuzet od strane levog + operatora, rezultat je `(5 + 3) + 1`

Ako je operator `+` levo asocijativan, operand 3 će biti preuzet od strane levog operatora: `(5 + 3) + 1`. Ako je desno asocijativan: `5 + (3 + 1)`.

Ovo može biti značajno kod evaluacije. Iako se u fazi parsiranja ne bavimo evaluacijom (izračunavanjem), zanima nas struktura jer kad bude trebala evaluacija - već tada moramo imati rešeno pitanje asocijativnosti. I ne mora biti operator sabiranja niti operandi nužno numeričke vrednosti - princip važi za sve operatore.

## Dvosmislenost gramatike

### Problem

Za gramatiku sa operatorima + i -:

```
E -> num
E -> E + E
E -> E - E
```

I string `5 - 3 + 1` (w = num - num + num), postoje dva različita stabla parsiranja koja daju:

- `5 - (3 + 1)` = 1
- `(5 - 3) + 1` = 3

Rezultati evaluacije su različiti!

### Definicija

Kažemo da je gramatika **dvosmislena** (višeznačna) ako za neki polazni string postoje bar dva različita stabla parsiranja.

Važne činjenice:

- Ne postoji univerzalni algoritam za detekciju dvosmislene gramatike ili njenog pretvaranja u gramatiku koja nije dvosmislena.
- Dvosmislenost je osobina gramatike, ne jezika! Isti jezik može biti opisan i dvosmislenom i jednoznačnom gramatikom.

### Rešenja

1. Možemo promeniti gramatiku
2. Možemo koristiti mehanizme u bisonu za definisanje prioriteta i asocijativnosti

### Rešenje promenom gramatike: vrsta rekurzije

Dvosmislena gramatika:

```
E -> num
E -> E + E
```

**Desna rekurzija** - daje desno asocijativno stablo:

```
E -> num
E -> num + E
```

Izvođenje za `5 + 3 + 1`:

```
E => num + E => num + num + E => num + num + num
```

Stablo je definisano kao lista - uvek se grana udesno, dajući `num + (num + num)`.

**Leva rekurzija** - daje levo asocijativno stablo:

```
E -> num
E -> E + num
```

Izvođenje za `5 + 3 + 1`:

```
E => E + num => E + num + num => num + num + num
```

Stablo je definisano kao lista - uvek se grana ulevo, dajući `(num + num) + num`.

Dvosmislenost jeste problem, vrsta rekurzije može odrediti stablo. Međutim, vrsta rekurzije koja se pojavljuje može biti problem za određenu vrstu parsiranja (leva rekurzija je problem za top-down parsere).

## Prioritet operatora

### Problem

Za gramatiku sa operatorima različitog prioriteta:

```
E -> num
E -> E + E
E -> E * E
```

I string `5 + 3 * 2` (w = num + num * num), postoje dva različita stabla:

- Ako prvo primenimo pravilo za `+`: dobijamo `5 + (3 * 2)` - množenje ima veći prioritet
- Ako prvo primenimo pravilo za `*`: dobijamo `(5 + 3) * 2` - sabiranje ima veći prioritet

Moramo obezbediti i asocijativnost i prioritet.

### Rešenje promenom gramatike

Ideja: izraz `5 + 3 * 2 + 4 * 1` posmatramo kao sabirke. Sabirak može biti prost broj ili proizvod. Umesto jednog nivoa pravila, uvodimo dva nivoa:

```
E -> E + T
E -> T
T -> T * num
T -> num
```

Za `5 + 3 * 2`:

```
E
=> E + T
=> T + T
=> num + T
=> num + T * num
=> num + num * num
```

Stablo jasno pokazuje da se `3 * 2` grupiše zajedno (kao `T`), a tek onda se sabira sa `5`. Svaki nivo pravila definiše operatore istog prioriteta, a dublje pravilo ima veći prioritet.

### Rešenje u bisonu: deklaracije prioriteta i asocijativnosti

Za miniC: ima samo `+` i `-`, pa prioritet između njih nije potreban. Ali ako se dodaju `*` i `/`, treba razmisliti o prioritetu.

U bisonu postoje sledeće deklaracije (navode se umesto `%token`):

```yacc
%left     -- levo asocijativan
%right    -- desno asocijativan
%nonassoc -- nije asocijativan (a OP b OP c je sintaksna greška)
%precedence -- definiše samo prioritet, ne i asocijativnost
```

Ranije navedeni operator ima **manji** prioritet. Operatori navedeni u istom redu imaju isti prioritet. Na primer:

```yacc
%left '<' '>' '='
%left '+' '-'
%left '*' '/'
```

Ovde relacioni operatori imaju najmanji prioritet, pa sabiranje/oduzimanje, pa množenje/deljenje sa najvećim prioritetom.

### Pravila i prioritet

Pravila preuzimaju prioritet poslednjeg tokena u pravilu. Može se eksplicitno promeniti prioritet pravila dodeljivanjem prioriteta određenog tokena pomoću `%prec`:

```yacc
%left '+' '-'
%left '*' '/'
%left UMINUS

exp : exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | '-' exp %prec UMINUS
    | /* ... */
    ;
```

`UMINUS` je token koji se nikad ne pojavljuje kao prepoznati token pri skeniranju. Dodat je samo zbog razrešenja prioriteta - unarni minus treba da ima veći prioritet od množenja i deljenja.

Obratiti pažnju na koji token je poslednji u pravilu. Na primer: `exp '+' exp` ima prioritet kao `+`, ali `exp '+' exp ';'` ima prioritet kao `';'` jer je tačka-zarez poslednji token.

## Konflikti u bisonu

Bison podrazumevano generiše LALR(1) parser - koristi 1 lookahead (LA) token, čita ulaz s leva na desno i konstruiše najdešnje izvođenje u obrnutom redosledu.

Ukoliko postoji višeznačnost u gramatici, javljaju se konflikti - potencijalno se u datom stanju može izvršiti više akcija.

### Shift-reduce konflikti

Nastaju kada, posmatrajući LA token, može da se izvrši i shift i reduce akcija. Primeri:

```
5 + 2 + 3  ->  (5 + 2) + 3   potreban reduce
5 + 2 * 3  ->  5 + (2 * 3)   potreban shift
5 * 2 + 3  ->  (5 * 2) + 3   potreban reduce
```

### Reduce-reduce konflikti

Nastaju kada postoji više pravila koja se mogu primeniti na ulazni niz.

### Razrešavanje konflikata

**Podrazumevano razrešavanje u bisonu:**

- Shift-reduce: prednost se daje shift akciji. Ukoliko tokeni i pravila imaju definisan prioritet, onda se podrazumevana akcija menja.
- Reduce-reduce: prednost se daje reduce pravilu koje je ranije navedeno.

**Razrešavanje sa definisanim prioritetom:**

**Reduce** se bira ako:

- Prioritet pravila je veći od prioriteta LA tokena
- Prioritet pravila i LA tokena je isti, a asocijativnost pravila je `left`

**Shift** se bira u ostalim slučajevima:

- Prioritet pravila je manji od prioriteta LA tokena
- Prioritet pravila i LA tokena je isti, a asocijativnost pravila nije `left`
- Token ili pravilo nemaju definisan prioritet

### Primeri razrešavanja

Sa deklaracijama:

```yacc
%left '+' '-'
%left '*' '/'
```

- `5 + 2 + 3`: na steku imamo `E + E`, LA je `+`. Pravilo `exp '+' exp` ima prioritet `+`, LA token je `+` - isti prioritet, asocijativnost je `left` - biramo **reduce**: `(5 + 2) + 3`
- `5 + 2 * 3`: na steku `E + E`, LA je `*`. Pravilo ima prioritet `+`, LA token `*` ima veći prioritet - biramo **shift**: `5 + (2 * 3)`
- `5 * 2 + 3`: na steku `E * E`, LA je `+`. Pravilo ima prioritet `*` koji je veći od `+` - biramo **reduce**: `(5 * 2) + 3`

## Dangling else problem

Posmatrajmo sledeći kod:

```c
if (a != b) if (a > b) b = a; else a = b;
```

Kako se ovo interpretira? Postoje dve mogućnosti:

**Mogućnost 1** - else pripada unutrašnjem if-u:

```c
if (a != b)
    if (a > b)
        b = a;
    else
        a = b;
```

**Mogućnost 2** - else pripada spoljašnjem if-u:

```c
if (a != b)
    if (a > b)
        b = a;
else
    a = b;
```

Ovo je poznati "dangling else" problem. Sa gramatikom:

```
if_stmt -> IF exp stmt
if_stmt -> IF exp stmt ELSE stmt
```

Oba stabla parsiranja su validna prema gramatici - gramatika je dvosmislena. U praksi (i u većini programskih jezika) se preferira mogućnost 1 - `else` se vezuje za najbliži `if`.

### Rešenje u bisonu

```yacc
%nonassoc ONLY_IF
%nonassoc _ELSE
%%

if_statement
    : if_part %prec ONLY_IF
    | if_part _ELSE statement
    ;

if_part
    : _IF _LPAREN rel_exp _RPAREN statement
    ;
```

Kako ovo radi? Kad `_ELSE` bude LA token:

- Može se uraditi **reduce** `if_part -> if_statement` (pravilo ima prioritet `ONLY_IF`)
- Može se uraditi **shift** `_ELSE` (token ima prioritet `_ELSE`)

Pošto je `_ELSE` naveden posle `ONLY_IF`, `_ELSE` ima veći prioritet. Pravilo za reduce ima prioritet kao `ONLY_IF` koji je manji od prioriteta `_ELSE` tokena za shift. Rezultat: bira se **shift**, što znači da se `else` vezuje za najbliži `if`. Tačno ono što želimo.

## Napomene o konfliktima

- Podrazumevane akcije mogu biti neodgovarajuće.
- Posebno obratiti pažnju na reduce-reduce konflikte - oni ukazuju na ozbiljan problem u gramatici.
- Bolje je proučiti i izmeniti gramatiku nego se oslanjati na podrazumevano razrešavanje.
- Gramatika se uvek može transformisati tako da nema potrebe za deklaracijama prioriteta, ali deklaracije su ponekad jednostavnije rešenje.

## Veza sa miniC-om

- miniC ima samo `+` i `-`, pa nije potrebno razmišljati o prioritetu između operatora.
- Ako se dodaju `*` i `/`, treba razmisliti o prioritetu - ili promeniti gramatiku (dodati nivo za T) ili koristiti bison deklaracije.
- miniC koristi `%nonassoc` i `%prec` za rešavanje dangling else problema.