library IEEE;
use ieee.std_logic_1164.all;

entity Zadatak_tb is
end Zadatak_tb;

architecture Test_tb of Zadatak_tb is
    signal sCLK     : std_logic := '0';
    signal sRST     : std_logic := '0';
    signal sEN      : std_logic := '0';
    signal sSEL     : std_logic_vector(1 downto 0) := "00";
    signal sDATA    : std_logic_vector(4 downto 0) := "00000";
    signal sRESULT  : std_logic_vector(4 downto 0);

    constant sCLK_PER : time := 10 ns;

    component Zadatak is
        Port (
            iCLK    : in  std_logic;
            iRST    : in  std_logic;
            iEN     : in  std_logic;
            iSEL    : in  std_logic_vector(1 downto 0);
            iDATA   : in  std_logic_vector(4 downto 0);
            oRESULT : out std_logic_vector(4 downto 0)
        );
    end component;
begin
    uut : Zadatak
        port map (
            iCLK    => sCLK,
            iRST    => sRST,
            iEN     => sEN,
            iSEL    => sSEL,
            iDATA   => sDATA,
            oRESULT => sRESULT
        );

    iCLK_process : process
    begin
        while true loop
            sCLK <= '0';
            wait for sCLK_PER / 2;
            sCLK <= '1';
            wait for sCLK_PER / 2;
        end loop;
    end process;

    stimulus : process
    begin
        sRST <= '1';
        wait for 2.25 * sCLK_PER;
        sRST <= '0';

        sEN <= '1';
        sSEL <= "00";
        wait for 10 * sCLK_PER;

        sSEL <= "01";
        wait for 20 * sCLK_PER;

        sDATA <= "00100";
        sSEL <= "10";
        wait for 2 * sCLK_PER;

        sSEL <= "11";
        wait for 5 * sCLK_PER;

        wait;
    end process;
end Test_tb;
