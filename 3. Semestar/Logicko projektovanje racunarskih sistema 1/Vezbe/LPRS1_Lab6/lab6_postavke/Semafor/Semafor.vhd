library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	iCLK    : in  std_logic;
				iRST    : in  std_logic;
				iOK     : in  std_logic;
				iHAZ    : in  std_logic;
				oRED    : out std_logic;
				oYELLOW : out std_logic;
				oGREEN  : out std_logic);
end Semafor;

architecture Behavioral of Semafor is


begin
 
	
end Behavioral;