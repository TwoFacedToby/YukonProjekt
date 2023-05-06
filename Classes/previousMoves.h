//
// Created by kk199 on 05/05/2023.
//

#ifndef YUKONPROJEKT_PREVIOUSMOVES_H
#define YUKONPROJEKT_PREVIOUSMOVES_H

#include <stdbool.h>
#include "deck.h"

typedef struct moveHistory{
    int startCol; //ACE == A, 2-9 = 2-9, 10 == T, Jack == J, Queen == Q, King == K
    char cardNum; //Clubs == C, Diamonds == D, Hearts == H, Spades == S
    char cardType;
    int endColumn; //Columns 1-7 == 1-7, Finished Piles 1-4 == 8-11
    bool was_visible;
    struct moveHistory* next;
}moves;

moves* addRedoToUndo(moves* lastMoves, column* col, moves* undoMove);

moves* undoLastMove(moves* lastMoves, column* col, moves* undoMove);

moves* instantiateMovesList();

moves* addPreviousMoves(moves* playerMoves, int colStart, char cardNum, char cardType, int colEnd, bool wasVisible);


#endif //YUKONPROJEKT_PREVIOUSMOVES_H
