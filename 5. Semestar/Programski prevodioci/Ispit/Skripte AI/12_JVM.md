# Java Virtuelna Mašina (JVM)

## Izvršno okruženje - podsetnik

Generisanje koda je faza sinteze - neophodno je okruženje u okviru kog će se program izvršavati. Prevođenje je uvek u skladu sa okruženjem. Okruženje je podrška za organizaciju i upravljanje memorijom, upravljanje pozivima funkcija i upravljanje apstrakcijama jezika.

Programski jezik je definisan sintaksom i semantikom u odnosu na apstraktnu mašinu. Prevodilac prevodi u odnosu na izvršno okruženje - to može biti konkretna mašina (CPU registri, RAM, instrukcije, OS interfejs) ili virtuelna mašina (softver).

## Virtuelna mašina

Virtuelna mašina je zapravo program (softver) koji se ponaša kao mašina (računar). Omogućava izvršavanje apstrakcija. Postoje stanja (upravlja se različitim podacima koji modeliraju memoriju) i postoje instrukcije (poseban skup instrukcija). Sve je "izgrađeno od softvera", nema veze sa organizacijom memorije i instrukcijama na konkretnoj mašini.

Razlikujemo:

- **Sistemska VM** - simulira računar i operativni sistem
- **Procesna VM** - podrška za izvršavanje programa

Primeri procesnih VM: JVM (Java Virtual Machine), CLR (Common Language Runtime za .NET)

Prednosti: nezavisnost od platforme, sigurnost, portabilnost, mogućnosti za optimizacije.

## Dva tipa VM prema izvršavanju operacija

### Stack-based VM

- Lokacija operanada i rezultata nije eksplicitno naznačena - uvek je na vrhu steka
- Sve se realizuje preko operacija sa stekom
- Tri instrukcije su potrebne da se izvrši sabiranje (push, push, add)
- Jednostavnije instrukcije, manje parametara
- Brže i jednostavnije za implementaciju
- Primeri: Java VM, .NET CLR

### Register-based VM

- Eksplicitno navođenje adresa (operandi su u registrima)
- Jedna instrukcija za sabiranje (add r1, r2, r3)
- Bliže fizičkim mašinama
- Kod je manje kompaktan
- Često potrebne određene pretpostavke o CPU
- Određene optimizacije moguće
- Primer: Android Runtime Environment (ART)

### Stek arhitektura - princip rada

Jedino skladište je stek. Forma instrukcije `r = F(a1, ..., an)`: POP n operanada sa vrha steka, izračunaj funkciju F, PUSH rezultat na vrh steka.

```
PUSH 7      ; stek: [7]
PUSH 5      ; stek: [7, 5]
ADD         ; pop 5 i 7, izracunaj 7+5=12, push 12; stek: [12]
```

## JVM arhitektura

### Kompilacija i izvršavanje

```
program.java  ->  javac (java compiler)  ->  program.class  ->  JVM  ->  execution
```

Class fajl je nezavisan od platforme (arhitektura + OS). Sadrži bytecode - međukod Java Virtuelne Mašine. To je jezik višeg nivoa od asemblerskog, bogat metapodacima (debug informacije, informacije o tipovima...).

### Dva steka u JVM

- **Stek za izračunavanje (evaluation/operand stack)** - evaluacija izraza i prenos vrednosti unutar jedne metode
- **Stek aktivacionih blokova (call stack)** - modeluje dinamiku poziva metoda

Ovo su dva različita steka sa različitim namenama.

## JVM memorijski model

### Stek

Svaka nit (thread) ima svoj stek na kom se nalaze frejmovi (lokalne promenljive, međurezultati, podrška za aktivaciju i povratak iz metoda).

### Heap

Sve niti dele ovu oblast. Smeštaju se svi objekti.

### Programski brojač

Svaka nit ima svoj registar za programski brojač.

### Method Area

Sve niti dele ovu oblast. Inicijalizuje se na početku. Za svaku klasu/interfejs se čuva bajtkod metoda i runtime constant pool.

### Constant Pool

Sadrži string i numeričke konstante, kao i simboličke reference (članovi drugih klasa/interfejsa - dynamic linking).

Napomena: JVM nema registre opšte namene. Naravno, konkretna implementacija JVM-a interno koristi registre konkretne mašine.

## Stek frejm

Svaki poziv metode kreira frejm na steku. Frejm sadrži (makar):

- **Lokalne promenljive** - adresiraju se preko indeksa (prva je 0). Kod metoda instance prva promenljiva (indeks 0) je `this`. Slede argumenti pa lokalne promenljive. Neki tipovi zauzimaju više mesta - `long` i `double` zauzimaju dva mesta.
- **Operand stack** - na početku prazan, koristi se za računanje (push, pop), za pripremu argumenata i za preuzimanje povratne vrednosti.
- **Pokazivač na CP odgovarajuće klase** - pristup konstantama i elementima drugih klasa ili interfejsa.

### Razlika instance metode i statičke metode

```java
public int fun1(int a, int b) {     // lokalne: 0=this, 1=a, 2=b, 3=r
    int r = a + b + x;
    return r;
}
public static int fun2(int a, int b) { // lokalne: 0=a, 1=b, 2=r
    int r = a + b + s;
    return r;
}
```

U instance metodi `fun1`, `iload_1` učitava `a` (jer je indeks 0 zauzet za `this`). U statičkoj metodi `fun2`, `iload_0` učitava `a` (nema `this`).

## Skup instrukcija

Instrukcije se sastoje od opcode-a (1 bajt) i 0 ili više operanada. Instrukcije zavise od tipa - prefiks označava tip (`i` za int, `f` za float, `a` za referencu, `l` za long, `d` za double).

### Čitanje i pisanje (promenljive <-> operand stek)

```
iload, fload, aload      ; promenljiva na stek
istore, fstore, astore   ; sa steka u promenljivu
iconst_0 ... iconst_5    ; konstanta na stek (postoje samo od -1 do 5)
bipush                    ; konstanta (-128 do 127) na stek
ldc                       ; konstanta iz constant pool-a na stek
```

### Aritmetičke operacije

```
iadd, fadd    ; sabiranje
isub, fsub    ; oduzimanje
imul          ; množenje
ior           ; bitwise or
iinc          ; inkrement lokalne promenljive (ne koristi stek)
```

### Rad sa objektima

```
new           ; kreiranje objekta
getstatic, putstatic    ; statička polja
getfield, putfield      ; instance polja
newarray, iaload, iastore, arraylength  ; nizovi
```

### Kontrola toka

```
if_icmpeq, if_icmplt, ifle, ifnull   ; uslovni skokovi
goto                                   ; bezuslovni skok
```

### Metode

```
invokevirtual     ; poziv instance metode (polimorfizam)
invokeinterface   ; poziv metode interfejsa
invokestatic      ; poziv statičke metode
invokespecial     ; poziv konstruktora, super metode, privatne metode
invokedynamic     ; dinamički poziv (lambda, konkatenacija stringova...)
ireturn, freturn  ; povratak sa vrednosti
return            ; povratak bez vrednosti (void)
```

### Kodiranje instrukcija

Opcodes su kodirane jednim bajtom. Neke operacije imaju operande koji zauzimaju više bajtova:

- `iconst_0` - 1 bajt, operand je enkodiran u samu operaciju (opcode 0x03)
- `bipush 10` - 2 bajta, opcode + operand (za konstante između -128 i 127, opcode 0x10)

Brojevi sa leve strane u disassembliranom kodu su indeks - bajt ofset od početka metode.

## Primeri

### Primer 1: osnovni program

```java
public class Main {
    public static void main(String[] args) {
        int a, b;
        a = 5;
        b = 3;
        a = a + b;
        System.out.println(a);
    }
}
```

Disassemblirani bytecode (`javap -c Main.class`):

```
public static void main(java.lang.String[]);
  Code:
     0: iconst_5           // push 5 na stek
     1: istore_1           // pop sa steka u lokalnu 1 (a)
     2: iconst_3           // push 3 na stek
     3: istore_2           // pop sa steka u lokalnu 2 (b)
     4: iload_1            // push a na stek
     5: iload_2            // push b na stek
     6: iadd               // pop oba, saberi, push rezultat
     7: istore_1           // pop rezultat u a
     8: getstatic #7       // System.out na stek
    11: iload_1            // push a na stek (priprema za invoke)
    12: invokevirtual #13  // println(a)
    15: return
```

### Primer 2: petlja

```java
public int fun1(int a) {
    for (int i = 0; i <= 10; i++) {
        a++;
    }
    return a;
}
```

Bytecode:

```
 0: iconst_0            // push 0
 1: istore_2            // i = 0  (lokalna 2)
 2: iload_2             // push i
 3: bipush 10           // push 10
 5: if_icmpgt 17        // uzmi 2 sa steka, ako je prvi > drugog, skoci na 17
 8: iinc 1, 1           // a++ (lokalna 1, inkrementiraj za 1)
11: iinc 2, 1           // i++
14: goto 2              // skok na pocetak petlje
17: iload_1             // push a
18: ireturn             // return a
```

### Primer 3: poziv statičke metode

```java
public class MethodTest {
    public static void main(String[] args) {
        int a = 5;
        System.out.println(sum(a));
    }
    public static int sum(int m) {
        int sum = 0;
        for (int i = 0; i <= m; i++) {
            sum += i;
        }
        return sum;
    }
}
```

Bytecode za `main`:

```
 0: iconst_5
 1: istore_1
 2: getstatic #7        // System.out
 5: iload_1
 6: invokestatic #13    // poziv sum(I)I
 9: invokevirtual #19   // println
12: return
```

Bytecode za `sum`:

```
 0: iconst_0            // sum = 0
 1: istore_1
 2: iconst_0            // i = 0
 3: istore_2
 4: iload_2             // push i
 5: iload_0             // push m
 6: if_icmpgt 19        // if i > m goto 19
 9: iload_1             // push sum
10: iload_2             // push i
11: iadd                // sum + i
12: istore_1            // sum = rezultat
13: iinc 2, 1           // i++
16: goto 4              // nazad na pocetak petlje
19: iload_1             // push sum
20: ireturn             // return sum
```

### Primer 4: stringovi i constant pool

```java
public class HVTest {
    public static void main(String[] args) {
        int a = 3, b = 5;
        String str = "Hello World: ";
        System.out.println(str + (a + b));
    }
}
```

Bytecode:

```
 0: iconst_3            // push 3
 1: istore_1            // a = 3
 2: iconst_5            // push 5
 3: istore_2            // b = 5
 4: ldc #7              // push "Hello World: " (iz CP)
 6: astore_3            // str = referenca
 7: getstatic #9        // System.out
10: aload_3             // push str
11: iload_1             // push a
12: iload_2             // push b
13: iadd                // a + b
14: invokedynamic #15, 0  // konkatenacija stringa
19: invokevirtual #19   // println
22: return
```

## Struktura class fajla

Class fajl je niz bajtova sa određenom strukturom:

- **Magic number** - 0xCAFEBABE (odabrao James Gosling)
- **Major i minor verzija**
- **Constant pool** - broj elemenata i sama tabela
- **Access flags** - flegovi za public, abstract, enum...
- **This class, super class** - indeksi u CP tabeli
- **Interfejsi** - broj interfejsa, niz indeksa u CP tabeli
- **Polja** - broj polja i tabela sa informacijama
- **Metode** - broj metoda i tabela sa informacijama (uključujući bytecode)
- **Atributi** - broj atributa i tabela sa informacijama

### Constant Pool - detaljnije

Uređen skup konstanti koje određeni tip koristi. Sadrži sve potrebno za izvršavanje svega definisanog u nekoj klasi ili interfejsu. Simboličke reference opisuju KAKO da se nešto pronađe. Dok smo u fajlu, nismo u memoriji.

Tipovi zapisa u CP:

- `Methodref` - referenca na metodu: Class.NameAndType
- `Fieldref` - referenca na polje: Class.NameAndType
- `Class` - ime klase
- `NameAndType` - ime:tip (V za void, I za int, Ljava/lang/String; za String...)
- `Utf8` - niz bajtova (stringovi, imena)
- `String` - referenca ka sadržaju stringa
- `Integer`, `Float`, `Double`, `Long` - numeričke konstante
- `InvokeDynamic` - dinamički poziv

### Verbose ispis

Sa `javap -c -v Main.class` dobijamo potpune informacije: constant pool, stack/locals/args_size za svaku metodu, LineNumberTable (veza sa izvornim kodom - liniji 4 u izvornom kodu odgovara bajt ofset 0 u bytecodu).

## Izvršavanje

Izvršavanje počinje od kreiranja inicijalne klase i poziva main metode. Dinamički se radi učitavanje i povezivanje klasa - između ostalog formira se runtime CP na osnovu CP iz class fajla. Otkrivanje i povezivanje imena (resolution): simbolička referenca se zamenjuje konkretnom referencom, najčešće kod prvog korišćenja. Opis iz CP-a - JVM traži - dobija adresu runtime strukture.

Za izvršavanje je potrebna implementacija: Java bytecode interpreter i/ili JIT kompajler za konkretnu mašinu.

## JIT kompajler

JIT (Just-In-Time) kompajler vrši prevođenje tokom izvršavanja. Cilj je iskoristiti prednosti dva tradicionalna pristupa:

- **AOT (Ahead-Of-Time)** kompajler - prevodi pre izvršavanja
- **Interpreter** - tumači instrukciju po instrukciju tokom izvršavanja

### Proces JIT kompilacije

1. Posmatraju se delovi koda (klase, metode, petlje) - dinamička analiza programa
2. Vodi se evidencija o izvršavanju, značajnim delovima u programu (hot spots)
3. JVM odlučuje koji delovi su pogodni za kompilaciju na ciljni (mašinski) kod
4. Vodi se evidencija o prevedenim delovima
5. Kad je potreban određeni deo - umesto interpretera koristi se prevedeni kod

### OSR (On-Stack Replacement)

Prelaz sa interpretiranja na kompajliranu verziju. Ili sa jedne verzije koda na drugu. Može biti prelaska i u toku petlje, nakon određenog broja iteracija, kad je kompajlirana verzija gotova.

### Dinamičke optimizacije

Učestalost poziva nije jedini kriterijum za JIT kompilaciju. Prednost JIT prevođenja je i u mogućnostima dinamičkih optimizacija:

- Retko se poziva metod, ali ima deo koda koji se dobro može optimizovati - kompajlira se
- Može dodatno da se optimizuje ili da se promeni optimizacija (zbog pogrešnih pretpostavki ili nepotrebnih optimizacija)
- Bytecode je ulaz u optimizacionu mašinu

### Prednosti JIT-a

- Ubrzavanje izvršavanja
- Korišćenje detalja specifične arhitekture
- Dostupnost informacija koje su poznate samo u runtime-u
- Poboljšane optimizacije
- Što duže radi, potencijalno brže se izvršava

### Mane JIT-a

- Dodatno vreme za kompilaciju
- Povećano korišćenje memorije
- Zavisi od toga koliko i kada se delovi kompajliraju
- Merenje performansi zahteva posebnu pažnju (warmup faza)

## JVM nije samo za Javu

Kad se definiše VM, ne znači da nju mora i može koristiti samo jedan jezik. Kao što Java program može da se prevede na nešto drugo, tako i bilo koji drugi jezik može da koristi JVM.

JVM (bytecode) jezici: Java, Scala, Kotlin, Clojure, Jython...

CLR (CIL) jezici: C#, C++/CLI, F#, Eiffel, IronPython...

### Interpreted vs compiled languages

Iako koristimo ove termine - zapravo ne postoji stroga podela. Mogu se napraviti različite implementacije, prilikom prevođenja koriste se oba pristupa, određeni delovi se svakako izvršavaju u nekoj meri (front-end, analiza). CPython je implementacija jezika Python realizovana u C-u. GCC je kompajler za C. JIT kompajler kombinuje oba pristupa.

## Upravljanje memorijom

### Dinamičko zauzimanje memorije

Zadaci: voditi računa koliko je zauzeto/slobodno, zauzimati tražene delove memorije, tražiti od OS inicijalno i proširenje po potrebi, oslobađati određene delove memorije.

Dva osnovna pristupa: ručno (malloc/free) i automatski (GC).

### Preporuke za upravljanje memorijom

1. Osloboditi sve što više nije potrebno - inače dolazi do memory leaks
2. Ne pristupati onome što je oslobođeno i ne oslobađati prerano - pristup nepostojećem je greška, pristup nečem drugom na tom mestu je gora greška
3. Ne kreirati ono što ne treba - previše zauzimanja (na primer, bespotrebni copy konstruktori)

### Fragmentacija

Intenzivnim ponavljanjem zauzimanja i oslobađanja može se doći do značajne fragmentacije. Rezultat: nema memorije, a zapravo je ima, ali nije dobro iskorišćena. Zauzeta memorija je široko rasuta, nema velikih blokova slobodne memorije.

### Strategije alokacije

Prilikom novog zauzimanja traži se odgovarajuće slobodno mesto. Lista pokazivača na slobodne prostore čuva evidenciju. Od n mogućih slobodnih prostora, koji izabrati?

- **First-fit** - prvi koji je dovoljno velik
- **Best-fit** - najmanji mogući deo koji je dovoljno velik
- **Zauzimanje blokova** - veličine su stepeni broja 2

## Garbage Collection (GC)

"Automatsko" oslobađanje (recikliranje) memorije u izvršnom okruženju. Razlikuje objekte koji su dostupni od onih koji više neće biti korišćeni i bezbedno oslobađa memoriju.

Dva procesa (ne nužno funkcionalno odvojena): mehanizam za detekciju živih objekata i mehanizam za samo "oslobađanje" memorije.

### Reference Counting

Objekat je živ ako neko na njega pokazuje. Broje se reference - kad se pojavi nova referenca, poveća se brojač, kada prestane da pokazuje, smanji se brojač. Kada je broj referenci 0, objekat je nedostupan - kandidat za brisanje.

Prednosti: uvek se zna status jednog objekta, brzo.

Mane: zauzima dodatne resurse (mesto za brojanje), nije kompatibilan sa nekim JIT optimizacijama, problem sa cikličnim vezama.

Primer cikličnih veza:

```java
Osoba ana = new Osoba("Ana");
Osoba bojan = new Osoba("Bojan");
ana.partner = bojan;
bojan.partner = ana;
// posle izlaska iz metode - logicki ne postoje,
// ali tehnicki postoje jer imaju medjusobne reference
// reference counting ih nece osloboditi
```

Ciklične veze se pojavljuju u listama, grafovima, observer patternu...

### Trace-based GC

Objekat je živ ako je dostižan. Krene se od početnog skupa objekata (GC roots) i prate se sve reference. Kad se formira skup dostupnih objekata, svi ostali su kandidati za brisanje.

**Mark-and-sweep**: u jednom momentu se saznaje status za sve objekte, što daje priliku za manju fragmentaciju. Mana: svi moraju da se markiraju, što izaziva određene pauze. Prednost: ciklus može biti nedostižan bez obzira što u njemu postoje reference.

### Poboljšanja GC-a

- Kad se markiraju, objekti se pomeraju (compaction) tako da svi dostupni objekti budu spojeni - izbegava se fragmentacija. Memorija može biti podeljena na dva dela, radi se samo sa jednim delom.
- **Incremental GC** - ne mora odjednom sve da se odradi
- **Generational GC** - ko preživi dovoljno dugo neće biti dealociran
- Mehanizmi u programskom jeziku: soft, strong i weak reference, finalize metode

### Generational hypothesis

Većina objekata umire veoma brzo, dok mali broj objekata živi veoma dugo. Nema smisla svaki put skenirati ceo heap - treba se fokusirati na deo memorije gde se "najviše dešava".

Heap se deli na generacije:

- **Young Generation (Nursery)** - novo-alocirani objekti
  - **Eden** - ovde se kreiraju novi objekti
  - **Survivor 0 / Survivor 1** - objekti koji su preživeli Minor GC
- **Old Generation** - objekti koji su preživeli više GC ciklusa

Tok: novi objekat ide u Eden. Posle Minor GC, preživeli idu u Survivor prostor. Posle više GC ciklusa, prelaze u Old Gen. Major GC prazni Old Gen.

## JIT i GC - saradnja

U JVM-u GC ne radi izolovano. On sarađuje sa JIT kompajlerom koji ima dubok uvid u ponašanje programa.

### Escape Analysis

Objekat "beži" (escape-uje) ako postane vidljiv van metode (ili niti) u kojoj je kreiran. Objekat ne beži ako se ne vraća kao rezultat, ne čuva se u polju ili statičkoj promenljivoj, i ne izlazi iz metode.

Ako objekat ne beži, JIT može:

- Alocirati objekat na steku umesto na heap-u
- Primeniti scalar replacement - raspakuje objekat na stek i/ili registre

Rezultat: JIT smanjuje pritisak na GC, a programer piše kao da se svi objekti alociraju na heap-u i podležu GC-u. Programer ne mora da razmišlja o tome - optimizacija je transparentna.