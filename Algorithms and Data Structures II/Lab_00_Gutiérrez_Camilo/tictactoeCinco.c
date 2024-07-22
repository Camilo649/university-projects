#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define BOARD_SIZE 5
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int cell = 0;

    print_sep(BOARD_SIZE);
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(BOARD_SIZE);
    }
}

//FUNCIONES AUXILIARES

char get_hotizontal_winner(char board[BOARD_SIZE][BOARD_SIZE], unsigned int row) //Función que verifica si alguien ganó de manera horizontal.
{
    unsigned int column = 0;
    char h_winner = board[row][column];
    
    while (column < (BOARD_SIZE - 1) && h_winner != '-')
    {
        column = column + 1;
        if (h_winner != board[row][column])
        {
            h_winner = '-';
        }
    }

    return h_winner;
}

char get_vertical_winner(char board[BOARD_SIZE][BOARD_SIZE], unsigned int column) //Función que verifica si alguien ganó de manera vertical.
{
    unsigned int row = 0;
    char v_winner = board[row][column];

    while (row < (BOARD_SIZE - 1) && v_winner != '-')
    {
        row = row + 1;
        if (v_winner != board[row][column])
        {
            v_winner = '-';
        }
    }

    return v_winner;
}

char get_first_diagonal_winner(char board[BOARD_SIZE][BOARD_SIZE]) //Función que verifica si alguien ganó completando la primera diagonal.
{
    unsigned int i = 0;
    char d_winner = board[i][i];

    while (i < (BOARD_SIZE - 1) && d_winner != '-')
    {
        i = i + 1;
        if (d_winner != board[i][i])
        {
            d_winner = '-';
        }
    }

    return d_winner;
}

char get_second_diagonal_winner(char board[BOARD_SIZE][BOARD_SIZE]) //Función que verifica si alguien ganó completando la segunda diagonal.
{
    unsigned int j = 0;
    char d_winner = board[BOARD_SIZE - 1][j];

    while (j < (BOARD_SIZE - 1) && d_winner != '-')
    {
        j = j + 1;
        if (d_winner != board[(BOARD_SIZE - 1) - j][j])
        {
            d_winner = '-';
        }
    }

    return d_winner;
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char winner = get_first_diagonal_winner(board);
    unsigned int i = 0;

    if (winner == '-')
    {
        winner = get_second_diagonal_winner(board);
    }
    while (i < BOARD_SIZE && winner == '-')
    {
        winner = get_hotizontal_winner(board, i);
        if (winner == '-')
        {
            winner = get_vertical_winner(board, i);
        }
        i = i + 1;   
    }
    
    return winner;
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])
{
    bool free_cell = false;
    int row;
    int column;

    row = 0;
    while (row < BOARD_SIZE && free_cell == false){
        column = 0;
        while (column < BOARD_SIZE && free_cell == false){
            if (board[row][column] == '-')
          {
            free_cell = true;
          }
            column = column + 1;
        }
        row = row +1 ;
    }

    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    //Mediante dos ciclos for, me creo un tablero N*N "vacío".
    char board[BOARD_SIZE][BOARD_SIZE];
    for (unsigned int i = 0; i < BOARD_SIZE; i++){
        for (unsigned int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = '-';
        }
    }
    char turn = 'X';
    char winner = '-';
    int cell = 0;
 
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posicion (numero del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un numero desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / BOARD_SIZE;
            int colum = cell % BOARD_SIZE;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda invalida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Gano %c\n", winner);
    }
    return 0;
}