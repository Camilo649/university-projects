module shiftl2 #(parameter N = 64)(
	
	input logic [N-1:0] a,
	output logic [N-1:0] y
	);
	
	assign y = a << 2;

endmodule