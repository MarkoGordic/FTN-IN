library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity lprs_hello_tb is
end entity;

architecture Test of lprs_hello_tb is

	signal sRST   :  std_logic;
	signal sCLK   :  std_logic;
	signal sDIS   :  std_logic_vector(1 downto 0);
	signal s7SEGM :  std_logic_vector(6 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;

	component lprs_hello is
	port(
		iRST  : in  std_logic;
		iCLK  : in  std_logic;
		oDIS  : out std_logic_vector(1 downto 0);
		o7SEGM : out std_logic_vector(6 downto 0)
	);
	end component;

begin

	uut: lprs_hello port map
	(
		iRST => sRST,
		iCLK => sCLK,
		oDIS => sDIS,
		o7SEGM => s7SEGM
	);
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   stim_proc: process
   begin
		sRST <= '1';
		wait for 3.25 * iCLK_PERIOD;
		sRST <= '0';
		wait;
	end process;
	
end architecture;