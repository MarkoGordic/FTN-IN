# Skripta - Programski prevodioci - TEST2

Predmet: Programski prevodioci  
Program: Informacioni inženjering 2024/2025  

> [!NOTE]
> Skripta je napravljena uz pomoć predavanja, vežbi i zbirke za miniC. Moguće su greške, poželjno je korišćenje skripte uz zvanične materijale.

# 1. Formalni jezici i automati

Formalni jezik je bilo koji skup reči nad nekom azbukom.

| Deo prevodioca | Klasa jezika |
| --- | --- |
| **Leksika** | **regularni jezici** |
| **Sintaksa** | **kontekstno slobodni jezici** |
| Semantika | nije formalni jezik |

DKA - deterministički konačni automat  
NKA - nedeterministički automat  
PDA - potisni automat  

# 2. Generisanje koda

Generisanje koda je faza kompajliranja u kojoj se proizvodi datoteka sa ekvivalentnim programom napisanim na ciljnom programskom jeziku. Ciljni jezik je jezik niskog nivoa i može biti neki mašinski ili asemblerski jezik. Ciljni jezik na koji će (u primeru) biti preveden miniC programski jezik je hipotetski asemblerski jezik.

## 2.1 Hipotetski asemblerski kod

### 2.1.1 Osnovne osobine

- Hipotetska registarska mašina.
- Podrazumeva se da registri i memorijske lokacije zauzimaju po 4 bajta.
- Ukupno ima 16 registara (%0 do %15):
  - %0 do %12 - registri opšte namene (radni registri)
  - %13 - registar za povratnu vrednost funkcije
  - %14 - pokazivač stek frejma (stack frame pointer)
  - %15 - pokazivač vrha steka (stack top pointer)

### 2.1.2 Labele

- Labele započinju malim slovom, iza koga mogu da slede mala slova, cifre i podcrta `_` (alfabet je 7-bitni ASCII).
- Iza labele se navodi dvotačka.
- Ispred sistemskih labela navodi se znak `@`.

### 2.1.3 Operandi

- Neposredni operand: `$0`, `$-152`, ili `$lab` (adresa labele).
- Registarski operand: `%0`, `%1`, ... (vrednost je sadržaj registra).
- Direktni operand: `a` (adresa labele ili sadržaj lokacije, u zavisnosti od konteksta).
- Indirektni operand: `(%0)` (sadržaj memorijske lokacije koju adresira sadržaj registra).
- Indeksni operand: `-8(%14)`, `4(%14)`, `tabela(%0)` (baza + sadržaj registra).

Operandi se dele na:
- ulazne: neposredni, registarski, direktni, indirektni i indeksni
- izlazne: registarski, direktni, indirektni i indeksni

### 2.1.4 Instrukcije (pregled)

U sklopu hipotetskog asemblera imamo sledeće instrukcije (oznaka `x` se menja sa `S` za signed i `U` za unsigned operacije):

- CMPx (ulazni operand, ulazni operand) - upoređivanje dva registra
- JMP - uslovni skok na adresu
- JEQ - skok ako su jednaki
- JNE - skok ako nisu jednaki
- JLTx - skok ako je manje
- JLEx - skok ako je manje ili jednako
- JGTx - skok ako je veće
- JGEx - skok ako je veće ili jednako
- PUSH (ulazni operand) - stavljanje vrednosti na stek
- POP (izlazni operand) - skidanje vrednosti sa steka
- CALL (ulazni operand) - poziv funkcije
- RET - povratak iz funkcije
- ADDx (ulazni operand, ulazni operand, izlazni operand) - sabiranje
- SUBBx (ulazni operand, ulazni operand, izlazni operand) - oduzimanje
- MULx (ulazni operand, ulazni operand, izlazni operand) - množenje
- DIVx (ulazni operand, ulazni operand, izlazni operand) - deljenje
- MOV (ulazni operand, izlazni operand) - kopiranje vrednosti iz jednog registra u drugi
- WORD

Napomena: u opisu jezika naredbe se pojavljuju u varijantama `S` (signed), `U` (unsigned) i `F` (float), u zavisnosti od tipa.

### 2.1.5 Stack frame i adresiranje promenljivih

- Stack frame je deo steka koji je rezervisan za jednu funkciju prilikom njenog poziva.

Pristup argumentima preko %14:
- prvi argument: `8(%14)`
- drugi argument: `12(%14)`
- treći argument: `16(%14)`
- n-ti argument: `(4*n + 4)(%14)`

Pristup lokalnim promenljivima preko %14:
- prva lokalna: `-4(%14)`
- druga lokalna: `-8(%14)`
- treća lokalna: `-12(%14)`
- n-ta lokalna: `-4*n(%14)`

## 2.2 Primeri ekvivalencije

Pre implementacije generisanja koda, korisno je imati šeme ekvivalencije (šablone) za to kako se miniC iskazi prevode u asemblerski kod.

U primerima se podrazumeva da su `a`, `b`, `c` celobrojne označene lokalne promenljive, deklarisane tim redom.

### 2.2.1 Iskaz pridruživanja

Listing: jednostavan iskaz pridruživanja
```asm
a = b - a ; 
SUBS -8(%14), -4(%14), %0
MOV %0, -4(%14)
```

- Među-rezultati izraza se smeštaju u radne registre.
- Radni registar se zauzima za rezultat svakog aritmetičkog izraza i oslobađa čim se njegova vrednost preuzme.

Listing: složeniji izraz
```asm
a = (a - b) + (a - c) - c ;
SUBS -4(%14), -8(%14), %0
SUBS -4(%14), -12(%14), %1
ADDS %0, %1, %0
SUBS %0, -12(%14), %0
MOV %0, -4(%14)
```

**Caka (radni registri kao stek):**
- Zauzimanje i oslobađanje radnih registara ide LIFO (kao stek).
- Koristi se brojač `free_reg_num` kao pokazivač na prvi slobodan radni registar.

### 2.2.2 Funkcija

#### 2.2.2.1 Definicija funkcije

- Povratna vrednost funkcije se smešta u registar `%13`.
- Registar `%14` je frame pointer, `%15` je stack top.

Listing: definicija funkcije
```asm
int f(int p) {
  int a;
  return p + a;
}

f:
PUSH %14
MOV %15, %14
SUBS %15, $4, %15
@f_body:
ADDS 8(%14), -4(%14), %0
MOV %0, %13
JMP @f_exit
@f_exit:
MOV %14, %15
POP %14
RET
```

#### 2.2.2.2 Poziv funkcije

Listing: poziv funkcije (argument je izraz)
```asm
a = f(a + b);
ADDS -4(%14), -8(%14), %0
PUSH %0
CALL f
ADDS %15, $4, %15
MOV %13, -4(%14)
```

Listing: poziv funkcije (argument literal)
```asm
a = f(1);
PUSH $1
CALL f
ADDS %15, $4, %15
MOV %13, -4(%14)
```

### 2.2.3 if iskaz

Listing: if-else
```asm
if (a < b)
  a = 1;
else
  a = 2;

@if0:
CMPS -4(%14), -8(%14)
JGES @false0
@true0:
MOV $1, -4(%14)
JMP @exit0
@false0:
MOV $2, -4(%14)
@exit0:
```

**Caka (jedinstvene labele):**
- Labele moraju biti jedinstvene, najčešće tako što se koriste brojevi iz `lab_num`.

Listing: if bez else
```asm
if (a < b)
  a = 1;

@if0:
CMPS -4(%14), -8(%14)
JGES @false0
@true0:
MOV $1, -4(%14)
JMP @exit0
@false0:
@exit0:
```

## 2.3 miniC parser sa generisanjem koda

Datoteke `codegen.c/.h` sadrže pomoćne funkcije, a deo generisanja je direktno u parseru (`micko.y`). Parser pre parsiranja napravi `output.asm` i u nju generiše kod. Ako dođe do greške, datoteka se briše.

Najčešće korišćene funkcije:
```c
void gen_sslab(char *str1, char *str2);
void gen_snlab(char *str, int num);
void gen_cmp(int op1_index, int op2_index);
void gen_mov(int input_index, int output_index);
```

### 2.3.1 Promenljive u parseru

```c
int lab_num = -1;
FILE *output;
```

### 2.3.2 Definicija funkcije (micko.y)

Generisanje:
1) labela funkcije  
2) PUSH %14  
3) MOV %15, %14  
4) telo funkcije (zauzimanje prostora za lokale)  
5) exit labela  
6) MOV %14, %15  
7) POP %14  
8) RET  

```c
function
: type _ID
{
  fun_idx = lookup_symbol($2, FUN);
  if (fun_idx == -1)
    fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
  else
    err("redefinition of function '%s'", $2);

  code("\n%s:", $2);
  code("\n\t\t\tPUSH\t%%14");
  code("\n\t\t\tMOV\t%%15,%%14");
}
_LPAREN parameter _RPAREN
{
  set_atr1(fun_idx, $5);
  var_num = 0;
}
body
{
  clear_symbols(fun_idx + 1);
  gen_sslab($2, "_exit");
  code("\n\t\t\tMOV\t%%14,%%15");
  code("\n\t\t\tPOP\t%%14");
  code("\n\t\t\tRET");
}
;
```

### 2.3.3 Telo funkcije (zauzimanje prostora za lokalne)

```c
body
: _LBRACKET variable_list
{
  if (var_num)
    code("\n\t\t\tSUBS\t%%15,$%d,%%15", 4*var_num);
  gen_sslab(get_name(fun_idx), "_body");
}
statement_list _RBRACKET
;
```

### 2.3.4 Iskaz dodele

```c
assignment_statement
: _ID _ASSIGN num_exp _SEMICOLON
{
  int idx = lookup_symbol($1, (VAR | PAR));
  if (idx == -1)
    err("invalid lvalue '%s' in assignment", $1);
  else if (get_type(idx) != get_type($3))
    err("incompatible types in assignment");
  gen_mov($3, idx);
}
;
```

### 2.3.5 Aritmetičke operacije (radni registri)

```c
num_exp
: exp
| num_exp _AROP exp
{
  if (get_type($1) != get_type($3))
    err("invalid operands: arithmetic operation");

  int t1 = get_type($1);
  code("\n\t\t\t%s\t", get_arop_stmt($2, t1));
  print_symbol($1);
  code(",");
  print_symbol($3);
  code(",");

  if ($3 >= 0 && $3 <= LAST_WORKING_REG) free_reg();
  if ($1 >= 0 && $1 <= LAST_WORKING_REG) free_reg();

  $$ = take_reg();
  print_symbol($$);
  set_type($$, t1);
}
;
```

### 2.3.6 Izrazi (poziv funkcije u izrazu)

```c
exp
: literal
| _ID
{
  $$ = lookup_symbol($1, (VAR | PAR));
  if ($$ == -1)
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

### 2.3.7 Poziv funkcije

```c
function_call
: _ID
{
  fcall_idx = lookup_symbol($1, FUN);
  if (fcall_idx == -1)
    err("'%s' is not a function", $1);
}
_LPAREN argument _RPAREN
{
  if (get_atr1(fcall_idx) != $4)
    err("wrong number of arguments");

  code("\n\t\t\tCALL\t%s", get_name(fcall_idx));
  if ($4 > 0)
    code("\n\t\t\tADDS\t%%15,$%d,%%15", $4 * 4);

  set_type(FUN_REG, get_type(fcall_idx));
  $$ = FUN_REG;
}
;
```

### 2.3.8 Argument (PUSH)

```c
argument
: /* empty */
{ $$ = 0; }
| num_exp
{
  if (get_atr2(fcall_idx) != get_type($1))
    err("incompatible type for argument");

  free_if_reg($1);
  code("\n\t\t\tPUSH\t");
  print_symbol($1);
  $$ = 1;
}
;
```

### 2.3.9 if iskaz (labela, kontra skok, exit)

```c
if_part
: _IF _LPAREN
{
  $<i>$ = ++lab_num;
  gen_snlab("if", lab_num);
}
rel_exp
{
  code("\n\t\t\t%s\t@false%d",
    get_jump_stmt($4, TRUE), $<i>3);
  gen_snlab("true", $<i>3);
}
_RPAREN statement
{
  code("\n\t\t\tJMP\t@exit%d", $<i>3);
  gen_snlab("false", $<i>3);
  $$ = $<i>3;
}
;
```

```c
: if_part %prec ONLY_IF
{ gen_snlab("exit", $1); }
| if_part _ELSE statement
{ gen_snlab("exit", $1); }
;
```

### 2.3.10 Relacioni izraz (CMP)

```c
rel_exp
: num_exp _RELOP num_exp
{
  if (get_type($1) != get_type($3))
    err("invalid operands: relational operator");

  $$ = $2 + ((get_type($1) - 1) * RELOP_NUMBER);
  gen_cmp($1, $3);
}
;
```

### 2.3.11 return iskaz

```c
return_statement
: _RETURN num_exp _SEMICOLON
{
  if (get_type(fun_idx) != get_type($2))
    err("incompatible types in return");

  gen_mov($2, FUN_REG);
  code("\n\t\t\tJMP\t@%s_exit", get_name(fun_idx));
}
;
```

### 2.3.12 main() parsera (output.asm i brisanje na grešku)

```c
int main() {
  int synerr;

  init_symtab();
  output = fopen("output.asm", "w+");
  synerr = yyparse();
  clear_symtab();
  fclose(output);

  if (warning_count)
    printf("\n%d warning(s).\n", warning_count);

  if (error_count) {
    remove("output.asm");
    printf("\n%d error(s).\n", error_count);
  }

  if (synerr) return -1;
  else return error_count;
}
```

## 2.4 Runtime Environment

Podrška za izvršavanje programa napisanih u višim programskim jezicima.

Izvršno okruženje podrazumeva:
1. Organizaciju memorije
2. Upravljanje životnim vekom
3. Upravljanje pozivima funkcija
4. Upravljanje ostalim apstrakcijama

Izvršno okruženje predstavlja "mašinu" koja može biti virtuelna (npr. Java) ili konkretna (npr. C).

**Sekvenca pozivanja** je niz instrukcija koje se izvršavaju prilikom poziva funkcije sa ciljem formiranja aktivacionog bloka (activation block) na steku.

**Sekvenca povratka** je niz instrukcija koje se izvršavaju prilikom povratka iz funkcije sa ciljem uništavanja aktivacionog bloka na steku.

## 2.5 MICKO pravila

- Brojač odnosno pokazivač na stek registara se zove `free_reg_num` i njegova vrednost može da se kreće od 0 do 12 (imamo 13 registara opšte namene: %0 do %12).
- Ukoliko bi `free_reg_num` bio veći od 12, došlo bi do fatalne greške.
- Promenljiva `lab_num` se koristi za generisanje jedinstvenih oznaka (labela) u asemblerskom kodu.