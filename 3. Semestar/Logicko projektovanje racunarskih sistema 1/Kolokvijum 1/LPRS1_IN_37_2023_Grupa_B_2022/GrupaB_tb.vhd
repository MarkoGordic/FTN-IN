library ieee;
use ieee.std_logic_1164.all;
 
entity GrupaB_tb is
end GrupaB_tb;
 
architecture Test OF GrupaB_tb is 
 
   component GrupaB is
	port ( 
			iCLK  	:  in std_logic;
			iRST  	:  in std_logic;
			iDATA		:  in std_logic_vector(7 downto 0);
			iEN   	:  in std_logic;
			iLOAD   	:  in std_logic;
			oCODE 	: out std_logic_vector(2 downto 0);
			oCNTG		: out std_logic_vector(3 downto 0);
			oCNTS		: out std_logic_vector(3 downto 0)
	);
	end component;
    
	signal sCLK 	: std_logic := '0';
	signal sRST 	: std_logic := '0';
	signal sDATA	: std_logic_vector(7 downto 0) := "00000000";
	signal sEN  	: std_logic := '0';
	signal sLOAD  	: std_logic := '0';
	signal sCODE	: std_logic_vector(2 downto 0);
	signal sCNTG	: std_logic_vector(3 downto 0);
	signal sCNTS	: std_logic_vector(3 downto 0);
	
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: GrupaB PORT MAP (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
			 iDATA	=> sDATA,
          iEN		=> sEN,
			 iLOAD	=> sLOAD,
          oCODE	=> sCODE,
			 oCNTG	=> sCNTG,
			 oCNTS	=> sCNTS
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
		wait for 3.25 * iCLK_period;
		sRST <= '0';
		
		sDATA <= "11111110";
		wait for iCLK_period;
		
		sLOAD <= '1';
		sEN <= '1';
		wait for iCLK_period;
		sLOAD <= '0';
		
		wait for iCLK_period * 2;
		sEN <= '0';
		
		wait for iCLK_period * 10;
		
		sEN <= '1';
		wait for 5 * iCLK_period;
		sEN <= '0';
		
		sRST <= '1';
		wait for iCLK_period;
		sRST <= '0';
		
      wait;
   end process;

end;