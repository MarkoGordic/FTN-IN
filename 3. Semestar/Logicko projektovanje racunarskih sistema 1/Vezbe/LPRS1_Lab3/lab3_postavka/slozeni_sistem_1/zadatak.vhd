library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zadatak is
	port(
		iA : in std_logic_vector(7 downto 0);
		iB : in std_logic_vector(2 downto 0);
		iSEL : in std_logic_vector(1 downto 0);
		oY : out std_logic_vector(3 downto 0);
		oSEGM : out std_logic_vector(6 downto 0);
		oZERO : out std_logic
	);
end entity;

architecture Behavioral of zadatak is
	
begin

end architecture;