library ieee;
use ieee.std_logic_1164.all;

entity zadatak_tb is
end entity;

architecture Behavioral of zadatak_tb is
	
	signal sA : std_logic_vector(7 downto 0);
	signal sB : std_logic_vector(2 downto 0);
	signal sSEL : std_logic_vector(1 downto 0);
	signal sY : std_logic_vector(3 downto 0);
	signal sSEGM : std_logic_vector(6 downto 0);
	signal sZERO : std_logic;

	component zadatak is
		port(
			iA : in std_logic_vector(7 downto 0);
			iB : in std_logic_vector(2 downto 0);
			iSEL : in std_logic_vector(1 downto 0);
			oY : out std_logic_vector(3 downto 0);
			oSEGM : out std_logic_vector(6 downto 0);
			oZERO : out std_logic
		);
	end component;

begin

	uut : zadatak port map(
		iA => sA,
		iB => sB,
		iSEL => sSEL,
		oY => sY,
		oSEGM => sSEGM,
		oZERO => sZERO
	);
	
	stimulus: process
	begin
	
		sA <= "00000001";
		sB <= "011";
		
		sSEL <= "00";
		wait for 100 ns;
		
		sSEL <= "01";
		wait for 100 ns;
		
		sSEL <= "10";
		wait for 100 ns;
		
		sSEL <= "11";
		wait for 100 ns;
		
		wait;
	end process stimulus;

end architecture;