transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {D:/NASTAVA/LPRS1/2021-22/labs/lab5/lab5_postavke/Automat-pomerac/automat.vhd}

vcom -93 -work work {D:/NASTAVA/LPRS1/2021-22/labs/lab5/lab5_postavke/Automat-pomerac/simulation/modelsim/automat_tb.vhd}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L fiftyfivenm -L rtl_work -L work -voptargs="+acc"  automat_tb

add wave *
view structure
view signals
run 1 us
