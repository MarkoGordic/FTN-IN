# Sintaksna analiza

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta je sintaksna analiza?

Sintaksna analiza je druga faza prevođenja, odmah nakon leksičke analize. Dok je leksička analiza odgovorna za razbijanje ulaznog teksta na tokene, sintaksna analiza (parsiranje) proverava da li je ulazni niz tokena formiran na osnovu pravila po kojima se grade konstrukcije u programskom jeziku. Drugim rečima, ako je skeniranje konstruisanje reči od karaktera, onda je parsiranje konstruisanje rečenica od reči.

Šematski, tok izgleda ovako:

```
string --> [Leksička pravila] --> tokeni --> [Sintaksna pravila] --> parse tree / AST + greške
```

Parser na ulazu prima tokene (iz skenera), a na izlazu daje potvrdu da je program sintaksno ispravan ili prijavljuje greške. Opciono, parser može proizvesti parse stablo (parse tree) ili apstraktno sintaksno stablo (AST) kao internu reprezentaciju strukture programa.

## Greške u sintaksnoj analizi

Šta bi bila greška u sintaksnoj analizi? To zavisi od toga kako definišemo pravila našeg jezika. Pogledajmo sledeći primer:

```c
if x == 5
{
    y 3 //komentar
}
```

Ako naš jezik definiše da:

- uslov u `if` naredbi mora biti u zagradama - onda je `if x == 5` greška jer nedostaju zagrade
- nijedna konstrukcija u jeziku nema oblik `<identifikator> <broj>` - onda je `y 3` greška
- svaki iskaz mora imati `;` na kraju - onda je i to greška

Važno je napomenuti da razmatranje tipa promenljive `x` (da li je `x` uopšte broj i da li sme da se vrši takvo poređenje) ne pripada sintaksnoj analizi. To je posao sledeće faze - semantičke analize (type checking).

## Odluke koje treba doneti

Prilikom dizajniranja parsera, potrebno je doneti nekoliko ključnih odluka:

- Koje tokene ćemo prepoznavati?
- Koji tokeni imaju vrednosti?
- Kako skener i parser komuniciraju, kako se preuzimaju tokeni?
- Kako definisati pravila sintakse?
- Kako implementirati parser (sintaksni analizator)?
- Koje strukture podataka ćemo koristiti?

## Implementacija parsera

Osnovni algoritam parsera je:

- čitamo tokene sa ulaza
- nekako proveravamo da li su raspoređeni pravilno
- informišemo o rezultatu (ok ili greška)

Postoje tri osnovna pristupa implementaciji:

1. **Ručno, proizvoljno** - bez formalizacije, pisanjem koda koji direktno proverava strukturu
2. **Ručno + formalizacija pravila** - koristimo formalnu gramatiku kao vodilju, ali parser pišemo sami
3. **Alat + formalizacija pravila** - koristimo alat (poput bisona) koji na osnovu formalne gramatike automatski generiše parser

Ključna teorijska činjenica je da leksika programskih jezika predstavlja regularan jezik, dok velik deo sintakse programskih jezika predstavlja kontekstno slobodan jezik. Ovo znači da su za sintaksnu analizu potrebni moćniji formalizmi i alati nego za leksičku analizu.

### Problemi koji se pojavljuju

Bez obzira na pristup, pojavljuju se određeni problemi: dvosmislenost gramatike, konflikti prilikom parsiranja, prioritet operacija, obrada grešaka i drugi.

### Šta je ulaz za sledeću fazu?

Postavlja se pitanje šta je ulaz za semantičku analizu. Postoje dve opcije:

- **Ništa eksplicitno** - sve se radi paralelno, odmah se utvrđuje da li je i sintaksno i semantički sve u redu (sintaksna i semantička analiza se prepliću).
- **Interna struktura** - realizuje se neka interna struktura (poput AST-a) na osnovu koje se može lako utvrditi da li važe semantička pravila.

## Formalno opisivanje sintakse

Da bismo mogli formalno da opišemo pravila strukture koda napisanog u programskom jeziku, koristimo gramatike. Ideja je sledeća:

```
naredbe = if_naredba ili for_naredba ili naredba_dodele
if_naredba = if (uslov) naredbe else naredbe
...
```

### BNF (Backus-Naur) forma

Pravila sintakse programskih jezika se često navode u BNF formi. BNF koristi dva tipa simbola:

- **Terminali (simboli)** - konkretne "reči" jezika, tokeni. Terminali su završni elementi - nema daljih produkcija. Terminali se ne mogu naći sa leve strane pravila.
- **Neterminali (pojmovi)** - apstraktne kategorije koje se dalje razlažu pravilima. U BNF notaciji se navode koristeći `<` i `>`.

Oznaka `::=` je oznaka za pravilo izvođenja (produkciju).

Primer BNF gramatike:

```
<assignment statement> ::= <variable> = <expression>
<expression> ::= <term>
<expression> ::= <expression> + <term>
<term> ::= ...
```

### Alternativni zapisi

Zapisi gramatike mogu izgledati i drugačije:

- Izostavljaju se `<>`, ali se nekako pravi razlika između pojmova i simbola (na primer, pojmovi se pišu kurzivom)
- Koristi se `->` umesto `::=`
- Koristi se `:=` umesto `::=`
- `|` se koristi za alternative (umesto navođenja posebnih pravila)

Na primer:

```
assignment statement -> variable = expression
expression -> term | expression + term
term -> ...
```

### Primer: gramatika za vreme

Pogledajmo konkretan primer gramatike koja opisuje format vremena:

```
time    -> hour ":" minute
         | hour ":" minute ":" second

hour    -> 2DIGIT
minute  -> 2DIGIT
second  -> 2DIGIT

2DIGIT  -> DIGIT DIGIT
DIGIT   -> "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

U ovoj gramatici:

- **Pojmovi (neterminali)** su: time, hour, minute, second, 2DIGIT, DIGIT
- **Simboli (terminali)** su: "0", "1", "2", ..., "9", ":"

Važna napomena: `2DIGIT` i `DIGIT` bi mogli biti tokeni prepoznati u leksičkoj analizi na osnovu druge gramatike (gramatike leksike, regularnih izraza). Tada bi oni bili terminali za tu gramatiku. Ovo ilustruje fundamentalnu razliku između skenera i parsera: skener radi sa azbukom karaktera, a parser radi sa azbukom tokena.

### Primer: gramatika za tekst na srpskom

Pogledajmo gramatiku koja opisuje jednostavan tekst na srpskom jeziku:

```
text
    -> sentence
    -> text sentence

sentence
    -> words dot

words
    -> capital_word
    -> words word
    -> words capital_word

word
    -> small_letter
    -> word small_letter

capital_word
    -> capital_letter
    -> capital_word small_letter

dot
    -> "."

capital_letter
    -> "A" | "B" | "C" | ... | "Z"

small_letter
    -> "a" | "b" | "c" | ... | "z"
```

U ovoj gramatici, tokeni (terminali) su individualna slova i tačka, a pojmovi (neterminali) su `text`, `sentence`, `words`, `word`, `capital_word`, `dot`.

Koji su ispravni ulazi prema ovoj gramatici?

```
Danas pada kiša.    OK
pada.               ERR  (rečenica mora početi velikim slovom)
kiša pada           ERR  (nedostaje tačka na kraju)
```

Zanimljivo pitanje: šta bi još mogli biti tokeni? Umesto da skener prepoznaje individualna slova, mogli bismo definisati da skener prepoznaje cele reči (`capital_word` i `word`) - u tom slučaju bi gramatika parsera bila jednostavnija, a složenost bi se prebacila na skener.

### Proširene BNF forme (EBNF)

Proširene BNF forme dodaju dodatne oznake za veću izražajnost:

- `[ ... ]` - ponavljanje sadržaja 0 ili 1 put (opciono)
- `{ ... }` - ponavljanje sadržaja 0 ili više puta
- `( ... )` - grupisanje
- Nekad: `,` za konkatenaciju, `;` za kraj pravila
- Nekad: `*`, `+`, `?` (slično regularnim izrazima)

Na primer, gornja gramatika za tekst bi u EBNF formi izgledala ovako:

```
text
    -> sentence { sentence }

sentence
    -> words dot

words
    -> capital_word { ( word | capital_word ) }

word
    -> small_letter { small_letter }

capital_word
    -> capital_letter { small_letter }

dot
    -> "."
```

Ovo je kompaktniji zapis koji je lakši za čitanje, ali opisuje isti jezik.

## Kako napisati parser?

Parser je algoritam kojim možemo za bilo koji ulaz da kažemo:

- našli smo izvođenje prateći pravila (parsiranje je uspešno) ILI
- ne postoji nijedno izvođenje (sintaksna greška)

Pogledajmo konkretan primer. Za ulaz "Ovo je tekst." i gramatiku sa tokenima `CAPITAL_WORD`, `WORD` i `DOT`, niz tokena je:

```
CAPITAL_WORD  WORD  WORD  DOT  EOF
```

Parser treba da utvrdi da li ovaj niz tokena može da se izvede iz početnog pojma `text` primenom pravila gramatike.

## Dva osnovna tipa parsera

### Silazno parsiranje (top-down)

Kod silaznog parsiranja pokušavamo da od početnog pojma izvedemo ulazni niz simbola prateći pravila produkcije. Akcija je: leva strana pravila se zamenjuje desnom.

Najčešća implementacija silaznog parsiranja je **rekurzivni spust** (recursive descent parser). Karakteristike rekurzivnog spusta:

- Postoji funkcija za svaki pojam (neterminal) odgovorna za obradu tog pojma
- Početna funkcija odgovara početnom pojmu i ona poziva odgovarajuće funkcije (za pojmove sa desne strane pravila)
- Funkcije su rekurzivne zbog rekurzivne prirode gramatike programskih jezika
- Algoritam je intuitivan i relativno jednostavan za direktnu implementaciju (ručno)

Na primer, za gramatiku:

```
text
    -> sentence
    -> text sentence
```

Imali bismo funkciju `parse_text()` koja poziva `parse_sentence()`, a `parse_sentence()` poziva odgovarajuće funkcije za svoje pod-pojmove.

#### Problemi silaznog parsiranja

Silazno parsiranje ima svoje probleme:

- **Alternative** - šta raditi kad postoji više alternativa? Potrebno je odrediti heuristiku za izbor ispravne alternative.
- **Greške** - šta se smatra greškom? Kraj izvršavanja pre kraja ulaznog teksta? Pogrešan izbor alternative?
- **Backtracking** - jedan pristup je pokušaj jedne alternative, pa ako ne uspe, vraćanje unazad i pokušaj druge. Ovo može biti neefikasno.
- **Prediktivno parsiranje** - pametniji pristup: na osnovu sledećeg tokena (lookahead) predvideti koja alternativa je ispravna. Za ovo se koriste First i Follow skupovi, LL(k) gramatike.
- **Leva rekurzija** - može biti problem za rekurzivni spust jer dovodi do beskonačne rekurzije. Postoje heuristike za uklanjanje leve rekurzije.

Silazno parsiranje je jednostavnije za direktnu implementaciju (ručno pisanje parsera).

### Uzlazno parsiranje (bottom-up)

Kod uzlaznog parsiranja pokušavamo da od ulaznog niza simbola, redukcijom, dobijemo početni pojam. Akcija je: desna strana pravila se zamenjuje levom. Pravila izvođenja se otkrivaju u obrnutom redosledu u odnosu na silazno parsiranje.

Uzlazno parsiranje podržava širu klasu gramatika od silaznog.

#### Shift-reduce algoritam

Najpoznatiji algoritam uzlaznog parsiranja je shift-reduce, koji radi na sledeći način:

1. Preuzima se jedan simbol (token) iz ulaznog niza (**shift**) i dodaje na vrh steka
2. Proverava se da li sekvenca na vrhu steka odgovara desnoj strani nekog pravila
3. Ako odgovara - zamenjuje se čitava sekvenca pojmom sa leve strane (**reduce**)
4. Ako ne odgovara - nastavlja se preuzimanje (novi shift)

Važno je obratiti pažnju da se kod redukcije desna strana pravila menja levom i da se za ovaj algoritam koristi stek.

#### Detaljan primer shift-reduce parsiranja

Pogledajmo kako shift-reduce algoritam obrađuje ulaz "Ovo je tekst." sa sledećom gramatikom:

```
text
    -> sentence
    -> text sentence

sentence
    -> words DOT

words
    -> CAPITAL_WORD
    -> words WORD
    -> words CAPITAL_WORD
```

Tokeni na ulazu: `CAPITAL_WORD WORD WORD DOT EOF`

Korak po korak:

```
Korak 1 (shift):   Stek: [CAPITAL_WORD]              Ulaz: WORD WORD DOT EOF
                    CAPITAL_WORD odgovara desnoj strani pravila words -> CAPITAL_WORD

Korak 2 (reduce):  Stek: [words]                     Ulaz: WORD WORD DOT EOF
                    Zamenjujemo CAPITAL_WORD sa words

Korak 3 (shift):   Stek: [words, WORD]               Ulaz: WORD DOT EOF
                    words WORD odgovara desnoj strani pravila words -> words WORD

Korak 4 (reduce):  Stek: [words]                     Ulaz: WORD DOT EOF
                    Zamenjujemo words WORD sa words

Korak 5 (shift):   Stek: [words, WORD]               Ulaz: DOT EOF
                    words WORD ponovo odgovara pravilu words -> words WORD

Korak 6 (reduce):  Stek: [words]                     Ulaz: DOT EOF

Korak 7 (shift):   Stek: [words, DOT]                Ulaz: EOF
                    words DOT odgovara pravilu sentence -> words DOT

Korak 8 (reduce):  Stek: [sentence]                  Ulaz: EOF
                    Zamenjujemo words DOT sa sentence

Korak 9 (reduce):  Stek: [text]                      Ulaz: EOF
                    sentence odgovara pravilu text -> sentence
                    Zamenjujemo sentence sa text

Korak 10:          Stek: [text], Ulaz: EOF
                    Stigli smo do početnog pojma text uz prazan ulaz - USPEH!
```

Parsiranje je uspešno jer smo redukcijama stigli od ulaznog niza tokena do početnog pojma `text`.

## Bison - alat za generisanje parsera

Bison je alat za automatsko generisanje parsera. Na osnovu gramatike sintakse nekog jezika generiše funkciju koja predstavlja parser za taj jezik. Jednostavno se integriše sa flex-om koji se koristi za leksičku analizu.

Karakteristike bisona:

- Generiše **bottom-up** parser
- Koristi **shift-reduce** algoritam
- Podržane gramatike su podskup kontekstno slobodnih gramatika

### Teorijska osnova

Postoji jasna paralela između formalnih jezika i automata:

| Formalni jezik | Automat | Alat |
|----------------|---------|------|
| Regularni jezici (gramatike) | Konačni automati (finite automata) | Flex |
| Kontekstno slobodni jezici (gramatike) | Potisni automati (pushdown automata) | Bison |

Flex i bison simuliraju rad automata koji prepoznaju stringove jezika (leksika, sintaksa) generisanog odgovarajućom gramatikom.

### Ideja iza automatskog generisanja parsera

Princip je isti kao kod flex-a, samo na višem nivou:

1. **MI** - sintaksu predstavimo gramatikom, formalno
2. **TEORIJA** - za kontekstno slobodnu gramatiku (CFG) postoji odgovarajući potisni automat (konačni automat + stek/memorija)
3. **ALAT** - formira odgovarajući automat koji će biti zadužen za prepoznavanje

Rezultat: imamo mašinu/alat/implementaciju za prepoznavanje programskih konstrukcija i prihvatanje ulaznog programskog koda.

### Postupak rada sa flex-om i bison-om

1. Definisati tokene (u fajlu `jezik.y`)
2. Definisati gramatiku sintakse (u fajlu `jezik.y`)
3. Povezati flex i bison (include + deklaracije)
4. Omogućiti da flex vraća odgovarajuće tokene (u fajlu `jezik.l` dodati `return _IF;` i slično)
5. Kompajlirati obe stvari da se dobiju skener, parser i main (make)
6. Pokrenuti

### Struktura fajlova

**jezik.l** (flex specifikacija):

```c
#include "syntax.tab.h"
%%
... regularni izrazi ...
"if"    { return _IF; }
%%
```

**jezik.y** (bison specifikacija):

```c
int yylex(void);
...
%token _IF
%token _ID
...
%%
... gramatika ...
if_statement...
%%
int main() {
    return yyparse();
}
```

Ključne razlike u odnosu na prethodnu fazu (samo flex):

- `main()` funkcija je sada u bison fajlu i poziva `yyparse()` umesto `yylex()`
- Flex fajl uključuje header koji generiše bison (`syntax.tab.h`) da bi znao za tokene
- Flex sada vraća tokene (`return _IF;`) koje bison koristi za parsiranje
- Bison generiše `jezik.tab.c` sa funkcijom `yyparse()`, a flex generiše `lex.yy.c` sa funkcijom `yylex()`

### Konkretan primer: flex i bison za tekst

Za gramatiku teksta sa tokenima `CAPITAL_WORD`, `WORD` i `DOT`:

**jezik.l** (flex):

```c
"."          { return DOT; }
[A-Z][a-z]*  { return CAPITAL_WORD; }
[a-z]+       { return WORD; }
```

**jezik.y** (bison):

```yacc
text
    : sentence
    | text sentence
    ;

sentence
    : words DOT
    ;

words
    : CAPITAL_WORD
    | words CAPITAL_WORD
    | words WORD
    ;
```

Primetimo da je bison sintaksa za gramatiku drugačija od BNF notacije - koristi se `:` umesto `->` ili `::=`, alternative se odvajaju sa `|`, a svako pravilo se završava sa `;`.

### Korisničke akcije

Kao i u flex-u, možemo dodati korisničke akcije u bison pravila. Akcije se pišu u vitičastim zagradama:

```yacc
%%
... gramatika ...
if_statement... { printf("..."); }
%%
int main() {
    return yyparse();
}
```

Na primer, mogli bismo zadati zadatak: prebrojati koliko ima reči i rečenica u ulaznom tekstu. Za to bismo dodali odgovarajuće akcije uz pravila gramatike. Pitanje je: gde ispisujemo ove vrednosti? Odgovor: na mestu u gramatici gde znamo da je obrada završena (na primer, u pravilu za `text` ili u `main()` funkciji nakon uspešnog parsiranja).

## Rezime: odnos leksičke i sintaksne analize

| Aspekt | Leksička analiza (Skener) | Sintaksna analiza (Parser) |
|--------|---------------------------|----------------------------|
| Ulaz | String (karakteri) | Tokeni |
| Izlaz | Tokeni | Parse tree / AST |
| Azbuka | Karakteri | Tokeni |
| Formalizacija | Regularni izrazi | Gramatike (BNF) |
| Formalni jezici | Regularni jezici | Kontekstno slobodni jezici |
| Automati | Konačni automati | Potisni automati |
| Alat | Flex | Bison |
| Generisana funkcija | `yylex()` | `yyparse()` |