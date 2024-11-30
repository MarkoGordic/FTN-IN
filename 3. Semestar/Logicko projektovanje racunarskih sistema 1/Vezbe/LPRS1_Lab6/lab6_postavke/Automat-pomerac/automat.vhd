library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity automat is
    Port ( 	iCLK    	: in  std_logic;
				iRST    	: in  std_logic;
				iSTOP   	: in  std_logic;
				iRL	   : in  std_logic;
				iRR		: in  std_logic;
				iSRA		: in 	std_logic;
				oDATA		: out std_logic_vector(7 downto 0));
end automat;

architecture Behavioral of automat is


begin


end architecture;