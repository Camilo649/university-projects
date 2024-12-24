module signext #(parameter N = 64)(
	
	input logic [31:0] a,
	output logic [N-1:0] y
	);
	
	logic [10:0] opcode;
	always_comb begin
      y = {N{1'b0}};
		opcode = a[31:21];
		// Si a es LDUR o STUR
		if (opcode === 11'b111_1100_0010 || opcode === 11'b111_1100_0000) begin
			y = {{N-9{a[20]}}, a[20:12]};
		end
		// Si a es CBZ
		else if (opcode[10:3] === 8'b101_1010_0) begin
			y = {{N-19{a[23]}}, a[23:5]};
		end
	end

endmodule