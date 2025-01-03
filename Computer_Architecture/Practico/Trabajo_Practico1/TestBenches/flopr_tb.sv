`timescale 1ns/100ps
module flopr_tb();

	parameter N = 64;

	logic clk, reset;
	logic [N-1:0] d, q;
	logic [31:0] vectornum, errors; // bookkeeping variables
	logic [N-1:0] testvectors [0:9] = '{ 'd119, // array of testvectors
                                        'd5,
                                        'd39,
                                        'd102,
                                        'd21,
                                        'd24,
                                        'd79,
                                        'd50,
                                        'd96,
                                        'd62 };
   logic [N-1:0] qexpected [0:9] = '{ 'd0, // expected outputs
                                       'd0,
                                       'd0,
                                       'd0,
                                       'd0,
                                       'd21,
                                       'd24,
                                       'd79,
                                       'd50,
                                       'd96 };

	// instantiate device under test
	flopr dut(clk, reset, d, q);
	
	// generate clock
	always // no sensitivity list, so it always executes
		begin
			clk = 1; #5; clk = 0; #5;
		end
		
	initial // at start of test pulse reset
		begin
			vectornum = 0; errors = 0; reset = 1; #50;
			reset = 0;
		end

	// apply test vectors on rising edge of clk
	always @(posedge clk)
		begin
			#1; d = testvectors[vectornum]; q = qexpected[vectornum];
		end

	// check results on falling edge of clk
	always @(negedge clk)
		begin
		if (q !== qexpected[vectornum])
			begin
				$display("Error: inputs = %d", testvectors[vectornum]);
				$display("outputs = %d (%d expected)",q,qexpected[vectornum]);
				errors = errors + 1;
			end
		else $display("outputs = %d",q);
			
	// Note: to print in hexadecimal, use %h.

	// increment array index and read next testvector
		vectornum = vectornum + 1;
		if (vectornum === 10	)
			begin
				$display("%d tests completed with %d errors",vectornum, errors);
				$stop;
			end
	end
	
endmodule
// === and !== can compare values that are 1, 0, x, or z.