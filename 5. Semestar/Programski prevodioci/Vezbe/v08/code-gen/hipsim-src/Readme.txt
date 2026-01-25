HipSim, Simulator hipotetskog procesora (c) 2013,2016 Žarko Živanov


1. Opis
-------

Simulator omogućava izvršavanje naredbi hipotetskog procesora, u režimu rada
korak po korak, gde je moguće pratiti registre i stanje memorije, i u režimu
kompletnog izvršavanja, gde se na ekranu samo ispisuje izlazni kod programa
(pogodno za brzo i automatsko testiranje). Simulator ne predstavlja kompletnu
emulaciju hipotetskog procesora na nivou mikrokoda, nego samo simulaciju
izvršavanja njegovih naredbi.

Simulacija hipotetskog procesora se zasniva na sledećim pretpostavkama:
- memorija za kod je organizovana po lokacijama, gde je 1 lokacija = 1 naredba
  (ne odgovara realnom slučaju, ali olakšava simulaciju)
- memorija za podatke i stek je organizovana po bajtovima, podaci se nalaze
  na početku, a stek na kraju memorije
- dodata je naredba HALT koja zaustavlja izvršavanje naredbi procesora
- memorija podataka se inicijlano puni sa 0xa5, a memorija koda sa INS_HALT
- za ispis koda u toku izvršavanja se generiše posebna struktura, zasnovana
  na ulaznom asemblerskom kodu (varijanta prettyprint-a)


2. Instalacija
--------------

Simulator ne treba instalirati, sve što je potrebno je da se kompajlira sa:
    make
nakon čega će se dobiti izvršni fajl hipsim. Ovaj fajl se može iskopirati u
direktorijum u kome se nalazi miniC kompajler, radi lakšeg pozivanja.
Ukoliko se hipsim-src direktorijum nalazi unutar direktorijuma sa miniC
kompajlerom, pozivanje make za miniC kompajler će odraditi i make za
simulator i izvršni fajl simulatora postaviti u direktorijum miniC kompajlera.


3. Pokretanje
-------------

Nakon što je dobijena izvršna verzija simulatora, u režimu korak po korak se 
može pokrenuti sa (pod pretpostavkom da je hipsim u tekućem direktorijumu):
    ./hipsim < asm_fajl
gde je asm_fajl hipotetski asemblerski kod dobijen iz miniC kompajlera.

Izlazni kod simulatora je:
    0 - ako se simulacija završila sa HALT naredbom,
        odnosno ako je kod sintaksno ispravan (-c opcija)
    1 - ako se desila greška prilikom parsiranja asemblerskog koda
    2 - ako se detektovala grešku prilikom parsiranja argumenata simulatora
    3 - ako se desila greška tomom simulacije
    4 - ako se prekoračio broj koraka u simulaciji

Nakon pokretanja se dobija ekran sličan ovom:

----------------------------------------------------
Line#  Addr    [> - PC, * - breakpoint]
  1   [   0] main:
  2   [   0] 			PUSH %14
  3   [   1] 			MOV %15, %14
  4   [   2] 			SUBU %15, $8, %15
  5   [   3] @main_body:
  6 > [   3] 			MOV $8, a
  7   [   4] 			MOV $12, b
  8   [   5] @if0:
  9   [   5] 			CMPS a, b
 10   [   6] 			JLES @false0

Global variables (name[address]=value)
       a[ 0]=0           b[ 4]=0           c[ 8]=0

Registers
PC=3      Flags[ZSCO]=[0000]
%0 =0     %1 =0     %2 =0     %3 =0     
%4 =0     %5 =0     %6 =0     %7 =0     
%8 =0     %9 =0     %10=0     %11=0     
%12=0     %13=0     %14=1016  %15=1008  

Stack ([address]=value)
[1020]=16           <-FP+4
[1016]=0            <-FP
[1012]=-1515870811  <-FP-4
[1008]=-1515870811  <-FP-8
Press any key to continue...
----------------------------------------------------

U gornjem delu su prikazane naredbe programa oko programskog brojača,
zatim slede globalne promenljive, nakon njih sadržaj registara i indikatora
i na kraju stek. Pritiskom na bilo koji taster, izvršava se sledeća naredba.
Nailazak na naredbu HALT završava simulaciju, nakon čega se ispisuje izlazni
kod programa (vrednost koju je vratila main funkcija). Ukoliko se želi
prekinuti izvršavanje simulatora, treba upotrebiti ctrl+c.

Da bi se simulator pokrenuo u režimu kompletnog izvršavanja, kod pokretanja
treba dodati opciju "-r":
    ./hipsim -r < asm_fajl
Kod ovakvog pokretanja, na ekranu će se samo ispisati vrednost koju je vratila
main funkcija, bez ikakvih drugih ispisa (osim ako simulirani kod upadne u
beskonačnu petlju; pogledati -s opciju).


4. Licence
----------

Simulator je, osim getch funkcije, licenciran pod GPL3 licencom, za detalje
pogledati gpl.txt fajl.

getch (c) Zobayer Hasan,
http://zobayer.blogspot.com/2010/12/getch-getche-in-gccg.html


5. Istorija izmena
------------------

1.2 - 30.01.2019.
    defs.h
        - dodate definicije za JC, JNC, JO i JNO
    simulator.c
        - simulacija sada radi korektno za neoznačene vrednosti veće od 2^31
        - dodata simulacija za JC, JNC, JO i JNO
    hipsim.l
        - dodato prepoznavanje za JC, JNC, JO i JNO
        - iskorišteno atol umesto atoi
    hipsim.y
        - union član i promenjen sa int na long
        - dodata obrada za JC, JNC, JO i JNO
        - ukoliko ima grešaka u ASM kodu, ne radi se analiza labela

1.1.3 - 14.01.2018.
    defs.h
        - nešto izmenjen ispis za argerror i simerror makroe
    simulator.c
        - izmenjeno postavljanje indikatora za ADD, SUB, MUL i DIV
        - parametar data set_operand funkcije postavljen na word tip
    hipsim.y
        - dodate dve biblioteke, libgen.h i unistd.h, zbog upozorenja u novijim verzijama GCC-a
        - izbačen ispis greške za _ADDRESS, pošto se proverava u check_global
    Makefile
        - u clean dodato brisanje svih backup (*~) fajlova

1.1.2 - 25.11.2017.
    hipsim.l
        - dodat + kao predznak za brojeve
    Readme.txt
        - dodat tekst vezan za izmene u Makefile-u


1.1.1 - 31.10.2017.
    Makefile
        - dodata opcija zadavanja putanje izvršnog fajla
        - dodata mogućnost kompjaliranja bez ispisa
          (oba kako bi se odradila integracija u Makefile Micko kompajlera)
    hipsim.l
        - dodat + kao predznak za brojeve
    Readme.txt
        - dodat tekst vezan za izmene u makefile-u

1.1 - 05.12.2016.
    hipsim.y
        - dodata opcija za zadavanje argumenta main funkcije
        - izbačena warning funkcija (nije korištena)
        - bolje definisan izlazni kod simulatora
        - ispravljena greška kod provere broja koraka
    simulator.c
        - dodata funkcija getmem i izmenjen kod za simulaciju da je
          koristi umesto direktnog pristupa (detekcija grešaka sa memorijom)
        - u add_entry_code dodat argument za prosleđivanje main funkciji
        - kod dorađen da se može kompajlirati na 64-bitnim sistemima
        - deljenje nulom izaziva kraj simulacije, uz exit kod SIM_ERROR
        - funkcije grupisane po nameni
        - reorganizovan ispis grešaka
        - dopunjen simulator.h u skladu sa izmenama
    defs.h
        - izmenjeni makroi za ispis grešaka
        - uvedeni kodovi grešaka
        - vrste operanada i instrukcija kreću od 1, umesto od 0 (za debug)

1.0.2 - 28.11.2015.
    hipsim.y
        - dodat indirektni operand u output operande
        - dodat $label operand u input operande
    simulator.c
        - dodata detekcija izmena u prikazu steka

1.0.1 - 07.12.2014.
    hipsim.y
        - parametar za sintaksnu proveru preimenovan iz -s u -c
        - dodata opcija za postavljanje maksimalnog broja koraka kod kompletnog izvršavanja

1.0 - inicijalna verzija simulatora

