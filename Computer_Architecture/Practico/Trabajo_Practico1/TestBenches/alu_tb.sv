`timescale 1 ns / 100 ps
`define clk_freq 5 //--> half a cycle!!
// Esta es la cantidad de lineas que tiene el archivo de testvectors
`define testvector_size 20

module alu_tb();

	parameter N = 64;

	logic clk;
	// DUT SIGNALS
	// entradas del modulo a testear
	logic [N-1:0] a;
	logic [N-1:0] b;
	logic [3:0] ALUControl;
	// Salidas del modulo a testear
	logic [N-1:0] result;
	logic zero;
	
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
	logic [N-1:0] result_expected_output;
	logic zero_expected_output;
	logic [31:0] error_count, vector_index;
	logic [3*N+7:0] testvectors [0:`testvector_size-1];
	
	// Aca se instancia el modulo a testear (DUT = Device Under Test)
	// Notar que este modulo no necesita señal de clock
	alu dut(a,b,ALUControl,result,zero);

	initial begin
		// Si usan mas seniales de test/control las tendrian que inicializar aca
		vector_index = 0; error_count = 0; result_expected_output = 0; zero_expected_output = 0;
		$readmemh("/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1_y_2/TestBenches/alu_test.tv", testvectors);	
		#1;
	end
	
	// Aca es donde se usa la linea actual de testvectors. En este caso el modulo tiene una
	// sola entrada, pero otros modulos requeriran que haya otras combinaciones. La variable 
	// expected_output tambien se puede separar en varias seniales, pero sugiero no hacerlo.
	// El mensajito de "tests completed..." deberia aparecer siempre.
	// Si no lo ven en su Modelsim, algo malio sal
	always @(posedge clk) begin
		#2;
		ALUControl = testvectors[vector_index][3*N+7:3*N+4];
		a = testvectors[vector_index][3*N+3:2*N+4];
		b = testvectors[vector_index][2*N+3:N+4];
		result_expected_output = testvectors[vector_index][N+3:4];
		zero_expected_output = testvectors[vector_index][0];
	end
	
	// Aca se verifica que la salida del modulo bajo test coincida con la salida esperada
	// El if mas interno concatena todas las salidas en uno solo, ya que dependen del modulo,
	// expected_output viene del archivo testvector.
	// En el cuerpo del if interno se usan instrucciones $display, que van a poder ver en la
	// pantalla del Modelsim cuando termina la simulacion. Para cada modulo que prueben van
	// a tener que cambiar los distintos mensajes de display, excepto quizas el de vector_index
	always @(negedge clk) begin
	   #2;
		if ((result !== result_expected_output) || (zero !== zero_expected_output)) begin
			$display("Error: AT TEST %d", vector_index);
			$display(" INPUTS = : %h, %h, %h", ALUControl, a, b);
			$display(" OUTPUTS = %h, %h", result, zero);
			$display(" EXPECTED = %h, %h", result_expected_output, zero_expected_output);
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