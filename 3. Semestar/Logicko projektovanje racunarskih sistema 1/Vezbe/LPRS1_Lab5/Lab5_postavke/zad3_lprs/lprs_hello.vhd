library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity lprs_hello is
port(
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	oDIS  : out std_logic_vector(1 downto 0);
	o7SEGM : out std_logic_vector(6 downto 0)
);
end entity;


architecture Behavior of lprs_hello is
	signal sTC			: std_logic;
	signal sDIS_SEL 	: std_logic_vector(1 downto 0);

	--signal sDIS_CNT 	: std_logic_vector(14 downto 0); -- Sva slova se prikazuju "istovremeno"
	signal sDIS_CNT 	: std_logic_vector(21 downto 0);

	--constant cDIS_MAX	: std_logic_vector(14 downto 0) := "111111111111111"; -- Sva slova se prikazuju "istovremeno"
	constant cDIS_MAX	: std_logic_vector(21 downto 0) := "1111111111111111111111";

begin


end architecture;