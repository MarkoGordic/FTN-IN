library ieee;
use ieee.std_logic_1164.all;

entity mux_primena_tb is
end entity;

architecture Behavioral of mux_primena_tb is
	
	signal sA : std_logic_vector(3 downto 0);
	signal sB : std_logic_vector(3 downto 0);
	signal sSEL : std_logic_vector(1 downto 0);
	signal sC : std_logic_vector(3 downto 0);

	component mux_primena is
		port(
			iA : in std_logic_vector(3 downto 0);
			iB : in std_logic_vector(3 downto 0);
			iSEL : in std_logic_vector(1 downto 0);
			oC : out std_logic_vector(3 downto 0)
		);
	end component;

begin

	uut : mux_primena port map(
		iA => sA,
		iB => sB,
		iSEL => sSEL,
		oC => sC
	);
	
	stimulus: process
	begin

		wait;
	end process stimulus;

end architecture;