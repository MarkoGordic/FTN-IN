library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity GrupaA is
	port ( 
			iCLK  	:  in std_logic;
			iRST  	:  in std_logic;
			iEN   	:  in std_logic;
			iDEC		:  in std_logic_vector(2 downto 0);
			oGREAT	: out std_logic;
			oCNTP 	: out std_logic_vector(3 downto 0);
			oCNTN 	: out std_logic_vector(3 downto 0)
	);
end entity;

architecture Behavioral of GrupaA is

	signal sDEC : std_logic_vector(7 downto 0);
	signal sREG : std_logic_vector(7 downto 0);
	signal sSHIFT : std_logic_vector(7 downto 0);
	signal sENP, sENN : std_logic;
	signal sCNTP, sCNTN : std_logic_vector(3 downto 0);
	
begin

-- dekoder
sDEC <= "00000001" when iDEC = "000" else
		  "00000010" when iDEC = "001" else
		  "00000100" when iDEC = "010" else
		  "00001000" when iDEC = "011" else
		  "00010000" when iDEC = "100" else
		  "00100000" when iDEC = "101" else
		  "01000000" when iDEC = "110" else
		  "10000000";

-- registar
process(iRST, iCLK) begin
	if (iRST = '1') then
		sREG <= (others => '0');
	elsif(rising_edge(iCLK)) then
		if(iEN = '1') then
			sREG <= sDEC;
		end if;
	end if;
end process;

-- pomerac za 2 mesta udesno
sSHIFT <= sREG(7) & sREG(7) & sREG(7 downto 2);

-- komparator
oGREAT <= '1' when sSHIFT > "00000011" else '0';

-- parnost
process(sREG) begin
	if(sREG(0) = '0') then -- paran
		sENP <= '1';
		sENN <= '0';
	else -- neparan
		sENP <= '0';
		sENN <= '1';
	end if;
end process;

-- brojac parnih
process(iCLK, iRST) begin
	if(iRST = '1') then
		sCNTP <= (others => '0');
	elsif(rising_edge(iCLK)) then
		if(sENP = '1') then
			sCNTP <= sCNTP + 1;
		end if;
	end if;
end process;

-- brojac neparnih
process(iCLK, iRST) begin
	if(iRST = '1') then
		sCNTN <= (others => '0');
	elsif(rising_edge(iCLK)) then
		if(sENN = '1') then
			sCNTN <= sCNTN + 1;
		end if;
	end if;
end process;

oCNTP <= sCNTP;
oCNTN <= sCNTN;

end Behavioral;
