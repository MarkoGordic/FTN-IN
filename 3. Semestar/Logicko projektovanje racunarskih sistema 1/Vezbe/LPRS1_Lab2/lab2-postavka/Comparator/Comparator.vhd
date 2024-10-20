library ieee;
use ieee.std_logic_1164.all;

entity Comparator is
	port(
		iA 		: in std_logic_vector(1 downto 0);
		iB 		: in std_logic_vector(1 downto 0);
		oLESS		: out std_logic;
		oGREAT	: out std_logic;
		oEQUAL	: out std_logic
	    );
end entity;

architecture Behavioral of Comparator is

end architecture;
