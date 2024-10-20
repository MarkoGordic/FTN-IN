library ieee;
use ieee.std_logic_1164.all;

entity zadatak_tb is
end entity;

architecture Behavioral of zadatak_tb is
	
	signal sA : std_logic_vector(7 downto 0);
	signal sB : std_logic_vector(2 downto 0);
	signal sSEL : std_logic_vector(1 downto 0);
	signal sY : std_logic_vector(3 downto 0);
	signal sZERO : std_logic;

	component zadatak is
		port(
			iA : in std_logic_vector(7 downto 0);
			iB : in std_logic_vector(2 downto 0);
			iSEL : in std_logic_vector(1 downto 0);
			oY : out std_logic_vector(3 downto 0);
			oZERO : out std_logic
		);
	end component;

begin

	uut : zadatak port map(
		iA => sA,
		iB => sB,
		iSEL => sSEL,
		oY => sY,
		oZERO => sZERO
	);
	
	stimulus: process
	begin
	
		
		wait;
	end process stimulus;

end architecture;