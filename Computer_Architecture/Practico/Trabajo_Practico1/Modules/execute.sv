module execute #(parameter N = 64)(
	
	input logic AluSrc,
	input logic [3:0] AluControl,
	input logic [N-1:0] PC_E, signImm_E, readData1_E, readData2_E,
	output logic [N-1:0] PCBranch_E, aluResult_E, writeData_E,
	output logic zero_E
	);
	
	logic [N-1:0] shiftl2_output, mux2_output;
	logic adder_zero;
	
	shiftl2 shiftl2_E(signImm_E, shiftl2_output);
	alu adder_E(PC_E, shiftl2_output, 4'b0010, PCBranch_E, adder_zero);
	mux2 mux2_E(readData2_E, signImm_E, AluSrc, mux2_output);
	alu alu_E(readData1_E, mux2_output, AluControl, aluResult_E, zero_E);
	assign writeData_E = readData2_E;

endmodule