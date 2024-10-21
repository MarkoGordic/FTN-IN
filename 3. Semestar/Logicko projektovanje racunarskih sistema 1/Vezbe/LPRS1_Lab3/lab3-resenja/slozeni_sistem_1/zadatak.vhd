library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zadatak is
	port(
		iA : in std_logic_vector(7 downto 0);
		iB : in std_logic_vector(2 downto 0);
		iSEL : in std_logic_vector(1 downto 0);
		oY : out std_logic_vector(3 downto 0);
		oSEGM : out std_logic_vector(6 downto 0);
		oZERO : out std_logic
	);
end entity;

architecture Behavioral of zadatak is
	-- interni signali
	signal sENC : std_logic_vector(2 downto 0);
	
	-- definisemo sabirke i rezultat
	signal sADD_A : std_logic_vector(3 downto 0);
	signal sADD_B : std_logic_vector(3 downto 0);
	signal sADD : std_logic_vector(3 downto 0);
	
	signal sCOMPL : std_logic_vector(3 downto 0);
	signal sSHR : std_logic_vector(3 downto 0);
	signal sDEC : std_logic_vector(7 downto 0);
	signal sMUX  : std_logic_vector(3 downto 0);
	
begin
	-- prioritetni koder
	sENC <= "111" when iA(7)='1' else
	        "110" when iA(6)='1' else
			  "101" when iA(5)='1' else
			  "100" when iA(4)='1' else
			  "011" when iA(3)='1' else
			  "010" when iA(2)='1' else
			  "001" when iA(1)='1' else
			  "000" when iA(0)='1' else
			  "011";
	
	-- prenos
	sADD_A <= '0' & sENC;
	sADD_B <= '0' & iB;
	
	-- sabirac
	sADD <= sADD_A + sADD_B;

	-- komplementer
	sCOMPL <= not(sADD) + '1';
	
	-- pomerac
	sSHR <= sADD(3) & sADD(3) & sADD(3 downto 2);
	
	-- dekoder
	sDEC <= "00000001" when iB="000" else
			  "00000010" when iB="001" else
			  "00000100" when iB="010" else
			  "00001000" when iB="011" else
			  "00010000" when iB="100" else
			  "00100000" when iB="101" else
			  "01000000" when iB="110" else
			  "10000000";
			  
	-- multiplekser
	sMUX <= sCOMPL when iSEL = "00" else
			  sSHR when iSEL = "01" else
			  sDEC(7 downto 4) when iSEL = "10" else
			  sDEC(3 downto 0);
			  
	oY <= sMUX;
	
	oZERO <= '1' when SMUX = 0 else '0';
	
	process (sMUX) begin
		 case (sMUX) is 
			  when "0000" => oSEGM <= "0000001";  -- Izlaz za 0
			  when "0001" => oSEGM <= "1001111";  -- Izlaz za 1
			  when "0010" => oSEGM <= "0010010";  -- Izlaz za 2
			  when "0011" => oSEGM <= "0000110";  -- Izlaz za 3
			  when "0100" => oSEGM <= "1001100";  -- Izlaz za 4
			  when "0101" => oSEGM <= "0100100";  -- Izlaz za 5
			  when "0110" => oSEGM <= "0100000";  -- Izlaz za 6
			  when "0111" => oSEGM <= "0001111";  -- Izlaz za 7
			  when "1000" => oSEGM <= "0000000";  -- Izlaz za 8
			  when "1001" => oSEGM <= "0000100";  -- Izlaz za 9
			  when others => oSEGM <= "1111111";  -- Default case (sve iskljuceno)
		 end case;
	end process;
	
end architecture;