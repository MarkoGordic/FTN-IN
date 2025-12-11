# Skripta – Programski prevodioci (miniC)

Predmet: Programski prevodioci  
Program: Informacioni inženjering 2024/2025  
Autor: Marko Gordić

> [!NOTE]  
> Skripta je napravljenja uz pomoć predavanja, vežbi i zbirke za miniC. Moguće su greške, poželjno je korišćenje skripte uz zvanične materijale.

# Sadržaj

1. **Leksika i sintaksa miniC-a**  
2. **Mićko i faze kompajliranja**  
3. **Leksička analiza (flex)**  
4. **Sintaksna analiza (bison)**  
5. **Semantička analiza i tabela simbola**  

# 1. Leksika i sintaksa miniC-a

## 1.1 Leksika

- Leksika se bavi opisivanjem osnovnih gradivnih elemenata jezika.  
- String simbola zove se **leksema** (instanca tokena).  
- Skup leksema i pravila njihovog formiranja predstavlja leksiku jezika.  
- Identifikator u miniC je pojednostavljen u odnosu na C: sastoji se od malih slova, velikih slova i cifara, i ne sme započinjati cifrom.  
- Ispravni primeri: `a`, `A`, `abc`, `number`, `Number`, `MyNumber`, `num2`, `num2str`; neispravni: `3a`, `_x`, `my_number`.  

## 1.2 Sintaksa

- Najmanji miniC program mora imati makar jednu funkciju. Svaki miniC program mora imati `main` sa povratnim tipom `int`.  
- miniC podržava dva tipa podataka: `int` i `unsigned`.  
- Moguća je samo jedna deklaracija promenljive odjednom (nije dozvoljeno `int a, b;`).  
- Funkcije se sastoje od tipa, imena, zagrada i jednog opcionog parametra unutar zagrada.  
- Funkcija može imati prazno telo.  
- Telo funkcije: prvo deklaracije lokalnih promenljivih, pa iskazi; deklaracija posle iskaza nije ispravna.  
- Iskazi u telu: `if`, `return`, iskaz dodele i blok iskaza.  
- Od aritmetičkih operacija podržano je samo sabiranje i oduzimanje.  
- Unutar blokova nije moguće deklarisati promenljivu (greška).  
- Linijski komentari počinju sa `//` i važe do `\n`.  

# 2. Mićko i faze kompajliranja

## 2.1 Mićko

- Faze kompajliranja: leksička analiza → sintaksna analiza → semantička analiza → generisanje koda.  
- Sve faze koriste **tabelu simbola** (čuva podatke o svim simbolima prepoznatim tokom kompajliranja).  
- Vrste grešaka koje Mićko može javiti:  
  - Leksičke (npr. pogrešno napisano ime, ključna reč ili operator)  
  - Sintaksne (npr. relacioni izraz sa nepotpunim parom zagrada)  
  - Semantičke (npr. operator primenjen na nekompatibilni operand)  

# 3. Leksička analiza (flex)

## 3.0 miniC skener – pravila

```c
[ \t\n]+             { /* skip */ }

"int"                { yylval.i = INT;  return _TYPE; }
"unsigned"           { yylval.i = UINT; return _TYPE; }
"if"                 { return _IF; }
"else"               { return _ELSE; }
"return"             { return _RETURN; }

"("                  { return _LPAREN; }
")"                  { return _RPAREN; }
"{"                  { return _LBRACKET; }
"}"                  { return _RBRACKET; }
";"                  { return _SEMICOLON; }
"="                  { return _ASSIGN; }
","                  { return _COMMA; }

"+"                  { yylval.i = ADD; return _AROP; }
"-"                  { yylval.i = SUB; return _AROP; }

"<"                  { yylval.i = LT; return _RELOP; }
">"                  { yylval.i = GT; return _RELOP; }
"<="                 { yylval.i = LE; return _RELOP; }
">="                 { yylval.i = GE; return _RELOP; }
"=="                 { yylval.i = EQ; return _RELOP; }
"!="                 { yylval.i = NE; return _RELOP; }

[a-zA-Z][a-zA-Z0-9]* { yylval.s = strdup(yytext); 
                       return _ID; }
[+-]?[0-9]{1,10}     { yylval.s = strdup(yytext); 
                       return _INT_NUMBER;}
[0-9]{1,10}[uU]      { yylval.s = strdup(yytext); 
                       yylval.s[yyleng-1] = 0;
                       return _UINT_NUMBER;}

\/\/.*               { /* skip */ }
.                    { printf("line %d: LEXICAL ERROR on char %c\n", yylineno, *yytext);}
```

## 3.1 Leksička analiza

- Leksički analizator nosi ime skener.  
- Kada skener naiđe na simbol koji nije prepoznat treba da izbaci leksičku grešku.  
- Na predmetu koristimo program za generisanje skenera **flex**.  
- Specifikaciju pravila koje koristi flex definiše korisnik u specijalnoj `.l` datoteci; sadrži reči koje skener treba da prepozna.  
- Specifikacija se sastoji od regularnih izraza koje skener treba da prepozna i akcija koje treba da se izvrše kada se izraz prepozna; obična akcija je vraćanje tokena za taj simbol.  
- Token je numerička oznaka klase (vrste) simbola.  
- Ako skener ne prepozna nijedan simbol u prosleđenom tekstu, default akcija je ispisivanje unetog teksta na standardni izlaz.  
- Skener se nalazi u datoteci `lex.yy.c` u sklopu funkcije `yylex()`.  

## 3.2 miniC skener

- miniC prepoznaje operatore `>`, `<`, `<=`, `>=`, `!=`.  
- miniC **ne prepoznaje** logičke operatore `&&`, `||` ili `!`; pojava istih generiše leksičku grešku.  
- miniC ima token `LITERAL`, a nema token `CONSTANT`.  
- Obratiti pažnju kod regularnih izraza: `[a,b]+` traži string jedne ili više pojava karaktera `a`, `b` ili zareza (`,`); zarez nema specijalno značenje.  
- `noyywrap` znači da će skener skenirati samo jednu datoteku.  
- `yylineno` koristi globalnu flex promenljivu sa brojem trenutno skenirane linije.  
- Kada se uz token šalje dodatni podatak (npr. uz `NUMBER` i string “123”), koristi se unija `yylval` (sadrži `int` i `char*`).  
- U miniC-u se za brojeve tipa `int` i `uint` vezuje token `_TYPE`; uz njega se dodatno šalju vrednosti `INT` ili `UINT` kroz `yylval`.  
- Prepoznati string je u `yytext`, dužina je u `yyleng`.  
- Skener je osetljiv na redosled pravila: ključne reči stavljamo iznad pravila za identifikator.  
- Simbol `.` označava bilo koji znak osim `\n`; služi da prepozna leksičku grešku (bilo koji znak koji ne pripada prethodnim pravilima).  

# 4. Sintaksna analiza (bison)

## 4.1 Sintaksna analiza

- Sintaksa jezika opisuje pravila po kojima se kombinuju simboli jezika.  
- Sintaksa se opisuje gramatikom, obično pomoću BNF notacije.  
- Proces sintaksne analize vrši parser i zove se parsiranje.  
- Koristimo generator parsera **bison**.  
- Specifikaciju koju koristi bison definišemo u `.y` datoteci; sadrži gramatiku koju parser prepoznaje.  
- `.y` se prosleđuje bison-u koji generiše C parser u funkciji `yyparse()` u `y.tab.c`.  
- Napomena: `statement` uključuje i `compound_statement`.  
- Pojam body je napravljen tako da se u njemu prvo moraju naci deklaracije promenljivih, pa tek onda statementi
  ```c
  body
    : _LBRACKET variable_list statement_list _RBRACKET
    ;
  ```

## 4.2 miniC parser

- Globalna promenljiva `yylval` je unija sa `int` (i) i `char*` (s).  
- Tokeni koje parser prima od skenera moraju biti definisani pomoću `%token`.  
- Bez oporavka od grešaka parser staje na prvoj sintaksnoj grešci.  

# 5. Semantička analiza i tabela simbola

## 5.1 Semantička analiza

- Semantička analiza je faza kompajliranja u kojoj se proverava značenje koda.  
- Najčešće se implementira u parseru, tako što se pravilima dodaju semantičke provere.  
- miniC ne prepoznaje tip `void`, pa se `function_call` vodi kao tip `<i>`; funkcija uvek mora vratiti `int` ili `unsigned`.  
- Pri brisanju lokalnih simbola posle funkcije zovemo `clear_symbols(fun_idx + 1)` da očuvamo ime funkcije (globalno, koristi se tokom obrade celog programa).  
- miniC parser je **LR** (bottom-up): gradi stablo od listova ka korenu; ulaz čita sleva nadesno i koristi desno izvođenje na gore.  
- Svi tokeni koji u deklaraciji imaju `<i>` ili `<s>` očekuju semantičku vrednost kojoj pristupamo sa `$1`, `$2`, …; samom pojmu dodeljujemo vrednost kroz `$$` u akciji pravila.  

## 5.2 Organizacija memorije u miniC-u

- Globalni identikatori su statični: postoje za sve vreme izvršavanja programa i mogu se rezervisati pri kompajliranju.  
- Lokalni identifikatori su dinamični: postoje samo dok se izvršava trenutna funkcija, čuvaju se na steku i brišu se kada više nisu potrebni.  

## 5.3 Tabela simbola

- Tabela simbola je struktura podataka koja čuva identifikatore iz kompajliranog programa i informacije o njima.  
- Vrste simbola: `NO_KIND`, `REG`, `LIT`, `FUN`, `VAR`, `PAR`.  
- Polja jednog elementa:  
  - `name` – string identifikator imena  
  - `kind` – vrsta simbola  
  - `type` – tip (`TYPE_INT`, `TYPE_UINT`)  
  - `atr1` – različito u odnosu na tip:  
    - lokalna promenljiva → redni broj promenljive  
    - funkcija → broj parametara  
    - parametar → redni broj parametra  
    - ostali → prazno  
  - `atr2` – za funkciju čuva tip parametra  
- Ubacivanje simbola:  

```c
int insert_symbol(char *name, unsigned kind, unsigned type, unsigned atr1, unsigned atr2);
```

- Ubacivanje literala:  

```c
int insert_literal(char *str, unsigned type);
```

- `yyerror()` i `warning()` služe za prijavu grešaka i upozorenja.  

## 5.4 Pronalaženje simbola i pristup atributima

Pronalaženje simbola u tabeli simbola obavlja se sledećom funkcijom:

```c
// vraća indeks pronađenog simbola ili -1 ako ga nema
int lookup_symbol(char *name, unsigned kind);
```

Po pronalaženju simbola, moguće je pristupiti željenim kolonama preko `get` i `set` funkcija:

```c
// set/get nad indeksom iz lookup_symbol
void set_name(int idx, char *name);
char* get_name(int idx);
void set_kind(int idx, unsigned kind);
unsigned get_kind(int idx);
void set_type(int idx, unsigned type);
unsigned get_type(int idx);
void set_atr1(int idx, unsigned atr1);
unsigned get_atr1(int idx);
void set_atr2(int idx, unsigned atr2);
unsigned get_atr2(int idx);
```