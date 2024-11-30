library ieee;
use ieee.std_logic_1164.all;
 
entity Semafor_tb is
end Semafor_tb;
 
architecture Test of Semafor_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component Semafor
    port(	iCLK    : in  std_logic;
				iRST    : in  std_logic;
				iOK     : in  std_logic;
				iHAZ    : in  std_logic;
				oRED    : out std_logic;
				oYELLOW : out std_logic;
				oGREEN  : out std_logic);
    end component;
    
   --Inputs
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
   signal sOK  : std_logic := '1';
   signal sHAZ : std_logic := '0';
  
 	--Outputs
   signal sRED    : std_logic;
   signal sYELLOW : std_logic;
	signal sGREEN  : std_logic;
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Semafor port map (
          iCLK => sCLK,
          iRST => sRST,
          iOK => sOK,
          iHAZ => sHAZ,
          oRED => sRED,
          oYELLOW => sYELLOW,
          oGREEN => sGREEN);

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

END;