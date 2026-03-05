# Semantička analiza

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta je semantička analiza?

Semantika znači značenje. Semantička analiza proverava da li se poštuju pravila koja daju značenje programu. Dok sintaksna analiza proverava da li je program strukturno ispravan (da li su "rečenice" pravilno formirane), semantička analiza proverava da li program ima smisla.

Tipična pitanja koja semantička analiza rešava:

- Da li je promenljiva definisana pre korišćenja?
- Da li postoji `main()` funkcija?
- Da li je identifikator vidljiv u datom kontekstu?
- Da li su identifikatori jednoznačni?
- Da li su tipovi u izrazima odgovarajući?
- Da li su tipovi argumenata i parametara funkcije odgovarajući?

Semantička pravila se definišu neformalno, opisima i kroz primere. Za razliku od sintaksnih pravila koja su kontekstno slobodna (kontekstno nezavisna), semantička pravila više nisu kontekstno slobodna - zavise od konteksta u kome se konstrukcija pojavljuje. Postoje i formalne metode za opisivanje semantike (operaciona, aksiomska i denotaciona semantika), ali se u praksi najčešće koriste neformalni opisi.

## Ulaz za semantičku analizu

Postavlja se pitanje: šta je ulaz za semantičku analizu, tj. šta je rezultat parsiranja? Postoje dva pristupa:

1. **(Ništa eksplicitno)** - Semantička analiza, pa čak i generisanje koda, se može izvršiti u okviru parsera. Koriste se korisničke akcije u bison pravilima.
2. **(Struktura)** - Realizuje se posebna međureprezentacija, apstraktno sintaksno stablo (AST), čijim obilaskom se omogućava semantička analiza i generisanje koda.

## Semantičke vrednosti tokena i pojmova

Tokom parsiranja, preuzimaju se informacije, računaju se vrednosti i izvršavaju se određene akcije potrebne za naredne faze. Često se koriste izmenjene, proširene gramatike koje, pored sintaksne strukture, sadrže informacije potrebne za semantičku analizu i kasnije faze. Produkcijama se dodeljuju semantička pravila.

Na primer:

- evidentiraju se ili izračunavaju neke vrednosti (`x = 5`, `x = 2 + 3`)
- dodaju se informacije o tipovima (`int x`)
- izvršavaju se sporedni efekti (print, update global)

### Semantička vrednost tokena

Skener postavlja vrednost prilikom formiranja tokena. Na primer, leksema `"123"` postaje token `num` koji ima dodatnu (semantičku) vrednost `123`.

### Semantička vrednost pojma

Kada parser obradi pravilo kao `E -> E + num`, on postavlja vrednost pojma `E` sa leve strane na osnovu vrednosti tokena `num` i vrednosti pojma `E` sa desne strane (čija vrednost već postoji jer je ranije izračunata). Različiti izrazi mogu imati različite vrednosti. Neki tokeni i pojmovi ne moraju imati vrednosti.

## Pristup u micko kompajleru

U micko kompajleru koristi se bison sa korisničkim akcijama definisanim uz pravila gramatike. Ovakve akcije se koriste za proveru semantičkih zahteva, ali i za generisanje koda. Time se proces prevođenja završava u parseru. Ovo je jednostavno za implementaciju, ali ograničenih mogućnosti.

Nakon statičke semantičke analize, cilj je:

- Prihvatiti što više ispravnih programa
- Odbaciti što više neispravnih programa
- Skupiti još informacija potrebnih za generisanje koda

Time je završen prednji deo kompajlera (front-end) koji ne zavisi od ciljnog jezika. Nakon analize (leksička, sintaksna, semantička) dolazi na red sinteza (generisanje koda).

## Semantička pravila u miniC-u

### Opseg vidljivosti i važenja (scope)

- **Globalni identifikatori** su imena funkcija. Vidljivost: od mesta definicije do kraja programskog teksta.
- **Lokalni identifikatori** su definisani u okviru funkcija - to su parametri i lokalne promenljive. Vidljivost: od mesta definicije do kraja funkcije.
- Identifikatori mogu biti korišćeni samo nakon deklaracije.

### Jednoznačnost

- Svi globalni identifikatori moraju biti međusobno različiti.
- Svi lokalni identifikatori iste funkcije moraju biti međusobno različiti.
- Lokalni identifikatori raznih funkcija mogu biti identični.
- Lokalni identifikatori i globalni identifikatori mogu biti identični.
- Ako postoje identični globalni i lokalni identifikatori neke funkcije, tada van te funkcije važe globalni, a unutar nje lokalni identifikatori.
- Rezervisane reči smeju da se koriste samo u skladu sa svojom ulogom, i na globalnom i na lokalnom nivou.
- Standardni identifikator `main` je rezervisan samo na globalnom nivou.

### Tipovi

- Leva i desna strana iskaza dodele moraju imati isti tip.
- Tipovi parametara i odgovarajućih argumenata funkcije moraju biti identični.
- Tip izraza `return` iskaza neke funkcije i tip povratne vrednosti funkcije moraju biti identični.
- U istom relacionom izrazu identifikatori moraju biti istog tipa.
- Podrazumeva se da je tip literala `int` ako nije eksplicitno naznačeno da je tip `unsigned`.

## Tabela simbola

Tabela simbola (TS) je ključna struktura podataka u semantičkoj analizi. Sadrži informacije o identifikatorima (imenima) - njihove tipove, informacije o opsegu vidljivosti i druge atribute.

Termin "simbol" se ovde odnosi na konkretan identifikator u programu, a ne na token. Tabela simbola se izgrađuje i može se menjati u toku analize - kad se naiđe na ime, dodaje se u TS, kad se dobije nova informacija, može se menjati. Tabela se često pretražuje.

### Elementi tabele simbola u micko-u

Svaki element tabele simbola u micko kompajleru ima sledeća polja:

| Polje | Opis |
|-------|------|
| **name** | String simbola (leksema) |
| **kind** | Vrsta simbola: FUN (funkcija), VAR (promenljiva), PAR (parametar), LIT (literal), REG (registar) |
| **type** | Tip simbola: INT, UINT |
| **atr1** | Za lokalnu promenljivu: redni broj promenljive. Za parametar: redni broj parametra. Za funkciju: broj parametara. Za ostale: nije definisano. |
| **atr2** | Za funkcije: tip parametra. Za ostale: nije definisano. |

Registri i konstante se dodaju u tabelu radi uniformnosti. Inicijalizacija tabele rezerviše prvih n mesta za registre koji su prisutni sve vreme u tabeli. O registrima se govori kasnije jer zavise od ciljne arhitekture.

### Primer tabele simbola

Za sledeći kod:

```c
int f(unsigned p) {
    int a;
    unsigned b;
    b = 3u;
    b = b + p;
    a = 8;
}
```

Tabela simbola tokom analize funkcije `f` izgleda ovako:

| name | kind | type | atr1 | atr2 |
|------|------|------|------|------|
| f    | FUN  | INT  | 1    | UINT |
| p    | PAR  | UINT | 1    | -    |
| a    | VAR  | INT  | 1    | -    |
| b    | VAR  | UINT | 2    | -    |
| 3    | LIT  | UINT | -    | -    |
| 8    | LIT  | INT  | -    | -    |

Za funkciju `f`: `atr1 = 1` znači da ima 1 parametar, `atr2 = UINT` znači da je tip tog parametra `unsigned`. Za promenljive: `atr1` je redni broj promenljive (a je 1, b je 2).

### Još jedan primer

Za dva primera funkcija:

```c
int main() {
    int a;
}
```

| name | kind | type | atr1 | atr2 |
|------|------|------|------|------|
| main | FUN  | INT  | 0    | -    |
| a    | VAR  | INT  | 1    | -    |

```c
int main(int p) {
    int a;
    unsigned x;
}
```

| name | kind | type | atr1 | atr2 |
|------|------|------|------|------|
| main | FUN  | INT  | 1    | INT  |
| p    | PAR  | INT  | 1    | -    |
| a    | VAR  | INT  | 1    | -    |
| x    | VAR  | UINT | 2    | -    |

### Ponašanje tabele kao stek

Ceo prevodilac se realizuje u jednom prolazu, pa se i tabela simbola popunjava i koristi u skladu sa tim. Tabela se ponaša kao stek:

- Globalni identifikatori (imena funkcija) se dodaju u TS.
- Lokalni identifikatori se dodaju odmah nakon odgovarajućeg globalnog.
- Kada se završi prolaz kroz funkciju, lokalni identifikatori se brišu.

Na primer, za program:

```c
unsigned f(unsigned x) {
    return x + x;
}
int main() {
    unsigned a;
    a = f(5u);
    a = f(1u, a);   //error
}
```

Tabela simbola posle analize obe funkcije (lokalni identifikatori su obrisani):

| name | kind | type | atr1 | atr2 |
|------|------|------|------|------|
| f    | FUN  | UINT | 1    | UINT |
| main | FUN  | INT  | -    | -    |

Napomena: informacije o identifikatorima mogu biti potrebne i kasnije (za dijagnostiku), pa se ne sme raditi fizičko brisanje - elementi se logički označavaju kao neaktivni.

## Implementacija tabele simbola

### Definicije tipova i vrsta

```c
// defs.h
#define SYMBOL_TABLE_LENGTH 64

enum types { NO_TYPE, INT, UINT };

enum kinds { NO_KIND = 0x1, REG = 0x2, LIT = 0x4,
             FUN = 0x8, VAR = 0x10, PAR = 0x20 };
```

Primetimo da su vrednosti u `kinds` enumeraciji stepeni dvojke (bitmask). Ovo omogućava da se pri pretraživanju tabele traži više vrsta odjednom korišćenjem bitskog ILI operatora, na primer `VAR|PAR` traži i promenljive i parametre.

### Struktura elementa tabele

```c
// symtab.h
typedef struct sym_entry {
    char *name;      // ime simbola
    unsigned kind;   // vrsta simbola
    unsigned type;   // tip vrednosti simbola
    unsigned atr1;   // dodatni atribut simbola
    unsigned atr2;   // dodatni atribut simbola
} SYMBOL_ENTRY;

// symtab.c
SYMBOL_ENTRY symbol_table[SYMBOL_TABLE_LENGTH];
int first_empty = 0;
```

Tabela je implementirana kao niz fiksne dužine (64 elementa) sa indeksom koji pokazuje na prvi prazan element.

### Funkcije za rad sa tabelom simbola

```c
// Vraca indeks prvog sledeceg praznog elementa.
// Greska ako prekoracimo
int get_next_empty_element(void);

// Vraca indeks poslednjeg zauzetog elementa.
int get_last_element(void);

// Ubacuje novi simbol i vraca indeks ubacenog elementa
// ili -1 ako nema slobodnog elementa
int insert_symbol(char *name, unsigned kind, unsigned type,
                  unsigned atr1, unsigned atr2);

// Ubacuje konstantu u tabelu (ako vec ne postoji)
int insert_literal(char *str, unsigned type);

// Vraca indeks pronadjenog simbola ili -1
int lookup_symbol(char *name, unsigned kind);
```

Važne napomene:

- `insert_symbol` ubacuje simbol (informaciju o identifikatoru - promenljiva, funkcija, parametar). Koristi `get_next_empty_element` i postavlja vrednosti. **Ne proverava se ovde da li već postoji taj identifikator u tabeli** - to je zadatak procesa analize, ovo je samo struktura podataka.
- `insert_literal` proverava da li već postoji simbol u tabeli. Literal ne nosi mnogo semantičkih informacija, samo vrednost i tip. Nema potrebe da unosimo istu konstantu nekoliko puta. Dodatno ima i proveru opsega.
- `lookup_symbol` pretražuje tabelu po imenu i vrsti i vraća indeks ili -1 (`NO_INDEX`).

### Set i get metode

```c
void set_name(int index, char *name);
char* get_name(int index);
void set_kind(int index, unsigned kind);
unsigned get_kind(int index);
void set_type(int index, unsigned type);
unsigned get_type(int index);
void set_atr1(int index, unsigned atr1);
unsigned get_atr1(int index);
void set_atr2(int index, unsigned atr2);
unsigned get_atr2(int index);
```

### Funkcije za upravljanje životnim ciklusom

```c
// Inicijalizacija tabele - koristi se pre parsiranja
void init_symtab(void);

// Brise sve elemente tabele - koristi se posle parsiranja
void clear_symtab(void);

// Brise elemente tabele od zadatog indeksa
// Koristi se kad se zavrsi parsiranje funkcije
void clear_symbols(unsigned begin_index);

// Ispisuje sve elemente tabele
void print_symtab(void);
```

## Semantičke vrednosti u bisonu - %union i tipovi

Semantičke vrednosti naravno imaju tip. Podrazumevani tip je `int`, ali to često nije dovoljno jer nam trebaju različiti tipovi za različite tokene i pojmove.

### Problem

U flex-u, semantička vrednost tokena se postavlja preko globalne promenljive `yylval`:

```c
"int"                 { yylval... = INT; return _TYPE; }
"+"                   { yylval... = ADD; return _AROP; }
[a-zA-Z][a-zA-Z0-9]* { yylval... = strdup(yytext); return _ID; }
```

Potrebno nam je da nekad tip bude `int` (za TYPE, AROP), a nekad `string` (za ID, brojeve).

### Rešenje: %union deklaracija

`%union` deklaracija definiše sve moguće tipove semantičkih vrednosti (odgovara C uniji):

```c
%union {
    int i;
    char *s;
}
```

Zatim se za svaki token i pojam definiše koji tip koristi:

**U bison fajlu (minic.y):**

```yacc
%union {
    int i;
    char *s;
}

%token <i> _TYPE
%token <s> _ID
%token <s> _INT_NUMBER
%token <s> _UINT_NUMBER
%token <i> _AROP
%token <i> _RELOP

%type <i> num_exp exp literal function_call argument rel_exp
```

**U flex fajlu (minic.l):**

```c
"int"                 { yylval.i = INT; return _TYPE; }
"+"                   { yylval.i = ADD; return _AROP; }
[a-zA-Z][a-zA-Z0-9]* { yylval.s = strdup(yytext); return _ID; }
```

Sada se pristupa odgovarajućem polju unije (`yylval.i` ili `yylval.s`) u zavisnosti od tipa tokena.

### Semantičke vrednosti pojmova u akcijama

U bison akcijama:

- `$$` - semantička vrednost pojma sa leve strane pravila (kome se dodeljuje vrednost)
- `$n` - semantička vrednost n-te komponente u pravilu (sa desne strane)
- Ukoliko nema dodele u akciji, podrazumevano je `$$ = $1` (osim u slučaju praznog pravila - tada je nedefinisano)

```yacc
exp
    : literal
    | _ID
      {
          $$ = ...
      }
    | function_call
    | _LPAREN num_exp _RPAREN
      { $$ = $2; }
    ;
```

### Mid-rule akcije

Akcije su obično na kraju pravila, ali ne moraju biti. Mogu se staviti i u sredinu pravila (mid-rule action). Ove akcije se računaju kao komponente prilikom referenciranja za dobijanje semantičkih vrednosti:

```yacc
pojam
    : prvi_deo_pravila
      {
          $<i>$ = ...    // akcija 1
      }
      drugi_deo_pravila
      {
          ...$<i>n...   // pristup vrednosti iz akcije 1
          $$ = ...       // akcija 2
      }
    ;
```

Važna pravila za mid-rule akcije:

- Semantičkoj vrednosti akcije (1) se pristupa preko `$<tip>$` - mora se navesti tip jer nemamo definisano kog tipa je ta akcija (za razliku od tokena i pojmova)
- U akciji (2) možemo pristupiti vrednosti akcije (1) preko `$<tip>n`
- U akciji (1) ne možemo koristiti `$$` za postavljanje vrednosti celog pravila
- Samo poslednju akciju (2) možemo iskoristiti za postavljanje vrednosti celog pravila

## Implementacija semantičkih pravila

Semantička pravila se implementiraju prilikom parsiranja, u akcijama pravila u `.y` fajlu, koristeći tabelu simbola. Koriste se sledeće pomoćne promenljive:

```c
int var_num = 0;      // Broj identifikatora u trenutnom opsegu (funkciji)
int fun_idx = -1;     // Indeks simbola funkcije koja se trenutno parsira
int fcall_idx = -1;   // Indeks simbola funkcije čiji poziv parsiramo
```

### Pravilo: svi lokalni identifikatori iste funkcije moraju biti međusobno različiti

```yacc
variable
    : _TYPE _ID _SEMICOLON
      {
          if(lookup_symbol($2, VAR|PAR) == NO_INDEX)
              insert_symbol($2, VAR, $1, ++var_num, NO_ATR);
          else
              err("redefinition of '%s'", $2);
      }
    ;
```

Kada se naiđe na deklaraciju promenljive, prvo se proverava da li već postoji promenljiva ili parametar sa istim imenom (`lookup_symbol` sa `VAR|PAR` - bitski OR koji pretražuje i VAR i PAR). Ako ne postoji, dodaje se u tabelu. Ako postoji, prijavljuje se greška o redefiniciji.

### Pravilo: svi globalni identifikatori moraju biti međusobno različiti + brisanje lokalnih

```yacc
function
    : _TYPE _ID
      {
          fun_idx = lookup_symbol($2, FUN);
          if(fun_idx == NO_INDEX)
              fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
          else
              err("redefinition of function '%s'", $2);
      }
      _LPAREN parameter _RPAREN body
      {
          clear_symbols(fun_idx + 1);
          var_num = 0;
      }
    ;
```

Ovde vidimo mid-rule akciju. Prva akcija (posle `_ID`) proverava da li funkcija sa tim imenom već postoji i ubacuje je u tabelu. `atr1` i `atr2` se postavljaju na `NO_ATR` jer ih još ne znamo (biće postavljeni u pravilu za `parameter`). Druga akcija (posle `body`) briše sve lokalne simbole koji su dodati posle funkcije (`clear_symbols(fun_idx + 1)`) i resetuje brojač promenljivih.

### Pravilo: parametar funkcije

```yacc
parameter
    : /* empty */
      { set_atr1(fun_idx, 0); }
    | _TYPE _ID
      {
          insert_symbol($2, PAR, $1, 1, NO_ATR);
          set_atr1(fun_idx, 1);
          set_atr2(fun_idx, $1);
      }
    ;
```

Ovde se ne realizuje nijedno sintaksno pravilo - samo se menja tabela simbola. Za prazan parametar, postavljamo `atr1` funkcije na 0 (nema parametara). Za parametar sa tipom i imenom, ubacujemo element za parametar i ažuriramo element za funkciju: `atr1` postaje 1 (ima 1 parametar), `atr2` postaje tip parametra.

### Pravilo: identifikator mora biti deklarisan pre upotrebe

```yacc
assignment_statement
    : _ID _ASSIGN num_exp _SEMICOLON
      {
          int idx = lookup_symbol($1, VAR|PAR);
          if(idx == NO_INDEX)
              err("invalid lvalue '%s' in assignment", $1);
          else
              if(get_type(idx) != get_type($3))
                  err("incompatible types in assignment");
      }
    ;
```

Sa leve strane dodele može biti samo identifikator koji se odnosi na promenljivu ili parametar. Ako `lookup_symbol` ne pronađe identifikator, prijavljuje se greška. Takođe se proverava kompatibilnost tipova.

Za korišćenje identifikatora u izrazu:

```yacc
exp
    : literal
    | _ID
      {
          $$ = lookup_symbol($1, VAR|PAR);
          if($$ == NO_INDEX)
              err("'%s' undeclared", $1);
      }
    | function_call
    | _LPAREN num_exp _RPAREN
      { $$ = $2; }
    ;
```

Semantička vrednost `exp` je indeks u tabeli simbola. Za `_ID`, preuzimamo indeks tog identifikatora (jer tamo je informacija o tipu). Za zagrade, preuzimamo vrednost od `num_exp`. Za `literal` i `function_call`, oni sami postavljaju vrednost.

### Pravilo: tipovi moraju biti odgovarajući

Za aritmetičke i relacione izraze:

```yacc
num_exp
    : exp
    | num_exp _AROP exp
      {
          if(get_type($1) != get_type($3))
              err("invalid operands: arithmetic operation");
      }
    ;

rel_exp
    : num_exp _RELOP num_exp
      {
          if(get_type($1) != get_type($3))
              err("invalid operands: relational operator");
      }
    ;
```

Oba operanda moraju biti istog tipa. `get_type($1)` i `get_type($3)` rade jer su semantičke vrednosti `num_exp` i `exp` indeksi u tabeli simbola, pa `get_type` može da preuzme tip iz tabele.

### Literal

```yacc
literal
    : _INT_NUMBER
      { $$ = insert_literal($1, INT); }
    | _UINT_NUMBER
      { $$ = insert_literal($1, UINT); }
    ;
```

Literal se ubacuje u tabelu simbola (ako već ne postoji) i vraća se indeks. Podrazumevani tip je `INT` ako nije eksplicitno `UINT`.

### Return iskaz

```yacc
return_statement
    : _RETURN num_exp _SEMICOLON
      {
          if(get_type(fun_idx) != get_type($2))
              err("incompatible types in return");
      }
    ;
```

Tip izraza u `return` iskazu mora odgovarati tipu povratne vrednosti funkcije (koji se čuva u tabeli simbola pod indeksom `fun_idx`).

### Poziv funkcije

```yacc
function_call
    : _ID
      {
          fcall_idx = lookup_symbol($1, FUN);
          if(fcall_idx == NO_INDEX)
              err("'%s' is not a function", $1);
      }
      _LPAREN argument _RPAREN
      {
          if(get_atr1(fcall_idx) != $4)
              err("wrong number of args to function '%s'",
                  get_name(fcall_idx));
          set_type(FUN_REG, get_type(fcall_idx));
          $$ = FUN_REG;
      }
    ;
```

Ovde se dešava nekoliko stvari:

- Prvo se proverava da li identifikator postoji kao funkcija.
- Zatim se proverava da li broj argumenata odgovara broju parametara (`get_atr1` vraća broj parametara).
- `FUN_REG` je 13 (definisano u `defs.h`) - u hipotetskom asembleru registar 13 će biti registar za povratnu vrednost iz funkcije.
- U tabeli simbola čuvamo samo tipove sadržaja koji se nalaze u odgovarajućim registrima.
- Zašto `$4` a ne `$3`? Zato što mid-rule akcija postaje komponenta - akcija je `$2`, `_LPAREN` je `$3`, `argument` je `$4`.

### Argument poziva funkcije

```yacc
argument
    : /* empty */
      { $$ = 0; }
    | num_exp
      {
          if(get_atr2(fcall_idx) != get_type($1))
              err("incompatible type for argument in '%s'",
                  get_name(fcall_idx));
          $$ = 1;
      }
    ;
```

Semantička vrednost argumenta je broj argumenata (0 ili 1). Proverava se i da li tip argumenta odgovara tipu parametra funkcije (`get_atr2` vraća tip parametra).

### Provera da postoji main()

```yacc
program
    : function_list
      {
          if(lookup_symbol("main", FUN) == NO_INDEX)
              err("undefined reference to 'main'");
      }
    ;
```

Na samom kraju parsiranja celog programa proverava se da li postoji funkcija `main`. Ovo je poslednja semantička provera.

### Pojmovi bez semantičkih akcija

Sledeći pojmovi ne zahtevaju dodatne semantičke akcije jer su čisto strukturni: `function_list`, `body`, `variable_list`, `statement_list`, `statement`, `compound_statement`, `if_statement`, `if_part`.

## Rezime toka semantičke analize

1. Inicijalizuje se tabela simbola (`init_symtab`)
2. Parsiranje počinje - bison poziva `yyparse()`
3. Za svaku funkciju: dodaje se u TS, obrađuje se parametar, obrađuju se lokalne promenljive, proveravaju se iskazi, na kraju se brišu lokalni simboli
4. Za svaki identifikator u izrazu: proverava se da li postoji u TS
5. Za svaki operator: proverava se kompatibilnost tipova operanada
6. Za svaku dodelu: proverava se da leva strana postoji i da su tipovi kompatibilni
7. Za svaki return: proverava se kompatibilnost sa tipom funkcije
8. Za svaki poziv funkcije: proverava se da funkcija postoji, da je broj argumenata ispravan i da su tipovi kompatibilni
9. Na kraju programa: proverava se da `main` postoji
10. Čisti se tabela simbola (`clear_symtab`)