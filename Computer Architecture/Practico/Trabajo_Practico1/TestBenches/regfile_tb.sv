`timescale 1 ns / 100 ps
`define clk_freq 5 //--> half a cycle!!
// Esta es la cantidad de lineas que tiene el archivo de testvectors
`define testvector_size 40

module regfile_tb();

	parameter N = 64;

	// DUT SIGNALS
	// entradas del modulo a testear
	logic clk, we3;
	logic [4:0] ra1;
	logic [4:0] ra2;
	logic [4:0] wa3;
	logic [N-1:0] wd3;
	// Salidas del modulo a testear
	logic [N-1:0] rd1; 
	logic [N-1:0] rd2;
	
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
	logic [N-1:0] rd1_expected_output, rd2_expected_output;
	logic [31:0] error_count, vector_index;
	logic [3*5+3*N:0] testvectors [0:`testvector_size-1];
	
	// Aca se instancia el modulo a testear (DUT = Device Under Test)
	regfile dut(clk,we3,ra1,ra2,wa3,wd3,rd1,rd2);

	initial begin
		// Si usan mas seniales de test/control las tendrian que inicializar aca
		vector_index = 0; error_count = 0; rd1_expected_output = 0; rd2_expected_output = 0;
		$readmemb("/home/camilo/Desktop/university-projects-main/university-projects-main/Computer_Architecture/Projectos_Quartus/Trabajo_Practico1/TestBenches/regfile_test.tv", testvectors);	
		#1;
	end
	
	// Aca es donde se usa la linea actual de testvectors. En este caso el modulo tiene una
	// sola entrada, pero otros modulos requeriran que haya otras combinaciones. La variable 
	// expected_output tambien se puede separar en varias seniales, pero sugiero no hacerlo.
	// El mensajito de "tests completed..." deberia aparecer siempre.
	// Si no lo ven en su Modelsim, algo malio sal
	always @(posedge clk) begin
		#2;
		we3 = testvectors[vector_index][3*5+3*N];
		ra1 = testvectors[vector_index][3*5+3*N-1:2*5+3*N];
		ra2 = testvectors[vector_index][2*5+3*N-1:5+3*N];
		wa3 = testvectors[vector_index][5+3*N-1:3*N];
		wd3 = testvectors[vector_index][3*N-1:2*N];
		rd1_expected_output = testvectors[vector_index][2*N-1:N];
		rd2_expected_output = testvectors[vector_index][N-1:0];
	end
	
	// Aca se verifica que la salida del modulo bajo test coincida con la salida esperada
	// El if mas interno concatena todas las salidas en uno solo, ya que dependen del modulo,
	// expected_output viene del archivo testvector.
	// En el cuerpo del if interno se usan instrucciones $display, que van a poder ver en la
	// pantalla del Modelsim cuando termina la simulacion. Para cada modulo que prueben van
	// a tener que cambiar los distintos mensajes de display, excepto quizas el de vector_index
	always @(negedge clk) begin
	   #2;
		if ((rd1 !== rd1_expected_output) || (rd2 !== rd2_expected_output)) begin
			$display("Error: AT TEST %d", vector_index);
			$display(" INPUTS = : %b, %b, %b, %b, %b", we3, ra1, ra2, wa3, wd3);
			$display(" OUTPUTS = %b, %b", rd1, rd2);
			$display(" EXPECTED = %b, %b", rd1_expected_output, rd2_expected_output);
			$display(" TESTVECTOR_LINE: %b)", testvectors[vector_index]);
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