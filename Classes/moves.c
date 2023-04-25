//
// Created by kk199 on 25/04/2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "deck.h"
#include <stdlib.h>


int convertFrokLetter(char letter){
    switch (letter) {
        case 'A':
            letter = 1;
            break;
        case 'K':
            letter = 13;
            break;
        case 'Q':
            letter = 12;
            break;
        case 'J':
            letter = 11;
            break;
        case 'T':
            letter = 10;
            break;
        default:
            atoi(&letter);
            break;

    }

    return letter;
}

bool legalMove(column* col, int colStart, char type, char number, int colEnd){

    column* fromCol;
    column* toCol;
    ListElement* currNode;
    ListElement* placementNode;

    fromCol = col;
    toCol = col;

    for (int i = 0; i < colStart-1; ++i) {

        fromCol = fromCol->next;

    }

    currNode = fromCol->node;

    while(currNode->Card->num != number || currNode->Card->type != type){
        if(currNode->next == NULL){
            return false;
        }
        currNode = currNode->next;

    }

    for (int i = 0; i < colEnd-1; ++i) {

        toCol = toCol->next;

    }

    ListElement* lastElementInRow = toCol->node;

    while (lastElementInRow->next != NULL){
        lastElementInRow = lastElementInRow->next;
    }

    int checkerNumberLast = convertFrokLetter(lastElementInRow->Card->num);
    int checkerNumberFirst = convertFrokLetter(number);



    if(checkerNumberLast == checkerNumberFirst + 1 && lastElementInRow->Card->type != type){
        return true;
    }
    else{
        return false;
    }

}
