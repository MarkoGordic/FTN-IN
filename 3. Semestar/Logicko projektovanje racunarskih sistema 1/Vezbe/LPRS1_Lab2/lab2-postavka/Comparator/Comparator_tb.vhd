library ieee;
use ieee.std_logic_1164.all;

-- entitet test bench-a je bez prolaza
entity Comparator_tb is
end Comparator_tb;

architecture Test_tb of Comparator_tb is

	-- broj signala = broj prolaza glavnog entiteta
	signal sA : std_logic_vector(1 downto 0);
	signal sB : std_logic_vector(1 downto 0);
	signal sLESS 	: std_logic;
	signal sGREAT 	: std_logic;
	signal sEQUAL	: std_logic;
	
	-- komponenta koju testiramo - Comparator
	component Comparator is
	port(
		iA 		: in std_logic_vector(1 downto 0);
		iB 		: in std_logic_vector(1 downto 0);
		oLESS		: out std_logic;
		oGREAT	: out std_logic;
		oEQUAL	: out std_logic
	    );
	end component;
	
	begin
	-- mapiranje glavnih portova i signala test bench-a
	uut : entity work.Comparator(if_else) port map (
	 	iA => sA,
	 	iB => sB,
	 	oLESS => sLESS,
		oGREAT => sGREAT,
		oEQUAL => sEQUAL
	 );

	-- TO DO: Testirati sve opisane arhitekture entiteta Component
	
	-- zadavanje svih kombinacija ULAZNIH signala
	stimulus : process
	begin
		sA <= "00";
		sB <= "00";
		wait for 100 ns;
		sA <= "00";
		sB <= "01";
		-- TO DO: dodati preostale kombinacije ulaza A i B
	end process stimulus;
end architecture;
