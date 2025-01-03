transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1/Practica {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1/Practica/Ejercicio13.sv}

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1/Practica {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1/Practica/Ejercicio10_tb.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  Ejercicio10_tb

add wave *
view structure
view signals
run -all
