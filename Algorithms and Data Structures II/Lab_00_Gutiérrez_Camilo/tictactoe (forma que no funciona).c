#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define BOARD_SIZE 3
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

char get_hotizontal_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char h_winner = '-';
    bool h_winner_exists;
    int j;

    for (int i = 0; i < BOARD_SIZE; i++){
        j = 0;
        h_winner_exists = true;
        while (j < BOARD_SIZE - 1 && h_winner_exists){
            if (board[i][j] == board[i][j+1] && board[i][j] != '-')
            {
                j = j+1;
                if (j == BOARD_SIZE - 1)
                {
                    h_winner = board[i][j];
                }
            }
            else
            {
                h_winner_exists = false;
            }
        }
    }
    return h_winner;
}

char get_vertical_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char v_winner = '-';
    bool v_winner_exists;
    int j;

    for (int i = 0; i < BOARD_SIZE; i++){
        j = 0;
        v_winner_exists = true;
        while (j < BOARD_SIZE - 1 && v_winner_exists){
            if (board[j][i] == board[j+1][i] && board[j][i] != '-')
            {
               j = j+1;
               if (j == BOARD_SIZE - 1)
                {
                    v_winner = board[j][i];
                }
            }
            else
            {
                v_winner_exists = false;
            }
        }
    }
    return v_winner;
}

char get_first_diagonal_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char d_winner = '-';
    int i = 0;
    bool d_winner_exists = true;

    while (i<BOARD_SIZE - 1 && d_winner_exists){
        if (board[i][i] == board[i+1][i+1] && board[i][i] != '-')
        {
            i = i+1;
            if (i == BOARD_SIZE - 1)
            {
                d_winner = board[i][i];
            }
        }
        else
        {
            d_winner_exists = false;
        }
    }
    return d_winner;
}

char get_second_diagonal_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char d_winner = '-';
    int i = 0;
    int j = BOARD_SIZE - 1;
    bool d_winner_exists = true;

    while (i<BOARD_SIZE - 1 && j>0 && d_winner_exists){
        if (board[i][j] == board[i+1][j-1] && board[i][j] != '-')
        {
            i = i+1;
            j = j-1;
            if (i == BOARD_SIZE - 1 && j == 0)
            {
                d_winner = board[i][j];
            }
            else
            {
                d_winner_exists = false;
            }
        }
    }
    return d_winner;
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char winner = '-';
    if (get_hotizontal_winner(board) != '-')
    {
        winner = get_hotizontal_winner(board);
    }
    else if (get_vertical_winner(board) != '-')
    {
        winner = get_vertical_winner(board);
    }
    else if (get_first_diagonal_winner(board) != '-')
    {
        winner = get_first_diagonal_winner(board);
    }
    else if (get_second_diagonal_winner(board) != '-')
    {
        winner = get_second_diagonal_winner(board);
    }
    return winner;
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])
{
    bool free_cell=false;
    int row;
    int column;

    row = 0;
    while (row < BOARD_SIZE && free_cell==false){
        column = 0;
        while (column < BOARD_SIZE && free_cell==false){
            if (board[row][column] == '-')
          {
            free_cell = true;
          }
            column = column+1;
        }
        row = row+1;
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

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