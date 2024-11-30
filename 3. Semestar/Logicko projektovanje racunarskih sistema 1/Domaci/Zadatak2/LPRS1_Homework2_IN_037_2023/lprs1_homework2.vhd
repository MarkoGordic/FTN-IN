library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity lprs1_homework2 is
    port (
        iCLK        : in  std_logic;
        iRST        : in  std_logic;

        iSTART      : in  std_logic;
        iTEAM_A     : in  std_logic;
        iTEAM_B     : in  std_logic;
        iPOINTS     : in  std_logic_vector(1 downto 0);

        oA_WIN      : out std_logic;
        oB_WIN      : out std_logic;
		  
		  oGREEN		  : out std_logic;

        ------ ============== DISPLAY =================== ------
        oDIS        : out std_logic_vector(1 downto 0);
        o7SEGM      : out std_logic_vector(6 downto 0)
    );
end entity;

architecture Behavioral of lprs1_homework2 is

-- Funkcija koja dekodira prosleđeni std_logic_vector u novi vektor koji sadrži cifru za 7-segm displej
function decode_7segm(value : std_logic_vector(3 downto 0)) return std_logic_vector is
    variable segm : std_logic_vector(6 downto 0);
begin
    case value is
        when "0000" => segm := "0000001";  -- Prikazuje 0
        when "0001" => segm := "1001111";  -- Prikazuje 1
        when "0010" => segm := "0010010";  -- Prikazuje 2
        when "0011" => segm := "0000110";  -- Prikazuje 3
        when "0100" => segm := "1001100";  -- Prikazuje 4
        when "0101" => segm := "0100100";  -- Prikazuje 5
        when "0110" => segm := "0100000";  -- Prikazuje 6
        when "0111" => segm := "0000111";  -- Prikazuje 7
        when "1000" => segm := "0000000";  -- Prikazuje 8
        when "1001" => segm := "0000100";  -- Prikazuje 9
        when others => segm := "1111111";  -- Prikazuje prazno (greška)
    end case;

    return segm;
end function;

-- Signal deklaracije
signal sSTART             : std_logic;

signal sA_SCORE_UNITS     : std_logic_vector(3 downto 0);
signal sA_SCORE_TENS      : std_logic_vector(3 downto 0);
signal sA_CNT_EN          : std_logic;
signal sA_POINT_ADDED     : std_logic;
signal sA_TENS_COUNT_EN   : std_logic;
signal sWIN_A             : std_logic;

signal sB_SCORE_UNITS     : std_logic_vector(3 downto 0);
signal sB_SCORE_TENS      : std_logic_vector(3 downto 0);
signal sB_CNT_EN          : std_logic;
signal sB_POINT_ADDED     : std_logic;
signal sB_TENS_COUNT_EN   : std_logic;
signal sWIN_B             : std_logic;
signal sGREEN				  : std_logic;

------------ =============================================== -------------
signal sTC                : std_logic;  -- Indikator dozvole za promenu displeja
signal sDIS_SEL           : std_logic_vector(1 downto 0);
signal sDIS_CNT           : std_logic_vector(14 downto 0);
constant cDIS_MAX         : std_logic_vector(14 downto 0) := "111111111111111";

signal sDISPLAY_0         : std_logic_vector(6 downto 0); -- Izlazi iz 7SEG dekodera
signal sDISPLAY_1         : std_logic_vector(6 downto 0); -- Izlazi iz 7SEG dekodera
signal sDISPLAY_2         : std_logic_vector(6 downto 0); -- Izlazi iz 7SEG dekodera
signal sDISPLAY_3         : std_logic_vector(6 downto 0); -- Izlazi iz 7SEG dekodera

begin

-- Postavljamo vrednost za START signal
sSTART <= iSTART;

-- Dodela vrednosti signalima za dozvolu brojanja za tim A i tim B
sA_CNT_EN <= '1' when (iTEAM_A = '1' and sA_POINT_ADDED = '0' and sWIN_A = '0' and sWIN_B = '0') else '0';
sB_CNT_EN <= '1' when (iTEAM_B = '1' and sB_POINT_ADDED = '0' and sWIN_A = '0' and sWIN_B = '0') else '0';

-- =================== TIM A =======================

-- A_POINT_ADDED registar
-- ULAZ: iTEAM_A, sA_CNT_EN
-- IZLAZ: sA_POINT_ADDED
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sA_POINT_ADDED <= '0';
    elsif (rising_edge(iCLK)) then
        if iTEAM_A = '0' then
            sA_POINT_ADDED <= '0';
        elsif sA_CNT_EN = '1' then
            sA_POINT_ADDED <= '1';
        else
            sA_POINT_ADDED <= sA_POINT_ADDED;
        end if;
    end if;
end process;

-- A_SCORE_UNITS registar
-- ULAZ: iPOINTS, sA_POINT_ADDED, sA_CNT_EN
-- IZLAZ: sA_SCORE_UNITS
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sA_SCORE_UNITS <= "0000";
    elsif (rising_edge(iCLK)) then
        if sSTART = '1' then
            -- Dodavanje poena za tim A na osnovu stanja enable signala za brojanje
            if sA_CNT_EN = '1' and sA_POINT_ADDED = '0' then
                case iPOINTS is
                    when "01" => sA_SCORE_UNITS <= sA_SCORE_UNITS + 1;
                    when "10" => sA_SCORE_UNITS <= sA_SCORE_UNITS + 2;
                    when "11" => sA_SCORE_UNITS <= sA_SCORE_UNITS + 3;
                    when others => null;
                end case;
            end if;

            -- Provera za povećanje desetica
            if sA_SCORE_UNITS > "1001" then
                sA_SCORE_UNITS <= sA_SCORE_UNITS - "1010";  -- Oduzimamo 10
            end if;
        end if;
    end if;
end process;

-- A_TENS_COUNT_EN registar
-- ULAZ: sA_SCORE_UNITS
-- IZLAZ: sA_TENS_COUNT_EN
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sA_TENS_COUNT_EN <= '0';
    elsif (rising_edge(iCLK)) then
        if sSTART = '1' then
            if sA_SCORE_UNITS > "1001" then
                sA_TENS_COUNT_EN <= '1';
            else
                sA_TENS_COUNT_EN <= '0';
            end if;
        else
            sA_TENS_COUNT_EN <= '0';
        end if;
    end if;
end process;

-- A_SCORE_TENS registar
-- ULAZ: sA_TENS_COUNT_EN
-- IZLAZ: sA_SCORE_TENS 

process(iCLK, iRST)
begin
    if (iRST = '1') then
        sA_SCORE_TENS <= "0000";
    elsif (rising_edge(iCLK)) then
        if sA_TENS_COUNT_EN = '1' then
            sA_SCORE_TENS <= sA_SCORE_TENS + 1;
        end if;
    end if;
end process;

-- sWIN_A registar
-- ULAZ: sA_SCORE_UNITS, sA_SCORE_TENS
-- IZLAZ: sWIN_A
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sWIN_A <= '0';
    elsif (rising_edge(iCLK)) then
        if sA_SCORE_TENS > "0010" or (sA_SCORE_TENS = "0010" and sA_SCORE_UNITS > "0000") then
            sWIN_A <= '1';
        end if;
    end if;
end process;

-- Izlaz za pobednika tima A
oA_WIN <= sWIN_A;

-- =================== TIM B =======================

-- B_POINT_ADDED registar
-- ULAZ: iTEAM_B, sB_CNT_EN
-- IZLAZ: sB_POINT_ADDED
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sB_POINT_ADDED <= '0';
    elsif (rising_edge(iCLK)) then
        if iTEAM_B = '0' then
            sB_POINT_ADDED <= '0';
        elsif sB_CNT_EN = '1' then
            sB_POINT_ADDED <= '1';
        else
            sB_POINT_ADDED <= sB_POINT_ADDED;
        end if;
    end if;
end process;

-- B_SCORE_UNITS registar
-- ULAZ: iPOINTS, sB_POINT_ADDED, sB_CNT_EN
-- IZLAZ: sB_SCORE_UNITS
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sB_SCORE_UNITS <= "0000";
    elsif (rising_edge(iCLK)) then
        if sSTART = '1' then
            -- Dodavanje poena za tim B na osnovu stanja enable signala za brojanje
            if sB_CNT_EN = '1' and sB_POINT_ADDED = '0' then
                case iPOINTS is
                    when "01" => sB_SCORE_UNITS <= sB_SCORE_UNITS + 1;
                    when "10" => sB_SCORE_UNITS <= sB_SCORE_UNITS + 2;
                    when "11" => sB_SCORE_UNITS <= sB_SCORE_UNITS + 3;
                    when others => null;
                end case;
            end if;

            -- Provera za povećanje desetica
            if sB_SCORE_UNITS > "1001" then
                sB_SCORE_UNITS <= sB_SCORE_UNITS - "1010";  -- Oduzimamo 10
            end if;
        end if;
    end if;
end process;

-- B_TENS_COUNT_EN registar
-- ULAZ: sB_SCORE_UNITS
-- IZLAZ: sB_TENS_COUNT_EN
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sB_TENS_COUNT_EN <= '0';
    elsif (rising_edge(iCLK)) then
        if sSTART = '1' then
            if sB_SCORE_UNITS > "1001" then
                sB_TENS_COUNT_EN <= '1';
            else
                sB_TENS_COUNT_EN <= '0';
            end if;
        else
            sB_TENS_COUNT_EN <= '0';
        end if;
    end if;
end process;

-- B_SCORE_TENS registar
-- ULAZ: sB_TENS_COUNT_EN
-- IZLAZ: sB_SCORE_TENS
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sB_SCORE_TENS <= "0000";
    elsif (rising_edge(iCLK)) then
        if sB_TENS_COUNT_EN = '1' then
            sB_SCORE_TENS <= sB_SCORE_TENS + 1;
        end if;
    end if;
end process;

-- sWIN_B registar
-- ULAZ: sB_SCORE_UNITS, sB_SCORE_TENS
-- IZLAZ: sWIN_B
process(iCLK, iRST)
begin
    if (iRST = '1') then
        sWIN_B <= '0';
    elsif (rising_edge(iCLK)) then
        if sB_SCORE_TENS > "0010" or (sB_SCORE_TENS = "0010" and sB_SCORE_UNITS > "0000") then
            sWIN_B <= '1';
        end if;
    end if;
end process;

-- Izlaz za pobednika tima B
oB_WIN <= sWIN_B;

-- ======================= 7SEGM DISPLEJ =============================

-- Proces za vremensko multipleksiranje 7-segm displeja
process(iCLK, iRST)
begin
    if(iRST = '1') then
        sDIS_CNT <= (others => '0');
    elsif(rising_edge(iCLK)) then
        -- Proveravamo da li je DIS_CNT dostigao max vrednost
        if(sDIS_CNT < cDIS_MAX) then
            sDIS_CNT <= sDIS_CNT + 1;
        else
            -- Dostigli smo max vrednost, resetujemo brojač
            sDIS_CNT <= (others => '0');
        end if;
    end if;
end process;

-- sTC registar
-- ULAZ: sDIS_CNT
-- IZLAZ: sTC
process(iCLK, iRST)
begin
    if(iRST = '1') then
        sTC <= '0';
    elsif(rising_edge(iCLK)) then
        if(sDIS_CNT = cDIS_MAX) then
            sTC <= '1'; -- Dozvola promene displeja
        else
            sTC <= '0'; -- Zabrana promene displeja
        end if;
    end if;
end process;

-- sDIS_SEL registar
-- ULAZ: sTC
-- IZLAZ: sDIS_SEL
process(iCLK, iRST)
begin
    if(iRST = '1') then
        sDIS_SEL <= (others => '0');
    elsif(rising_edge(iCLK)) then
        if(sTC = '1') then
            if(sDIS_SEL = "11") then
                -- Mod 4, vraćamo na 0
                sDIS_SEL <= (others => '0');
            else
                -- Prelazimo na sledeći displej
                sDIS_SEL <= sDIS_SEL + 1;
            end if;
        end if;
    end if;
end process;

-- Multiplekser - Ažuriramo izlazni signal za odabir aktivnog displeja
oDIS <= "00" when sDIS_SEL = "00" else
        "01" when sDIS_SEL = "01" else
        "10" when sDIS_SEL = "10" else
        "11";

-- Ažuriramo izlaz na 7-segm na osnovu aktivnog displeja
o7SEGM <= sDISPLAY_0 when sDIS_SEL = "00" else
          sDISPLAY_1 when sDIS_SEL = "01" else
          sDISPLAY_2 when sDIS_SEL = "10" else
          sDISPLAY_3;

-- Proces za dekodiranje 7-segm displeja
-- Pri svakoj promeni jedinica i desetica, računamo nove vrednosti na ekranima i šaljemo u njihove signale.
-- Za to se koristi funkcija koja prima logic vektor broja a vraća odgovarajući logic vektor za 7-segm
process(sA_SCORE_UNITS, sA_SCORE_TENS, sB_SCORE_UNITS, sB_SCORE_TENS)
begin
    -- Tim A sa desne strane
    sDISPLAY_0 <= decode_7segm(sA_SCORE_UNITS);
    sDISPLAY_1 <= decode_7segm(sA_SCORE_TENS);

    -- Tim B sa leve strane
    sDISPLAY_2 <= decode_7segm(sB_SCORE_UNITS);
    sDISPLAY_3 <= decode_7segm(sB_SCORE_TENS);
end process;

oGREEN <= '1' when ((sB_SCORE_TENS > "0001" or (sB_SCORE_TENS = "0001" and sB_SCORE_UNITS > "0001")) or (sA_SCORE_TENS > "0001" or (sA_SCORE_TENS = "0001" and sA_SCORE_UNITS > "0001"))) else '0';

end Behavioral;
