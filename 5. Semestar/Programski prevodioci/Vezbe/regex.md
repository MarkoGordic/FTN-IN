# Flex Regex Reference

## 1. Osnovni obrasci

- **`x`** – bukvalno slovo _x_  
  ➜ hvata: `x` u tekstu `"exam"` (drugo slovo)

- **`.`** – bilo koji karakter osim novog reda  
  ➜ hvata: `a`, `5`, `?`, `%` itd.

- **`[xyz]`** – bilo koji od navedenih karaktera  
  ➜ hvata: `x` ili `y` ili `z` u `"pyzor"`

- **`[a-fZ]`** – opseg (a–f) ili `Z`  
  ➜ hvata: `b` u `"blue"`, `Z` u `"Zebra"`

- **`[^A-Z]`** – bilo koji karakter koji NIJE veliko slovo  
  ➜ hvata: `_`, `a`, `9`, ali ne i `F`

- **`[^A-Z\n]`** – bilo šta osim velikog slova ili novog reda  
  ➜ hvata: `@` ali ne hvata `A` niti `\n`

- **`[a-z]{-}[aeiou]`** – mala slova MINUS samoglasnici  
  ➜ hvata: `b`, `c`, `d`, `f`… (suglasnici)

---

## 2. Kvantifikatori (ponavljanja)

- **`r*`** – nula ili više  
  ➜ `a*` hvata: `""`, `"a"`, `"aaa"`

- **`r+`** – jedno ili više  
  ➜ `a+` hvata: `"a"`, `"aaaa"` (ne hvata prazno)

- **`r?`** – nula ili jedno  
  ➜ `a?` hvata: `""` ili `"a"`

- **`r{3}`** – tačno 3 ponavljanja  
  ➜ `a{3}` hvata: `"aaa"`

- **`r{2,5}`** – između 2 i 5  
  ➜ `a{2,5}` hvata: `"aa"`, `"aaa"`, `"aaaa"`, `"aaaaa"`

- **`r{2,}`** – 2 ili više  
  ➜ `a{2,}` hvata: `"aa"`, `"aaaaaa"` …

---

## 3. Escape sekvence

- **`\n \t \r`** – novi red, tab  
  ➜ `\n` hvata karakter novog reda

- **`\x41`** – heks 41 = `'A'`  
  ➜ hvata: `"A"`

- **`\123`** – oktalna vrednost  
  ➜ zavisi od broja, npr. `\141` = `'a'`

- **`"foo"`** – doslovno `"foo"`  
  ➜ hvata: `"foo"` u `"foobar"`

---

## 4. Grupisanje i opcije

- **`(abc)`** – grupisanje  
  ➜ hvata `"abc"` kao jedan blok

- **`(?:abc)`** – isto, ali bez hvatanja grupe  
  ➜ hvata `"abc"`

- **`(?i:abc)`** – case-insensitive unutar grupe  
  ➜ hvata: `"ABC"`, `"aBc"`, `"abc"`

- **`(?s:.)`** – `.` hvata baš svaki bajt uključujući `\n`  
  ➜ hvata: novi red, binarne bajtove

---

## 5. Konkatenacija i alternacija

- **`rs`** – r pa s  
  ➜ `ab` hvata `"ab"`

- **`r|s`** – ili  
  ➜ `cat|dog` hvata `"cat"` ili `"dog"`

---

## 6. Trailing kontekst

- **`r/s`** – r samo ako ga prati s (ali se s _ne pojede_)  
  ➜ `foo/bar` na `"foobar"` hvata `foo`, ali proverava da sledi `bar`

- **`r$`** – r na kraju reda  
  ➜ `abc$` hvata `"abc"` samo ako je pre `\n`

- **`^r`** – r na početku reda  
  ➜ `^abc` hvata `"abc"` samo ako je prvi tekst linije

---

## 7. Start uslovi

- **`<S>abc`** – hvata `"abc"` samo u stanju `S`
- **`<A,B>xyz`** – važi u više stanja
- **`<<EOF>>`** – kraj fajla  
  ➜ hvata samo kada više nema ulaza

---

## 8. Proširene karakter klase

- **POSIX klase**

  - `[[:digit:]]` hvata `0–9`
  - `[[:alpha:]]` hvata sva slova
  - `[[:alnum:]]` hvata slova ili cifre
  - `[[:space:]]` hvata whitespace

- **Negirane POSIX klase**  
  ➜ `[[:^digit:]]` hvata sve što NIJE cifra

- **Unija (`{+}`)**  
  ➜ `[a-f]{+}[0-9]` hvata `a–f` i `0–9`

- **Razlika (`{-}`)**  
  ➜ `[a-z]{-}[aeiou]` → hvata suglasnike
