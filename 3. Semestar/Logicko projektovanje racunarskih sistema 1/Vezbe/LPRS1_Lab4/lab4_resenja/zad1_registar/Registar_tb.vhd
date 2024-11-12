library ieee;
use ieee.std_logic_1164.all;

entity Registar_tb is
end entity;
 
architecture Test of Registar_tb is
  
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
	signal sD : std_logic_vector(7 downto 0);
   signal sWE : std_logic  := '0';
   signal sQ : std_logic_vector(7 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component Registar is  
			port (
				iCLK 	: in  std_logic;
				iRST 	: in  std_logic;
				iD 	: in  std_logic_vector (7 downto 0);
				iWE 	: in  std_logic;
				oQ 	: out std_logic_vector (7 downto 0)
		);
   end component;

begin

   uut: Registar port map (
          iCLK => sCLK,
          iRST => sRST,
          iD	=> sD,
			 iWE	=> sWE,
          oQ	=> sQ
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   stimulus : process
   begin
		-- 1. resetovanje sistema 2.25 perioda takta (NECELOBROJNA VREDNOST!)
		sRST <= '1';  		
		wait for 2.25* iCLK_PERIOD;
		sRST <= '0';
		-- 2. Signal iD = 5, 2 perioda + iWE = 0
		sD <= "00000101"; 
		wait for 2 * iCLK_PERIOD;
		-- 3. Aktivirati iWE 2 perioda, iD na -1 i deaktivirati iWE.
		sWE <= '1';
		wait for 2 * iCLK_PERIOD;
		sD <= "11111111";
		sWE <= '0';
		wait for iCLK_PERIOD;
		-- 4. Ponovo aktivirati iWE 2 perioda, a zatim deaktivirati.
		sWE <= '1';
		wait for 2 * iCLK_PERIOD;
		sWE <= '0';
		wait for 1 * iCLK_PERIOD;
		-- 5. Postaviti iD na vrednost 15 ukupno 2 perioda.
		sD <= "00001111";
		wait for 2 * iCLK_PERIOD;
		-- 6. Resetovati sistem 2 perioda takta i ponovo pokrenuti sistem
		sRST <= '1';
		wait for 2* iCLK_PERIOD;
		sRST <= '0';
		-- 7. Aktivirati signal dozvole upisa 2 perioda, a zatim deaktivirati
		sWE <= '1';
		wait for 2 * iCLK_PERIOD;
		sWE <= '0';
		wait;

   end process;
end architecture;
