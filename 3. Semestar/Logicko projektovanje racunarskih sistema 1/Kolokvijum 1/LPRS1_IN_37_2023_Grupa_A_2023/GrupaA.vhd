library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity GrupaA is
	port (
		iCLK	: in std_logic;
		iRST	: in std_logic; -- AKTIVAN NA 1
		iD		: in std_logic_vector(7 downto 0); -- digitalni predajnik
		iDEN	: in std_logic; -- dozvola za upis u digitalni predajnik
		oTX	: out std_logic
	);
end entity;

architecture Behavioral of GrupaA is
	
	signal sDR 		: std_logic_vector(7 downto 0);
	signal sEP 		: std_logic; -- bit parnong pariteta
	signal sDRP 	: std_logic_vector(8 downto 0); -- sDR & sEP
	signal sSHIFT 	: std_logic_vector(11 downto 0);
	signal sSEL 	: std_logic_vector(3 downto 0);
	
begin

	-- 8-bitni registar sDR
	process(iRST, iCLK) begin
		if(iRST = '1') then
			sDR <= (others => '0');
		elsif(rising_edge(iCLK)) then
			if(iDEN = '1') then
				sDR <= iD;
			end if;
		end if;
	end process;

	-- EVEN PARITY GENERATOR
	sEP <= sDR(7) xor sDR(6) xor sDR(5) xor sDR(4) xor sDR(3) xor sDR(2) xor sDR(1) xor sDR(0);
	
	-- sDR & sEP
	sDRP <= sDR(7 downto 0) & sEP;
	
	-- pomeracki registar sSHIFT
	process(iRST, iCLK) begin
		if(iRST = '1') then
			sSHIFT <= (others => '0');
		elsif(rising_edge(iCLK)) then
			if(sSHIFT = 0 and iDEN = '1') then
				sSHIFT(11) <= iDEN;
			else
				-- pomeramo registar za 1 mesto udesno
				sSHIFT <= '0' & sSHIFT(11 downto 1);
			end if;
		end if;
	end process;
	
	-- koder
	sSEL <= "1011" when sSHIFT(11) = '1' else
			"1010" when sSHIFT(10) = '1' else
			"1001" when sSHIFT(9) = '1' else
			"1000" when sSHIFT(8) = '1' else
			"0111" when sSHIFT(7) = '1' else
			"0110" when sSHIFT(6) = '1' else
			"0101" when sSHIFT(5) = '1' else
			"0100" when sSHIFT(4) = '1' else
			"0011" when sSHIFT(3) = '1' else
			"0010" when sSHIFT(2) = '1' else
			"0001" when sSHIFT(1) = '1' else
			"0000" when sSHIFT(0) = '1' else
			"0000";
	
	-- multiplekser
	oTX <= '0' 		when sSEL = "0000" else
			 sDRP(0) when sSEL = "0001" else
			 sDRP(1) when sSEL = "0010" else
			 sDRP(2) when sSEL = "0011" else
			 sDRP(3) when sSEL = "0100" else
			 sDRP(4) when sSEL = "0101" else
			 sDRP(5) when sSEL = "0110" else
			 sDRP(6) when sSEL = "0111" else
			 sDRP(7) when sSEL = "1000" else
			 sDRP(8) when sSEL = "1001" else
			 '1';
	
end architecture;