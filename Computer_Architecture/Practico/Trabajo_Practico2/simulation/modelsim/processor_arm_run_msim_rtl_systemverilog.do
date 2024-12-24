transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/signext.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/shiftl2.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/regfile.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/mux2.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/maindec.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/imem.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/flopr.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/fetch.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/execute.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/alu.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/writeback.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/processor_arm.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/memory.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/decode.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/datapath.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/controller.sv}
vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/aludec.sv}
vcom -93 -work work {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/modulos/dmem.vhd}

vlog -sv -work work +incdir+/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/test-benches {/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico2/test-benches/processor_tb.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  processor_tb

add wave *
view structure
view signals
run -all
