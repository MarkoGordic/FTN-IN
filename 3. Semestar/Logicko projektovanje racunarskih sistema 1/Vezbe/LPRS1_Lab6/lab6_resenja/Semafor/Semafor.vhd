library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	iCLK    : in  std_logic;
				iRST    : in  std_logic;
				iOK     : in  std_logic;
				iHAZ    : in  std_logic;
				oRED    : out std_logic;
				oYELLOW : out std_logic;
				oGREEN  : out std_logic);
end Semafor;

architecture Behavioral of Semafor is

	type tSTATE is (IDLE, RED, RED_YELLOW, GREEN, YELLOW, HAZARD);
	signal sSTATE, sNEXT_STATE : tSTATE;

begin

	-- registar za pamcecnje stanja
	process(iRST, iCLK) begin
		if(iRST = '1') then
			sSTATE <= IDLE;
		elsif(rising_edge(iCLK) then
			sSTATE <= sNEXT_STATE;
		end if;
	end process;
	
	-- funckcija prelaza
	process(sSTATE, iHAZ, iOK) begin
		case sSTATE is
			when IDLE =>
				if(iOK = '1') then
					sNEXT_STATE <= RED;
				else
					sNEXT_STATE <= IDLE;
				end if;
			
			when RED =>
				if(iHAZ = '1') then
					sNEXT_STATE <= HAZARD;
				else
					sNEXT_STATE <= RED_YELLOW;
				end if;
			
			when RED_YELLOW =>
				if(iHAZ = '1') then
					sNEXT_STATE <= HAZARD;
				else
					sNEXT_STATE <= GREEN;
				end if;
			
			when GREEN =>
				if(iHAZ = '1') then
					sNEXT_STATE <= HAZARD;
				else
					sNEXT_STATE <= YELLOW;
				end if;
				
			when YELLOW =>
				if(iHAZ = '1') then
					sNEXT_STATE <= HAZARD;
				else
					sNEXT_STATE <= RED;
				end if;
				
			when HAZARD =>
				if(iOK = '1') then
					sNEXT_STATE <= RED;
				else
					sNEXT_STATE <= HAZARD;
				end if;
				
			when others =>
				sNEXT_STATE <= IDLE;
				
		end case;
	end process;
	
	oRED <= '1' when sSTATE = RED or sSTATE = RED_YELLOW or sSTATE = HAZARD else '0';
	oYELLOW <= '1' when sSTATE = RED_YELLOW or sSTATE = YELLOW or sSTATE = HAZARD else '0';
	oGREEN <= '1' when sSTATE = GREEN or sSTATE = HAZARD else '0';
	
end Behavioral;