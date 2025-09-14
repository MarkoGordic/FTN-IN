## 1. (C++) Šta će biti ispis sledećeg programa?

```cpp
#include <iostream>
using namespace std;

void c(int x) {
    x = 2;
}

void c(int &x) {
    x = 3;
}

void c(int *x) {
    *x = 5;
}

int main() {
    int p = 4;

    c(p);
    cout << p;
    c(p);
    cout << p;

    return 0;
}
```

**Tačan odgovor: Kod se neće kompajlirati.**

## 2. (C++) Šta će biti ispis sledećeg programa?

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 1;
    int b = 2;

    int *pa = &b;
    int *pb = &a;

    a = b++;

    cout << *pa;
    cout << (*pb);

    return 0;
}
```

**Tačan odgovor: 32**

## 3. (C++) Kako se pravilno preklapa operator dodele preko metode?

```cpp
1. A& operator+=(const A& other)
2. A operator+=(const A& other)
3. friend A operator+=(const A& other)
4. friend A& operator+=(const A& other)
```

**Tačan odgovor: 1**

4. (C++) Šta će biti ispis sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A {
    public:
        virtual void m() { cout << "a"; }
};

class B : public A{
    public:
        void m() { cout << "b"; }
};

int main() {
    A* p;

    A a;
    B b;


    b.m();
    p = &b;
    p->m();

    return 0;
}
```

**Tačan odgovor: bb**

## 5. (C++) Šta treba da se stavi umesto XXXX?

```cpp
template <typename XXXX>
struct MyTemplate {
    T a;
    T b[TT];
    T c[TT];
};
```

1. class T, int TT
2. int T, int TT
3. int T, class TT
4. class T, int TT, int TT

**Tačan odgovor: class T, int TT**

## 6. (Java) Šta će biti ispis sledećeg programa?

```java
class A {
    protected int a;

    A(int aa) { a = aa; }

    public int getA() {
        return this.a;
    }

    public void m() { a++; }
}

class B extends A {
    protected int b = 2;

    B(int n) { super(n); }
    public void m() { b += 2; }
}

public class Main {
    public static void main(String[] args) {
        A a = new A(3);
        B b = new B(3);

        b.m();
        b.m();
        a.m();
        a.m();
        System.out.print(a.getA());
        System.out.print(b.getA());
    }
}
```

**Tačan odgovor: 53**

## 7. (C++) Šta će biti ispis sledećeg programa?

```cpp
#include <iostream>
using namespace std;

class A {
public:
    A()  { cout << "1"; }
    ~A() { cout << "2"; }
};

class B {
    A a;
public:
    B()  { cout << "3"; }
    ~B() { cout << "4"; }
};

class C : public B {
public:
    C()  { cout << "5"; }
    ~C() { cout << "6"; }
};

int main() {
    C c;
    return 0;
}
```

**Tačan odgovor: 135642**

## 8. (Java) Šta će biti ispis sledećeg programa?

```java
import java.util.*;

class A {
    int x;

    A(int x) {
        this.x = x;
    }

    @Override
    public String toString() {
        return String.valueOf(x);
    }
}

public class Main {
    public static void main(String[] args) {
        A a1 = new A(4);
        A a2 = new A(3);
        A a3 = new A(2);
        A a4 = new A(1);

        a1 = a4;
        a2 = a3;

        List<A> lista = Arrays.asList(a1, a2, a3, a4);

        for (int i = 0; i < 4; i++) {
            int x = lista.get(i).x;
            System.out.print(x);
        }
    }
}
```

**Tačan odgovor: 1221**

## 9. (Java) Šta će biti ispis sledećeg programa?

```java
class A {
    public int x, y;

    A(int x, int y) { this.x = x; this.y = y; }
}

public class Main {
    public static void main(String[] args) {
        A a1 = new A(3,5);
        A a2 = a1;
        a2.x += 100;

        System.out.println("" + a1.x + a2.y + a1.x + a2.y);
    }
}
```

**Tačan odgovor: 10351035**

## 10. Koji od sledećih iskaza je tačan?

1. Referenci se predručuje vrednost koja je već u memoriji
2. Postoji pokazivač na referencu
3. Klasu zovemo apstraktna ako su joj sve metode čiste virtualne (pure virtual)
4. Prijateljska funkcija može da pristupi privatnim članovima klase
