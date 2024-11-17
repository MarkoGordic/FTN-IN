-- Copyright (C) 2018  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 18.0.0 Build 614 04/24/2018 SJ Lite Edition"

-- DATE "11/13/2022 22:52:45"

-- 
-- Device: Altera 10M16SAU169C8G Package UFBGA169
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	hard_block IS
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic
	);
END hard_block;

-- Design Ports Information
-- ~ALTERA_TMS~	=>  Location: PIN_G1,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TCK~	=>  Location: PIN_G2,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDI~	=>  Location: PIN_F5,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDO~	=>  Location: PIN_F6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_CONFIG_SEL~	=>  Location: PIN_D7,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- ~ALTERA_nCONFIG~	=>  Location: PIN_E7,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_nSTATUS~	=>  Location: PIN_C4,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_CONF_DONE~	=>  Location: PIN_C5,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default


ARCHITECTURE structure OF hard_block IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \~ALTERA_TMS~~padout\ : std_logic;
SIGNAL \~ALTERA_TCK~~padout\ : std_logic;
SIGNAL \~ALTERA_TDI~~padout\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~padout\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~padout\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~padout\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~padout\ : std_logic;
SIGNAL \~ALTERA_TMS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TCK~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TDI~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~ibuf_o\ : std_logic;

BEGIN

ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
END structure;


LIBRARY ALTERA;
LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Brojac IS
    PORT (
	iRST : IN std_logic;
	iCLK : IN std_logic;
	iEN : IN std_logic;
	oCNT : BUFFER std_logic_vector(23 DOWNTO 0)
	);
END Brojac;

-- Design Ports Information
-- oCNT[0]	=>  Location: PIN_D13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[1]	=>  Location: PIN_C13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[2]	=>  Location: PIN_F10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[3]	=>  Location: PIN_G12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[4]	=>  Location: PIN_H9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[5]	=>  Location: PIN_B11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[6]	=>  Location: PIN_F8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[7]	=>  Location: PIN_E13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[8]	=>  Location: PIN_E9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[9]	=>  Location: PIN_F13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[10]	=>  Location: PIN_F9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[11]	=>  Location: PIN_B12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[12]	=>  Location: PIN_E12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[13]	=>  Location: PIN_G10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[14]	=>  Location: PIN_F12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[15]	=>  Location: PIN_G9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[16]	=>  Location: PIN_A8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[17]	=>  Location: PIN_A9,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[18]	=>  Location: PIN_A11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[19]	=>  Location: PIN_A10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[20]	=>  Location: PIN_B10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[21]	=>  Location: PIN_C9,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[22]	=>  Location: PIN_C10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[23]	=>  Location: PIN_D8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- iEN	=>  Location: PIN_M3,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- iCLK	=>  Location: PIN_H6,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- iRST	=>  Location: PIN_F1,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default


ARCHITECTURE structure OF Brojac IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_iRST : std_logic;
SIGNAL ww_iCLK : std_logic;
SIGNAL ww_iEN : std_logic;
SIGNAL ww_oCNT : std_logic_vector(23 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_ADC1~_CHSEL_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \iCLK~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \~QUARTUS_CREATED_UNVM~~busy\ : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~~eoc\ : std_logic;
SIGNAL \oCNT[0]~output_o\ : std_logic;
SIGNAL \oCNT[1]~output_o\ : std_logic;
SIGNAL \oCNT[2]~output_o\ : std_logic;
SIGNAL \oCNT[3]~output_o\ : std_logic;
SIGNAL \oCNT[4]~output_o\ : std_logic;
SIGNAL \oCNT[5]~output_o\ : std_logic;
SIGNAL \oCNT[6]~output_o\ : std_logic;
SIGNAL \oCNT[7]~output_o\ : std_logic;
SIGNAL \oCNT[8]~output_o\ : std_logic;
SIGNAL \oCNT[9]~output_o\ : std_logic;
SIGNAL \oCNT[10]~output_o\ : std_logic;
SIGNAL \oCNT[11]~output_o\ : std_logic;
SIGNAL \oCNT[12]~output_o\ : std_logic;
SIGNAL \oCNT[13]~output_o\ : std_logic;
SIGNAL \oCNT[14]~output_o\ : std_logic;
SIGNAL \oCNT[15]~output_o\ : std_logic;
SIGNAL \oCNT[16]~output_o\ : std_logic;
SIGNAL \oCNT[17]~output_o\ : std_logic;
SIGNAL \oCNT[18]~output_o\ : std_logic;
SIGNAL \oCNT[19]~output_o\ : std_logic;
SIGNAL \oCNT[20]~output_o\ : std_logic;
SIGNAL \oCNT[21]~output_o\ : std_logic;
SIGNAL \oCNT[22]~output_o\ : std_logic;
SIGNAL \oCNT[23]~output_o\ : std_logic;
SIGNAL \iCLK~input_o\ : std_logic;
SIGNAL \iCLK~inputclkctrl_outclk\ : std_logic;
SIGNAL \iEN~input_o\ : std_logic;
SIGNAL \sCNT[0]~23_combout\ : std_logic;
SIGNAL \iRST~input_o\ : std_logic;
SIGNAL \sCNT[1]~24_combout\ : std_logic;
SIGNAL \sCNT[1]~25\ : std_logic;
SIGNAL \sCNT[2]~26_combout\ : std_logic;
SIGNAL \sCNT[2]~27\ : std_logic;
SIGNAL \sCNT[3]~28_combout\ : std_logic;
SIGNAL \sCNT[3]~29\ : std_logic;
SIGNAL \sCNT[4]~30_combout\ : std_logic;
SIGNAL \sCNT[4]~31\ : std_logic;
SIGNAL \sCNT[5]~32_combout\ : std_logic;
SIGNAL \sCNT[5]~33\ : std_logic;
SIGNAL \sCNT[6]~34_combout\ : std_logic;
SIGNAL \sCNT[6]~35\ : std_logic;
SIGNAL \sCNT[7]~36_combout\ : std_logic;
SIGNAL \sCNT[7]~37\ : std_logic;
SIGNAL \sCNT[8]~38_combout\ : std_logic;
SIGNAL \sCNT[8]~39\ : std_logic;
SIGNAL \sCNT[9]~40_combout\ : std_logic;
SIGNAL \sCNT[9]~41\ : std_logic;
SIGNAL \sCNT[10]~42_combout\ : std_logic;
SIGNAL \sCNT[10]~43\ : std_logic;
SIGNAL \sCNT[11]~44_combout\ : std_logic;
SIGNAL \sCNT[11]~45\ : std_logic;
SIGNAL \sCNT[12]~46_combout\ : std_logic;
SIGNAL \sCNT[12]~47\ : std_logic;
SIGNAL \sCNT[13]~48_combout\ : std_logic;
SIGNAL \sCNT[13]~49\ : std_logic;
SIGNAL \sCNT[14]~50_combout\ : std_logic;
SIGNAL \sCNT[14]~51\ : std_logic;
SIGNAL \sCNT[15]~52_combout\ : std_logic;
SIGNAL \sCNT[15]~53\ : std_logic;
SIGNAL \sCNT[16]~54_combout\ : std_logic;
SIGNAL \sCNT[16]~55\ : std_logic;
SIGNAL \sCNT[17]~56_combout\ : std_logic;
SIGNAL \sCNT[17]~57\ : std_logic;
SIGNAL \sCNT[18]~58_combout\ : std_logic;
SIGNAL \sCNT[18]~59\ : std_logic;
SIGNAL \sCNT[19]~60_combout\ : std_logic;
SIGNAL \sCNT[19]~61\ : std_logic;
SIGNAL \sCNT[20]~62_combout\ : std_logic;
SIGNAL \sCNT[20]~63\ : std_logic;
SIGNAL \sCNT[21]~64_combout\ : std_logic;
SIGNAL \sCNT[21]~65\ : std_logic;
SIGNAL \sCNT[22]~66_combout\ : std_logic;
SIGNAL \sCNT[22]~67\ : std_logic;
SIGNAL \sCNT[23]~68_combout\ : std_logic;
SIGNAL sCNT : std_logic_vector(23 DOWNTO 0);
SIGNAL \ALT_INV_iRST~input_o\ : std_logic;

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_iRST <= iRST;
ww_iCLK <= iCLK;
ww_iEN <= iEN;
oCNT <= ww_oCNT;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\~QUARTUS_CREATED_ADC1~_CHSEL_bus\ <= (\~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\);

\iCLK~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \iCLK~input_o\);
\ALT_INV_iRST~input_o\ <= NOT \iRST~input_o\;
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: LCCOMB_X26_Y28_N20
\~QUARTUS_CREATED_GND~I\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \~QUARTUS_CREATED_GND~I_combout\ = GND

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	combout => \~QUARTUS_CREATED_GND~I_combout\);

-- Location: IOOBUF_X50_Y21_N9
\oCNT[0]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(0),
	devoe => ww_devoe,
	o => \oCNT[0]~output_o\);

-- Location: IOOBUF_X50_Y21_N2
\oCNT[1]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(1),
	devoe => ww_devoe,
	o => \oCNT[1]~output_o\);

-- Location: IOOBUF_X50_Y21_N16
\oCNT[2]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(2),
	devoe => ww_devoe,
	o => \oCNT[2]~output_o\);

-- Location: IOOBUF_X50_Y11_N2
\oCNT[3]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(3),
	devoe => ww_devoe,
	o => \oCNT[3]~output_o\);

-- Location: IOOBUF_X50_Y11_N24
\oCNT[4]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(4),
	devoe => ww_devoe,
	o => \oCNT[4]~output_o\);

-- Location: IOOBUF_X50_Y22_N2
\oCNT[5]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(5),
	devoe => ww_devoe,
	o => \oCNT[5]~output_o\);

-- Location: IOOBUF_X50_Y22_N23
\oCNT[6]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(6),
	devoe => ww_devoe,
	o => \oCNT[6]~output_o\);

-- Location: IOOBUF_X50_Y15_N16
\oCNT[7]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(7),
	devoe => ww_devoe,
	o => \oCNT[7]~output_o\);

-- Location: IOOBUF_X50_Y22_N16
\oCNT[8]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(8),
	devoe => ww_devoe,
	o => \oCNT[8]~output_o\);

-- Location: IOOBUF_X50_Y15_N23
\oCNT[9]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(9),
	devoe => ww_devoe,
	o => \oCNT[9]~output_o\);

-- Location: IOOBUF_X50_Y21_N24
\oCNT[10]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(10),
	devoe => ww_devoe,
	o => \oCNT[10]~output_o\);

-- Location: IOOBUF_X50_Y22_N9
\oCNT[11]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(11),
	devoe => ww_devoe,
	o => \oCNT[11]~output_o\);

-- Location: IOOBUF_X50_Y16_N16
\oCNT[12]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(12),
	devoe => ww_devoe,
	o => \oCNT[12]~output_o\);

-- Location: IOOBUF_X50_Y14_N16
\oCNT[13]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(13),
	devoe => ww_devoe,
	o => \oCNT[13]~output_o\);

-- Location: IOOBUF_X50_Y16_N23
\oCNT[14]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(14),
	devoe => ww_devoe,
	o => \oCNT[14]~output_o\);

-- Location: IOOBUF_X50_Y14_N23
\oCNT[15]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(15),
	devoe => ww_devoe,
	o => \oCNT[15]~output_o\);

-- Location: IOOBUF_X19_Y17_N9
\oCNT[16]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(16),
	devoe => ww_devoe,
	o => \oCNT[16]~output_o\);

-- Location: IOOBUF_X19_Y17_N16
\oCNT[17]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(17),
	devoe => ww_devoe,
	o => \oCNT[17]~output_o\);

-- Location: IOOBUF_X16_Y17_N9
\oCNT[18]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(18),
	devoe => ww_devoe,
	o => \oCNT[18]~output_o\);

-- Location: IOOBUF_X16_Y17_N2
\oCNT[19]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(19),
	devoe => ww_devoe,
	o => \oCNT[19]~output_o\);

-- Location: IOOBUF_X19_Y17_N23
\oCNT[20]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(20),
	devoe => ww_devoe,
	o => \oCNT[20]~output_o\);

-- Location: IOOBUF_X19_Y17_N2
\oCNT[21]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(21),
	devoe => ww_devoe,
	o => \oCNT[21]~output_o\);

-- Location: IOOBUF_X21_Y17_N30
\oCNT[22]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(22),
	devoe => ww_devoe,
	o => \oCNT[22]~output_o\);

-- Location: IOOBUF_X16_Y17_N16
\oCNT[23]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(23),
	devoe => ww_devoe,
	o => \oCNT[23]~output_o\);

-- Location: IOIBUF_X0_Y9_N22
\iCLK~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iCLK,
	o => \iCLK~input_o\);

-- Location: CLKCTRL_G4
\iCLK~inputclkctrl\ : fiftyfivenm_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \iCLK~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \iCLK~inputclkctrl_outclk\);

-- Location: IOIBUF_X0_Y3_N15
\iEN~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iEN,
	o => \iEN~input_o\);

-- Location: LCCOMB_X49_Y18_N0
\sCNT[0]~23\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[0]~23_combout\ = sCNT(0) $ (\iEN~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => sCNT(0),
	datad => \iEN~input_o\,
	combout => \sCNT[0]~23_combout\);

-- Location: IOIBUF_X25_Y22_N15
\iRST~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iRST,
	o => \iRST~input_o\);

-- Location: FF_X49_Y18_N1
\sCNT[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[0]~23_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(0));

-- Location: LCCOMB_X49_Y18_N10
\sCNT[1]~24\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[1]~24_combout\ = (sCNT(1) & (sCNT(0) $ (VCC))) # (!sCNT(1) & (sCNT(0) & VCC))
-- \sCNT[1]~25\ = CARRY((sCNT(1) & sCNT(0)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110011010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(1),
	datab => sCNT(0),
	datad => VCC,
	combout => \sCNT[1]~24_combout\,
	cout => \sCNT[1]~25\);

-- Location: FF_X49_Y18_N11
\sCNT[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[1]~24_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(1));

-- Location: LCCOMB_X49_Y18_N12
\sCNT[2]~26\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[2]~26_combout\ = (sCNT(2) & (!\sCNT[1]~25\)) # (!sCNT(2) & ((\sCNT[1]~25\) # (GND)))
-- \sCNT[2]~27\ = CARRY((!\sCNT[1]~25\) # (!sCNT(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(2),
	datad => VCC,
	cin => \sCNT[1]~25\,
	combout => \sCNT[2]~26_combout\,
	cout => \sCNT[2]~27\);

-- Location: FF_X49_Y18_N13
\sCNT[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[2]~26_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(2));

-- Location: LCCOMB_X49_Y18_N14
\sCNT[3]~28\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[3]~28_combout\ = (sCNT(3) & (\sCNT[2]~27\ $ (GND))) # (!sCNT(3) & (!\sCNT[2]~27\ & VCC))
-- \sCNT[3]~29\ = CARRY((sCNT(3) & !\sCNT[2]~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(3),
	datad => VCC,
	cin => \sCNT[2]~27\,
	combout => \sCNT[3]~28_combout\,
	cout => \sCNT[3]~29\);

-- Location: FF_X49_Y18_N15
\sCNT[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[3]~28_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(3));

-- Location: LCCOMB_X49_Y18_N16
\sCNT[4]~30\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[4]~30_combout\ = (sCNT(4) & (!\sCNT[3]~29\)) # (!sCNT(4) & ((\sCNT[3]~29\) # (GND)))
-- \sCNT[4]~31\ = CARRY((!\sCNT[3]~29\) # (!sCNT(4)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(4),
	datad => VCC,
	cin => \sCNT[3]~29\,
	combout => \sCNT[4]~30_combout\,
	cout => \sCNT[4]~31\);

-- Location: FF_X49_Y18_N17
\sCNT[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[4]~30_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(4));

-- Location: LCCOMB_X49_Y18_N18
\sCNT[5]~32\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[5]~32_combout\ = (sCNT(5) & (\sCNT[4]~31\ $ (GND))) # (!sCNT(5) & (!\sCNT[4]~31\ & VCC))
-- \sCNT[5]~33\ = CARRY((sCNT(5) & !\sCNT[4]~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(5),
	datad => VCC,
	cin => \sCNT[4]~31\,
	combout => \sCNT[5]~32_combout\,
	cout => \sCNT[5]~33\);

-- Location: FF_X49_Y18_N19
\sCNT[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[5]~32_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(5));

-- Location: LCCOMB_X49_Y18_N20
\sCNT[6]~34\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[6]~34_combout\ = (sCNT(6) & (!\sCNT[5]~33\)) # (!sCNT(6) & ((\sCNT[5]~33\) # (GND)))
-- \sCNT[6]~35\ = CARRY((!\sCNT[5]~33\) # (!sCNT(6)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(6),
	datad => VCC,
	cin => \sCNT[5]~33\,
	combout => \sCNT[6]~34_combout\,
	cout => \sCNT[6]~35\);

-- Location: FF_X49_Y18_N21
\sCNT[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[6]~34_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(6));

-- Location: LCCOMB_X49_Y18_N22
\sCNT[7]~36\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[7]~36_combout\ = (sCNT(7) & (\sCNT[6]~35\ $ (GND))) # (!sCNT(7) & (!\sCNT[6]~35\ & VCC))
-- \sCNT[7]~37\ = CARRY((sCNT(7) & !\sCNT[6]~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(7),
	datad => VCC,
	cin => \sCNT[6]~35\,
	combout => \sCNT[7]~36_combout\,
	cout => \sCNT[7]~37\);

-- Location: FF_X49_Y18_N23
\sCNT[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[7]~36_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(7));

-- Location: LCCOMB_X49_Y18_N24
\sCNT[8]~38\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[8]~38_combout\ = (sCNT(8) & (!\sCNT[7]~37\)) # (!sCNT(8) & ((\sCNT[7]~37\) # (GND)))
-- \sCNT[8]~39\ = CARRY((!\sCNT[7]~37\) # (!sCNT(8)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(8),
	datad => VCC,
	cin => \sCNT[7]~37\,
	combout => \sCNT[8]~38_combout\,
	cout => \sCNT[8]~39\);

-- Location: FF_X49_Y18_N25
\sCNT[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[8]~38_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(8));

-- Location: LCCOMB_X49_Y18_N26
\sCNT[9]~40\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[9]~40_combout\ = (sCNT(9) & (\sCNT[8]~39\ $ (GND))) # (!sCNT(9) & (!\sCNT[8]~39\ & VCC))
-- \sCNT[9]~41\ = CARRY((sCNT(9) & !\sCNT[8]~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(9),
	datad => VCC,
	cin => \sCNT[8]~39\,
	combout => \sCNT[9]~40_combout\,
	cout => \sCNT[9]~41\);

-- Location: FF_X49_Y18_N27
\sCNT[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[9]~40_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(9));

-- Location: LCCOMB_X49_Y18_N28
\sCNT[10]~42\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[10]~42_combout\ = (sCNT(10) & (!\sCNT[9]~41\)) # (!sCNT(10) & ((\sCNT[9]~41\) # (GND)))
-- \sCNT[10]~43\ = CARRY((!\sCNT[9]~41\) # (!sCNT(10)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(10),
	datad => VCC,
	cin => \sCNT[9]~41\,
	combout => \sCNT[10]~42_combout\,
	cout => \sCNT[10]~43\);

-- Location: FF_X49_Y18_N29
\sCNT[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[10]~42_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(10));

-- Location: LCCOMB_X49_Y18_N30
\sCNT[11]~44\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[11]~44_combout\ = (sCNT(11) & (\sCNT[10]~43\ $ (GND))) # (!sCNT(11) & (!\sCNT[10]~43\ & VCC))
-- \sCNT[11]~45\ = CARRY((sCNT(11) & !\sCNT[10]~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(11),
	datad => VCC,
	cin => \sCNT[10]~43\,
	combout => \sCNT[11]~44_combout\,
	cout => \sCNT[11]~45\);

-- Location: FF_X49_Y18_N31
\sCNT[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[11]~44_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(11));

-- Location: LCCOMB_X49_Y17_N0
\sCNT[12]~46\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[12]~46_combout\ = (sCNT(12) & (!\sCNT[11]~45\)) # (!sCNT(12) & ((\sCNT[11]~45\) # (GND)))
-- \sCNT[12]~47\ = CARRY((!\sCNT[11]~45\) # (!sCNT(12)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(12),
	datad => VCC,
	cin => \sCNT[11]~45\,
	combout => \sCNT[12]~46_combout\,
	cout => \sCNT[12]~47\);

-- Location: FF_X49_Y17_N1
\sCNT[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[12]~46_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(12));

-- Location: LCCOMB_X49_Y17_N2
\sCNT[13]~48\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[13]~48_combout\ = (sCNT(13) & (\sCNT[12]~47\ $ (GND))) # (!sCNT(13) & (!\sCNT[12]~47\ & VCC))
-- \sCNT[13]~49\ = CARRY((sCNT(13) & !\sCNT[12]~47\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(13),
	datad => VCC,
	cin => \sCNT[12]~47\,
	combout => \sCNT[13]~48_combout\,
	cout => \sCNT[13]~49\);

-- Location: FF_X49_Y17_N3
\sCNT[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[13]~48_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(13));

-- Location: LCCOMB_X49_Y17_N4
\sCNT[14]~50\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[14]~50_combout\ = (sCNT(14) & (!\sCNT[13]~49\)) # (!sCNT(14) & ((\sCNT[13]~49\) # (GND)))
-- \sCNT[14]~51\ = CARRY((!\sCNT[13]~49\) # (!sCNT(14)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(14),
	datad => VCC,
	cin => \sCNT[13]~49\,
	combout => \sCNT[14]~50_combout\,
	cout => \sCNT[14]~51\);

-- Location: FF_X49_Y17_N5
\sCNT[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[14]~50_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(14));

-- Location: LCCOMB_X49_Y17_N6
\sCNT[15]~52\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[15]~52_combout\ = (sCNT(15) & (\sCNT[14]~51\ $ (GND))) # (!sCNT(15) & (!\sCNT[14]~51\ & VCC))
-- \sCNT[15]~53\ = CARRY((sCNT(15) & !\sCNT[14]~51\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(15),
	datad => VCC,
	cin => \sCNT[14]~51\,
	combout => \sCNT[15]~52_combout\,
	cout => \sCNT[15]~53\);

-- Location: FF_X49_Y17_N7
\sCNT[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[15]~52_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(15));

-- Location: LCCOMB_X49_Y17_N8
\sCNT[16]~54\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[16]~54_combout\ = (sCNT(16) & (!\sCNT[15]~53\)) # (!sCNT(16) & ((\sCNT[15]~53\) # (GND)))
-- \sCNT[16]~55\ = CARRY((!\sCNT[15]~53\) # (!sCNT(16)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(16),
	datad => VCC,
	cin => \sCNT[15]~53\,
	combout => \sCNT[16]~54_combout\,
	cout => \sCNT[16]~55\);

-- Location: FF_X49_Y17_N9
\sCNT[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[16]~54_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(16));

-- Location: LCCOMB_X49_Y17_N10
\sCNT[17]~56\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[17]~56_combout\ = (sCNT(17) & (\sCNT[16]~55\ $ (GND))) # (!sCNT(17) & (!\sCNT[16]~55\ & VCC))
-- \sCNT[17]~57\ = CARRY((sCNT(17) & !\sCNT[16]~55\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(17),
	datad => VCC,
	cin => \sCNT[16]~55\,
	combout => \sCNT[17]~56_combout\,
	cout => \sCNT[17]~57\);

-- Location: FF_X49_Y17_N11
\sCNT[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[17]~56_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(17));

-- Location: LCCOMB_X49_Y17_N12
\sCNT[18]~58\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[18]~58_combout\ = (sCNT(18) & (!\sCNT[17]~57\)) # (!sCNT(18) & ((\sCNT[17]~57\) # (GND)))
-- \sCNT[18]~59\ = CARRY((!\sCNT[17]~57\) # (!sCNT(18)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(18),
	datad => VCC,
	cin => \sCNT[17]~57\,
	combout => \sCNT[18]~58_combout\,
	cout => \sCNT[18]~59\);

-- Location: FF_X49_Y17_N13
\sCNT[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[18]~58_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(18));

-- Location: LCCOMB_X49_Y17_N14
\sCNT[19]~60\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[19]~60_combout\ = (sCNT(19) & (\sCNT[18]~59\ $ (GND))) # (!sCNT(19) & (!\sCNT[18]~59\ & VCC))
-- \sCNT[19]~61\ = CARRY((sCNT(19) & !\sCNT[18]~59\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(19),
	datad => VCC,
	cin => \sCNT[18]~59\,
	combout => \sCNT[19]~60_combout\,
	cout => \sCNT[19]~61\);

-- Location: FF_X49_Y17_N15
\sCNT[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[19]~60_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(19));

-- Location: LCCOMB_X49_Y17_N16
\sCNT[20]~62\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[20]~62_combout\ = (sCNT(20) & (!\sCNT[19]~61\)) # (!sCNT(20) & ((\sCNT[19]~61\) # (GND)))
-- \sCNT[20]~63\ = CARRY((!\sCNT[19]~61\) # (!sCNT(20)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(20),
	datad => VCC,
	cin => \sCNT[19]~61\,
	combout => \sCNT[20]~62_combout\,
	cout => \sCNT[20]~63\);

-- Location: FF_X49_Y17_N17
\sCNT[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[20]~62_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(20));

-- Location: LCCOMB_X49_Y17_N18
\sCNT[21]~64\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[21]~64_combout\ = (sCNT(21) & (\sCNT[20]~63\ $ (GND))) # (!sCNT(21) & (!\sCNT[20]~63\ & VCC))
-- \sCNT[21]~65\ = CARRY((sCNT(21) & !\sCNT[20]~63\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(21),
	datad => VCC,
	cin => \sCNT[20]~63\,
	combout => \sCNT[21]~64_combout\,
	cout => \sCNT[21]~65\);

-- Location: FF_X49_Y17_N19
\sCNT[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[21]~64_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(21));

-- Location: LCCOMB_X49_Y17_N20
\sCNT[22]~66\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[22]~66_combout\ = (sCNT(22) & (!\sCNT[21]~65\)) # (!sCNT(22) & ((\sCNT[21]~65\) # (GND)))
-- \sCNT[22]~67\ = CARRY((!\sCNT[21]~65\) # (!sCNT(22)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(22),
	datad => VCC,
	cin => \sCNT[21]~65\,
	combout => \sCNT[22]~66_combout\,
	cout => \sCNT[22]~67\);

-- Location: FF_X49_Y17_N21
\sCNT[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[22]~66_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(22));

-- Location: LCCOMB_X49_Y17_N22
\sCNT[23]~68\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[23]~68_combout\ = sCNT(23) $ (!\sCNT[22]~67\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010110100101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(23),
	cin => \sCNT[22]~67\,
	combout => \sCNT[23]~68_combout\);

-- Location: FF_X49_Y17_N23
\sCNT[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[23]~68_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(23));

-- Location: UNVM_X0_Y18_N40
\~QUARTUS_CREATED_UNVM~\ : fiftyfivenm_unvm
-- pragma translate_off
GENERIC MAP (
	addr_range1_end_addr => -1,
	addr_range1_offset => -1,
	addr_range2_offset => -1,
	is_compressed_image => "false",
	is_dual_boot => "false",
	is_eram_skip => "false",
	max_ufm_valid_addr => -1,
	max_valid_addr => -1,
	min_ufm_valid_addr => -1,
	min_valid_addr => -1,
	part_name => "quartus_created_unvm",
	reserve_block => "true")
-- pragma translate_on
PORT MAP (
	nosc_ena => \~QUARTUS_CREATED_GND~I_combout\,
	xe_ye => \~QUARTUS_CREATED_GND~I_combout\,
	se => \~QUARTUS_CREATED_GND~I_combout\,
	busy => \~QUARTUS_CREATED_UNVM~~busy\);

-- Location: ADCBLOCK_X25_Y28_N0
\~QUARTUS_CREATED_ADC1~\ : fiftyfivenm_adcblock
-- pragma translate_off
GENERIC MAP (
	analog_input_pin_mask => 0,
	clkdiv => 1,
	device_partname_fivechar_prefix => "none",
	is_this_first_or_second_adc => 1,
	prescalar => 0,
	pwd => 1,
	refsel => 0,
	reserve_block => "true",
	testbits => 66,
	tsclkdiv => 1,
	tsclksel => 0)
-- pragma translate_on
PORT MAP (
	soc => \~QUARTUS_CREATED_GND~I_combout\,
	usr_pwd => VCC,
	tsen => \~QUARTUS_CREATED_GND~I_combout\,
	chsel => \~QUARTUS_CREATED_ADC1~_CHSEL_bus\,
	eoc => \~QUARTUS_CREATED_ADC1~~eoc\);

ww_oCNT(0) <= \oCNT[0]~output_o\;

ww_oCNT(1) <= \oCNT[1]~output_o\;

ww_oCNT(2) <= \oCNT[2]~output_o\;

ww_oCNT(3) <= \oCNT[3]~output_o\;

ww_oCNT(4) <= \oCNT[4]~output_o\;

ww_oCNT(5) <= \oCNT[5]~output_o\;

ww_oCNT(6) <= \oCNT[6]~output_o\;

ww_oCNT(7) <= \oCNT[7]~output_o\;

ww_oCNT(8) <= \oCNT[8]~output_o\;

ww_oCNT(9) <= \oCNT[9]~output_o\;

ww_oCNT(10) <= \oCNT[10]~output_o\;

ww_oCNT(11) <= \oCNT[11]~output_o\;

ww_oCNT(12) <= \oCNT[12]~output_o\;

ww_oCNT(13) <= \oCNT[13]~output_o\;

ww_oCNT(14) <= \oCNT[14]~output_o\;

ww_oCNT(15) <= \oCNT[15]~output_o\;

ww_oCNT(16) <= \oCNT[16]~output_o\;

ww_oCNT(17) <= \oCNT[17]~output_o\;

ww_oCNT(18) <= \oCNT[18]~output_o\;

ww_oCNT(19) <= \oCNT[19]~output_o\;

ww_oCNT(20) <= \oCNT[20]~output_o\;

ww_oCNT(21) <= \oCNT[21]~output_o\;

ww_oCNT(22) <= \oCNT[22]~output_o\;

ww_oCNT(23) <= \oCNT[23]~output_o\;
END structure;


