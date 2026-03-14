# Rasuta organizacija datoteka (statička)

## Uvod - o čemu se radi?

Zamislimo da imamo ogromnu biblioteku sa hiljadama knjiga. Ako bismo knjige redali nasumično po policama, pronalaženje bilo koje knjige značilo bi pretresanje cele biblioteke. Ali šta ako bismo imali magičnu formulu koja, čim joj kažemo naslov knjige, odmah kaže: "Ta knjiga je na polici broj 7, treća s leva"? Upravo to radi rasuta organizacija datoteke - umesto da pretražujemo celu datoteku, formula nam direktno kaže gde se slog nalazi.

Rasuto organizovane datoteke (engleski: *hash files*) dele se na **statičke** i **dinamičke**. Za statičke rasute datoteke karakteristično je da se veličina dodeljenog adresnog prostora mora odrediti prilikom projektovanja i da se tokom eksploatacije ne može menjati. Dinamičke rasute datoteke nemaju to ograničenje jer se veličina dodeljenog adresnog prostora menja tokom ažuriranja, saglasno trenutnim potrebama. Statičke rasute datoteke su, istorijski, nastale mnogo pre dinamičkih.

U ovoj skripti bavimo se isključivo statičkim rasutim datotekama.

Rasuta organizacija datoteke se često naziva i **direktnom**, jer se slogu ili grupi slogova pristupa direktno, na osnovu poznavanja adrese memorijske lokacije u koju su slogovi smešteni. Adresa lokacije se dobija **transformacijom vrednosti identifikatora** sloga u adresu.

---

## Identifikator i transformacija

### Šta je identifikator?

**Identifikator** predstavlja obeležje čije vrednosti jednoznačno određuju slogove datoteke. Sam identifikator, kao obeležje, može, a ne mora pripadati skupu obeležja tipa sloga datoteke. Ako skup obeležja tipa sloga sadrži identifikator, tada ulogu identifikatora, po pravilu, igra **primarni ključ** datoteke. Međutim, ako identifikator ne pripada skupu obeležja tipa sloga, tada se vrednosti identifikatora pridružuju svakom slogu eksterno, van konteksta sadržaja datoteke. Pri tome mora postojati neko pravilo povezivanja vrednosti identifikatora i slogova datoteke.

> [!NOTE]
> Zamislimo to ovako: u školi se o učenicima ne govori navodeći njihova imena, već navodeći broj reda i poziciju klupe u koju su raspoređeni da sede. Taj "broj reda i klupa" je identifikator koji je pridružen spolja - nije deo "sadržaja" učenika, ali jednoznačno ga određuje.

### Transformacija vrednosti identifikatora u adresu

Za transformaciju vrednosti identifikatora u adresu koristi se funkcija $h$ koja preslikava domen identifikatora $K$ u skup adresa $A$ lokacija memorijskog prostora dodeljenog datoteci. Znači:

$$h : dom(K) \rightarrow A$$

Ako je $k_i$ vrednost identifikatora $K$ pridružena slogu $S_i$, $i \in \{1, ..., N\}$, tada se adresa $A_i \in A$ lokacije u koju treba smestiti slog $S_i$ dobija kao:

$$A_i = h(k_i)$$

Transformacija vrednosti identifikatora u adresu može biti:

- **Deterministička** - kod koje jednoj vrednosti identifikatora odgovara najviše jedna adresa i svakoj adresi odgovara najviše jedna vrednost identifikatora. Drugim rečima, funkcija $h$ je **injektivna**.
- **Probabilistička** - koja vrednost identifikatora pretvara u adresu nekom od metoda za generisanje pseudoslučajnih brojeva. Pri tome, svakoj vrednosti identifikatora odgovara jedna od adresa memorijskog prostora dodeljenog datoteci, ali jednoj od adresa može odgovarati više rezultata transformacije identifikatora.

> [!IMPORTANT]
> Ključna razlika: kod determinističke transformacije, jedinstven ključ daje jedinstvenu adresu (1-1 preslikavanje). Kod probabilističke, više različitih ključeva može dati istu adresu, što dovodi do pojave **sinonima**.

### Baket - osnovna jedinica smeštanja

Kada je reč o rasutim datotekama, lokacija u koju se smešta jedan ili više slogova naziva se **baketom**. Pojam baketa analogan je pojmu bloka. Analogno pojmu faktora blokiranja, uvodi se pojam **faktora baketiranja** $b$ ($b \geq 1$). Faktor baketiranja ukazuje na maksimalno mogući broj slogova u jednom baketu. Transformacijom se vrednost identifikatora pretvara u adresu baketa.

> [!TIP]
> Baket je kao fioka u ormaru - u jednu fioku (baket) može da stane određen broj predmeta (slogova). Faktor baketiranja $b$ nam kaže koliko predmeta staje u jednu fioku.

---

## 11.1 Opšti postupak formiranja rasute datoteke

Statičkoj rasutoj datoteci se u postupku formiranja dodeljuje $Q = bB$ lokacija, pri čemu važi $N \leq Q$. Nakon formiranja se $Q$ više ne može menjati.

I u slučaju determinističke transformacije i u slučaju probabilističke transformacije identifikatora u adresu, redosled smeštanja slogova u datoteku je nevažan. Slogovi se, saglasno hronološkom redosledu nastanka, uvoze u proceduru za traženje, gde se vrši transformacija vrednosti identifikatora u adresu. Ako je traženje neuspešno, slog se smešta u baket sa izračunatom adresom. Kod probabilističke transformacije se može desiti da baket, čija adresa je dobijena transformacijom, bude popunjen. Tada se primenjuju posebni postupci za traženje lokacije u koju će se slog smestiti.

U nastavku ovog poglavlja, opisana je relativna datoteka, kao predstavnik rasutih datoteka sa determinističkom transformacijom identifikatora u adresu, i opisano je nekoliko varijanti rasutih datoteka sa probabilističkom transformacijom vrednosti identifikatora u adresu. Sve ove datoteke poseduju niz specifičnosti kada je u pitanju formiranje, traženje i ažuriranje, ali i jednu zajedničku karakteristiku - postupak obrade. Karakteristike obrade svih rasuto organizovanih datoteka obrađene su na jednom mestu u okviru ovog poglavlja.

---

## 11.2 Direktne datoteke

Najjednostavniji vid determinističke transformacije identifikatora u adresu predstavlja slučaj kada vrednost identifikatora odgovara adresi baketa. Tada je transformacija trivijalna, tj. $A_i = k_i$. Strogo govoreći, jedino rasuto organizovane datoteke dobijene trivijalnom transformacijom vrednosti identifikatora u adresu baketa s pravom nose naziv **"direktne"**.

Postoje dve vrste rasuto organizovanih datoteka dobijenih trivijalnom transformacijom vrednosti identifikatora u adresu:

1. Kod **prve** je vrednost identifikatora jednaka **mašinskoj adresi**, a kod
2. **druge** je vrednost identifikatora jednaka **relativnoj adresi** - deo sloga.

### Direktne datoteke sa mašinskim adresama

Kod direktnih datoteka sa mašinskim adresama, svakom slogu se pridružuje identifikator u obliku mašinske adrese. Ako se datoteka nalazi na magnetnom disku, taj identifikator predstavlja trojku (*broj cilindra, broj staze, broj sektora*). Za korišćenje direktnih datoteka sa mašinskim adresama, neophodno je u programu eksplicitno navesti mašinsku adresu baketa, kojem se želi pristupiti. Zbog toga se ne mogu koristiti putem programa pisanih u višim programskim jezicima; imaju samo istorijski značaj.

### Nedostaci direktnih datoteka

Te nedostatke predstavljaju:

- **Čvrsta povezanost slogova datoteke sa fizičkim karakteristikama memorijskog uređaja** - odsustvo logičke veze između vrednosti identifikatora i sadržaja sloga.
- Programer mora da vodi računa o fizičkoj adresi lokacije u kojoj je smešten slog, pri čemu ta adresa nema nikakve logičke veze sa sadržajem sloga.
- Ako se podaci o istom entitetu javljaju u više direktnih datoteka, istom entitetu se pridružuje više različitih identifikatora.
- Ako se neki identifikator, nakon brisanja podataka o jednom entitetu, dodeli drugom, može doći do konfuzije pri obradi ranijih i aktuelnih podataka.

Čvrsta povezanost slogova datoteke sa fizičkim karakteristikama memorijskog uređaja dovodi do potrebe izmene vrednosti identifikatora dodeljenih slogovima datoteke, pri promeni memorijskog uređaja, ili čak samo dela memorijskog prostora dodeljenog datoteci na istom memorijskom uređaju.

---

## 11.3 Rasute datoteke sa determinističkom transformacijom

Problem čvrste povezanosti slogova datoteke sa fizičkim karakteristikama memorijskog uređaja rešava se korišćenjem **relativnih adresa**. Lokacije memorijskog prostora dodeljenog datoteci privično se numerišu rednim brojevima od $1$ do $Q$ (ili od $0$ do $Q - 1$). Ti redni brojevi predstavljaju relativne adrese lokacija i identifikatore slogova, koji se smeštaju u lokacije sa odgovarajućom relativnom adresom. Identifikator i dalje ne predstavlja podskup obeležja tipa sloga. Pošto se svakoj lokaciji na memorijskom uređaju može pristupiti samo na osnovu njene mašinske adrese, relativne adrese se moraju transformisati u mašinske. Ova transformacija predstavlja zadatak dela sistema za upravljanje podacima koji se naziva **relativnom metodom pristupa**. Često se i datoteke, formirane korišćenjem relativne metode pristupa, nazivaju relativnim datotekama.

U lokacije memorijskog prostora dodeljenog relativnoj datoteci, slogovi se upisuju saglasno vrednosti identifikatora. Ne postoji fiksno pravilo za pridruživanje vrednosti identifikatora slogovima datoteke. Međutim, kada se to pravilo jedanput utvrdi, ono uspostavlja vezu između sloga i adrese lokacije, u koju je slog smešten. Za fizičku strukturu relativne datoteke je, takođe, karakteristično da ne poseduje informaciju o vezama između sloga u logičkoj strukturi podataka datoteke.

### Primer 11.3 - Fizička struktura relativne datoteke

Na slici 11.2 je prikazana fizička struktura relativne datoteke od $N = 13$ slogova. Faktor baketiranja iznosi $b = 3$, a datoteci je dodeljeno $Q = 15$ lokacija. Datoteka sadrži iste slogove kao serijska datoteka na slici 8.1. Pravilo za pridruživanje vrednosti identifikatora slogovima dato je sledećom tabelom:

| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| $S_i$ | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
| $A_i$ | $A_1^1$ | $A_1^2$ | $A_1^3$ | $A_2^1$ | $A_2^2$ | $A_2^3$ | $A_3^1$ | $A_3^2$ | $A_3^3$ | $A_4^1$ | $A_4^2$ | $A_4^3$ | $A_5^3$ |

Svakom hronološki narednom slogu pridružena je adresa prve slobodne lokacije od početka memorijskog prostora dodeljenog datoteci. Naime, hronološki prvom slogu je dodeljena lokacija sa adresom $A_1^1$, a $i$-tom slogu se pridružuje adresa $A_p^q$, gde je $p = \lceil i / b \rceil$, a $q = 1 + (i - 1) \pmod{b}$, za $i = 2, ..., 13$.

Datoteka izgleda ovako (5 baketa, svaki sa po 3 lokacije):

| Baket | Lokacija 1 | Lokacija 2 | Lokacija 3 |
|---|---|---|---|
| $A_1$ | 34, $p(S_1)$ | 07, $p(S_2)$ | 03, $p(S_3)$ |
| $A_2$ | 15, $p(S_4)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |
| $A_3$ | 64, $p(S_7)$ | 43, $p(S_8)$ | 23, $p(S_9)$ |
| $A_4$ | 27, $p(S_{10})$ | 13, $p(S_{11})$ | 49, $p(S_{12})$ |
| $A_5$ | 25, $p(S_{13})$ | * | |

---

### 11.3.1 Relativna metoda pristupa

Sistem za upravljanje podacima mainframe računarskih sistema su posedovali metodu pristupa za standardizovano formiranje, korišćenje i ažuriranje relativnih datoteka. Ovu metodu pristupa koristili su programi pisani u višim programskim jezicima. Savremena softverska okruženja, koja čine operativni sistem, kao što je Unix, i programski jezik, kao što je C, podržavaju relativne datoteke putem standardnih bibliotečkih funkcija, ali ostavljaju aplikativnim programima da reše čitav niz rutinskih aktivnosti rada sa datotekom, koje su operativni sistemi mainframe računara i programski jezici, kao Cobol, podržavali.

Jedan od zadataka relativne metode pristupa predstavlja transformacija vrednosti relativne adrese (tzv. relativnog ključa) u mašinsku adresu. Osim toga, relativna metoda pristupa vrši, za račun programa, upis slogova u datoteku, brisanje slogova, izvršava program o neuspešnom čitanju ili brisanju, ako je adresirana lokacija prazna i o neuspešnom upisu, ako se na adresiranoj lokaciji već nalazi neki slog. Za realizaciju svake od ovih aktivnosti, program saopštava metodi pristupa relativnu adresu sloga, putem promenljive definisane u programu.

Operativni sistemi mainframe računara i programski jezici, kao što je Cobol, posmatrali su relativnu datoteku kao niz slogova. Relativna adresa sloga je njegov redni broj od početka datoteke. Operativni sistem Unix i programski jezici, kao što je C, posmatraju datoteku kao niz bajtova. Saglasno tome, relativna adresa sloga je jednaka proizvodu rednog broja sloga i broja bajtova, upotrebljenih za njegovo memorisanje. Ova činjenica ukazuje na neophodnost korišćenja slogova konstantne dužine u relativnim datotekama.

Relativna metoda pristupa pruža programu usluge na nivou bloka, tako da ne vrši blokiranje i rastavljanje blokova na slogove, odnosno prihvata samo vrednost faktora blokiranja jednaku jedinici. Da bi se, u cilju boljeg iskorišćenja memorijskog prostora, slogovi ipak mogli smeštati u relativnu datoteku blokirano, aktivnosti blokiranja i rastavljanja blokova na slogove se moraju realizovati u okviru samog programa. U tom cilju se organizaciona jedinica podataka koja se razmenjuje između programa i relativne datoteke na eksternom memorijskom uređaju mora definisati kao jednodimenzionalni niz.

#### Formiranje u programskom jeziku C

Operativni sistem Unix i programski jezici, kao što je C, ne prave razliku između serijske, sekvencijalne, relativne, ili bilo koje druge vrste organizacije datoteke. Oni za formiranje svake datoteke podržavaju iste sistemske pozive (`open`, `write`, `read`, `seek`) i odgovarajuće bibliotečke funkcije, ostavljajući aplikativnom programu da obezbedi svu funkcionalnost, koju zahteva određena vrsta organizacije datoteke i njena metoda pristupa.

#### Formiranje u programskom jeziku Cobol

U standardnom programskom jeziku Cobol postoji određeni broj naredbi za rad sa relativnom datotekom. Fraze, putem kojih se opisuje organizacija datoteke nalaze se u paragrafu `FILE CONTROL`, sekcije `INPUT-OUTPUT SECTION`, dela `ENVIRONMENT DIVISION`. Te fraze su:

```
SELECT ime_datoteke (logičko_ime)
    ASSIGN TO ime_uređaja
    ORGANIZATION IS RELATIVE
    [ACCESS MODE IS {SEQUENTIAL [RELATIVE KEY IS ime_promenljive] |
    {RANDOM | DYNAMIC} RELATIVE KEY IS ime_promenljive}]
```

Fraza `ACCESS MODE IS` je opciona, a ako se ne navede, način pristupa je `SEQUENTIAL`. Fraza `RELATIVE KEY` se mora navesti u programu ako `ACCESS MODE` nije `SEQUENTIAL`, a umesto `ime_promenljive` se upisuje naziv identifikatora.

Pri formiranju relativne datoteke, način pristupa se deklariše kao `SEQUENTIAL`, a datoteka se otvara kao izlazna. U delu `PROCEDURE DIVISION` se, nakon čitanja ulazne datoteke i formiranja baketa, vrši upis u relativnu datoteku putem naredbe:

```
WRITE ime_sloga
    [INVALID KEY imperativna naredba].
```

`Ime_sloga` je naziv sloga datoteke, opisanog u sekciji `FILE SECTION`. Pri upisu prvog baketa, relativna metoda pristupa postavlja vrednost jedan u relativni ključ, tako da se prvi baket upisuje u lokaciju sa relativnom adresom $1$. Pri izvršavanju svake naredne `WRITE` naredbe, vrednost relativnog ključa se povećava za jedinicu. Fraza `INVALID KEY` stupa u dejstvo, ako za upis baketa nema mesta u okviru prostora rezervisanog za relativnu datoteku. To znači da se, pre početka formiranja, za datoteku mora rezervisati $Q \geq N$ lokacija.

---

### 11.3.2 Formiranje relativne datoteke

Korisnici mainframe računarskih sistema su za formiranje relativne datoteke pisali program, koji je koristio usluge relativne metode pristupa. Taj program je učitavao sukcesivne slogove neke serijske datoteke, pridruživao im vrednosti identifikatora i smeštao ih u lokacije, čije relativne adrese predstavljaju vrednosti identifikatora.

Zavisno od korišćenog operativnog sistema, postojala su dva postupka za formiranje relativne datoteke. Razlike pri formiranju su poticale od činjenice da se, prema jednom od postupaka, prethodno moraju u sve lokacije datoteke upisati lažni slogovi. Upis lažnih slogova se vršio u onim slučajevima kada metoda pristupa, nakon prvog zatvaranja datoteke, definiše granice datoteke saglasno broju upisanih slogova. Ukoliko dodeljen prostor ostaje na raspolaganju datoteci nakon prvog zatvaranja, bez obzira na broj upisanih slogova, prethodni upis lažnih slogova nije neophodan.

Sadržaj statusne oznake treba da ukaže da je reč o inicijalno praznim lokacijama.

---

### 11.3.3 Traženje u relativnoj datoteci

Traženje i logički narednog i slučajno odabranog sloga u relativnoj datoteci vrši se metodom transformacije identifikatora u adresu. Pošto je transformacija trivijalna, ceo postupak se svodi na saopštavanje vrednosti identifikatora, odnosno relativne adrese lokacije, relativnoj metodi pristupa.

Na osnovu tako zadate adrese, metoda pristupa prenosi baket u radnu zonu programa. Ako se traženi slog nalazi u baketu, traženje se završilo uspešno. Inače je traženje neuspešno.

#### Primer 11.5 - Traženje u Cobol programu

Traženje sloga u relativnoj datoteci putem programa pisanog u Cobolu realizuje se tako što se za način pristupa deklariše da je `RANDOM`. U delu procedure se, nakon postavljanja vrednosti identifikatora u `ime_promenljive`, izdaje naredba:

```
READ ime_datoteke RECORD
    INVALID KEY imperativna naredba.
```

Imperativna naredba stupa u dejstvo ako je adresirana lokacija prazna.

#### Primer 11.6 - Traženje u C programu

Posmatra se datoteka `student.data` sa slogovima konstantne dužine od 47 bajtova, formirana postupkom opisanim u primeru 3.11. Neka je u datoteku upisano 30 slogova. Da bi se pročitao slog sa rednim brojem 17, potrebno je prvo izvršiti pozicioniranje na njegov početak, korišćenjem `fseek` naredbe:

```c
fseek(fpt, 752L, 0);
```

a zatim izvršiti čitanje putem naredbe:

```c
pov_vred = fscanf(fpt, "%11d%30[^|]%6d",
    &student.broj_indeksa, student.ime, &student.broj_poena);
```

Broj pristupa $R_u$ pri uspešnom traženju, kako logički narednog tako i slučajno odabranog sloga, iznosi:

$$R_u = 1$$

Kada je reč o broju upoređenja, tu se mogu razlikovati dva slučaja. U prvom, svakom slogu se pridružuje relativna adresa lokacije. Tada je:

$$U_u = 1$$

U drugom slučaju se slogu pridružuje adresa baketa. Pošto baket može sadržati do $b$ slogova, broj upoređenja uzima celobrojne vrednosti iz intervala:

$$1 \leq U_u \leq b$$

---

### 11.3.4 Ažuriranje relativne datoteke

Ažuriranje relativne datoteke se vrši u režimu direktne obrade. Upis novog sloga se vrši na sledeći način. Prvo se novom slogu pridruži vrednost identifikatora (relativna adresa). Zatim se slog upisuje u datoteku, ako u baketu postoji slobodna lokacija. Pre upisa novog sloga u datoteku, eventualno se vrši provera da li slog sa takvom vrednošću ključa postoji. Ta provera može tražiti da se primeni linearno traženje.

**Brisanje** sloga se u relativnoj datoteci može vršiti na dva načina. Jedan koristi usluge metode pristupa, a kod drugog se sprovodi pod potpunom kontrolom programa. U oba slučaja brisanje je **logičko**. Jedino u drugom slučaju, statusno polje mora biti sadržano u opisu sloga. Brisanje pod kontrolom programa se koristi kada je $b > 1$.

Ako se za brisanje koriste usluge metode pristupa, tada se nakon definisanja vrednosti identifikatora daje nalog metodi pristupa da to i sprovede. U slučaju brisanja pod potpunom kontrolom programa, prvo se sadržaj adresiranog baketa pročita, pa se, nakon provere vrednosti ključa i izmene sadržaja statusnog polja sloga, baket ponovo upisuje u datoteku.

#### Brisanje u Cobolu

Ako se u programu, pisanom u Cobolu, brisanje vrši korišćenjem usluga metode pristupa, tada se, nakon postavljanja vrednosti identifikatora u `ime_promenljive`, izdaje naredba:

```
DELETE ime_datoteke RECORD.
```

Nakon toga relativna metoda pristupa tretira lokaciju kao inicijalno praznu. U slučaju brisanja pod kontrolom programa, nakon izmene sadržaja statusnog polja, izdaje se naredba:

```
REWRITE ime_sloga.
```

Ovako izbrisan slog, metoda pristupa tretira kao aktuelan.

---

### 11.3.5 Ocena karakteristika relativne datoteke

Relativna datoteka se odlikuje efikasnijim traženjem logički narednog sloga nego serijska datoteka i manje efikasnim traženjem logički narednog sloga nego sekvencijalna datoteka. Traženje slučajno odabranog sloga je veoma efikasno. I za traženje logički narednog i za traženje slučajno odabranog sloga, potreban je samo **jedan pristup datoteci**. Naravno, u oba slučaja je potrebno izvršiti i jedno traženje u tabeli identifikatora. Tabela identifikatora je, često dovoljno mala, tako da se permanentno nalazi u operativnoj memoriji. Međutim, uvođenjem pojma relativne adrese lokacije kao identifikatora, rešava se jedino problem čvrste povezanosti slogova datoteke sa karakteristikama memorijskog uređaja. Odsustvo logičke veze između vrednosti identifikatora i sadržaja sloga predstavlja prepreku za šire korišćenje relativnih datoteka u praksi.

Saglasno tome, spontano se nameće ideja da se, u svojstvu identifikatora, iskoristi ključ tipa sloga tako da numerička vrednost ključa predstavlja relativnu adresu lokacije, u koju treba smestiti slog. Znači, $A_i = k(S_i)$, $i = 1, ..., N$. Nažalost, direktna primena ove ideje, često, dovodi do izuzetno neefikasnog korišćenja memorijskog prostora, jer se mora predvideti po jedna lokacija za svaku od mogućih vrednosti ključa.

#### Primer 11.10

Da bi se relativna datoteka, u kojoj ključ uzima vrednosti iz skupa prvih 99 prirodnih brojeva, realizovala tako da važi $A_i = k(S_i)$, $i, j \in \{1, ..., N\}$, potrebno je rezervisati 99 lokacija, jer ključ može uzeti svaku vrednost iz skupa $\{1, ..., 99\}$. Ako je $N = 13$, tada koeficijent korišćenja memorijskog prostora iznosi $k \approx 0{,}13$.

#### Primer 11.11

Vrednosti obeležja *MBR* (matični broj građana) su trinaestocifreni brojevi. Srbija ima oko 10 miliona stanovnika. Ako bi se obeležje *MBR* upotrebilo kao identifikator, iskorišćenje memorijskog prostora relativne datoteke bi bilo $10^{-6}$. Tek svaka milionita lokacija bi bila popunjena nekim slogom.

Neka je dat tip sloga `STAN(OZU, KBR, BRS, POS)`, gde je `OZU` oznaka ulice sa `dom(OZU) = {1, ..., U}`, `KBR` kućni broj sa `dom(KBR) = {1, ..., B}`, `BRS` broj stana sa `dom(BRS) = {1, ..., S}` i `POS` ostali podaci o stanu. Ključ tipa sloga je `{OZU, KBR, BRS}`. Relativna adresa $A$ lokacije u koju su smešteni podaci o stanu broj $s$, zgrade sa kućnim brojem $b$, u ulici sa oznakom $u$, izračunava se kao:

$$A = s + (b - 1)S + (u - 1)SB$$

a za datoteku se mora rezervisati $SBU$ lokacija.

Neka je u gradu sa 300000 stanovnika i 100000 stanova, $U = 2000$, $B = 100$ i $S = 50$, tada je za relativnu datoteku potrebno rezervisati $10^7$ lokacija. Iskorišćenje memorijskog prostora datoteke bi bilo $10^{-2}$.

> [!WARNING]
> Korišćenje ključa kao identifikatora u osnovi predstavlja dobru ideju. Međutim, širok opseg mogućih i relativno mali broj aktuelnih vrednosti ključa ograničava direktnu primenu te ideje samo na slučajeve kada aktuelne vrednosti ključa gusto zaposedaju opseg mogućih vrednosti ključa.

Pored navedenih primena, relativna metoda pristupa se može upotrebiti za izgradnju spregnute datoteke. Tu se relativna adresa lokacije logički narednog sloga smešta u polje pokazivača tekućeg sloga. Takođe, relativna metoda pristupa predstavlja osnovu za izgradnju rasutih datoteka sa probabilističkom transformacijom ključa u adresu.

---

## 11.4 Opšte karakteristike rasutih datoteka sa probabilističkom transformacijom

Da bi se prevaziši nedostaci, do kojih dovodi deterministička, uvodi se **probabilistička transformacija** vrednosti ključa u adresu. Postoji veći broj metoda probabilističke transformacije vrednosti ključa u adresu. Pogodnost za primenu svake od njih zavisi od raspodele vrednosti ključa unutar opsega njegovih mogućih vrednosti. Bez obzira na specifičnosti algoritama, sve ove metode imaju za cilj da izvrše što ravnomerniju transformaciju vrednosti ključa u adresu i kompresiju potrebnog adresnog prostora.

Drugim rečima, zadatak metode transformacije je da svaku od postojećih (ne i mogućih) vrednosti ključa pretvori u jedinstvenu adresu lokacije u okviru minimalno potrebnog adresnog prostora. Nažalost, ovako idealno postavljen cilj se u praksi veoma retko postiže.

U opštem slučaju, probabilistička transformacija ključa u adresu realizuje se u **četiri koraka**. To su, redom:

1. **Pretvaranje nenumeričke u numeričku vrednost ključa** - potrebno jedino ako su vrednosti ključa nenumeričke.
2. **Pretvaranje numeričke vrednosti ključa u pseudoslučajan broj** u opseg dozvoljenih vrednosti relativne adrese i
3. **Prevođenje relativne u mašinsku adresu.**

Prvi tri koraka, najčešće, predstavljaju zadatak programa, a četvrti predstavlja zadatak relativne metode pristupa. Prevođenje nenumeričke u numeričku vrednost ključa je potrebno jedino ako su vrednosti ključa nenumeričke. Pretvaranje numeričke vrednosti ključa u pseudoslučajan broj realizuje se primenom neke od formula za generisanje pseudoslučajnih brojeva. Pošto dobijeni pseudoslučajan broj može imati vrednost veću od broja lokacija dodeljenih datoteci, mora se izvršiti njegova korekcija. Korekcija se vrši množenjem pseudoslučajnog broja odgovarajućim faktorom, manjim od jedinice. Rezultat primene ova tri koraka predstavlja relativnu adresu.

Na ovom mestu će biti ukratko opisane tri metode probabilističke transformacije ključa u adresu, koje su u praksi stekle veću popularnost.

---

### Metoda ostatka pri deljenju

Značajnu primenu u praksi našla je metoda kod koje se relativna adresa $A$ dobija kao celobrojni ostatak deljenja vrednosti ključa $k(S)$ nekim brojem $m$:

$$A = 1 + k(S) \pmod{m}$$

Jedinica se dodaje celobrojnom ostatku deljenja kako bi relativna adresa uzimala vrednosti iz skupa $\{1, 2, ..., B\}$. Saglasno tome, između broja baketa $B$ i broja $m$ važi odnos $m = B$.

To dalje znači da je korekcija pseudoslučajnog broja, pri primeni ove metode nije potrebna, odnosno da pseudoslučajni broj predstavlja relativnu adresu.

Zadatak svake metode probabilističke transformacije, pa i metode ostatka pri deljenju, je da šta ravnomernije, a to znači što slučajnije, pretvori svaku od postojećih vrednosti ključa u adresu. Zbog toga je nepogodno da broj $m$ bude paran broj, jer će se tada za sve neparne vrednosti ključa dobijati i neparne relativne adrese, a za parne vrednosti ključa parne adrese. Broj $m$ takođe ne sme predstavljati stepen osnove brojnog sistema, jer tada relativnu adresu predstavljaju cifre najmanje težine ključa, bez obzira na vrednosti ostalih cifara. Najpogodnije je da $m$ predstavlja prost broj ili neparan broj sa relativno velikim prostim činiocima.

#### Primer 11.13

Ako ključ datoteke uzima vrednosti iz skupa $\{1, ..., 99\}$, a datoteci se dodeli 5 baketa, tada će metoda ostatka pri deljenju, slogu sa vrednošću ključa $k(S) = 07$ pridružiti relativnu adresu 3, a slogu sa vrednošću ključa $k(S) = 25$, relativnu adresu 1.

> [!TIP]
> Provera: $A = 1 + 07 \pmod{5} = 1 + 2 = 3$. Za $k(S)=25$: $A = 1 + 25 \pmod{5} = 1 + 0 = 1$.

Metoda ostatka pri deljenju je veoma pogodna za primenu u slučajevima kada se vrednosti ključa javljaju u takozvanim paketima. To znači da su pojedini intervali unutar opsega dozvoljenih vrednosti gusto zaposednuti aktuelnim vrednostima ključa, dok se između njih nalaze intervali sa neaktuelnim vrednostima ključa. U tom slučaju, metoda ostatka pri deljenju dodeljuje slogovima sa sukcesivnim vrednostima ključa iz paketa, adrese fizički susednih baketa, što rezultuje u ravnomernom zaposedanju baketa.

---

### Metoda centralnih cifara kvadrata ključa

Prema ovoj metodi se vrednost ključa diže na kvadrat, a zatim se uzima onoliki broj centralnih cifara kvadrata vrednosti ključa koliko pozicija treba da sadrži relativna adresa. Ove centralne cifre se, po potrebi, mnoze nekim brojem manjim od jedan, kako bi relativna adresa uzimala vrednost iz minimalno potrebnog intervala vrednosti, koji odgovara broju baketa dodeljenih datoteci.

Neka je $k(S) \in \{0, 1, ..., v^p - 1\}$. Tada se vrednost ključa može predstaviti u polinomijalnom obliku kao:

$$k(S) = \sum_{i=0}^{p-1} a_i v^i, \quad a_i \in \{0, 1, ..., v - 1\}$$

Relativna adresa $A$ uzima vrednosti iz skupa $\{1, ..., B\}$, gde je $B = kv^n$ broj baketa, $n = \lceil \log_v B \rceil$ i $1 \leq n \leq p$. Kvadrat vrednosti ključa se može predstaviti u polinomijalnom obliku kao:

$$(k(S))^2 = \sum_{i=0}^{2p-1} c_i v^i, \quad a_i \in \{0, 1, ..., v - 1\}$$

Iz niza $(c_{2n-1}, c_{2n-2}, ..., c_1, c_0)$ izdvaja se niz:

$$(c_{t+n-1}, c_{t+n-2}, ..., c_{t+1}, c_t)$$

gde je $t = \lfloor p - n/2 \rfloor$. Elementi ovog niza predstavljaju cifre pseudoslučajnog broja $T$, te je:

$$T = \sum_{i=0}^{n-1} c_{t+i} v^i$$

Relativna adresa $A$ se izračunava na sledeći način:

$$A = \left\lfloor \frac{r}{v^n} Q \right\rfloor + 1$$

gde se $r$ dobija iz: $r = \lfloor k/v^t \rfloor \mod v^n$

#### Algoritam transformacije metodom srednjih cifara kvadrata

```
PROCES transformacija (U(k(S), p, Q), I(r), UI())
(*
U  - Q je broj baketa rasute datoteke, p je maksimalni broj cifara vrednosti k(S).
I  - r je relativna adresa matičnog baketa
*)
POČETAK PROCESA transformacija
  POSTAVI n ← ⌈log_v Q⌉         (*broj pozicija relativne adrese*)
  POSTAVI t ← ⌊p - n/2⌋
  POSTAVI k ← (k(S))²
  POSTAVI r ← ⌊k/v^t⌋ mod v^n
  POSTAVI r ← ⌊rQ/v^n⌋ + 1)
KRAJ PROCESA transformacija
```

#### Primer 11.14

U slučaju datoteke iz primera 11.13, $B = 5$, a $v = 10$. Tada je $n = 1$ i $B/v^n = 0{,}5$. Pošto ključ uzima vrednosti iz skupa $\{1, ..., 99\}$, to je $p = 2$, te je $t = 1$.

- Za $k(S) = 07$: $(k(S))^2 = 49$, te je $T = 4$ i $A = 3$.
- Za $k(S) = 25$: $(k(S))^2 = 625$, te je $T = 2$ i $A = 2$.

---

### Metoda preklapanja

Metoda preklapanja je pogodna za primenu kada je broj pozicija $p$ ključa mnogo veći od broja pozicija $n$ relativne adrese u datoteci. Ime je dobila zbog činjenice da se, pri njenoj primeni, cifre ključa premeštaju kao pri savijanju (preklapanju) hartije. Preklapanje se izvodi po osama koje zdesna u levo određuju broj pozicija $n$ relativne adrese, a prema skici na slici 11.5. Na taj način se dobija $\lceil p/n \rceil$ brojeva iste dužine. Sabiranjem ovih brojeva po modulu $v^n$ i njihovim eventualnim množenjem faktorom $k$ ($\leq 1$) u cilju sažimanja, dobija se relativna adresa lokacije, gde je $k = B / v^n$.

Neka je $k(S)$ predstavljeno putem (11.1). Pseudoslučajni broj $T$ se u slučaju metode preklapanja izračunava po formuli:

$$T = \left( \sum_{k=0}^{q} \sum_{i=0}^{n-1} c_r v^i + \sum_{k=1}^{q} \sum_{i=0}^{n-1} c_s v^i \right) \pmod{v^n}$$

gde je $q = \lfloor p/2n \rfloor$, $r = 2kn + i$, $s = 2kn - i - 1$, i odgovarajuća ograničenja za $c_r$ i $c_s$.

Relativna adresa $A$ se i u slučaju metode preklapanja izračunava putem formule (11.3).

#### Primer 11.15

Neka je $k(S) = 768013295$ i $n = 3$. Na slici 11.6 prikazan je efekat primene formule (11.4) za dobijanje pseudoslučajnog broja $T = 373$.

Vizuelno, preklapanje izgleda ovako: broj 768013295 se "presavije" i sabere:

```
7 6 8 | 0 1 3 | 2 9 5
      →  3 1 0  (preokrenuto 8 6 7 → jer se preklapanje vrši)
      +  0 1 3
      +  5 9 2  (preokrenuto 2 9 5)
      = 1373 (mod 10³) = 373
```

---

### 11.4.2 Sinonimi i prekoračioci

Ozbiljan nedostatak svih metoda probabilističke transformacije ključa u adresu predstavlja pojava **sinonima**. Ova pojava se naziva i **kolizijom ključeva**, a nastaje kao posledica činjenice da dve različite vrednosti ključa $k(S_i)$ i $k(S_j)$ mogu transformacijom dobiti istu relativnu adresu, jer je $h(k(S_i)) = h(k(S_j))$.

Metoda probabilističke transformacije vrednosti ključa u adresu deli skup slogova datoteke na disjunktne podskupove. Svim slogovima jednog podskupa dodeljena je adresa istog baketa. Slogovi jednog podskupa predstavljaju jedan **skup sinonima**. Broj ovih podskupova u jednoj rasutoj datoteci, jednak je broju baketa $B$. Pri tome, nekim baketima mogu biti pridruženi i prazni podskupovi skupa slogova datoteke.

#### Primer 11.16

U tabeli na slici 11.7 prikazani su rezultati dodeljivanja relativnih adresa baketa skupu slogova serijske datoteke sa slike 7.1, metodom ostatka pri deljenju. Broj baketa, dodeljenih datoteci, iznosi $B = 5$. Saglasno tabeli, svakom baketu, osim baketa sa relativnom adresom $A = 2$, je dodeljen barem jedan slog. Skup sinonima sa adresom $A = 5$ predstavlja skup $\{S_1, S_5, S_6, S_7, S_{12}\}$.

| | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
| $A$ | 5 | 3 | 4 | 1 | 5 | 5 | 5 | 4 | 4 | 3 | 4 | 5 | 1 |

Svakom slogu se transformacijom pridružuje adresa jednog baketa. Taj baket će se u daljem tekstu nazivati **matičnim**. Slogovi se smeštaju u svoje matične bakete dok se kapacitet baketa ne popuni. Slogovi, smešteni u svoj matični baket, nazivaju se **primarnim**. Pošto se baket popuni, svaki naredni slog sinonim smešta se u neku drugu lokaciju. Takvi slogovi se nazivaju **prekoračiocima**.

> [!IMPORTANT]
> **Matični baket** = baket čija adresa je rezultat transformacije za dati slog.
> **Primarni slog** = slog smešten u svoj matični baket.
> **Prekoračilac** = slog sinonim koji se ne može smestiti u matični baket jer je ovaj popunjen.

Pojava prekoračilaca je nepoželjna, jer zahteva pronalaženje slobodne lokacije za smeštaj tog sloga i dovodi do produženja vremena pristupa pri kasnijem traženju tog sloga. Broj prekoračilaca će biti to manji što su slogovi ravnomernije raspodeljeni po baketima.

Verovatnoća pojave sinonima zavisi od raspodele vrednosti ključa unutar opsega dozvoljenih vrednosti, od odabrane metode transformacije i faktora popunjenosti memorijskog prostora. Od raspodele vrednosti ključa zavisi koja je od metoda transformacije, u posmatranom slučaju, biti najpogodnija, tj. dati najravnomerniju raspodelu slogova po baketima.

---

### Faktor popunjenosti

Intuitivno se može naslutiti da će, bez obzira na metodu transformacije, broj sinonima biti to manji što je manji odnos između broja slogova $N$ i broja lokacija $Q = Bb$ dodeljenih datoteci. Odnos:

$$q = N/Q$$

između ove dve veličine naziva se **faktorom popunjenosti**. Pri tome je $0 < q \leq 1$.

Izbor faktora popunjenosti $q$ ostvaruje veliki uticaj na karakteristike rasuto organizovane datoteke. Ako je $q$ malo, verovatnoća pojave više slogova u jednom skupu sinonima je takođe mala, ali je malo i iskorišćenje memorijskog prostora. Ako je $q$ veliko (blizu jedinice), iskorišćenje memorijskog prostora je dobro, ali je velika i verovatnoća pojave sinonima. **U praksi se bira $q \leq 0{,}8$.**

#### Primer 11.17

U graničnom slučaju, kada je $Q = v^p$, za faktor baketiranja $b = 1$, metoda ostatka pri deljenju predstavlja injektivnu funkciju. Međutim, to je slučaj trivijalne transformacije kod koje vrednost ključa predstavlja relativnu adresu.

#### Primer 11.18

Ako se pretpostavi da je, u slučaju rasute datoteke iz primera 11.16, $b = 3$, tada je $Q = 15$ i $q \approx 0{,}87$. Za $q \approx 0{,}62$, pri istom faktoru baketiranja se dobija $B = 7$. U tabeli na slici 11.8 su prikazani rezultati transformacije vrednosti ključa u adresu metodom ostatka pri deljenju za $B = 7$.

| | $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ | $S_9$ | $S_{10}$ | $S_{11}$ | $S_{12}$ | $S_{13}$ |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| $k(S_i)$ | 34 | 07 | 03 | 15 | 19 | 29 | 64 | 43 | 23 | 27 | 13 | 49 | 25 |
| $A$ | 7 | 1 | 4 | 2 | 6 | 2 | 2 | 2 | 3 | 7 | 7 | 1 | 5 |

Upoređivanje sadržaja tabela na slikama 11.7 i 11.8 ukazuje da je raspodela slogova po baketima ravnomernija pri manjem faktoru popunjenosti. Naravno, ovaj primer ukazuje samo na to kakvo ponašanje slučajne veličine $\bar{s}$, gde je $\bar{s}$ broj sinonima pridruženih transformacijom jednom baketu datoteke, treba očekivati pri smanjenju faktora popunjenosti $q$.

---

### Faktor baketiranja

Nužnost ekonomičnog korišćenja memorijskog prostora dovodi do kompromisnih opredeljenja pri izboru faktora popunjenosti $q$, što rezultuje i u pojavi sinonima i u pojavi slogova prekoračilaca. **Očekivani broj prekoračilaca po jednom baketu**, pri datom faktoru popunjenosti $q$, zavisi od veličine faktora baketiranja $b$.

Ako se pretpostavi da je verovatnoća dodele svake od raspoloživih adresa svakom slogu datoteke ista i da to dodeljivanje adresa predstavlja međusobno nezavisne događaje, tada verovatnoća pojave prekoračilaca opada sa porastom faktora baketiranja $b$. U graničnom slučaju, kada je $b \geq N$, broj prekoračilaca je nula. Međutim, tada se gubi mogućnost direktnog pristupa slogovima, jer se svi nalaze u jednom baketu. Za $b < N$, verovatnoća pojave prekoračilaca je različita od nule, ali sa smanjenjem faktora baketiranja raste preciznost određivanja verovatne adrese lokacije slučajno odabranog sloga, pri traženju.

Veliki faktori baketiranja dovode do dugih vremena razmene podataka između operativne i eksterne memorije, a takođe zahtevaju rezervisanje velikog bafera u operativnoj memoriji. U praksi se retko koriste veći baket faktori od $10$, te pojava prekoračilaca predstavlja neminovnost.

---

### 11.4.3 Očekivani broj sinonima i prekoračilaca

Transformacija vrednosti ključa u adresu predstavlja seriju od $N$ nezavisnih eksperimenata. Verovatnoća da se svakom od $N$ slogova datoteke dodeli jedna od $B$ adresa baketa je, u svakom eksperimentu, ista. Metoda transformacije deli skup od $N$ slogova na $B$ disjunktnih podskupova. Slogovi u istom podskupu nazivaju se **sinonimima**. Broj slogova u jednom podskupu predstavlja slučajnu veličinu, te verovatnoća $P(i)$ da neki podskup sadrži $i$ ($= \bar{s}$) slogova iznosi:

$$P(i) = \binom{N}{i} \left(\frac{1}{B}\right)^i \left(1 - \frac{1}{B}\right)^{N-i}$$

Za velike vrednosti $N$ i $B$, koje su tipične za realne datoteke, verovatnoća $1/B$ postaje veoma mala (teži nuli), te za slučaj konstantnog odnosa $N/B$, binomna raspodela prelazi u **Poissonovu**, a $P(i)$ postaje:

$$P(i) = \frac{(qb)^i}{i!} e^{-qb}$$

gde je $qb = N/B = c^{lo}$.

Broj slogova $\bar{s}$ u jednom skupu sinonima predstavlja slučajnu veličinu, koja uzima vrednosti iz skupa $\{0, 1, ..., N\}$. **Očekivana vrednost** $\bar{s}$ broja slogova u jednom skupu iznosi:

$$\bar{s} = \sum_{i=0}^{N} iP(i)$$

Zamenom (11.5) u (11.6) dobija se:

$$\boxed{\bar{s} = qb}$$

> [!IMPORTANT]
> Očekivani broj sinonima po jednom baketu iznosi $\bar{s} = qb$, što je proizvod faktora popunjenosti i faktora baketiranja.

Broj prekoračilaca iz jednog baketa, kao slučajna veličina, uzima vrednosti iz skupa $\{0, 1, ..., N - b\}$. Pod pretpostavkom da se u bakete smeštaju samo matični slogovi, očekivani broj prekoračilaca $\bar{L}$ iz jednog baketa dat je matematičkim očekivanjem:

$$\bar{L} = \sum_{i=b+1}^{N} (i - b) P(i)$$

Pošto brojevi prekoračilaca iz svakog od $B$ baketa predstavljaju nezavisne slučajne veličine, očekivani broj prekoračilaca iz svih $B$ baketa datoteke iznosi:

$$\overline{LB} = B \sum_{i=b+1}^{N} (i - b) P(i)$$

a očekivani broj prekoračilaca po jednom od $N$ slogova iznosi:

$$\frac{\overline{LB}}{N} = \frac{1}{qb} \sum_{i=b+1}^{N} (i - b) P(i)$$

Na slici 11.9 nacrtane su krive $\overline{LB}/N = f(q)$ za razne vrednosti $b$. Posmatranjem ovih krivih može se zaključiti da očekivani broj prekoračilaca raste sa porastom $q$ i opada sa porastom $b$.

#### Primer 11.19

Za $q = 0{,}87$ i $b = 3$, očekivani broj sinonima po jednom baketu datoteke iznosi $\bar{s} = 2{,}61$. Za $N = 10000$, ukupni očekivani broj prekoračilaca iz datoteke iznosi, saglasno slici 11.9, $\overline{LB} = 1800$.

---

### 11.4.4 Postupci za smeštaj prekoračilaca

Za rešavanje problema smeštanja prekoračilaca postoje **dva osnovna postupka**:

1. **Datoteka sa jedinstvenim adresnim prostorom** - prekoračioci se smeštaju u neku od slobodnih lokacija unutar tog jedinstvenog adresnog prostora.
2. **Datoteka sa dve zone** - primarnu i zonu prekoračenja. Prekoračioci se smeštaju u neku od slobodnih lokacija unutar zone prekoračenja.

Svaki od ovih osnovnih postupaka se deli na nekoliko varijanti, zavisno od metode određivanja adrese baketa u kojem će se tražiti slobodna lokacija za smeštaj prekoračioca i, zavisno od činjenice da li se svi sinonimi jednog skupa međusobno sprežu ili ne.

**U rasute datoteke sa jedinstvenim adresnim prostorom spadaju:**
- datoteka sa linearnim traženjem lokacije za smeštaj prekoračilaca,
- datoteka sa slučajnim traženjem lokacije za smeštaj prekoračilaca,
- datoteka sa sprezanjem prekoračilaca (u jedinstvenom adresnom prostoru).

**U rasute datoteke sa zonom prekoračenja spadaju:**
- datoteka sa sprezanjem prekoračilaca u zoni prekoračenja i
- datoteka sa serijskom zonom prekoračenja.

---

### 11.4.5 Opšte napomene o projektovanju i formiranju rasutih datoteka sa probabilističkom transformacijom

Pri projektovanju rasute datoteke sa probabilističkom transformacijom vrednosti ključa u adresu utvrđuje se:

- faktor popunjenosti memorijskog prostora $q$,
- faktor baketiranja $b$,
- metoda transformacije vrednosti ključa u adresu i
- postupak za smeštanje prekoračilaca.

Ova opredeljenja donose se s obzirom na raspodelu vrednosti ključa unutar opsega mogućnih vrednosti, veličinu sloga, obim i karakter ažuriranja datoteke, zadati srednji broj pristupa datoteci pri uspešnom i neuspešnom traženju.

Na osnovu utvrđenih vrednosti za $q$ i $b$, određuje se broj baketa putem formule:

$$B = \left\lceil \frac{N}{bq} \right\rceil$$

Mada sistemi za upravljanje bazama podataka, po pravilu, poseduju metodu pristupa za rasute datoteke, softver za upravljanje datotekama je poseduje retko. Zbog toga se aktivnosti formiranja rasuto organizovane datoteke realizuju delom u okviru aplikativnog programa, a delom uz pomoć relativne metode pristupa. Transformacija vrednosti ključa u adresu, smeštanje prekoračilaca, formiranje baketa od više slogova i izdvajanje slogova iz baketa predstavljaju zadatke aplikativnog programa. Upis i čitanje baketa iz datoteke predstavljaju zadatke relativne metode pristupa. Čitav postupak formiranja rasute datoteke se odvija u režimu direktne obrade.

Pošto se rasuta datoteka realizuje kao relativna, preporučljivo je inicijalno formirati praznu datoteku. Pri tome se mogu, po potrebi, popuniti specijalnim sadržajima statusna polja lokacija, polja ključa i polja pokazivača. Razlog za formiranje prazne datoteke predstavlja i činjenica da se relativna datoteka prvi put često može otvoriti samo kao izlazna. Ukoliko datoteka sadrži primarnu i zonu prekoračenja, ove dve zone se mogu realizovati kao dve relativne datoteke.

Kod datoteka sa rasutom organizacijom se javlja potreba prepoznavanja slobodnih lokacija unutar baketa. Taj problem se rešava ili putem indeksa slobodnih lokacija i njihovog sprezanja, ili putem sadržaja statusnog polja ili upisom specijalnih znakova u lokaciju. U svojstvu tih specijalnih znakova će se u daljem tekstu koristiti zvezdica `()` u polju ključa.

---

### 11.4.6 Opšte napomene o traženju u rasutim datotekama sa probabilističkom transformacijom

Traženje logički narednog i traženje slučajno odabranog sloga se, u rasutim datotekama, vrši metodom transformacije argumenta u adresu baketa. Ako se traženi slog ne nađe u matičnom baketu, a uslovi za nastavak traženja postoje, traženje se nastavlja ili linearnom metodom ili ponovnom transformacijom ili praćenjem pokazivača. Generalno, uslovi za nastavak traženja postoje, ako matični baket ima prekoračilaca.

- **Linearna metoda** se primenjuje kod datoteka sa linearnim traženjem i datoteka sa serijskom zonom prekoračenja.
- **Ponovna transformacija** se koristi kod datoteka sa slučajnim traženjem.
- **Praćenje pokazivača** se koristi kod datoteka sa sprezanjem prekoračilaca.

Pri datom faktoru popunjenosti i datom faktoru baketiranja, efikasnost traženja zavisi od primenjenog postupka za smeštaj prekoračilaca.

Očekivani broj pristupa rasutoj datoteci sa velikim brojem slogova $N$ i brojem baketa $B$, bez obzira na postupak za smeštaj prekoračilaca, i pri uspešnom i pri neuspešnom traženju **ne zavisi od broja slogova datoteke** $N$, već samo od parametara $q$ i $b$. Naime, ako se traženi slog nalazi u matičnom baketu, ili matični baket nema prekoračilaca, tada je broj pristupa $R = 1$. Traženje se nastavlja jedino ako matični baket ima prekoračilaca. Očekivani broj prekoračilaca ne zavisi od broja slogova $N$. Naime, pošto je:

$$\sum_{i=0}^{N} P(i) = 1 \quad \text{i} \quad \sum_{i=0}^{N} iP(i) = qb$$

izraz (11.8) se jednostavnim transformacijama pretvara u izraz:

$$\bar{L} = b(q - 1) + \sum_{i=0}^{b} (b - i) P(i)$$

koji očigledno ne zavisi od $N$.

> [!IMPORTANT]
> Ovo je jedna od ključnih prednosti rasutih datoteka: očekivani broj pristupa pri traženju ne zavisi od veličine datoteke $N$, već samo od faktora popunjenosti $q$ i faktora baketiranja $b$. Datoteka sa 100 i datoteka sa 100000 slogova imaju isti očekivani broj pristupa!

---

## 11.5 Rasute datoteke sa linearnim traženjem

Za izgradnju fizičke strukture rasute datoteke sa linearnim traženjem lokacija za smeštaj prekoračilaca, koristi se sledeći postupak dodele adresa lokacija slogovima. Nakon transformacije vrednosti ključa u adresu, slog se smešta u matični baket, ako u njemu postoji slobodna lokacija. Inače, slog se smešta u prvi baket sa slobodnom lokacijom iza svog matičnog baketa. Traženje prve slobodne lokacije može zahtevati veći broj pristupa sukcesivnim baketima. Ako se redni broj baketa, u kojem se traži slobodna lokacija, označi sa $n$ ($n = 1, ..., B - 1$), pri čemu $n$ predstavlja redni broj u odnosu na matični baket kao početak, tada se relativna adresa $A_n$ tog baketa izračunava kao:

$$A_n = 1 + A_{n-1} \pmod{B}$$

gde je $A_0 = h(k(S))$ adresa matičnog baketa.

Treba zapaziti da pri primeni metode linearnog traženja, slog može postati prekoračilac i ako su prekoračioci iz drugih baketa popunili njegov matični baket.

#### Primer 11.20

Korišćenjem tabele sa slike 11.7, dobijena je rasuta datoteka sa linearnim traženjem, prikazana na slici 11.10. Pri tome je $N = 13$, $B = 5$, $b = 3$ i $q = 0{,}87$. Zvezdica u polju ključa ukazuje da je lokacija nezauzeta.

Slogovi sa vrednostima ključa $k(S_7) = 64$ i $k(S_{11}) = 13$, kao prekoračioci iz baketa sa relativnim adresama $A_r = 5$ i $A_r = 4$, respektivno, zauzeli su lokacije u baketu sa relativnom adresom $A_r = 1$. Na taj način je i slog sa vrednošću ključa $k(S_{13}) = 25$, koji pripada baketu sa relativnom adresom $A_r = 1$, postao prekoračilac.

Fizička struktura (slika 11.10):

| Baket | Lokacija 1 | Lokacija 2 | Lokacija 3 |
|---|---|---|---|
| 1 | 15, $p(S_4)$ | 64, $p(S_7)$ | 13, $p(S_{11})$ |
| 2 | 49, $p(S_{12})$ | 25, $p(S_{13})$ | * |
| 3 | 07, $p(S_2)$ | 27, $p(S_{10})$ | * |
| 4 | 03, $p(S_3)$ | 43, $p(S_8)$ | 23, $p(S_9)$ |
| 5 | 34, $p(S_1)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |

---

### 11.5.1 Formiranje rasute datoteke sa linearnim traženjem

U principu, postupak formiranja rasute datoteke sa linearnim traženjem zasnovan je na opštem postupku formiranja rasutih datoteka, opisanom u tački 11.1 i na primeni opisanog postupka dodele adresa lokacija slogovima.

Na slici 11.11 prikazan je pseudokod algoritma formiranja rasute datoteke sa linearnim traženjem. Ovaj algoritam poziva algoritam procesa formiranja prazne datoteke (slika 11.12), i algoritam procesa traženja (slika 11.15). Formiranjem prazne datoteke obezbeđuje se, upisom specijalne oznake u polje ključa svake lokacije, informacija o inicijalno slobodnim lokacijama. Upis slogova se vrši nakon neuspešnog traženja, da bi se, u datoteci, sprečila pojava slogova sa istim vrednostima ključa.

---

### 11.5.2 Traženje u rasutoj datoteci sa linearnim traženjem

U rasutoj datoteci sa linearnim traženjem lokacije za smeštaj prekoračilaca, traženje logički narednog i traženje slučajno odabranog sloga vrši se metodom transformacije argumenta u adresu. Na osnovu rezultata transformacije, pristupa se matičnom baketu. Ako se traženi slog nalazi u matičnom baketu, traženje se završava uspešno. Ako matični baket ne sadrži traženi slog, a sadrži slobodnu lokaciju, traženje se završava neuspešno. Inače se traženje nastavlja linearnom metodom tako, što se adresa baketa, u kojem će se nastaviti traženje, određuje putem formule (11.14). Ponovo, traženje se završava uspešno kada se naiđe na slog sa traženom vrednošću ključa. Traženje se završava kao neuspešno, kada se naiđe na baket sa slobodnom lokacijom, ili kada se, saglasno cirkularnom postupku određivanja adresa baketa, ponovo dođe do matičnog baketa.

#### Primer 11.22

Neka je $a = 49$, a traženje se vrši u datoteci prikazanoj na slici 11.10. Relativna adresa matičnog baketa je $A_0 = 5$, $m = 3$, a $l = 5$, te broj pristupa potreban za pronalaženje sloga sa vrednošću ključa $k(S_{12}) = 49$, iznosi $R_u = 3$.

Neka je $m$ broj slogova u matičnom baketu, a $l$ broj sukcesivno zauzetih lokacija do prve slobodne lokacije u baketu sa relativnom adresom $A_0 + n$, gde je $A_0 = h(a)$, a $n \in \{1, 2, ..., B - 1\}$, tada se relativna adresa $A_n$ tog baketa izračunava kao (11.14).

Broj pristupa $R_u$ pri uspešnom traženju ili logički narednog ili slučajno odabranog sloga, uzima celobrojne vrednosti iz intervala:

$$1 \leq R_u \leq 1 + \lceil l/b \rceil$$

gde je $R_u = 1$ za $m < b$ i $1 \leq R_u \leq 1 + \lceil l/b \rceil$ za $m = b$.

Pri neuspešnom traženju, broj pristupa datoteci dat je sledećom formulom:

$$R_n = \begin{cases} 1 & \text{za } m < b \\ 1 + \lceil l/b \rceil & \text{za } m = b \end{cases}$$

Pri vrednostima faktora popunjenosti $q$ bliskim jedinici može doći do smeštanja nekog od prekoračilaca u baket koji prethodi s obzirom na smer linearnog traženja, njegovom matičnom baketu. Tada maksimalni broj pristupa pri traženju jednog sloga teži vrednosti $R = B$.

U datoteci sa malim brojem slogova, očekivani broj pristupa pri uspešnom traženju jednog sloga, ili pri neuspešnom traženju, može se izračunavati primenom formula (11.11) i (11.12), respektivno.

#### Primer 11.23

Primenom formula (11.11) i (11.12), u slučaju datoteke sa slike 11.10 dobija se $\bar{R}_u \approx 1{,}46$ i $\bar{R}_n = 2{,}2$.

---

### 11.5.3 Ažuriranje rasute datoteke sa linearnim traženjem

**Upis novog sloga** u rasutu datoteku sa linearnim traženjem vrši se u lokaciju na kojoj se zaustavilo neuspešno traženje. Broj pristupa, potreban za upis jednog novog sloga iznosi:

$$R_i = R_n + 1$$

gde je $R_n$ dato formulom (11.16).

**Brisanje sloga** iz datoteke sa linearnim traženjem može biti ili logičko ili fizičko. Kod logičkog brisanja potrebno je koristiti **tri vrednosti statusne oznake**: jednu, recimo $0$, za inicijalno slobodnu lokaciju; drugu, recimo $1$, za lokaciju koja sadrži aktuelni slog; i treću, recimo $9$, za lokaciju koja sadrži neaktuelni slog. Na taj način, nailaskom na lokaciju sa neaktuelnim sadržajem, traženje se ne prekida.

Međutim, logičko brisanje dovodi do degradacije performansi traženja, jer, vremenom, cela datoteka prelazi u kontinualan niz zauzetih i oslobođenih lokacija, tako da se broj pristupa pri neuspešnom traženju približava svojoj maksimalnoj vrednosti $R_n^{max} = B$, a raste i broj pristupa pri uspešnom traženju. Opisani problemi logičkog brisanja rešavaju se povremenom reorganizacijom datoteke. Pri reorganizaciji se iz datoteke eliminišu logički izbrisani slogovi.

Broj pristupa, potreban za logičko brisanje jednog sloga iznosi:

$$R_d = R_u + 1$$

gde je $R_u$ dato formulom (11.15).

**Fizičko brisanje** se realizuje tako što se u lokaciju sloga, koji se briše, prenosi sadržaj prve naredne lokacije sa većom adresom. Iz lokacije sa većom, u lokaciju sa manjom adresom, pomeraju se slogovi koji se nalaze između lokacije, čiji sadržaj se briše, i prve prazne lokacije. U poslednju lokaciju posmatranog niza sukcesivno zauzetih lokacija upisuje se niz specijalnih znakova, koji ukazuju da je lokacija inicijalno prazna.

Pri tom pomeranju se mora voditi računa da se slog ne prenese u baket iza svog matičnog baketa (s obzirom na smer traženja), jer se tada više neće moći pronaći (sem u slučaju da je $q = 1$). Ovo pomeranje predstavlja svojevrsnu dinamičku reorganizaciju datoteke, jer dovodi prekoračioca bliže svom matičnom baketu i oslobađa memorijski prostor.

---

### 11.5.4 Analiza karakteristika datoteke sa linearnim traženjem

Iskustva, stečena primenom rasutih datoteka sa linearnim traženjem lokacije za smeštaj prekoračilaca, pokazuju da je postupak pogodan za datoteke sa faktorom popunjenosti $q < 0{,}7$. Pri većim faktorima popunjenosti dolazi do čestih dugotrajnih traženja. Razlog nastanka ove pojave leži u fenomenu stvaranja dugih nizova zauzetih lokacija.

#### Primer 11.25

Na slici 11.22 je prikazana mala datoteka sa $N = 7$ slogova, $B = 13$ baketa i faktorom baketiranja $b = 1$. Naredi, osim slog će biti upisan u jedan od šest slobodnih baketa nije ista za svaki baket. Na primer, novi slog će biti smešten u baket sa adresom $A_{12}$, ako je $A_0 \leq h(k(S)) \leq A_{12}$, a u baket sa adresom $A_{13}$ samo ako je $h(k(S)) = A_{13}$. Ako je verovatnoća transformacije svake od vrednosti ključa u svaku od 13 adresa ista, tada je verovatnoća smeštanja novog sloga u baket sa adresom $A_{12}$ četiri puta veća od verovatnosti njegovog smeštanja u baket sa adresom $A_{13}$. Zbog toga, dugi nizovi sukcesivno zauzetih baketa rastu veoma brzo. Do još gore situacije dolazi ako se dva niza spoje.

Fenomen stvaranja dugih nizova zauzetih lokacija naziva se **nagomilavanjem** (clustering, pile-up). Postoje dva osnovna postupka zaštite od efekta nagomilavanja. Prvi je da se koriste faktori popunjenosti $q < 0{,}7$.

Drugi postupak zaštite od efekta nagomilavanja je da se traženje slobodne lokacije ne vrši povećavanjem adrese baketa za jedan, već za neku konstantu $k > 1$. Konstanta $k$ treba da bude prirodan broj relativno prost u odnosu na $B$, da bi se mogao ispitati svaki baket pri traženju slobodne lokacije. Pošto svi prekoračioci iz jednog baketa i dalje prolaze isti put, formirače se nizovi udaljeni $k$ baketa jedan od drugog, čime se smanjuje verovatnoća njihovog spajanja.

> [!WARNING]
> **Nagomilavanje** (clustering) je glavni problem datoteka sa linearnim traženjem. Dugački nizovi zauzetih lokacija se samo povećavaju jer novi slogovi imaju veću verovatnoću da padnu na kraj dugačkog niza. Zato se ove datoteke koriste samo za $q < 0{,}7$.

---

### 11.5.5 Rasute datoteke sa slučajnim traženjem

U rasutim datotekama sa slučajnim traženjem lokacije za smeštaj prekoračilaca, postupak traženja slobodne lokacije je zasnovan na stvaranju zavisnosti između koraka traženja $k$ i vrednosti ključa sloga. Sada se koriste **dve funkcije** za transformaciju vrednosti ključa u adresu, $h_1(k(S))$ i $h_2(k(S))$. Dovođenjem u zavisnost veličine $k$ od vrednosti ključa putem transformacije $h_2$, obezbeđuje se da svaki prekoračilac iz istog baketa prelazi drugi put pri traženju slobodne lokacije. Na taj način se izbegava nagomilavanje.

Adresa $n$-tog baketa, u odnosu na matični, u kojem se traži slobodna lokacija, izračunava se po formuli:

$$A_n = \begin{cases} A_{n-1} + h_2(k(S)) & \text{za } A_{n-1} + h_2(k(S)) \leq B \\ A_{n-1} + h_2(k(S)) - B & \text{za } A_{n-1} + h_2(k(S)) > B \end{cases}$$

gde je $A_0 = h_1(k(S))$.

Dok transformacija $h_1$ proizvodi vrednosti iz segmenta $[1, B]$, transformacija $h_2$ mora biti relativno prost u odnosu na $B$. Ako je $h_1(k(S)) = 1 + k(S) \pmod{B}$, gde je $B$ prost broj, tada se za drugu transformaciju može izabrati $h_2(k(S)) = 1 + k(S) \pmod{B - 1}$, ili pošto je za $B$ neparan broj, $B - 1$ parno, $h_2(k(S)) = 1 + k(S) \pmod{B - 2}$.

#### Primer 11.27

U datoteci na slici 11.10, slogovi sa vrednostima ključa $k(S_7) = 64$ i $k(S_{12}) = 49$ predstavljaju prekoračioce iz baketa sa relativnom adresom 5. Ako je:

$$h_2(k(S)) = 1 + k(S) \pmod{4}$$

tada bi se, na osnovu (11.17), slobodna lokacija za slog sa vrednošću ključa $k(S_7) = 64$ tražila, redom, u baketima sa relativnim adresama 1, 2, 3, 4. Za slog sa vrednošću ključa $k(S_{12}) = 49$, slobodna lokacija bi se tražila redom u baketima sa relativnim adresama 2, 4, 1, 3.

---

### 11.5.6 Ocena karakteristika rasutih datoteka sa otvorenim adresiranjem

Datoteke sa linearnim i datoteke sa slučajnim traženjem lokacije za smeštaj prekoračilaca se jednim imenom nazivaju **rasutim datotekama sa otvorenim adresiranjem**. Pogodne su za primenu pri faktorima popunjenosti $q$ čija vrednost ne prelazi $0{,}7$.

Slučajno traženje rešava problem pojave nagomilavanja samo u slučajevima kada se iz nekoliko bliskih baketa javlja veći broj prekoračilaca. Primena ovih datoteka je ograničena na slučajeve kada je čestalost ažuriranja datoteke relativno mala. U suprotnom, inicijalni faktor popunjenosti mora biti ispod granice od $q = 0{,}7$.

Postoje tri osnovna razloga za nagli rast broja pristupa pri uspešnom, a naročito pri neuspešnom traženju, u slučajevima kada $q$ raste preko vrednosti $0{,}7$. To su:

- traženje se vrši i u baketima koji ne sadrže slogove iz skupa sinonima traženog sloga,
- neuspešno traženje se zaustavlja tek po dolasku do slobodne lokacije i
- prekoračioci iz jednih baketa izazivaju pojavu prekoračilaca iz drugih baketa.

Ova dva nedostatka izbegavaju se izgradnjom rasutih datoteka sa sprezanjem u primarnoj zoni, a sva tri izbegavanjem rasutih datoteka sa sprezanjem u zoni prekoračenja.

---

## 11.6 Rasute datoteke sa sprezanjem u primarnoj zoni

Da bi se izbegla prva dva nedostatka rasutih datoteka sa otvorenim adresiranjem, uvodi se **sprezanje**. Putem pokazivača se sprežu svi slogovi jednog skupa sinonima, bez obzira da li se nalaze u matičnom ili nekom drugom baketu. U tom cilju, lokacija za smeštaj sloga se proširuje jednim poljem pokazivača. To polje sadrži adresu lokacije u koju je smešten naredni slog istog skupa sinonima.

Svaki baket se snabdeva **zaglavljem**, koje sadrži:

- polje pokazivača $u$ za smeštaj adrese lokacije prvog sloga iz skupa sinonima baketa,
- polje pokazivača $b$ za smeštaj adrese prvog prethodnog baketa sa slobodnom lokacijom,
- polje pokazivača $n$ za smeštaj adrese prvog narednog baketa sa slobodnom lokacijom i
- polje $e$, koje sadrži broj slobodnih lokacija baketa.

Baketi sa slobodnim lokacijama su **međusobno dvostruko spregnuti**. Takođe, fizička struktura datoteke je snabdevena jednom malom pomoćnom strukturom podataka. To je indeks slobodnih baketa $E$, koji sadrži adresu prvog baketa sa slobodnom lokacijom.

#### Primer 11.28

Na slici 11.24 prikazana je rasuta datoteka sa sprezanjem u primarnoj zoni, koja sadrži $N = 13$ slogova smeštenih u $B = 5$ baketa. Faktor baketiranja je $b = 3$. Datoteka sadrži iste slogove kao i rasuta datoteka sa linearnim traženjem na slici 11.10. Slobodne lokacije sadrže zvezdicu u polju ključa.

Treba naglasiti da je ista raspodela prekoračilaca po baketima u obe datoteke posledica usvojenog hronološkog redosleda nastanka slogova i raspodele aktuelnih vrednosti ključa u opsegu mogućih vrednosti ključa. U opštem slučaju, raspodele prekoračilaca po baketima u ove dve vrste rasutih datoteka se razlikuju, jer se u rasutoj datoteci sa sprezanjem prekoračioci smeštaju u baket čija adresa se nalazi u pokazivaču $E$, bez obzira na adresu njihovog matičnog baketa.

---

### 11.6.1 Formiranje rasute datoteke sa sprezanjem u primarnoj zoni

Pored primene opštih principa formiranja rasutih datoteka i opisanog postupka dodele adresa lokacija prekoračiocima, postupak formiranja rasute datoteke sa sprezanjem u primarnoj zoni poseduje i određene specifičnosti.

Prvi korak postupka formiranja rasute datoteke sa sprezanjem u primarnoj zoni predstavlja formiranje prazne liste sa lancem dvostruko spregnutih baketa. Pri tome, u matičnim baketima pokazivači $u$ sadrže `*` kao oznaku kraja, a polje $e$ sadrži vrednost faktora baketiranja $b$.

Pri punjenju datoteke, slogovi se smeštaju u matične bakete, dok se ovi ne popune, a zatim, kao prekoračioci, u baket čiju adresu sadrži indeks slobodnih lokacija $E$. Svi slogovi jednog skupa sinonima se međusobno sprežu tako, što se adresa lokacije novog sloga smešta u polje pokazivača hronološki prethodnog sloga. Dotadašnji sadržaj polja pokazivača u matičnom baketu smešta se u polje pokazivača novog sloga. Adresa lokacije hronološki prvog sloga skupa sinonima smešta se u polje pokazivača u matičnom baketu, bez obzira gde je slog upisan.

Pri upisu novog sloga u baket, smanjuje se sadržaj polja $e$ za jedan. Kada polje brojača nezauzetih lokacija $e$ dobije vrednost nula, baket se isključuje iz lanca nezauzetih baketa. Ako je taj baket, do tada, predstavljao prvi nezauzeti baket, njegov pokazivač ka narednom slobodnom baketu se prenosi u indeks slobodnih baketa $E$. Ažuriranje lanca dvostruko spregnute datoteke.

---

### 11.6.2 Traženje u rasutoj datoteci sa sprezanjem u primarnoj zoni

Traženje sloga u datoteci sa sprezanjem u primarnoj zoni vrši se tako što se, na osnovu transformacije argumenta u adresu pristupa matičnom baketu. Polje $u$ zaglavlja matičnog baketa sadrži adresu lokacije prvog sloga iz skupa sinonima, tako da se traženje nastavlja praćenjem pokazivača. Nailaskom na slog sa traženom vrednošću ključa, traženje se završava uspešno. Kriterijum završetka neuspešnog traženja predstavlja dolazak do oznake kraja lanca sinonima.

Broj pristupa $R_u$ pri uspešnom traženju jednog sloga uzima celobrojne vrednosti iz intervala $[1, 1 + \bar{s}]$, odnosno:

$$1 \leq R_u \leq 1 + \bar{s}$$

gde je $\bar{s}$ broj slogova u skupu sinonima ($0 \leq \bar{s} \leq N$).

Gornja granica broja pristupa $R_u$ se dobija u najnepovoljnijem slučaju, kada su svi sinonimi jednog skupa smešteni u različite bakete i nijedan u matični.

Treba zapaziti da pokazivač ka prvom slogu iz skupa sinonima baketa, predstavlja neophodan deo fizičke strukture podataka datoteke. Naime, u matičnom baketu se mogu nalaziti prekoračioci iz raznih drugih baketa i nijedan primarni slog. U tom slučaju bi traženje sloga iz skupa sinonima baketa, bez pokazivača ka prvom slogu, bilo neizvodljivo.

Pri neuspešnom traženju jednog sloga, broj pristupa $R_n$ iznosi $R_n = 1$, kada su svi sinonimi smešteni u matični baket, a $R_n = 1 + \bar{s}$, kada se nijedan sinonim ne nalazi u matičnom baketu.

Očekivani broji pristupa pri uspešnom traženju u maloj datoteci sa poznatom strukturom, izračunava se na osnovu formule (11.11), a pri neuspešnom traženju primenom formule (11.12).

#### Primer 11.29

Da bi se, u datoteci na slici 11.24, pronašao slog sa vrednošću ključa $k(S_{12}) = 49$, potrebno je $R_u = 3$ pristupa, a da bi se utvrdilo da slog sa vrednošću ključa $k(S) = 71$ u datoteci ne postoji, potrebno je $R_n = 1$ pristup.

Očekivani broji pristupa pri uspešnom i pri neuspešnom traženju sloga u datoteci na slici 11.24 iznose, redom, $\bar{R}_u \approx 1{,}46$ i $\bar{R}_n \approx 1{,}8$.

---

### 11.6.3 Ažuriranje rasute datoteke sa sprezanjem u primarnoj zoni

Upis novog sloga u rasutu datoteku sa sprezanjem u primarnoj zoni vrši se nakon neuspešnog traženja. Ukoliko je matični baket popunjen, novi slog se upisuje u baket sa slobodnom lokacijom.

**Brisanje sloga** iz datoteke vrši se ili logički ili kao i u spregnutoj datoteci. Pri brisanju kao u spregnutoj datoteci, ako je pre brisanja baket bio popunjen, mora se izvršiti i ažuriranje u lancu slobodnih baketa. Takođe, u lokaciju izbrisanog sloga upisuje se niz specijalnih znakova koji ukazuju da je lokacija slobodna.

---

### 11.6.4 Ocena karakteristika rasute datoteke sa sprezanjem u primarnoj zoni

Međusobnim sprezanjem slogova svakog skupa sinonima, povećava se efikasnost traženja u odnosu na datoteke sa otvorenim adresiranjem. To povećanje efikasnosti posebno dolazi do izražaja u datotekama sa faktorom popunjenosti preko $0{,}7$ i u slučaju neuspešnog traženja, a posledica je činjenice da se traženje vrši samo u baketima koji sadrže slogove iz traženog skupa sinonima i činjenice da se traženje zaustavlja nailaskom na oznaku kraja lanca sinonima.

Povećanje efikasnosti traženja je postignuto na račun manje efikasnosti korišćenja memorijskog prostora, pri istom faktoru popunjenosti kao u datoteci sa otvorenim adresiranjem.

Brisanje slogova, kao u spregnutoj datoteci, obezbeđuje dinamičko upravljanje slobodnim lokacijama memorijskog prostora dodeljenog datoteci, ali ne rešava problem prekoračilaca. Degradacija performansi traženja zbog pojave da jedni prekoračioci izazivaju pojavu drugih, može se rešiti reorganizacijom, ili formiranjem datoteke u dva prolaza.

---

## 11.7 Rasute datoteke sa sprezanjem u zoni prekoračenja

Datoteci sa sprezanjem u zoni prekoračenja dodeljena su **dva memorijska prostora**. To su **primarna zona** i **zona prekoračenja**. Primarna zona sadrži matične bakete, a zona prekoračenja bakete za smeštaj prekoračilaca. Na taj način se eliminiše mogućnost zaposedanja matičnih baketa od strane prekoračilaca iz drugih baketa.

Svaki matični baket i svaka lokacija u zoni prekoračenja proširena je poljem za smeštaj pokazivača. Pokazivač matičnog baketa sadrži adresu lokacije prvog sloga iz odgovarajućeg lanca prekoračilaca. Zona prekoračenja sadrži skup lanaca, čiji indeksi početka se nalaze u baketima primarne zone. Za faktor baketiranja u zoni prekoračenja se često bira $b = 1$. Naime, prekoračioci se u zonu prekoračenja smeštaju slučajnim redosledom, tako da je mala verovatnoća da se u isti baket smeste dva ili više prekoračilaca iz istog skupa sinonima. S druge strane, veći baketi zahtevaju veći bafer u operativnoj memoriji i duže vreme prenosa.

Zona prekoračenja se snabdeva i jednom malom pomoćnom strukturom podataka. To je indeks slobodnih baketa $E$.

---

### 11.7.1 Dimenzionisanje zone prekoračenja

Određivanje broja lokacija $Z$ potrebnih za smeštaj prekoračilaca otežava činjenica da se tačan broj prekoračilaca ne može unapred predvideti. Dimenzionisanje zone prekoračenja vrši se na osnovu očekivanog broja prekoračilaca i srednje kvadratnog odstupanja broja prekoračilaca iz primarne zone.

Brojevi prekoračilaca iz svakog baketa primarne zone predstavljaju nezavisne slučajne veličine $L_i$ ($i = 1, ..., B$) sa istom raspodelom, istim matematičkim očekivanjem i istom disperzijom. Na osnovu centralne granične teoreme sledi da, za dovoljno veliko $B$, ukupni broj prekoračilaca:

$$L_B = \sum_{i=1}^{B} L_i$$

predstavlja slučajnu veličinu sa **normalnom raspodelom**.

Problem dimenzionisanja zone prekoračenja svodi se na određivanje takvog broja lokacija $Z$ u zoni prekoračenja, da bude zadovoljen uslov:

$$P(L_B \leq Z) \geq p$$

gde je $p$ neka unapred zadata verovatnoća. Drugim rečima, treba odrediti $Z$ tako da sa verovatnoćom ne manjom od $p$, ukupni broj prekoračilaca iz primarne zone ne bude veći od $Z$.

Pošto su zadovoljeni uslovi centralne granične teoreme, to je ekvivalentno sa:

$$\Phi\left(\frac{Z - \overline{LB}}{\sqrt{D}}\right) \geq p$$

gde je $\overline{LB}$ matematičko očekivanje slučajne veličine $L_B$, dato sa (11.9), $D$ njena disperzija, a $\Phi(x)$ funkcija normalne raspodele. Na osnovu nezavisnosti $L_i$, sledi $D = B\sigma^2$, gde je $\sigma^2$ disperzija slučajne veličine $L_i$. Dalje je $\sigma^2 = M(L^2) - (\bar{L})^2$, gde je:

$$M(L^2) = \sum_{i=b+1}^{N} (i - b)^2 P(i)$$

Tako se dobija:

$$\sigma^2 = qb + 2b(1 - q) \sum_{i=0}^{b-1} (b - i) P(i) - \left(\sum_{i=0}^{b-1} (b - i) P(i)\right)^2 - \sum_{i=0}^{b-1} (b - i)^2 P(i)$$

Neka je $k$ argument funkcije normalne raspodele, za koji važi $\Phi(k) \geq p$. Tada se broj lokacija u zoni prekoračenja izračunava po formuli:

$$Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil$$

Parametar $k$ se pronalazi iz tablica funkcije normalne raspodele za dato $p$, $\sigma$ se procenjuje na osnovu slike 11.26, a $\overline{LB}$ na osnovu slike 11.9.

Uvođenjem zone prekoračenja u fizičku strukturu rasute datoteke menja se i **faktor popunjenosti**. Faktor popunjenosti $q'$ cele datoteke sa zonom prekoračenja izračunava se kao:

$$q' = \frac{N}{bB + Z}$$

#### Primer 11.31

Za rasutu datoteku sa $q = 0{,}87$, $b = 10$, $N = 10000$ i $B = 1150$ treba dimenzionisati zonu prekoračenja tako da sa verovatnoćom $p \geq 0{,}998$ u nju mogu da se smeste svi prekoračioci. Za $p = 0{,}998$ iz tablice funkcije normalne raspodele se dobija $k \approx 3$. Sa slika 11.9 i 11.26 se, redom, procenjuje $\overline{LB} \approx 750$ i $\sigma \approx 1{,}45$, te se dobija $Z = 898$. Stvarni faktor popunjenosti za ovu datoteku iznosi $q' \approx 0{,}81$.

Pri smeštanju prekoračilaca u zoni prekoračenja, prekoračioci se mogu biti dosta udaljeni od svojih matičnih baketa. Na jedinici magnetnog diska ta udaljenost može iznositi više cilindara, što produžava vreme pristupa. Da bi se vreme pristupa slogovima u zoni prekoračenja skratilo, nakon svake grupe sa određenim brojem matičnih baketa, rezerviše se jedan broj baketa za smeštaj prekoračilaca iz te grupe matičnih baketa. Na taj način se dobijaju **lokalne zone prekoračenja**, raspodelene između baketa primarne zone. Takođe se može rezervisati i **zajednička zona prekoračenja** za smeštaj prekoračilaca iz lokalnih zona prekoračenja.

Nedostatak ovog postupka predstavlja činjenica da transformacija vrednosti ključa u adresu ne sme proizvoditi adrese baketa određenih za smeštaj prekoračilaca, što komplikuje algoritam transformacije.

---

### 11.7.2 Formiranje rasute datoteke sa sprezanjem u zoni prekoračenja

Prvi korak formiranja rasute datoteke sa sprezanjem u zoni prekoračenja predstavlja formiranje prazne primarne i prazne zone prekoračenja, kao dve posebne datoteke. Dalje se postupak odvija po opštim principima formiranja rasutih datoteka uz poštovanje specifičnih pravila za dodelu adresa lokacija slogovima. To znači i da se prekoračioci smeštaju u zonu prekoračenja po principima upisa novog sloga u jednostruko spregnutu datoteku.

Na slici 11.28 prikazan je pseudokod algoritma za formiranje rasute datoteke sa sprezanjem u zoni prekoračenja. Ovaj algoritam poziva procese formiranja prazne primarne i prazne zone prekoračenja, čiji su algoritmi prikazani, redom, na slikama 11.29 i 11.30, kao i proces dodavanja novog sloga, čiji algoritam je prikazan na slici 11.38.

---

### 11.7.3 Traženje u rasutoj datoteci sa sprezanjem u zoni prekoračenja

Traženje sloga u rasutoj datoteci sa sprezanjem u zoni prekoračenja vrši se tako što se, nakon transformacije argumenta u adresu, pristupa matičnom baketu. Ako matični baket sadrži traženi slog, traženje se završava uspešno. Inače, ako pokazivač matičnog baketa ne sadrži oznaku kraja, traženje se nastavlja praćenjem pokazivača u zoni prekoračenja. Ukoliko pokazivač matičnog baketa sadrži oznaku kraja, traženje se završava neuspešno. Ponovo, traženje se zaustavlja uspešno nailaskom na traženi slog, a neuspešno nailaskom na kraj lanca sinonima.

Na slici 11.31 prikazan je pseudokod algoritma traženja sloga u rasutoj datoteci sa sprezanjem u zoni prekoračenja. Ovaj algoritam poziva proces transformacije vrednosti ključa u adresu, čiji algoritam je prikazan na slici 11.4.

Broj pristupa $R_u$ pri uspešnom traženju jednog sloga, uzima celobrojne vrednosti iz intervala $[1, 1 + l]$, odnosno:

$$1 \leq R_u \leq 1 + l$$

gde je $l$ definisano kao:

$$l = \begin{cases} 0 & \text{za } \bar{s} \leq b \\ \bar{s} - b & \text{za } \bar{s} > b \end{cases}$$

i $\bar{s}$ je broj slogova u skupu sinonima.

Gornja granica broja pristupa $R_u$ se dobija u najnepovoljnijem slučaju, kada su svi sinonimi jednog skupa smešteni u različite bakete i nijedan u matični. Broj slogova $\bar{s}$ u skupu sinonima predstavlja slučajnu veličinu sa Poissonovom raspodelom, koja uzima vrednosti iz skupa $\{0, 1, ..., N\}$. Saglasno tome, maksimalni broj pristupa datoteci pri traženju jednog sloga iznosi $R_{max} = N - b + 1$. No, ta vrednost predstavlja praktično nemoguć događaj.

U najnepovoljnijem slučaju, ukupni broj pristupa $R_b$, potreban da se prođe svaki od $\bar{s}$ slogova jednog skupa sinonima u rasutoj datoteci sa sprezanjem u zoni prekoračenja, dat je formulom:

$$R_b = \begin{cases} \bar{s} & \text{za } 1 \leq \bar{s} \leq b \\ \bar{s} + \frac{(\bar{s} - b + 1)(\bar{s} - b)}{2} & \text{za } b < \bar{s} \leq N \end{cases}$$

Pri tome je, za $\bar{s} > b$, $b$ pristupa matičnom baketu potrebno da bi se pročitalo svaki od $b$ slogova u baketu, takođe potrebno izvršiti $\bar{s} - b$ pristupa matičnom baketu pri traženju svakog od $\bar{s} - b$ prekoračilaca, a za pronalaženje svih $\bar{s} - b$ prekoračilaca potrebno je:

$$\sum_{i=1}^{\bar{s}-b} i = \frac{(\bar{s} - b + 1)(\bar{s} - b)}{2}$$

pristupa zoni prekoračenja.

#### Primer 11.32

U datoteci na slici 11.25, matični baket sa relativnom adresom $A_r = 5$ ima $\bar{s} = 5$ slogova u skupu sinonima, te je $R_b = 8$.

---

### 11.7.4 Ažuriranje rasute datoteke sa sprezanjem u zoni prekoračenja

**Upis novog sloga** u rasutu datoteku sa sprezanjem u zoni prekoračenja vrši se, nakon neuspešnog traženja, ili u matični baket ili u prvu slobodnu lokaciju u zoni prekoračenja. Ako se upis novog sloga vrši u zonu prekoračenja, novi slog se upisuje kao prvi u lancu prekoračilaca. Broj pristupa $R_i$ pri upisu novog sloga dat je formulom:

$$R_i = \begin{cases} 2 & \text{za } 0 \leq \bar{s} < b \\ \bar{s} - b + 4 & \text{za } b \leq \bar{s} \leq N \end{cases}$$

Ako se novi slog upisuje u matični baket, potrebno je izvršiti dva pristupa. Ako se novi slog upisuje u zonu prekoračenja, nakon neuspešnog traženja, za koje treba $1 + \bar{s} - b$ pristupa, potreban je jedan pristup za čitanje prve slobodne lokacije i po jedan pristup za upis novog sloga i matičnog baketa sa izmenjenim pokazivačem, u datoteku.

**Brisanje sloga** iz rasute datoteke sa sprezanjem u zoni prekoračenja se vrši nakon uspešnog traženja, a može se vršiti na jedan od dva načina. Prvi predstavlja logičko brisanje. Logičko brisanje podrazumeva postojanje statusnog polja u formatu svake lokacije i korišćenje tri vrednosti statusne oznake, kao u slučaju rasute datoteke sa sprezanjem u primarnoj zoni.

Broj pristupa $R_d$, potreban za logičko brisanje jednog sloga, iznosi:

$$R_d = R_u + 1$$

Drugi postupak brisanja sloga iz rasute datoteke sa sprezanjem u zoni prekoračenja, predstavlja modifikaciju postupka ažuriranja jednostruko spregnute datoteke. Prema ovom postupku, brisanje sloga u lokaciji sa adresom $A_i^j$ ($j \in \{1, ..., b\}$) matičnog baketa sa relativnom adresom $A_r = i$, ($i \in \{1, ..., B\}$) vrši se pomeranjem sadržaja lokacija sa adresama $A_i^{j+1}, ..., A_i^b$ za jednu lokaciju ka početku baketa. Ako matični baket nema prekoračilaca, u lokaciju $A_i^b$ se upisuju specijalni znaci, koji ukazuju da je lokacija inicijalno prazna. Inače se u lokaciju $A_i^b$ upisuje prvi prekoračilac, a u pokazivač matičnog baketa upisuje se pokazivač tog prekoračioca. Lokacija prekoračioca se proglašava za prvu slobodnu u zoni prekoračenja. Brisanje sloga u zoni prekoračenja vrši se kao u jednostruko spregnutoj datoteci.

Broj pristupa $R_d$, potreban za realizaciju drugog postupka brisanja iznosi:

$$R_d = 2$$

ako matični baket nema prekoračilaca:

$$R_d = 4$$

ako prekoračioci postoje, a briše se ili slog iz matičnog baketa ili prvi prekoračilac, i:

$$R_d = R_u + 2$$

ako se briše prekoračilac koji nije prvi. Pri tome je $1 < R_u \leq 1 + \bar{s} - b$.

---

### 11.7.5 Ocena karakteristika rasute datoteke sa sprezanjem u zoni prekoračenja

Osnovnu prednost rasute datoteke sa sprezanjem u zoni prekoračenja nad drugim vrstama rasutih datoteka, predstavlja **manji očekivani broj pristupa pri neuspešnom traženju**. Ova prednost dolazi posebno do izražaja pri vrednostima faktora popunjenosti $q$ bliskim $1$.

Interesantno je napomenuti da, teorijski, očekivani broj pristupa $\bar{R}_u$ pri uspešnom traženju, ni u najnepovoljnijem slučaju ne prelazi vrednost $\bar{R}_u = 1{,}5$. To se lako proverava stavljanjem vrednosti $q = 1$ i $b = 1$ u formulu (11.22).

Ovi pozitivni efekti postignuti su, kako smeštanjem prekoračilaca u zonu prekoračenja, tako i njihovim sprezanjem sa matičnim baketom. Međutim, i zona prekoračenja i pokazivači zahtevaju dodatni memorijski prostor.

Analiza slika 11.32 i 11.33 pokazuje da očekivani broj pristupa datoteci i pri uspešnom i pri neuspešnom traženju naglo opada sa porastom baket faktora $b$ u intervalu $[1, 10]$.

Za velike vrednosti $N$ i $B$, očekivani ukupni broj pristupa $\bar{R}_b$ potreban za pronalaženje svih $\bar{s}$ slogova, iznosi:

$$\bar{R}_b = qb + \sum_{i=b+1}^{N} \frac{i - b + 1}{2} (i - b) P(i)$$

Odnos:

$$\bar{R}_b = \frac{B\bar{R}_b}{N}$$

Pa:

$$\bar{R}_u = 1 + \frac{qb}{2} - (b - 1)\frac{2q - 1}{2q} - \frac{1}{2qb} \sum_{i=0}^{b} (b - i)(b - i) P(i)$$

Ako su zadovoljene pretpostavke navedene na početku tačke 11.4.3, tada očekivani broj pristupa $\bar{R}_u$ ne zavisi od broja slogova $N$ i broja baketa $B$, već samo od faktora popunjenosti $q$ i faktora baketiranja $b$. Korišćenjem formule (11.22), na slici 11.32 su nacrtane krive $\bar{R}_u = f(q)$ za razne vrednosti faktora baketiranja $b$. Treba zapaziti da su na apscisu na slici 11.32 nanete vrednosti za $q = N/bB$, a ne vrednosti za $q' = N/(bB + Z)$.

Broj pristupa $R_n$ pri neuspešnom traženju je dat sa:

$$R_n = \begin{cases} 1 & \text{za } 0 \leq \bar{s} \leq b \\ 1 + \bar{s} - b & \text{za } b < \bar{s} \leq N \end{cases}$$

Očekivani broj pristupa $\bar{R}_n$ pri neuspešnom traženju jednog sloga, iznosi:

$$\bar{R}_n = \sum_{i=0}^{b} P(i) + \sum_{i=b+1}^{N} (i - b + 1) P(i)$$

što se, nakon jednostavnih transformacija, svodi na:

$$\bar{R}_n = 1 + b(q - 1) + \sum_{i=0}^{b} (b - i) P(i)$$

Ponovo se može zaključiti da ni očekivani broj pristupa $\bar{R}_n$ ne zavisi od broja slogova $N$ i broja baketa $B$ datoteke, koji je konstanta. Korišćenjem formule (11.23), na slici 11.33 nacrtane su krive $\bar{R}_n = f(b)$ za razne vrednosti faktora popunjenosti $q$.

#### Primer 11.33

Za $q = 0{,}87$ i $b = 3$, na osnovu krivih sa slika 11.32 i 11.33, može se proceniti da je $\bar{R}_u \approx 1{,}31$ i $\bar{R}_n \approx 1{,}4$. Korišćenjem formula (11.11) i (11.12), za slučaj datoteke sa slike 11.25 se dobija $\bar{R}_u \approx 1{,}31$ i $\bar{R}_n \approx 1{,}6$.

---

### 11.7.6 Rasuta datoteka sa serijskom zonom prekoračenja

Rasuta datoteka sa serijskom zonom prekoračenja se odlikuje strukturnom jednostavnošću. Prekoračioci se međusobno ne sprežu niti se povezuju sa matičnim baketom. Datoteka je pogodna za primenu u slučajevima kada je ukupni broj prekoračilaca mali, a ažuriranje retko.

Primenom formula (11.11) i (11.12) dobija se, redom $\bar{R}_u = 1{,}23$ i $\bar{R}_n = 1{,}8$.

#### Primer 11.35

Na slici 11.40 prikazana je struktura rasute datoteke sa serijskom zonom prekoračenja za slučaj $N = 13$, $B = 5$, $b = 3$. U zoni prekoračenja se nalaze dva baketa sa faktorom baketiranja $b = 3$.

Struktura:

**PRIMARNA ZONA:**

| Baket | Lok. 1 | Lok. 2 | Lok. 3 |
|---|---|---|---|
| 1 | 15, $p(S_4)$ | 25, $p(S_{13})$ | * |
| 2 | * | * | * |
| 3 | 07, $p(S_2)$ | 27, $p(S_{10})$ | * |
| 4 | 03, $p(S_3)$ | 43, $p(S_8)$ | 23, $p(S_9)$ |
| 5 | 34, $p(S_1)$ | 19, $p(S_5)$ | 29, $p(S_6)$ |

**ZONA PREKORAČENJA:**

| Baket | Lok. 1 | Lok. 2 | Lok. 3 |
|---|---|---|---|
| $A_1$ | 64, $p(S_7)$ | 13, $p(S_{11})$ | 49, $p(S_{12})$ |
| $A_2$ | * | * | * |

Povećanje baket faktora $b$ preko $10$ dovodi do malog smanjenja srednjeg broja pristupa, a povećava vreme razmene podataka između operativne i eksterne memorije, što potkrepluje tvrdnju iznetu u tački 11.4.2 da se u praksi retko koriste faktori baketiranja veći od $10$.

---

## 11.8 Obrada rasutih datoteka sa probabilističkom transformacijom

Rasute datoteke su nepogodne za korišćenje u ulozi osnovne (prve) vodeće datoteke. Mogu se koristiti kao obrađivane i vodeće u režimu direktne obrade. Pošto im fizička struktura ne sadrži informaciju o logičkoj strukturi podataka, rasute datoteke se ne mogu koristiti kao vodeće u režimu redosledne obrade.

Rasute datoteke se mogu obrađivati i u režimu redosledne i u režimu direktne obrade. Pošto su efikasnosti traženja i logički narednog i slučajno odabranog sloga iste, iste su i performanse redosledne i direktne obrade rasute datoteke.

Neka je $N_v = N_v'' + N_v'$ broj slogova vodeće datoteke, a $\bar{R}_u$ očekivani broj pristupa pri uspešnom, a $\bar{R}_n$ očekivani broj pristupa pri neuspešnom traženju jednog sloga u rasutoj datoteci. Tada se očekivani ukupni broj pristupa $\bar{R}_{uk}$, bilo pri redoslednoj, bilo pri direktnoj obradi, izračunava putem formule:

$$\bar{R}_{uk} = N_v'' \bar{R}_u + N_v' \bar{R}_n$$

#### Primer 11.36

Ako vodeća datoteka generiše sledeći niz argumenata traženja (03, 06, 13, 19, 25, 29, 49, 55, 64) pri obradi rasute datoteke sa linearnim traženjem prikazane na slici 11.10, obrada će biti redosledna. Ukupni broj pristupa datoteci će iznositi $\bar{R}_{uk} = 16$.

U primeru 11.22 je, za datoteku sa slike 11.10, izračunato $\bar{R}_u = 1{,}46$ i $\bar{R}_n = 2{,}2$. Pošto je, u posmatranoj obradi, 7 traženja uspešno, a 2 su neuspešna, za očekivani ukupni broj pristupa se dobija $\bar{R}_{uk} = 14{,}62$.

#### Primer 11.37

Neka je datoteka od $N = 10000$ slogova organizovana kao rasuta sa sprezanjem u zoni prekoračenja. Neka je dalje $q = 0{,}9$, a $b = 10$. Na osnovu slike 11.32 se dobija $\bar{R}_u = 1{,}2$, a na osnovu slike 11.33 se dobija $\bar{R}_n = 1{,}8$. Ako se rasuta datoteka obrađuje putem vodeće datoteke od $N_v'' = 8400$ i $N_v' = 900$ slogova, dobija se $\bar{R}_{uk} = 11700$.

Za srednje vreme pristupa i prenosa baketa u operativnu memoriju od $\bar{t} = 30$ msek, dobija se $\bar{T}_{uk} = 351$ sek. Očekivano vreme razmene podataka između datoteke i programa, pri uspešnom traženju slučajno odabranog sloga, iznosi samo $36$ msek.

> [!TIP]
> Zahvaljujući malom očekivanom broju pristupa pri traženju slučajno odabranog sloga, rasute datoteke su, pre svega, pogodne za direktnu obradu. Kada je reč o redoslednoj obradi rasute datoteke, treba zapaziti da ukupni očekivani broj pristupa datoteci linearno zavisi od broja slogova vodeće datoteke. U graničnom slučaju, za $N_v = N$, $\bar{R}_{uk} > N$.

#### Primer 11.38 - Kada je isplativije sortirati pa sekvencijalno obraditi?

Može se postaviti pitanje za koji odnos broja slogova $N_v$ vodeće i broja $N$ obrađivane rasute datoteke, pogodnije rasutu datoteku prvo sortirati pa onda obrađivati u redoslednom režimu kao sekvencijalnu. Odgovor se može dobiti putem sledećeg razmatranja, koje ne pretenduje na strogu preciznost.

Sortiranje rasute datoteke traži $6B$ pristupa, a za redoslednu obradu sekvencijalne datoteke je potrebno $B$ pristupa. Znači, treba da bude $7B < \bar{R} N_v$, gde je $\bar{R}$ očekivani broj pristupa rasutoj datoteci pri traženju jednog sloga. To dalje znači da treba da bude zadovoljen odnos:

$$\frac{N_v}{N} > \frac{7}{f\bar{R}}$$

Neka je $f = 20$, $\bar{R} = 1{,}5$, $\bar{t}_s = 10$ msek srednje vreme pristupa i prenosa bloka sekvencijalne i $\bar{t}_r = 30$ msek srednje vreme pristupa i prenosa bloka rasute datoteke u operativnu memoriju. Tada je postupak sa sortiranjem pogodniji od redosledne obrade rasute datoteke za:

$$\frac{N_v}{N} > \frac{7\bar{t}_s}{f\bar{R}\bar{t}_r} \approx 0{,}08$$

---

## 11.9 Oblasti primene rasutih datoteka

Fizičke strukture podataka zasnovane na principima izgradnje rasutih datoteka intenzivno se koriste u svim sistemima za upravljanje mrežnim i u pojedinim sistemima za upravljanje relacionim bazama podataka. Ti sistemi poseduju metode pristupa za formiranje, korišćenje i ažuriranje ovih struktura. Fizičke strukture tipa rasutih datoteka se, u tim sistemima, javljaju pod nazivima **CALC** i **HASH**.

Operativni sistemi retko poseduju metode pristupa za rasute datoteke. Rasute datoteke se mogu formirati kao relativne, korišćenjem principa i algoritama opisanih u ovom poglavlju.

Fizičke strukture tipa rasutih datoteka se intenzivno koriste u interaktivnoj daljinskoj obradi. U ovom režimu rada, korisnici sa terminala traže proizvoljnim redosledom pristup slogovima, a veoma je važno da vreme traženja podataka bude što kraće. Rasuto organizovane datoteke se koriste i u režimu paketne obrade, kada sadrže podatke koji se iz programa uvek traže nekim slučajnim redosledom. Osnovnu prednost rasutih, nad drugim vrstama organizacija datoteka predstavlja **mali očekivani broj pristupa pri traženju slučajno odabranog sloga**.

U odnosu na druge vrste organizacije, statičke rasute datoteke poseduju i određene **nedostatke**:

1. **Veličina datoteke mora se unapred odrediti.** To ih čini pogodnim samo za datoteke čiji sadržaj se retko menja. Intenzivno upisivanje novih slogova dovodi do približavanja faktora popunjenosti ka jedinici i neminnovne degradacije performansi obrade. Tada jedino rešenje predstavlja preprojektovanje i ponovno formiranje datoteke, što je skupo.

2. **Problem izbora metode transformacije** - takve probabilističke transformacije vrednosti ključa u adresu, koja će obezbediti ravnomernu raspodelu broja sinonima po baketima i pri formiranju i pri kasnijem ažuriranju datoteke. Opredeljenje za neodgovarajuću metodu transformacije dovodi do pojave velikog broja prekoračilaca iz pojedinih baketa.

3. **Maksimalna vrednost broja pristupa može biti nepredvidivo velika**, jer je ograničena samo brojem slogova (sprezanje) ili brojem baketa (otvoreno adresiranje) u datoteci. Ovi izimni slučajevi predstavljaju praktično nemoguće događaje, ali ukazuju da su gornje granice broja pristupa veoma visoke.

Nedostatak rasuto organizovanih datoteka se može ubrojiti i činjenica da ukupni broj pristupa u redoslednoj obradi zavisi od broja slogova vodeće datoteke, što ih ne kvalifikuje kao pogodne za redoslednu obradu u slučajevima, kada je broj slogova vodeće datoteke blizak broju slogova obrađivane datoteke.

---

## 🎴 Brza pitanja (definicije i pojmovi)

**P1:** Šta je identifikator u kontekstu rasute datoteke i koja je njegova uloga?

**P2:** Koja je razlika između determinističke i probabilističke transformacije vrednosti identifikatora u adresu?

**P3:** Šta je baket i šta predstavlja faktor baketiranja $b$?

**P4:** Šta je faktor popunjenosti $q$ i koja je preporučena vrednost u praksi?

**P5:** Šta su sinonimi, a šta prekoračioci u rasutoj datoteci?

**P6:** Koja su dva osnovna postupka za smeštaj prekoračilaca?

**P7:** Šta je nagomilavanje (clustering) i kod kojeg tipa rasute datoteke se javlja?

**P8:** Zašto je broj $m$ u metodi ostatka pri deljenju poželjno da bude prost ili neparan sa velikim prostim činiocima?

---

## 📝 Šira pitanja za proveru razumevanja

**P1:** Objasnite postupak formiranja rasute datoteke sa linearnim traženjem. Šta se dešava kada je matični baket popunjen?

**O1:** Prilikom formiranja, za svaki slog se transformacijom ključa izračunava adresa matičnog baketa. Ako u matičnom baketu postoji slobodna lokacija, slog se tu smešta. Ako je matični baket popunjen, slog postaje prekoračilac i smešta se u prvi naredni baket sa slobodnom lokacijom, prema cirkularnom redosledu adresa. Ovo može dovesti do pojave nagomilavanja (clustering), pa se ovaj tip datoteke preporučuje samo za faktor popunjenosti $q < 0{,}7$.

**P2:** Za rasute datoteke sa velikim brojem slogova, dokažite da očekivani broj pristupa ne zavisi od broja slogova $N$. Od čega zavisi?

**O2:** Pošto važi $\sum P(i) = 1$ i $\sum iP(i) = qb$, izraz za očekivani broj prekoračilaca $\bar{L}$ se transformiše u oblik $\bar{L} = b(q-1) + \sum_{i=0}^{b}(b-i)P(i)$, koji ne sadrži $N$. Zato očekivani broj pristupa zavisi samo od faktora popunjenosti $q$ i faktora baketiranja $b$, a ne od veličine datoteke $N$. To je ključna prednost rasutih datoteka - datoteka sa 100 i sa 100000 slogova ima isti očekivani broj pristupa.

**P3:** Za rasutu datoteku sa $N = 10000$ slogova, faktorom baketiranja $b = 3$ i faktorom popunjenosti $q = 0{,}87$, izračunajte očekivani broj sinonima po jednom baketu i odredite broj baketa.

**O3:** Očekivani broj sinonima po jednom baketu iznosi $\bar{s} = qb = 0{,}87 \times 3 = 2{,}61$. Broj baketa se izračunava iz formule $B = \lceil N/(bq) \rceil = \lceil 10000/(3 \times 0{,}87) \rceil = \lceil 3831{,}4 \rceil = 3832$. Ukupan broj lokacija je $Q = bB = 3 \times 3832 = 11496$.

**P4:** Uporedite rasute datoteke sa otvorenim adresiranjem, sprezanjem u primarnoj zoni i sprezanjem u zoni prekoračenja. Koje su glavne prednosti i mane svake varijante?

**O4:** Datoteke sa otvorenim adresiranjem su najjednostavnije ali pate od nagomilavanja i pogodne su samo za $q < 0{,}7$. Datoteke sa sprezanjem u primarnoj zoni eliminišu nepotrebno traženje u nesrodnim baketima i zaustavljaju traženje na kraju lanca sinonima, ali prekoračioci i dalje mogu zauzimati tuđe matične bakete. Datoteke sa sprezanjem u zoni prekoračenja eliminišu i taj problem razdvajanjem primarne zone i zone prekoračenja, pružajući najmanju vrednost $\bar{R}_n$ pri neuspešnom traženju, ali zahtevaju dodatni memorijski prostor za zonu prekoračenja i pokazivače.

**P5:** Objasnite kako se dimenzionše zona prekoračenja. Za datoteku sa $q = 0{,}87$, $b = 10$, $N = 10000$ i $B = 1150$, ako je $\overline{LB} \approx 750$, $\sigma \approx 1{,}45$ i $p = 0{,}998$ (što daje $k \approx 3$), koliko lokacija treba rezervisati u zoni prekoračenja?

**O5:** Zona prekoračenja se dimenzionše tako da, sa zadatom verovatnoćom $p$, primi sve prekoračioce. Koristi se normalna raspodela jer je ukupni broj prekoračilaca $L_B$ zbir nezavisnih slučajnih veličina. Formula je $Z = \lceil \overline{LB} + k\sigma\sqrt{B} \rceil = \lceil 750 + 3 \times 1{,}45 \times \sqrt{1150} \rceil = \lceil 750 + 3 \times 1{,}45 \times 33{,}91 \rceil = \lceil 750 + 147{,}5 \rceil = 898$ lokacija. Stvarni faktor popunjenosti je $q' = N/(bB + Z) = 10000/(11500 + 898) \approx 0{,}81$.
