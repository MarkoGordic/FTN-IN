library ieee;
use ieee.std_logic_1164.all;

entity Brojac_tb is
end entity;
 
architecture Test of Brojac_tb is
  
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
   signal sEN : std_logic := '0';
	signal s7SEGM : std_logic_vector(6 downto 0);
   signal sCNT : std_logic_vector(23 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component Brojac is port (   
		iRST  : in  std_logic;
		iCLK  : in  std_logic;
		iEN   : in  std_logic;
		o7SEGM : out std_logic_vector(6 downto 0);
		oCNT  : out std_logic_vector(23 downto 0)
	);
   end component;

begin

   uut: Brojac port map (
          iCLK => sCLK,
          iRST => sRST,
          iEN => sEN,
			 o7SEGM => s7SEGM,
          oCNT => sCNT
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   stim_proc : process
   begin
		   -- reset sistema pre zadavanja sekvence ulaza
			sRST <= '1';
			wait for 5.25 * iCLK_period;
			sRST <= '0';
			
			-- nema dozvole brojanja 5 perioda takta	
			sEN <= '0';
			wait for 5 * iCLK_period;
			
			-- dozvoli brojanje 15 perioda takta
			sEN <= '1';
			wait for 15 * iCLK_period;
			
			-- nema dozvole brojanja 5 perioda takta	
			sEN <= '0';
			wait for 5 * iCLK_period;
			
			-- dozvoli brojanje do kraja simulacije	
			sEN <= '1';
			wait;
   end process;
end architecture;
