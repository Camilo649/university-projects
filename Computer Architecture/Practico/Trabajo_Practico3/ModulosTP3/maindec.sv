module maindec (
	
	input logic [10:0] Op,
	input logic reset,
	input logic ExtIRQ,
	output logic Reg2Loc,
	output logic [1:0] ALUSrc,
	output logic MemtoReg,
	output logic RegWrite,
	output logic MemRead,
	output logic MemWrite,
	output logic Branch,
	output logic [1:0] ALUOp,
	output logic Exc,
	output logic ERet,
	output logic [3:0] EStatus,
	output logic BranchR
	);
				
	logic NotAnInstr;
	always_comb begin
		if (reset) begin
			Reg2Loc = 0;
			ALUSrc = 0;
			MemtoReg = 0;
			RegWrite = 0;
			MemRead = 0;
			MemWrite = 0;
			Branch = 0;
			ALUOp = 2'b00;
			NotAnInstr = 0;
			Exc = 0;
			ERet = 0;
			EStatus = 4'b0000;
			BranchR = 0;
		end else begin
			casez (Op)
				11'b100_0101_1000, 11'b110_0101_1000, 11'b100_0101_0000, 11'b101_0101_0000: begin // R-type
					Reg2Loc = 0;
					ALUSrc = 2'b00;
					MemtoReg = 0;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b10;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b111_1100_0010: begin // LDUR
					Reg2Loc = 1'bx;
					ALUSrc = 2'b01;
					MemtoReg = 1;
					RegWrite = 1;
					MemRead = 1;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b00;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b111_1100_0000: begin // STUR
					Reg2Loc = 1;
					ALUSrc = 2'b01;
					MemtoReg = 1'bx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 1;
					Branch = 0;
					ALUOp = 2'b00;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b101_1010_0???: begin // CBZ
					Reg2Loc = 1;
					ALUSrc = 2'b00;
					MemtoReg = 1'bx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 0;
					Branch = 1;
					ALUOp = 2'b01;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b110_1011_0100: begin // ERET
					Reg2Loc = 0;
					ALUSrc = 2'b00;
					MemtoReg = 1'bx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 0;
					Branch = 1;
					ALUOp = 2'b01;
					ERet = 1;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b110_1010_1001: begin // MRS
					Reg2Loc = 1;
					ALUSrc = 2'b1x;
					MemtoReg = 0;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b01;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
				11'b110_1011_0000: begin // BR
					Reg2Loc = 0;
					ALUSrc = 2'b00;
					MemtoReg = 0;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b01;
					ERet = 0;
					EStatus = 4'b0000;
					NotAnInstr = 0;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 1;
				end
				default: begin // Invalid OpCode
					Reg2Loc = 1'bx;
					ALUSrc = 2'bxx;
					MemtoReg = 0;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'bxx;
					ERet = 0;
					EStatus = 4'b0010;
					NotAnInstr = 1;
					Exc = ExtIRQ | NotAnInstr;
					BranchR = 0;
				end
			endcase
			if (ExtIRQ) begin
				EStatus = 4'b0001;
			end
		end
	end
		
endmodule