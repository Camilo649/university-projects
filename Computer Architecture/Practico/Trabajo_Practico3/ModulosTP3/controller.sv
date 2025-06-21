// CONTROLLER

module controller(input logic [10:0] instr,
						input logic ExcAck, ExtIRQ, reset,
						output logic [3:0] AluControl, EStatus,
						output logic [1:0] AluSrc,
						output logic reg2loc, regWrite, Branch, memtoReg,
										 memRead, memWrite, ExtIAck, Exc, ERet,
										 BranchR);
											
	logic [1:0] AluOp_s;
											
	maindec 	decPpal 	(.Op(instr),
							.reset(reset),
							.ExtIRQ(ExtIRQ),
							.Reg2Loc(reg2loc), 
							.ALUSrc(AluSrc), 
							.MemtoReg(memtoReg), 
							.RegWrite(regWrite), 
							.MemRead(memRead), 
							.MemWrite(memWrite), 
							.Branch(Branch), 
							.ALUOp(AluOp_s),
							.Exc(Exc),
							.ERet(ERet),
							.EStatus(EStatus),
							.BranchR(BranchR));	
					
								
	aludec 	decAlu 	(.funct(instr), 
							.aluop(AluOp_s), 
							.alucontrol(AluControl));
							
	assign ExtIAck = ExcAck & ExtIRQ;
			
endmodule
