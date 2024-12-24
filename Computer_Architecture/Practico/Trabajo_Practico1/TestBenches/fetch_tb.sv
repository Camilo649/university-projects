`timescale 1 ns / 100 ps
`define clk_freq 5 //--> half a cycle!!
// Esta es la cantidad de lineas que tiene el archivo de testvectors
`define testvector_size 13

module fetch_tb();

	parameter N = 64;

	// DUT SIGNALS
	// entradas del modulo a testear
	logic PCSrc_F, clk, reset;
	logic [N-1:0] PCBranch_F;
	// Salidas del modulo a testear
	logic [N-1:0] imem_addr_F;
	
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
	logic [N-1:0] imem_addr_F_expected_output;
	logic [31:0] error_count, vector_index;
	logic [7+2*N:0] testvectors [0:`testvector_size-1];
	
	// Aca se instancia el modulo a testear (DUT = Device Under Test)
	// Notar que este modulo no necesita señal de clock
	fetch dut(PCSrc_F,clk,reset,PCBranch_F,imem_addr_F);

	initial begin
		// Si usan mas seniales de test/control las tendrian que inicializar aca
		vector_index = 0; error_count = 0; PCSrc_F = 0; reset = 0; imem_addr_F_expected_output = 0;
		$readmemh("/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1_y_2/TestBenches/fetch_test.tv", testvectors);	
		#1;
	end
	
	// Aca es donde se usa la linea actual de testvectors. En este caso el modulo tiene una
	// sola entrada, pero otros modulos requeriran que haya otras combinaciones. La variable 
	// expected_output tambien se puede separar en varias seniales, pero sugiero no hacerlo.
	// El mensajito de "tests completed..." deberia aparecer siempre.
	// Si no lo ven en su Modelsim, algo malio sal
	always @(posedge clk) begin
		#2;
		PCSrc_F = testvectors[vector_index][7+2*N-3];
		reset = testvectors[vector_index][2*N];
		PCBranch_F = testvectors[vector_index][2*N-1:N];
		imem_addr_F_expected_output = testvectors[vector_index][N-1:0];
		
		// $display("TEST %d PCSrc_F: %h", vector_index, PCSrc_F);
		// $display("TEST %d reset: %h", vector_index, reset);
		// $display("TEST %d PCBranch_F: %h", vector_index, PCBranch_F);
		// $display("TEST %d imem_addr_F: %h", vector_index, imem_addr_F);
	end
	
	// Aca se verifica que la salida del modulo bajo test coincida con la salida esperada
	// El if mas interno concatena todas las salidas en uno solo, ya que dependen del modulo,
	// expected_output viene del archivo testvector.
	// En el cuerpo del if interno se usan instrucciones $display, que van a poder ver en la
	// pantalla del Modelsim cuando termina la simulacion. Para cada modulo que prueben van
	// a tener que cambiar los distintos mensajes de display, excepto quizas el de vector_index
	always @(negedge clk) begin
	   #2;
		if (imem_addr_F !== imem_addr_F_expected_output) begin
			$display("Error: AT TEST %d", vector_index);
			$display(" INPUTS = : %h, %h, %h", PCSrc_F, reset, PCBranch_F);
			$display(" OUTPUTS = %h", imem_addr_F);
			$display(" EXPECTED = %h", imem_addr_F_expected_output);
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