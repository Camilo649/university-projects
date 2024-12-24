module Ejercicio10 (input logic A, B, C, clk,
						  output logic Z);
						  
	logic P;
	
	assign P = A & B;
	always_ff @ (posedge clk)
	begin
		Z <= P | C;
	end
endmodule