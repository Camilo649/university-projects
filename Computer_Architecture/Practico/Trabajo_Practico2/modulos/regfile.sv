module regfile #(parameter N=64)
	(input logic clk, we3,
	input logic [4:0] ra1, ra2, wa3,
	input logic [N-1:0] wd3,
	output logic [N-1:0] rd1, rd2);

	// declaramos el banco de 32 registros de 64 bits cada uno
	logic [N-1:0] REGS [0:31];
	
	initial 
	begin
		// Inicializamos los registros x0 a X30 con sus valores correspondiente y X31 en cero 
		REGS  = '{default:'0};
		for (logic [N-1:0] i = 0; i < 'd31; ++i) 
			REGS[i] = i;
	end
	
	always @(posedge clk) begin
		if (we3 == 1 && wa3 != 5'd31)
			REGS[wa3] <= wd3;
	end

	always_comb begin
		// Para rd1
		if (ra1 == 5'd31)
			rd1 = 64'b0;
	   else 
	       rd1 = REGS[ra1];
	   // Para rd2
		if (ra2 == 5'd31)
			rd2 = 64'b0;
	   else 
	       rd2 = REGS[ra2];
	end

endmodule