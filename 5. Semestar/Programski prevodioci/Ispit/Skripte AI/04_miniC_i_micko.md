# miniC jezik i micko kompajler

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta je miniC?

miniC je programski jezik koji je podskup programskog jezika C. To znači da je svaki ispravan miniC program ujedno i ispravan C program, pa se miniC programi mogu kompajlirati regularnim C kompajlerom. miniC je nastao odabirom osobina i koncepata C jezika koji su interesantni za kurs implementacije kompajlera. Međutim, te osobine su uzete u ograničenoj meri, tako da olakšaju implementaciju jezika. Autori su se uzdržali od mnogih karakteristika C-a koje nepotrebno komplikuju implementaciju, a u edukativnom smislu ne doprinose značajno.

Kompajler za miniC jezik naziva se **micko**. Autori su doc. dr Zorica Suvajdžin Rakić, prof. dr Miroslav Hajduković i prof. dr Žarko Živanov. Izvorni kod se nalazi na GitHub-u: https://github.com/zsuvajdzin/micko

## Primer miniC programa

Pogledajmo kompletan miniC program koji računa apsolutnu vrednost broja:

```c
//OPIS: ABS funkcija
//RETURN: 5

int abs(int i) {
    int res;

    if(i < 0)
        res = 0 - i;
    else
        res = i;

    return res;
}

int main() {
    return abs(-5);
}
```

Ovaj program ima dve funkcije: `abs` koja izračunava apsolutnu vrednost i `main` koja poziva `abs(-5)`. Čak i na ovako jednostavnom primeru možemo videti sve ključne osobine miniC jezika - tipove, funkcije sa parametrima, lokalne promenljive, if-else, aritmetičke operacije, pozive funkcija i return iskaz.

## Leksika miniC jezika

### Tokeni

miniC jezik prepoznaje sledeće tokene:

| Token | Opis |
|-------|------|
| ID | Identifikator |
| INT_NUMBER | Označeni celobrojni literal |
| UINT_NUMBER | Neoznačeni celobrojni literal |
| LPAREN, RPAREN | Male zagrade `(` `)` |
| LBRACKET, RBRACKET | Vitičaste zagrade `{` `}` |
| SEMICOLON | Tačka-zarez `;` |
| AROP | Aritmetički operator (`+`, `-`) |
| RELOP | Relacioni operator (`<`, `>`, `<=`, `>=`, `==`, `!=`) |
| ASSIGN | Operator dodele `=` |
| TYPE | Tip podatka (`int`, `unsigned`) |
| IF | Ključna reč `if` |
| ELSE | Ključna reč `else` |
| RETURN | Ključna reč `return` |

### Identifikatori

Identifikator u miniC jeziku se sastoji od malih slova, velikih slova i cifara, i ne sme započinjati cifrom. Primeri ispravnih identifikatora: `a`, `A`, `abc`, `number`, `Number`, `MyNumber`, `num2`, `num2str`. Primeri neispravnih identifikatora: `3a`, `_x`, `my_number`. Primetimo da miniC ne dozvoljava donju crtu u identifikatorima - to je pojednostavljenje u odnosu na C.

### Literali

Celobrojni označeni literal se sastoji od opcionalnog predznaka (plus ili minus) iza kojeg sledi jedna ili više cifara. Neoznačeni celobrojni literal se sastoji od jedne ili više cifara iza kojih sledi malo ili veliko slovo `u`. Primeri: `0`, `-123`, `12345`, `5u`, `1234U`.

### Preskakanje

Skener preskače beline (razmake, tabulatore, nove redove) i linijske komentare (koji počinju sa `//`).

## Sintaksa miniC jezika

### Neterminali (pojmovi)

Neterminali u gramatici miniC jezika su:

```
program, function_list, function,
type, parameter,
body, variable_list, variable,
statement_list, statement,
compound_statement, assignment_statement,
num_exp, exp, literal,
function_call, argument,
if_statement, if_part, rel_exp,
return_statement
```

### Program i funkcije

```yacc
program
    : function_list
    ;

function_list
    : function
    | function_list function
    ;

function
    : type _ID _LPAREN parameter _RPAREN body
    ;
```

Program se sastoji od liste funkcija, a lista funkcija sadrži jednu ili više funkcija. Program ima bar jednu funkciju.

Obratiti pažnju: nigde u gramatici ne piše da mora postojati funkcija `main()`. To je semantičko pravilo, ne sintaksno - sintaksno je dovoljno da postoji bar jedna funkcija bilo kog imena. Međutim, da bi program mogao da započne izvršavanje, potrebna mu je `main()` funkcija. Povratna vrednost funkcije `main()` je celobrojnog tipa (`int`).

### Tipovi i parametri

```yacc
type
    : _TYPE
    ;

parameter
    : /* empty */
    | type _ID
    ;
```

Obratiti pažnju na nekoliko važnih ograničenja:

- **Nema liste parametara.** Funkcija ima 0 ili 1 parametar - ne može imati više.
- **Nema void.** Funkcija mora vratiti `int` ili `unsigned`.
- miniC jezik podržava samo `int` i `unsigned` tipove podataka, tj. označene i neoznačene celobrojne vrednosti.

Primeri ispravnih zaglavlja funkcija:

```c
int f() { ... }           // funkcija bez parametara
int f(unsigned a) { ... } // funkcija sa jednim parametrom
```

### Telo funkcije, promenljive

```yacc
body
    : _LBRACKET variable_list statement_list _RBRACKET
    ;

variable_list
    : /* empty */
    | variable_list variable
    ;

variable
    : _TYPE _ID _SEMICOLON
    ;
```

Obratiti pažnju:

- **U telu prvo idu deklaracije, a onda iskazi.** Nije dozvoljeno mešanje deklaracija i iskaza.
- **Nema višestruke deklaracije.** U jednoj deklaraciji se deklariše samo jedna promenljiva.
- Telo može a ne mora da sadrži lokalne promenljive. Isto tako, može a ne mora da sadrži iskaze (prazno telo je dozvoljeno).

Ispravni primeri:

```c
int f() { }                        // prazno telo
int f(int a) { return a; }         // samo iskaz
int f() { int x; }                 // samo deklaracija
unsigned f() { unsigned x; x = 0u; } // deklaracija pa iskaz
```

Neispravan primer - deklaracija posle iskaza:

```c
int f() {
    int x;
    x = 0;
    int y;    // GREŠKA: deklaracija posle iskaza
    y = 0;
}
```

Neispravan primer - višestruka deklaracija:

```c
int counter, line;  // GREŠKA: samo jedna promenljiva po deklaraciji
```

### Iskazi

```yacc
statement_list
    : /* empty */
    | statement_list statement
    ;

statement
    : compound_statement
    | assignment_statement
    | if_statement
    | return_statement
    ;
```

Obratiti pažnju: `compound_statement` (blok) je vrsta iskaza - što znači da svuda gde se očekuje iskaz, može se staviti i blok.

### Složena naredba (blok), dodela i return

```yacc
compound_statement
    : _LBRACKET statement_list _RBRACKET
    ;

assignment_statement
    : _ID _ASSIGN num_exp _SEMICOLON
    ;

return_statement
    : _RETURN num_exp _SEMICOLON
    ;
```

Obratiti pažnju:

- **U bloku nije dozvoljena deklaracija.** Sve deklaracije moraju biti na početku funkcije, a ne unutar bloka.
- **Ne postoji void** - `return` iskaz mora sadržati numerički izraz. `return;` bez vrednosti je greška.

Primeri ispravnih iskaza dodele:

```c
a = b;
counter = 0;
line = line + 1;
c = j + (k - 4);
m = f();
```

Primeri ispravnih return iskaza:

```c
return 0;
return a + 1 - (d + 5);
return f3(a);
```

Neispravan return:

```c
return;  // GREŠKA: return iskaz mora sadržati izraz
```

Primeri ispravnih blokova:

```c
{ }
{ a = 8; }
{
    if (a == b)
        counter = 0;
    a = 10;
}
```

Neispravan blok - deklaracija unutar bloka:

```c
{
    int a;  // GREŠKA: u bloku se ne može deklarisati promenljiva
    a = 8;
}
```

### If naredba

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

If naredba može biti sa ili bez `else` dela. Uslov if iskaza u miniC jeziku sadrži relacioni izraz. Koriste se direktive `%nonassoc` i `%prec` u bisonu za rešavanje poznate dvosmislenosti "dangling else" - kada postoji ugnježđeni if bez else-a, bison mora da zna da li `else` pripada unutrašnjem ili spoljašnjem `if`-u. Ovim direktivama se obezbeđuje da se `else` uvek vezuje za najbliži `if`.

Primeri ispravnih if iskaza:

```c
if (a < b)
    a = b;

if (a < b) {
    a = b;
}

if (a == b)
    counter = counter + 1;
else
    counter = counter - 1;
```

### Numerički izrazi i poziv funkcije

```yacc
num_exp
    : exp
    | num_exp _AROP exp
    ;

exp
    : literal
    | _ID
    | function_call
    | _LPAREN num_exp _RPAREN
    ;

literal
    : _INT_NUMBER
    | _UINT_NUMBER
    ;
```

Numerički izraz (`num_exp`) se gradi od literala, promenljivih i poziva funkcija. Od aritmetičkih operacija, podržano je samo sabiranje i oduzimanje. Numerički izraz se može pisati i u malim zagradama.

Podsetnik: `num_exp` se pojavljuje u `assignment_statement` i `return_statement`.

Primeri ispravnih numeričkih izraza:

```c
a
0
line + 1
j + (k - 4)
f()
2 + f()
```

### Poziv funkcije i argument

```yacc
function_call
    : _ID _LPAREN argument _RPAREN
    ;

argument
    : /* empty */
    | num_exp
    ;
```

Poziv funkcije se sastoji od imena funkcije i malih zagrada u kojima se može, a ne mora, navesti jedan argument.

Primetiti rekurziju koja nije direktna:

```
num_exp -> exp -> function_call -> argument -> num_exp
```

Ova indirektna rekurzija omogućava da argument poziva funkcije bude složen numerički izraz koji i sam može sadržati pozive funkcija.

Primeri poziva:

```c
unsigned f0() { return 0u; }
int f1(int a) { return a + a; }

int f() {
    unsigned x;
    int y;
    x = f0();       // OK
    x = f0(5u);     // GREŠKA: f0 nema parametar
    y = f1();       // GREŠKA: f1 ima parametar
    y = f1(3);      // OK
}
```

### Relacioni izraz

```yacc
rel_exp
    : num_exp _RELOP num_exp
    ;
```

Podsetnik: `rel_exp` se pojavljuje u `if_part`. Relacije koje su podržane u miniC jeziku su: `<`, `>`, `<=`, `>=`, `==` i `!=`.

## Semantika miniC jezika

Semantika jezika opisuje značenje sintaksno ispravnih konstrukcija. Kod koji je sintaksno ispravan ne mora biti i semantički ispravan. Na primer, ako se poziva funkcija koja nije prethodno definisana, to predstavlja semantičku grešku.

### Standardni identifikatori

Standardni identifikatori su: rezervisane reči (`int`, `unsigned`, `if`, `else`, `return`) i identifikator `main`. Identifikator `main` je ime funkcije za koju se podrazumeva da je definisana u izvršivom miniC programu. Izvršavanje miniC programa započinje izvršavanjem `main` funkcije:

```c
int main() {
    ...
}
```

Ako telo `main` funkcije (kao i svake druge) ne sadrži `return` iskaz, podrazumeva se da je povratna vrednost funkcije nedefinisana i da do povratka iz funkcije dolazi po izvršavanju poslednjeg iskaza iz njenog tela.

### Opseg vidljivosti (scope)

Prema opsegu vidljivosti, identifikatori se razvrstavaju u globalne i lokalne.

**Globalni identifikatori** su imena funkcija. Oni su definisani na nivou programa (van funkcija). Opseg vidljivosti globalnih identifikatora je od mesta njihove definicije do kraja programskog teksta.

**Lokalni identifikatori** su imena lokalnih promenljivih i parametara i oni su definisani u okviru funkcija. Opseg vidljivosti lokalnih identifikatora je od mesta njihove definicije do kraja tela funkcije u kojoj su definisani. Svaka funkcija poseduje svoje lokalne promenljive.

Identifikatori mogu biti korišćeni samo iza njihove definicije (to proizlazi iz opsega njihovog važenja).

Može se desiti da se isto ime deklariše u nekoliko ugneždenih opsega vidljivosti. U tom slučaju, koristi se deklaracija imena koja je najbliža datoj upotrebi imena. Primer C iskaza:

```c
{
    int x = 1;   // prva promenljiva x
    int y = 2;
    {
        int x = 3;   // druga promenljiva x
        y += x;      // koristi se druga x (vrednost 3)
    }
    y += x;          // koristi se prva x (vrednost 1)
}
// y na kraju ima vrednost 6
```

### Jednoznačnost identifikatora

- Svi globalni identifikatori moraju biti međusobno različiti.
- Svi lokalni identifikatori iste funkcije moraju biti međusobno različiti.
- Ako postoje identični globalni i lokalni identifikatori neke funkcije, tada van te funkcije važe globalni, a unutar nje lokalni identifikatori.
- Lokalni identifikatori raznih funkcija mogu biti identični.
- Rezervisane reči smeju da se koriste samo u skladu sa svojom ulogom, i na globalnom i na lokalnom nivou.
- Standardni identifikator `main` je rezervisan samo na globalnom nivou.

### Provera tipova

Na upotrebu identifikatora utiče njegov tip. Pravila provere tipova u miniC-u su:

- Tip identifikatora sa leve strane iskaza pridruživanja određuje tip izraza sa desne strane - leva i desna strana iskaza pridruživanja moraju imati isti tip.
- Tip izraza iz `return` iskaza neke funkcije i tip te funkcije moraju biti identični.
- Tipovi korespondentnih parametara funkcije i argumenata iz njenog poziva moraju biti identični.
- Argumenti poziva funkcije moraju da se slažu po broju sa parametrima funkcije.
- U istom relacionom izrazu smeju biti samo identifikatori istog tipa.

## Kompletna miniC gramatika (BNF)

Gramatika miniC jezika u BNF notaciji, gde simboli (terminali) započinju donjom crtom `_` da bi se razlikovali od pojmova (neterminala):

### Leksički nivo (terminali)

```
_letter      ::= "a" | "A" | "b" | "B" | ... | "z" | "Z"
_digit       ::= "0" | "1" | "2" | ... | "9"
_identifier  ::= letter ( letter | digit )*
_int_literal ::= digit+
_uint_literal::= digit+ ( "u" | "U" )
```

### Sintaksni nivo (pojmovi)

```
program          ::= function_list
function_list    ::= function | function_list function
function         ::= type _identifier "(" param ")" body
type             ::= "int" | "unsigned"
param            ::= | type _identifier
body             ::= "{" variable_list stmt_list "}"
variable_list    ::= | variable_list variable
variable         ::= type _identifier ";"
stmt_list        ::= | stmt_list stmt
stmt             ::= compound_stmt | assignment_stmt | if_stmt | return_stmt
compound_stmt    ::= "{" stmt_list "}"
assignment_stmt  ::= _identifier "=" num_exp ";"
num_exp          ::= exp | num_exp "+" exp | num_exp "-" exp
exp              ::= literal | _identifier | function_call | "(" num_exp ")"
literal          ::= _int_literal | _uint_literal
function_call    ::= _identifier "(" argument ")"
argument         ::= | num_exp
if_stmt          ::= if_part | if_part "else" stmt
if_part          ::= "if" "(" rel_exp ")" stmt
rel_exp          ::= num_exp "<" num_exp | num_exp ">" num_exp
                   | num_exp "<=" num_exp | num_exp ">=" num_exp
                   | num_exp "==" num_exp | num_exp "!=" num_exp
return_stmt      ::= "return" num_exp ";"
```

Razmak i kraj linije imaju funkciju separatora simbola.

## Struktura micko kompajlera

Micko kompajler na GitHub-u ima faze razdvojene u zasebne direktorijume:

- **scanner** - leksička analiza (flex)
- **syntax** - sintaksna analiza (bison)
- **syntax-union** - sintaksa sa union tipom
- **syntax-w-conflict** - sintaksa sa prikazom konflikta
- **syntax-errors** - sintaksa sa obradom grešaka
- **semantic** - semantička analiza
- **code-gen** - generisanje koda (poslednja faza)
- **gramatika** - formalna gramatika miniC-a
- **hipsim-src** - izvorni kod hipotetskog simulatora
- **pymicko** - Python implementacija micko kompajlera

Faze su razdvojene tako da se svaka može proučavati i razvijati nezavisno, sa poslednjom fazom koja je generisanje koda (code-gen).