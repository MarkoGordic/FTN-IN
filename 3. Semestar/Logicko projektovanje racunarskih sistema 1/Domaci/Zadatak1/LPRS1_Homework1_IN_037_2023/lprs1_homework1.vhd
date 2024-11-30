library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_signed.all;

entity lprs1_homework1 is
	port(
		-- ulazni portovi
		iA  : in std_logic_vector(3 downto 0);
		iB  : in std_logic_vector(3 downto 0);
		iOP : in std_logic_vector(4 downto 0);
		
		-- izlazni portovi
		oRES 	 : out std_logic_vector(3 downto 0);
		oZERO  : out std_logic;
		oSIGN  : out std_logic;
		oCARRY : out std_logic;
		oSEGM  : out std_logic_vector(6 downto 0)
	);
end entity;

architecture Behavioral of lprs1_homework1 is
	signal sOPER : std_logic_vector(2 downto 0);
	signal sRES : std_logic_vector(4 downto 0);
	signal sRESsm : std_logic_vector(3 downto 0);
	
begin
	-- prioritetni koder
	sOPER <= "100" when iOP(4)='1' else -- sabiranje
				"011" when iOP(3)='1' else -- oduzimanje
				"010" when iOP(2)='1' else -- logicka AND operacija
				"001" when iOP(1)='1' else -- Pomeranje iA ulevo za jedno mesto
				"000" when iOP(0)='1' else -- operacija po izboru
				"111";							-- bez operacije i sRES = 0
	
	-- ALU jedinica IF-ELSE
	alu: process (sOPER, iA, iB) begin
		-- sabiranje
		if (sOPER = "100") then
			sRES <= (iA(3) & iA) + (iB(3) & iB);
		-- oduzimanje
		elsif (sOPER = "011") then
			sRES <= ('0' & iA) - ('0' & iB);
		-- logicka AND
		elsif (sOPER = "010") then
			sRES <= '0' & (iA and iB); -- vrsim and i dodajem 0 na carry flag
		-- pomeranje ulevo iA (jednom)
		elsif (sOPER = "001") then
			sRES <= iA(3 downto 0) & '0';
		-- aritmeticko pomeranje udesno iB (jednom)
		elsif (sOPER = "000") then
			sRES <= iB(3) & iB(3) & iB(3 downto 1);
		else
			sRES <= "00000";
		end if;
	end process alu;

	oZERO <= '1' when sRES(3 downto 0) = "0000" else '0'; -- nula
	oSIGN <= '1' when sRES(3)='1' else '0'; -- znak
	oCARRY <= '1' when ((iA(3) xor iB(3) xor sRES(4)) = '1') and sOPER="100" else '0'; -- carry
	
	-- diode
	oRES <= sRES(3 downto 0);
	sRESsm <= sRES(3 downto 0);
	
	-- dekoder za 7-segmentni displej (od -8 do +7)
	-- razliku za - i + pravimo tako sto gledamo da li gori SIGN lampica na semaforu
	process (sRESsm) begin
		 case (sRESsm) is 
			  when "0000" => oSEGM <= "0000001";  -- Izlaz za 0
			  when "0001" => oSEGM <= "1001111";  -- Izlaz za 1
			  when "0010" => oSEGM <= "0010010";  -- Izlaz za 2
			  when "0011" => oSEGM <= "0000110";  -- Izlaz za 3
			  when "0100" => oSEGM <= "1001100";  -- Izlaz za 4
			  when "0101" => oSEGM <= "0100100";  -- Izlaz za 5
			  when "0110" => oSEGM <= "0100000";  -- Izlaz za 6
			  when "0111" => oSEGM <= "0001111";  -- Izlaz za 7
			  -- when "1000" => oSEGM <= "0000000";  -- Izlaz za 8
			  -- when "1001" => oSEGM <= "0000100";  -- Izlaz za 9
			  when "1111" => oSEGM <= "1001111";  -- Izlaz za -1
			  when "1110" => oSEGM <= "0010010";  -- Izlaz za -2
			  when "1101" => oSEGM <= "0000110";  -- Izlaz za -3
			  when "1100" => oSEGM <= "1001100";  -- Izlaz za -4
			  when "1011" => oSEGM <= "0100100";  -- Izlaz za -5
			  when "1010" => oSEGM <= "0100000";  -- Izlaz za -6
			  when "1001" => oSEGM <= "0001111";  -- Izlaz za -7
			  when "1000" => oSEGM <= "0000000";  -- Izlaz za -8
			  when others => oSEGM <= "1111111";  -- Default case (sve iskljuceno)
		 end case;
	end process;

	
end architecture;