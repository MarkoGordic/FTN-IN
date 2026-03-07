# Python - internals iz ugla programskih prevodilaca

Napomena: Sve je pojednostavljeno i služi kao ilustracija.

## Modeli izvršavanja - poređenje

Različiti jezici koriste različite modele:

**C model**: `.c` -> kompajler -> `exe, out,...` (izvršni fajl koji se direktno pokreće na mašini)

**Java model**: `.java` -> kompajler (javac) -> `.class` (bytecode) -> VM (JVM) izvršava class fajl. Kompilacija i izvršavanje su odvojeni koraci, na različitim mašinama mogu biti različite VM.

**Python model**: `.py` -> kompajler + VM su objedinjeni u jednom programu (`python`). Komanda `python` sadrži i kompajler (koji prevodi na bytecode) i PVM (Python Virtual Machine) koja izvršava taj bytecode. Kompajler i VM su "unutra", korisnik vidi samo `.py` fajl i rezultate izvršavanja.

Ključna razlika: kod Jave korisnik eksplicitno poziva kompajler (`javac`), a zatim VM (`java`). Kod Pythona, kompajler se poziva implicitno - korisnik pokreće `python program.py` i odmah vidi rezultate. Često korisnici nisu ni svesni da postoji prevođenje (kompajler) jer ga ne pozivaju eksplicitno.

## Alati - poređenje Java i Python

**Java:**

- `javac` - kompajler - izlaz su `.class` fajlovi koji sadrže bytecode (nečitljiv)
- `java` - izvršava class na JVM (interpreter)
- `javap` - disasembler za class fajlove

**Python (CPython):**

- `python` - kompajler i PVM interpreter u jednom
- `py_compile` - izlaz `.pyc` fajl koji sadrži bytecode (nečitljiv): `python -m py_compile test.py`
- `dis` - podrška za disasembler za bytecode: `python -m dis test.py` ili `dis.dis(...)`

## Python bytecode - primer

```python
def saberi():
    a = 5
    b = 3
    a = a + b
    print(a)
```

Disassemblirani bytecode (`dis.dis(test.saberi)`):

```
  2     0 LOAD_CONST      1 (5)        # push konstantu 5 na stek
        3 STORE_FAST      0 (a)        # pop sa steka u lokalnu a

  3     6 LOAD_CONST      2 (3)        # push konstantu 3 na stek
        9 STORE_FAST      1 (b)        # pop sa steka u lokalnu b

  4    12 LOAD_FAST       0 (a)        # push a na stek
       15 LOAD_FAST       1 (b)        # push b na stek
       18 BINARY_ADD                    # pop oba, saberi, push rezultat
       19 STORE_FAST      0 (a)        # pop rezultat u a

  5    22 LOAD_GLOBAL     0 (print)    # push referencu na print
       25 LOAD_FAST       0 (a)        # push a
       28 CALL_FUNCTION   1            # pozovi print sa 1 argumentom
       31 POP_TOP                      # ukloni povratnu vrednost sa steka
       32 LOAD_CONST      0 (None)     # push None
       35 RETURN_VALUE                 # return None
```

Brojevi sa leve strane (2, 3, 4, 5) su linije u izvornom kodu. Brojevi u sredini (0, 3, 6...) su bajt ofseti.

### Metapodaci o funkciji

Sa `dis.show_code(test.saberi)` dobijamo:

```
Name:          saberi
Filename:      ...test.py
Argument count: 0
Kw-only arguments: 0
Number of locals: 2
Stack size:    2
Flags:         OPTIMIZED, NEWLOCALS, NOFREE
Constants:
   0: None
   1: 5
   2: 3
Names:
   0: print
Variable names:
   0: a
   1: b
```

Ovaj ispis pokazuje da se za svaku funkciju čuvaju: konstante (Constants), globalna imena (Names), lokalne promenljive (Variable names), veličina steka, broj lokalnih promenljivih, i razni flegovi.

## Gramatika Pythona

Python koristi PEG (Parsing Expression Grammar) parser. Gramatika je definisana u fajlu `python.gram`.

Primer pravila iz gramatike:

```
simple_stmt:
    | assignment
    | star_expressions
    | return_stmt
    | import_stmt
    ...

compound_stmt:
    | function_def
    | if_stmt
    | class_def
    | with_stmt
    | for_stmt
    | try_stmt
    | while_stmt
    | match_stmt
    ...

factor:
    | '+' factor
    | '-' factor
    | '~' factor
    | power
```

U implementaciji, pravila sadrže i akcije za kreiranje AST čvorova:

```
factor[expr_ty] (memo):
    | '+' a=factor { _PyAST_UnaryOp(UAdd, a, EXTRA) }
    | '-' a=factor { _PyAST_UnaryOp(USub, a, EXTRA) }
    | '~' a=factor { _PyAST_UnaryOp(Invert, a, EXTRA) }
    | power
```

Resursi: `docs.python.org/3/reference/grammar.html`, `devguide.python.org/internals/parser/`, `peps.python.org/pep-0617/`

## AST u Pythonu

Python omogućava programski pristup AST-u putem `ast` modula:

```python
import ast, inspect, test

tree = ast.parse(inspect.getsource(test.saberi))
ast.dump(tree)
```

Rezultat za funkciju `saberi`:

```
Module(body=[
    FunctionDef(name='saberi',
        args=arguments(args=[], ...),
        body=[
            Assign(targets=[Name(id='a', ctx=Store())],
                   value=Num(n=5)),
            Assign(targets=[Name(id='b', ctx=Store())],
                   value=Num(n=3)),
            Assign(targets=[Name(id='a', ctx=Store())],
                   value=BinOp(left=Name(id='a', ctx=Load()),
                               op=Add(),
                               right=Name(id='b', ctx=Load()))),
            Expr(value=Call(func=Name(id='print', ctx=Load()),
                           args=[Name(id='a', ctx=Load())],
                           keywords=[]))
        ],
        decorator_list=[], returns=None)
])
```

Za vizualizaciju AST-a može se koristiti: `python-ast-explorer.com`.

### Transformacija AST-a

Moguće je programski menjati AST pre izvršavanja, što omogućava napredne metaprogramske tehnike. Primer - zamena celobrojnog deljenja razlomcima:

```python
import ast
from fractions import Fraction

class IntegerWrapper(ast.NodeTransformer):
    """Wraps all integers in a call to Integer()"""
    def visit_Num(self, node):
        if isinstance(node.n, int):
            return ast.Call(func=ast.Name(id='Integer', ctx=ast.Load()),
                           args=[node], keywords=[])
        return node

class Integer(object):
    def __init__(self, value):
        self.value = value
    def __truediv__(self, other):
        if isinstance(other, Integer):
            return Fraction(numerator=self.value, denominator=other.value)

code = "print((1/10)+(2/10))"

print("Without AST transformation:")
exec(code)
# 0.30000000000000004

print("With AST transformation:")
tree = ast.parse(code)
tree = IntegerWrapper().visit(tree)
ast.fix_missing_locations(tree)
co = compile(tree, "<ast>", "exec")
exec(co)
# 3/10
```

Bez transformacije, `(1/10) + (2/10)` daje `0.30000000000000004` (floating-point greška). Sa transformacijom AST-a, svi integeri se zamenjuju `Integer` objektima koji koriste `Fraction` za deljenje, pa rezultat je tačan: `3/10`.

## Izvršavanje bytecoda - CPython implementacija

Jezgro CPython interpretera je u fajlu `ceval.c`. Osnovni princip je petlja sa switch naredbom koja obrađuje svaki opcode:

```c
DISPATCH();
{
    switch (opcode)
    {
#include "generated_cases.c.h"
    ...
```

Primeri implementacije instrukcija (iz `executor_cases.c.h`):

```c
case _LOAD_CONST: {
    PyObject *value;
    oparg = CURRENT_OPARG();
    value = GETITEM(FRAME_CO_CONSTS, oparg);
    Py_INCREF(value);             // inkrementiraj reference count
    stack_pointer[0] = value;
    stack_pointer += 1;           // push na stek
    break;
}

case _STORE_FAST: {
    PyObject *value;
    oparg = CURRENT_OPARG();
    value = stack_pointer[-1];
    SETLOCAL(oparg, value);       // postavi lokalnu promenljivu
    stack_pointer += -1;          // pop sa steka
    break;
}

case _POP_TOP: {
    PyObject *value;
    value = stack_pointer[-1];
    Py_DECREF(value);             // dekrementiraj reference count
    stack_pointer += -1;
    break;
}
```

Primetiti `Py_INCREF` i `Py_DECREF` - CPython koristi reference counting za upravljanje memorijom.

### Computed GOTOs optimizacija

Tradicionalna bytecode petlja koristi `switch` naredbu, koju kompajler optimizuje kao jedan indirektni skok sa lookup tabelom adresa. Međutim, pošto je taj indirektni skok deljeni za sve opcode-ove, CPU teško predviđa gde će sledeći skok biti.

"Threaded code" (computed GOTOs) koristi eksplicitnu tabelu skokova i eksplicitnu instrukciju indirektnog skoka na kraju svakog opcode-a. Pošto je instrukcija skoka na različitoj adresi za svaki opcode, CPU može bolje da predvidi sledeći skok.

Ova optimizacija (korišćenjem GCC labels-as-values ekstenzije) daje 15-20% ubrzanje u odnosu na normalnu switch verziju, zavisno od kompajlera i CPU arhitekture.

Napomena: mora se paziti da kompajler ne "optimizuje" indirektne skokove tako što ih deli između opcode-ova. Takve optimizacije se mogu isključiti na GCC-u sa `-fno-gcse` flagom.

## CPython vs PyPy

### CPython

- Referentna implementacija Pythona, napisana u C-u
- Koristi optimizovani interpreter, ne JIT (za sad)
- **Quickening** - zamena instrukcija drugim bytecode instrukcijama tokom izvršavanja, dozvoljava dinamičku promenu koda
- Fokus na stabilnost i praktičnost

### PyPy

- Alternativna implementacija Pythona
- Koristi JIT kompajler
- Agresivno optimizuje
- Bolje performanse za dugotrajne programe
- Otežava debug

## Tipizacija

Python je dinamički tipiziran jezik, ali postoji podrška za opcione tipske anotacije:

- `mypy` - opcioni statički type checker za Python
- PEP-ovi za tipizaciju: `peps.python.org/topic/typing`

Resursi: `mypy.readthedocs.io`, `mypy-lang.org`