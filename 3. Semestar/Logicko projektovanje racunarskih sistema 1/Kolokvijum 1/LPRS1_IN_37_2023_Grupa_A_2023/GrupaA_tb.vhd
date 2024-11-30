library ieee;
use ieee.std_logic_1164.all;
 
entity GrupaA_tb is
end GrupaA_tb;
 
architecture Test OF GrupaA_tb is 
 
   component GrupaA is
		port ( 
				iCLK  	:  in std_logic;
				iRST  	:  in std_logic;
				iD			:  in std_logic_vector(7 downto 0);
				iDEN   	:  in std_logic;
				oTX   	:  out std_logic
		);
	end component;
    
	signal sCLK 	: std_logic := '0';
	signal sRST 	: std_logic := '0';
	signal sD		: std_logic_vector(7 downto 0) := "00000000";
	signal sDEN  	: std_logic := '0';
	signal sTX 		: std_logic := '0';
	
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: GrupaA PORT MAP (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
			 iD		=> sD,
          iDEN		=> sDEN,
			 oTX		=> sTX
        );

   -- Clock process definitions
   iCLK_process :process
   begin
		sCLK <= '1';
		wait for iCLK_period/2;
		sCLK <= '0';
		wait for iCLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin	
		sRST <= '1';
		wait for 5.25 * iCLK_period;
		sRST <= '0';
		
		wait for 5 * iCLK_period;
		sD <= X"F0";
		sDEN <= '1';
		
		wait for iCLK_period;
		sD <= (others => '0');
		sDEN <= '0';
		
		
		
		wait for 16 * iCLK_period;
		sD <= X"AA";
		sDEN <= '1';
		
		wait for iCLK_period;
		sD <= (others => '0');
		sDEN <= '0';
		
		
		
		wait for 16 * iCLK_period;
		sD <= X"0F";
		sDEN <= '1';
		
		wait for iCLK_period;
		sD <= (others => '0');
		sDEN <= '0';
		
		wait for 16 * iCLK_period;
		
		sRST <= '1';
		wait for 3 * iCLK_period;
		sRST <= '0';
		
      wait;
   end process;

end;