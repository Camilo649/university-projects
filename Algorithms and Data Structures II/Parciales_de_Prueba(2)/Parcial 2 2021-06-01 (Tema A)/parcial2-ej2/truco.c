#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

struct _s_truco_card {
    unsigned int rank;
    char suit;
    unsigned int num;
};

#define ESPADA "ESPADA"
#define BASTO  "BASTO"
#define ORO    "ORO"
#define COPA   "COPA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'e') {
        str = ESPADA;
    } else if (p=='b') {
        str = BASTO;
    } else if (p=='o') {
        str = ORO;
    } else if (p=='c') {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit) {
    printf(" ----------------\n"
           " :%2d            :\n"
           " :              :\n"
           " :              :\n"
           " :    ""%-7s""   :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :           %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit) {
    int rank=0;

    if (4 <= num && num <= 12) 
    { 
        if (num == 12)
        {
            rank = 8;
        }
        else if (num == 11)
        {
            rank = 7;
        }
        else if (num == 10)
        {
            rank = 6;
        }
        else if (num == 7 && (suit == 'c' || suit == 'b'))
        {
            rank = 3;
        }
        else if (num == 6)
        {
            rank = 2;
        }
        else if (num == 5)
        {
            rank = 1;
        }
    } 
    else 
    { 
        if (num == 3)
        {
            rank = 11;
        }
        else if (num == 2)
        {
            rank = 10;
        }
        else if (suit == 'c' || suit == 'o')
        {
            rank = 9;
        } 
    }
    if (num==1 && suit == 'e') 
    {     
        rank = 15;
    } 
    else if (num==1 && suit=='b') 
    { 
        rank = 14;
    } 
    else if (num==7 && suit=='e') 
    { 
        rank = 13;
    } 
    else if (num==7 && suit=='o') 
    { 
        rank = 12;
    }
    return rank;
}

static bool is_valid_num(int num){

    return (1 <= num && num <= 12 && num != 8 && num != 9);
}

static bool is_valid_suit(char p){

    return (p=='e' || p=='o' || p=='c' || p=='b');
}

static bool invrep(truco_card c) {

    return c != NULL && is_valid_num(c->num) && is_valid_suit(c->suit);
}

truco_card truco_card_new(int num, char p) {
    truco_card card;
   
    card = malloc(sizeof(struct _s_truco_card ));
    card->suit = p;
    card->num = num;
    card->rank = card_rank(num, p);

    assert(invrep(card));
    return card;
}

bool truco_card_win(truco_card a, truco_card b) {
   
    return a->rank > b->rank;
}

bool truco_card_tie(truco_card a, truco_card b) {

    return a->rank == b->rank;
}

void truco_card_dump(truco_card c) {
    dump(c->num, c->suit);
}

truco_card truco_card_destroy(truco_card c) {
    free(c);
    c = NULL;

    return c;
}
