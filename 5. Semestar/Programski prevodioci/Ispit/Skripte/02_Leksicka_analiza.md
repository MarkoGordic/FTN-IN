# Leksička analiza

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta je leksička analiza?

Leksička analiza je prva faza prevođenja programa. Njen zadatak je da ulazni izvorni kod, koji je u suštini jedan dugačak string (niz karaktera), podeli na smislene delove. Ti smisleni delovi nazivaju se lekseme, a proces njihovog prepoznavanja i klasifikovanja proizvodi tokene koji se prosleđuju sledećoj fazi - sintaksnoj analizi. Ako skener naiđe na nešto što ne pripada jeziku, prijavljuje grešku.

Ova faza ima i svoje nazive koji objašnjavaju suštinu procesa. Naziva se skener jer skeniramo tekst na ulazu, slovo po slovo, leksemu po leksemu. Naziva se i lekser jer proizvodi lekseme.

Šematski:

```
string --> [Leksička pravila] --> tokeni + greške
```

## Lekseme

Lekseme su individualni delovi izvornog koda koje skener prepoznaje kao smislene celine. Pogledajmo konkretan primer:

```c
if (x == 5)
{
    y = 3; //komentar
}
```

Kada skener pročita ovaj kod, on ga razbija na sledeće lekseme:

```
if  (  x  ==  5  )  {  y  =  3  ;  }
```

Primetimo nekoliko stvari. Prvo, komentar `//komentar` nije prepoznat kao leksema - skener ga prepoznaje i odbacuje jer komentari nisu deo jezika koji se dalje obrađuje. Drugo, beline (razmaci, tabulatori, novi redovi) između leksema su takođe prepoznate od strane skenera. U nekim jezicima beline utiču na značenje programa (kao u Pythonu, gde uvlačenje definiše blokove koda), dok se u drugim jezicima ignorišu. Čak i kada se ignorišu za prevođenje, beline mogu biti od koristi za druge aktivnosti (na primer, za formatiranje poruka o greškama).

## Greške u leksičkoj analizi

Šta bi bila greška u leksičkoj analizi? Pogledajmo sledeći primer:

```c
if (8k == 5)
{
    y = 3 * 2;
}
```

Ako je naš jezik takav da identifikator ne može da počne brojem niti numerička vrednost može da se završi slovom `k`, onda `8k` ne odgovara nijednom leksičkom pravilu - to je leksička greška. Slično, ako naš jezik ne prepoznaje `*` kao deo jezika (nema ga u azbuki), onda je i to leksička greška.

Ovo nas dovodi do pitanja: šta znači "deo jezika"? Jezik je definisan skupom pravila, i samo ono što ta pravila dozvoljavaju može biti ispravna leksema. Sve ostalo je greška.

## Tokeni

Lekseme se klasifikuju po tipu uz eventualno dodavanje korisnih informacija - tako nastaju tokeni. Token je par koji čine vrsta tokena (ili klasa tokena) i vrednost tokena.

- **Vrsta tokena** je apstraktna reprezentacija klase jezičkih jedinica. Na primer, svi relacioni operatori (`==`, `<`, `>`, `!=`) pripadaju istoj vrsti tokena.
- **Vrednost tokena** nije obavezna i najčešće predstavlja konkretnu prepoznatu vrednost za konkretan ulazni string.

Lekseme su instance tokena koje su prepoznate prilikom obrade ulaznog stringa.

### Primer klasifikacije leksema u tokene

Pogledajmo kako se lekseme klasifikuju:

| Leksema | Vrsta tokena (neformalno) | Vrsta tokena (enum) | Vrednost tokena |
|---------|---------------------------|---------------------|-----------------|
| if      | Ključna reč               | KW                  | if              |
| while   | Ključna reč               | KW                  | while           |
| =       | Dodela                    | ASG                 |                 |
| ==      | Relacioni operator        | ROP                 | ==              |
| <       | Relacioni operator        | ROP                 | <               |
| +       | Aritmetički operator      | AOP                 | +               |
| ;       | Tačka zarez               | SC                  |                 |
| x       | Identifikator             | ID                  | x               |
| y       | Identifikator             | ID                  | y               |
| 5       | Literal                   | LIT                 | 5               |

Ovde je važno primetiti da neke lekseme nemaju vrednost tokena jer im ona nije potrebna - na primer, dodela (`=`) i tačka-zarez (`;`) su jednoznačni, pa vrsta tokena sadrži dovoljno informacija.

### Različiti pristupi klasifikaciji

Klasifikacija tokena nije jedinstven postupak - zavisi od dizajnera. Na primer, moguće je sve operatore (`=`, `==`, `<`, `+`) staviti u jednu zajedničku klasu `Operator` umesto da ih delimo na dodelu, relacione operatore i aritmetičke operatore. U tom slučaju, vrednost tokena preuzima veću ulogu jer razlikuje konkretne operatore unutar iste klase. Izbor klasifikacije zavisi od toga šta je korisno za naredne faze prevođenja.

### Dodatne informacije u tokenu

Token može evidentirati i poziciju u izvornom kodu radi informativnih poruka o greškama. Pamti se linija, ili linija i kolona, ili pomeraj od početka teksta. Mogu se pamtiti i druge informacije (atributi) koje su korisne za naredne faze.

Kog tipa su vrednosti tokena? To zavisi od implementacije - mogu biti stringovi, celobrojne vrednosti (za enumeracije), strukture, i slično.

### Zašto uopšte prepoznajemo i pamtimo tokene?

Ovo je važno pitanje. Za samu leksičku analizu, tokeni nam zapravo nisu neophodni. Dovoljno bi bilo samo da delove stringa prepoznamo kao elemente jezika i javimo da li ima grešaka ili ne - tj. da li je program napisan korišćenjem ispravnih reči. Međutim, tokeni su nam potrebni u nastavku, u sledećim fazama prevođenja. Sintaksna analiza, na primer, radi sa tokenima, a ne sa sirovim tekstom.

## Implementacija skenera

Kako se implementira skener? Osnovni algoritam je sledeći:

- čitamo string sa ulaza, karakter po karakter
- prepoznajemo lekseme
- kreiramo tokene
- informišemo o rezultatu (ok ili greška)

Postoje dva osnovna pristupa implementaciji:

1. **Ručno** - korišćenjem `while` petlji, `if/switch` naredbi i lookahead mehanizma. Ovaj pristup je proizvoljan i fleksibilan, ali zahteva više posla.
2. **Pomoću alata** - korišćenjem alata kao što su flex, lex, antlr i drugih. U ovom slučaju nam treba neka formalizacija jezika (regularni izrazi) na osnovu koje alat automatski generiše skener.

### Problemi koji se pojavljuju

Bez obzira na pristup, prilikom implementacije skenera pojavljuju se određeni problemi:

- Potrebno je da `<=` bude ispravno prepoznato kao jedan operator, a ne kao dva zasebna operatora `<` i `=`.
- Ako postoje rezervisane reči (kao `if`, `while`), potrebno je da one ne budu prepoznate kao opšti identifikatori.
- Pojava greške - da li odmah stati sa obradom i prijaviti grešku, ili dati informaciju o grešci i pokušati dalje sa analizom?
- Beline - da li su važne ili ne za konkretan jezik?
- Signal za kraj - može biti važno za naredne faze.

### Šta je ulaz za sledeću fazu?

Kada se leksička analiza završi, postavlja se pitanje kako se rezultat prosleđuje sintaksnoj analizi. Postoje opcije:

- obraditi ceo ulazni string i generisati niz tokena koji se u celosti predaje narednoj fazi
- prosleđivati, na zahtev, token po token narednoj fazi
- nešto treće (na primer, hibridni pristup)

## Regularni izrazi

Za opis leksike programskog jezika mogu se koristiti regularni izrazi. Zašto bismo to radili? Zato što nam omogućavaju jednostavnu formalnu reprezentaciju leksike jezika. Flex, na primer, na osnovu leksike definisane regularnim izrazima automatski kreira skener. Čak i kod ručne implementacije, regularni izrazi se mogu iskoristiti za prepoznavanje leksema.

### Teorijski kontekst

Regularni izrazi se koriste za opis regularnih jezika. Regularni jezici su vrsta formalnih jezika. Još jedna vrsta formalnih jezika su kontekstno slobodni jezici. Jezik leksike programskih jezika predstavlja regularan jezik, dok velik deo sintakse programskih jezika predstavlja kontekstno slobodan jezik. Ovo razlikovanje je ključno jer određuje koje alate i metode koristimo za svaku fazu prevođenja.

### Osnovna pravila regularnih izraza

| Oznaka | Primer | Formiranje | Skup reči |
|--------|--------|------------|-----------|
| (prazno) | | Prazan string | {""} |
| a | a | Svaki simbol (karakter) je RE | {"a"} |
| ab | ab | Konkatenacija dva RE | {"ab"} |
| * | ab* | RE na koji se odnosi se ponavlja 0 ili više puta | {"a", "ab", "abb", ...} |
| + | ab+ | RE na koji se odnosi se ponavlja 1 ili više puta | {"ab", "abb", ...} |
| ? | ab? | RE na koji se odnosi se ponavlja 0 ili 1 put | {"a", "ab"} |

### Proširena pravila

| Oznaka | Primer | Formiranje | Skup reči |
|--------|--------|------------|-----------|
| \| | a\|b | Alternativa | {"a", "b"} |
| ( ) | a(b\|c) | Grupisanje | {"ab", "ac"} |
| [ ] | [abc] | Alternative | {"a", "b", "c"} |
| [ - ] | [a-c] | Opseg | {"a", "b", "c"} |
| [^ ] | [^abc] | Alternative koje ne odgovaraju navedenom | {"d", "e", ... (ostalo iz azbuke)} |
| {m,n} | a{1,3} | Broj ponavljanja | {"a", "aa", "aaa"} |
| . | a. | Bilo koji znak (osim nove linije) | {"aa", "ab", "ac", ...} |
| \\ | a\\. | Escape - specijalne karaktere tretiramo kao obične | {"a."} |

Napomena: unutar uglastih zagrada, tačka se često interpretira kao bukvalni znak `.`, a ne kao specijalni karakter.

## Ideja iza automatskog generisanja skenera

Čitav princip se zasniva na sledećem lancu:

1. **MI** - leksiku predstavimo regularnim izrazima.
2. **TEORIJA** - za svaki regularni izraz postoji odgovarajući konačni automat i zna se precizan postupak kako se on formira.
3. **ALAT** - generiše funkciju koja simulira rad odgovarajućeg automata koji će biti zadužen za prepoznavanje.

Rezultat: napišemo regularne izraze i dobijemo gotovu mašinu/alat/implementaciju za prepoznavanje leksema.

Šematski, tok generisanja i izvršavanja izgleda ovako:

```
Generisanje (flex):    Regularni izrazi --> DFA --> Skener

Izvršavanje (C):       Source --> Skener --> Tokeni
```

Dakle, flex od regularnih izraza generiše deterministički konačni automat (DFA), koji zatim čini osnovu skenera. Taj skener prima izvorni kod na ulazu i proizvodi tokene na izlazu.

## Flex - praktična upotreba

### Postupak rada sa flex-om

1. Regularni izrazi koji predstavljaju gramatiku leksike se navode u specifikaciji (fajl `jezik.l`).
2. Specifikacija se prosleđuje flex programu: `$ flex jezik.l`
3. Rezultat je izlazni fajl `lex.yy.c` u kome je definisana funkcija `int yylex(void)`.
4. Nakon kompajliranja dobija se izvršni fajl: `$ gcc -o skener lex.yy.c`
5. Pokreće se interaktivno (ulaz je tastatura: `$ ./skener`) ili se vrši analiza ulaznog fajla (`$ ./skener < test.txt`).

### Primer: jezik koji prepoznaje brojeve

Definišimo jednostavan jezik L = {0, 1, 42, 402, 000150, ...} - skup svih reči nad azbukom koju čine cifre, bez prazne reči. Regularni izraz za ovaj jezik je:

```
[0-9]+
```

Flex specifikacija (`jezik.l`):

```lex
%option noyywrap
%%
[0-9]+
%%
int main() {
    yylex();
}
```

Ova specifikacija ima tri sekcije razdvojene sa `%%`:

- **Opcije i definicije** - `%option noyywrap` i druge konfiguracije
- **Pravila** - regularni izrazi i odgovarajuće akcije
- **Korisnički kod** - `main` funkcija i ostali C kod

### Opcija noyywrap

Kada flex dobije indikaciju da je završeno čitanje sa jednog ulaza, on proverava vrednost funkcije `yywrap()`. Povratna vrednost ukazuje na to da li se nastavlja sa sledećim ulazom (na primer, novi fajl) - povratna vrednost je 0, ili je obrada završena - povratna vrednost je 1.

Ako nije definisana ova funkcija, onda:
- ili je potrebno definisati opciju `noyywrap` (kao da je `yywrap` vratio 1)
- ili se mora linkovati biblioteka koja ima ovu funkciju (`libfl` biblioteka, povratna vrednost 1)

Opcija se može navesti i na komandnoj liniji: `$ flex --noyywrap jezik.l`

### Pokretanje i kompajliranje

Pokretanje flex-a:

```bash
$ flex jezik.l
```

Nakon izvršavanja kreiran je fajl `lex.yy.c` koji sadrži preko 1500 redova automatski generisanog C koda. Da li se isplati za tako jednostavan jezik? Za ovaj trivijalan primer možda ne, ali za složenije jezike - apsolutno.

Kompajliranje:

```bash
$ gcc lex.yy.c
$ gcc -o jezik lex.yy.c
```

Opcija `-o` definiše naziv izlaznog programa. Ako se izostavi, biće kreiran fajl `a.out`.

### Ponašanje skenera

Kada pokrenemo skener (`$ ./jezik`), njegovo podrazumevano ponašanje je:

- Sve dok ulazni string odgovara nekom regularnom izrazu - ne postoji podrazumevana akcija, odnosno pročitani tekst se preskače i nastavlja se sa radom (za sada je sve u redu, nastavi).
- Ukoliko pročitano ne odgovara nijednom regularnom izrazu - podrazumevana akcija je kopiranje tog teksta na izlaz.

Za izlazak iz interaktivnog režima koristi se `ctrl+D`.

### Dodavanje korisničkih akcija

Možemo dodati korisničke akcije koje se izvršavaju kada se prepozna odgovarajuća leksema:

```lex
%option noyywrap
%%
[0-9]+    { printf("Broj!"); }
%%
int main() {
    yylex();
}
```

Sada će se za svaki prepoznati broj na izlazu ispisati "Broj!".

## Rešavanje tipičnih problema

### Problem: višeznačni operatori

Operator `<=` treba prepoznati kao jedan operator, a ne kao dva operatora `<` i `=`. Ovo se rešava pravilom poznatim kao "Maximal munch" (ili "longest match") - pronalazi se najduži string koji odgovara nekom regularnom izrazu. Dakle, ako se `<=` može prepoznati kao celina, to ima prednost nad prepoznavanjem samo `<`.

### Problem: rezervisane reči vs. identifikatori

Ključna reč `if` treba prepoznati kao ključnu reč, a ne kao identifikator. Ako je identifikator definisan kao `[a-zA-Z][a-zA-Z0-9]*`, onda `if` odgovara i tom paternu. Rešenje je u tome da se bira prvi pronađeni regularni izraz koji odgovara - patern za `if` treba navesti pre paterna za identifikator u specifikaciji. Flex koristi pravilo prioriteta: ako se dva paterna poklapaju sa istim stringom iste dužine, bira se onaj koji je prvi naveden u specifikaciji.

## Flex i alternativni alati

Flex nije jedini alat za generisanje skenera. On je nastao kao unapređenje starijeg Lex alata. Koriste se i drugi alati kao što su Antlr, re2c, javaCC i mnogi drugi.

Pitanje za razmišljanje: koje su prednosti i mane korišćenja alata za generisanje skenera naspram samostalno (ručno) implementiranog skenera?

- **Prednosti alata**: brži razvoj, manja mogućnost grešaka, formalna osnova, lakše održavanje
- **Prednosti ručne implementacije**: veća kontrola, mogućnost optimizacije za specifične slučajeve, nezavisnost od alata, potencijalno bolje poruke o greškama