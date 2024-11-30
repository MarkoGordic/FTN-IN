transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vcom -93 -work work {Semafor.vho}

vcom -93 -work work {D:/NASTAVA/LPRS1/2020-21/labs/Uradjene vezbe/lab5/lab5_postavka/simulation/modelsim/Semafor_tb.vhd}

vsim -t 1ps +transport_int_delays +transport_path_delays -sdftyp /NA=Semafor_vhd.sdo -L altera -L altera_lnsim -L fiftyfivenm -L gate_work -L work -voptargs="+acc"  Semafor_tb

add wave *
view structure
view signals
run 1 us
