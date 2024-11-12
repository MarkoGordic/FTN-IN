library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
 
entity Slozeni_tb is
end entity;
 
architecture Test of Slozeni_tb is

	--Inputs and outputs
   signal sCLK   : std_logic := '0';
   signal sRST   : std_logic := '0';
   signal sEN    : std_logic := '0';
	signal sCNT : std_logic_vector(7 downto 0);
   signal sSHREG : std_logic_vector(7 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component Slozeni is port(
		iCLK   : in  std_logic;
      iRST   : in  std_logic;
      iEN    : in  std_logic;
		oCNT   : out std_logic_vector (7 downto 0);
      oSHREG : out std_logic_vector(7 downto 0)
      );
   end component;

begin

   uut: Slozeni port map (
          iCLK => sCLK,
          iRST => sRST,
          iEN => sEN,
			 oCNT => sCNT,
          oSHREG => sSHREG
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   -- Stimulus process
   stim_proc: process
   begin
		
		sRST <= '1';
		wait for 5.25 * iCLK_PERIOD;
		sRST <= '0';
		
		sEN <= '0';
		wait for 5 * iCLK_PERIOD;
		
		sEN <= '1';
		wait for 15 * iCLK_PERIOD;
		
		sEN <= '0';
		wait for 5 * iCLK_PERIOD;
		
		sEN <= '1';
		wait for 135 * iCLK_PERIOD;
		
		sRST <= '1';
		wait for 2 * iCLK_PERIOD;
		
		sRST <= '1';
		sEN <= '1';
		
		wait;
   end process;

END;
