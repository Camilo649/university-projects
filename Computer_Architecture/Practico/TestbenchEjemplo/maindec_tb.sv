`timescale 1 ns / 100 ps
`define clk_freq 5 //--> half a cycle!!
// Esta es la cantidad de lineas que tiene el archivo de testvectors
`define testvector_size 21


module maindec_tb();
	logic clk, reset;
	// DUT SIGNALS
	// entradas del modulo decoder
	logic [10:0] Op;
	// Salidas del modulo decoder
	logic Reg2Loc, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch;
	logic [1:0] ALUOp
	
	// TEST AND CONTROL DATA
	//logic [2:0] padding; // No es necesario agregar seniales muertas o no conectadas, pero puede llegar a hacer falta
	// Estas son seniales que sirven para el test, y no serían parte de nuestro 
	// modulo cuando se lo instancie como parte de una jerarquia mas grande
	// Notar lo siguiente:
	// - expected_output es un array de bits que despues se compara contra una concatenacion
	// - error_count y vector_index son seniales de 32 bits, pero en el codigo 
	// del testbench se los "trata como" enteros. No existe declararlos como int
	// - testvectors esta declarado como una matriz (ancho primero, alto despues del nombre
	// porque va a tener por cada fila una fila del archivo de testvectors
	logic [8:0] expected_output;
	logic [31:0] error_count, vector_index;
	logic [19:0] testvectors [0:`testvector_size-1];
	
	// Aca se instancia el modulo a testear (DUT = Device Under Test)
	// Notar que este modulo no necesita señal de clock
	maindec dut(.Op(Op), 
				.Reg2Loc(Reg2Loc), .ALUSrc(ALUSrc), .MemtoReg(MemtoReg), 
				.RegWrite(RegWrite), .MemRead(MemRead), .MemWrite(MemWrite), 
				.Branch(Branch), .ALUOp(ALUOp));

	initial begin
		// Si usan mas seniales de test/control las tendrian que inicializar aca
		vector_index = 0; error_count = 0; expected_output = 0; clk = 1; reset = 1; 
		$readmemb("testvectors/maindec_test.tv", testvectors); // Recomiendo no cambiar esta linea
		#3; reset = 0;
	end
	
	// Aca se verifica que la salida del modulo bajo test coincida con la salida esperada
	// El if mas interno concatena todas las salidas en uno solo, ya que dependen del modulo,
	// expected_output viene del archivo testvector.
	// En el cuerpo del if interno se usan instrucciones $display, que van a poder ver en la
	// pantalla del Modelsim cuando termina la simulacion. Para cada modulo que prueben van
	// a tener que cambiar los distintos mensajes de display, excepto quizas el de vector_index
	always @(posedge clk) begin
	   #2;
		if (~reset) begin
			if ({Reg2Loc, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp} !== expected_output) begin  //MODIFY SIGNALS CHECK
				$display("Error: AT TEST %d", vector_index);
				$display(" INPUTS = OP : %b", Op); 	//MODIFY
				$display(" OUTPUTS = %b, %b, %b, %b, %b, %b, %b, %b", Reg2Loc, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp);	//MODIFY
				$display(" EXPECTED = %b", expected_output);	//MODIFY
				$display(" TESTVECTOR_LINE: %h)", testvectors[vector_index]);
				error_count = error_count + 1;
			end
		end	
   end
	
	// Aca es donde se usa la linea actual de testvectors. En este caso el modulo tiene una
	// sola entrada, pero otros modulos requeriran que haya otras combinaciones. La variable 
	// expected_output tambien se puede separar en varias seniales, pero sugiero no hacerlo.
	// El mensajito de "tests completed..." deberia aparecer siempre, a diferencia del loop anterior
	// Si no lo ven en su Modelsim, algo malio sal
	always @(negedge clk) begin
		#2;
		// Ejemplo de una linea de testvector: 11111000000___110001000
		// En Op entran los primeros 11 bits, en expected_output el resto
		{Op, expected_output} = testvectors[vector_index]; //MODIFY
		vector_index = vector_index + 1;
		if (vector_index == `testvector_size+1) begin 
		   $display("%d tests completed with %d errors", vector_index, error_count);
			$stop;
		end
	end

	always begin
		clk = ~clk;
		#`clk_freq;
	end
endmodule
