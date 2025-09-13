# 📘 Skripta – NPPJ

### Predmet: Napredno programiranje i programski jezici (NPPJ)

### Program: Informacioni inženjering 2024/2025

---

# ✍️ Copyright – Marko Gordić, IN 37/2023

> [!CAUTION]  
> Ova skripta je napravljena na osnovu predavanja, vežbi i primera. Može sadržati greške i propuste. Koristiti isključivo kao pomoćno sredstvo uz zvanične materijale.

---

# 📑 Sadržaj

1. 🏗️ **Konstruktor i destruktor**
2. 🧩 **Static polja i metode**
3. 🪢 **Redosled konstruisanja i uništavanja**
4. 🧬 **Nasleđivanje i višestruko nasleđivanje**
5. 🌀 **Apstraktne klase i virtuelne metode**
6. 🔧 **Generičke klase i template mehanizam**
7. 🔗 **Friend funkcije i pristup poljima**
8. 🔄 **Reference i pokazivači**
9. 📍 **Pokazivač `this`**
10. ☕ **Java deo – osnovne razlike u odnosu na C++**
11. 🗂️ **Primeri koda sa objašnjenjem**

---

# 1. Konstruktor i destruktor

- Konstruktor se **zove isto kao i klasa**.
- Parametri sa podrazumevanim vrednostima uvek idu na kraj.
- Ako svi parametri u konstruktoru imaju podrazumevane vrednosti → **ne sme se praviti prazan konstruktor** (konflikt!).
- Konstruktor inicijalizator (`:`) se koristi samo za inicijalizaciju polja i roditeljskih klasa.

```cpp
class Osoba {
private:
    string ime;
    string prezime;
public:
    Osoba(string i = "N", string p = "N") : ime(i), prezime(p) {}
};
```

- **Destruktor** se poziva obrnutim redosledom od konstruktora.

---

# 2. Static polja i metode

- Static polja su **zajednička svim instancama klase**.
- Poziv:
  - `Artikal::instanci`
  - `obj.instanci` (ako je public)

Ako je `private` → mora ići kroz **get metodu**.

```cpp
class Artikal {
private:
    static int brojac;
public:
    static int getBrojac() { return brojac; }
};

int Artikal::brojac = 0;
```

---

# 3. Redosled konstruisanja i uništavanja

> [!IMPORTANT]  
> Redosled konstruktora:
>
> 1. Bazna klasa
> 2. Polja klase, **redosledom deklaracije u klasi**
> 3. Telo konstruktora

Destruktori idu obrnutim redom.

---

# 4. Nasleđivanje

- Nasleđuju se polja i metode, ali **ne i konstruktori, destruktori i friend funkcije**.
- Ako su polja `private` u roditelju, u kopirnom konstruktoru koristimo get metode.

```cpp
Student(const Student& s) : Osoba(s.getIme(), s.getPrezime()), brojIndeksa(s.brojIndeksa) {}
```

- C++ → podržava direktno višestruko nasleđivanje.
- Java → **ne podržava**, koristi interfejse.

---

# 5. Apstraktne klase i virtuelne metode

- Apstraktna metoda = virtuelna metoda bez tela:

```cpp
virtual double getP() const = 0;
```

- Virtuelnost se nasleđuje, apstraktnost samo ako metoda ostane nedefinisana.

---

# 6. Generičke klase (Template)

```cpp
template <class T, int D>
class Niz {
    T podaci[D];
};
```

- `T` → tip koji se prosleđuje.
- `D` → konstanta, ne može da se menja.

---

# 7. Friend funkcije

- Friend funkcije imaju direktan pristup privatnim poljima.
- Obične funkcije moraju koristiti get metode.

---

# 8. Reference

- Moraju se odmah inicijalizovati.
- Ne mogu se prevezati.
- Više referenci može pokazivati na istu promenljivu.

---

# 9. Pokazivač `this`

- `this` → pokazuje na objekat koji je pozvao metodu.
- `*this` → sam objekat.

---

# 10. Java – osnovne razlike

- Nema pokazivača, sve su reference.
- Svi objekti se nalaze na **heap-u**.
- Sve metode su implicitno virtuelne.
- Nema destruktora → koristi se **Garbage Collector**.
- Klasa `Object` je koren hijerarhije.
- `final` → konstante, zabrana override-a ili nasleđivanja.
- Višestruko nasleđivanje se rešava preko **interfejsa**.

```java
public abstract class Osoba {
    public abstract void printOsoba();
}

public class Student extends Osoba {
    @Override
    public void printOsoba() {
        System.out.println("Student");
    }
}
```

---

# 11. Primeri koda sa rešenjima

## Redosled konstruktora

```cpp
class A { public: A() { cout << "A"; } };

class B { public: B() { cout << "B"; } };

class D {
    A a; B b;
    public: D() { cout << "D"; }
};

int main() {
    D d;
}
```

📌 Izlaz:

```
ABD
```

---

## Virtuelne funkcije i destruktori

```cpp
struct Base {
    Base() { cout << "Base ctor\n"; }
    virtual ~Base() { cout << "Base dtor\n"; }
    virtual void foo() { cout << "Base foo\n"; }
};

struct Derived : Base {
    Derived() { cout << "Derived ctor\n"; }
    ~Derived() { cout << "Derived dtor\n"; }
    void foo() override { cout << "Derived foo\n"; }
};

int main() {
    Base* obj = new Derived();
    obj->foo();
    delete obj;
}
```

📌 Izlaz:

```
Base ctor
Derived ctor
Derived foo
Derived dtor
Base dtor
```

---
