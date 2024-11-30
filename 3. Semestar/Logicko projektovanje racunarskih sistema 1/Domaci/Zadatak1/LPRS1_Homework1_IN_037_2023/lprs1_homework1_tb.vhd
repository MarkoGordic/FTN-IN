library ieee;
use ieee.std_logic_1164.all;

entity lprs1_homework1_tb is
end entity;

architecture Test of lprs1_homework1_tb is

	signal sA  : std_logic_vector(3 downto 0);
	signal sB  : std_logic_vector(3 downto 0);
	signal sOP : std_logic_vector(4 downto 0);
	
	signal sRES   : std_logic_vector(3 downto 0);
	signal sZERO  : std_logic;
	signal sSIGN  : std_logic;
	signal sCARRY : std_logic;
	signal sSEGM  : std_logic_vector(6 downto 0);
	
	component lprs1_homework1 is
		port(
			iA  : in std_logic_vector(3 downto 0);
			iB  : in std_logic_vector(3 downto 0);
			iOP : in std_logic_vector(4 downto 0);
			oRES 	 : out std_logic_vector(3 downto 0);
			oZERO  : out std_logic;
			oSIGN  : out std_logic;
			oCARRY : out std_logic;
			oSEGM  : out std_logic_vector(6 downto 0)
		);
	end component;

begin
	uut : lprs1_homework1
		port map(
			iA   		=> sA,
			iB   		=> sB,
			iOP  		=> sOP,
			oRES 		=> sRES,
			oZERO 	=> sZERO,
			oSIGN 	=> sSIGN,
			oCARRY	=> sCARRY,
			oSEGM 	=> sSEGM
		);

	stimulus : process
	begin
		-- Test Case 1: (sA = 5, sB = 3)
		sA <= "1001";  -- 5
		sB <= "0001";  -- 3
		sOP <= "10000";  -- Sabiranje BEZ CARRY
		wait for 100 ns;
		
		-- Test Case 2: (sA = 7, sB = -1)
		sA <= "0111";  -- 7
		sB <= "1111";  -- -1
		sOP <= "10000";  -- Sabiranje CARRY
		wait for 100 ns;
		
		-- Test Case 3: (sA = 7, sB = 2)
		sA <= "0111";  -- 7
		sB <= "0010";  -- 2
		sOP <= "01000";  -- Oduzimanje 
		wait for 100 ns;

		-- Test Case 4: (sA = 6, sB = 3)
		sA <= "0110";  -- 6
		sB <= "0011";  -- 3
		sOP <= "00100";  -- AND
		wait for 100 ns;

		-- Test Case 5: Left Shift (sA = 4)
		sA <= "0100";  -- 4
		sB <= "0000";  -- /
		sOP <= "00010";  -- Left shift 
		wait for 100 ns;

		-- Test Case 6: Right Shift (sB = -7)
		sA <= "0000";  -- /
		sB <= "1001";  -- -7
		sOP <= "00001";  -- Right shift 

		wait;
	end process;

end architecture;
