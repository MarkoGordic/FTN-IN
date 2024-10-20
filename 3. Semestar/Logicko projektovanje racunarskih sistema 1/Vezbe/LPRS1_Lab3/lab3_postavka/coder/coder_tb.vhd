library ieee;
use ieee.std_logic_1164.all;

entity coder_tb is
end entity;

architecture Behavioral of coder_tb is
	
	signal sX : std_logic_vector(7 downto 0);
	signal sY : std_logic_vector(2 downto 0);

	component coder is
		port(
			iX : in std_logic_vector(7 downto 0);
			oY : out std_logic_vector(2 downto 0)
		);
	end component;
	
begin

	uut : coder port map(
		iX => sX,
		oY => sY
	);
	
	stimulus: process
	begin
	
		wait;
	end process stimulus;

end architecture;