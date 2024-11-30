library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity GrupaB is
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
end entity;

architecture Behavioral of GrupaB is

	signal sCOMP : std_logic_vector(7 downto 0);
	signal sROR : std_logic_vector(7 downto 0);
	signal sENG, sENS : std_logic;
	signal sCNTG, sCNTS : std_logic_vector(3 downto 0);
	
begin

	-- komplementer
	sCOMP <= (not iDATA) + 1;
	
	-- rotirajuci registar
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST = '1') then
				sROR <= (others => '0');
			else
				if(iEN = '1' and iLOAD = '1') then
					sROR <= sCOMP;
				elsif(iEN = '1' and iLOAD = '0') then
					sROR <= sCOMP(6 downto 0) & sCOMP(7);
				end if;
			end if;
		end if;
	end process;
	
	-- prioritetni koder
	oCODE <= "111" when sROR(7) = '1' else
				"110" when sROR(6) = '1' else
				"101" when sROR(5) = '1' else
				"100" when sROR(4) = '1' else
				"011" when sROR(3) = '1' else
				"010" when sROR(2) = '1' else
				"001" when sROR(1) = '1' else
				"000";
				
	-- komparator
	process(sROR) begin
		if(sROR < "00000101") then
			sENG <= '0';
			sENS <= '1';
		else
			sENG <= '1';
			sENS <= '0';
		end if;
	end process;
	
	-- brojac za manje
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST = '1') then
				sCNTS <= (others => '0');
			else
				if(sENS = '1') then
					sCNTS <= sCNTS + 1;
				end if;
			end if;
		end if;
	end process;
	
	-- brojac za vece
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST = '1') then
				sCNTG <= (others => '0');
			else
				if(sENG = '1') then
					sCNTG <= sCNTG + 1;
				end if;
			end if;
		end if;
	end process;
	
	oCNTG <= sCNTG;
	oCNTS <= sCNTS;
	
end Behavioral;
