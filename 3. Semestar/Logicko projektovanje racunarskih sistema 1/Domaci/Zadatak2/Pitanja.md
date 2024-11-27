# Zadatak 2 - Košarkaški semafor

## 📜 Teorijska Pitanja

###  1. Koja je razlika između kombinacionih i skevencijalnih mreža?

- Razlika između kombinacionih i sekvencijalnih mreža je u tome što kombinacione mreže proizvode izlaz koji zavisi isključivo od trenutnih vrednosti na ulazu, dok sekvencijalne mreže koriste memorijske elemente da bi zapamtile prethodna stanja. Sekvencijalne mreže omogućavaju rad sistema kroz stanja („prethodno“, „trenutno“ i „sledeće“) u vremenu, dok kombinacione mreže funkcionišu samo u prostoru ukoliko imaju dovoljno vremena za računanje, računajući trenutne ulazne vrednosti.

###  2. Šta je asinhroni reset?

- Asinhroni reset je reset koji nije sinhronizovan sa takt signalom, odnosno kada god se postavi 
na aktivnu vrednost, flip-flopovi se vraćaju u početno stanje, bez obzira u kom 
vremenskom trenutku se to desilo

###  3. Šta je sinhroni reset?

- Sinhroni reset je reset sinhronizovan sa takt signalom, tako da se vraćanje flip-flopova u početno 
stanje ne dešava do prve ivice takt signala nakon što je reset postao aktivan. 

###  4. Šta je vremensko multipleksiranje?

- Vremensko multipleksiranje je tehnika koja omogućava deljenje jednog prenosnog medijuma između više korisnika tako što se svakom korisniku dodeljuje određeni vremenski interval, odnosno slot, tokom kojeg može koristiti medijum za prenos podataka. Ideja je da se prenos podataka odvija naizmenično, tako da se svaki slot koristi za jedan izvor informacija. Ovaj proces je dovoljno brz da ljudskom oku ili korisniku deluje kao da se svi uređaji ili korisnici istovremeno koriste resurs.
Vremensko multipleksiranje koristimo u kontrolisanju više 7-segmentnih displeja povezanih na iste pinove. Umesto da svaki displej ima svoj set pinova, svi displeji su povezani na zajedničke pinove, dok se putem vremenskog multipleksiranja naizmenično prikazuje informacija na svakom displeju. Brzim preklapanjem između displeja stvara se iluzija da svi rade istovremeno.

###  5.  Ako znamo da ploča MAX10000 radi na 12MHz, do koliko brojač treba da broji da bi u sistemu prošla jedna sekunda? 

- Da bi prošla jedna sekunda, brojač treba da prebroji svaki ciklus takta. Pošto postoji 12 miliona takvih ciklusa, brojač mora da broji do 12,000,000.

###  6. Čemu služi sTC signal u kodu?

- sTC služi za upravljanje promenom selektora displeja u vremenskom multipleksiranju i bira koji displej se trenutno koristi.

###  7. Čemu služi iRST u kodu?

-  Reset (iRST) je ulazni signal koji postavlja sve kontrolne i brojačke signale u početno stanje kako bismo mogli da odradimo više test-slučajva, u određenim procesima resetuje samo određene signale koji se nalaze u ti procesima kada je on aktivan.

###  8. Kako je implementiran 7-segmentni displej?

- Brojač sDIS_CNT služi za aktiviranje svakog displeja uz dozvolu signala sTC, dok se signal za izbor displeja (sDIS_SEL) koristi za usmeravanje odgovarajućih podataka na aktivni displej. Binarne vrednosti ulaza se dekodiraju u odgovarajuće segmente za prikaz cifara 0-9 na svakom displeju. Brzo prebacivanje između displeja stvara iluziju da svi displeji istovremeno prikazuju podatke.

###  9. Kako bi na displeju prikazali slovo 'L'?
- o7SEGM <= "1110001"; -- L

## 💻 Praktična Pitanja

###  1. Dodati novi izlaz koji će svetleti zeleno svaki put kada neki tim ima više od 9 poena.

- Prvo je neophodno definisati novi signal

> signal sGREEN : std_logic;

- Zatim je potrebno napraviti novi kombinacioni blok koji će postaviti vrednost signala sGREEN na 1 ukoliko tim A ili tim B imaju više od 9 poena.

```vhdl
sGREEN <= '1' when (sA_SCORE_TENS > "0000") else '0';
```

###  2. Izmeniti redosled displeja.

- Pre izmena, kod je izgledao ovako:

```vhdl
process(sA_SCORE_UNITS, sA_SCORE_TENS, sB_SCORE_UNITS, sB_SCORE_TENS)
begin
    -- Tim A sa desne strane
    sDISPLAY_0 <= decode_7segm(sA_SCORE_UNITS);
    sDISPLAY_1 <= decode_7segm(sA_SCORE_TENS);

    -- Tim B sa leve strane
    sDISPLAY_2 <= decode_7segm(sB_SCORE_UNITS);
    sDISPLAY_3 <= decode_7segm(sB_SCORE_TENS);
end process;
```

- Sada menjamo redosled displeja tako da tim A bude sa leve strane, a tim B sa desne strane.

```vhdl
process(sA_SCORE_UNITS, sA_SCORE_TENS, sB_SCORE_UNITS, sB_SCORE_TENS)
begin
    -- Tim B sa desne strane
    sDISPLAY_0 <= decode_7segm(sB_SCORE_UNITS);
    sDISPLAY_1 <= decode_7segm(sB_SCORE_TENS);

    -- Tim A sa leve strane
    sDISPLAY_2 <= decode_7segm(sA_SCORE_UNITS);
    sDISPLAY_3 <= decode_7segm(sA_SCORE_TENS);
end process;
```

### 3. Dodati signal koji će se aktivirati kada je rezultat nerešen.

- Prvo je neophodno definisati novi signal

> signal sDRAW : std_logic;

- Zatim je potrebno napraviti novi kombinacioni blok koji će postaviti vrednost signala sDRAW na 1 ukoliko tim A i tim B imaju isti broj poena.

```vhdl
sDRAW <= '1' when (sA_SCORE_UNITS = sB_SCORE_UNITS) and (sA_SCORE_TENS = sB_SCORE_TENS) else '0';
```