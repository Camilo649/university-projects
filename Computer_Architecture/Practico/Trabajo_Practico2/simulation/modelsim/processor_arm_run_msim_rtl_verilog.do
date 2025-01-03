transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos/shiftl2.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos/mux2.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos/execute.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/modulos/alu.sv}

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/test-benches {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Lab1/lab1-adc2024-g2-main/test-benches/execute_tb_CAM.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  execute_tb_CAM

add wave *
view structure
view signals
run -all
