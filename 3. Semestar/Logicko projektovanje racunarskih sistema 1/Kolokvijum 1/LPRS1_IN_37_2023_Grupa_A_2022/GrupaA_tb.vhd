library ieee;
use ieee.std_logic_1164.all;
 
entity GrupaA_tb is
end GrupaA_tb;
 
architecture Test OF GrupaA_tb is 
 
   component GrupaA is
	port ( 
		iCLK  	:  in std_logic;
		iRST  	:  in std_logic;
		iEN   	:  in std_logic;
		iDEC		:  in std_logic_vector(2 downto 0);
		oGREAT	: out std_logic;
		oCNTP 	: out std_logic_vector(3 downto 0);
		oCNTN 	: out std_logic_vector(3 downto 0)
	);
	end component;
    
	signal sCLK 	: std_logic := '0';
	signal sRST 	: std_logic := '0';
	signal sEN  	: std_logic := '0';
	signal sDEC	  	: std_logic_vector(2 downto 0) := "000";
	signal sGREAT 	: std_logic;
	signal sCNTP	: std_logic_vector(3 downto 0);
	signal sCNTN	: std_logic_vector(3 downto 0);
	
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: GrupaA PORT MAP (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
          iEN		=> sEN,
			 iDEC		=> sDEC,
			 oGREAT	=> sGREAT,
          oCNTP	=> sCNTP,
          oCNTN	=> sCNTN
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
		
		sDEC <= "000";
		sEN <= '1'; -- dozvoljavamo rad registra
		wait for iCLK_period * 10;
		
		sDEC <= "001";
		wait for iCLK_period * 8;
		
		sEN <= '0';
		sRST <= '1';
		wait for 5 * iCLK_period;
		sRST <= '0';
		
		sEN <= '1';
		sDEC <= "111";
		wait for iCLK_period * 10;
		
		sDEC <= "001";
		wait for iCLK_period * 10;
		
		sEN <= '0';
		sRST <= '1';
		wait for iCLK_period;
		sRST <= '0';
		
      wait;
   end process;

end;