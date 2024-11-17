library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Zadatak is
    Port (
        iCLK    : in  std_logic;
        iRST    : in  std_logic;
        iEN     : in  std_logic;
        iSEL    : in  std_logic_vector(1 downto 0);
        iDATA   : in  std_logic_vector(4 downto 0);
        oRESULT : out std_logic_vector(4 downto 0)
    );
end Zadatak;

architecture Behavioral of Zadatak is
    signal sCNT     : std_logic_vector(4 downto 0) := "00000";
    signal sFX      : std_logic_vector(4 downto 0);
    signal sSHREG   : std_logic_vector(4 downto 0) := "01010";
    signal sCOMP    : std_logic_vector(4 downto 0);
    signal sCONST   : std_logic_vector(4 downto 0) := "10001"; -- 17
begin
    -- Brojac
    process(iCLK, iRST)
    begin
        if iRST = '1' then
            sCNT <= "00000";
        elsif rising_edge(iCLK) then
            if iEN = '1' then
                sCNT <= sCNT + 1;
            end if;
        end if;
    end process;

    -- Pomeracki registar
    process(iCLK, iRST)
    begin
        if iRST = '1' then
            sSHREG <= "01010";
        elsif rising_edge(iCLK) then
            if sCNT(0) = '0' then
                sSHREG <= sSHREG(0) & sSHREG(4 downto 1);
            end if;
        end if;
    end process;

    -- Komplementer
    sCOMP <= not iDATA + 1;

    -- F(x) = sCNT + 3
    sFX <= sCNT + "00011";

    -- Multiplekser
    with iSEL select
        oRESULT <= sFX     when "00",
                   sSHREG   when "01",
                   sCOMP    when "10",
                   sCONST   when others;
end Behavioral;
