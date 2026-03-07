# Programski prevodioci - Uvod i osnovne faze

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Šta je programski jezik i šta su programski prevodioci?

Programiranje je ideja. Programski jezik je alat kojim tu ideju izražavamo. Da bismo zaista dobro poznavali neki programski jezik, nije dovoljno samo znati njegovu sintaksu - potrebno je razumeti kako se programi pisani u tom jeziku prevode i kako se izvršavaju. Pored toga, bitno je poznavati osnove i koncepte koji stoje iza jezika, istoriju razvoja jezika, trendove i dobre prakse.

Programski prevodilac (kompajler) je softver koji prevodi program napisan u jednom jeziku na drugi jezik. Najjednostavnije rečeno, cilj prevodioca je da ono što programer razume prevede u ono što računar razume.

Prevođenje najčešće podrazumeva jedan od sledećih scenarija:

- viši programski jezik prevodi se u asembler ili mašinski jezik
- viši programski jezik prevodi se u međukod (IR - intermediate representation)
- viši programski jezik prevodi se u drugi programski jezik

Konkretni primeri ovakvih prevođenja su Clang/LLVM (koji prevodi C/C++ kroz IR u mašinski kod), Emscripten (koji prevodi C++ u WebAssembly), Rustc (koji koristi LLVM za generisanje ciljnog koda), ili TypeScript kompajler (koji prevodi TypeScript u JavaScript).

### Primer prevođenja: iz C++ u asembler

Evo kako izgleda konkretan primer prevođenja jedne C++ funkcije u x86-64 asembler (gcc 13.2, -O2, intel sintaksa):

```cpp
int testFunction(int* input, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += input[i];
    }
    return sum;
}
```

Prevedeno u asembler:

```asm
testFunction(int*, int):
        test    esi, esi
        jle     .L4
        movsx   rsi, esi
        xor     eax, eax
        lea     rdx, [rdi+rsi*4]
.L3:
        add     eax, DWORD PTR [rdi]
        add     rdi, 4
        cmp     rdi, rdx
        jne     .L3
        ret
.L4:
        xor     eax, eax
        ret
```

Ova funkcija samo sabira elemente niza. Kompajler je iz čitljivog C++ koda generisao optimizovan mašinski kod sa petljom, registrima i skokovima - nešto što bi bilo veoma teško i nepraktično pisati ručno za svaki program.

## Polazni i ciljni jezik

Svaki prevodilac radi sa dva jezika: polaznim jezikom (source language) i ciljnim jezikom (target language). Polazni jezik je onaj u kome je program napisan, a ciljni jezik je onaj u koji se program prevodi.

Najvažniji cilj prevodioca je da prevede ispravno - da očuva značenje programa i da se prevedeni program ponaša onako kako se očekuje.

Pored ispravnosti, postoje i druge značajne karakteristike prevodilaca:

- brzo izvršavanje samog prevođenja
- brzo izvršavanje prevedenog programa
- optimalno korišćenje resursa (memorija, procesor)
- informativne poruke o greškama i mogućnost oporavka od grešaka
- mogućnost proširivanja i izmena prevodioca

## Vrste prevodilaca

Postoji više vrsta prevodilaca, a svaka ima svoje karakteristike:

| Vrsta | Opis | Primer |
|-------|------|--------|
| Kompajler | Prevodi ceo program u izvršni fajl | GCC, Clang |
| Interpreter | Izvršava program "u hodu", naredbu po naredbu | Python, Bash |
| JIT kompajler | Kombinuje oba pristupa - interpretira i kompajlira u toku izvršavanja | Java HotSpot, V8 |
| Transpajler | Prevodi na jezik istog nivoa | TypeScript -> JS |
| AI-kompajler | Model koji generiše i optimizuje kod | GitHub Copilot |

Važno je razumeti razliku između kompajlera i interpretera. Kompajler prevodi ceo program odjednom u izvršni fajl, koji se nakon toga može pokretati nezavisno od kompajlera. Interpreter, sa druge strane, čita i izvršava program naredbu po naredbu, bez generisanja zasebnog izvršnog fajla. JIT (Just-In-Time) kompajler kombinuje oba pristupa - program se najpre interpretira, a delovi koji se često izvršavaju se kompajliraju u mašinski kod radi boljih performansi.

## Česte zablude

Kada govorimo o prevodiocima, postoji nekoliko čestih zabluda koje treba razjasniti:

- Greške u programu nisu samo sintaksne greške - postoje i semantičke, logičke i greške u toku izvršavanja.
- Interpreter nije "spor kompajler" - to su suštinski različiti pristupi izvršavanju programa.
- Nije tačno da se Python isključivo interpretira, a Java isključivo kompajlira - stvarnost je mnogo složenija. Python ima bajtkod kompilaciju, a Java koristi JIT.
- IR (međureprezentacija) se nekad smatrao opcionalnim korakom, ali danas je gotovo neizbežan deo modernih prevodilaca.
- Optimizacija nije skup trikova - to je formalna stvar zasnovana na matematičkim transformacijama.

## Razvoj programskog jezika

Razvoj jednog programskog jezika je ozbiljan softverski projekat koji se sastoji iz tri velike faze: osmisliti, definisati i implementirati.

### Osmisliti

Kada osmišljavamo novi jezik, treba doneti mnogo odluka. Prvo, treba definisati ideju i opšte ciljeve: da li je jezik namenjen edukaciji, istraživanju ili profesionalnoj upotrebi? Da li je to DSL (domain-specific language) ili jezik opšte namene? Da li je cilj izvršavanje programa ili služi kao međujezik?

Zatim dolaze specifični tehnički ciljevi: brzina prevođenja, brzina izvršavanja, sigurnost, pristup i upravljanje memorijom. Na kraju treba odlučiti i o samom razvoju: da li koristimo postojeće alate ili sve radimo samostalno, da li svaki korak razvijamo zasebno ili neke korake spajamo, u kom jeziku implementiramo prevodilac.

Sve ove odluke su međusobno povezane i često postoji kompromis između različitih ciljeva.

### Definisati

Kada definišemo jezik, treba precizirati sledeće stvari:

- **Leksika jezika** - skup pravila koja definišu šta sve čini jezik (azbuka i dozvoljene reči)
- **Sintaksa jezika** - skup pravila koja definišu ispravno formirane programske strukture (gramatika)
- **Semantika jezika** - skup pravila koja određuju i upravljaju značenjem jezika
- **Strukture podataka i algoritmi** - kreiraju se u različitim fazama prevođenja (tabele, stabla...)
- **Obrada grešaka** - gde i na koji način se vrši obrada grešaka
- **Međujezik** - poznavati postojeći ili formirati novi
- **Optimizacije** - obavezne i dodatne
- **Jezici i alati** - koje tehnologije koristiti
- **Arhitektura rešenja** - procesi, integracije, automatizacija, build alati, testiranje

Krajnji rezultat definisanja treba da bude funkcionalan sistem.

### Implementirati

Za implementaciju prevodioca potrebno je široko znanje iz raznih oblasti:

- **Strukture podataka** - stek, red, heap, heš tabele, stabla, grafovi
- **Algoritmi** - obilasci stabla/grafova, rekurzivni spust, bojenje grafova
- **Teorija formalnih jezika** - regularni jezici, kontekstno osetljive/slobodne gramatike
- **Teorija automata** - konačni automati (deterministički, nedeterministički), potisni automati
- **Programski jezici** - jezik za koji pravimo prevodilac, jezik u kom implementiramo prevodilac, ciljni jezik
- **Arhitektura računara i operativni sistemi** - zbog ciljnog jezika i izvršavanja
- **Metode testiranja**
- **Razvojni alati**
- **Terminologija**

## Koliko je to teško?

Složenost izrade prevodioca zavisi od ambicija. Primitivan prevodilac, univerzitetski projekat ili hobi jezik - nije jako teško. Prevodilac za industriju ili DSL - znatno teže. Prevodilac opšte namene sa standardizacijom - prilično ozbiljan poduhvat.

Teorijski deo uključuje matematiku i formalizme, čiji je uticaj značajan i vidljiv čak i na osnovnim nivoima. Puno je različitih povezanih koraka i delova, pa lako može postati nepregledno i neuredno. Zato je proširivost veoma bitna karakteristika.

## Korisnici prevodioca

Korisnici kompajlera su programeri - i to ih čini specifičnom grupom korisnika. Bagovi i problemi u kompajleru mogu izazvati ozbiljne probleme jer programer od kompajlera očekuje da radi brzo, pouzdano i jednostavno. U opštem slučaju, programer ne obraća pažnju na kompajler jer rešava svoj problem, pa su korisnici prevodilaca u tom smislu zahtevniji nego korisnici ostalih softverskih rešenja. Da bi se prevodilac šire prihvatio, obično se očekuje i neka biblioteka (core, standard) i prateći alati.

## Zašto učiti o prevodiocima?

Čak i ako nećemo svi pisati kompajlere, postoji mnogo razloga za učenje ove oblasti:

- Zaokružuje se priča o programskim jezicima - razumemo kako zaista funkcionišu.
- Ovo su osnovna znanja računarskih nauka (Computer Science).
- Potrebno je za razvoj jezika za specifične domene (DSL).
- Znanja, metode, tehnike, koncepti i teorija imaju primenu u drugim oblastima.
- Razvoj kompajlera predstavlja izazov u razvoju kompleksnijeg softvera i traži metodološki pristup.
- Obrada teksta i govora (prirodni jezik) koristi slične principe.

Možda najvažniji razlog: prevodioci su osnova svih modernih alata. Linteri, transpajleri, IDE alati, JIT kompajleri, AI asistenti - svi koriste iste faze obrade (metode, znanja) kao i klasični prevodioci.

---

## Osnovne faze prevodioca

Prevodilac je kompleksan sistem koji se sastoji iz više faza. Svaka faza je posebno razvijana i izučavana, sa specifičnim strukturama podataka i algoritmima. Formalan uticaj teorije je značajan i vidljiv.

Jedan jezik može imati više prevodilaca (implementacija). Na primer, za C++ postoje GCC, Clang, MSVC i drugi kompajleri, svaki sa svojim karakteristikama.

Osnovna cevovod (pipeline) prevođenja izgleda ovako:

```
Polazni jezik -> Leksika -> Sintaksa -> Semantika -> Generisanje koda -> Ciljni jezik
```

Uz ovaj osnovni tok, kroz sve faze prožima se i upravljanje greškama. Pored toga, u modernim prevodiocima prisutne su i transformacije koda, analiza koda, optimizacije i upravljanje resursima.

### Prošireni pipeline sa međureprezentacijom (IR)

U modernim prevodiocima, pipeline se obično proširuje uvođenjem međureprezentacije (IR - Intermediate Representation):

```
Polazni jezik -> Leksika -> Sintaksa -> Semantika -> Generisanje IR -> IR -> Generisanje koda -> Ciljni jezik
```

Ova podela prevodioca na delove koji koriste IR dovodi do koncepta front end-a, middle end-a i back end-a:

- **Front end** - obuhvata leksičku analizu, sintaksnu analizu i semantičku analizu. Ovaj deo zavisi od polaznog jezika.
- **Middle end** - radi sa međureprezentacijom (IR). Ovde se vrše optimizacije nezavisne od polaznog i ciljnog jezika.
- **Back end** - obuhvata generisanje ciljnog koda iz IR-a. Ovaj deo zavisi od ciljne platforme.

Prednost ovog pristupa je ogromna: ako imamo N polaznih jezika (SL1, SL2, SL3...) i M ciljnih platformi (TL1, TL2, TL3...), umesto da pravimo N x M kompajlera, možemo napraviti N front end-ova i M back end-ova koji svi dele zajednički IR. Na primer, LLVM koristi upravo ovaj princip - Clang (za C/C++), Rustc (za Rust) i drugi front end-ovi svi generišu LLVM IR, a zatim LLVM back end generiše kod za različite ciljne platforme.

---

## Faza 1: Leksička analiza (Skener)

Leksička analiza je prva faza prevođenja. Skener (leksički analizator) prima izvorni kod kao niz karaktera (string) i na osnovu leksičkih pravila pretvara ga u niz tokena. Ako naiđe na nešto što ne može da prepozna, prijavljuje grešku.

### Primer leksičke analize

Posmatrajmo sledeći kod:

```c
if (x == 5)
{
    y = 3; //komentar
}
```

Skener najpre razbija ovaj tekst na lekseme - individualne "reči" jezika:

```
if  (  x  ==  5  )  {  y  =  3  ;  }
```

Zatim svaku leksemu klasifikuje u odgovarajući token. Token je uređena trojka koja sadrži tip tokena, vrednost i broj linije:

```
<KEYW, IF, 1> <LPAREN,, 1> <IDENT, x, 1>
<ROP, EQ, 1> <NUM, 5, 1> <RPAREN,, 1>
<LBRAC,, 2> <IDENT, y, 3> <ASSIGN,, 3> <NUM, 3, 3>
<SC,, 3> <RBRAC,, 4>
```

Primetimo da komentar `//komentar` nije deo tokena - skener ga prepoznaje i odbacuje jer komentari nisu relevantni za dalju obradu.

### Alati i koncepti u leksičkoj analizi

Leksička pravila se opisuju pomoću regularnih izraza. Na primer:

```
identifier -> letter ( letter | digit )*
ar_operator -> "+" | "-"
rel_operator -> "==" | "<"
```

Za implementaciju se koriste automati (konačni automati), a u praksi se često koristi alat **flex** koji na osnovu specifikacije regularnih izraza automatski generiše skener u jeziku C.

---

## Faza 2: Sintaksna analiza (Parser)

Sintaksna analiza je druga faza. Parser prima niz tokena od skenera i na osnovu sintaksnih pravila (gramatike) proverava da li je struktura programa ispravna. Rezultat parsiranja može biti parse stablo (parse tree) ili apstraktno sintaksno stablo (AST). Ako struktura nije ispravna, parser prijavljuje grešku.

### Primer sintaksne analize

Pretpostavimo da u posmatranom jeziku važi pravilo da naredba dodele ima oblik `identifikator = izraz ;`. Pogledajmo dva primera:

```
x = 5;
y 3;
```

Skener za prvu liniju generiše tokene `<IDENT, x> <ASSIGN, => <NUM, 5>` - i to je ispravno prema sintaksnim pravilima. Međutim, za drugu liniju dobijamo `<IDENT, y> <NUM, 3>` - nedostaje operator dodele, pa parser prijavljuje grešku.

### Gramatike i alati

Sintaksna pravila se opisuju pomoću gramatika, najčešće kontekstno slobodnih gramatika (BNF notacija). Na primer:

```
num_exp ::= exp
          | num_exp _ar_operator exp

exp ::= literal
      | _identifier
      | function_call
      | "(" num_exp ")"
```

Za implementaciju se koristi alat **bison** koji na osnovu specifikacije gramatike automatski generiše parser u jeziku C. Bison se koristi u kombinaciji sa flex-om.

---

## Faza 3: Semantička analiza

Semantička analiza je treća faza prevođenja. Ona proverava da li program, iako sintaksno ispravan, ima smisla sa stanovišta značenja. Koristi sintaksna pravila, AST i tabelu simbola da bi utvrdila semantičku ispravnost programa.

### Primer semantičke greške

Pogledajmo sledeći kod:

```c
int x = 5;
string str = "abc";
x = str;
```

Ovaj kod je sintaksno ispravan - svaka linija ima oblik ispravne naredbe. Međutim, semantički je neispravan jer pokušavamo da dodelimo string vrednost celobrojnoj promenljivoj. Semantička analiza otkriva ovakve greške.

### Tabela simbola i semantička pravila

Ključna struktura podataka u semantičkoj analizi je **tabela simbola** - struktura u kojoj se čuvaju informacije o svim identifikatorima u programu (ime, tip, opseg važenja itd.).

Primeri semantičkih pravila:

- Svi globalni identifikatori moraju biti međusobno različiti.
- Lokalni identifikatori raznih funkcija mogu biti identični.

Primer semantičke provere u kodu:

```c
if(get_type(fun_idx) == VOID)
    err("Function cannot return value");
else if(get_type(fun_idx) != get_type($2))
    err("incompatible types in return");
return_count++;
```

Ovaj kod proverava da li funkcija koja je deklarisana kao `void` pokušava da vrati vrednost, i da li se tip povratne vrednosti slaže sa deklarisanim tipom funkcije.

Semantička pravila se implementiraju unutar bison specifikacije, u kombinaciji sa flex-om i tabelom simbola, sve u jeziku C.

---

## Faza 4: Generisanje koda

Generisanje koda je poslednja glavna faza prevodioca. Na osnovu informacija prikupljenih u prethodnim fazama (sintaksna pravila, AST, tabela simbola), ova faza generiše ciljni kod. Generisanje može biti direktno u ciljni jezik ili kroz međukod (IR).

### Primer generisanja koda

Za sledeću funkciju u višem programskom jeziku:

```c
int f(int p) {
    int a;
    return p + a;
}
```

Generisani asemblerski kod (hipotetski asembler) izgleda ovako:

```asm
f:
    PUSH   %14
    MOV    %15,%14
    SUBS   %15,$4,%15
@f_body:
    ADDS   8(%14),-4(%14),%0
    ...
```

### Alati za generisanje koda

U implementaciji se koristi hipotetski asembler (HAJ) kao ciljni jezik. Kod za generisanje se piše u C-u, unutar bison akcija. Na primer:

```c
code("\n\t\t%s\t", ar_instructions[ADD + (get_type(idx) - 1) * AROP_NUMBER]);
gen_sym_name(idx);
code(",$1,");
gen_sym_name(idx);
```

Za testiranje generisanog koda koristi se emulator koji izvršava hipotetski asemblerski kod.

---

## Celokupan tok razvoja prevodioca

Kada se sve faze posmatraju zajedno, razvoj prevodioca prati ovaj tok:

1. **Leksička analiza** - definišu se regularni izrazi, koristi se flex, pišu se test primeri
2. **Sintaksna analiza** - definišu se gramatike, koristi se bison u kombinaciji sa flex-om, pišu se test primeri
3. **Semantička analiza** - definišu se semantička pravila, koristi se tabela simbola, sve se integriše sa flex-om i bison-om, pišu se test primeri
4. **Generisanje koda** - generiše se asembler (hipotetski), koristi se emulator za testiranje, sve se build-uje i testira

Svaka faza se oslanja na prethodnu i gradi na njenim rezultatima. Ceo sistem se implementira u jeziku C, koristi flex za leksičku analizu i bison za sintaksnu analizu, a testira se na svakom koraku sa odgovarajućim test primerima.