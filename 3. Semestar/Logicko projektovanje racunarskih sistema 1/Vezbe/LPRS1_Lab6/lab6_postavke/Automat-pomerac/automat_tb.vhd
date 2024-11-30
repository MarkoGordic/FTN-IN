library ieee;
use ieee.std_logic_1164.all;
 
entity automat_tb is
end automat_tb;
 
architecture Test OF automat_tb is 
 
   component automat is
   Port (  	iCLK    	: in  std_logic;
				iRST    	: in  std_logic;
				iSTOP   	: in  std_logic;
				iRL	   : in  std_logic;
				iRR		: in  std_logic;
				iSRA		: in 	std_logic;
				oDATA		: out std_logic_vector(7 downto 0));
	end component;
    
	signal sCLK 	: std_logic := '0';
	signal sRST 	: std_logic := '0';
	signal sSTOP  	: std_logic := '0';
	signal sR_L  	: std_logic := '0';
	signal sR_R		: std_logic := '0';
	signal sSRA  	: std_logic := '0';
	signal sDATA	: std_logic_vector(7 downto 0) := "00000000";
	
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: automat PORT MAP (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
          iSTOP	=> sSTOP,
          iRL		=> sR_L,
          iRR	 	=> sR_R,
          iSRA		=> sSRA,
          oDATA 	=> sDATA);

   -- Clock process definitions
   iCLK_process :process
   begin
		sCLK <= '0';
		wait for iCLK_period/2;
		sCLK <= '1';
		wait for iCLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      
      wait;
   end process;

end;