//
// Created by tobia on 24/04/2023.
//
#include <stdbool.h>

#ifndef YUKONPROJEKT_DECK_H
#define YUKONPROJEKT_DECK_H

typedef struct CARD{
    char num; //ACE == A, 2-9 = 2-9, 10 == T, Jack == J, Queen == Q, King == K
    char type; //Clubs == C, Diamonds == D, Hearts == H, Spades == S
    int column; //Columns 1-7 == 1-7, Finished Piles 1-4 == 8-11
    bool is_visible;
}card;

typedef struct Node{
    card* Card;
    struct Node* next;
}ListElement;

typedef struct DeckNode{
    card Card;
    struct DeckNode* next;
}deckNode;

typedef struct ColumnStart{
    int column;
    struct Node* node;
    struct ColumnStart* next;
}column;

//For the printf statement in main
typedef struct ColumnStartNode {
    column *col_start;
    struct ColumnStartNode *next;
} ColumnStartNode;

deckNode* readDeckFromFile(const char* filename);

column* instantiate_yukon_board(deckNode* deck, bool showCards, bool visible);

deckNode* loader(char inputArr[]);

void printer(column* col);

deckNode* splitter (deckNode* deck, int splitCard);

#endif //YUKONPROJEKT_DECK_H
