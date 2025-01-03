module alu #(parameter N = 64)(
	
	input logic [N-1:0] a,
	input logic [N-1:0] b,
	input logic [3:0] ALUControl,
	output logic [N-1:0] result,
	output logic zero
	);
				
	always_comb begin
		case (ALUControl)
			4'b0000: begin
				result = a & b;  // a AND b
			end
			4'b0001: begin
				result = a | b;  // a OR b
			end
			4'b0010: begin
				result = a + b;  // add (a+b)
			end
			4'b0110: begin
				result = a - b;  // sub (a-b)
			end
			4'b0111: begin
				result = b;  // pass input b
			end
			default: begin
				result = {N{1'b1}};
			end
		endcase
		
		if (result === {N{1'b0}}) begin
			zero = 1;
		end
		else begin
			zero = 0;
		end
    end
		
endmodule