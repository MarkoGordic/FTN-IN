library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity PomReg is port (
		iRST   : in  std_logic;
      iCLK   : in  std_logic;
      iLOAD  : in  std_logic;
		iARITH : in  std_logic;
		iSHL   : in  std_logic;
		iSHR   : in  std_logic;
		iDATA  : in  std_logic_vector(7 downto 0);
		oSHREG : out std_logic_vector(7 downto 0)
		);
end entity;

architecture Behavioral of PomReg is
    	 
begin
	

end architecture;
