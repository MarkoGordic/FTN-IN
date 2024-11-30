-------------------------------------------------------------
-- Ime i prezime: Marko Gordic
-- Broj indeksa: IN 37/2023
-- Grupa na vežbama: 3.
-- Asistent: Aleks
-------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity lprs1_homework2_tb is
end entity;
 
architecture Test of lprs1_homework2_tb is
  
   signal sCLK 	: std_logic := '0';
   signal sRST    : std_logic := '0';

	signal sSTART	: std_logic:='0';
	signal sPOINTS : std_logic_vector(1 downto 0):="00";
	signal sTEAM_A : std_logic;
	signal sTEAM_B : std_logic;
	
	signal sA_WIN 	: std_logic;
	signal sB_WIN 	: std_logic;
	
	signal sDIS    : std_logic_vector(1 downto 0);
	signal s7SEGM  : std_logic_vector(6 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component lprs1_homework2 is  
			port (
				iCLK 		: in  std_logic;
				iRST 		: in  std_logic;
				
				iSTART	: in  std_logic;
				iPOINTS 	: in  std_logic_vector(1 downto 0);
				iTEAM_A	: in  std_logic;
				iTEAM_B	: in  std_logic;
				
				oA_WIN 	: out std_logic;
				oB_WIN 	: out std_logic;

				oDIS  	: out std_logic_vector(1 downto 0);
				o7SEGM   : out std_logic_vector(6 downto 0)
		);
   end component;

begin

   uut: lprs1_homework2 port map (
	
          iCLK => sCLK,
          iRST => sRST,
			 
          iSTART	=> sSTART,
			 iPOINTS => sPOINTS,
			 iTEAM_A	=> sTEAM_A,
			 iTEAM_B	=> sTEAM_B,	
			 
			 oA_WIN => sA_WIN,
			 oB_WIN => sB_WIN,
			 
			 oDIS => sDIS,
			 o7SEGM => s7SEGM
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   -- Stimulus proces za testiranje
    stimulus : process
    begin
		  sRST <= '1';
		  wait for 5.25 * iCLK_period;
		  sRST <= '0';
		
			
		  sTEAM_A <= '0';
		  sTEAM_B <= '0';
		
        -- ===================================== TEST 1 (A-23:B-0)
        sSTART <= '1';

        -- Dodavanje poena za tim A
        sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;

        sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;

		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "10";  -- 2 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 4 * iCLK_PERIOD;
		  
        -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "10";  -- 2 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  -- ============================== TEST 2 -> (A-15:B-21)
		  sRST <= '1';
		  wait for 2 * iCLK_PERIOD;
		  sRST <= '0';
		  wait for iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "10";  -- 2 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "10";  -- 2 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "10";  -- 2 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  -- ============================== TEST 3 -> (A-21:B-21) ???
		  sRST <= '1';
		  wait for 2 * iCLK_PERIOD;
		  sRST <= '0';
		  wait for iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
		  sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  -- ============================== TEST 4 -> START se gasi u sred igre ???
		  sRST <= '1';
		  wait for 2 * iCLK_PERIOD;
		  sRST <= '0';
		  wait for iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sTEAM_A <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_A <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
		  sSTART <= '0';
		  
		  -- Dodavanje poena za tim B
        sTEAM_B <= '1';
        sPOINTS <= "11";  -- 3 poena
        wait for iCLK_PERIOD;
        sTEAM_B <= '0';
		  
		  wait for 2 * iCLK_PERIOD;
		  
        -- Kraj simulacije
        wait;
    end process;
end architecture;
