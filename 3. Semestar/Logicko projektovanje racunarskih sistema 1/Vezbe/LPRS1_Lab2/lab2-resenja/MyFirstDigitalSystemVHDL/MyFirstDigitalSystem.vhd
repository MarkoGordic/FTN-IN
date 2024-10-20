library ieee;
use ieee.std_logic_1164.all;

entity MyFirstDigitalSystem is

	port(
		iA: in std_logic;
		iB: in std_logic;
		oY: out std_logic
	);

end entity;

architecture Behavioral of MyFirstDigitalSystem is

	-- interni signal sS koji je vidljiv samo unutar arhitekture
	signal sS : std_logic;
	
begin
	-- unutar begin opisujemo rad arhitekture
	sS <= iA and iB;
	oY <= not(sS);
	
	-- moglo se zapisati i kao:
	-- oY <= not (iA and iB);

end architecture;