# Tipovi

Uvek imati na umu: dizajn jezika + implementacija - jasno + ispravno korišćenje.

## Šta je tip?

Tip je skup vrednosti i skup operacija dozvoljenih nad tim skupom vrednosti. Drugim rečima: koje vrednosti postoje i šta smem da radim sa njima?

```c
int x;
```

Celobrojne vrednosti - x će moći da učestvuje u definisanim operacijama. To je memorijska lokacija kojoj je dato simboličko ime, koja će sadržavati podatak nad kojim se može izvršiti određena operacija.

Važno: tip je apstrakcija. Iako su povezani, tip != implementacija. Na primer, `int` u C-u su celobrojne vrednosti ograničene arhitekturom (mogu biti 16, 32 ili 64 bita), dok `int` u Javi su uvek 32-bitne celobrojne vrednosti - to je odluka u dizajnu jezika, ne u implementaciji.

## Sistem tipova (Type System)

Logički okvir, skup pravila koja se odnose na tipove. Definiše:

- Koji osnovni tipovi postoje
- Kako se grade složeni tipovi
- Kako se tipovi dodeljuju izrazima
- Koje operacije su dozvoljene
- Kada su dva tipa kompatibilna
- Kada su dva tipa ekvivalentna

Sistem tipova postoji zbog preciznije specifikacije ponašanja. On je deo semantičke definicije jezika - pravila koja izlaze iz okvira kontekstno-slobodne gramatike. Omogućava otkrivanje većeg broja grešaka u odnosu na leksiku i sintaksu.

## Ekvivalencija tipova

Dva osnovna pristupa:

### Nominalna ekvivalencija

Tipovi su isti ako imaju isto ime. U C++ i Javi: dve klase sa istim implementacijama ali različitim imenom (npr. `Point` i `Tacka`) su različiti tipovi.

### Strukturna ekvivalencija

Tipovi su isti ako imaju istu strukturu. TypeScript koristi ovaj pristup - ako dva tipa imaju ista polja, smatraju se kompatibilnim. Go interface radi slično - ako implementiraš sve metode interfejsa, znači da implementiraš taj interface.

Primer u TypeScript-u:

```typescript
class Osoba {
    ime: string = "Neko";
}
class Student {
    ime: string = "Petar";
}

function predstaviSe(objekat: Osoba) {
    console.log(objekat.ime);
}

let s = new Student();
predstaviSe(s);  // OK - strukturna ekvivalencija
```

Iako je `Student` potpuno drugačija klasa od `Osoba`, TypeScript ih smatra kompatibilnim jer imaju istu strukturu (polje `ime` tipa `string`).

## Konverzije tipova

Kada su tipovi kompatibilni i kako radimo konverzije? Različiti pristupi:

- Nisu dozvoljene konverzije
- Mora eksplicitno
- Može implicitno i eksplicitno

### Implicitna konverzija (coercion)

Kompajler automatski konvertuje tip kad je to bezbedno:

```c
int i = 5;
float f = i;    // implicitna konverzija int -> float
```

### Eksplicitna konverzija (casting)

Programer preuzima odgovornost:

```c
float f = 3.14;
int i = (int)f;   // eksplicitni cast
```

### Upcasting i downcasting

**Upcasting** - konverzija iz izvedene klase u baznu. Uvek bezbedno:

```java
Osoba osoba = new Student();  // upcasting
```

Ovo je u skladu sa Liskov Substitution Principle - svuda gde se očekuje bazna klasa, može se koristiti izvedena.

**Downcasting** - konverzija iz bazne klase u izvedenu. Programer preuzima odgovornost, može dovesti do greške:

```java
Student student = (Student)osoba;  // downcasting
```

## Provera i zaključivanje tipova

Typing = type checking + type inference

### Type checking (provera tipova)

Provera da li su operacija i operandi dozvoljeni - da li operandi imaju odgovarajuće tipove za datu operaciju.

### Type inference (zaključivanje o tipovima)

Zaključivanje o tipovima na osnovu konteksta. Primeri:

```java
var x = 10;       // Java - tip se zaključuje iz konteksta
```

```cpp
auto x = 10;      // C++ - tip se zaključuje iz konteksta
```

Ovo nije dinamička tipiziranost - tip je poznat u vreme kompajliranja (postoji u AST-u), ali programer ga nije eksplicitno naveo. Ovo je ergonomija jezika.

Formalno, koriste se inference rules. Na primer: ako u datom kontekstu izraz e1 ima tip int i izraz e2 ima tip int, onda i njihov zbir ima tip int.

## Statičko vs dinamičko tipiziranje

### Statičko tipiziranje (Static typing)

- Provera tipova tokom faze prevođenja
- Primeri: C, C++, Java
- Generisani kod zavisi od tipova
- Rano otkrivanje grešaka
- Informaciju o tipu nosi kompajler (tabela simbola, AST)

### Dinamičko tipiziranje (Dynamic typing)

- Provera tipova tokom faze izvršavanja
- Primeri: Lisp, Python
- Generisani kod je isti (tipovi nemaju uticaj na generisani kod)
- Informaciju o tipu nosi sam objekat u runtime-u

### Poređenje

**Statičko:**

- Ranije otkrivanje grešaka, manje runtime grešaka
- Brže izvršavanje, bolja optimizacija
- Sigurnost - cilj nije samo provera ispravnosti već i zaštita programera od sopstvenih pretpostavki ili previda
- Sporiji razvoj, više koda

**Dinamičko:**

- Brži razvoj (isprobavanje rešenja, prototipovi, razvojni ciklusi)
- Raznovrsniji jezički konstrukti, kompaktniji kod
- Lakše "hakovanje" koda, fleksibilnost
- Sporije izvršavanje (?)
- Skoro izvesno više dokumentacije i konvencija

Pitanje discipline: tera me jezik (statičko) vs. teram sam sebe (dinamičko) - mana ili vrlina?

Odgovor savremenih jezika: TypeScript dodaje statičke tipove JavaScript-u, mypy dodaje opcione statičke tipove Python-u.

### Duck typing

Python koristi duck typing - "ako hoda kao patka i kvače kao patka, onda je patka":

```python
class Osoba:
    ime = "Neko"

class Student:
    ime = "Petar"

def predstavi_se(objekat):
    print(objekat.ime)

s = Student()
predstavi_se(s)  # OK - duck typing, dinamicki
```

Poređenje sa TypeScript-om: TypeScript koristi strukturnu ekvivalenciju sa statičkim tipiziranjem, dok Python koristi duck typing sa dinamičkim tipiziranjem. Oba pristupa dozvoljavaju da `Student` prođe gde se očekuje `Osoba`, ali na potpuno različite načine i u različitim fazama.

## Moderni jezici - kombinovanje pristupa

Moderni programski jezici usvajaju prednosti oba koncepta:

- C# ima atribute, refleksiju, `dynamic` tip i DLR (Dynamic Language Runtime)
- `var x;` (Java) i `auto x = 10;` (C++) nisu dinamička tipiziranost - tip je poznat u compile-time, ali programer ga nije eksplicitno naveo

## Strogo vs slabo tipiziranje

### Strogo (jako) tipizirani (Strongly typed)

- Vrednosti i operacije su strogo vezane za određeni tip
- Postojanje ograničenja
- Kompajler garantuje da se neće desiti greška u odnosu na tipove (type error)
- Python: `rezultat = "5" + 2` - greška!

### Slabo tipizirani (Weakly typed)

- Vrednosti nisu strogo vezane za određeni tip
- "Pametni" jezici - učini da nekako radi
- JavaScript: `let rezultat = "5" + 2;` daje `"52"` (string konkatenacija)

### Gde je granica?

Pitanje "Da li je jezik X strogo ili slabo tipiziran?" nema uvek jasan odgovor. Primeri iz C-a:

```c
char c = 'A';
int rezultat = c + 10;         // implicitna konverzija char -> int

float f = 3.14f;
int *p = (int *)&f;            // reinterpretacija memorije kroz cast
```

C dozvoljava neke opasne operacije (reinterpretacija memorije), ali zahteva eksplicitni cast - da li je to strogo ili slabo tipiziranje?

## Vezivanje (Binding)

Binding je veza između simboličkog imena i memorijske lokacije (ili konkretne implementacije).

### Rano vezivanje (Early/Static binding)

- Veza se uspostavlja u vreme kompajliranja
- **Overloading** - early binding, compile-time polimorfizam: kompajler zna koju verziju funkcije da pozove na osnovu tipova argumenata

### Kasno vezivanje (Late/Dynamic binding)

- Veza se uspostavlja u vreme izvršavanja
- **Overriding** - late binding, runtime polimorfizam: tek u runtime-u se zna koja verzija metode treba da se pozove (virtuelna tabela)

Umesto "čisto" statičkog, preciznog i odmah poznatog pristupa, moderna praksa je: odredi što više što ranije vs. odredi što više što kasnije.

## Terminologija - pažnja

U oblasti postoji problem sa terminologijom - precizno i kolokvijalno se mešaju, a kontekst je bitan.

- Ponekad se, verovatno pogrešno ili neprecizno, koristi pojam "netipiziran" (untyped) za dinamički tipizirane jezike
- Statički tipiziran jezik može imati konstrukte za dinamičku tipizaciju

Važno razlikovati:

```
Statically typed     !=  Strongly typed   !=  Compiled
Dynamically typed    !=  Weakly typed     !=  Interpreted
```

Ovo su nezavisne dimenzije. Na primer, Python je dinamički tipiziran ali strogo tipiziran. JavaScript je dinamički tipiziran ali slabo tipiziran. C je statički tipiziran ali ima slabe aspekte (pointer casting).