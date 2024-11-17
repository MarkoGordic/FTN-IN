library ieee;
use ieee.std_logic_1164.all;

entity Zadatak_tb is
end Zadatak_tb;

architecture Test_tb of Zadatak_tb is
	signal sCLK 	: std_logic;
	signal sRST 	: std_logic := '0';
	signal sEN 		: std_logic := '0';
	signal sSEL 	: std_logic_vector(1 downto 0) := "00";
	signal sDATA 	: std_logic_vector(4 downto 0) := "00000";
	signal sRESULT : std_logic_vector(4 downto 0);
	
	constant iCLK_period : time := 10 ns;

component Zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
           iSEL    : in  std_logic_vector(1 downto 0);
           iDATA   : in	 std_logic_vector(4 downto 0);
			  oRESULT : out std_logic_vector(4 downto 0));
end component;

begin

	uut : Zadatak port map (
		iCLK 		=> sCLK,
		iRST 		=> sRST,
		iEN 		=> sEN,
		iSEL 		=> sSEL,
		iDATA 	=> sDATA,
		oRESULT	=> sRESULT
	);

	iCLK_process: process
		begin
			sCLK <= '0';
			wait for iCLK_period / 2; 
			sCLK <= '1';
			wait for iCLK_period / 2;
	end process; 

	
	stimulus : process
	begin
		
		wait;
	end process stimulus;

end architecture;