# Generisanje koda

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Izvršna okruženja (Runtime Environment)

Izvršno okruženje predstavlja podršku za izvršavanje programa napisanih u višim programskim jezicima. Kompajler je dužan da ispravno prevede sve apstrakcije definisane jezikom i da omogući podršku za sve te apstrakcije na ciljnoj mašini. Na primer, kad izvršavanje dođe do poziva funkcije, potrebno je ispravno pozvati funkciju, proslediti argumente, izvršiti funkciju i vratiti kontrolu izvršavanja na mesto odakle je funkcija pozvana.

Izvršno okruženje obično podrazumeva:

- **Organizaciju memorije** - kako je podeljena memorija (code, data objects, function activations...)
- **Upravljanje životnim vekom** - trajanje (binding; runtime koncept vs. statički doseg - scope)
- **Upravljanje pozivima funkcija** - kako pozvati, kako preneti argumente, kako se vratiti iz funkcije
- **Upravljanje ostalim apstrakcijama** - izuzeci, garbage collection, kontrolisano izvršavanje, interfejsi prema OS (in/out)...

Izvršno okruženje predstavlja "mašinu" - računski model, interfejs za izvršavanje. Može biti konkretna mašina (u tom kontekstu često govorimo o apstraktnoj mašini) ili virtuelna mašina (međujezik i interpreter, npr. JVM). U svakom slučaju, prilikom prevođenja moramo da znamo: kako izgleda memorija, kako se realizuju pozivi funkcija, koji je skup instrukcija.

### Organizacija memorije

Tipična organizacija memorije:

```
+------------------+  niže adrese
|      code        |
+------------------+
|    static data   |
+------------------+
|      heap        |  HP raste naniže
+------------------+
|       ...        |
+------------------+
|      stack       |  SP raste naviše
+------------------+  više adrese
```

Ako se prevodi na fizičku mašinu, prevodilac koristi logički adresni prostor koji se kasnije mapira na fizičke adrese.

### Podrška za funkcije

Poziv funkcije predstavlja aktivaciju funkcije. Funkcije se pozivaju određenim redom, a pri završetku jedne funkcije kontrola se vraća na funkciju iz koje je pozvana. Formiraju se sekvence (calling and return sequences). Ovo ponašanje odgovara steku, pa se blokovi smeštaju na stek. Naziv za takav blok je **stek frejm** (stack frame).

### Aktivacioni blok (Activation Record - AR)

Za svaki poziv funkcije se određuje blok sa podacima koji odgovaraju i definišu taj poziv. Podaci u AR mogu biti:

- **Actual parameters** - argumenti / stvarni parametri
- **Returned values** - povratna vrednost funkcije
- **Control link** - AR funkcije koja poziva
- **Access link** - pristup podacima koji se nalaze na drugom mestu
- **Saved status** - stanje mašine u trenutku poziva (npr. povratna adresa i sadržaji nekih registara)
- **Local data** - lokalne promenljive
- **Temporaries** - privremeni podaci

U micko kompajleru, AR ima sledeću strukturu (pojednostavljenu):

- Argumenti / stvarni parametri
- Saved status / povratna adresa
- Control link / AR funkcije koja poziva
- Lokalne promenljive
- Povratna vrednost (kroz registar %13)

### Sekvence pozivanja i povratka

**Sekvenca pozivanja (calling sequence)** - niz aktivnosti koje izvršavaju FCR (caller - funkcija koja poziva) i FCE (callee - funkcija koja je pozvana) u cilju formiranja aktivacionog bloka:

FCR:
- Izračunati vrednosti za argumente
- Zauzeti i postaviti mesto za podatke koji predstavljaju argumente
- Postaviti povratnu adresu
- Preneti kontrolu na funkciju koja se poziva

FCE:
- Postaviti kontrolu veze i ostali deo statusa
- Obezbediti mesto za lokalne podatke

**Sekvenca povratka (return sequence):**

FCE:
- Postaviti povratnu vrednost
- Osloboditi prostor za lokalne podatke
- Prebaciti kontrolu na funkciju iz koje je pozvana

FCR:
- Osloboditi mesto zauzeto za podatke koji predstavljaju argumente

### Ugnježdene funkcije

Funkcije definisane u okviru neke druge funkcije. Problem se javlja kod nelokalnih vrednosti koje nisu globalne (lokalne promenljive za spoljašnju funkciju - unutrašnja ima pristup). Ne znamo kako će izgledati aktivacije funkcija (stek, ARs, šta ako je funkcija rekurzivna), pa moramo imati mehanizam za pretragu.

Ideja: kad se kreira AR za ugnježdenu funkciju, dodaje se Access link na najnoviju aktivaciju spoljašnje funkcije. Dobija se lanac aktivacija. Vodi se evidencija o leksičkim nivoima (dubina) da bismo znali gde duž lanca tražimo vrednosti. Alternativni pristup je Display - pomoćni niz pokazivača na nivoe kako bi se izbeglo prolaženje kroz ceo lanac.

## Hipotetski asemblerski jezik (HAJ)

### Arhitektura

Micko prevodi na hipotetski asemblerski jezik koji se izvršava na hipotetskoj registarskoj mašini sa sledećim karakteristikama:

- Registri i memorijske lokacije zauzimaju 4 bajta
- Postoji 16 registara:
  - **%0 - %12** - registri opšte namene (radni registri)
  - **%13** - registar za povratnu vrednost funkcije (FUN_REG)
  - **%14** - pokazivač frejma (FP - Frame Pointer)
  - **%15** - pokazivač steka (SP - Stack Pointer)

### Adresiranje

**Argumenti** se adresiraju u odnosu na FP (%14):

```
argument 1:  8(%14)
argument 2:  12(%14)
argument n:  (4 + n*4)(%14)
```

**Lokalne promenljive** se adresiraju u odnosu na FP (%14):

```
lokalna promenljiva 1:  -4(%14)
lokalna promenljiva 2:  -8(%14)
lokalna promenljiva n:  -(n*4)(%14)
```

Indeksni operand `x(%y)` znači: vrednost je sadržaj memorijske lokacije čija adresa je zbir vrednosti broja x i sadržaja registra y. Primeri: `8(%14)`, `-8(%14)`, `label1(%0)`.

### Skup instrukcija

**Aritmetičke operacije** (x je S za označene, U za neoznačene):

```
ADDx  ulazni, ulazni, izlazni    -- sabiranje
SUBx  ulazni, ulazni, izlazni    -- oduzimanje
MULx  ulazni, ulazni, izlazni    -- množenje
DIVx  ulazni, ulazni, izlazni    -- deljenje
```

**Prebacivanje vrednosti:**

```
MOV   ulazni, izlazni            -- kopiranje vrednosti
```

**Poređenje:**

```
CMPx  ulazni, ulazni             -- postavlja status registar
```

**Bezuslovni skok:**

```
JMP   ulazni                     -- skok na adresu
```

**Uslovni skokovi** (u zavisnosti od status registra):

```
JEQ   ulazni     -- skok ako je jednako
JNE   ulazni     -- skok ako nije jednako
JGTx  ulazni     -- skok ako je veće
JLTx  ulazni     -- skok ako je manje
JGEx  ulazni     -- skok ako je veće ili jednako
JLEx  ulazni     -- skok ako je manje ili jednako
```

**Upravljanje stekom:**

```
PUSH  ulazni     -- stavi vrednost na stek
POP   izlazni    -- skini vrednost sa steka
```

**Poziv i povratak:**

```
CALL  ulazni     -- smesti PC na stek, skoči na adresu
RET              -- skini adresu sa steka, skoči na nju
```

**Direktiva:**

```
WORD  broj       -- zauzimanje određenog broja memorijskih lokacija
```

## Primeri prevođenja

### Primer 1: jednostavna funkcija

```c
int fun() {
    int a;
    int b;
    a = 3;
    b = 2;
    a = b - a;
    return a;
}
```

Iskaz `a = b - a` se prevodi u:

```asm
SUBS  -8(%14), -4(%14), %0     ; b - a, rezultat u %0
MOV   %0, -4(%14)              ; smesti rezultat u a
```

Međurezultat se smešta u registar. Pretpostavlja se da su svi radni registri slobodni.

### Primer 2: složeniji izraz

```c
a = (a + b) + (c + d) - e;
```

Prevodi se u:

```asm
ADDS  -4(%14), -8(%14), %0       ; a + b -> %0
ADDS  -12(%14), -16(%14), %1     ; c + d -> %1
ADDS  %0, %1, %0                 ; (a+b) + (c+d) -> %0
SUBS  %0, -20(%14), %0           ; rezultat - e -> %0
MOV   %0, -4(%14)                ; smesti u a
```

Pretpostavka: a, b, c, d, e su lokalne promenljive deklarisane tim redom.

### Primer 3: kompletna funkcija sa pozivom

```c
int f(int p) {
    int a;
    a = 3;
    return p + a;
}
int main() {
    int a;
    a = f(7);
    return 0;
}
```

Generisani kod:

```asm
f:
        PUSH    %14                 ; sačuvaj stari FP
        MOV     %15,%14             ; postavi novi FP = SP
        SUBS    %15,$4,%15          ; zauzmi mesto za 1 lokalnu (a)
@f_body:
        MOV     $3,-4(%14)          ; a = 3
        ADDS    8(%14),-4(%14),%0   ; p + a -> %0
        MOV     %0,%13              ; povratna vrednost = %0
        JMP     @f_exit             ; skoči na izlaz
@f_exit:
        MOV     %14,%15             ; oslobodi lokalne (SP = FP)
        POP     %14                 ; vrati stari FP
        RET                         ; vrati se (PC sa steka)

main:
        PUSH    %14
        MOV     %15,%14
        SUBS    %15,$4,%15
@main_body:
        PUSH    $7                  ; stavi argument 7 na stek
        CALL    f                   ; pozovi f (PC na stek, skoči)
        ADDS    %15,$4,%15          ; oslobodi argument sa steka
        MOV     %13,%0              ; preuzmi povratnu vrednost
        MOV     %0,-4(%14)          ; a = f(7)
        MOV     $0,%13              ; return 0
        JMP     @main_exit
@main_exit:
        MOV     %14,%15
        POP     %14
        RET
```

### Detaljan tok poziva f(7) na steku

Korak po korak šta se dešava na steku:

1. `PUSH $7` - argument 7 stavljen na stek, SP se pomera
2. `CALL f` - adresa naredne instrukcije (addr 22) stavljena na stek, PC = adresa f
3. `PUSH %14` - stari FP stavljen na stek
4. `MOV %15,%14` - FP = SP (novi frejm pointer)
5. `SUBS %15,$4,%15` - SP se pomera za 4 bajta (mesto za lokalnu a)
6. `MOV $3,-4(%14)` - a = 3 (lokalna promenljiva na -4 od FP)
7. `ADDS 8(%14),-4(%14),%0` - p + a (argument na +8 od FP, lokalna na -4) -> %0 = 10
8. `MOV %0,%13` - %13 = 10 (povratna vrednost)
9. `JMP @f_exit` - skoči na izlaz
10. `MOV %14,%15` - SP = FP (oslobodi lokalne)
11. `POP %14` - vrati stari FP
12. `RET` - PC = adresa sa steka (addr 22, nastavak u main)
13. `ADDS %15,$4,%15` - oslobodi argument sa steka
14. `MOV %13,-4(%14)` - a = 10

### Primer 4: if-else

```c
if(a < b)
    a = 1;
else
    a = 2;
```

Generisani kod:

```asm
@if0:
        CMPS    -4(%14),-8(%14)     ; uporedi a i b
        JGES    @false0             ; ako a >= b, skoči na false
@true0:
        MOV     $1,-4(%14)          ; a = 1
        JMP     @exit0              ; skoči na kraj
@false0:
        MOV     $2,-4(%14)          ; a = 2
@exit0:
```

Obratiti pažnju: suprotno (negacija) od `a < b` je `a >= b`, a ne `a > b`. Skokovi su "obrnuti" - ako je uslov `<`, generiše se skok `JGES` (skok ako je >=, tj. suprotno od uslova).

## Implementacija generisanja koda

### Pomoćni fajlovi

U micko kompajleru, generisanje koda dodaje sledeće fajlove i dopunjuje postojeće:

- `defs.h` - dopunjen (konstante, makroi)
- `codegen.h` - dodat (deklaracije funkcija)
- `codegen.c` - dodat (implementacija)
- `micko.y` - dopunjen (GK akcije u pravilima)

### Makro code i izlazni fajl

```c
// defs.h
#define code(args...) ({fprintf(output, args); \
    if (++out_lin > 2000) err("Too many output lines"), exit(1); })

// micko.y
output = fopen("output.asm", "w+");
```

Generisani kod se upisuje u fajl `output.asm` dok se parsira.

### Upravljanje registrima

```c
// defs.h
#define LAST_WORKING_REG 12
#define FUN_REG 13

// codegen.c
int free_reg_num = 0;
```

Radni registri su 0-12. Zauzimaju se kao stek (prvi slobodni) i oslobađaju se posle korišćenja.

```c
int take_reg(void) {
    if(free_reg_num > LAST_WORKING_REG) {
        err("Compiler error! No free registers!");
        exit(EXIT_FAILURE);
    }
    return free_reg_num++;
}

void free_reg(void) {
    if(free_reg_num < 1) {
        err("Compiler error! No more registers to free!");
        exit(EXIT_FAILURE);
    }
    else
        set_type(--free_reg_num, NO_TYPE);
}

void free_if_reg(int reg_index) {
    if(reg_index >= 0 && reg_index <= LAST_WORKING_REG)
        free_reg();
}
```

### Generisanje imena simbola

Funkcija `gen_sym_name` generiše odgovarajući operand na osnovu vrste simbola iz tabele simbola:

```c
void gen_sym_name(int index) {
    if(index > -1) {
        if(get_kind(index) == VAR)        // lokalna promenljiva
            code("-%d(%%14)", get_atr1(index) * 4);
        else if(get_kind(index) == PAR)   // parametar
            code("%d(%%14)", 4 + get_atr1(index) * 4);
        else if(get_kind(index) == LIT)   // literal
            code("$%s", get_name(index));
        else                               // funkcija, registar
            code("%s", get_name(index));
    }
}
```

### Generisanje poređenja i premeštanja

```c
void gen_cmp(int op1_index, int op2_index) {
    if(get_type(op1_index) == INT)
        code("\n\t\tCMPS \t");
    else
        code("\n\t\tCMPU \t");
    gen_sym_name(op1_index);
    code(",");
    gen_sym_name(op2_index);
    free_if_reg(op2_index);
    free_if_reg(op1_index);
}

void gen_mov(int input_index, int output_index) {
    code("\n\t\tMOV \t");
    gen_sym_name(input_index);
    code(",");
    gen_sym_name(output_index);
    if(output_index >= 0 && output_index <= LAST_WORKING_REG)
        set_type(output_index, get_type(input_index));
    free_if_reg(input_index);
}
```

### GK za definiciju funkcije

```yacc
function
    : type _ID
      {
          fun_idx = lookup_symbol($2, FUN);
          if(fun_idx == NO_INDEX)
              fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
          else
              err("redefinition of function '%s'", $2);
          code("\n%s:", $2);              // labela: f:
          code("\n\t\t\tPUSH\t%%14");     // sačuvaj stari FP
          code("\n\t\t\tMOV \t%%15,%%14"); // novi FP = SP
      }
      _LPAREN parameter _RPAREN body
      {
          clear_symbols(fun_idx + 1);
          var_num = 0;
          code("\n@%s_exit:", $2);         // labela: @f_exit:
          code("\n\t\t\tMOV \t%%14,%%15"); // SP = FP
          code("\n\t\t\tPOP \t%%14");      // vrati stari FP
          code("\n\t\t\tRET");             // vrati se
      }
    ;
```

### GK za telo funkcije

```yacc
body
    : _LBRACKET variable_list
      {
          if(var_num)
              code("\n\t\t\tSUBS\t%%15,$%d,%%15", 4 * var_num);
          code("\n@%s_body:", get_name(fun_idx));
      }
      statement_list _RBRACKET
    ;
```

### GK za return

```yacc
return_statement
    : _RETURN num_exp _SEMICOLON
      {
          if(get_type(fun_idx) != get_type($2))
              err("incompatible types in return");
          gen_mov($2, FUN_REG);
          code("\n\t\t\tJMP \t@%s_exit", get_name(fun_idx));
      }
    ;
```

### GK za aritmetičke operacije

```yacc
num_exp
    : exp
    | num_exp _AROP exp
      {
          if(get_type($1) != get_type($3))
              err("invalid operands: arithmetic operation");
          int t1 = get_type($1);
          code("\n\t\t%s\t",
               ar_instructions[$2 + (t1 - 1) * AROP_NUMBER]);
          gen_sym_name($1);
          code(",");
          gen_sym_name($3);
          code(",");
          free_if_reg($3);
          free_if_reg($1);
          $$ = take_reg();
          gen_sym_name($$);
          set_type($$, t1);
      }
    ;
```

Pomoćne tabele:

```c
enum arops { ADD, SUB, MUL, DIV, AROP_NUMBER };
static char *ar_instructions[] = { "ADDS", "SUBS", "MULS", "DIVS",
                                   "ADDU", "SUBU", "MULU", "DIVU" };
```

### GK za poziv funkcije

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
              err("wrong number of arguments");
          code("\n\t\t\tCALL\t%s", get_name(fcall_idx));
          if($4 > 0)
              code("\n\t\t\tADDS\t%%15,$%d,%%15", $4 * 4);
          set_type(FUN_REG, get_type(fcall_idx));
          $$ = FUN_REG;
      }
    ;
```

### GK za argument

```yacc
argument
    : /* empty */
      { $$ = 0; }
    | num_exp
      {
          if(get_atr2(fcall_idx) != get_type($1))
              err("incompatible type for argument in '%s'",
                  get_name(fcall_idx));
          free_if_reg($1);
          code("\n\t\t\tPUSH\t");
          gen_sym_name($1);
          $$ = 1;
      }
    ;
```

### GK za exp (preuzimanje povratne vrednosti)

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
      {
          $$ = take_reg();
          gen_mov(FUN_REG, $$);
      }
    | _LPAREN num_exp _RPAREN
      { $$ = $2; }
    ;
```

### GK za dodelu

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
          gen_mov($3, idx);
      }
    ;
```

### GK za if-else

```yacc
if_statement
    : if_part %prec ONLY_IF
      { code("\n@exit%d:", $1); }
    | if_part _ELSE statement
      { code("\n@exit%d:", $1); }
    ;

if_part
    : _IF _LPAREN
      {
          $<i>$ = ++lab_num;
          code("\n@if%d:", lab_num);
      }
      rel_exp
      {
          code("\n\t\t%s\t@false%d", opp_jumps[$4], $<i>3);
          code("\n@true%d:", $<i>3);
      }
      _RPAREN statement
      {
          code("\n\t\tJMP \t@exit%d", $<i>3);
          code("\n@false%d:", $<i>3);
          $$ = $<i>3;
      }
    ;
```

Tabela obrnutih skokova:

```c
static char* opp_jumps[] = {
    "JGES", "JLES", "JGTS", "JLTS", "JNE ", "JEQ ",  // INT
    "JGEU", "JLEU", "JGTU", "JLTU", "JNE ", "JEQ "   // UINT
};
```

### GK za relacioni izraz

```yacc
rel_exp
    : num_exp _RELOP num_exp
      {
          if(get_type($1) != get_type($3))
              err("invalid operands: relational operator");
          $$ = $2 + ((get_type($1) - 1) * RELOP_NUMBER);
          gen_cmp($1, $3);
      }
    ;
```

Enumeracija i flex pravila:

```c
enum relops { LT, GT, LE, GE, EQ, NE, RELOP_NUMBER };

// u flex-u:
"<"  { yylval.i = LT; return _RELOP; }
">"  { yylval.i = GT; return _RELOP; }
"<=" { yylval.i = LE; return _RELOP; }
">=" { yylval.i = GE; return _RELOP; }
"==" { yylval.i = EQ; return _RELOP; }
"!=" { yylval.i = NE; return _RELOP; }
```

### Pojmovi bez generisanja koda

Sledeći pojmovi ne zahtevaju generisanje koda: `program`, `function_list`, `variable_list`, `statement_list`, `statement`, `compound_statement`, `parameter`, `variable`, `literal`.

## Izvršavanje i poređenje

### Hipsim simulator

`hipsim` je program koji simulira izvršavanje na hipotetskoj mašini. Prima `.asm` fajlove i nudi:

- Rezultat izvršavanja (brzo testiranje)
- Korak-po-korak izvršavanje (stanje memorije i registri)

### Poređenje sa pravim kompajlerima

Isti program preveden micko kompajlerom (HAJ) i gcc kompajlerom (x86-64) pokazuje strukturalnu sličnost - oba koriste iste principe (push FP, postavi novi FP, zauzmi lokalne, vrati FP, RET). Razlike su u detaljima skupa instrukcija i konvencijama (gcc koristi `rbp`/`rsp`, prenosi argument u registru `edi`, koristi `eax` za povratnu vrednost, itd.).

Poređenje sa MIPS arhitekturom (RISC) pokazuje da se principi čuvaju, ali je sintaksa i konvencija potpuno drugačija.

Clang kompajler, pored generisanja koda, može da ispiše i AST (apstraktno sintaksno stablo) programa, što je primer međureprezentacije o kojoj smo govorili u kontekstu semantičke analize.

Za istraživanje različitih kompajlera i arhitektura: **Compiler Explorer** - godbolt.org.