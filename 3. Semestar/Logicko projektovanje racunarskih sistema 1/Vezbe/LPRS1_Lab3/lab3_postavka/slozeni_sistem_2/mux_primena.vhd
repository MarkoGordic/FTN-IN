library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;


entity mux_primena is
	port(
		iA : in std_logic_vector(3 downto 0);
		iB : in std_logic_vector(3 downto 0);
		iSEL : in std_logic_vector(1 downto 0);
		oC : out std_logic_vector(3 downto 0)
	);
end entity;


architecture Behavioral of mux_primena is
	
begin

end architecture;