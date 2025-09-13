## 1. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class MyClass {};

void f(MyClass a) {
    cout << "Nisi više ";
}

void f(const MyClass *a) {
    cout << "moja bol";
}

int main() {
    MyClass x;
    f(x);
    f(&x);
    return 0;
}
```

- A. Nisi više moja bol
- B. moja bol
- C. Nisi više
- D. Kod se neće kompajlirati zbog ambigue pozicije poziva funkcije f.
- E. Ništa od ponuđenog.
- F. moja bolNisi više

**Tačan odgovor: A. Nisi više moja bol**

## 2. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class IntArray {
    int el[10];

public:
    int& operator[](int i) {
        cout << "Sweet";
        return el[i];
    }

    int operator[](int i) const {
        cout << "Cry";
        return el[i];
    }
};

int main() {
    IntArray ia;
    ia[5] = 10;
    cout << ia[5];
    return 0;
}
```

- A. CrySweet10
- B. SweetCry10
- C. SweetSweet10
- D. CryCry10
- E. Kod se neće kompajlirati zbog redefinicije operatora [].

**Tačan odgovor: C. SweetSweet10**

## 3. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "Već "; }
};

class B {
public:
    B() { cout << "odavno "; }
};

class C {
public:
    C() { cout << "spremam "; }
};

class D {
private:
    A a;
    B b;
public:
    D() { cout << "svog "; }
};

class E : public D {
private:
    C c;
public:
    E() { cout << "mrkova "; }
};

class F : public E {
public:
    F() { cout << "stalno" << endl; }
};

int main()
{
    F f;
    return 0;
}
```

**Tačan odgovor: Već odavno svog spremam mrkova stalno**

## 4. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A {
public:
    A()  { cout << "I "; }
    ~A() { cout << "last "; }
};

class B : public A {
public:
    B()  { cout << "always "; }
    ~B() { cout << "you "; }
};

class C : public B {
private:
    A a;
public:
    C()  { cout << "make "; }
    ~C() { cout << "were "; }
};

class D : public C {
private:
    B b;
public:
    D()  { cout << "it "; }
    ~D() { cout << "feel "; }
};

class E : public D {
public:
    E()  { cout << "you "; }
    ~E() { cout << "like "; }
};

class F : public E {
public:
    F()  { cout << "you "; }
    ~F() { cout << "one"; }
};

int main() {
    F f;
    return 0;
}
```

**Tačan odgovor: I always I make I always it you you onelike feel you last were last you last**

## 5. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;
    int &c = a;
    int *d = &b;
    int *e = &a;
    int &f = b;
    int *g = &a;

    c = 20;
    *e = 30;
    f = c;
    *d = 40;
    g = d;
    *g = 50;

    int &h = *g;
    h = 60;

    *e = *d + c;
    f = *e - h;

    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
```

**Tačan odgovor: a = 90, b = 30**

## 6. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

struct Base {
    static void f()    { cout << "B"; }
    virtual void g()   { cout << "b"; }
};

struct Derived : Base {
    static void f()    { cout << "D"; }
    void g() override  { cout << "d"; }
};

int main() {
    Base *obj = new Derived();
    obj->f();
    obj->g();
    return 0;
}
```

**Tačan odgovor: Bd**

## 7. (Teorija) Koji od navedenih iskaza su tačni?

1. Konstruktor objekta se automatski poziva pri kreiranju instance klase.

2. Destruktor se poziva automatski prilikom uništavanja objekta ili izlaska iz opsega.

3. Kompozicija je veza između klasa u kojoj jedna klasa sadrži instancu druge klase.

4. Public članovima klase može se pristupiti i izvan te klase (javno su dostupni svuda).

5. Apstraktna klasa je ona koja sadrži bar jednu čisto virtuelnu (apsktraktnu) metodu.

---

- A. Tačni su iskazi 1, 2 i 3.
- B. Tačni su iskazi 1, 3 i 5.
- C. Svi navedeni iskazi su tačni.
- D. Nijedan od navedenih iskaza nije tačan.
- E. Tačni su samo iskazi 2 i 4.

**Tačan odgovor: C**

## 8. (Teorija) Koja od navedenih tvrdnji o nasleđivanju je tačna?

1. Java podržava višestruko nasleđivanje (jedna klasa može imati više roditeljskih klasa).

2. C++ ne podržava višestruko nasleđivanje klasa.

3. U Javi sve klase (posredno ili neposredno) nasleđuju klasu `Object`.

4. C++ klasa ne može imati više od jedne bazne klase.

---

- A. Tačni su iskazi 1, 2.
- B. Tačni su iskazi 1, 2 i 3.
- C. Svi navedeni iskazi su tačni.
- D. Nijedan od navedenih iskaza nije tačan.
- E. Tačan je samo iskaz 3
- F. Tačan je samo iskaz 2

**Tačan odgovor: E**

## 9. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 4;
    int b = 3;
    int &r = a;
    int *p = &b;
    int *q = &a;

    cout << a++ << b;
    cout << r << ++b;
    cout << (*p) << q[0]--;
    cout << a << b;

    return 0;
}
```

**Tačan odgovor: 43544544**

## 10. (C++) Koja je ispravna implementacija destruktora klase `Box` koji je dat u nastavku?

```cpp
#include <cstdlib>

template<class T, class U, int N>
class Box {
    T* p;
    U  a[N];
    U* q;
public:
    Box() : p(new T[N]), q(new U) {}
    ~Box(); // dopuni
};
```

- A: Box::~Box(){ delete p; delete q; }
- B: Box::~Box(){ delete[] p; delete[] q; }
- C: Box::~Box(){ delete[] p; delete q; }
- D: Box::~Box(){ }

**Tačan odgovor: C**

## 11. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class B {
public:
    int m, n;
    B(){ m=5; n=6; }
    ~B(){ cout<<m<<n; }
    friend ostream& operator<<(ostream &out, const B& b) {
        out<<b.m<<b.n;
        return out;
    }
};

void g1(B b){ b.m=7; b.n=7; }
void g2(B& b){ b.m=3; b.n=3; }
void g3(const B& b){ cout<<b; }

int main() {
    B b;
    g2(b);
    cout<<b;
    g1(b);
    g3(b);
    return 0;
}
```

- A: 33 77 77 33
- B: 33 77 77 77
- C: 33 33 77 77
- D: 33 77 33 33

**Tačan odgovor: 33773333**

## 12. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A {
    int a, b;
public:
    A() : a(1), b(2) {}
    A(int aa = 2, int bb = 4) : a(aa), b(bb) {}
    A(const A& aa) : a(aa.a), b(aa.b) {}
    void ispis() { cout << ++a << b++; }
};

int main() {
    A a, a2(3,4), a3(a2);
    a.ispis();
    a2.ispis();
    a3.ispis();
    return 0;
}
```

- A: 223445
- B: 224454
- C: 224444
- D: 234544
- E: Neće se ništa ispisati jer ćemo dobiti upozorenje o grešci

**Tačan odgovor: E**

## 13. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

enum Vrednosti {
    A = -1,
    B = 2,
    C = A + B,
    D = B + C,
    E = D - A,
    F = E,
    G = F + C
};

int main() {
    Vrednosti niz[7] = {A, B, C, D, E, F, G};
    for (int i = 0; i < 7; i++) {
        cout << niz[i];
    }
    return 0;
}
```

- A: -1213445
- B: -121345
- C: 0213445
- D: -1213345

**Tačan odgovor: A**

## 14. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

template<class Typ, int Val>
class Temp {
    Typ i, j;
public:
    Temp() { i = Val; j = Val; }
    Temp(Typ ii, Typ jj) { this->i = ++ii; this->j = jj; }
    ~Temp() { cout << i << j; }
};

int main() {
    Temp<int, 1> t1;
    Temp<int, 2> t2(3, 4);
    return 0;
}
```

- A: 1144
- B: 4411
- C: 11
- D: 44

**Tačan odgovor: B**

## 15. (Teorija) Koje od navedenih tvrdnji su netačne?

1. new se koristi za dinamičko alociranje memorije.

2. Apstraktna klasa sadrži bar jednu apstraktnu (pure virtual) metodu.

3. delete oslobađa dinamički alociranu memoriju.

4. this se koristi za dinamičko alociranje memorije.

---

- A: 1 i 2
- B: samo 2
- C: samo 4
- D: svi
- E: samo 3 i 4
- F: samo 1, 2 i 3

**Tačan odgovor: C**

## 16. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class T {
public:
    T(){ cout << "1"; }
    virtual void show(){ cout << "2"; }
};

class Q : public T {
public:
    Q(){ cout << "3"; }
    void show(){ cout << "4"; }
    ~Q(){ cout << "5"; }
};

int main(){
    T t;
    Q q;
    T* p = &t;
    t.show();
    p = &q;
    p->show();
    return 0;
}
```

- A: 11324
- B: 11325
- C: 113245
- D: 112345

**Tačan odgovor: C**

## 17. (C++) Koje tvrdnje su tačne?

1. Deklaracija metode ne sadrži telo metode.

2. Definicija metode može biti van tela klase (Class::metoda).

3. Definicija metode mora biti unutar tela klase.

4. Deklaracija metode mora biti unutar tela klase.

---

- A: 1 i 2
- B: 1 i 3
- C: 2 i 4
- D: 1, 2 i 4
- E: samo 3
- F: sve su tačne

**Tačan odgovor: A**

## 18. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class K {
    int x, y, z;
public:
    K(){ x = 1; y = 2; z = 3; }
    void f(){
        for (int i = 1; i <= 3; i++){
            for (int j = 0; j < i; j++){
                x += i;
                y += j;
            }
            z += i;
        }
        cout << x << y << z;
    }
};

int main(){
    K k;
    k.f();
}
```

- A: 4718
- B: 1569
- C: 1596
- D: 1469

**Tačan odgovor: B**

## 19. (Teorija) Koje od sledećih iskaza su tačni?

1. Konstruktor služi da napravi objekat.
2. Destruktor se poziva automatski.
3. Kompozicija je veza između klasa.
4. Public članovima se može pristupiti iz unutrašnje (ugnježdene) klase.
5. Apstraktna klasa sadrži bar jednu apstraktnu (pure virtual) metodu.

---

- A: 1, 2 i 3
- B: 1, 2, 3 i 5
- C: 2, 3 i 4
- D: svi su tačni
- E: samo 1 i 5
- F: nijedan

**Tačan odgovor: D (svi su tačni)**

## 20. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct KlasaX {
    static int x;
    KlasaX(){ ++x; }
    ~KlasaX(){ --x; }
};

struct KlasaY : public KlasaX {
    static int y;
    KlasaY(){ ++y; }
    ~KlasaY(){ --y; }
    static void test(){
        KlasaY local;
    }
};

struct KlasaZ {
    KlasaZ(){ KlasaX::x += 2; KlasaY::y -= 1; }
    ~KlasaZ(){ KlasaX::x -= 1; KlasaY::y += 3; }
};

int KlasaX::x = 1;
int KlasaY::y = (int)std::pow(2,2);

int main(){
    KlasaY y1;
    KlasaX x1;
    KlasaZ z1;
    KlasaY::test();
    KlasaY y2;
    cout << KlasaY::y << KlasaX::x;
    return 0;
}
```

- A: 75
- B: 57
- C: 56
- D: 76

**Tačan odgovor: C**

## 21. (Teorija) Označi NETAČAN odgovor

1. Metoda se proglašava virtuelnom ključnom reči virtual ispred povratnog tipa.

2. Postoje pokazivači na reference.

3. Virtuelnost se nasleđuje (ostaje virtuelna kroz hijerarhiju).

4. Ne postoje pokazivači na reference.

---

- A: samo 2
- B: 2 i 4
- C: 1 i 2
- D: samo 1
- E: 1 i 3
- F: sve rečenice

**Tačan odgovor: A**

## 22. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A{
protected:
    int a;
public:
    A(int aa = 0) : a(aa) { ++a; }

    friend bool operator==(const A& x, const A& y){
        if (x.a > y.a)      return 1;
        else if (x.a < y.a) return 0;
        else                return 1 + 1;
    }

    friend bool operator!=(const A& x, const A& y){
        return !(x == y);
    }
};

int main(){
    A a1(2), a2(2), a3(3), a4(4);
    cout << (a1 == a2)
         << (a2 == a3)
         << (!(a1 == a2))
         << (a3 != a4)
         << "\n";
    return 0;
}
```

- A: 1001
- B: 1011
- C: 1101
- D: 0111

**Tačan odgovor: A**

## 23. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

struct A {
    string name;
    A(string n) : name(n) { cout << "Konstruktor: " << name << "\n"; }
    ~A() { cout << "Destruktor: " << name << "\n"; }
};

struct B {
    A a1;
    A a2;
    A a3;

    B() : a2("drugi"), a1("prvi"), a3("treci") {
        cout << "Konstruktor B\n";
    }
    ~B() {
        cout << "Destruktor B\n";
    }
};

int main() {
    B b;
    return 0;
}
```

**Tačan odgovor:**

```
Konstruktor: prvi
Konstruktor: drugi
Konstruktor: treci
Konstruktor B
Destruktor B
Destruktor: treci
Destruktor: drugi
Destruktor: prvi
```

## 24. (C++) Koji od sledećih napisanih preklapanja operatora su ispravni?

```cpp
1. friend Complex& operator+(Complex& c1, Complex& c2);
2. friend Complex operator+(const Complex& c1, const Complex& c2);
3. Complex operator+(Complex c1, Complex c2) const;
4. Complex& operator+(const Complex& c1);
```

**Tačan odgovor: samo 2**

## 25. (C++) Koji od sledećih napisanih preklapanja operatora su ispravni?

```cpp
1. Complex& operator=(const Complex& other);
2. Complex operator=(const Complex& other);
3. const Complex& operator=(Complex other);
4. Complex operator=(Complex& other) const;
```

**Tačan odgovor: samo 1**

## 26. (C++) Koji od sledećih napisanih preklapanja operatora su ispravni?

```cpp
1. Complex& operator++();
2. Complex operator++();
3. Complex& operator++(int);
4. const Complex operator++(int);
```

**Tačan odgovor: samo 4**

## 27. (C++) Koji od sledećih napisanih preklapanja operatora su ispravni?

```cpp
1. friend ostream operator<<(ostream& out, Complex& c);
2. friend ostream& operator<<(ostream& out, Complex c);
3. friend ostream& operator<<(ostream& out, const Complex& c);
4. ostream& operator<<(Complex& c, ostream& out);
```

**Tačan odgovor: samo 3**

## 28. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>

using namespace std;

void f(int &r) {
    r=5;
}

void f(int *p) {
    *p=9;
}

int main() {
   int a=3;
   cout<<a;
   f(a);
   cout<<a;
   f(&a);
   cout<<a;
   return 0;
}
```

**Tačan odgovor: 359**

## 29. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

void f(int &x, int &y)      { x += 2; y += 3; }
void f(int *x, int *y)      { *x += 5; *y += 7; }
void f(const int &x, int &y){ y += x; }

int main() {
    int a = 1, b = 2;
    cout << a << b;
    f(a, b);
    cout << a << b;
    f(&a, &b);
    cout << a << b;
    f(a, b);
    cout << a << b;
    f(b, a);
    cout << a << b;
    return 0;
}
```

**Tačan odgovor: 123581210151317**

## 30. (C++) Šta će biti ispisano izvršavanjem sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class X {
    char c;
public:
    X(char cc = 'A'){ c = cc; cout << c; }
    ~X(){ cout << 'B'; }
};

class Y : public X {
    X m;
public:
    Y() : X('C'), m('D'){ cout << 'E'; }
    ~Y(){ cout << 'F'; }
};

class Z {
    Y y;
    X x;
public:
    Z() : x('G'){ cout << 'H'; }
    ~Z(){ cout << 'I'; }
};

int main(){
    Z z;
    return 0;
}
```

**Tačan odgovor: CDEGHIBFBB**
