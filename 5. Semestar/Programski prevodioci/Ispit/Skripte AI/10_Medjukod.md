# Međukod

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Zašto međukod?

U klasičnom modelu kompajlera, polazni jezik prolazi kroz leksičku, sintaksnu i semantičku analizu, pa se direktno generiše ciljni jezik. Međutim, u praksi se često uvodi dodatna faza - generisanje međukoda (intermediate code/representation):

```
Polazni jezik -> Leksika -> Sintaksa -> Semantika -> Generisanje međukoda -> Međukod -> Generisanje koda -> Ciljni jezik
```

Prednosti korišćenja međukoda:

- **Jedan prednji modul za jedan polazni jezik, više zadnjih modula za različite ciljne jezike** - isti front-end se koristi za sve ciljne platforme
- **Više polaznih jezika, jedan zadnji modul za određeni ciljni jezik** - različiti jezici dele isti back-end
- **Optimizacije** - mnoge optimizacije se lakše rade na međukodu nego na izvornom ili ciljnom kodu
- **Brže prilagođavanje promenama** koje nastaju i u polaznim jezicima i ciljnim arhitekturama

## Terminologija

**Međureprezentacija** (Intermediate Representation - IR) - može imati različite oblike: kod ili neka struktura. Većina prevodilaca ima neku vrstu IR.

**Međujezik** (Intermediate Language - IL) - ciljni jezik za prednji modul, a izvorni jezik za zadnji modul. Ima manji nivo apstrakcije u odnosu na polazni, a veći nivo u odnosu na ciljni jezik.

## Sekvenca međureprezentacija

Prevodioci mogu koristiti sekvencu različitih IR:

```
Polazni jezik -> IR 1 -> ... -> IR n -> Ciljni jezik
```

Prva IR ima veći nivo apstrakcije, bliža je polaznom jeziku i obično je strukturnog tipa (stablo). Poslednja IR je detaljnija, bliža ciljnom jeziku i obično je linearnog tipa (niz instrukcija).

Sukcesivno se smanjuje apstrakcija, a povećavaju detalji implementacije. Različite optimizacije su pogodnije za različite nivoe apstrakcije. Može biti i više prolazaka kroz iste reprezentacije.

## Oblici međureprezentacija

### Apstraktno sintaksno stablo (AST)

Reprezentacija izvornog koda u obliku stabla. Koristi se i u sistemima za analizu i transformaciju programa.

Razlika između konkretnog i apstraktnog stabla: konkretno stablo parsiranja prikazuje postupak izvođenja sa svim detaljima polaznog koda (uključujući neterminale, zagrade, separatore), dok apstraktno sintaksno stablo je usmereno na izvršavanje i ne sadrži sve detalje.

Na primer, za izraz `num + num * num` sa gramatikom `E -> E + T, T -> T * num`:

Konkretno stablo:

```
         E
       / | \
      E   +   T
      |     / | \
      T    T   *  num
      |    |
     num  num
```

Apstraktno stablo (AST):

```
       +
      / \
    num   *
         / \
       num  num
```

AST sadrži samo operatore i operande - nema neterminala, zagrada ni separatora.

### Postfiksna notacija (RPN)

Obrnuta poljska notacija (Reverse Polish Notation - RPN). Operator je uvek iza svojih operanada.

Primeri:

```
Infiksna:    a = -b * (c + d) / (e - f);
Postfiksna:  a b unarni_minus c d + * e f - / =

Infiksna:    m = (a + b) * c - -d;
Postfiksna:  m a b + c * d unarni_minus - =
```

Osobine postfiksne notacije:

- Operator je uvek iza svojih operanada
- Ne zahteva zagrade (prioritet je već ugrađen u redosled)
- Prilagođena stek mašinama / stek arhitekturama
- Može se dobiti postorder obilaskom sintaksnog stabla

Za konverziju iz infiksne u postfiksnu notaciju postoji Dijkstrin Shunting yard algoritam.

### Izvršavanje postfiksne notacije na steku

Za izraz `a + 2 * b` postfiksna notacija je `a 2 b * +`. Izvršavanje na stek mašini koristi privremene promenljive:

```
a 2 b * +

Korak 1: push a
Korak 2: push 2
Korak 3: push b
Korak 4: * -> pop b, pop 2, izračunaj 2*b, stavi rezultat
          x = 2 * b  -> push a, push x
Korak 5: + -> pop x, pop a, izračunaj a+x, stavi rezultat
          y = a + x  -> push y
```

### Troadresni kod (TAC - Three-Address Code)

Troadresni kod je nizak nivo međujezika koji se lako prevodi u konkretan asemblerski jezik. Svaka instrukcija ima najviše 3 operanda/adrese.

Opšti oblici:

```
result := op1 operator op2
operator source => result
operator op1, op2 => result
result := op1
```

Neki izrazi se moraju predstaviti sa više instrukcija. Međurezultati se smeštaju u privremene promenljive.

Primer - jednostavni izrazi:

```
p = x + y * z;          t1 := y * z
                         p := x + t1

a = b * c + b * d;      t1 := b * c
                         t2 := b * d
                         t3 := t1 + t2
                         a := t3
```

Broj privremenih promenljivih je potencijalno neograničen.

Primer - if-else:

```c
if (a < b)
    c = a;
else
    c = b;
```

Može se prevesti na dva načina:

Varijanta 1 (obrnuti uslov):

```
    t1 := a >= b
    if t1 goto L1
    c := a
    goto L2
L1:
    c := b
L2:
    ...
```

Varijanta 2 (ifz - if zero):

```
    t1 := a < b
    ifz t1 goto L1
    c := a
    goto L2
L1:
    c := b
L2:
    ...
```

### Zapisi troadresnog koda

Troadresni kod može imati različite implementacije/zapise. Ne mora imati simbolički oblik - može imati numerički oblik gde određene vrednosti kodiraju i operacije i operande.

**Četvorke (quadruples)** - svaka instrukcija ima 4 polja: operator, operand1, operand2, rezultat:

```
a = b * c + b * d;

* b c t1
* b d t2
+ t1 t2 t3
= t3 a
```

**Trojke (triples)** - nema polja za rezultat, koriste se redni brojevi naredbi za referencu na međurezultat:

```
(0) * b c
(1) * b d
(2) + (0) (1)
(3) assign a (2)
```

## Ostali oblici IR

- **Graf kontrole toka (CFG - Control Flow Graph)** - graf koji prikazuje tok izvršavanja programa
- **SSA (Static Single Assignment)** - oblik u kome se svakoj promenljivoj dodeljuje vrednost tačno jednom
- Konkretni zapisi ne moraju nužno imati 4 elementa

## Primeri međujezika u praksi

- **p-code** - za Pascal
- **bytecode** - za Java (JVM); i drugi bytecode-like formati
- **C kao IL** - korišćenje C jezika kao međujezika
- **GIMPLE** - gcc-ov interni IR
- **LLVM IR** - međureprezentacija LLVM kompajlerske infrastrukture
- **CIL** - Common Intermediate Language za .NET platformu
- **Wasm** - WebAssembly

## Generisanje međukoda iz stabla

Ako imamo stablo (AST), međukod se može kreirati obilaskom:

- Za svako podstablo se generiše odgovarajući međukod
- Delovi se spoje u konačni kod
- Rezultat iskaza (ukoliko je potrebno) se smesti u privremenu promenljivu i ime te promenljive se vraća i koristi dalje
- Mogu se iskoristiti ideje slične kao kod micko kompajlera, ali je preglednije i lakše za održavanje