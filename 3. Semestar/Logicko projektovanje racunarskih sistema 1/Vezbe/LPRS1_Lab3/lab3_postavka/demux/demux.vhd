library ieee;
use ieee.std_logic_1164.all;

entity demux is
	port(
		iX : in std_logic;
		iSEL : in std_logic_vector(1 downto 0);
		oY0 : out std_logic;
		oY1 : out std_logic;
		oY2 : out std_logic;
		oY3 : out std_logic
	);
end entity;
----------------------------------------------------
architecture logicka_kola of demux is
begin
end architecture logicka_kola;
----------------------------------------------------
architecture uslovna_dodela of demux is
begin	
end architecture uslovna_dodela;
----------------------------------------------------
architecture if_else of demux is
begin
end architecture if_else;
----------------------------------------------------
architecture cases of demux is
begin
end architecture cases;