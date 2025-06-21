`timescale 1 ns / 100 ps
`define clk_freq 5 //--> half a cycle!!
// Esta es la cantidad de lineas que tiene el archivo de testvectors
`define testvector_size 16

module execute_tb();

	parameter N = 64;

	logic clk;
	// DUT SIGNALS
	// entradas del modulo a testear
	logic AluSrc;
	logic [3:0] AluControl;
	logic [N-1:0] PC_E, signImm_E, readData1_E, readData2_E;
	// Salidas del modulo a testear
	logic [N-1:0] PCBranch_E, aluResult_E, writeData_E;
	logic zero_E;
	
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
	logic [N-1:0] PCBranch_E_expected_output, aluResult_E_expected_output, writeData_E_expected_output;
	logic zero_E_expected_output;
	logic [31:0] error_count, vector_index;
	logic [3+2*4+7*N:0] testvectors [0:`testvector_size-1];
	
	// Aca se instancia el modulo a testear (DUT = Device Under Test)
	// Notar que este modulo no necesita señal de clock
	execute dut(AluSrc, AluControl, PC_E, signImm_E, readData1_E, readData2_E, PCBranch_E, aluResult_E, writeData_E, zero_E);

	initial begin
		// Si usan mas seniales de test/control las tendrian que inicializar aca
		vector_index = 0; error_count = 0; AluSrc = 0; AluControl = 0; PC_E = 0; signImm_E = 0; readData1_E = 0; readData2_E = 0;
		PCBranch_E_expected_output = 0; aluResult_E_expected_output = 0; writeData_E_expected_output = 0; zero_E_expected_output = 0;
		$readmemh("/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1_y_2/TestBenches/execute_test.tv", testvectors);	
		#1;
	end
	
	// Aca es donde se usa la linea actual de testvectors. En este caso el modulo tiene una
	// sola entrada, pero otros modulos requeriran que haya otras combinaciones. La variable 
	// expected_output tambien se puede separar en varias seniales, pero sugiero no hacerlo.
	// El mensajito de "tests completed..." deberia aparecer siempre.
	// Si no lo ven en su Modelsim, algo malio sal
	always @(posedge clk) begin
		#2;
		AluSrc = testvectors[vector_index][2*4+7*N];
		AluControl = testvectors[vector_index][2*4+7*N-1:4+7*N];
		PC_E = testvectors[vector_index][4+7*N-1:4+6*N];
		signImm_E = testvectors[vector_index][4+6*N-1:4+5*N];
		readData1_E = testvectors[vector_index][4+5*N-1:4+4*N];
		readData2_E = testvectors[vector_index][4+4*N-1:4+3*N];
		PCBranch_E_expected_output = testvectors[vector_index][4+3*N-1:4+2*N];
		aluResult_E_expected_output = testvectors[vector_index][4+2*N-1:4+N];
		writeData_E_expected_output = testvectors[vector_index][4+N-1:4];
		zero_E_expected_output = testvectors[vector_index][0];
	end
	
	// Aca se verifica que la salida del modulo bajo test coincida con la salida esperada
	// El if mas interno concatena todas las salidas en uno solo, ya que dependen del modulo,
	// expected_output viene del archivo testvector.
	// En el cuerpo del if interno se usan instrucciones $display, que van a poder ver en la
	// pantalla del Modelsim cuando termina la simulacion. Para cada modulo que prueben van
	// a tener que cambiar los distintos mensajes de display, excepto quizas el de vector_index
	always @(negedge clk) begin
	   #2;
		if ((PCBranch_E !== PCBranch_E_expected_output)
			|| (aluResult_E !== aluResult_E_expected_output)
			|| (writeData_E !== writeData_E_expected_output)
			|| (zero_E !== zero_E_expected_output)) begin
			$display("Error: AT TEST %d", vector_index);
			$display(" INPUTS = : %h, %h, %h, %h, %h, %h", AluSrc, AluControl, PC_E, signImm_E, readData1_E, readData2_E);
			$display(" OUTPUTS = %h, %h, %h, %h", PCBranch_E, aluResult_E, writeData_E, zero_E);
			$display(" EXPECTED = %h, %h, %h, %h", PCBranch_E_expected_output, aluResult_E_expected_output, writeData_E_expected_output, zero_E_expected_output);
			$display(" TESTVECTOR_LINE: %h)", testvectors[vector_index]);
			error_count = error_count + 1;
		end
		vector_index = vector_index + 1;
		if (vector_index == `testvector_size) begin 
			$display("%d tests completed with %d errors", vector_index, error_count);
			$stop;
		end	
   end

	// generate clock
	always begin // no sensitivity list, so it always executes
		clk = 1; #5; clk = 0; #5;
	end
	
endmodule