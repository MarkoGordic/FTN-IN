library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Brojac is port ( 
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	iEN   : in  std_logic;
	oCNT  : out std_logic_vector(7 downto 0)
	);
end entity;

architecture Behavioral of Brojac is
	
	
begin
	
end Behavioral;
