onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix decimal /execute_tb/clk
add wave -noupdate -radix decimal /execute_tb/AluSrc
add wave -noupdate -radix decimal /execute_tb/AluControl
add wave -noupdate -radix decimal /execute_tb/PC_E
add wave -noupdate -radix decimal /execute_tb/signImm_E
add wave -noupdate -radix decimal /execute_tb/readData1_E
add wave -noupdate -radix decimal /execute_tb/readData2_E
add wave -noupdate -radix decimal /execute_tb/PCBranch_E
add wave -noupdate -radix decimal /execute_tb/aluResult_E
add wave -noupdate -radix decimal /execute_tb/writeData_E
add wave -noupdate -radix decimal /execute_tb/zero_E
add wave -noupdate -radix decimal /execute_tb/PCBranch_E_expected_output
add wave -noupdate -radix decimal /execute_tb/aluResult_E_expected_output
add wave -noupdate -radix decimal /execute_tb/writeData_E_expected_output
add wave -noupdate -radix decimal /execute_tb/zero_E_expected_output
add wave -noupdate -radix decimal /execute_tb/error_count
add wave -noupdate -radix decimal /execute_tb/vector_index
add wave -noupdate -divider shiftl2
add wave -noupdate -radix decimal /execute_tb/dut/shiftl_E/a
add wave -noupdate -radix decimal /execute_tb/dut/shiftl_E/y
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {3186 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 236
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {60679 ps}
