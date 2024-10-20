library ieee;
use ieee.std_logic_1164.all;

entity mux_tb is
end mux_tb;


architecture Behavioral of mux_tb is
	
	signal sX0 : std_logic;
	signal sX1 : std_logic;
	signal sX2 : std_logic;
	signal sX3 : std_logic;
	signal sSEL : std_logic_vector(1 downto 0);
	signal sY : std_logic;
	
	component mux is
		port(
			iX0 : in std_logic;
			iX1 : in std_logic;
			iX2 : in std_logic;
			iX3 : in std_logic;
			iSEL : in std_logic_vector(1 downto 0);
			oY : out std_logic
		);
	end component;

begin

	uut : entity work.mux(if_else) port map(
		iX0 => sX0,
		iX1 => sX1,
		iX2 => sX2,
		iX3 => sX3,
		iSEL => sSEL,
		oY => sY
	);

	stimulus: process
	begin
	
		sX0 <= '1';
		sX1 <= '0';
		sX2 <= '1';
		sX3 <= '0';
		
		sSEL <= "00";
		wait for 200 ns;
		
		sSEL <= "01";
		wait for 200 ns;
		
		sSEL <= "10";
		wait for 200 ns;
		
		sSEL <= "11";
		wait;
		
	end process stimulus;
	
end architecture;