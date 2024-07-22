	.text
    	

	MOVZ X1, 0xBBB0, LSL#48 		//X1 = 0xBBB0000000000000
	MOVK X1, 0xAAA, LSL#0 			//X1 = 0xBBB0000000000AAA
    


end:
infloop: B infloop
