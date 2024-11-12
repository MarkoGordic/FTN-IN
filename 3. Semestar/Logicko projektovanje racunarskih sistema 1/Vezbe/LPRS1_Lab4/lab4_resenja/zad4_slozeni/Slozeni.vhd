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

	signal sCNT 	: std_logic_vector(7 downto 0);
	signal sTC		: std_logic;
	signal sLOAD 	: std_logic;
	signal sARITHM : std_logic;
	signal sSHREG	: std_logic_vector(7 downto 0);

begin

	process (iCLK, iRST) begin
		if (iRST = '1') then
			sCNT <= (others => '0');
		elsif (rising_edge(iCLK)) then
			if (iEN = '1' ) then
				sCNT <= sCNT + 1;
			end if;
		end if;
	end process;
	
	sTC <= '1' when sCNT=255 else '0';
	
	oCNT <= sCNT;
	
	sLOAD <= '1' when (sCNT = 8 or sCNT = 128) else '0';
	
	sARITHM <= '1' when sCNT > 128 else '0';
	
	-- pomeracki registar
	
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sSHREG <= "00000000";
		elsif (rising_edge(iCLK)) then
			
			if (sLOAD = '1') then
				sSHREG <= sCNT;
			else
				if (sARITHM = '1') then
					-- >> 1
					sSHREG <= sSHREG(7) & sSHREG(7 downto 1);
				else
					-- << 1
					sSHREG <= sSHREG(6 downto 0) & '0';
				end if;
			end if;
			
		end if;
	end process;
	
	oSHREG <= sSHREG;
	
end architecture;