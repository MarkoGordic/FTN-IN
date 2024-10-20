library ieee;
use ieee.std_logic_1164.all;

entity mux is
	port(
		iX0 : in std_logic;
		iX1 : in std_logic;
		iX2 : in std_logic;
		iX3 : in std_logic;
		iSEL : in std_logic_vector(1 downto 0);
		oY : out std_logic
	);
end entity;

-----------------------------------------------------
architecture logicka_kola of mux is
	
	signal sS0, sS1, sS2, sS3 : std_logic;
	
begin
	-- logicka kola
	sS0 <= iX0 and not(iSEL(1)) and not(iSEL(0));
	sS1 <= iX1 and not(iSEL(1)) and iSEL(0);
	sS2 <= iX2 and iSEL(1) and not(iSEL(0));
	sS3 <= iX3 and iSEL(1) and iSEL(0);
	oY <= sS0 or sS1 or sS2 or sS3;
end architecture logicka_kola;

-----------------------------------------------------
architecture uslovna_dodela of mux is	
begin
	-- uslovna dodela
	oY <= iX0 when iSEL="00" else
		   iX1 when iSEL="01" else
			iX2 when iSEL="10" else
			iX3;
	
end architecture uslovna_dodela;	
-----------------------------------------------------	
architecture if_else of mux is
begin			
	-- if-elsif-else
	process (iX0, iX1, iX2, iX3, iSEL) begin
		if (iSEL="00") then
			oY <= iX0;
		elsif (iSEL="01") then
			oY <= iX1;
		elsif (iSEL="10") then
			oY <= iX2;
		else
			oY <= iX3;
		end if;
	end process;
end architecture if_else;
-----------------------------------------------------	
architecture cases of mux is
	
	signal sS0, sS1, sS2, sS3 : std_logic;
	
begin
	-- case
	process (iX0, iX1, iX2, iX3, iSEL) begin
		case (iSEL) is
			when "00" => oY <= iX0;
			when "01" => oY <= iX1;
			when "10" => oY <= iX2;
			when others => oY <= iX3;
		end case;
	end process;
end architecture cases;