# Zadatak 1 - Kalkulator

## 🎓 Autori

- [Marko Gordic](https://github.com/MarkoGordic) - IN 37/2023
- [Nađa Jakšić](https://github.com/NadjaJaksic) - IN 33/2023
- [Aleksandra Golić](https://github.com/) - IN 55/2023

## 📜 Teorijska Pitanja

###  1. Šta je multiplekser i da li ga ima u kodu (i skica)?

- Multiplekser je kombinaciona mreža sa 2^n ulaza, n upravljačkih signala i jednim izlazom. Na osnovu upravljačkih signala bira se jedan od ulaza koji se prosleđuje na izlaz. (ALU jedinica u kodu)

###  2. Šta je demultiplekser i da li ga ima u kodu (i skica)?

- Demultiplekser je kombinaciona mreža sa jednim ulazom, n upravljačkih signala i 2^n izlaza. Na osnovu upravljačkih signala bira se jedan od izlaza na koji se prosleđuje ulaz. Nemamo ga u kodu.

###  3. Šta je koder i da li ga ima u kodu (i skica)?

- Koder je kombinaciona mreža koja ima 2^n ulaza i n izlaza. Na osnovu ulaza generiše se jedan od n izlaza. U nastavku je prikazan koder sa 4 ulaza i 2 izlaza:

|iE|iX3|iX2|iX1|iX0|oD1|oD0|
|---|---|---|---|---|---|---|
| 0 | X | X | X | X | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 1 | 0 | 0 | 1 | 0 | 0 | 1 |
| 1 | 0 | 1 | 0 | 0 | 1 | 0 | 
| 1 | 1 | 0 | 0 | 0 | 1 | 1 |

- Kod kodera se može javiti problem višestrukog odabira izlaza. U ovom slučaju, prioritetni koder bira izlaz sa najvećim prioritetom. Ukoliko se na ulazu pojavi više od jedne jedinice, prioritetni koder će odabrati izlaz sa najvećim prioritetom.I imamo prioritetni koder kodu.

###  4. Šta je dekoder i da li ga ima u kodu (i skica)?

- Dekoder je kombinaciona mreža sa n ulaza i 2^n izlaza, koja dekoduje binarni signal na ulazu i aktivira tačno jedan od svojih izlaza na osnovu vrednosti binarnog ulaza. U kodu nam je on 7-segmentni displej.
###  5. Ukoliko imamo 8 ulaza kod multipleksera koliko nam treba bitova upravljačkih signala (ista kombinacija pitanja i za demultiplekser,koder, dekoder…)?

- Treba nam 3 bita upravljačkog signala.

###  6. Šta je prioritetni koder i kako funkcioniše u našem kodu?

- Prioritetni koder je koder koji bira izlaz sa najvećim prioritetom. Kod nas u kodu je dodat kako bi se izbegla greška ako korisnik pritisne više tastera istovremeno. Takođe kod nas u kodu je prioritetni koder višeg reda, odnosno prioritetniji su viši bitovi (s leva na desno).U odnosu na to koji bit ulaza je postavljen na jedinicu prvi, ta aritmetička jedinica će biti izvršena.

###  7. Objašnjenje za oCarry i oSign u kodu (na kojim se bitovima nalaze).

- oCarry se nalazi na 5. bitu (prenos), a oSign na 4. 

###  8. Zašto je prioritetni koder ovde višeg prioriteta?

- Prioritetni koder je višeg prioriteta jer je bitno da se prvo izvrši operacija koja je višeg prioriteta, a zatim ona koja je nižeg prioriteta.
 
###  9. Šta je lista osetljivosti?

-  Lista osetljivosti procesa služi alatu za simulaciju kako bi znao kada komponenta (kombinaciona mreža) koja se opisuje procesom može da promeni izlaznu vrednost. Sa svakom promenom argumenta iz liste osetljivosti izvršava se niz naredbi zadat u okviru tela procesa. Dakle, u listi osetljivosti kombinacionog procesa treba da budu navedeni svi ulazi kombinacione mreže koji utiču na promenu izlaza u datom procesu. 

###  10. Šta bi se desilo kad bi se obrisao neki parametar iz liste osetljivosti i kako bi to uticalo na kod?

- Ukoliko bismo obrisali neki parametar iz liste osetljivosti, naš izlaz ne bi zavisio od njega, tako da ako bismo ga koristili u našim operacijama naš izlaz ne bi bio izmenjen.

###  11. Šta je komplement 2 predstava, kako je dobijamo i čemu služi,kako je primenjujemo?

- Komplement 2 predstava služi za predstavljanje označenih binarnih brojeva. Dobijamo je invertovanjem bitova (pretvaramo 0 u 1 i obrnuto) i dodavanjem broja 1 na dobijeni rezultat (+1). U našem slučaju olakšava oduzimanje. U slučaju da nemamo komplement 2, ne bismo mogli da oduzmemo veći broj od manjeg, zbog predstavljanja negativnog rezultata.

###  12. Objašnjenje simulacije.

###  13. Koja komponenta je aritmetičko logička jedinica?

- Aritmetičko logička jedinica predstavlja multiplekser (2^n ulaza, n upravljačkih signala, jedan izlaz).

### 14. Kako bismo oduzeli iA od iB ako nisu u komplement 2 predstavi?

- sRES <= ('0' & iA) + ('0' & iB_complement) + "00001";

## 💻 Praktična Pitanja

###  1. Dodati ulaz iE koji kad je na 1 prioritetni koder radi, a kada je na 0 ne radi.

Kako bi dodali ulaz iE moramo izmeniti listu ulaznih portova:

```vhdl
port(
		-- ulazni portovi
		iA  : in std_logic_vector(3 downto 0);
		iB  : in std_logic_vector(3 downto 0);
		iOP : in std_logic_vector(4 downto 0);
        iE  : in std_logic; -- dodatni ulaz

        -- ...
);
```

A zatim je potrebno izmeniti prioritetni koder tako da radi samo kada je iE na 1. U nastavku je prikazan deo koda koji se odnosi na prioritetni koder:

```vhdl
sOPER <= "100" when iOP(4)='1' else
		 "011" when iOP(3)='1' else
		 "010" when iOP(2)='1' else
		 "001" when iOP(1)='1' else
		 "000" when iOP(0)='1' else
		 "111";
```

Kako bi prioritetni koder radio samo kada je iE na 1, potrebno je dodati uslovnu dodelu:

```vhdl
sOPER <= "100" when iOP(4)='1' and iE='1' else
         "011" when iOP(3)='1' and iE='1' else
         "010" when iOP(2)='1' and iE='1' else
         "001" when iOP(1)='1' and iE='1' else
         "000" when iOP(0)='1' and iE='1' else
         "111";
```

###  2. Napisati umesto uslovne dodele kod prioritetnog kodera istu verziju samo sa if i case.

U nastavku je prikazan prioritetni koder sa uslovnom dodelom:

```vhdl
sOPER <= "100" when iOP(4)='1' else
         "011" when iOP(3)='1' else
         "010" when iOP(2)='1' else
         "001" when iOP(1)='1' else
         "000" when iOP(0)='1' else
         "111";
```

Isti prioritetni koder možemo napisati koristeći `if` naredbu:

```vhdl
process (iOP) is
begin
    if iOP(4) = '1' then
        sOPER <= "100";
    elsif iOP(3) = '1' then
        sOPER <= "011";
    elsif iOP(2) = '1' then
        sOPER <= "010";
    elsif iOP(1) = '1' then
        sOPER <= "001";
    elsif iOP(0) = '1' then
        sOPER <= "000";
    else
        sOPER <= "111";
    end if;
end process;
```

Isto tako, prioritetni koder možemo napisati koristeći `case` naredbu:

```vhdl
process (iOP) is
begin
    case iOP is
        when "10000" =>
            sOPER <= "100";
        when "01000" =>
            sOPER <= "011";
        when "00100" =>
            sOPER <= "010";
        when "00010" =>
            sOPER <= "001";
        when "00001" =>
            sOPER <= "000";
        when others =>
            sOPER <= "111";
    end case;
end process;
```

###  3. Napisati novi izlaz oGREAT koji se pali ako su 3 niža bita rezultata veća od 3.

Kako bi dodali novi izlaz oGREAT, potrebno je izmeniti listu izlaznih portova:

```vhdl
port(
        -- ...
        
        -- izlazni portovi
        oRES   : out std_logic_vector(3 downto 0);
        oCARRY : out std_logic;
        oSIGN  : out std_logic;
        oZERO  : out std_logic;
        oSEGM  : out std_logic_vector(6 downto 0);
        oGREAT : out std_logic; -- dodatni izlaz
);
```

Zatim, potrebno je dodeliti vrednost oGREAT izlazu na sledeći način:

```vhdl
    oRES <= sRES(3 downto 0); -- Postavljamo izlaz

    oGREAT <= '1' when sRES(2) = '1' else '0'; -- Računamo oGREAT tako što proveravamo 3 (najviši bit) od 3 koja posmatramo
```

###  4. Dodati izlaz oYELLOW koji svetli žuto ukoliko je sRES veći od 3.

Kako bi dodali novi izlaz oYELLOW, potrebno je izmeniti listu izlaznih portova:

```vhdl
port(
        -- ...
        
        -- izlazni portovi
        oRES   : out std_logic_vector(3 downto 0);
        oCARRY : out std_logic;
        oSIGN  : out std_logic;
        oZERO  : out std_logic;
        oSEGM  : out std_logic_vector(6 downto 0);
        oYELLOW: out std_logic; -- dodatni izlaz
);
```

Zatim, potrebno je dodeliti vrednost oYELLOW izlazu na sledeći način:

```vhdl
    oRES <= sRES(3 downto 0); -- Postavljamo izlaz

    oYELLOW <= '1' when sRES > "00011" else '0'; -- Računamo oYELLOW tako što proveravamo da li je sRES veći od 3
```

###  5. Dodati novi signal sPOM koji čuva višak bitova pri pomeranju bitova.

Kako bi dodali novi signal sPOM, potrebno je izmeniti listu signala:

```vhdl
architecture Behavioral of lprs1_homework1 is
    signal sOPER : std_logic_vector(2 downto 0);
    signal sRES : std_logic_vector(4 downto 0);
    signal sRESsm : std_logic_vector(3 downto 0);
    signal sPOM : std_logic; -- novi signal za višak bitova pri pomeranju
begin
```

A potom je potrebno dodati logiku koja će čuvati višak bitova pri pomeranju bitova:

```vhdl
process (sOPER, iA, iB) begin
    if (sOPER = "100") then
        -- sabiranje
    elsif (sOPER = "011") then
        -- oduzimanje
    elsif (sOPER = "010") then
        -- logicka AND
    elsif (sOPER = "001") then
        sPOM <= iA(3); -- čuvamo najviši bit pre pomeranja
        -- pomeranje ulevo iA (jednom)
    elsif (sOPER = "000") then
        sPOM <= iB(0); -- čuvamo najniži bit pre pomeranja
        -- aritmeticko pomeranje udesno iB (jednom)
    else
        sRES <= "00000";
    end if;
end process;
```

###  6. Šiftovati ulevo neki ulaz za 4 mesta.

Prvo, proširite sOPER signal tako da uključite kod za šiftovanje za 4 mesta. Na primer, koristimo vrednost "110" za ovu operaciju:

```vhdl
sOPER <= "100" when iOP(4)='1' else -- sabiranje
         "011" when iOP(3)='1' else -- oduzimanje
         "010" when iOP(2)='1' else -- logicka AND operacija
         "001" when iOP(1)='1' else -- Pomeranje iA ulevo za jedno mesto
         "110" when iOP(0)='1' else -- Pomeranje iA ulevo za 4 mesta
         "111";                     -- bez operacije i sRES = 0
```

Zatim, dodajte logiku za šiftovanje ulevo za 4 mesta:

```vhdl
alu: process (sOPER, iA, iB) begin
    if (sOPER = "100") then
        -- sabiranje
    elsif (sOPER = "011") then
        -- oduzimanje
    elsif (sOPER = "010") then
        -- logicka AND
    elsif (sOPER = "001") then
        -- pomeranje ulevo iA (jednom)
    elsif (sOPER = "110") then
        sRES <= "00000"; -- svi bitovi postaju 0 pri šiftovanju ulevo za 4 mesta
    elsif (sOPER = "000") then
        -- aritmeticko pomeranje udesno iB (jednom)
    else
        sRES <= "00000";
    end if;
end process alu;
```