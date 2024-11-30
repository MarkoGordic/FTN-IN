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

-- DATE "12/16/2020 14:23:47"

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
-- ~ALTERA_CONFIG_SEL~	=>  Location: PIN_D7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_nCONFIG~	=>  Location: PIN_E7,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_nSTATUS~	=>  Location: PIN_C4,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_CONF_DONE~	=>  Location: PIN_C5,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default


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

ENTITY 	Semafor IS
    PORT (
	iCLK : IN std_logic;
	iRST : IN std_logic;
	iOK : IN std_logic;
	iHAZ : IN std_logic;
	oRED : OUT std_logic;
	oYELLOW : OUT std_logic;
	oGREEN : OUT std_logic
	);
END Semafor;

-- Design Ports Information
-- oRED	=>  Location: PIN_K1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oYELLOW	=>  Location: PIN_M3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oGREEN	=>  Location: PIN_L2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- iOK	=>  Location: PIN_L3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- iHAZ	=>  Location: PIN_K2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- iCLK	=>  Location: PIN_H5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- iRST	=>  Location: PIN_H4,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Semafor IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_iCLK : std_logic;
SIGNAL ww_iRST : std_logic;
SIGNAL ww_iOK : std_logic;
SIGNAL ww_iHAZ : std_logic;
SIGNAL ww_oRED : std_logic;
SIGNAL ww_oYELLOW : std_logic;
SIGNAL ww_oGREEN : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~_CHSEL_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \iRST~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \iCLK~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \~QUARTUS_CREATED_UNVM~~busy\ : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~~eoc\ : std_logic;
SIGNAL \oRED~output_o\ : std_logic;
SIGNAL \oYELLOW~output_o\ : std_logic;
SIGNAL \oGREEN~output_o\ : std_logic;
SIGNAL \iCLK~input_o\ : std_logic;
SIGNAL \iCLK~inputclkctrl_outclk\ : std_logic;
SIGNAL \iHAZ~input_o\ : std_logic;
SIGNAL \iOK~input_o\ : std_logic;
SIGNAL \sNEXT_STATE.BLINK~0_combout\ : std_logic;
SIGNAL \iRST~input_o\ : std_logic;
SIGNAL \iRST~inputclkctrl_outclk\ : std_logic;
SIGNAL \sCNT~0_combout\ : std_logic;
SIGNAL \sCNT~2_combout\ : std_logic;
SIGNAL \sCNT[1]~1_combout\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \sSTATE.BLINK~q\ : std_logic;
SIGNAL \sSTATE.IDLE~0_combout\ : std_logic;
SIGNAL \sSTATE.IDLE~q\ : std_logic;
SIGNAL \Selector1~0_combout\ : std_logic;
SIGNAL \Selector1~1_combout\ : std_logic;
SIGNAL \sSTATE.HAZARD~q\ : std_logic;
SIGNAL \sNEXT_STATE.GREEN~0_combout\ : std_logic;
SIGNAL \sSTATE.GREEN~q\ : std_logic;
SIGNAL \sNEXT_STATE.YELLOW~0_combout\ : std_logic;
SIGNAL \sSTATE.YELLOW~q\ : std_logic;
SIGNAL \Selector0~0_combout\ : std_logic;
SIGNAL \Selector0~1_combout\ : std_logic;
SIGNAL \sSTATE.RED~q\ : std_logic;
SIGNAL \sNEXT_STATE.RED_YELLOW~0_combout\ : std_logic;
SIGNAL \sSTATE.RED_YELLOW~q\ : std_logic;
SIGNAL \oRED~0_combout\ : std_logic;
SIGNAL \oYELLOW~0_combout\ : std_logic;
SIGNAL sCNT : std_logic_vector(2 DOWNTO 0);
SIGNAL \ALT_INV_iRST~inputclkctrl_outclk\ : std_logic;

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_iCLK <= iCLK;
ww_iRST <= iRST;
ww_iOK <= iOK;
ww_iHAZ <= iHAZ;
oRED <= ww_oRED;
oYELLOW <= ww_oYELLOW;
oGREEN <= ww_oGREEN;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\~QUARTUS_CREATED_ADC1~_CHSEL_bus\ <= (\~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\);

\iRST~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \iRST~input_o\);

\iCLK~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \iCLK~input_o\);
\ALT_INV_iRST~inputclkctrl_outclk\ <= NOT \iRST~inputclkctrl_outclk\;
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: LCCOMB_X26_Y19_N12
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

-- Location: IOOBUF_X0_Y3_N2
\oRED~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \oRED~0_combout\,
	devoe => ww_devoe,
	o => \oRED~output_o\);

-- Location: IOOBUF_X0_Y3_N16
\oYELLOW~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \oYELLOW~0_combout\,
	devoe => ww_devoe,
	o => \oYELLOW~output_o\);

-- Location: IOOBUF_X0_Y7_N9
\oGREEN~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \sSTATE.GREEN~q\,
	devoe => ww_devoe,
	o => \oGREEN~output_o\);

-- Location: IOIBUF_X0_Y8_N15
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

-- Location: CLKCTRL_G3
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

-- Location: IOIBUF_X0_Y3_N8
\iHAZ~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iHAZ,
	o => \iHAZ~input_o\);

-- Location: IOIBUF_X0_Y3_N22
\iOK~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iOK,
	o => \iOK~input_o\);

-- Location: LCCOMB_X1_Y3_N4
\sNEXT_STATE.BLINK~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sNEXT_STATE.BLINK~0_combout\ = (!\iOK~input_o\ & \sSTATE.HAZARD~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \iOK~input_o\,
	datad => \sSTATE.HAZARD~q\,
	combout => \sNEXT_STATE.BLINK~0_combout\);

-- Location: IOIBUF_X0_Y8_N22
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

-- Location: CLKCTRL_G4
\iRST~inputclkctrl\ : fiftyfivenm_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \iRST~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \iRST~inputclkctrl_outclk\);

-- Location: LCCOMB_X1_Y3_N24
\sCNT~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT~0_combout\ = (sCNT(0) & (sCNT(2) $ (sCNT(1)))) # (!sCNT(0) & (sCNT(2) & sCNT(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(0),
	datac => sCNT(2),
	datad => sCNT(1),
	combout => \sCNT~0_combout\);

-- Location: FF_X1_Y3_N25
\sCNT[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(2));

-- Location: LCCOMB_X1_Y3_N8
\sCNT~2\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT~2_combout\ = (!sCNT(0) & ((sCNT(1)) # (!sCNT(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(2),
	datac => sCNT(0),
	datad => sCNT(1),
	combout => \sCNT~2_combout\);

-- Location: FF_X1_Y3_N9
\sCNT[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT~2_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(0));

-- Location: LCCOMB_X1_Y3_N14
\sCNT[1]~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT[1]~1_combout\ = sCNT(1) $ (sCNT(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => sCNT(1),
	datad => sCNT(0),
	combout => \sCNT[1]~1_combout\);

-- Location: FF_X1_Y3_N15
\sCNT[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT[1]~1_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(1));

-- Location: LCCOMB_X1_Y3_N18
\Equal0~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~0_combout\ = (!sCNT(1) & (!sCNT(0) & sCNT(2)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => sCNT(1),
	datac => sCNT(0),
	datad => sCNT(2),
	combout => \Equal0~0_combout\);

-- Location: FF_X1_Y3_N5
\sSTATE.BLINK\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sNEXT_STATE.BLINK~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.BLINK~q\);

-- Location: LCCOMB_X1_Y3_N30
\sSTATE.IDLE~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sSTATE.IDLE~0_combout\ = (\sSTATE.IDLE~q\) # ((\iOK~input_o\ & \Equal0~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \iOK~input_o\,
	datac => \sSTATE.IDLE~q\,
	datad => \Equal0~0_combout\,
	combout => \sSTATE.IDLE~0_combout\);

-- Location: FF_X1_Y3_N31
\sSTATE.IDLE\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sSTATE.IDLE~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.IDLE~q\);

-- Location: LCCOMB_X1_Y3_N0
\Selector1~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Selector1~0_combout\ = (\sSTATE.IDLE~q\ & (\iHAZ~input_o\ & (!\sSTATE.BLINK~q\ & !\sSTATE.HAZARD~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \sSTATE.IDLE~q\,
	datab => \iHAZ~input_o\,
	datac => \sSTATE.BLINK~q\,
	datad => \sSTATE.HAZARD~q\,
	combout => \Selector1~0_combout\);

-- Location: LCCOMB_X1_Y3_N16
\Selector1~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Selector1~1_combout\ = (\Selector1~0_combout\) # ((!\iOK~input_o\ & \sSTATE.BLINK~q\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \iOK~input_o\,
	datac => \sSTATE.BLINK~q\,
	datad => \Selector1~0_combout\,
	combout => \Selector1~1_combout\);

-- Location: FF_X1_Y3_N17
\sSTATE.HAZARD\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Selector1~1_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.HAZARD~q\);

-- Location: LCCOMB_X1_Y3_N20
\sNEXT_STATE.GREEN~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sNEXT_STATE.GREEN~0_combout\ = (\sSTATE.RED_YELLOW~q\ & !\iHAZ~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \sSTATE.RED_YELLOW~q\,
	datad => \iHAZ~input_o\,
	combout => \sNEXT_STATE.GREEN~0_combout\);

-- Location: FF_X1_Y3_N21
\sSTATE.GREEN\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sNEXT_STATE.GREEN~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.GREEN~q\);

-- Location: LCCOMB_X1_Y3_N10
\sNEXT_STATE.YELLOW~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sNEXT_STATE.YELLOW~0_combout\ = (\sSTATE.GREEN~q\ & !\iHAZ~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \sSTATE.GREEN~q\,
	datad => \iHAZ~input_o\,
	combout => \sNEXT_STATE.YELLOW~0_combout\);

-- Location: FF_X1_Y3_N11
\sSTATE.YELLOW\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sNEXT_STATE.YELLOW~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.YELLOW~q\);

-- Location: LCCOMB_X1_Y3_N2
\Selector0~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Selector0~0_combout\ = (\iOK~input_o\ & ((\sSTATE.BLINK~q\) # ((!\iHAZ~input_o\ & \sSTATE.YELLOW~q\)))) # (!\iOK~input_o\ & (!\iHAZ~input_o\ & ((\sSTATE.YELLOW~q\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011001110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \iOK~input_o\,
	datab => \iHAZ~input_o\,
	datac => \sSTATE.BLINK~q\,
	datad => \sSTATE.YELLOW~q\,
	combout => \Selector0~0_combout\);

-- Location: LCCOMB_X1_Y3_N28
\Selector0~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Selector0~1_combout\ = (\Selector0~0_combout\) # ((\iOK~input_o\ & ((\sSTATE.HAZARD~q\) # (!\sSTATE.IDLE~q\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111110001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \iOK~input_o\,
	datab => \sSTATE.HAZARD~q\,
	datac => \sSTATE.IDLE~q\,
	datad => \Selector0~0_combout\,
	combout => \Selector0~1_combout\);

-- Location: FF_X1_Y3_N29
\sSTATE.RED\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Selector0~1_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.RED~q\);

-- Location: LCCOMB_X1_Y3_N26
\sNEXT_STATE.RED_YELLOW~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sNEXT_STATE.RED_YELLOW~0_combout\ = (!\iHAZ~input_o\ & \sSTATE.RED~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \iHAZ~input_o\,
	datad => \sSTATE.RED~q\,
	combout => \sNEXT_STATE.RED_YELLOW~0_combout\);

-- Location: FF_X1_Y3_N27
\sSTATE.RED_YELLOW\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sNEXT_STATE.RED_YELLOW~0_combout\,
	clrn => \ALT_INV_iRST~inputclkctrl_outclk\,
	ena => \Equal0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \sSTATE.RED_YELLOW~q\);

-- Location: LCCOMB_X1_Y3_N12
\oRED~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \oRED~0_combout\ = (\sSTATE.RED_YELLOW~q\) # (\sSTATE.RED~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \sSTATE.RED_YELLOW~q\,
	datad => \sSTATE.RED~q\,
	combout => \oRED~0_combout\);

-- Location: LCCOMB_X1_Y3_N22
\oYELLOW~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \oYELLOW~0_combout\ = (\sSTATE.RED_YELLOW~q\) # ((\sSTATE.BLINK~q\) # (\sSTATE.YELLOW~q\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011111110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \sSTATE.RED_YELLOW~q\,
	datab => \sSTATE.BLINK~q\,
	datac => \sSTATE.YELLOW~q\,
	combout => \oYELLOW~0_combout\);

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

ww_oRED <= \oRED~output_o\;

ww_oYELLOW <= \oYELLOW~output_o\;

ww_oGREEN <= \oGREEN~output_o\;
END structure;


