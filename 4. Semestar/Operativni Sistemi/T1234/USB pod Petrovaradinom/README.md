# USB pod Petrovaradinom

<center>
<img src="./image.png" alt="USB" width="500"/>
</center>

## Zadatak

Te večeri Novi Sad diše tiše nego obično: kej, svetla preko Dunava, isti krug koraka što vraća misli na mesto. Damjan se našao kod Varadinskog mosta kad mu je pod nogom zatreperilo nešto sitno. Sagne se – USB, izgreban, sa ugraviranim slovom **G**. Kada ga je otvorio pronašao je i mali, uredno presavijen papirić. Kod kuće je priključio USB: samo jedan fajl, `mila.me`, a u njemu duga lista pesama kao da je neko ostavio mapu od tonova i naslova. Ništa mu nije bilo jasno, dok nije razmotao papirić: uputstvo za dešifrovanje, strelice i brojevi – taman koliko da izazove radoznalost. 🔍✨

### Ulaz

U ulaznoj datoteci `mila.me` su podaci podeljeni delimiterom `#` i prate sledeći format:

1. ime pesme – string - maksimalno 100 karaktera
2. ime autora – string - maksimalno 100 karaktera
3. dužina pesme u sekundama – int
4. ključ – int
5. ID ključa – int
6. ime albuma – string - maksimalno 100 karaktera
7. ID – int

**Primer reda:**  
`Budi tu#EKV#255#17#42#Par godina za nas#12`

### Pravila obrade

1. Poruku nose pesme čiji je **ID deljiv sa 3**.
2. Kako bismo dobili karakter koji nam je potreban za poruku, potrebno je uzeti **ime pesme**. Izdvojiti **jedan karakter** koji se nalazi na indeksu vrednosti **kljuca** - `ime_pesme[kljuc]`. Ako je vrednost `kljuca` broj koji je veci od dužine imena, potrebno je koristiti formulu `kljuc % strlen(ime_pesme)`.
3. Potrebno je napraviti još jednu strukturu i klasu u kojoj ćemo čuvati parove `(ID ključa, karakter)` tokom obrade podataka
4. **Kako se dobija poruka:** kada sakupiš sve parove, **poređaj ih po rastućem ID-ju ključa** i **spoji karaktere redom** (bez razmaka i delimetera). Dobijeni niz je tajna poruka.
5. Sve pesme sa **parnim ID** upiši u `plejlista_parni.txt` **bez delimetera**.
6. U `poruka.txt` upiši **samo** dobijenu poruku.

### Paralelizacija

- **1 nit – čitač ulaza.** Čita `mila.me`, parsira redove (delimiter `#`)
- **4 niti – radnici.** Svaka obrađuje zapise:
  - za `ID % 3 == 0` izdvoji karakter i pošalji **(ID ključa, karakter)** u red za poruku
  - za **parne** `ID` pošalji ceo red (u `#` formatu) u red za plejlistu
- **1 nit – štampač plejliste.** Preuzima iz reda za plejlistu i piše u `plejlista_parni.txt`; završava kada više nema stavki za obradu.
- **1 nit – štampač poruke.** Počinje završnu fazu **tek kada čitač i svi radnici završe sa slanjem stavki** (na primer, nakon što dobije informaciju da su redovi ispražnjeni ili da su sve stavke obrađene). Tada sortira sakupljene **(ID ključa, karakter)** po **ID-ju ključa** i upisuje spojene znakove u `poruka.txt`.
