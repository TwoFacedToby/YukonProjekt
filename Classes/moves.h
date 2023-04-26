//
// Created by kk199 on 25/04/2023.
//
#include <stdbool.h>
#include "deck.h"

#ifndef YUKONPROJEKT_MOVES_H
#define YUKONPROJEKT_MOVES_H

bool legalMove(column* col, int colStart, char type, char number, int colEnd);
bool legalPileMove(column* col, int colStart, int colEnd);

#endif //YUKONPROJEKT_MOVES_H
