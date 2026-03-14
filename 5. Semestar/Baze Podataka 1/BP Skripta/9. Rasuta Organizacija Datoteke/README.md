# Statička rasuta organizacija datoteke

Zamislimo sledeću situaciju: imaš telefonski imenik sa milion brojeva, i neko te pita za broj telefona osobe sa prezimenom "Petrović". Ako je imenik sortiran po abecedi, možeš relativno brzo da nađeš traženi broj - ali šta ako bi mogao da iz samog prezimena *direktno izračunaš* na kojoj se stranici taj broj nalazi? Bez ikakvog listanja, bez pretraživanja - samo izračunaš i odmah odeš na pravu stranicu. Upravo to rade rasuto organizovane datoteke, i u ovoj skripti ćemo detaljno proći kroz sve varijante ove moćne organizacije.

---

## 1. Uvod u rasute datoteke

Rasuto organizovane datoteke se dele na dve osnovne kategorije: **statičke** i **dinamičke**. Ključna razlika je sledeća:

- Kod **statičke rasute datoteke**, veličina dodeljenog adresnog prostora se određuje prilikom projektovanja i tokom eksploatacije se ne može menjati.
- Kod **dinamičke rasute datoteke**, veličina dodeljenog adresnog prostora se menja tokom ažuriranja, saglasno trenutnim potrebama.

Statičke rasute datoteke su, istorijski gledano, nastale mnogo pre dinamičkih. U daljem tekstu ćemo se baviti isključivo statičkim rasutim datotekama, koje se skraćeno nazivaju **rasutim datotekama**.

Rasuta organizacija datoteke se često naziva i **direktnom**, jer se slogu ili grupi slogova pristupa direktno, na osnovu poznavanja adrese memorijske lokacije u koju su slogovi smešteni. Adresa lokacije se dobija **transformacijom vrednosti identifikatora sloga u adresu**.

### 1.1 Identifikator

**Identifikator** predstavlja obeležje čije vrednosti jednoznačno određuju slogove datoteke. Sam identifikator, kao obeležje, može a ne mora pripadati skupu obeležja tipa sloga datoteke.

Hajde da razjasnimo ove dve situacije:

1. **Identifikator pripada skupu obeležja tipa sloga** - tada on igra ulogu identifikatora, a po pravilu i ulogu primarnog ključa datoteke. Na primer, JMBG u datoteci studenata.
2. **Identifikator NE pripada skupu obeležja tipa sloga** - tada se vrednosti identifikatora pridružuju svakom slogu eksterno, van konteksta sadržaja datoteke. Pri tome mora postojati neko pravilo povezivanja vrednosti identifikatora i slogova datoteke.

> [!NOTE]
> **Primer 11.1.** Pridruživanje vrednosti identifikatora slogovima datoteke je, na određeni način, analogno situaciji kada se o učenicima nekog razreda u školi ne govori navodeći njihova imena, već navodeći broj reda i poziciju klupe u koju su raspoređeni da sede.

### 1.2 Funkcija transformacije

Za transformaciju vrednosti identifikatora u adresu koristi se **funkcija $h$** koja preslikava domen identifikatora $K$ u skup adresa $A$ lokacija memorijskog prostora dodeljenog datoteci. Znači:

$$h : dom(K) \rightarrow A$$

Ako je $k_i$ vrednost identifikatora $K$ pridružena slogu $S_i$, $i \in \{1, ..., N\}$, tada se adresa $A_i \in A$ lokacije u koju treba smestiti slog $S_i$ dobija kao:

$$A_i = h(k_i)$$

Transformacija vrednosti identifikatora u adresu može biti:

- **Deterministička** - svaka vrednost identifikatora se preslikava u adresu lokacije po jednoznačnom pravilu. Kod jedne vrednosti identifikatora odgovara najviše jedna vrednost adrese, i svakoj adresi odgovara najviše jedna vrednost identifikatora. Drugim rečima, funkcija $h$ je u slučaju determinističke transformacije **injektivna**.
- **Probabilistička** - vrednost identifikatora se pretvara u adresu nekom od metoda za generisanje pseudoslučajnih brojeva. Svakoj vrednosti identifikatora odgovara jedna od adresa memorijskog prostora dodeljenog datoteci, ali jednoj adresi može odgovarati više rezultata transformacije identifikatora.

### 1.3 Fizička struktura i baketi

Fizička struktura podataka rasute datoteke ne sadrži informaciju o vezama između slogova logičke strukture podataka. U dve fizički susedne lokacije mogu, a ne moraju biti memorisani logički susedni slogovi. Sa tačke gledišta logičke strukture podataka, slogovi su slučajno rasuti po memorijskom prostoru dodeljenom datoteci - otuda i ime.

Kada je reč o rasutim datotekama, lokacija u koju se smešta jedan ili više slogova naziva se **baketom**. Pojam baketa je analogan pojmu bloka. Analogno pojmu faktora blokiranja, uvodi se pojam **faktora baketiranja $b$** ($b \geq 1$). Faktor baketiranja ukazuje na maksimalno mogući broj slogova u jednom baketu. Transformacijom se vrednost identifikatora pretvara u adresu baketa.

> [!TIP]
> Zamislite baket kao fioku u ormanu. Faktor baketiranja $b$ je broj predmeta koji stanu u jednu fioku. Ako je $b = 3$, u svaku fioku mogu stati 3 sloga.

**Primer 11.2.** Na slici 11.1 prikazana je fizička struktura jedne rasute datoteke od $N = 10$ slogova sa faktorom baketiranja $b = 3$. Datoteci je dodeljeno $B = 5$ baketa. Datoteka sadrži pravi podskup skupa slogova serijske datoteke. Kao identifikator, korišćen je primarni ključ datoteke. Za transformaciju je korišćena formula:

$$h(k_i) = 1 + k(S_i)(\text{mod } B)$$

Za $i \in \{1, ..., N\}$. Rezultat transformacije predstavlja relativnu adresu baketa.

| Baket | Lokacija 1 | Lokacija 2 | Lokacija 3 |
|-------|-----------|-----------|-----------|
| 1 | 15, $p(S_4)$ | 25, $p(S_7)$ | - |
| 2 | - | - | - |
| 3 | 07, $p(S_2)$ | 27, $p(S_9)$ | - |
| 4 | 03, $p(S_3)$ | 23, $p(S_8)$ | 13, $p(S_{10})$ |
| 5 | 34, $p(S_1)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |

---

## 2. Opšti postupak formiranja rasute datoteke

Statičkoj rasutoj datoteci se u postupku formiranja dodeljuje $Q = bB$ lokacija, pri čemu važi $N \leq Q$. Nakon formiranja se $Q$ više ne može menjati.

I u slučaju determinističke i u slučaju probabilističke transformacije identifikatora u adresu, redosled smeštanja slogova u datoteku je nevažan. Slogovi se, saglasno hronološkom redosledu nastanka, uvode u proceduru za traženje, gde se vrši transformacija vrednosti identifikatora u adresu. Ako je traženje neuspešno, slog se smešta u baket sa izračunatom adresom.

Kod probabilističke transformacije se može desiti da baket, čija adresa je dobijena transformacijom, bude popunjen. Tada se primenjuju posebni postupci za traženje lokacije u koju će se slog smestiti.

U nastavku ovog poglavlja, opisana je **relativna datoteka**, kao predstavnik rasutih datoteka sa determinističkom transformacijom identifikatora u adresu, i opisano je nekoliko varijanti rasutih datoteka sa probabilističkom transformacijom vrednosti identifikatora u adresu. Sve ove datoteke poseduju niz specifičnosti kada je u pitanju formiranje, traženje i ažuriranje, ali i jednu zajedničku karakteristiku. To je postupak obrade. Karakteristike obrade svih rasuto organizovanih datoteka su na jednom mestu u okviru ovog poglavlja.

---

## 3. Direktne datoteke

Najjednostavniji vid determinističke transformacije identifikatora u adresu predstavlja slučaj kada vrednost identifikatora odgovara adresi baketa. Tada je transformacija trivijalna, tj. $A_i = k_i$. Strogo govoreći, jedino rasuto organizovane datoteke dobijene trivijalnom transformacijom vrednosti identifikatora u adresu baketa s pravom nose naziv **"direktne"**.

Postoje dve vrste rasuto organizovanih datoteka dobijenih trivijalnom transformacijom vrednosti identifikatora u adresu:

1. **Kod prve**, vrednost identifikatora je jednaka **mašinskoj adresi**.
2. **Kod druge**, vrednost identifikatora je jednaka **relativnoj adresi**. U oba slučaja identifikator ne predstavlja deo sloga.

Kod direktnih datoteka sa mašinskim adresama, svakom slogu se pridružuje identifikator u obliku mašinske adrese. Ako se datoteka nalazi na magnetnom disku, taj identifikator predstavlja trojku (*broj cilindra, broj staze, broj sektora*). Za korišćenje direktnih datoteka sa mašinskim adresama, neophodno je u programu eksplicitno navesti mašinsku adresu baketa, kojem se želi pristupiti. Zbog toga se ne mogu koristiti putem programa pisanih u višim programskim jezicima, te imaju samo istorijski značaj. U daljem tekstu će biti ukazano na još dva nedostatka ovih datoteka.

Te nedostatke predstavljaju:

- **Čvrsta povezanost** slogova datoteke sa fizičkim karakteristikama memorijskog uređaja
- **Odsustvo logičke veze** između vrednosti identifikatora i sadržaja sloga

### 3.1 Posledice odsustva logičke veze

Odsustvo logičke veze između vrednosti identifikatora i sadržaja sloga ima za posledicu:

- Da programer mora da vodi računa o fizičkoj adresi lokacije u kojoj je smešten slog, pri čemu ta adresa nema nikakve logičke veze sa sadržajem sloga.
- Ako se podaci o istom entitetu javljaju u više direktnih datoteka, istom entitetu se pridružuje više različitih identifikatora.
- Ako se neki identifikator, nakon brisanja podataka o jednom entitetu, dodeli drugom, može doći do konfuzije pri obradi ranijih i aktuelnih podataka.

---

## 4. Rasute datoteke sa determinističkom transformacijom

Problem čvrste povezanosti slogova datoteke sa fizičkim karakteristikama memorijskog uređaja rešava se korišćenjem **relativnih adresa**. Lokacije memorijskog prostora dodeljenog datoteci privremeno se numerišu rednim brojevima od $1$ do $Q$ (ili od $0$ do $Q - 1$). Ti redni brojevi predstavljaju i relativne adrese lokacija i identifikatore slogova, koji se smeštaju u lokacije sa odgovarajućom relativnom adresom.

Identifikator i dalje ne predstavlja podskup skupa obeležja tipa sloga. Pošto se svakoj lokaciji na memorijskom uređaju može pristupiti samo na osnovu njene mašinske adrese, relativne adrese se moraju transformisati u mašinske. Ova transformacija predstavlja zadatak dela sistema za upravljanje podacima koji se naziva **relativnom metodom pristupa**. Često se i datoteke, formirane korišćenjem relativne metode pristupa, nazivaju **relativnim datotekama**.

U lokacije memorijskog prostora dodeljenog relativnoj datoteci, slogovi se upisuju saglasno vrednosti identifikatora. Ne postoji fiksno pravilo za pridruživanje vrednosti identifikatora slogovima datoteke. Međutim, kada se to pravilo jedanput utvrdi, ono uspostavlja vezu između sloga i adrese lokacije u koju je slog smešten. Za fizičku strukturu relativne datoteke je, takođe, karakteristično da ne poseduje informaciju o vezama između slogova u logičkoj strukturi podataka datoteke.

**Primer 11.3.** Na slici 11.2 prikazana je fizička struktura relativne datoteke od $N = 13$ slogova. Faktor baketiranja iznosi $b = 3$, a datoteci je dodeljeno $Q = 15$ lokacija. Datoteka sadrži iste slogove kao serijska datoteka. Pravilo za pridruživanje vrednosti identifikatora slogovima dato je sledećom tabelom:

| $S_i$ | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|----------|----------|----------|----------|
| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
| $k_i$ | $A_1^1$ | $A_2^1$ | $A_3^1$ | $A_2^1$ | $A_2^2$ | $A_2^3$ | $A_3^1$ | $A_3^2$ | $A_3^3$ | $A_4^1$ | $A_4^2$ | $A_4^2$ | $A_5^1$ |

Svakom hronološki narednom slogu pridružena je adresa prve slobodne lokacije od početka memorijskog prostora dodeljenog datoteci. Naime, hronološki prvom slogu je dodeljena lokacija sa adresom $A_1^1$, a $i$-tom slogu se pridružuje adresa $A_p^q$, gde je $p = \lceil i/b \rceil$, a $q = 1 + (i - 1)(\text{mod } b)$, za $i = 2, ..., 13$.

Fizička struktura relativne datoteke iz primera 11.3:

| Baket | Lokacija 1 | Lokacija 2 | Lokacija 3 |
|-------|-----------|-----------|-----------|
| $A_1$ | 34, $p(S_1)$ | 07, $p(S_2)$ | 03, $p(S_3)$ |
| $A_2$ | 15, $p(S_4)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |
| $A_3$ | 64, $p(S_7)$ | 43, $p(S_8)$ | 23, $p(S_9)$ |
| $A_4$ | 27, $p(S_{10})$ | 13, $p(S_{11})$ | 49, $p(S_{12})$ |
| $A_5$ | 25, $p(S_{13})$ | $*$ | - |

### 4.1 Relativna metoda pristupa

Sistem za upravljanje podacima mainframe računarskih sistema su posedovali metodu pristupa za standardizovano formiranje, korišćenje i ažuriranje relativnih datoteka. Ovu metodu pristupa koristili su programi pisani u višim programskim jezicima. Savremena softverska okruženja, bilo koji operativni sistemi (Unix, C), bilo koji programski jezici, podržavaju relativne datoteke putem standardnih bibliotečkih funkcija, ali ostavljaju aplikativnom programu da reše čitav niz rutinskih aktivnosti rada sa datotekom, koje su operativni sistemi mainframe računara i programski jezici (Cobol) podržavali.

Jedan od zadataka relativne metode pristupa je transformacija vrednosti relativne adrese (tzv. relativnog ključa) u mašinsku adresu. Osim toga, relativna metoda pristupa vrši upis slogova u datoteku, brisanje slogova, izvještava program o neuspešnom čitanju ili brisanju (ako je adresirana lokacija prazna), i o neuspešnom upisu (ako se u adresiranoj lokaciji već nalazi neki slog).

Operativni sistemi mainframe računara i programski jezici, kao što je Cobol, posmatrali su relativnu datoteku kao niz slogova. Relativna adresa sloga je njegov redni broj od početka datoteke. Operativni sistem Unix i programski jezici (C) posmatraju datoteku kao niz bajtova. Relativna adresa sloga je jednaka proizvodu rednog broja sloga od početka datoteke i broja bajtova, upotrebljenih za njegovo memorisanje. Ova činjenica ukazuje na neophodnost korišćenja slogova konstantne dužine u relativnim datotekama.

Relativna metoda pristupa pruža programu usluge na nivou bloka, tako da ne vrši blokiranje i rastavljanje blokova na slogove, odnosno prihvata samo jednu vrednost faktora blokiranja (jednaku jedinici). Da bi se, u cilju boljeg iskorišćenja memorijskog prostora, slogovi ipak mogli smeštati u relativnu datoteku blokirano, aktivnosti blokiranja i rastavljanja blokova na slogove se moraju realizovati u okviru samog programa. U tom cilju se organizaciona jedinica podataka koja se razmenjuje između programa i relativne datoteke na eksternom memorijskom uređaju mora definisati kao jednodimenzionalni niz.

### 4.2 Formiranje relativne datoteke

Korisnici mainframe računarskih sistema su za formiranje relativne datoteke pisali program koji je koristio usluge relativne metode pristupa. Taj program je učitavao sukcesivne slogove neke serijske datoteke, pridruživao im vrednosti identifikatora i smeštao ih u lokacije čije adrese predstavljaju vrednosti identifikatora.

Pri formiranju relativne datoteke, metoda pristupa postavlja vrednost jednog u relativni ključ, tako da se prvi baket upisuje u lokaciju sa relativnom adresom $1$. Pri izvršavanju svake naredne WRITE naredbe, vrednost relativnog ključa se povećava za jedinicu. To znači da se, pre početka formiranja, za datoteku mora rezervisati $Q \geq N$ lokacija.

Zavisno od korišćenog operativnog sistema, postojala su dva postupka za formiranje relativne datoteke. Razlike pri formiranju su poticale od činjenice da se, prema jednom od postupaka, prethodno moraju u sve lokacije datoteke upisati lažni slogovi. Upis lažnih slogova se vrši u onim slučajevima kada metoda pristupa, nakon prvog zatvaranja datoteke, definiše granice datoteke saglasno broju upisanih slogova. Ukoliko ceo dodeljeni prostor ostaje na raspolaganju datoteci nakon prvog zatvaranja, prethodni upis lažnih slogova nije neophodan. Prethodni upis lažnih slogova nije neophodan ni u slučaju kada operativni sistem dinamički dodeljuje memorijski prostor pri narastanju datoteke. Međutim, ako se pri ažuriranju slogovi žele logički brisati, pogodno je prvo formirati lažne slogove sa statusnom oznakom. Sadržaj statusne oznake treba da ukaže da se radi o inicijalno praznim lokacijama.

### 4.3 Traženje u relativnoj datoteci

Traženje i logički narednog i slučajno odabranog sloga u relativnoj datoteci vrši se metodom transformacije identifikatora u adresu. Pošto je transformacija trivijalna, ceo postupak se svodi na saopštavanje vrednosti identifikatora, odnosno relativne adrese lokacije, relativnoj metodi pristupa.

Na osnovu tako zadate adrese, metoda pristupa prenosi baket u radnu zonu programa. Ako se traženi slog nalazi u baketu, traženje se završilo uspešno. Inače je traženje neuspešno.

**Primer 11.5.** Traženje sloga u relativnoj datoteci putem programa pisanog u Cobolu realizuje se tako što se za način pristupa deklariše da je RANDOM. U delu procedure se, nakon postavljanja vrednosti identifikatora u ime_promenljive, izdaje naredba:

```
READ ime_datoteke RECORD
   INVALID KEY imperativna naredba.
```

Imperativna naredba stupa u dejstvo ako je adresirana lokacija prazna.

**Primer 11.6.** Neka se datoteka `student.data` sa slogovima konstantne dužine od 47 bajtova formira postupkom opisanim u primeru 3.11. Neka je u datoteku upisano 30 slogova. Da bi se pročitao slog sa rednim brojem 17, potrebno je prvo izvršiti pozicioniranje na njegov početak korišćenjem `fseek` naredbe:

```c
fseek(fpt, 752L, 0);
```

a zatim izvršiti čitanje putem naredbe:

```c
pov_vred = fscanf(fpt, "%11d%30[^\n]%6d",
    &student.broj_indeksa, student.ime, &student.broj_poena);
```

Broj pristupa $R_u$ pri uspešnom traženju, kako logički narednog tako i slučajno odabranog sloga, iznosi:

$$R_u = 1$$

Kada je reč o broju upoređenja, tu se mogu razlikovati dva slučaja. U prvom, svakom slogu se pridružuje relativna adresa lokacije. Tada je:

$$U_u = 1$$

U drugom slučaju, slogu se pridružuje adresa baketa. Pošto baket može sadržati do $b$ slogova, broj upoređenja uzima celobrojne vrednosti iz intervala:

$$1 \leq U_u \leq b$$

**Primer 11.6 (nastavak).** Da bi se pronašlo bilo logički naredno, bilo slučajno odabrani slog u datoteci na slici 11.2, mora se koristiti tabela putem koje su relativne adrese lokacija pridružene slogovima. Nije teško utvrditi da je za uspešno traženje svakog od 13 slogova potreban jedan pristup i jedno upoređenje.

Očigledno, traženje u relativnoj datoteci sa identifikatorom koji nije podskup skupa obeležja tipa sloga predstavlja dosta maglovit pojam. Ako se traženi slog ne nalazi u lokaciji sa pretpostavljenom adresom, to ne znači da takav slog u datoteci ne postoji. Ova činjenica dolazi do posebnog izražaja pri analizi performansi neuspešnog traženja.

**Primer 11.7.** Tabela iz primera 11.3 bi mogla sadržati i trojku $(71, S_{14}, A_5^3)$, koja se odnosi na slog koji je u međuvremenu izbrisan. Tada bi za neuspešno traženje sloga sa vrednošću ključa $k(S) = 71$ takođe bio potreban jedan pristup datoteci i jedno upoređenje argumenata traženja i ključa. Međutim, ako tabela ne sadrži slog sa vrednošću ključa $k(S) = 71$, tada bi bilo $R_n = 0$.

Traženje se u relativnoj datoteci može vršiti i primenom metode linearnog traženja. No, tada se ona posmatra kao serijska datoteka.

### 4.4 Ažuriranje relativne datoteke

Ažuriranje relativne datoteke se vrši u režimu direktne obrade. Upis novog sloga se vrši na sledeći način. Prvo se novom slogu pridruži vrednost identifikatora (relativna adresa). Zatim se slog upisuje u datoteku, ako u baketu postoji slobodna lokacija. Pre upisa novog sloga u datoteku, eventualno se vrši provera da li slog sa takvom vrednošću ključa postoji. Ta provera se može tražiti da se primeni linearno traženje.

Brisanje sloga se u relativnoj datoteci može vršiti na dva načina. Jedan koristi usluge metode pristupa, a kod drugog se sprovodi pod potpunom kontrolom programa. U oba slučaja, statusno polje mora biti sadržano u opisu sloga. Brisanje je logičko. Jedino u drugom slučaju statusno polje mora biti sadržano u opisu sloga. Brisanje pod kontrolom programa se koristi kada je $b > 1$.

**Primer 11.9.** Ako se u programu pisanom u Cobolu brisanje vrši korišćenjem usluga metode pristupa, tada se nakon postavljanja vrednosti identifikatora u ime_promenljive izdaje naredba:

```
DELETE ime_datoteke RECORD.
```

Nakon toga, relativna metoda pristupa tretira lokaciju kao inicijalno praznu. U slučaju brisanja pod kontrolom programa, nakon izmene sadržaja statusnog polja, izdaje se naredba:

```
REWRITE ime_sloga.
```

Ovako izbrisan slog, metoda pristupa tretira kao aktuelan.

### 4.5 Ocena karakteristika relativne datoteke

Relativna datoteka se odlikuje **efikasnijim traženjem logički narednog sloga** nego serijska datoteka i **manje efikasnim traženjem logički narednog sloga** nego sekvencijalna datoteka. Traženje slučajno odabranog sloga je veoma efikasno. I za traženje logički narednog i za traženje slučajno odabranog sloga, potreban je samo jedan pristup datoteci. Naravno, u oba slučaja je potrebno izvršiti i jedno traženje u tabeli identifikatora.

Tabela identifikatora je, često, dovoljno mala tako da se permanentno nalazi u operativnoj memoriji. Međutim, uvođenjem pojma relativne adrese lokacije kao identifikatora, rešava se jedino problem čvrste povezanosti slogova datoteke sa karakteristikama memorijskog uređaja. Odsustvo logičke veze između vrednosti identifikatora i sadržaja sloga predstavlja prepreku za šire korišćenje relativnih datoteka u praksi.

Saglasno tome, spontano se nameće ideja da se, u svojstvu identifikatora, iskoristi ključ tipa sloga tako da numerička vrednost ključa predstavlja relativnu adresu lokacije u koju treba smestiti slog. Znači, $A_i = k(S_i)$, $i = 1, ..., N$. Nažalost, direktna primena ove ideje često dovodi do izuzetno neefikasnog korišćenja memorijskog prostora, jer se mora predvideti po jedna lokacija za svaku od mogućih vrednosti ključa.

**Primer 11.10.** Da bi se relativna datoteka, u kojoj ključ uzima vrednosti iz skupa prvih 99 prirodnih brojeva, realizovala tako da važi $A_i = k(S_i)$, $i, j \in \{1, ..., N\}$, potrebno je rezervisati 99 lokacija, jer ključ može uzeti svaku vrednost iz skupa $\{1, ..., 99\}$. Ako je $N = 13$, tada koeficijent korišćenja memorijskog prostora iznosi $k \approx 0{,}13$.

**Primer 11.11.** Vrednosti obeležja *MBR* (matični broj građana) su trinaestocifreni brojevi. Srbija ima oko 10 miliona stanovnika. Ako bi se obeležje *MBR* upotrebilo kao identifikator, iskorišćenje memorijskog prostora relativne datoteke bi bilo $10^{-6}$. Tek svaka milionita lokacija bi bila popunjena nekim slogom.

Neka je dat tip sloga $STAN(OZU, KBR, BRS, POS)$, gde je $OZU$ oznaka ulice sa $dom(OZU) = \{1, ..., U\}$, $KBR$ kućni broj sa $dom(KBR) = \{1, ..., B\}$, $BRS$ broj stana sa $dom(BRS) = \{1, ..., S\}$ i $POS$ ostali podaci o stanu. Ključ tipa sloga je $\{OZU, KBR, BRS\}$.

Relativna adresa $A$ lokacije u koju su smešteni podaci o stanu broj $s$, zgrade sa kućnim brojem $b$, u ulici sa oznakom $u$, izračunava se kao:

$$A = s + (b - 1)S + (u - 1)SB$$

a za datoteku se mora rezervisati $SBU$ lokacija.

Neka je u gradu sa $300000$ stanovnika i $100000$ stanova, $U = 2000$, $B = 100$ i $S = 50$, tada je za relativnu datoteku potrebno rezervisati $10^7$ lokacija. Iskorišćenje memorijskog prostora datoteke bi bilo $10^{-2}$.

> [!WARNING]
> Korišćenje ključa kao identifikatora predstavlja, u osnovi, dobru ideju. Međutim, širok opseg mogućih i relativno mali broj aktuelnih vrednosti ključa ograničava direktnu primenu te ideje samo na slučajeve kada aktuelne vrednosti ključa gusto zaposedaju opseg mogućih vrednosti ključa.

Pored navedenih primera, relativna metoda pristupa se može upotrebiti za izgradnju spregnute datoteke. Tu se relativna adresa lokacije logički narednog sloga smešta u polje pokazivača tekućeg sloga. Takođe, relativna metoda pristupa predstavlja osnovu za izgradnju rasutih datoteka sa probabilističkom transformacijom ključa u adresu.

---

## 5. Opšte karakteristike rasutih datoteka sa probabilističkom transformacijom

### 5.1 Odnos opsega mogućih vrednosti i adresnog prostora

Odnos između opsega mogućih vrednosti ključa i veličine adresnog prostora dodeljenog datoteci igra važnu ulogu pri formiranju i korišćenju rasuto organizovanih datoteka. Ključ često uzima vrednosti iz veoma velikog opsega mogućih vrednosti, ograničenog samo brojem pozicija $p$ i brojem dozvoljenih vrednosti $v$ koje svaka pozicija može imati. Broj dozvoljenih vrednosti $v$ odgovara broju slova azbuke upotrebljene za predstavljanje vrednosti ključa.

Veličina $v$ predstavlja osnovu brojnog sistema, što znači da ključ može uzimati jednu od $v^p$ ili jednu od $v^p - 1$ vrednosti.

**Primer 11.12.** Ako ključ ima 6 pozicija, a azbuku predstavljaju decimalne cifre od 0 do 9, ključ može uzeti svaku od $10^6$ različitih vrednosti. Da su za predstavljanje vrednosti ključa upotrebljena slova latinske azbuke, veličina opsega mogućih vrednosti ključa bi iznosila $26^6$.

Veličinu adresnog prostora dodeljenog datoteci je najpogodnije izraziti uz pomoć broja lokacija $Q = Bb$, gde je $B$ broj baketa, a $b$ broj lokacija u baketu. Pošto je broj aktuelnih slogova $N$ u datoteci po pravilu mnogo manji od broja mogućih vrednosti ključa $v^p$, to se pri projektovanju rasuto organizovane datoteke uspostavlja sledeći odnos:

$$v^p \gg Q \geq N$$

### 5.2 Metode probabilističke transformacije vrednosti ključa u adresu

Da bi se prevazišli nedostaci do kojih dovodi deterministička transformacija ključa u adresu, uvodi se probabilistička transformacija ključa u adresu. Postoji veći broj metoda probabilističke transformacije svake od njih zavisi od raspodele vrednosti unutar opsega njegovih mogućih vrednosti. Bez obzira na specifičnosti algoritama, sve ove metode imaju za cilj da izvrše što ravnomerniju transformaciju vrednosti ključa u adresu i kompresiju potrebnog adresnog prostora.

Drugim rečima, zadatak metode transformacije je da za svaku od postojećih (ne i mogućih) vrednosti ključa pretvori u jedinstvenu adresu lokacije u okviru minimalno potrebnog adresnog prostora. Nažalost, ovako idealno postavljeni cilj se u praksi veoma retko postiže.

U opštem slučaju, probabilistička transformacija ključa u adresu realizuje se u **četiri koraka**:

1. Pretvaranje nenumeričke u numeričku vrednost ključa
2. Pretvaranje numeričke vrednosti ključa u pseudoslučajan broj
3. Prevođenje vrednosti pseudoslučajnog broja u opseg dozvoljenih relativnih adresa
4. Pretvaranje relativne u mašinsku adresu

Prva tri koraka najčešće predstavljaju zadatak programa, a četvrti predstavlja zadatak relativne metode pristupa. Prevođenje nenumeričke u numeričku vrednost ključa je potrebno jedino ako su vrednosti ključa nenumeričke. Pretvaranje numeričke vrednosti ključa u pseudoslučajan broj realizuje se primenom neke od formula za generisanje pseudoslučajnih brojeva. Pošto dobijeni pseudoslučajni broj može imati vrednost veću od broja lokacija dodeljenih datoteci, mora se izvršiti njegova korekcija. Korekcija se vrši množenjem pseudoslučajnog broja odgovarajućim faktorom, manjim od jedinice. Rezultat primene ova tri koraka predstavlja relativnu adresu.

Na ovom mestu će biti kratko opisane tri metode probabilističke transformacije ključa u adresu, koje su u praksi stekle veću popularnost.

### 5.3 Metoda ostatka pri deljenju

Značajnu primenu u praksi našla je metoda kod koje se relativna adresa $A$ dobija kao celobrojni ostatak deljenja vrednosti ključa $k(S)$ nekim brojem $m$:

$$A = 1 + k(S)(\text{mod } m)$$

Jedinica se dodaje celobrojnom ostatku deljenja kako bi relativna adresa uzimala vrednosti iz skupa $\{1, 2, ..., B\}$. Saglasno tome, između broja baketa $B$ i broja $m$ važi odnos $m = B$.

To dalje znači da korekcija pseudoslučajnog broja pri primeni ove metode nije potrebna, odnosno da pseudoslučajni broj predstavlja relativnu adresu.

Zadatak svake metode probabilističke transformacije, pa i metode ostatka pri deljenju, je da što ravnomernije, a to znači što slučajnije, pretvori svaku od postojećih vrednosti ključa u adresu. Zbog toga je nepogodno da broj $m$ bude paran broj, jer će se tada za sve neparne vrednosti ključa dobijati neparne relativne adrese, a za parne vrednosti ključa parne adrese. Broj $m$ takođe ne sme predstavljati stepen osnove brojnog sistema, jer će tada relativnu adresu predstavljati cifre najmanje težine ključa, bez obzira na vrednosti ostalih cifara. Najpogodnije je da $m$ predstavlja **prost broj** ili **neparan broj sa relativno velikim prostim činiocima**.

**Primer 11.13.** Ako ključ datoteke uzima vrednosti iz skupa $\{1, ..., 99\}$, a datoteci se dodeli 5 baketa, tada metoda ostatka pri deljenju, slogu sa vrednošću ključa $k(S) = 07$ pridružuje relativnu adresu 3, a slogu sa vrednošću ključa $k(S) = 25$ relativnu adresu 1.

Metoda ostatka pri deljenju je veoma pogodna za primenu u slučajevima kada se vrednosti ključa javljaju u takozvanim paketima. To znači da su pojedini intervali unutar opsega dozvoljenih vrednosti ključa gusto zaposednuti aktuelnim vrednostima ključa, dok se između njih nalaze intervali sa neaktuelnim vrednostima ključa. U tom slučaju, metoda ostatka pri deljenju dodeljuje slogovima sa sukcesivnim vrednostima ključa iz paketa adrese fizički susednih baketa, što rezultuje u ravnomernom zaposedanju baketa.

```mermaid
graph LR
    A[Vrednost ključa k] --> B["Izračunaj k mod m"]
    B --> C["Dodaj 1"]
    C --> D["Relativna adresa A"]
    style A fill:#e1f5fe
    style D fill:#c8e6c9
```

### 5.4 Metoda centralnih cifara kvadrata ključa

Prema ovoj metodi, vrednost ključa se digne na kvadrat, a zatim se uzima onoliki broj centralnih cifara kvadrata vrednosti ključa koliko pozicija treba da sadrži relativna adresa. Ove centralne cifre se, po potrebi, mnoze nekim brojem manjim od jedan, kako bi relativna adresa uzimala vrednost iz minimalnog potrebnog intervala vrednosti, koji odgovara broju baketa dodeljenih datoteci.

Neka je $k(S) \in \{0, 1, ..., v^p - 1\}$. Tada se vrednost ključa može predstaviti u polinomijalnom obliku kao:

$$k(S) = \sum_{i=0}^{p-1} a_i v^i, \quad a_i \in \{0, 1, ..., v - 1\}$$

Relativna adresa $A$ uzima vrednosti iz skupa $\{1, ..., B\}$, gde je $B = kv^n$ broj baketa, $n = \lceil \log_v B \rceil$ i $1 \leq n \leq p$. Kvadrat vrednosti ključa se može predstaviti u polinomijalnom obliku kao:

$$(k(S))^2 = \sum_{i=0}^{2p-1} c_i v^i, \quad a_i \in \{0, 1, ..., v - 1\}$$

Iz niza $(c_{2n-1}, c_{2n-2}, ..., c_1, c_0)$ izdvaja se niz:

$$(c_{t+n-1}, c_{t+n-2}, ..., c_{t+1}, c_t)$$

gde je $t = \lfloor p - n/2 \rfloor$. Elementi niza predstavljaju cifre pseudoslučajnog broja $T$:

$$T = \sum_{i=0}^{n-1} c_{t+i} v^i$$

Relativna adresa $A$ se izračunava na sledeći način:

$$B = \left\lceil \frac{N}{bq} \right\rceil$$

$$(11.3) \quad A = \lfloor rQ/v^n \rfloor + 1$$

gde je $r$ dobijena iz pseudokoda algoritma.

**Primer 11.14.** U slučaju datoteke iz primera 11.13, $B = 5$, a $v = 10$. Tada je $n = 1$ i $B/v^n = 0{,}5$. Pošto ključ uzima vrednosti iz skupa $\{1, ..., 99\}$, to je $p = 2$, te je $t = 1$.

- Za $k(S) = 07$: dobija se $(k(S))^2 = 49$, te je $T = 4$ i $A = 3$.
- Za $k(S) = 25$: dobija se $(k(S))^2 = 625$, te je $T = 2$ i $A = 2$.

**Algoritam transformacije metodom srednjih cifara kvadrata:**

```
PROCES transformacija(U(k(S), p, Q), I(r), UI())
(* 
U  - Q je broj baketa rasute datoteke, p je maksimalni broj cifara vrednosti ključa k(S).
I  - r je relativna adresa matičnog baketa
*)
POČETAK PROCESA transformacija
  POSTAVI n ← ⌈log_v Q⌉        (*broj pozicija relativne adrese*)
  POSTAVI t ← ⌊p - n/2⌋
  POSTAVI k ← (k(S))²
  POSTAVI r ← ⌊k/v^t⌋ mod v^n
  POSTAVI r ← ⌊rQ/v^n⌋ + 1
KRAJ PROCESA transformacija
```

### 5.5 Metoda preklapanja

Metoda preklapanja je pogodna za primenu kada je broj pozicija $p$ ključa mnogo veći od broja pozicija $n$ relativne adrese u datoteci. Ime je dobila zbog činjenice da se, pri njenoj primeni, cifre ključa premeštaju kao pri savijanju (preklapanju) hartije. Preklapanje se izvodi po osama koje zdesna u levo određuje broj pozicija $n$ relativne adrese, a prema skici na slici 11.5.

Na taj način se dobija $\lceil p/n \rceil$ brojeva po modulu $v^n$ i njihovim eventualnim množenjem faktorom $k$ ($\leq 1$) u cilju sažimanja, dobija se relativna adresa lokacije, gde je $k = B/v^n$.

Neka je $k(S)$ predstavljeno putem formule (11.1). Pseudoslučajni broj $T$ se u slučaju metode preklapanja izračunava po formuli:

$$(11.4) \quad T = \left(\sum_{k=0}^{q} \sum_{i=0}^{n-1} c_r v^i + \sum_{k=1}^{q} \sum_{i=0}^{n-1} c_s v^i \right)(\text{mod } v^n)$$

gde je $q = \lfloor p/2n \rfloor$, $r = 2kn + i$, $s = 2kn - i - 1$,

$$c_r = \begin{cases} c_r, & \text{za } r < p \\ 0, & \text{za } r \geq p \end{cases} \quad \text{i} \quad c_s = \begin{cases} c_s, & \text{za } s < p \\ 0, & \text{za } s \geq p \end{cases}$$

Relativna adresa $A$ se i u slučaju metode preklapanja izračunava putem formule (11.3).

**Primer 11.15.** Neka je $k(S) = 768013295$ i $n = 3$. Na slici 11.6 prikazan je efekat primene formule (11.4) za dobijanje pseudoslučajnog broja $T = 373$.

---

## 6. Sinonimi i prekoračioci

### 6.1 Pojam sinonima

Ozbiljan nedostatak svih metoda probabilističke transformacije ključa u adresu predstavlja pojava koja se naziva i **kolizijom ključeva**, a nastaje kao posledica činjenice da dve različite vrednosti ključa $k(S_i)$ i $k(S_j)$ mogu transformacijom dobiti istu relativnu adresu, jer je $h(k(k(S_i))) = h(k(S_j))$.

Metoda probabilističke transformacije vrednosti ključa u adresu deli skup slogova datoteke na disjunktne podskupove. Svim slogovima jednog podskupa dodeljena je adresa istog baketa. Slogovi jednog podskupa predstavljaju jedan **skup sinonima**. Broj ovih podskupova u jednoj rasutoj datoteci, jednak je broju baketa $B$. Pri tome, nekim baketima mogu biti pridruženi i prazni podskupovi skupa slogova datoteke.

**Primer 11.16.** U tabeli na slici 11.7 prikazani su rezultati dodeljivanja relativnih adresa baketa skupu slogova serijske datoteke metodom ostatka pri deljenju. Broj baketa dodeljenih datoteci iznosi $B = 5$. Saglasno tabeli, svakom baketu, osim baketu sa relativnom adresom $A = 2$, je dodeljen barem jedan slog. Skup sinonima baketa sa relativnom adresom $A = 5$ predstavlja skup $\{S_1, S_5, S_6, S_7, S_{12}\}$.

| $S_i$ | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|----------|----------|----------|----------|
| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
| $A$ | 5 | 3 | 4 | 1 | 5 | 5 | 5 | 4 | 4 | 3 | 4 | 5 | 1 |

### 6.2 Pojam prekoračioca

Svakom slogu se transformacijom pridružuje adresa jednog baketa. Taj baket će se u daljem tekstu nazivati **matičnim**. Slogovi, smešteni u svoj matični baket, nazivaju se **primarnim**. Pošto se baket popuni, svaki naredni slog sinonim smešta se u neku drugu lokaciju. Takvi slogovi se nazivaju **prekoračiocima**.

Pojava prekoračilaca je nepoželjna, jer zahteva pronalaženje slobodne lokacije za smeštaj tog sloga i dovodi do produženja vremena pristupa pri kasnijem traženju tog sloga. Broj prekoračilaca će biti to manji što su slogovi ravnomernije raspodeljeni po baketima.

Verovatnoća pojave sinonima zavisi od raspodele vrednosti ključa unutar opsega dozvoljenih vrednosti, od odabrane metode transformacije i faktora popunjenosti memorijskog prostora. Od raspodele vrednosti ključa zavisi koja je metoda transformacije, u posmatranom slučaju, biti najpogodnija, tj. dati najravnomerniju raspodelu slogova po baketima.

### 6.3 Faktor popunjenosti

Intuitivno se može naslutiti da će, bez obzira na metodu transformacije, broj sinonima biti to manji što je manji odnos između broja slogova $N$ i broja lokacija $Q = Bb$ dodeljenih datoteci. Odnos:

$$q = N / Q$$

između ove dve veličine naziva se **faktorom popunjenosti**. Pri tome je $0 < q \leq 1$.

Izbor faktora popunjenosti $q$ ostvaruje veliki uticaj na karakteristike rasuto organizovane datoteke:

- Ako je $q$ malo, verovatnoća pojave više slogova u jednom skupu sinonima je takođe mala, ali je malo i iskorišćenje memorijskog prostora.
- Ako je $q$ veliko (blizu jedinice), iskorišćenje memorijskog prostora je dobro, ali je velika i verovatnoća pojave sinonima.

> [!IMPORTANT]
> U praksi se bira $q \leq 0{,}8$.

**Primer 11.17.** U graničnom slučaju, kada je $Q = v^p$, za faktor baketiranja $b = 1$, metoda ostatka pri deljenju predstavlja injektivnu funkciju. Medutim, to je slučaj trivijalne transformacije kod koje vrednost ključa predstavlja relativnu adresu.

**Primer 11.18.** Ako se pretpostavi da je, u slučaju rasute datoteke iz primera 11.16, $b = 3$, tada je $Q = 15$ i $q \approx 0{,}87$. Za $q \approx 0{,}62$, pri istom faktoru baketiranja se dobija $B = 7$. U tabeli na slici 11.8 su prikazani rezultati transformacije vrednosti ključa u adresu metodom ostatka pri deljenju za $B = 7$.

| $S_i$ | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|----------|----------|----------|----------|
| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
| $A$ | 7 | 1 | 4 | 2 | 6 | 2 | 2 | 2 | 3 | 7 | 7 | 1 | 5 |

Upoređivanje sadržaja tabela na slikama 11.7 i 11.8 ukazuje da je raspodela slogova po baketima ravnomernija pri manjem faktoru popunjenosti. Naravno, ovaj primer ukazuje samo na to kakvo ponašanje slučajne veličine $\bar{S}$, gde je $\bar{S}$ broj sinonima pridruženih transformacijom jednom baketu datoteke, treba očekivati pri smanjenju faktora popunjenosti $q$.

### 6.4 Faktor baketiranja

Nužnost ekonomičnog korišćenja memorijskog prostora dovodi do kompromisnih opredeljenja pri izboru faktora popunjenosti $q$, što rezultuje i u pojavi sinonima i u pojavi slogova prekoračilaca. Očekivani broj prekoračilaca po jednom baketu, pri datom faktoru popunjenosti $q$, zavisi od veličine faktora baketiranja $b$.

Ako se pretpostavi da je verovatnoća dodele svake od raspoloživih adresa svakom slogu datoteke ista i da to dodeljivanje adresa predstavlja međusobno nezavisne događaje, tada verovatnoća pojave prekoračilaca opada sa porastom faktora baketiranja $b$. U graničnom slučaju, kada je $b \geq N$, broj prekoračilaca je nula. Međutim, tada se gubi mogućnost direktnog pristupa slogovima, jer se svi nalaze u jednom baketu. Za $b < N$, verovatnoća pojave prekoračilaca je različita od nule, ali sa smanjenjem faktora baketiranja raste preciznost određivanja verovatne adrese lokacije slučajno odabranog sloga pri traženju.

Veliki faktori baketiranja dovode do dugih vremena razmene podataka između operativne i eksterne memorije, a takođe zahtevaju rezervisanje velikog bafera u operativnoj memoriji. U praksi se retko koriste veći baket faktori od 10, te pojava prekoračilaca predstavlja neminovnost.

### 6.5 Očekivani broj sinonima i prekoračilaca

Transformacija vrednosti ključa u adresu predstavlja seriju od $N$ nezavisnih eksperimenata. Verovatnoća da se svakom od $N$ slogova datoteke dodeli jedna od $B$ adresa baketa je, u svakom eksperimentu, ista. Metoda transformacije deli skup od $N$ slogova na $B$ disjunktnih podskupova. Slogovi u istom podskupu se nazivaju sinonimima. Broj slogova u jednom podskupu predstavlja slučajnu veličinu sa binomnom raspodelom, te verovatnoća $P(i)$ da neki podskup sadrži $i$ ($= \bar{S}$) slogova iznosi:

$$P(i) = \binom{N}{i} \left(\frac{1}{B}\right)^i \left(1 - \frac{1}{B}\right)^{N-i}$$

Za velike vrednosti $N$ i $B$, koje su tipične za realne datoteke, verovatnoća $1/B$ postaje veoma mala (teži nuli), te za slučaj konstantnog odnosa $N/B$, binomna raspodela prelazi u **Poissonovu**, a $P(i)$ postaje:

$$(11.5) \quad P(i) = \frac{(qb)^i}{i!} e^{-qb}$$

gde je $qb = N/B = c^{lo}$.

Broj slogova $\bar{S}$ u jednom skupu sinonima predstavlja slučajnu veličinu, koja uzima vrednosti iz skupa $\{0, 1, ..., N\}$. Očekivana vrednost $\bar{S}$ broja slogova u jednom skupu iznosi:

$$(11.6) \quad \bar{S} = \sum_{i=0}^{N} iP(i)$$

Zamenom (11.5) u (11.6) dobija se:

$$(11.7) \quad \bar{S} = qb$$

Broj prekoračilaca iz jednog baketa, kao slučajna veličina, uzima vrednosti iz skupa $\{0, 1, ..., N - b\}$. Pod pretpostavkom da se u bakete smeštaju samo matični slogovi, očekivani broj prekoračilaca $\bar{L}$ iz jednog baketa dat je matematičkim očekivanjem:

$$(11.8) \quad \bar{L} = \sum_{i=b+1}^{N} (i - b) P(i)$$

Pošto brojevi prekoračilaca iz svakog od $B$ baketa predstavljaju nezavisne slučajne veličine, očekivani broj prekoračilaca iz svih $B$ baketa datoteke iznosi:

$$(11.9) \quad \overline{LB} = B \sum_{i=b+1}^{N} (i - b) P(i)$$

a očekivani broj prekoračilaca po jednom od $N$ slogova iznosi:

$$\frac{\overline{LB}}{N} = \frac{1}{qb} \sum_{i=b+1}^{N} (i - b) P(i)$$

> [!TIP]
> Na slici 11.9 nacrtane su krive $\overline{LB}/N = f(q)$ za razne vrednosti $b$. Posmatranjem ovih krivih može se zaključiti da očekivani broj prekoračilaca raste sa porastom $q$ i opada sa porastom $b$.

**Primer 11.19.** Za $q = 0{,}87$ i $b = 3$, očekivani broj sinonima po jednom baketu datoteke sa velikim $N$ i $B$ iznosi $\bar{S} = 2{,}61$. Za $N = 10000$, ukupni očekivani broj prekoračilaca iz datoteke iznosi, saglasno slici 11.9, $\overline{LB} = 1800$.

Za male datoteke, sa nekoliko destina slogova, krive sa slike 11.9 se mogu koristiti samo za približne procene. U slučaju datoteke sa $N = 13$, $B = 5$ i $b = 3$, važi $q = 0{,}87$, te se sa slike 11.9 dobija $\overline{LB} \approx 2{,}3$.

---

## 7. Postupci za smeštaj prekoračilaca

Za rešavanje problema smeštanja prekoračilaca postoje dva osnovna postupka:

1. **U slučaju prvog**, datoteka poseduje jedinstven adresni prostor. Prekoračioci se smeštaju u neku od slobodnih lokacija unutar tog jedinstvenog adresnog prostora.
2. **Kod drugog postupka**, datoteka poseduje dve zone - **primarnu** i **zonu prekoračenja**. Prekoračioci se smeštaju u neku od slobodnih lokacija unutar zone prekoračenja.

Svaki od ovih osnovnih postupaka se deli na nekoliko varijanti, zavisno od metode određivanja adrese baketa u kojem će se tražiti slobodna lokacija za smeštaj prekoračioca i zavisno od činjenice da li se svi sinonimi jednog skupa međusobno sprežu ili ne.

**U rasute datoteke sa jedinstvenim adresnim prostorom spadaju:**

- Datoteka sa linearnim traženjem lokacije za smeštaj prekoračilaca
- Datoteka sa slučajnim traženjem lokacije za smeštaj prekoračilaca
- Datoteka sa sprezanjem prekoračilaca (u jedinstvenom adresnom prostoru)

**U rasute datoteke sa zonom prekoračenja spadaju:**

- Datoteka sa sprezanjem prekoračilaca u zoni prekoračenja
- Datoteka sa serijskom zonom prekoračenja

### 7.1 Opšte napomene o projektovanju i formiranju

Pri projektovanju rasute datoteke sa probabilističkom transformacijom vrednosti ključa u adresu utvrđuje se:

- Faktor popunjenosti memorijskog prostora $q$
- Faktor baketiranja $b$
- Metoda transformacije vrednosti ključa u adresu
- Postupak za smeštanje prekoračilaca

Ova opredeljenja donose se s obzirom na raspodelu vrednosti ključa unutar opsega mogućih vrednosti, veličinu sloga, obim i karakter ažuriranja datoteke, zadati srednji broj pristupa datoteci pri uspešnom i neuspešnom traženju.

Na osnovu utvrđenih vrednosti za $q$ i $b$, određuje se broj baketa putem formule:

$$B = \left\lceil \frac{N}{bq} \right\rceil$$

Mada sistemi za upravljanje bazama podataka po pravilu poseduju metodu pristupa za rasute datoteke, softver za upravljanje rasutim datotekama je posebno retko dostupan. Zbog toga se aktivnosti formiranja rasuto organizovane datoteke realizuju delom u okviru aplikativnog programa, a delom uz pomoć relativne metode pristupa. Transformacija vrednosti ključa u adresu, smeštanje prekoračilaca, formiranje baketa od više slogova i izdvajanje slogova iz baketa predstavljaju zadatke aplikativnog programa. Upis i čitanje baketa iz datoteke predstavljaju zadatke relativne metode pristupa. Čitav postupak formiranja rasute datoteke se odvija u režimu direktne obrade.

Pošto se rasuta datoteka realizuje kao relativna, preporučljivo je inicijalno formirati praznu datoteku. Pri tome se mogu, po potrebi, popuniti specijalnim sadržajima statusna polja lokacija, polja ključa i polja pokazivača. Razlog za formiranje prazne datoteke predstavlja i činjenica da se relativna datoteka prvi put često može otvoriti samo kao izlazna. Ukoliko datoteka sadrži primarnu i zonu prekoračenja, ove dve zone se mogu realizovati kao dve relativne datoteke.

Kod datoteka sa rasutom organizacijom se javlja potreba prepoznavanja slobodnih lokacija i njihovog sprezanja, ili putem indeksa slobodnih lokacija ili putem sadržaja statusnog polja ili upisom specijalnih znakova u lokaciju. U svojstvu tih specijalnih znakova će se u daljem tekstu koristiti zvezdica () u polju ključa.

### 7.2 Opšte napomene o traženju u rasutim datotekama sa probabilističkom transformacijom

Traženje logički narednog i traženje slučajno odabranog sloga se, u rasutim datotekama, vrši metodom transformacije argumenta u adresu baketa. Ako se traženi slog ne nađe u matičnom baketu, a uslovi za nastavak traženja postoje, traženje se nastavlja ili linearnom metodom ili ponovnom transformacijom ili praćenjem pokazivača.

Generalno, uslovi za nastavak traženja postoje, ako matični baket ima prekoračilaca. Linearna metoda se primenjuje kod datoteka sa linearnim traženjem i datoteka sa serijskom zonom prekoračenja. Ponovna transformacija se koristi kod datoteka sa slučajnim traženjem. Praćenje pokazivača se koristi u datotekama sa sprezanjem prekoračilaca.

Pri datom faktoru popunjenosti i datom faktoru baketiranja, efikasnost traženja zavisi od primenjenog postupka za smeštaj prekoračilaca.

Očekivani broj pristupa rasutoj datoteci sa velikim brojem slogova $N$ i brojem baketa $B$, bez obzira na postupak za smeštaj prekoračilaca, i pri uspešnom i pri neuspešnom traženju ne zavisi od broja slogova datoteke $N$, već samo od parametara $q$ i $b$. Naime, ako se traženi slog nalazi u matičnom baketu, ili matični baket nema prekoračilaca, tada je broj pristupa $R = 1$. Traženje se nastavlja jedino ako matični baket ima prekoračilaca. Očekivani broj prekoračilaca ne zavisi od broja slogova $N$. Naime, pošto je:

$$\sum_{i=0}^{N} P(i) = 1 \quad \text{i} \quad \sum_{i=0}^{N} iP(i) = qb$$

izraz (11.8) se jednostavnim transformacijama pretvara u izraz:

$$(11.10) \quad \bar{L} = b(q-1) + \sum_{i=0}^{b} (b-i)P(i)$$

koji očigledno ne zavisi od $N$.

Sprovedena analiza ukazuje da se eksploatacione karakteristike realnih datoteka sa velikim brojem slogova mogu orijentaciono procenjivati posmatranjem datoteka sa malim brojem slogova, ali sa istim faktorom popunjenosti, istim faktorom baketiranja, a uz pretpostavku da su raspodele aktuelnih vrednosti ključa u oba slučaja iste.

---

## 8. Očekivani broj pristupa datoteci

Za izračunavanje očekivanog broja pristupa $\overline{R_u}$ pri uspešnom traženju u rasutoj datoteci sa malim brojem slogova, može se koristiti formula:

$$(11.11) \quad \overline{R_u} = \frac{1}{N} \sum_{i=1}^{N} R_i^u$$

gde je $R_i^u$ broj pristupa potreban za pronalaženje $i$-tog sloga datoteke. Pretpostavka je da je verovatnoća traženja svakog sloga datoteke ista i da je poznata tačna fizička struktura datoteke.

Za izračunavanje očekivanog broja pristupa $\overline{R_n}$ pri neuspešnom traženju u rasutoj datoteci sa linearnim traženjem, sprezanjem u primarnoj zoni, sprezanjem u zoni prekoračenja i datoteci sa serijskom zonom prekoračenja, može se koristiti formula:

$$(11.12) \quad \overline{R_n} = \frac{1}{B} \sum_{i=1}^{B} R_i^n$$

gde je $R_i^n$ broj pristupa potreban da se utvrdi da slog, koji metoda transformacije pridružuje $i$-tom baketu, u datoteci ne postoji, a $B$ broj baketa rasute datoteke.

Za izračunavanje očekivanog broja pristupa $\overline{R_n}$ pri neuspešnom traženju u rasutoj datoteci sa slučajnim traženjem lokacije za smeštaj prekoračioca, mora se koristiti formula:

$$(11.13) \quad \overline{R_n} = \frac{1}{T} \sum_{i=1}^{T} R_i^n$$

gde je $T = v^p - 1 - N$ broj neaktuelnih vrednosti ključa, a $R_i^n$ broj pristupa potreban da se utvrdi da slog sa $i$-tom neaktuelnom vrednošću ključa u datoteci ne postoji.

Dok je za male vrednosti $N$ (reda 10) primena formule (11.11) i (11.12) jednostavna, primena formule (11.13) postaje teško izvodljiv zadatak već za $v^p \geq 100$ i $v^p \gg N$.

---

## 9. Rasute datoteke sa linearnim traženjem

### 9.1 Formiranje rasute datoteke sa linearnim traženjem

Za izgradnju fizičke strukture rasute datoteke sa linearnim traženjem lokacija za smeštaj prekoračilaca, koristi se sledeći postupak dodele adresa lokacija slogovima. Nakon transformacije vrednosti ključa u adresu, slog se smešta u matični baket, ako u njemu postoji slobodna lokacija. Inače, slog se smešta u prvi baket sa slobodnom lokacijom iza svog matičnog baketa. Traženje prve slobodne lokacije može zahtevati veći broj pristupa sukcesivnim baketima.

Ako se redni broj baketa u kojem se traži slobodna lokacija označi sa $n$ ($n = 1, ..., B - 1$), pri čemu $n$ predstavlja redni broj u odnosu na matični baket kao početak, tada se relativna adresa $A_n$ tog baketa izračunava kao:

$$(11.14) \quad A_n = 1 + A_{n-1} (\text{mod } B)$$

gde je $A_0 = h(k(S))$ adresa matičnog baketa.

Treba zapaziti da pri primeni metode linearnog traženja slog može postati prekoračilac i ako su prekoračioci iz drugih baketa popunili njegov matični baket.

**Primer 11.20.** Korišćenjem tabele sa slike 11.7, dobijena je rasuta datoteka sa linearnim traženjem, prikazana na slici 11.10. Pri tome je $N = 13$, $B = 5$, $b = 3$ i $q = 0{,}87$. Zvezdica u polju ključa ukazuje da je lokacija nezauzeta.

Slogovi sa vrednostima ključa $k(S_7) = 64$ i $k(S_{11}) = 13$, kao prekoračioci iz baketa sa relativnim adresama $A_r = 5$ i $A_r = 4$ respektivno, zauzeli su lokacije u baketu sa relativnom adresom $A_r = 1$. Na taj način je i slog sa vrednošću ključa $k(S_{13}) = 25$, koji pripada baketu sa relativnom adresom $A_r = 1$, postao prekoračilac.

| Baket | Lokacija 1 | Lokacija 2 | Lokacija 3 |
|-------|-----------|-----------|-----------|
| 1 | 15, $p(S_4)$ | 64, $p(S_7)$ | 13, $p(S_{11})$ |
| 2 | 49, $p(S_{12})$ | 25, $p(S_{13})$ | $*$ |
| 3 | 07, $p(S_2)$ | 27, $p(S_{10})$ | $*$ |
| 4 | 03, $p(S_3)$ | 43, $p(S_8)$ | 23, $p(S_9)$ |
| 5 | 34, $p(S_1)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |

Na slici 11.11 prikazan je pseudokod algoritma formiranja rasute datoteke sa linearnim traženjem. Ovaj algoritam poziva algoritam procesa formiranja prazne datoteke (slika 11.12) i algoritam procesa traženja (slika 11.15). Formiranjem prazne datoteke obezbeđuje se, upisom specijalne oznake u polje ključa svake lokacije, informacija o inicijalno slobodnim lokacijama. Upis slogova se vrši nakon neuspešnog traženja, da bi se u datoteci sprečila pojava slogova sa istim vrednostima ključa.

**Postupak formiranja u dva prolaza:** Da bi se barem pri formiranju izbegao efekat pojave prekoračilaca zbog zauzeća matičnog baketa od strane prekoračilaca iz drugih baketa, neki put se primenjuje takozvani postupak formiranja u dva prolaza:

- **U prvom prolazu**, slogovi se učitavaju iz ulazne datoteke $D_u$ i upisuju u rasuto ulazno-izlaznu datoteku $D_r$, ako postoji slobodna lokacija u matičnom baketu, inače se smeštaju u izlaznu datoteku prekoračilaca $D_p$.
- **U drugom prolazu**, prekoračioci iz datoteke $D_p$ prenose se u datoteku $D_r$ i smeštaju u prvu slobodnu lokaciju po formuli (11.14).

**Primer 11.21.** Ako bi se datoteka sa slike 11.10 formirala postupkom sa dva prolaza, njena dva prva baketa bi izgledala kao na slici 11.14. Slog sa vrednošću ključa $k(S_{13}) = 25$ bi bio smešten u matični baket.

### 9.2 Traženje u rasutoj datoteci sa linearnim traženjem

U rasutoj datoteci sa linearnim traženjem, traženje logički narednog i traženje slučajno odabranog sloga vrši se metodom transformacije argumenta u adresu. Na osnovu rezultata transformacije, pristupa se matičnom baketu. Ako se traženi slog nalazi u matičnom baketu, traženje se završava uspešno. Ako matični baket ne sadrži traženi slog, a sadrži slobodnu lokaciju, traženje se završava neuspešno. Inače se traženje nastavlja linearnom metodom tako, što se adresa baketa u kojem će se nastaviti traženje, određuje putem formule (11.14). Ponovo, traženje se završava uspešno kada se naiđe na slog sa traženom vrednošću ključa. Traženje se završava kao neuspešno kada se naiđe na baket sa slobodnom lokacijom, ili kada se, saglasno cirkularnom postupku određivanja adresa baketa, ponovo dođe do matičnog baketa.

**Primer 11.22.** Neka je $a = 49$, a traženje se vrši u datoteci prikazanoj na slici 11.10. Relativna adresa matičnog baketa je $A_0 = 5$, $m = 3$, a $l = 5$, te broj pristupa potreban za pronalaženje sloga sa vrednošću ključa $k(S_{12}) = 49$ iznosi $R_u = 3$.

### 9.3 Analiza broja pristupa pri linearnom traženju

Broj pristupa $R_u$ pri uspešnom traženju ili logički narednog ili slučajno odabranog sloga uzima celobrojne vrednosti iz intervala $[1, 1 + \lceil 1/b \rceil]$, odnosno:

$$(11.15) \quad 1 \leq R_u \leq 1 + \lceil 1/b \rceil$$

gde je $R_u = 1$ za $m < b$ i $1 \leq R_u \leq 1 + \lceil l/b \rceil$ za $m = b$.

Pri neuspešnom traženju, broj pristupa $R_n$ datoteci dat je sledećom formulom:

$$(11.16) \quad R_n = \begin{cases} 1 & \text{za } m < b \\ 1 + \lceil l/b \rceil & \text{za } m = b \end{cases}$$

Pri vrednostima faktora popunjenosti $q$ bliskim jedinici može doći do smeštanja nekog od prekoračilaca u baket koji prethodi s obzirom na smer linearnog traženja, njegovom matičnom baketu. Tada maksimalni broj pristupa pri traženju jednog sloga teži vrednosti $R = B$.

U datoteci sa malim brojem slogova, očekivani broj pristupa pri uspešnom traženju može se izračunavati primenom formula (11.11) i (11.12), respektivno.

**Primer 11.23.** Primenom formula (11.11) i (11.12), u slučaju datoteke sa slike 11.10, dobija se $\overline{R_u} \approx 1{,}46$ i $\overline{R_n} = 2{,}2$.

Za ocenu očekivanih eksploatacionih karakteristika datoteka sa velikim brojem slogova i baketa koriste se krive na slikama 11.16 i 11.17.

Na slici 11.16 prikazane su krive $\overline{R_u} = f(q)$ za razne vrednosti baketa faktora $b$. Krive su nacrtane na osnovu tabela date u [Kn]. Krive pokazuju da srednji broj pristupa pri uspešnom traženju naglo raste kada se faktor popunjenosti $q$ približava jedinici. Međutim, slika 11.16 pokazuje da je za $q \leq 0{,}7$ i $b \geq 2$, $\overline{R_u} < 2$. Pri manjim vrednostima faktora popunjenosti, ne samo da je mala verovatnoća pojave prekoračilaca, već je velika i verovatnoća da će prekoračilac biti smešten u prvi naredni baket, tako da je uspešno traženje efikasno. Slika 11.16 takođe ukazuje da $\overline{R_u}$ opada sa porastom $b$.

Broj pristupa datoteci pri neuspešnom traženju još brže raste sa porastom faktora popunjenosti $q$, jer indikacija o nepostojanju traženog sloga predstavlja nailazak na praznu lokaciju. Što je faktor popunjenosti veći, to je potreban veći broj pristupa da bi se pronašla slobodna lokacija. U graničnom slučaju, za $q = 1$, neuspešno traženje se završava ponovnim dolaskom do matičnog baketa, te je $R_n^{max} = B$. Na slici 11.17 prikazana je kriva $\overline{R_n} = f(q)$ za $b = 1$.

### 9.4 Ažuriranje rasute datoteke sa linearnim traženjem

Upis novog sloga u rasutu datoteku sa linearnim traženjem vrši se u lokaciju na kojoj se zaustavilo neuspešno traženje. Broj pristupa potreban za upis jednog novog sloga iznosi:

$$R_i = R_n + 1$$

gde je $R_n$ dato formulom (11.15).

Brisanje sloga iz datoteke sa linearnim traženjem može biti ili logičko ili fizičko. Kod logičkog brisanja potrebno je koristiti tri vrednosti statusne oznake: jednu, recimo $0$, za inicijalno slobodnu lokaciju, drugu, recimo $1$, za lokaciju koja sadrži aktuelni slog i treću, recimo $9$, za lokaciju koja sadrži neaktuelni slog.

Na taj način, nailaskom na lokaciju sa neaktuelnim sadržajem, traženje se ne prekida. Međutim, logičko brisanje dovodi do degradacije performansi traženja, jer vremenom cela datoteka prelazi u kontinualan niz zauzetih i oslobođenih lokacija, tako da se broj pristupa pri neuspešnom traženju približava svojoj maksimalnoj vrednosti $R_n^{max} = B$, a raste i broj pristupa pri uspešnom traženju. Opisani problemi logičkog brisanja rešavaju se povremenom reorganizacijom datoteke. Pri reorganizaciji se iz datoteke eliminišu logički izbrisani slogovi.

Broj pristupa potreban za logičko brisanje jednog sloga iznosi:

$$R_d = R_u + 1$$

gde je $R_u$ dato formulom (11.15).

**Problem fizičkog brisanja:** Fizičko brisanje se realizuje tako što se u lokaciju sloga koji se briše prenosi sadržaj prve naredne lokacije sa većom adresom. Iz lokacije sa većom u lokaciju sa manjom adresom, pomeraju se slogovi koji se nalaze između lokacije čiji sadržaj se briše, i prve prazne lokacije. U poslednju lokaciju posmatranog niza sukcesivno zauzetih lokacija upisuje se niz specijalnih znakova koji ukazuju da je lokacija inicijalno prazna.

Pri tom pomeranju se mora voditi računa da se slog ne prenese u baket iza svog matičnog baketa (s obzirom na smer traženja), jer se tada više neće moći pronaći (sem u slučaju da je $q = 1$). Ovo pomeranje predstavlja svojevrsnu dinamičku reorganizaciju datoteke, jer dovodi prekoračioca bliže svom matičnom baketu i oslobađa memorijski prostor.

Na slici 11.18 prikazan je pseudokod algoritma ažuriranja rasute datoteke sa linearnim traženjem. Ovaj algoritam poziva algoritme procesa traženja i brisanja, prikazane redom na slikama 11.15 i 11.19, a proces brisanja poziva potprocese provere kandidata (za selektivno pomeranje) sa slike 11.20.

**Primer 11.24.** Na slici 11.21 prikazana je fizička struktura rasute datoteke sa slike 11.10, nakon brisanja sloga sa vrednošću ključa $k(S_9) = 23$. Brisanje je izvršeno fizički.

### 9.5 Analiza karakteristika datoteke sa linearnim traženjem

Iskustva stečena primenom rasutih datoteka sa linearnim traženjem lokacije za smeštaj prekoračilaca pokazuju da je postupak pogodan za datoteke sa faktorom popunjenosti $q < 0{,}7$. Pri većim faktorima popunjenosti dolazi do čestih dugotrajnih traženja. Razlog nastanka ove pojave leži u fenomenu stvaranja dugih nizova zauzetih lokacija.

**Primer 11.25.** Na slici 11.22 je prikazana mala datoteka sa $N = 7$ slogova, $B = 13$ baketa i faktorom baketiranja $b = 1$. Naredni, osmi slog će biti upisan u jedan od šest slobodnih baketa. Međutim, verovatnoća da će novi slog biti smešten u baket sa adresom $A_{12}$, ako je $A_0 \leq h(k(S)) \leq A_{13}$, samo ako je $h(k(S)) = A_{13}$. Ako je verovatnoća transformacije svake od 13 adresa ista, tada je verovatnoća smeštanja novog sloga u baket sa adresom $A_{12}$ četiri puta veća od verovatnoće njegovog smeštanja u baket sa adresom $A_{13}$. Zbog toga se dva niza spoje, što je još gore situacija, desilo kada bi novi slog bio smešten u baket sa adresom $A_8$.

Fenomen stvaranja dugih nizova zauzetih lokacija naziva se **nagomilavanjem** (clustering, pile-up). Postoje dva osnovna postupka zaštite od efekta nagomilavanja. Prvi je da se koriste faktori popunjenosti $q < 0{,}7$.

**Primer 11.26.** Na slici 11.23 prikazana je rasuta datoteka sa linearnim traženjem formirana korišćenjem tabele sa slike 11.8. Za $N = 13$, $B = 7$ i $b = 3$, dobija se $q \approx 0{,}62$. Primenom formule (11.11), dobija se $\overline{R_u} \approx 1{,}08$, a na osnovu formule (11.12), dobija se $\overline{R_n} \approx 1{,}43$.

Postoje tri osnovna razloga za nagli rast broja pristupa pri uspešnom, a naročito pri neuspešnom traženju, u slučajevima kada $q$ raste preko vrednosti $0{,}7$. To su:

- Traženje se vrši i u baketima koji ne sadrže slogove iz skupa sinonima traženog sloga.
- Neuspešno traženje se zaustavlja tek po dolasku do slobodne lokacije.
- Prekoračioci iz jednih baketa izazivaju pojavu prekoračilaca iz drugih baketa.

Ova dva nedostatka izbegavaju se izgradnjom rasutih datoteka sa sprezanjem u primarnoj zoni, a sva tri izgradnjom rasutih datoteka sa sprezanjem u zoni prekoračenja.

---

## 10. Rasute datoteke sa slučajnim traženjem

U rasutim datotekama sa slučajnim traženjem lokacije za smeštaj prekoračilaca, postupak traženja slobodne lokacije je zasnovan na stvaranju zavisnosti između koraka traženja $k$ i vrednosti ključa sloga. Sada se koriste dve funkcije za transformaciju vrednosti ključa u adresu: $h_1(k(S))$ i $h_2(k(S))$.

Dovođenjem u zavisnost veličine $k$ od vrednosti ključa putem transformacije $h_2$, obezbeđuje se da svaki prekoračilac iz istog baketa prelazi drugi put pri traženju slobodne lokacije. Na taj način se izbegava nagomilavanje.

Adresa $n$-tog baketa, u odnosu na matični, u kojem se traži slobodna lokacija, izračunava se po formuli:

$$(11.17) \quad A_n = \begin{cases} A_{n-1} + h_2(k(S)) & \text{za } A_{n-1} + h_2(k(S)) \leq B \\ A_{n-1} + h_2(k(S)) - B & \text{za } A_{n-1} + h_2(k(S)) > B \end{cases}$$

gde je $A_0 = h_1(k(S))$.

Dok transformacija $h_1$ proizvodi vrednosti iz segmenta $[1, B]$, transformacija $h_2$ mora proizvoditi vrednosti iz segmenta $[1, B - 1]$. Rezultat transformacije $h_2$ mora biti relativno prost u odnosu na $B$, da bi se mogao ispitati svaki baket pri traženju slobodne lokacije. Ako je $B$ prost broj, tada se za drugu transformaciju može izabrati $h_2(k(S)) = 1 + k(S)(\text{mod } B)$, ili pošto je za $B$ neparan broj, $h_2(k(S)) = 1 + k(S)(\text{mod}(B - 2))$, [Kn].

**Primer 11.27.** U datoteci na slici 11.10, slogovi sa vrednostima ključa $k(S_7) = 64$ i $k(S_{12}) = 49$ predstavljaju prekoračioce iz baketa sa relativnom adresom 5. Ako je:

$$h_2(k(S)) = 1 + k(S)(\text{mod } 4)$$

tada bi se, na osnovu (11.17), slobodna lokacija za slog sa vrednošću ključa $k(S_7) = 64$ tražila, redom, u baketima sa relativnim adresama $1, 2, 3, 4$. Za slog sa vrednošću $k(S_{12}) = 49$, slobodna lokacija bi se tražila redom u baketima sa relativnim adresama $2, 4, 1, 3$.

### 10.1 Ocena karakteristika rasutih datoteka sa otvorenim adresiranjem

Datoteke sa linearnim i datoteke sa slučajnim traženjem lokacije za smeštaj prekoračilaca se jednim imenom nazivaju **rasutim datotekama sa otvorenim adresiranjem**. Pogodne su za primenu pri faktorima popunjenosti $q$ čija vrednost ne prelazi $0{,}7$.

Slučajno traženje rešava problem pojave nagomilavanja samo u slučajevima kada se iz nekoliko bliskih baketa javlja veći broj prekoračilaca. Primena ovih datoteka je ograničena na slučajeve kada je čestanost ažuriranja datoteke relativno mala. U suprotnom, inicijalni faktor popunjenosti mora da ispod granice od $q = 0{,}7$.

Postoje tri osnovna razloga za nagli rast broja pristupa pri uspešnom, a naročito pri neuspešnom traženju, u slučajevima kada $q$ raste preko vrednosti $0{,}7$:

- Traženje se vrši i u baketima koji ne sadrže slogove iz skupa sinonima traženog sloga.
- Neuspešno traženje se zaustavlja tek po dolasku do slobodne lokacije.
- Prekoračioci iz jednih baketa izazivaju pojavu prekoračilaca iz drugih baketa.

---

## 11. Rasute datoteke sa sprezanjem u primarnoj zoni

Da bi se izbegla prva dva nedostatka rasutih datoteka sa otvorenim adresiranjem, uvodi se **sprezanje**. Putem pokazivača se sprežu svi slogovi jednog skupa sinonima, bez obzira da li se nalaze u matičnom ili nekom drugom baketu. U tom cilju, lokacija za smeštaj sloga se proširuje jednim poljem. To polje sadrži adresu lokacije u koju je smešten naredni slog istog skupa sinonima baketa.

### 11.1 Struktura baketa sa sprezanjem

Svaki baket se snabdeva jednim zaglavljem, koje sadrži:

- Polje pokazivača $u$ za smeštaj adrese lokacije prvog sloga iz skupa sinonima baketa
- Polje pokazivača $b$ za smeštaj adrese prvog prethodnog baketa sa slobodnom lokacijom
- Polje pokazivača $n$ za smeštaj adrese prvog narednog baketa sa slobodnom lokacijom
- Polje $e$, koje sadrži broj slobodnih lokacija baketa

Baketi sa slobodnim lokacijama su međusobno dvostruko spregnuti. Takođe, fizička struktura datoteke je snabdevena jednom malom pomoćnom strukturom podataka. To je indeks slobodnih baketa $E$, koji sadrži adresu prvog baketa sa slobodnom lokacijom.

> [!IMPORTANT]
> Treba naglasiti da je ista raspodela prekoračilaca po baketima u obe datoteke posledica usvojenog hronološkog redosleda nastanka slogova i raspodele aktuelnih vrednosti ključa. U opštem slučaju, raspodele prekoračilaca po baketima u ove dve vrste rasutih datoteka se razlikuju, jer se u rasutoj datoteci sa sprezanjem prekoračioci smeštaju u baket čija adresa se nalazi u pokazivaču $E$, bez obzira na adresu njihovog matičnog baketa.

**Primer 11.28.** Na slici 11.24 prikazana je rasuta datoteka sa sprezanjem u primarnoj zoni koja sadrži $N = 13$ slogova smeštenih u $B = 5$ baketa. Faktor baketiranja je $b = 3$. Datoteka sadrži iste slogove kao i rasuta datoteka sa linearnim traženjem na slici 11.10. Slobodne lokacije sadrže zvezdicu u polju ključa.

### 11.2 Traženje u rasutoj datoteci sa sprezanjem u primarnoj zoni

Traženje sloga u datoteci sa sprezanjem u primarnoj zoni vrši se tako što se, na osnovu transformacije argumenta, pristupa matičnom baketu. Polje $u$ zaglavlja matičnog baketa sadrži adresu lokacije prvog sloga iz skupa sinonima, tako da se traženje nastavlja praćenjem pokazivača. Nailaskom na slog sa traženom vrednošću ključa, traženje se završava uspešno. Kriterijum završetka neuspešnog traženja predstavlja dolazak do oznake kraja lanca sinonima.

Broj pristupa $R_u$ pri uspešnom traženju jednog sloga uzima celobrojne vrednosti iz intervala $[1, 1 + \bar{S}]$, gde je $\bar{S}$ broj slogova u skupu sinonima ($0 \leq \bar{S} \leq N$).

Gornja granica broja pristupa $R_u$ se dobija u najnepovoljnijem slučaju, kada su svi sinonimi jednog skupa smešteni u različite bakete i nijedan u matični.

Treba zapaziti da pokazivač ka prvom slogu iz skupa sinonima baketa predstavlja neophodan deo fizičke strukture podataka datoteke. Naime, u matičnom baketu se mogu nalaziti prekoračioci iz raznih drugih baketa i nijedan primarni slog. U tom slučaju bi traženje sloga iz skupa sinonima, bez pokazivača ka prvom slogu, bilo neizvodljivo.

Pri neuspešnom traženju jednog sloga, broj pristupa $R_n$ iznosi $R_n = 1$, kada su svi sinonimi smešteni u matični baket, a $R_n = 1 + \bar{S}$, kada se nijedan sinonim ne nalazi u matičnom baketu.

Očekivani brojevi pristupa pri uspešnom traženju u maloj datoteci sa poznatom strukturom izračunavaju se na osnovu formule (11.11), a pri neuspešnom traženju primenom formule (11.12).

**Primer 11.29.** Da bi se u datoteci na slici 11.24 pronašao slog sa vrednošću ključa $k(S_{12}) = 49$, potrebno je $R_u = 3$ pristupa, a da bi se utvrdilo da slog sa vrednošću ključa $k(S) = 71$ u datoteci ne postoji, potrebno je $R_n = 1$ pristup.

Očekivani brojevi pristupa pri uspešnom i pri neuspešnom traženju sloga u datoteci na slici 11.24 iznose, redom, $\overline{R_u} \approx 1{,}46$ i $\overline{R_n} \approx 1{,}8$.

### 11.3 Ažuriranje rasute datoteke sa sprezanjem u primarnoj zoni

Upis novog sloga u rasutu datoteku sa sprezanjem u primarnoj zoni vrši se nakon neuspešnog traženja. Ukoliko je matični baket popunjen, novi slog se upisuje u baket sa slobodnom lokacijom. Adresa lokacije novog sloga smešta se u polje pokazivača hronološki prethodnog sloga. Adresa tog baketa se nalazi u indeksu slobodnih baketa $E$.

Novi slog se upisuje kao poslednji u lancu sinonima. Ažuriranje lanca slobodnih baketa predstavlja ažuriranje dvostruko spregnute datoteke.

Pri upisu novog sloga u baket, smanjuje se sadržaj polja $e$ za jedan. Kada polje brojača $e$ dobije vrednost nula, baket se isključuje iz lanca nezauzetih baketa. Ako je taj baket, do tada, predstavljao prvi nezauzeti baket, njegov pokazivač $n$ se prenosi u indeks slobodnih baketa $E$. Ažuriranje lanca slobodnih baketa predstavlja ažuriranje dvostruko spregnute datoteke.

Brisanje sloga iz datoteke vrši se i logički i kao u spregnutoj datoteci. Pri brisanju kao u spregnutoj datoteci, ako je pre brisanja baket bio popunjen, mora se izvršiti i ažuriranje u lancu slobodnih baketa. Takođe, u lokaciju izbrisanog sloga upisuje se niz specijalnih znakova koji ukazuju da je lokacija slobodna.

### 11.4 Ocena karakteristika rasute datoteke sa sprezanjem u primarnoj zoni

Međusobnim sprezanjem slogova svakog skupa sinonima povećava se efikasnost traženja u odnosu na datoteke sa otvorenim adresiranjem. To povećanje efikasnosti posebno dolazi do izražaja u datotekama sa faktorom popunjenosti preko $0{,}7$ i u slučaju neuspešnog traženja, a posledica je činjenice da se traženje vrši samo u baketima koji sadrže slogove iz traženog skupa sinonima i činjenice da se traženje zaustavlja nailaskom na oznaku kraja lanca sinonima.

Povećanje efikasnosti traženja je postignuto na račun manje efikasnosti korišćenja memorijskog prostora, pri istom faktoru popunjenosti kao u datoteci sa otvorenim adresiranjem.

Brisanje slogova, kao u spregnutoj datoteci, obezbeđuje dinamičko upravljanje slobodnim lokacijama memorijskog prostora dodeljenog datoteci, ali ne rešava problem prekoračilaca. Degradacija performansi traženja zbog pojave da jedni prekoračioci izazivaju pojavu drugih, može se rešiti reorganizacijom, ili formiranjem datoteke u dva prolaza.

---

## 12. Rasute datoteke sa sprezanjem u zoni prekoračenja

Datoteci sa sprezanjem u zoni prekoračenja dodeljena su dva memorijska prostora. To su **primarna zona** koja sadrži matične bakete, i **zona prekoračenja** za smeštaj prekoračilaca. Na taj način se eliminiše mogućnost zaposedanja matičnih baketa od strane prekoračilaca iz drugih baketa.

### 12.1 Struktura zone prekoračenja

Svaki matični baket i svaka lokacija u zoni prekoračenja je proširena poljem za smeštaj pokazivača. Pokazivač matičnog baketa sadrži adresu lokacije prvog sloga iz odgovarajućeg lanca prekoračilaca. Zona prekoračenja sadrži skup lanaca čiji indeksi početka se nalaze u baketima primarne zone.

Za faktor baketiranja u zoni prekoračenja se često bira $b = 1$. Naime, prekoračioci se u zonu prekoračenja smeštaju slučajnim redosledom, tako da je mala verovatnoća da se u isti baket smesti dva ili više prekoračilaca iz istog skupa sinonima. S druge strane, veći baketi zahtevaju veći bafer u operativnoj memoriji i duže vreme prenosa.

Zona prekoračenja se snabdeva i jednom malom pomoćnom strukturom podataka. To je indeks slobodnih baketa $E$.

### 12.2 Dimenzionisanje zone prekoračenja

Određivanje broja lokacija $Z$ potrebnih za smeštaj prekoračilaca otežava činjenica da se tačan broj prekoračilaca ne može unapred predvideti. Dimenzionisanje zone prekoračenja vrši se na osnovu očekivanog broja prekoračilaca i srednje kvadratnog odstupanja broja prekoračilaca iz primarne zone.

Brojevi prekoračilaca iz svakog baketa primarne zone predstavljaju nezavisne slučajne veličine $L_i$ ($i = 1, ..., B$) sa istom raspodelom, istim matematičkim očekivanjem i istom disperzijom. Na osnovu centralne granične teoreme sledi da, za dovoljno veliko $B^*$, ukupni broj prekoračilaca:

$$L_B = \sum_{i=1}^{B} L_i$$

predstavlja slučajnu veličinu sa normalnom raspodelom.

Problem dimenzionisanja zone prekoračenja svodi se na određivanje takvog broja lokacija $Z$, da bude zadovoljen uslov:

$$(11.18) \quad P(L_B \leq Z) \geq p$$

gde je $p$ neka unapred zadata verovatnoća. Drugim rečima, treba odrediti $Z$ tako da sa verovatnoćom ne manjom od $p$, ukupni broj prekoračilaca iz primarne zone ne bude veći od $Z$.

Pošto su zadovoljeni uslovi centralne granične teoreme [Ha], (11.18) je ekvivalentno sa:

$$P\left(\frac{L_B - \overline{LB}}{\sqrt{D}} \leq \frac{Z - \overline{LB}}{\sqrt{D}}\right) \approx \Phi\left(\frac{Z - \overline{LB}}{\sqrt{D}}\right) \geq p$$

gde je $\overline{LB}$ matematičko očekivanje slučajne veličine $L_B$, dato sa (11.9), $D$ njena disperzija, a $\Phi(x)$ funkcija normalne raspodele. Na osnovu nezavisnosti $L_i$, sledi $D = B\sigma^2$, gde je $\sigma^2$ disperzija slučajne veličine $L_i$. Dalje je:

$$\sigma^2 = M(L^2) - (\bar{L})^2$$

gde je:

$$M(L^2) = \sum_{i=b+1}^{N} (i-b)^2 P(i)$$

matematičko očekivanje drugog reda slučajne veličine $L_i$. Tako se dobija:

$$\sigma^2 = qb + 2b(1-q) \sum_{i=0}^{b-1} (b-i)P(i) - \left(\sum_{i=0}^{b-1} (b-i)P(i)\right)^2 - \sum_{i=0}^{b-1} (b-i)^2 P(i)$$

Neka je $k$ argument funkcije normalne raspodele, za koji važi $\Phi(k) \geq p$. Tada se broj lokacija u zoni prekoračenja izračunava po formuli:

$$(11.19) \quad Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil$$

Parametar $k$ se pronalazi iz tablice funkcije normalne raspodele za dato $p$, $\sigma$ se procenjuje na osnovu slike 11.26, a $\overline{LB}$ na osnovu slike 11.9.

Uvođenjem zone prekoračenja u fizičku strukturu rasute datoteke menja se i faktor popunjenosti. Faktor popunjenosti cele datoteke sa zonom prekoračenja izračunava se kao:

$$q' = \frac{N}{bB + Z}$$

**Primer 11.31.** Za rasutu datoteku sa $q = 0{,}87$, $b = 10$, $N = 10000$ i $B = 1150$ treba dimenzionisati zonu prekoračenja tako da sa verovatnoćom $p \geq 0{,}998$ u nju mogu da se smeste svi prekoračioci. Za $p = 0{,}998$ iz tablice funkcije normalne raspodele se dobija $k \approx 3$. Sa slika 11.9 i 11.26 se, redom, procenjuje $\overline{LB} \approx 750$ i $\sigma \approx 1{,}45$, te se dobija $Z = 898$. Stvarni faktor popunjenosti za ovu datoteku iznosi $q' \approx 0{,}81$.

### 12.3 Lokalne i zajednička zona prekoračenja

Pri smeštanju prekoračilaca u zonu prekoračenja, prekoračioci se mogu biti dosta udaljeni od svojih matičnih baketa. Na jednici magnetnog diska, to može značiti udaljenost više cilindara, što produžava vreme pristupa. Da bi se vreme pristupa slogovima u zoni prekoračenja skratilo, nakon svake grupe sa određenim brojem matičnih baketa, rezerviše se jedan broj baketa za smeštaj prekoračilaca iz te grupe matičnih baketa.

Na taj način se dobijaju **lokalne zone prekoračenja**, raspodeljene između baketa primarne zone. Takođe se može rezervisati i **zajednička zona** za smeštaj prekoračilaca iz lokalnih zona prekoračenja. Na slici 11.27 prikazana je struktura memorijskog prostora rasute datoteke sa raspodeljenom zonom prekoračenja.

Nedostatak ovog postupka predstavlja činjenica da transformacija vrednosti ključa u adresu ne sme proizvoditi adrese baketa određenih za smeštaj prekoračilaca, što komplikuje algoritam transformacije.

### 12.4 Formiranje rasute datoteke sa sprezanjem u zoni prekoračenja

Prvi korak formiranja rasute datoteke sa sprezanjem u zoni prekoračenja predstavlja formiranje prazne primarne i prazne zone prekoračenja, kao dve posebne datoteke. Dalje se postupak odvija po opštim principima formiranja rasutih datoteka uz poštovanje specifičnih pravila za dodelu adresa lokacija slogovima. To znači i da se prekoračioci smeštaju u prvu slobodnu lokaciju u zoni prekoračenja po principima upisa novog sloga u jednostruko spregnutu datoteku.

---

## 13. Karakteristike obrade rasutih datoteka

Sve varijante rasutih datoteka koje smo obradili imaju jednu zajedničku karakteristiku - postupak obrade. Formiranje baketa od više slogova i izdvajanje slogova iz baketa predstavljaju zadatke aplikativnog programa. Upis i čitanje baketa iz datoteke predstavljaju zadatke relativne metode pristupa. Čitav postupak formiranja rasute datoteke se odvija u režimu direktne obrade.

> [!CAUTION]
> Na ispitu se često pita da se uporede različite varijante rasutih datoteka po broju pristupa, faktoru popunjenosti i efikasnosti traženja. Obratite pažnju na to da:
> - Datoteke sa otvorenim adresiranjem (linearno i slučajno traženje) su pogodne za $q < 0{,}7$
> - Datoteke sa sprezanjem u primarnoj zoni poboljšavaju efikasnost neuspešnog traženja
> - Datoteke sa zonom prekoračenja eliminišu problem zaposedanja matičnih baketa od strane tuđih prekoračilaca

---

## 🎴 Brza pitanja (definicije, pojmovi, delovi)

**P:** Šta je rasuto organizovana datoteka?

**P:** Koja je razlika između statičke i dinamičke rasute datoteke?

**P:** Šta je identifikator u kontekstu rasute datoteke?

**P:** Koja je razlika između identifikatora koji pripada i koji ne pripada skupu obeležja tipa sloga?

**P:** Šta je funkcija transformacije $h$ i kako se definiše?

**P:** Šta je deterministička transformacija identifikatora?

**P:** Šta je probabilistička transformacija identifikatora?

**P:** Šta je baket?

**P:** Šta je faktor baketiranja $b$?

**P:** Kako glasi formula za transformaciju iz primera 11.2: $h(k_i) = 1 + k(S_i)(\text{mod } B)$?

**P:** Koliko lokacija se dodeljuje statičkoj rasutoj datoteci pri formiranju?

**P:** Šta je direktna datoteka?

**P:** Koje su dve vrste direktnih datoteka?

**P:** Koji su nedostaci direktnih datoteka sa mašinskim adresama?

**P:** Šta je relativna adresa?

**P:** Šta je relativna metoda pristupa?

**P:** Šta je relativna datoteka?

**P:** Kako se formira relativna datoteka?

**P:** Kako se vrši traženje u relativnoj datoteci?

**P:** Koliki je broj pristupa $R_u$ pri uspešnom traženju u relativnoj datoteci?

**P:** Koliki je broj upoređenja $U_u$ pri traženju u relativnoj datoteci kada se pridružuje adresa lokacije?

**P:** Koliki je opseg broja upoređenja $U_u$ kada se pridružuje adresa baketa?

**P:** Kako se vrši ažuriranje relativne datoteke?

**P:** Kako se vrši brisanje u relativnoj datoteci (dva načina)?

**P:** Koje su prednosti relativne datoteke u odnosu na serijsku i sekvencijalnu?

**P:** Zašto je direktno korišćenje ključa kao identifikatora problematično?

**P:** Kako glasi formula za relativnu adresu u primeru sa stanovima: $A = s + (b-1)S + (u-1)SB$?

**P:** Šta predstavlja svaki simbol u formuli za adresu stana?

**P:** Kakav je odnos $v^p \gg Q \geq N$ i šta svaki simbol predstavlja?

**P:** Koja su četiri koraka probabilističke transformacije ključa u adresu?

**P:** Kako glasi formula metode ostatka pri deljenju?

**P:** Zašto $m$ ne treba da bude paran broj u metodi ostatka pri deljenju?

**P:** Zašto $m$ ne treba da bude stepen osnove brojnog sistema?

**P:** Šta je najpogodnije za $m$ u metodi ostatka pri deljenju?

**P:** Kada je metoda ostatka pri deljenju posebno pogodna za primenu?

**P:** Kako funkcioniše metoda centralnih cifara kvadrata ključa?

**P:** Kako glasi polinomijalni oblik vrednosti ključa: $k(S) = \sum_{i=0}^{p-1} a_i v^i$?

**P:** Šta predstavlja pseudoslučajni broj $T$ u metodi centralnih cifara kvadrata?

**P:** Kako glasi formula za relativnu adresu $A = \lfloor rQ/v^n \rfloor + 1$?

**P:** Kako funkcioniše metoda preklapanja?

**P:** Kada je metoda preklapanja pogodna za primenu?

**P:** Kako glasi formula (11.4) za pseudoslučajni broj $T$ u metodi preklapanja?

**P:** Šta su sinonimi u kontekstu rasute datoteke?

**P:** Šta je kolizija ključeva?

**P:** Šta je skup sinonima?

**P:** Šta je matični baket?

**P:** Šta su primarni slogovi?

**P:** Šta su prekoračioci (overflow records)?

**P:** Zašto je pojava prekoračilaca nepoželjna?

**P:** Šta je faktor popunjenosti $q$ i kako se izračunava?

**P:** Koji je preporučeni opseg za faktor popunjenosti $q$?

**P:** Kako izbor faktora popunjenosti utiče na performanse datoteke?

**P:** Kako faktor baketiranja $b$ utiče na broj prekoračilaca?

**P:** Kako glasi Poissonova formula za verovatnoću $P(i)$?

**P:** Šta predstavlja $qb$ u Poissonovoj formuli?

**P:** Kako glasi formula za očekivanu vrednost $\bar{S} = qb$?

**P:** Kako glasi formula (11.8) za očekivani broj prekoračilaca $\bar{L}$ iz jednog baketa?

**P:** Kako glasi formula (11.9) za očekivani broj prekoračilaca iz svih $B$ baketa?

**P:** Koji su postupci za smeštaj prekoračilaca?

**P:** Koje datoteke spadaju u rasute datoteke sa jedinstvenim adresnim prostorom?

**P:** Koje datoteke spadaju u rasute datoteke sa zonom prekoračenja?

**P:** Šta se utvrđuje pri projektovanju rasute datoteke sa probabilističkom transformacijom?

**P:** Kako glasi formula za broj baketa: $B = \lceil N/(bq) \rceil$?

**P:** Kako glasi formula (11.10) za $\bar{L}$ koja ne zavisi od $N$?

**P:** Kako glasi formula (11.11) za $\overline{R_u}$?

**P:** Kako glasi formula (11.12) za $\overline{R_n}$?

**P:** Kako glasi formula (11.13) za $\overline{R_n}$ kod slučajnog traženja?

**P:** Kako se formira rasuta datoteka sa linearnim traženjem?

**P:** Kako glasi formula (11.14) za adresu narednog baketa: $A_n = 1 + A_{n-1}(\text{mod } B)$?

**P:** Šta je postupak formiranja u dva prolaza?

**P:** Kako se vrši traženje u rasutoj datoteci sa linearnim traženjem?

**P:** Kada se traženje završava uspešno, a kada neuspešno?

**P:** Kako glasi formula (11.15) za opseg broja pristupa pri uspešnom traženju?

**P:** Kako glasi formula (11.16) za broj pristupa pri neuspešnom traženju?

**P:** Koliki je broj pristupa za upis novog sloga: $R_i = R_n + 1$?

**P:** Koliki je broj pristupa za logičko brisanje: $R_d = R_u + 1$?

**P:** Koje tri vrednosti statusne oznake se koriste kod logičkog brisanja?

**P:** Kako se vrši fizičko brisanje sa selektivnim pomeranjem?

**P:** Šta je nagomilavanje (clustering)?

**P:** Koji faktor popunjenosti se preporučuje za datoteke sa linearnim traženjem?

**P:** Koji su tri razloga za nagli rast broja pristupa kada $q > 0{,}7$?

**P:** Kako funkcioniše rasuta datoteka sa slučajnim traženjem?

**P:** Kako glasi formula (11.17) za adresu $n$-tog baketa kod slučajnog traženja?

**P:** Šta su rasute datoteke sa otvorenim adresiranjem?

**P:** Šta je sprezanje u kontekstu rasutih datoteka?

**P:** Koja četiri polja sadrži zaglavlje baketa sa sprezanjem u primarnoj zoni?

**P:** Šta je indeks slobodnih baketa $E$?

**P:** Kako se vrši traženje u rasutoj datoteci sa sprezanjem u primarnoj zoni?

**P:** Koliki je opseg broja pristupa $R_u$ pri uspešnom traženju sa sprezanjem?

**P:** Kako se vrši ažuriranje rasute datoteke sa sprezanjem u primarnoj zoni?

**P:** Koje su dve zone kod rasute datoteke sa sprezanjem u zoni prekoračenja?

**P:** Šta je primarna zona, a šta zona prekoračenja?

**P:** Zašto se za faktor baketiranja u zoni prekoračenja često bira $b = 1$?

**P:** Kako glasi uslov (11.18) za dimenzionisanje zone prekoračenja?

**P:** Kako glasi formula (11.19) za broj lokacija u zoni prekoračenja: $Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil$?

**P:** Kako se izračunava faktor popunjenosti cele datoteke sa zonom prekoračenja: $q' = N/(bB + Z)$?

**P:** Šta su lokalne zone prekoračenja?

**P:** Šta je zajednička zona prekoračenja?

**P:** Koji je nedostatak raspodeljene zone prekoračenja?

---

## 📝 Šira pitanja za proveru razumevanja

**P:** Objasnite razliku između determinističke i probabilističke transformacije identifikatora u adresu. Koja je injektivna i zašto?

**O:** Deterministička transformacija preslikava svaku vrednost identifikatora u tačno jednu adresu po jednoznačnom pravilu, i svakoj adresi odgovara najviše jedna vrednost identifikatora - zato je ona injektivna funkcija. Probabilistička transformacija koristi metode za generisanje pseudoslučajnih brojeva, pa se može desiti da dve različite vrednosti identifikatora dobiju istu adresu (kolizija). Deterministička se koristi kod direktnih i relativnih datoteka, a probabilistička kod rasutih datoteka gde je opseg mogućih vrednosti ključa mnogo veći od adresnog prostora.

---

**P:** Zašto se kod metode ostatka pri deljenju preporučuje da broj $m$ bude prost ili neparan broj sa velikim prostim činiocima? Šta se dešava ako je $m$ paran ili stepen osnove brojnog sistema?

**O:** Ako je $m$ paran, sve neparne vrednosti ključa dobiće neparne relativne adrese, a parne vrednosti parne adrese, što narušava ravnomernost raspodele. Ako je $m$ stepen osnove brojnog sistema (npr. $10^k$), tada relativnu adresu određuju samo cifre najmanje težine ključa, bez obzira na ostale cifre. Prost broj ili neparan broj sa velikim prostim činiocima obezbeđuje da ostatak pri deljenju zavisi od svih cifara ključa, što daje ravnomerniju raspodelu slogova po baketima.

---

**P:** Za datoteku sa $N = 13$ slogova, $B = 5$ baketa i $b = 3$, izračunajte faktor popunjenosti $q$ i očekivani broj sinonima po baketu $\bar{S}$.

**O:** Faktor popunjenosti je $q = N/Q = N/(bB) = 13/(3 \times 5) = 13/15 \approx 0{,}87$. Očekivani broj sinonima po jednom baketu iznosi $\bar{S} = qb = 0{,}87 \times 3 = 2{,}61$. To znači da u proseku svaki baket sadrži oko 2,61 sloga, što je blizu kapaciteta baketa od 3, pa je visoka verovatnoća pojave prekoračilaca.

---

**P:** Uporedite rasute datoteke sa linearnim traženjem, sa sprezanjem u primarnoj zoni i sa sprezanjem u zoni prekoračenja po kriterijumima efikasnosti traženja i korišćenja memorijskog prostora.

**O:** Datoteka sa linearnim traženjem je najefikasnija po korišćenju memorije jer nema dodatnih polja, ali performanse brzo degradiraju za $q > 0{,}7$ zbog nagomilavanja. Datoteka sa sprezanjem u primarnoj zoni uvodi polja za pokazivače, čime se poboljšava neuspešno traženje jer se prate samo sinonimi, ali se tuđi prekoračioci i dalje mogu naći u matičnom baketu. Datoteka sa zonom prekoračenja potpuno eliminiše problem zaposedanja matičnih baketa od strane tuđih prekoračilaca, ali zahteva dodatni memorijski prostor za zonu prekoračenja i njeno dimenzionisanje.

---

**P:** Objasnite fenomen nagomilavanja (clustering) kod rasutih datoteka sa linearnim traženjem. Kako se može ublažiti?

**O:** Nagomilavanje nastaje kada se dugački nizovi zauzetih lokacija formiraju u datoteci. Što je niz duži, veća je verovatnoća da će novi slog biti smešten na njegov kraj, jer svaki slog čiji matični baket pada bilo gde unutar niza završava na istom mestu. Time niz raste eksponencijalno. Ublažava se korišćenjem faktora popunjenosti $q < 0{,}7$, primenom slučajnog traženja umesto linearnog (koje koristi drugu hash funkciju za korak), ili prelaskom na datoteke sa sprezanjem.

---

**P:** Kako se dimenzionise zona prekoračenja? Objasnite korake i formulu $Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil$.

**O:** Dimenzionisanje se zasniva na statističkoj analizi. Prvo se odredi očekivani broj prekoračilaca $\overline{LB}$ iz formule (11.9), zatim standardna devijacija $\sigma$ iz krive na slici 11.26. Za zadatu verovatnoću $p$ (npr. 0,998) pronađe se parametar $k$ iz tablice normalne raspodele. Formula $Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil$ daje broj lokacija u zoni prekoračenja koji sa zadatom verovatnoćom $p$ obezbeđuje dovoljno prostora za sve prekoračioce.

---

**P:** Objasnite zašto očekivani broj pristupa rasutoj datoteci sa velikim brojem slogova ne zavisi od $N$, već samo od $q$ i $b$.

**O:** Ovo sledi iz formule (11.10) gde se $\bar{L}$ izražava kao $b(q-1) + \sum_{i=0}^{b}(b-i)P(i)$, koja ne sadrži $N$. Razlog je što se pri Poissonovoj aproksimaciji svi parametri raspodele izražavaju preko proizvoda $qb = N/B$, a ne preko $N$ i $B$ pojedinačno. To znači da datoteka sa $N = 100$ i $B = 50$ ima iste očekivane performanse kao datoteka sa $N = 10000$ i $B = 5000$, pod uslovom da su $q$ i $b$ isti.

---

**P:** U čemu je prednost postupka formiranja rasute datoteke u dva prolaza u odnosu na standardni jednoprolazni postupak?

**O:** Kod standardnog postupka, prekoračioci iz jednih baketa mogu zauzeti lokacije u matičnim baketima drugih slogova, čime ti slogovi takođe postaju prekoračioci iako njihov matični baket ima slobodnog mesta. Kod dvoprolaznog postupka, u prvom prolazu se upisuju samo primarni slogovi u matične bakete, a u drugom prolazu se smeštaju prekoračioci. Time se garantuje da su matični baketi optimalno popunjeni primarnim slogovima, što smanjuje ukupni broj prekoračilaca i poboljšava performanse traženja.

---

**P:** Objasnite tri metode probabilističke transformacije ključa u adresu i navedite za šta je svaka posebno pogodna.

**O:** Metoda ostatka pri deljenju ($A = 1 + k(S) \text{ mod } m$) je najjednostavnija i pogodna kada se vrednosti ključa javljaju u paketima. Metoda centralnih cifara kvadrata diže ključ na kvadrat i uzima centralne cifre, čime se postiže da relativna adresa zavisi od svih cifara ključa. Metoda preklapanja je pogodna za ključeve sa velikim brojem pozicija ($p \gg n$) jer "presavija" cifre ključa i sabira ih, čime se dugačak ključ komprimuje u kraću adresu.
