#include <stdio.h>
#include <stdlib.h>

#include "truco.h"

int main(void)
{
    int res=0;
    unsigned int user_input_num1;
    unsigned int user_input_num2;
    char user_input_suit1;
    char user_input_suit2;
    truco_card card1=NULL;
    truco_card card2=NULL;

    printf("\n"
           "-----------\n"
           "TRUCO, CHE!\n"
           "-----------\n\n");

    printf("Ingrese el palo de la primera carta ('e' ---> Espada |'o' ---> Oro |'c' ---> Copa |'b' ---> Basto): \n");
    res = scanf(" %c", &user_input_suit1);
    if (res != 1)
    {
        printf("Error al leer.");
        exit(EXIT_FAILURE);
    }
    printf("Ingrese el número de la primera carta: \n");
    res = scanf("%u", &user_input_num1);
    if (res != 1)
    {
        printf("Error al leer.");
        exit(EXIT_FAILURE);
    }
    printf("Ingrese el palo de la primera carta ('e' ---> Espada |'o' ---> Oro |'c' ---> Copa |'b' ---> Basto): \n");
    res = scanf(" %c", &user_input_suit2);
    if (res != 1)
    {
        printf("Error al leer.");
        exit(EXIT_FAILURE);
    }
    printf("Ingrese el número de la primera carta: \n");
    res = scanf("%u", &user_input_num2);
    if (res != 1)
    {
        printf("Error al leer.");
        exit(EXIT_FAILURE);
    }

    card1 = truco_card_new(user_input_num1, user_input_suit1);
    card2 = truco_card_new(user_input_num2, user_input_suit2);

    if (truco_card_tie(card1, card2))
    {
        printf("¡La mano está parda!\n");
        truco_card_dump(card1);
        truco_card_dump(card2);
    }
    else
    {
        printf("La carta \n");
        truco_card_win(card1, card2) ? truco_card_dump(card1) : truco_card_dump(card2);
        printf("'mata' a la carta \n");
        truco_card_win(card1, card2) ? truco_card_dump(card2) : truco_card_dump(card1);
    }
    
    truco_card_destroy(card1);
    truco_card_destroy(card2);
    
    return EXIT_SUCCESS;
}
