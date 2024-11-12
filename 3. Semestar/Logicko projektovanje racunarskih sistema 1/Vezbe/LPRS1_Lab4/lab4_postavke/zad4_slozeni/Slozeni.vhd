library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Slozeni is port (
		iCLK   : in  std_logic;
      iRST   : in  std_logic;
      iEN    : in  std_logic;
		oCNT   : out std_logic_vector (7 downto 0);
      oSHREG : out  std_logic_vector (7 downto 0)
		);
end entity;

architecture Behavioral of Slozeni is


begin

	
end architecture;
