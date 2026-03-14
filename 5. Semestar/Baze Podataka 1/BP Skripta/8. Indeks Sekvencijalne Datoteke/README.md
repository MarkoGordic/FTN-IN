# Statička indeks-sekvencijalna organizacija datoteke

## Uvod - zašto nam treba indeksna datoteka?

Pre nego što krenemo u detalje, hajde da se podsetimo problema koji rešavamo. Do sada smo upoznali dve osnovne organizacije datoteka:

- **Sekvencijalne datoteke** su odlične za redoslednu obradu - čitamo slog po slog, lepo i efikasno. Traženje logički narednog sloga ide brzo. Ali šta ako nam treba jedan konkretan slog negde u sredini? Moramo da pretražimo polovinu datoteke u proseku.
- **Rasute datoteke** su odlične za direktni pristup - damo vrednost ključa, dobijemo adresu, preuzmemo slog. Ali redosledna obrada? Katastrofa.

Indeksne datoteke su **kompromis** između ova dva sveta. One pokušavaju da obezbede solidnu podršku i za direktnu i za redoslednu obradu, kao i za obe vrste traženja (slučajno odabranog i logički narednog sloga). To postižu tako što koriste **indeks** - pomoćnu strukturu koja sadrži parove (vrednost ključa, adresa sloga) i služi za preslikavanje argumenta traženja u adresu sloga u posebnoj datoteci (zoni podataka), koja je često organizovana kao sekvencijalna.

Postoji veći broj različitih vrsta indeksnih datoteka. Indeksne datoteke se, u osnovi, dele na **statičke** i **dinamičke**. Statičke datoteke su istorijski nastale pre dinamičkih i danas imaju samo didaktički značaj. Zovu se statičkim iz dva razloga: veličina dodeljenog memorijskog prostora im se određuje prilikom projektovanja i kasnije se ne menja, a indeks se nakon formiranja praktično više ne ažurira. Kod dinamičkih indeksnih datoteka se, tokom životnog veka, i menja dodeljeni memorijski prostor i ažurira indeks.

U ovom poglavlju obrađujemo **statičke indeks-sekvencijalne datoteke**.

---

## Tri zone indeks-sekvencijalne datoteke

Zamislimo indeks-sekvencijalnu datoteku kao jednu biblioteku koja ima tri prostorije.

Deo memorijskog prostora dodeljen statičkoj indeks-sekvencijalnoj datoteci sastoji se od **tri zone**:

1. **Primarna zona** (zona podataka) - ovde žive svi originalni slogovi, lepo poređani po ključu. Ovo je glavna prostorija biblioteke sa policama gde su knjige poređane po rednom broju.
2. **Zona indeksa** - ovo je katalog biblioteke, stablo traženja koje nam omogućava da brzo pronađemo u kom bloku primarne zone se nalazi traženi slog.
3. **Zona prekoračenja** - ovo je pomoćno skladište. Kada u primarnu zonu treba upisati novi slog, a blok je već pun, višak se "preliva" ovde.

Ove tri zone se mogu posmatrati kao tri datoteke čiji su slogovi međusobno povezani putem adresa, odnosno pokazivača.

> [!IMPORTANT]
> Na ispitu se redovno traži nabrajanje i objašnjenje ove tri zone. Zapamtite: **primarna zona** (sekvencijalna organizacija), **zona indeksa** (spregnuta organizacija - n-arno stablo), **zona prekoračenja** (spregnuta organizacija - lanci prekoračilaca).

---

## Struktura primarne zone

U primarnoj zoni nalaze se slogovi uređeni saglasno rastućim vrednostima ključa. Struktura primarne zone odgovara strukturi sekvencijalne datoteke. Slogovi su u primarnoj zoni blokirani - grupisani u blokove. Poželjno je da faktor blokiranja bude što veći. Pri datoj dužini sloga (izraženoj putem broja slova prirodne azbuke), faktor blokiranja je ograničen kapacitetom staze na jedinici magnetnog diska. Naime, blok najčešće ne može zauzimati više od jedne staze.

Primarna zona se kreira u postupku formiranja statičke indeks-sekvencijalne datoteke i **nikada se naknadno ne ažurira**. To je ključna karakteristika - jednom formirana, primarna zona ostaje netaknuta. Novi slogovi idu u zonu prekoračenja.

Ciljevi ovako organizovane primarne zone su da se iskoriste poželjne osobine sekvencijalne organizacije u redoslednoj obradi podataka i da se izbegne efekat loših performansi ažuriranja sekvencijalno organizovane datoteke (gde bi svaki upis novog sloga zahtevao pomeranje svih slogova sa većim ključem).

---

## Struktura zone indeksa

Zona indeksa je srce cele priče - ona nam omogućava brz pristup do bilo kog bloka u primarnoj zoni.

Struktura zone indeksa odgovara strukturi punog stabla traženja (pristupa) reda $n$ ($n \geq 2$) i visine $h$. Svaki čvor sadrži od $1$ do $n$ elemenata. Elemente čvorova predstavljaju parovi $(k_e, A_e)$, gde je:

- $k_e = k(S)$ - vrednost ključa sloga $S$
- $A_e$ - adresa bloka primarne zone u kojem se nalazi slog $S$, ili adresa nekog drugog čvora stabla traženja koji takođe sadrži $k_e$

Elementi su u čvorovima uređeni saglasno rastućim vrednostima ključa $k_e$, tako da struktura svakog čvora odgovara strukturi male sekvencijalne datoteke.

### Šta se propagira u zone indeksa?

Vrednost ključa $k_e$ predstavljaju ili **najveće**, ili **najmanje** vrednosti ključa iz svakog bloka primarne zone.

- **Elementi čvorova stabla** mogu sadržati ili samo najveće, ili samo najmanje vrednosti ključa iz svakog bloka.
- **Elementi listova stabla** sadrže po jednu vrednost ključa iz svakog bloka, a elementi čvorova na višim nivoima hijerarhije stabla sadrže po jednu vrednost ključa iz svakog direktno podređenog čvora.
- Vrednosti ključa u elementima čvorova koji ne predstavljaju listove stabla ponavljaju se u čvorovima na svim nižim nivoima hijerarhije.

Čvor koji ne predstavlja list, a sadrži $m$ ($1 \leq m \leq n$) elemenata, poseduje $m$ direktno podređenih čvorova.

**Adresa $A_e$** u listu stabla traženja predstavlja adresu bloka u zoni podataka koji sadrži slog sa vrednošću ključa $k(S) = k_e$. Adresa $A_e$ u čvoru na višem nivou hijerarhije stabla predstavlja adresu direktno podređenog čvora u kojem se nalazi element sa vrednošću ključa $k_e$. Adrese $A_e$ se mogu nazivati i pokazivačima.

### Dva primera: propagacija najvećih i najmanjih vrednosti

**Primer 12.1.** Pogledajmo indeks-sekvencijalnu datoteku od $N = 13$ slogova. Faktor blokiranja u primarnoj zoni je $f = 3$, a red stabla traženja u zoni indeksa je $n = 2$.

Ako stablo traženja sadrži **najveće** vrednosti ključa, onda čvorovi stabla sadrže kao najveću vrednost ključa vrednost 99, a ne stvarno najveću vrednost ključa u datoteci. Ovu vrednost ključa u stablo upisuje metoda pristupa pri formiranju datoteke. Pogledajmo kako to izgleda:

| Blok primarne zone | Slogovi (vrednosti ključa) | Najveća vrednost ključa |
|---|---|---|
| $A_1^p$ | 03, 07, 13 | 13 |
| $A_2^p$ | 15, 19, 23 | 23 |
| $A_3^p$ | 25, 27, 29 | 29 |
| $A_4^p$ | 34, 43, 49 | 49 |
| $A_5^p$ | 64 | 99 (najveća dozvoljena, jer je poslednji blok) |

Listovi stabla traženja sadrže parove: $(13, A_1^p)$, $(23, A_2^p)$ u prvom listu; $(29, A_3^p)$, $(49, A_4^p)$ u drugom listu; $(99, A_5^p)$, * u trećem listu (gde * označava kraj).

Na sledećem nivou (čvor iznad listova): $(23, A_1^i)$, $(49, A_2^i)$ u jednom čvoru i $(99, A_3^i)$, * u drugom.

Koren: $(49, A_4^i)$, $(99, A_5^i)$.

Ako stablo traženja sadrži **najmanje** vrednosti ključa, onda čvorovi stabla sadrže kao najmanju vrednost ključa vrednost 00, a ne stvarno najmanju vrednost ključa u datoteci. I ovu vrednost ključa u stablo upisuje metoda pristupa pri formiranju datoteke. Na adresama blokova u zoni indeksa nose oznaku $i$, a adrese blokova u primarnoj zoni oznaku $p$ kao gornji indeks.

---

## Formule za stablo traženja

Sada dolazimo do matematike zone indeksa. Ove formule nam govore koliko je stablo veliko i kako je strukturirano.

### Visina stabla

$$h = \lceil \log_n B \rceil$$

gde je:
- $h$ - visina stabla traženja (broj nivoa)
- $n$ - red stabla (maksimalni broj elemenata u čvoru)
- $B$ ($B \geq 1$) - broj blokova u primarnoj zoni

Kako na prvom nivou hijerarhije stabla postoji samo koren, to je $C_1 = 1$.

### Broj čvorova na i-tom nivou

$$C_i = \left\lceil \frac{B}{n^{h-i+1}} \right\rceil$$

gde je:
- $C_i$ - broj čvorova na $i$-tom nivou hijerarhije stabla ($i = 1, ..., h$)
- Za $i = 1$ dobija se $C_1 = \lceil B / n^h \rceil$

### Ukupni broj čvorova

$$C = \sum_{i=1}^{h} \left\lceil \frac{B}{n^{h-i+1}} \right\rceil$$

### Kapacitet stabla

**Kapacitet stabla** je $K = nC$. To je veličina koja govori koliko parova $(k_e, A_e)$ se može upisati u čvorove stabla.

### Broj elemenata na i-tom nivou

Čvorovi na $i$-tom nivou hijerarhije stabla traženja sadrže ukupno:

$$\left\lfloor \frac{B}{n^{h-i}} \right\rfloor$$

elemenata, tako da ukupni broj elemenata $E$ u stablu pristupa iznosi:

$$E = \sum_{i=1}^{h} \left\lceil \frac{B}{n^{h-i}} \right\rceil$$

### Primer 12.2.

Za $B = 5$ i $n = 2$, dobija se $h = 3$, $C = 6$, $K = 12$ i $E = 10$. Ove veličine predstavljaju performanse stabla traženja na slikama 12.1 i 12.2 iz udžbenika.

Problemi geometrijske reprezentacije fizičke strukture iole veće datoteke doveli su i do opredeljenja za nerealno male vrednosti reda stabla $n$ na slikama. U praksi se red stabla traženja bira u opsegu od 50 do 100.

> [!TIP]
> Na ispitu se često traži izračunavanje $h$, $C$, $K$ i $E$ za date vrednosti $B$ i $n$. Uvek kreni od $h = \lceil \log_n B \rceil$, pa izračunaj $C_i$ za svaki nivo, pa saberi u $C$. Kapacitet je prosto $K = nC$.

---

## Struktura zone prekoračenja

Zona prekoračenja, kao i primarna zona, sadrži slogove datoteke. Slogovi se upisuju u ovu zonu prekoračenja tokom ažuriranja, preciznije, prilikom upisa novih slogova u datoteku. Slogovi u zoni prekoračenja se nazivaju **prekoračioci**. Svaki blok primarne zone može imati svoje prekoračioce.

### Kako nastaju prekoračioci?

Hajde da pogledamo šta se dešava pri upisu novog sloga. Posmatrajmo list stabla traženja sa $m$ elemenata ($1 \leq m \leq n$):

$$(k_1, A_1), ..., (k_{e-1}, A_{e-1}), (k_e, A_e), (k_{e+1}, A_{e+1}), ..., (k_m, A_m)$$

gde $A_e$, $e = 1, ..., m$, predstavljaju adrese sukcesivnih blokova primarne zone.

Ako stablo traženja sadrži najveće vrednosti ključa iz svakog bloka primarne zone, tada slog sa vrednošću ključa $k(S)$ pripada:

- bloku sa adresom $A_1$, ako je $k(S) < k_1$, a
- bloku sa adresom $A_e$, ako je $k_{e-1} < k(S) \leq k_e$, za $e \in \{2, ..., m\}$.
- bloku sa adresom $A_m$, ako je $k(S) > k_m$.

Ako stablo traženja sadrži najmanje vrednosti ključa iz svakog bloka primarne zone, tada slog sa vrednošću ključa $k(S)$ pripada:

- bloku sa adresom $A_1$, ako je $k(S) \leq k_1$, a
- bloku sa adresom $A_e$, ako je $k_e \leq k(S) < k_{e+1}$, za $e \in \{1, ..., m-1\}$, a
- bloku sa adresom $A_m$, ako je $k(S) > k_m$.

### Slučaj nekompletnog bloka ($m \neq n$)

Kada blok nije kompletan, upis novog sloga u datoteku dovodi samo do pomeranja slogova unutar bloka. Slogovi sa vrednošću ključa većom od $k(S)$ pomeraju se za jednu lokaciju ka kraju bloka.

### Slučaj kompletnog bloka ($m = n$)

Kada je blok kompletan, pri ažuriranju, upis svakog novog sloga u datoteku dovodi do upisa jednog od slogova koji pripadaju bloku sa adresom $A_e$, $e \in \{1, ..., m\}$, u zonu prekoračenja. Neka je $k_{e(max)}$ trenutno maksimalna vrednost ključa u bloku sa adresom $A_e$.

- Ako je $k(S) < k_{e(max)}$, novi slog se upisuje u blok, a svi slogovi sa većom vrednošću ključa od $k(S)$ pomeraju se za jednu lokaciju ka kraju bloka. Slog sa vrednošću ključa $k_{e(max)}$ se upisuje u zonu prekoračenja.
- Ako je $k(S) > k_{e(max)}$, novi slog se direktno upisuje u zonu prekoračenja.

U slučaju kada blok nije kompletan, upis novog sloga dovodi samo do pomeranja slogova unutar bloka. Pošto se u ovoj knjizi kao oznaka kraja datoteke koristi *, ta oznaka bi se, pri ovom pomeranju, morala posebno tretirati. Razmatranje tehnike za rad sa nekompletnim blokovima izlaze izvan okvira ovog teksta i neće se poklanjati dalja pažnja.

### Primer 12.3.

Neka je $k(S) = 31$ vrednost ključa novog sloga. List sa adresom $A_2^i$ na slici 12.1 sadrži elemente $(29, A_3^p)$, $(49, A_4^p)$. Pošto je $29 < 31 < 49$, novi slog se upisuje u blok sa adresom $A_3^p$, a slog sa vrednošću ključa 49 prelazi u zonu prekoračenja. Novi slog sa vrednošću ključa $k(S) = 47$ takođe pripada bloku sa adresom $A_4^p$. Međutim, pošto nakon upisa sloga sa $k(S) = 31$, u bloku važi $k_{4(max)} = 43$, slog sa vrednošću ključa $k(S) = 47$ se upisuje u zonu prekoračenja. Upis novog sloga sa vrednošću ključa $k(S) = 71$ u blok sa adresom $A_5^p$ dovodi do pomeranja oznake kraja datoteke (*) u narednu lokaciju.

### Povezivanje prekoračilaca sa stablom traženja

Logički neposredno susedni prekoračioci iz jednog bloka spregnuti su pokazivačima, tako da zona prekoračenja sadrži skup jednostruko spregnutih lanaca. Pokazivači nose informaciju o vezama između slogova u logičkoj strukturi podataka datoteke.

Postoje **dva osnovna postupka** povezivanja prekoračilaca sa listom stabla traženja:

#### 1. Direktno povezivanje

Kod direktnog postupka povezivanja, lanac prekoračilaca je putem pokazivača neposredno povezan sa odgovarajućim elementom lista stabla traženja.

U stablu traženja indeks-sekvencijalne datoteke sa direktnim pristupom prekoračiocima, najčešće su upisane **najveće** vrednosti ključa iz svakog bloka primarne zone. Informaciju o prekoračiocima sadrže elementi listova stabla. Element lista predstavlja **četvorku** $(k_e, A_e, k_z, A_z)$, gde je:

- $k_e$ - najveća vrednost ključa iz bloka sa adresom $A_e$
- $k_z$ - najveća vrednost ključa prekoračioca iz bloka sa adresom $A_e$
- $A_z$ - adresa lokacije onog prekoračioca koji ima najmanju vrednost ključa

Inicijalno, nakon formiranja datoteke, važi $k_e = k_z$ (osim za krajnji desni element krajnjeg desnog lista, gde je $k_e \leq k_z$) i $A_e = A_z$. Jednakost $A_e = A_z$ ukazuje da iz bloka sa adresom $A_e$ nema prekoračilaca.

#### 2. Indirektno povezivanje

Kod indirektnog postupka, element lista stabla traženja je povezan sa lancem prekoračilaca posredno, putem pokazivača u bloku primarne zone.

Svaki blok primarne zone proširen je jednim poljem za smeštaj pokazivača. Pokazivač predstavlja adresu lokacije u koju je smešten prekoračilac sa najmanjom vrednošću ključa iz posmatranog bloka.

Kod jedne varijante indeks-sekvencijalne datoteke sa indirektnim povezivanjem prekoračilaca, lokacija svakog sloga unutar bloka proširena je jednim poljem pokazivača. Svaki novi slog se, pri ažuriranju, upisuje u zonu prekoračenja. Svi novi slogovi, čije se vrednosti ključa nalaze između vrednosti ključa dva fizički susedna sloga u bloku primarne zone, sprežu se tako da čine linearnu logičku strukturu.

U pokazivač sloga u primarnoj zoni upisuje se adresa lokacije u zoni prekoračenja koja sadrži slog sa prvom većom vrednošću ključa. Pokazivač prekoračioca sa najvećom vrednošću ključa u lancu sadrži ili oznaku kraja lanca ili adresu lokacije logički neposredno narednog sloga u primarnoj zoni. Svakom bloku u primarnoj zoni može odgovarati od $0$ do $f$ takvih lanaca u zoni prekoračenja.

> [!WARNING]
> Česta greška na ispitu: studenti mešaju direktno i indirektno povezivanje. Zapamtite - kod **direktnog** povezivanja, informacija o lancu prekoračilaca je u **listu stabla traženja** (četvorka). Kod **indirektnog** povezivanja, pokazivač na lanac prekoračilaca je u **bloku primarne zone**.

### Primer 12.4. (Direktno povezivanje)

Na slici 12.3 prikazani su listovi stabla traženja, primarna zona i zona prekoračenja, nakon upisa novih slogova $(31, p(S_{14}))$, $(14, p(S_{15}))$, $(47, p(S_{16}))$ i $(71, p(S_{17}))$ u indeks-sekvencijalnu datoteku sa slike 12.1. Povezivanje listova stabla sa lancima prekoračilaca je direktno. Faktor blokiranja u zoni prekoračenja je $f = 1$.

### Primer 12.5. (Indirektno povezivanje)

Na slici 12.4 prikazana je primarna zona i zona prekoračenja indeks-sekvencijalne datoteke sa indirektnim povezivanjem prekoračilaca, nakon upisa novih slogova $(31, p(S_{14}))$, $(14, p(S_{15}))$, $(47, p(S_{16}))$ i $(01, p(S_{17}))$. Stablo traženja ove datoteke prikazano je na slici 12.2. Inicijalno, pre ažuriranja, primarna zona ove datoteke je sadržala iste slogove kao i primarna zona datoteke na slici 12.1.

Pošto metoda pristupa upisuje vrednost ključa manju od najmanje moguće u stablo traženja, svi slogovi sa manjom vrednošću ključa od inicijalno najmanje, pripadaju prvom bloku primarne zone.

Pri formiranju indeks-sekvencijalne datoteke sa opisanom varijantom indirektnog povezivanja prekoračilaca, metoda pristupa upisuje kao prvi slog prvog bloka primarne zone **fiktivni slog** sa vrednošću ključa $0$. Na taj način se obezbeđuje mogućnost upisa u zonu prekoračenja i slogova sa vrednošću ključa manjom od inicijalno najmanje u datoteci.

U zonu prekoračenja su, slučajnim redom, jedan do drugog, upisani prekoračioci iz raznih blokova. Verovatnoća da se dva logički susedna sloga nađu u susednim lokacijama zone prekoračenja je mala. S druge strane, što je blok kraći to je kraće i vreme razmene podataka između operativne i eksterne memorije i manji je prostor u operativnoj memoriji potreban za smeštaj takvog bloka. Zato blokovi u zoni prekoračenja često poseduju **faktor blokiranja jedan**.

### Indeks slobodnih lokacija

**Indeks slobodnih lokacija** $E$ u zoni prekoračenja služi za vođenje evidencije o prvoj slobodnoj lokaciji. Indeks slobodnih lokacija služi za dinamičko upravljanje slobodnim prostorom. Slobodne lokacije nisu međusobno spregnute; sadrže samo relativnu adresu, kao sadržaj polja $E$, samo povećava za jedan.

---

## Indeks-sekvencijalna metoda pristupa

Operativni sistemi mainframe računarskih sistema opšte namene podržavali su metodu pristupa sa nizom programa za standardizovano formiranje, korišćenje, ažuriranje, proširivanje i reorganizaciju indeks-sekvencijalnih datoteka. Metoda pristupa je, po pravilu, omogućavala sekvencijalni, direktni i dinamički način pristupa indeks-sekvencijalnoj datoteci. Postojanje standardnih metoda pristupa i njihova povezanost sa višim programskim jezicima u mnogome je olakšavalo rad sa indeks-sekvencijalnim datotekama. Izgradnja stabla traženja i spregnutih slogova u zoni prekoračenja, traženje slučajno odabranog sloga, upis novog i brisanje postojećeg sloga predstavljali su zadatke metode pristupa. Korisnički programi su koristili usluge metode pristupa putem makro naredbi tipa READ, WRITE, REWRITE, DELETE i START.

### Definisanje u Cobolu

U standardnom programskom jeziku Cobol, postoji niz naredbi i rečenica putem kojih se definiše indeks-sekvencijalna organizacija datoteke. U SELECT rečenici sekcije FILE-CONTROL u delu ENVIRONMENT DIVISION postoje sledeće deklarativne rečenice za definisanje indeks-sekvencijalne organizacije datoteke:

```
SELECT ime-datoteke
    ASSIGN TO ime-uredjaja
    [ACCESS MODE IS {SEQUENTIAL | RANDOM | DYNAMIC}]
    ORGANIZATION IS INDEXED
    ACTUAL KEY IS ime_kljuca
```

Promenljiva `ime_kljuca` predstavlja, po pravilu, primarni ključ tipa sloga datoteke i definisana je u frazi opisa strukture sloga datoteke u okviru deklarativne fraze FD (opis datoteke). Vrednost te promenljive se koristi kao argument pri traženju slučajno odabranog sloga.

---

## Formiranje indeks-sekvencijalne datoteke

Program za formiranje indeks-sekvencijalne datoteke ili predstavlja gotov uslužni program čiji se parametri specijalizuju, ili se piše u nekom od viših programskih jezika. Oba programa koriste usluge metode pristupa. Pre početka formiranja indeks-sekvencijalne datoteke, slogovi se moraju urediti saglasno rastućim vrednostima ključa - ulazna datoteka u program za formiranje mora biti sekvencijalna datoteka.

Tok formiranja:

```
SER datoteka → SORT → SEQ datoteka → Program za formiranje IS datoteke → IS datoteka
```

Pri formiranju indeks-sekvencijalne datoteke, program učitava sukcesivne slogove ulazne sekvencijalne datoteke i putem metode pristupa smešta blokove u primarnu zonu indeks-sekvencijalne datoteke. Kako se koji blok upiše u primarnu zonu, metoda pristupa upiše u tekući list zone indeksa par $(k_e, A_e)$, gde je $k_e$ najveća (ili najmanja) vrednost ključa sloga u posmatranom bloku, a $A_e$ adresa bloka.

Kada se svi slogovi prenesu iz ulazne sekvencijalne datoteke u primarnu zonu indeks-sekvencijalne datoteke, metoda pristupa formira čvorove na višim nivoima hijerarhije stabla traženja. Formiranje stabla traženja se vrši postupkom s dna na gore i s leva na desno po nivoima. U svaki čvor na $i$-tom nivou hijerarhije ($i = h-1, h-2, ..., 1$), osim u krajnji desni, metoda pristupa upisuje najveće (ili najmanje) vrednosti ključa iz $n$ sukcesivnih čvorova na nivou hijerarhije $i + 1$, kao i adrese tih čvorova. U krajnji desni čvor metoda pristupa upisuje:

$$\left\lceil \frac{B}{n^{h-i}} \right\rceil - n\left(\left\lceil \frac{B}{n^{h-i+1}} \right\rceil - 1\right)$$

parova $(k_e, A_e)$.

Prilikom formiranja datoteke, u zonu prekoračenja se slogovi ne upisuju.

---

## Traženje u indeks-sekvencijalnoj datoteci

Traženje logički narednog sloga u indeks-sekvencijalnoj datoteci vrši se kombinovanom primenom metode linearnog traženja i metode traženja praćenjem pokazivača. Traženje počinje u prvom bloku primarne zone. Svako naredno traženje se nastavlja od tekućeg sloga datoteke. Linearna metoda se koristi za traženje u bloku primarne zone. Po dolasku do poslednjeg sloga bloka, traženje se nastavlja u lancu prekoračilaca (koji može biti i prazan) metodom praćenja pokazivača. Adresa lokacije prvog sloga lanca prekoračilaca nalazi se ili u listu stabla traženja, ili u polju pokazivača bloka.

### Traženje u stablu

Metoda pristupa koristi stablo pristupa za traženje adrese bloka u kojem se verovatno nalazi slučajno odabrani slog, čija vrednost ključa odgovara zadatom argumentu traženja. Algoritam traženja u stablu se odvija putem sukcesivnog pristupanja čvorovima na jednom putu od korena do lista. U svakom čvoru se vrši traženje u maloj sekvencijalnoj datoteci, ili metodom linearnog ili metodom binarnog traženja.

Ako stablo sadrži najveće vrednosti ključa iz svakog bloka primarne zone, traženje u čvoru može imati jedan od sledeća dva ishoda: $a = k_e$ ili $k_{e-1} < a < k_e$, za $e \in \{2, ..., m\}$, $m \leq n$. U oba slučaja traženje se nastavlja u podstablu sa korenom $C(A_e^i)$, gde $A_e^i$ ukazuje da se čvor $C$ nalazi u bloku (zone indeksa), u kojem se nalazi koren stabla, nalazi u zaglavlju datoteke.

Ako stablo sadrži najmanje vrednosti ključa iz svakog bloka primarne zone, traženje u čvoru može imati jedan od sledeća tri ishoda: $k_{e-1} < a < k_e$, $a = k_e$ ili $a > k_m$. Ako je $k_{e-1} < a < k_e$, traženje se nastavlja u podstablu sa korenom $C(A_{e-1}^i)$, (argument traženja $a$ ne može biti manji od $k_1$, gde je $k_1$ minimalna vrednost ključa u čvoru). Ako je $a = k_e$ ili $a > k_m$, traženje se, redom, nastavlja u podstablu $C(A_e^i)$, odnosno $C(A_m^i)$.

Traženje u stablu se završava u listu, gde metoda pristupa dobija adresu bloka u kojem treba nastaviti traženje.

### Primer 12.9.

Ako je argument traženja $a = 31$, tada algoritam traženja u stablu na slici 12.1 prolazi, redom, čvorove $C(A_6^i)$, $C(A_4^i)$, $C(A_2^i)$ i dobija adresu $A_3^p$ bloka u primarnoj zoni. U slučaju stabla na slici 12.2, algoritam traženja prelazi put $C(A_6^i)$, $C(A_4^i)$, $C(A_2^i)$ i dobija adresu $A_3^p$ bloka u primarnoj zoni. Tek u primarnoj zoni se traženje pokazuje kao neuspešno.

Sprovedena analiza ukazuje da je za traženje adrese bloka potrebno izvršiti:

$$(12.4) \qquad R = h$$

pristupa čvorovima stabla. Ovo traženje metoda pristupa realizuje tako što adresu bloka zone indeksa, u kojem se nalazi koren stabla, nalazi u zaglavlju datoteke. Nakon toga, metoda pristupa sukcesivno prenosi čvorove stabla u operativnu memoriju. Broj pristupa čvorovima stabla, dat formulom (12.4), predstavlja najpovoljniji slučaj. To je slučaj kada za smeštaj blokova zone indeksa postoji samo jedan bafer u operativnoj memoriji. Ako metodi pristupa stoje na raspolaganju dva bafera, tada se u jednom od njih stalno nalazi koren stabla, te je $R = h - 1$.

### Traženje logički narednog sloga - direktno povezivanje prekoračilaca

Kod traženja logički narednog sloga pristupa se blokovima primarne zone, prekoračiocima i listovima stabla traženja. Broj pristupa $R$ i pri uspešnom i pri neuspešnom traženju jednog logički narednog sloga uzima celobrojne vrednosti iz intervala:

$$(12.2) \qquad 0 \leq R \leq B + \left\lceil \frac{B}{n} \right\rceil + Z - (i + j + k)$$

gde je:
- $Z$ - ukupni broj slogova u zoni prekoračenja
- $i$ - redni broj tekućeg bloka datoteke u odnosu na početak primarne zone
- $j = \lceil i/n \rceil$ - redni broj tekućeg lista stabla traženja
- $k$ - broj slogova zone prekoračenja kojima se već pristupilo

### Traženje logički narednog sloga - indirektno povezivanje prekoračilaca

Broj pristupa $R$ i pri uspešnom i pri neuspešnom traženju jednog logički narednog sloga uzima celobrojne vrednosti iz intervala:

$$(12.3) \qquad 0 \leq R \leq B + Z - (i + k)$$

### Primer 12.7.

Za datoteku sa slike 12.3, $B = 5$, $\lceil B/n \rceil = 3$ i $Z = 4$. Neka je slog sa vrednošću ključa $k(S_5) = 15$, tekući slog datoteke. Tada je $i = 2$, $j = 1$ i $k = 0$. Da bi se pronašao slog sa vrednošću ključa $k(S_3) = 19$, treba izvršiti $R = 0$ pristupa datoteci, a da bi se pronašao slog sa vrednošću ključa $k(S_{17}) = 71$, treba izvršiti $R = 9$ pristupa datoteci.

### Primer 12.8.

Za datoteku sa slike 12.4, $B = 5$ i $Z = 4$. Neka je slog sa vrednošću ključa $k(S_{15}) = 14$, tekući slog datoteke. Tada je $i = 1$ i $k = 2$. Da bi se pronašao slog sa vrednošću ključa $k(S_5) = 19$, treba $R = 1$ pristup datoteci, a da bi se pronašao slog sa vrednošću ključa $k(S_{13}) = 64$, treba izvršiti $R = 6$ pristupa datoteci.

Upoređujući izraze (12.2) i (12.3) dolazi se do zaključka da je traženje logički narednog sloga efikasnije u indeks-sekvencijalnoj datoteci sa indirektnim nego u indeks-sekvencijalnoj datoteci sa direktnim povezivanjem prekoračilaca.

### Traženje slučajno odabranog sloga

Traženje slučajno odabranog sloga u datoteci, metoda pristupa realizuje ili u dva ili u do tri koraka. U dva koraka, ako je povezivanje prekoračilaca direktno. Potrebna su do tri koraka, ako je povezivanje prekoračilaca indirektno. U oba slučaja, prvi korak predstavlja traženje u stablu pristupa (da bi se izbegla fraza "traženje u stablu traženja", u daljem tekstu će se koristiti i termin stablu pristupa).

#### Direktno povezivanje prekoračilaca

Traženje se nastavlja u bloku primarne zone. To traženje metoda pristupa realizuje tako što adresu bloka zone indeksa, u kojem se nalazi koren stabla, nalazi u zaglavlju datoteke. Adresu krajnjeg levog lista stabla traženja metoda pristupa nalazi u zaglavlju datoteke. Logički naredni listovi ili zauzimaju sukcesivne blokove zone indeksa ili su spregnuti pokazivačima.

Broj pristupa $R$ i pri uspešnom i pri neuspešnom traženju jednog slučajno odabranog sloga uzima celobrojne vrednosti iz intervala:

$$h + 1 \leq R \leq h + z$$

gde je $z$ dužina lanca prekoračilaca za jedan blok primarne zone.

#### Indirektno povezivanje prekoračilaca

Kod indirektnog povezivanja, nakon prolaska kroz stablo traženja, prvo se pristupa bloku primarne zone, pa onda lancu prekoračilaca.

Broj pristupa $R$ i pri uspešnom i pri neuspešnom traženju jednog slučajno odabranog sloga uzima celobrojne vrednosti iz intervala:

$$h + 1 \leq R \leq h + 1 + z$$

Upoređujući ova dva izraza, dolazi se do zaključka da je traženje slučajno odabranog sloga efikasnije u indeks-sekvencijalnoj datoteci sa direktnim povezivanjem prekoračilaca.

---

## Formule za očekivani broj pristupa pri traženju slučajno odabranog sloga

Ovo je deo gde se pojavljuju ozbiljne formule. Hajde da ih razradimo jednu po jednu.

### Direktno povezivanje prekoračilaca

Neka je $z$ broj prekoračilaca jednog bloka, a $f$ faktor blokiranja u primarnoj zoni.

**Verovatnoća da se traženi slog nalazi u primarnoj zoni:**

$$(12.5) \qquad p_f = \frac{f}{f + z}$$

**Verovatnoća da se traženi slog nalazi u zoni prekoračenja:**

$$(12.6) \qquad p_z = \frac{z}{f + z}$$

gde je $p_i = 1/z$ verovatnoća da se traži $i$-ti prekoračilac. Ako je i verovatnoća zaustavljanja neuspešnog traženja na svakom slogu bloka primarne zone i na svakom prekoračiocu ista, za očekivani broj pristupa pri neuspešnom traženju se dobija:

**Očekivani broj pristupa pri uspešnom traženju:**

$$(12.7) \qquad \overline{R_u} = h + p_f \sum_{i=1}^{z} i \cdot p_i$$

Nakon sređivanja formule (12.7), dobija se:

$$(12.8) \qquad \overline{R_u} = h + \frac{2f + z(z+1)}{2(f+z)}$$

**Očekivani broj pristupa pri neuspešnom traženju:**

$$(12.9) \qquad \overline{R_n} = h + \frac{2f + z(z+1)}{2(f+z)}$$

jer je reč o neuspešnom traženju u datoteci gde je uvek $a < k_{z}$.

### Primer 12.10.

U datoteci na slici 12.3, blok primarne zone sa adresom $A_4^p$ ima dva prekoračioca. Pošto je $h = 3$, za pronalaženje sloga sa vrednošću ključa $k(S_{12}) = 49$, potrebno je $R = 5$ pristupa.

Neka je $29 < a \leq 49$, gde je $a$ argument traženja. Za očekivani broj pristupa datoteci pri uspešnom traženju (formula 12.8) se dobija $\overline{R_u} = 4{,}2$. Lako se proverava da je i u slučaju neuspešnog traženja $\overline{R_n} = 4{,}2$.

### Indirektno povezivanje prekoračilaca

Kada je povezivanje prekoračilaca sa listovima stabla traženja realizovano posredno, metoda pristupa prvo traži slučajno odabrani slog u bloku primarne zone. Adresu bloka metoda pristupa nalazi u stablu traženja. Ako se traženi slog u bloku ne nalazi, a blok ima neprazan lanac prekoračilaca, traženje se nastavlja u zoni prekoračenja.

Očekivani broj pristupa $\overline{R_u}$ pri uspešnom traženju dat je formulom:

$$(12.10) \qquad \overline{R_u} = h + p_f + p_z\left(1 + \sum_{i=1}^{z} i \cdot p_i\right)$$

gde su verovatnoće $p_f$ i $p_z$ date, redom, formulama (12.5) i (12.6). Nakon sređivanja formule (12.10), dobija se:

$$(12.11) \qquad \overline{R_u} = h + 1 + \frac{z(z+1)}{2(f+z)}$$

Pošto argument traženja ne može imati manju vrednost od najmanje vrednosti ključa u bloku, neuspešno traženje se ne može zaustaviti na prvom slogu bloka primarne zone. Verovatnoća da se neuspešno traženje zaustavi u bloku primarne zone iznosi:

$$(12.12) \qquad p_f = \frac{f - 1}{f + z}$$

Verovatnoća da se neuspešno traženje zaustavi na nekom od slogova u zoni prekoračenja iznosi:

$$(12.13) \qquad p_z = \frac{z + 1}{f + z}$$

Očekivani broj pristupa pri neuspešnom traženju jednog slučajno odabranog sloga u indeks-sekvencijalnoj datoteci sa indirektnim povezivanjem prekoračilaca iznosi:

$$(12.14) \qquad \overline{R_n} = h + p_f + p_z\left(1 + \sum_{i=1}^{z} i \cdot p_i\right)$$

gde je:

$$(12.15) \qquad p_i = \begin{cases} \frac{1}{z+1} & \text{za } 1 \leq i \leq z - 1 \\ \frac{2}{z+1} & \text{za } i = z \end{cases}$$

Nakon zamene (12.12), (12.13) i (12.15) u (12.14), dobija se:

$$(12.16) \qquad \overline{R_n} = h + 1 + \frac{z(z+3)}{2(f+z)}$$

### Primer 12.11.

U datoteci na slici 12.4, blok primarne zone sa adresom $A_3^p$ ima dva prekoračioca. Pošto je $h = 3$, za pronalaženje sloga sa vrednošću ključa $k(S_{15}) = 14$, potrebno je $R = 6$ pristupa.

Ako je $0 \leq a < 15$, gde je $a$ argument traženja, za očekivani broj pristupa datoteci pri uspešnom traženju (formula (12.11)) se dobija $\overline{R_u} = 4{,}6$. Pri neuspešnom traženju (formula (12.16)) se dobija $\overline{R_n} = 5$.

Upoređujući formule (12.8) i (12.9), redom, sa formulama (12.11) i (12.16) dolazi se do zaključka da je traženje slučajno odabranog sloga u indeks-sekvencijalnoj datoteci sa **direktnim** povezivanjem prekoračilaca efikasnije nego u datoteci sa **indirektnim** povezivanjem. Razlog leži u činjenici da se, u datoteci sa direktnim povezivanjem, odluka o nastavku traženja ili u bloku primarne zone ili u lancu prekoračilaca, donosi već u listu stabla traženja. U datoteci sa indirektnim povezivanjem, nakon prolaska kroz stablo traženja, prvo se pristupa bloku primarne zone, pa onda lancu prekoračilaca.

> [!TIP]
> Na ispitu se često traže ove formule i poređenje. Zapamtite ključnu razliku: direktno povezivanje je efikasnije za traženje slučajno odabranog sloga (jer odmah iz lista stabla znamo da li da idemo u primarnu zonu ili u prekoračioce), dok je indirektno povezivanje efikasnije za traženje logički narednog sloga (jer ne moramo pristupati listovima stabla).

---

## Obrada indeks-sekvencijalne datoteke

Datoteke sa indeks-sekvencijalnom organizacijom poseduju jedinstvenu karakteristiku da se efikasno mogu obrađivati i u režimu redosledne i u režimu direktne obrade. Pogodne su za korišćenje u ulozi vodeće datoteke kako u redoslednoj tako i u direktnoj obradi.

### Redosledna obrada

Redosledna obrada indeks-sekvencijalne datoteke putem vodeće datoteke od $N_v$ slogova odvija se naizmeničnim pristupanjem blokovima primarne zone i njihovim lancima prekoračilaca. Adresu prvog bloka primarne zone metoda pristupa pronalazi u zaglavlju datoteke.

Ukupni broj pristupa pri redoslednoj obradi $R_{uk}$ zavisi od postupka povezivanja prekoračilaca sa stablom traženja. Ako vodeća datoteka sadrži najveću vrednost ključa obrađivane indeks-sekvencijalne datoteke, tada je, za slučaj **direktnog** povezivanja:

$$(12.17) \qquad R_{uk} = B + Z + \lceil B/n \rceil$$

a u slučaju **indirektnog** povezivanja:

$$(12.18) \qquad R_{uk} = B + Z$$

gde je $Z$ ukupni broj prekoračilaca datoteke.

Očekivani broj pristupa $\overline{R}$ pri uspešnom ili neuspešnom traženju jednog logički narednog sloga dat je sa:

$$(12.19) \qquad \overline{R} = \frac{B + Z + \lceil B/n \rceil}{N_v}$$

za slučaj direktnog povezivanja prekoračilaca i sa:

$$(12.20) \qquad \overline{R} = \frac{B + Z}{N_v}$$

za slučaj indirektnog povezivanja prekoračilaca.

Redosledna obrada indeks-sekvencijalne datoteke sa **indirektnim** povezivanjem prekoračilaca je efikasnija od redosledne obrade datoteke sa direktnim povezivanjem. Pri uobičajenim vrednostima reda stabla $n$, razlika je neznatna.

Pri redoslednoj obradi indeks-sekvencijalne datoteke, metoda pristupa čita sukcesivne slogove datoteke i kontroliše nailazak na kraj datoteke. Upoređivanje argumenta traženja i ključa predstavlja zadatak programa.

### Direktna obrada

Za obradu indeks-sekvencijalne datoteke putem vodeće datoteke od $N_v = N_v^u + N_v^n$ slogova u režimu direktne obrade, očekivani ukupni broj pristupa $\overline{R_{uk}}$ indeks-sekvencijalnoj datoteci iznosi:

$$\overline{R_{uk}} = \overline{R_u} N_v^u + \overline{R_n} N_v^n$$

gde je $\overline{R_u}$ očekivani broj pristupa pri uspešnom traženju, a $\overline{R_n}$ očekivani broj pristupa pri neuspešnom traženju.

Očekivani broj prekoračilaca $\overline{z}$ po jednom bloku primarne zone iznosi:

$$(12.21) \qquad \overline{z} = \frac{Z}{B}$$

Zamenom (12.21) u (12.8) i (12.9), za datoteku sa **direktnim** povezivanjem prekoračilaca se dobija, redom:

$$(12.22) \qquad \overline{R_u} = h + \frac{2f + \overline{z}(\overline{z} + 1)}{2(f + \overline{z})}$$

$$(12.23) \qquad \overline{R_n} = h + \frac{2f + \overline{z}(\overline{z} + 1)}{2(f + \overline{z})}$$

Zamenom (12.21) u (12.11) i (12.16), za datoteku sa **indirektnim** povezivanjem prekoračilaca se dobija, redom:

$$(12.24) \qquad \overline{R_u} = h + 1 + \frac{\overline{z}(\overline{z} + 1)}{2(f + \overline{z})}$$

$$(12.25) \qquad \overline{R_n} = h + 1 + \frac{\overline{z}(\overline{z} + 3)}{2(f + \overline{z})}$$

Direktna obrada indeks-sekvencijalne datoteke sa **direktnim** povezivanjem prekoračilaca je efikasnija nego direktna obrada datoteke sa indirektnim povezivanjem prekoračilaca. Razlika nije velika, a posledica je činjenica da je u indeks-sekvencijalnoj datoteci sa direktnim povezivanjem prekoračilaca efikasniji postupak traženja slučajno odabranog sloga.

### Primer 12.13.

Neka je datoteka od $N = 9000$ slogova organizovana kao indeks-sekvencijalna. Faktor blokiranja u primarnoj zoni je $f = 10$, a u zoni prekoračenja $f = 1$, a u zoni indeksa $n = 50$. Tada je $B = 901$ i $\lceil B/n \rceil = 19$. Zona prekoračenja sadrži $Z = 1000$ slogova. Vodeća datoteka sadrži $N_v = 9300$ slogova. Srednje vreme pristupa i prenosa bloka u operativnu memoriju iznosi $\overline{t} = 20 \text{ msek}$.

**Direktno povezivanje:** $R_{uk} = 1920$, $\overline{T_{uk}} \approx 38{,}4$ sek, a $\overline{R} \approx 0{,}206$.

**Indirektno povezivanje:** $R_{uk} = 1901$, $\overline{T_{uk}} = 38{,}02$ sek, a $\overline{R} \approx 0{,}204$.

### Primer 12.15.

U indeks-sekvencijalnoj datoteci iz primera 12.13, očekivani broj prekoračilaca po jednom bloku primarne zone iznosi $\overline{z} = 1$. Visina stabla traženja iznosi $h = 3$. Neka je $\overline{t} = 30$ msek vreme pristupa i vreme prenosa slučajno odabranog bloka datoteke u operativnu memoriju.

Datoteka se obrađuje u direktnom režimu putem vodeće datoteke od $N_v^u = 2100$ i $N_v^n = 900$ slogova.

**Direktno povezivanje:** $\overline{R_u} = 4{,}0$, $\overline{R_n} = 4{,}0$, i $\overline{R_{uk}} = 12000$. Odgovarajuća vremena iznose $\overline{t_u} = 120$ msek, $\overline{t_n} = 120$ msek i $\overline{T_{uk}} = 360$ sek.

**Indirektno povezivanje:** $\overline{R_u} = 4{,}09$, $\overline{R_n} = 4{,}18$ i $\overline{R_{uk}} = 12351$. Odgovarajuća vremena iznose $\overline{t_u} = 122{,}7$ msek, $\overline{t_n} = 125{,}4$ msek i $\overline{T_{uk}} = 370{,}53$ sek.

Direktna obrada indeks-sekvencijalne datoteke sa direktnim povezivanjem prekoračilaca je efikasnija nego direktna obrada datoteke sa indirektnim povezivanjem prekoračilaca. Razlika nije velika, a posledica je činjenica da je u indeks-sekvencijalnoj datoteci sa direktnim povezivanjem prekoračilaca efikasniji postupak traženja slučajno odabranog sloga.

---

## Ažuriranje indeks-sekvencijalne datoteke

Ažuriranje indeks-sekvencijalne datoteke se vrši u režimu direktne obrade. Pri tome, metoda pristupa koristi stablo traženja za utvrđivanje adrese bloka primarne zone kojem novi slog pripada, ili u kojem se nalazi slog za brisanje.

### Upis novog sloga

Upis novog sloga u datoteku se vrši nakon neuspešnog traženja. Ako se neuspešno traženje zaustavilo u bloku primarne zone, tada se vrši pomeranje slogova sa vrednošću ključa većom od vrednosti ključa novog sloga, za jednu lokaciju ka kraju bloka. Novi slog se upisuje u lokaciju koju je zauzimao slog sa prvom većom vrednošću ključa, a slog sa do tada najvećom vrednošću ključa u bloku upisuje se u zonu prekoračenja. Prekoračilac se upisuje u lokaciju čiju adresu sadrži indeks slobodnih lokacija i povezuje se sa ostalim prekoračiocima iz bloka. Povezivanje sa stablom traženja zavisi od postupka povezivanja prekoračilaca.

Ako se neuspešno traženje zaustavilo na nekom od prekoračilaca, novi slog se upisuje u prvu slobodnu lokaciju i uvezuje se sa ostalim prekoračiocima, kao u slučaju jednostruko spregnute datoteke.

**Kod direktnog povezivanja prekoračilaca**, tada se pri upisu u zonu prekoračenja sloga sa najvećom vrednošću ključa u bloku, ažurira list stabla traženja. U polje $A_z$ se upisuje adresa lokacije novog sloga, a adresa te lokacije se upisuje u polje pokazivača bloka.

**Kod indirektnog povezivanja prekoračilaca**, tada se pri upisu u zonu prekoračenja ažurira pokazivač bloka. Stari sadržaj polja pokazivača bloka se upisuje u polje pokazivača lokacije novog sloga, a adresa te lokacije se upisuje u polje pokazivača bloka.

**Očekivani broj pristupa za upis jednog novog sloga** u indeks-sekvencijalnu datoteku sa **direktnim** pristupom prekoračiocima iznosi:

$$(12.26) \qquad \overline{R_i} = \overline{R_n} + 3p_f + 2p_z$$

gde je $\overline{R_n}$ dato sa (12.9), $p_f$ sa (12.5), a $p_z$ sa (12.6). Pri tome, sa verovatnoćom $p_f$ potrebno je izvršiti:

- 1 pristup za upis bloka u primarnu zonu,
- 1 pristup za upis prekoračioca i
- 1 pristup za ažuriranje lista stabla traženja.

Takođe, sa verovatnoćom $p_z$, potrebno je izvršiti:

- 1 pristup za upis prekoračioca i
- 1 pristup za upis ili logički prethodnog prekoračioca sa izmenjenim pokazivačem, ili za upis ažuriranog lista stabla traženja (ako novi slog ima vrednost ključa manju od do tada najmanje vrednosti ključa u lancu prekoračilaca).

Zamenom (12.9), (12.5) i (12.6) u (12.26), dobija se:

$$(12.27) \qquad \overline{R_i} = h + \frac{8f + z(z + 5)}{2(f + z)}$$

### Primer 12.16.

Za upis sloga sa vrednošću ključa $k(S_{15}) = 14$ u indeks-sekvencijalnu datoteku sa slike 12.1, bilo je potrebno $R_i = 7$ pristupa. Za neuspešno traženje 4 pristupa, za upis modifikovanog bloka sa adresom $A_3^p$ 1 pristup, za upis sloga $S_6$ u zonu prekoračenja 1 pristup i za upis modifikovanog lista sa adresom $A_1^i$ još jedan pristup. Rezultat ažuriranja prikazan je na slici 12.3.

**Očekivani broj pristupa za upis jednog novog sloga** u indeks-sekvencijalnu datoteku sa **indirektnim** pristupom prekoračiocima iznosi:

$$(12.28) \qquad \overline{R_i} = \overline{R_n} + 2$$

gde je $\overline{R_n}$ dato formulom (12.16). Pri tome je potrebno izvršiti:

- 1 pristup za upis ili modifikovanog bloka ili logički neposredno prethodnog prekoračioca sa izmenjenim pokazivačem
- 1 pristup za upis prekoračioca

### Primer 12.17.

Za upis sloga sa vrednošću ključa $k(S_{14}) = 31$ u indeks-sekvencijalnu datoteku sa indirektnim pristupom prekoračiocima čija primarna zona odgovara primarnoj zoni datoteke sa slike 12.1, a stablo traženja je prikazano na slici 12.2, bilo je potrebno $R = 6$ pristupa. Za neuspešno traženje 4 pristupa, za upis sloga $S_{14}$ u zonu prekoračenja 1 pristup i za upis u primarnu zonu bloka sa adresom $A_3^p$ sa modifikovanim pokazivačem 1 pristup. Rezultat ažuriranja prikazan je na slici 12.4.

### Brisanje sloga

Brisanje slogova u indeks-sekvencijalnoj datoteci se, najčešće, izvodi **logički**. Svaki slog u datoteci ima jedno malo statusno polje čija vrednost određuje da li je slog aktuelan ili nije. Fizičko brisanje slogova bi zahtevalo pomeranje slogova sa ažuriranjem lanca prekoračilaca, što zahteva veći broj pristupa datoteci.

Ovako, nakon neuspešnog traženja (ako slog nije pronađen), potreban je još samo jedan pristup datoteci da bi se logički izbrisani slog upisao sa izmenjenim statusom u datoteku. Znači, broj pristupa za brisanje jednog sloga iznosi:

$$R_d = R_u + 1$$

Lokacija logički izbrisanog sloga se može upotrebiti za upis novog sloga samo ako vrednost ključa novog sloga leži u strogo određenim granicama. Ako se lokacija logički izbrisanog sloga nalazi u bloku zone podataka, vrednost ključa novog sloga mora biti manja od najveće vrednosti ključa u bloku i takva da slog logički pripada posmatranom bloku. Ako se lokacija nalazi u zoni prekoračenja, novi slog mora imati manju vrednost ključa od direktnog sledbenika logički izbrisanog sloga i veću vrednost ključa od direktnog prethodnika logički izbrisanog sloga.

### Izmena sadržaja sloga

Izmena sadržaja postojećeg sloga u datoteci je jednostavna. Nakon uspešnog traženja, potreban je još samo jedan pristup da bi se modifikovani slog upisao u datoteku.

Praktično sve aktivnosti ažuriranja indeks-sekvencijalne datoteke izvršava metoda pristupa. Aplikativni program za ažuriranje poziva metodu pristupa putem određenih makro naredbi.

### Primer 12.18.

Upis novog sloga u indeks-sekvencijalnu datoteku putem aplikativnog programa pisanog u Cobolu izvodi se na sledeći način. Vrednost ključa novog sloga se postavlja u polje definisano kao ACTUAL KEY, zatim sledi niz naredbi:

```
READ ime-datoteke RECORD
    INVALID KEY MOVE novi-slog TO ime-sloga
    WRITE ime-sloga
```

Metoda pristupa prvo traži slog sa vrednošću ključa postavljenom u polje definisano kao ACTUAL KEY, mora se postaviti argument traženja, a naredba:

```
READ ime-datoteke RECORD
    INVALID KEY imperativna-naredba
```

inicira traženje. Ako je traženje uspešno, metoda pristupa postavlja traženi slog u opis sloga radnog područja programa. Inače se izvršava klauzula INVALID KEY.

Brisanje postojećeg sloga vrši se postavljanjem njegove vrednosti ključa u polje definisano kao ACTUAL KEY i izdavanjem naredbe:

```
DELETE ime-sloga
    INVALID KEY imperativna-naredba
```

Ako metoda pristupa nađe slog, izbrisaće ga. Inače predaje upravljanje frazi izvršavanjem programa frazom INVALID KEY.

### Primer 12.14.

Da bi se indeks-sekvencijalna datoteka obrađivala u režimu redosledne obrade putem programa pisanog u Cobolu, način pristupa datoteci u okviru SELECT rečenice mora biti definisan kao SEQUENTIAL. Svaki korak algoritma linearnog traženja logički narednog sloga sadrži naredbu:

```
READ ime-datoteke RECORD
    AT END imperativna-naredba
```

Metoda pristupa predaje upravljanje imperativnoj naredbi iza AT END fraze kada metoda pristupa naiđe na oznaku kraja datoteke.

---

## Reorganizacija indeks-sekvencijalne datoteke

Aktivnosti upisa slogova u zonu prekoračenja i logičkog brisanja slogova dovode do degradacije performansi traženja slogova i obrade datoteke. Stepen degradacije performansi zavisi od intenziteta ažuriranja datoteke.

Da bi se ove negativne posledice ažuriranja datoteke otklonile, periodično se pristupa **reorganizaciji** datoteke. Reorganizacija se sastoji od:

- sortiranja aktuelnih slogova primarne zone i zone prekoračenja i
- smeštanja tako uređenog skupa slogova u novu primarnu zonu uz generisanje novog stabla traženja.

### Interval reorganizacije

Interval vremena između dve reorganizacije datoteke određuje se ili kao **fiksan** vremenski period ili se **dinamički** određuje na osnovu stepena popunjenosti zone prekoračenja. U prvom slučaju se datoteka reorganizuje na primer jednom nedeljno ili mesečno. U drugom slučaju se reorganizaciji pristupa kada se zona prekoračenja popuni do određenog procenta svog obima, na primer do 80%, a dimenzionisana je da primi na primer 10% broja slogova primarne zone.

### Distribuirani slobodni prostor

**Distribuirani slobodni prostor** je postupak koji ublažava problem degradacije performansi obrade zbog upisa novih slogova. Prema ovom postupku, blokovi podataka se pri formiranju datoteke popunjavaju samo delimično, na primer 60% ili 80%. Na taj način se obezbeđuje prostor za upis novih slogova. Međutim, kada se slobodni prostor unutar nekog bloka popuni, novi slogovi ponovo dovode do popunjavanja zone prekoračenja. Distribuirani slobodni prostor samo produžava interval vremena između dve reorganizacije datoteke.

Korišćenje distribuiranog slobodnog prostora dovodi do neekonomičnog korišćenja memorijskog prostora na eksternoj memorijskoj jedinici, jer je najveći deo distribuiranog slobodnog prostora tokom dobrog dela vremena između dve reorganizacije prazan.

### Primer 12.19.

Jedna od deklarativnih fraza naredbe FD (opisa datoteke) u Cobolu je fraza `BLOCK CONTAINS [ceo-broj-1 TO] ceo-broj-2 RECORDS`. Tom frazom se određuje faktor blokiranja u datoteci putem konstante `ceo-broj-2`. Ako se navedu i `ceo-broj-1` i `ceo-broj-2`, tada će indeks-sekvencijalna datoteka, nakon formiranja, sadržati blokove sa `ceo-broj-1` slogova i sa (`ceo-broj-2` - (`ceo-broj-1`)) slobodnih lokacija. Te slobodne lokacije služe za upis novih slogova pri ažuriranju.

### Ažuriranje kao sekvencijalna datoteka

Indeks-sekvencijalna datoteka se, u principu, može ažurirati i kao sekvencijalna u režimu redosledne obrade. Tada se, po završetku ažuriranja mora generisati novo stablo traženja, jer granične vrednosti ključa u blokovima primarne zone nisu više usaglašene sa vrednostima ključa u elementima čvorova. Ovakav postupak predstavlja reorganizaciju, a ne ažuriranje datoteke.

---

## Oblasti primene i ocena karakteristika

Indeks-sekvencijalno organizovane datoteke predstavljaju veoma pogodno rešenje kada iste podatke treba obrađivati jedanput u režimu redosledne, a drugi put u režimu direktne obrade. Zbog toga ova vrsta organizacije datoteke uživa izuzetnu popularnost u praksi. Intenzivno se koristi u paketnoj obradi, a često i u interaktivnoj daljinskoj obradi.

Odmah nakon formiranja indeks-sekvencijalne datoteke, performanse njene redosledne obrade praktično ne zaostaju za performansama redosledne obrade sekvencijalne datoteke. Performanse njene direktne obrade ne zaostaju značajnije za performansama direktne obrade rasute datoteke.

Međutim, upis slogova u zonu prekoračenja dovodi do degradacije performansi redosledne obrade. Pri tome se performanse redosledne obrade mogu držati pod kontrolom pogodnim dimenzionisanjem zone prekoračenja. To ne važi i za performanse traženja slučajno odabranog sloga. Broj prekoračilaca iz jednog bloka može biti veoma veliki. Gornju granicu broja prekoračilaca iz jednog bloka predstavlja ukupni broj prekoračilaca datoteke. To svakako predstavlja praktično nemoguć događaj, ali ukazuje da broj pristupa pri traženju nekih slogova u datoteci može biti nepredvidivo velik. Ceo problem nameće potrebu da se, pri ažuriranju, u fizičkoj strukturi datoteke ne naruši informacija o vezama između slogova u logičkoj strukturi datoteke. Jedino rešenje predstavlja periodično reorganizovanje datoteke, a to je, u slučaju velikih datoteka, dosta skup posao.

Fizičke strukture podataka zasnovane na principima izgradnje indeks-sekvencijalnih datoteka su se intenzivno koristile u mrežnim bazama podataka. Relacioni i objektno-relacioni sistemi za upravljanje bazama podataka ih retko podržavaju, tako da indeks-sekvencijalne datoteke, kako su opisane u ovom poglavlju, imaju više istorijski značaj, tako da se nazivaju i klasičnim indeks-sekvencijalnim datotekama. Na osnovnoj ideji indeks-sekvencijalnih datoteka, a to je da se brz pristup slučajno odabranom slogu u sekvencijalnoj strukturi vrši korišćenjem stabla traženja, kao funkcije koja preslikava vrednost ključa u adresu, zasnovane su moderne indeksne datoteke sa **B-stablima**.

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

P: Koje su tri zone statičke indeks-sekvencijalne datoteke?

P: Šta je primarna zona indeks-sekvencijalne datoteke?

P: Kakva je organizacija primarne zone?

P: Da li se primarna zona naknadno ažurira nakon formiranja?

P: Koji su ciljevi organizacije primarne zone?

P: Šta je zona indeksa?

P: Kakvu strukturu ima zona indeksa?

P: Šta predstavlja par $(k_e, A_e)$ u zoni indeksa?

P: Šta predstavlja $A_e$ u listu stabla traženja?

P: Šta predstavlja $A_e$ u čvoru na višem nivou hijerarhije?

P: Šta se propagira u zonu indeksa - koje vrednosti ključa?

P: Koja se vrednost ključa upisuje kao najveća u stablo kada stablo sadrži propagaciju najvećih vrednosti?

P: Koja se vrednost ključa upisuje kao najmanja u stablo kada stablo sadrži propagaciju najmanjih vrednosti?

P: Kako glasi formula za visinu stabla traženja $h$?

P: Kako glasi formula za broj čvorova $C_i$ na $i$-tom nivou hijerarhije?

P: Kako glasi formula za ukupni broj čvorova stabla $C$?

P: Šta je kapacitet stabla $K$?

P: Kako glasi formula za ukupni broj elemenata $E$ u stablu pristupa?

P: Koliko su $h$, $C$, $K$ i $E$ za $B = 5$ i $n = 2$?

P: Šta je zona prekoračenja?

P: Šta su prekoračioci?

P: Kada nastaju prekoračioci?

P: Šta se dešava pri upisu novog sloga kada blok primarne zone nije kompletan?

P: Šta se dešava pri upisu novog sloga kada je blok primarne zone kompletan i $k(S) < k_{e(max)}$?

P: Šta se dešava pri upisu novog sloga kada je blok primarne zone kompletan i $k(S) > k_{e(max)}$?

P: Koja dva postupka povezivanja prekoračilaca sa listom stabla traženja postoje?

P: Kako funkcioniše direktno povezivanje prekoračilaca?

P: Šta predstavlja četvorka $(k_e, A_e, k_z, A_z)$ u listu kod direktnog povezivanja?

P: Šta znači jednakost $A_e = A_z$ kod direktnog povezivanja?

P: Kako funkcioniše indirektno povezivanje prekoračilaca?

P: Čime je proširen blok primarne zone kod indirektnog povezivanja?

P: Šta je fiktivni slog sa vrednošću ključa 0 kod indirektnog povezivanja?

P: Zašto je faktor blokiranja u zoni prekoračenja najčešće jednak 1?

P: Šta je indeks slobodnih lokacija $E$ u zoni prekoračenja?

P: Šta je indeks-sekvencijalna metoda pristupa?

P: Koje makro naredbe koriste korisnički programi za rad sa IS datotekom?

P: Kako se u Cobolu definiše indeks-sekvencijalna organizacija datoteke?

P: Koji su koraci u formiranju indeks-sekvencijalne datoteke?

P: Odakle počinje formiranje stabla traženja - sa kog nivoa?

P: Da li se pri formiranju datoteke upisuju slogovi u zonu prekoračenja?

P: Koliko parova $(k_e, A_e)$ metoda pristupa upisuje u krajnji desni čvor na $i$-tom nivou?

P: Kako se vrši traženje logički narednog sloga u IS datoteci?

P: Kako glasi formula (12.2) za interval broja pristupa pri traženju logički narednog sloga sa direktnim povezivanjem?

P: Kako glasi formula (12.3) za interval broja pristupa pri traženju logički narednog sloga sa indirektnim povezivanjem?

P: Koje traženje logički narednog sloga je efikasnije - sa direktnim ili indirektnim povezivanjem?

P: Koliko pristupa čvorovima stabla je potrebno za traženje u stablu?

P: Šta se dešava ako metoda pristupa ima dva bafera umesto jednog?

P: Kako se vrši traženje slučajno odabranog sloga u IS datoteci?

P: Kako glasi interval broja pristupa $R$ za traženje slučajno odabranog sloga sa direktnim povezivanjem?

P: Kako glasi interval broja pristupa $R$ za traženje slučajno odabranog sloga sa indirektnim povezivanjem?

P: Koje traženje slučajno odabranog sloga je efikasnije - sa direktnim ili indirektnim povezivanjem?

P: Kako glasi formula (12.5) za verovatnoću $p_f$?

P: Kako glasi formula (12.6) za verovatnoću $p_z$?

P: Kako glasi formula (12.8) za $\overline{R_u}$ kod direktnog povezivanja?

P: Kako glasi formula (12.9) za $\overline{R_n}$ kod direktnog povezivanja?

P: Kako glasi formula (12.11) za $\overline{R_u}$ kod indirektnog povezivanja?

P: Kako glasi formula (12.12) za verovatnoću $p_f$ kod neuspešnog traženja pri indirektnom povezivanju?

P: Kako glasi formula (12.13) za verovatnoću $p_z$ kod neuspešnog traženja pri indirektnom povezivanju?

P: Kako glasi formula (12.16) za $\overline{R_n}$ kod indirektnog povezivanja?

P: Kako glasi formula (12.15) za raspodelu verovatnoće $p_i$ pri indirektnom povezivanju?

P: Kako se izračunava ukupni broj pristupa $R_{uk}$ pri redoslednoj obradi sa direktnim povezivanjem?

P: Kako se izračunava ukupni broj pristupa $R_{uk}$ pri redoslednoj obradi sa indirektnim povezivanjem?

P: Koja redosledna obrada je efikasnija - sa direktnim ili indirektnim povezivanjem?

P: Kako se izračunava očekivani ukupni broj pristupa $\overline{R_{uk}}$ pri direktnoj obradi?

P: Kako se izračunava očekivani broj prekoračilaca $\overline{z}$ po jednom bloku?

P: Kako glasi formula (12.22) za $\overline{R_u}$ pri direktnoj obradi sa direktnim povezivanjem?

P: Kako glasi formula (12.24) za $\overline{R_u}$ pri direktnoj obradi sa indirektnim povezivanjem?

P: Koja direktna obrada je efikasnija - sa direktnim ili indirektnim povezivanjem?

P: Kako se vrši upis novog sloga u IS datoteku?

P: Kako glasi formula (12.26) za očekivani broj pristupa pri upisu sa direktnim povezivanjem?

P: Kako glasi formula (12.27) za $\overline{R_i}$ pri upisu sa direktnim povezivanjem?

P: Kako glasi formula (12.28) za $\overline{R_i}$ pri upisu sa indirektnim povezivanjem?

P: Kako se vrši logičko brisanje sloga u IS datoteci?

P: Koliko pristupa je potrebno za brisanje sloga ($R_d$)?

P: Kada se lokacija logički izbrisanog sloga može upotrebiti za upis novog sloga?

P: Kako se vrši izmena sadržaja postojećeg sloga?

P: Od čega se sastoji reorganizacija IS datoteke?

P: Koji su načini određivanja intervala reorganizacije?

P: Šta je distribuirani slobodni prostor?

P: Kako distribuirani slobodni prostor ublažava degradaciju performansi?

P: Koji je nedostatak distribuiranog slobodnog prostora?

P: Koje su prednosti indeks-sekvencijalne organizacije datoteke?

P: Za koje režime obrade je pogodna IS datoteka?

P: Šta je najveći nedostatak IS datoteke?

P: Na koji način su moderne indeksne datoteke zasnovane na principima IS datoteka?

P: Zašto se IS datoteke nazivaju i klasičnim indeks-sekvencijalnim datotekama?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasni kompletnu strukturu statičke indeks-sekvencijalne datoteke i kakvu organizaciju ima svaka od tri zone.

**O:** Statička indeks-sekvencijalna datoteka se sastoji od tri zone: primarne zone (zone podataka), zone indeksa i zone prekoračenja. Primarna zona ima sekvencijalnu organizaciju - slogovi su uređeni po rastućim vrednostima ključa i grupisani u blokove. Zona indeksa ima spregnutu organizaciju u obliku n-arnog punog stabla traženja čiji elementi su parovi (vrednost ključa, adresa bloka), a služi za brz pristup blokovima primarne zone. Zona prekoračenja takođe ima spregnutu organizaciju u obliku lanaca prekoračilaca - sadrži slogove koji se upisuju tokom ažuriranja kada je blok primarne zone pun.

**P:** Za datoteku sa $B = 10$ blokova i redom stabla $n = 3$, izračunaj visinu stabla $h$, ukupni broj čvorova $C$ i kapacitet stabla $K$.

**O:** Visina stabla: $h = \lceil \log_3 10 \rceil = \lceil 2{,}096 \rceil = 3$. Broj čvorova po nivoima: $C_1 = \lceil 10/27 \rceil = 1$, $C_2 = \lceil 10/9 \rceil = 2$, $C_3 = \lceil 10/3 \rceil = 4$. Ukupno: $C = 1 + 2 + 4 = 7$. Kapacitet: $K = nC = 3 \cdot 7 = 21$.

**P:** Uporedi direktno i indirektno povezivanje prekoračilaca sa listovima stabla traženja - kako funkcionišu i koji postupak je efikasniji za koje traženje?

**O:** Kod direktnog povezivanja, informacija o lancu prekoračilaca se čuva u samom listu stabla traženja kao četvorka $(k_e, A_e, k_z, A_z)$, pa se odmah po dolasku u list zna da li treba tražiti u primarnoj zoni ili u zoni prekoračenja. Kod indirektnog povezivanja, pokazivač na lanac prekoračilaca je u bloku primarne zone, pa se posle stabla mora pristupiti bloku pa tek onda eventualno prekoračiocima. Direktno povezivanje je efikasnije za traženje slučajno odabranog sloga (manje pristupa), dok je indirektno efikasnije za traženje logički narednog sloga (ne zahteva pristup listovima stabla).

**P:** Šta se tačno dešava prilikom upisa novog sloga u pun blok primarne zone kod IS datoteke?

**O:** Kada je blok primarne zone kompletan ($m = n$), pri upisu novog sloga sa vrednošću ključa $k(S)$: ako je $k(S) < k_{e(max)}$ (trenutno maksimalna vrednost ključa u bloku), novi slog se upisuje u blok na odgovarajuće mesto, svi slogovi sa većim ključem se pomeraju za jednu lokaciju ka kraju bloka, a slog sa do tada najvećom vrednošću ključa $k_{e(max)}$ se "istiskuje" u zonu prekoračenja. Ako je $k(S) > k_{e(max)}$, novi slog se direktno upisuje u zonu prekoračenja jer ne pripada primarnoj zoni tog bloka.

**P:** Izračunaj očekivani broj pristupa pri uspešnom i neuspešnom traženju za datoteku sa $h = 3$, $f = 10$ i $z = 2$ za obe varijante povezivanja.

**O:** Za direktno povezivanje: $\overline{R_u} = 3 + \frac{2 \cdot 10 + 2 \cdot 3}{2 \cdot 12} = 3 + \frac{26}{24} \approx 4{,}08$. Za indirektno povezivanje: $\overline{R_u} = 3 + 1 + \frac{2 \cdot 3}{2 \cdot 12} = 4 + 0{,}25 = 4{,}25$. Za neuspešno direktno: $\overline{R_n} = 4{,}08$ (ista formula). Za neuspešno indirektno: $\overline{R_n} = 3 + 1 + \frac{2 \cdot 5}{24} = 4 + 0{,}42 \approx 4{,}42$.

**P:** Objasni zašto i kako se vrši reorganizacija indeks-sekvencijalne datoteke i koji su načini za odlaganje reorganizacije.

**O:** Reorganizacija je neophodna jer upis slogova u zonu prekoračenja i logičko brisanje degradiraju performanse traženja i obrade. Postupak se sastoji od sortiranja aktuelnih slogova primarne zone i zone prekoračenja, smeštanja uređenih slogova u novu primarnu zonu i generisanja novog stabla traženja sa novom praznom zonom prekoračenja. Interval reorganizacije može biti fiksan (npr. mesečno) ili dinamički (npr. kada se zona prekoračenja popuni do 80%). Distribuirani slobodni prostor, pri kojem se blokovi primarne zone popunjavaju samo delimično (60-80%), produžava vreme do potrebne reorganizacije, ali po cenu neekonomičnog korišćenja memorije.

**P:** Objasni kako radi traženje logički narednog sloga u IS datoteci i zašto je indirektno povezivanje efikasnije za ovaj tip traženja.

**O:** Traženje logički narednog sloga kombinuje linearno traženje u bloku primarne zone sa praćenjem pokazivača u lancu prekoračilaca. Počinje u prvom bloku i nastavlja se sekvencijalno kroz blokove i njihove lance. Kod direktnog povezivanja, interval broja pristupa je $0 \leq R \leq B + \lceil B/n \rceil + Z - (i+j+k)$ jer se moraju pristupati i listovi stabla traženja. Kod indirektnog povezivanja, interval je $0 \leq R \leq B + Z - (i+k)$ jer se pokazivači na prekoračioce nalaze direktno u blokovima primarne zone, bez potrebe za pristupom listovima. Član $\lceil B/n \rceil$ predstavlja razliku.

**P:** Neka je IS datoteka od $N = 5000$ slogova sa $f = 5$, $n = 50$, $Z = 500$. Koliko iznosi ukupni broj pristupa pri redoslednoj obradi za obe varijante povezivanja?

**O:** $B = N/f = 5000/5 = 1000$, $\lceil B/n \rceil = \lceil 1000/50 \rceil = 20$. Za direktno povezivanje: $R_{uk} = B + Z + \lceil B/n \rceil = 1000 + 500 + 20 = 1520$. Za indirektno povezivanje: $R_{uk} = B + Z = 1000 + 500 = 1500$. Razlika je $\lceil B/n \rceil = 20$ pristupa, što pri velikom $n$ čini razliku neznatnom.

**P:** Koja je osnovna prednost IS datoteke u odnosu na sekvencijalnu i rasutou, i koji je njen najveći nedostatak?

**O:** IS datoteka predstavlja kompromis: podržava i efikasnu redoslednu obradu (zahvaljujući sekvencijalno organizovanoj primarnoj zoni) i relativno brz direktan pristup (zahvaljujući stablu traženja u zoni indeksa). Njen najveći nedostatak je degradacija performansi tokom ažuriranja jer se novi slogovi gomilaju u zoni prekoračenja, pri čemu lanci prekoračilaca mogu postati nepredvidivo dugački. Jedino rešenje je periodična reorganizacija, koja je za velike datoteke skup postupak. Ovaj problem su rešile moderne indeksne datoteke zasnovane na B-stablima, koje se dinamički i lokalizovano reorganizuju.

**P:** Objasni razliku u formulama za očekivani broj pristupa pri neuspešnom traženju između direktnog (12.9) i indirektnog (12.16) povezivanja.

**O:** Kod direktnog povezivanja, formula (12.9) glasi $\overline{R_n} = h + \frac{2f + z(z+1)}{2(f+z)}$. Kod indirektnog, formula (12.16) glasi $\overline{R_n} = h + 1 + \frac{z(z+3)}{2(f+z)}$. Ključna razlika je taj "+1" kod indirektnog koji dolazi od obaveznog pristupa bloku primarne zone pre pristupa prekoračiocima. Kod direktnog povezivanja, već u listu stabla se odlučuje da li ići u primarnu zonu ili u prekoračioce, čime se ponekad izbegava jedan pristup. Razlika u brojiocima ($2f + z(z+1)$ vs $z(z+3)$) potiče od različitih raspodela verovatnoće zaustavljanja neuspešnog traženja.
