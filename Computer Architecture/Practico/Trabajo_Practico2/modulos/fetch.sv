module fetch #(parameter N = 64)(
	
	input logic PCSrc_F, clk, reset,
	input logic [N-1:0] PCBranch_F,
	output logic [N-1:0] imem_addr_F
	);
	
	logic [N-1:0] mux2_output, adder_output;
	logic adder_zero;
	
	mux2 mux2_F(adder_output, PCBranch_F, PCSrc_F, mux2_output);
	flopr flopr_F(clk, reset, mux2_output, imem_addr_F);
	alu adder_F(imem_addr_F,64'b0000000000000000000000000000000000000000000000000000000000000100, 4'b0010, adder_output, adder_zero);

endmodule