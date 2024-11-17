library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
           iSEL    : in  std_logic_vector(1 downto 0);
           iDATA   : in	 std_logic_vector(4 downto 0);
			  oRESULT : out std_logic_vector(4 downto 0));
end Zadatak;

architecture Behavioral of Zadatak is


begin

	

end Behavioral;