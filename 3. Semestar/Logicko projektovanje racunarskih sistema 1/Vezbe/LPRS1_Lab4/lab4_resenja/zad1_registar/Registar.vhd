library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Registar is
	port (
				iCLK 	: in  std_logic;
				iRST 	: in  std_logic;
				iD 	: in  std_logic_vector (7 downto 0);
				iWE 	: in  std_logic;
				oQ 	: out std_logic_vector (7 downto 0)
		);
end entity;

architecture Behavioral of Registar is
    signal sREG : std_logic_vector(7 downto 0);
begin

	-- registar sa sinhronim resetom
    process (iCLK) begin
        if (iCLK'event and iCLK = '1') then
		if (iRST = '1') then
           	sREG <= (others => '0');	-- početna vrednost
		else
           	if (iWE = '1') then			-- ako je signal dozvole rada aktivan
                		sREG <= iD;		-- registar dobija vrednost sa ulaza iD
            	end if;
		end if;
        end if;
    end process;
    
    oQ <= sREG;

end Behavioral;
