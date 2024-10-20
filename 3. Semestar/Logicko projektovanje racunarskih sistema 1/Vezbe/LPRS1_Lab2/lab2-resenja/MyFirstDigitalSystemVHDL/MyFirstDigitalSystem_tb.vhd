library ieee;
use ieee.std_logic_1164.all;

-- prazan entitet za test bench
entity MyFirstDigitalSystem_tb is
end entity;

-- arhitektura digitalnog sistema
architecture Test_tb of MyFirstDigitalSystem_tb is
	
	-- broj signala = broj prolaza glavnog entiteta
	signal sA : std_logic;
	signal sB : std_logic;
	signal sY : std_logic;
	
	-- komponenta koju testiramo - MyFirstDigitalSystem
	component MyFirstDigitalSystem
		port(
			iA : in std_logic;
			iB : in std_logic;
			oY : out std_logic
		);
	end component;
	
	begin
	-- mapiranje glavnih protova i signala test bench-a
	uut : MyFirstDigitalSystem port map (
		iA => sA,
		iB => sB,
		oY => sY
	);
	
	-- zadavanje svih kombinacija ULAZNIH signala
	stimulus : process
	
	begin
		sA <= '0';
		sB <= '0';
		wait for 100 ns;
		sA <= '0';
		sB <= '1';
		wait for 100 ns;
		sA <= '1';
		sB <= '0';
		wait for 100 ns;
		sA <= '1';
		sB <= '1';
		wait;
	
	end process stimulus;
	
end architecture;
