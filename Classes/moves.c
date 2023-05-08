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
            letter = atoi(&letter);
            break;

    }

    return letter;
}

int legalMove(column* col, int colStart, char type, char number, int colEnd){

    column* fromCol;
    column* toCol;
    ListElement* currNode;
    ListElement* prev;


    fromCol = col;
    toCol = col;

    for (int i = 0; i < colStart-1; ++i) {

        fromCol = fromCol->next;

    }


    currNode = fromCol->node;

    if(number != 'F' && type != 'F'){

        while(currNode->Card->num != number || currNode->Card->type != type){
            if(currNode->next == NULL){
                return 0;
            }
            prev = currNode;
            currNode = currNode->next;

        }
    }
    else{
        while (currNode->next != NULL){
            prev = currNode;
            currNode = currNode->next;
        }
    }


    for (int i = 0; i < colEnd-1; ++i) {

        toCol = toCol->next;

    }

    int checkerNumberFirst = convertFrokLetter(currNode->Card->num);

    if(toCol->node == NULL && checkerNumberFirst == 13){
        int turned = 1;
        if(!prev->Card->is_visible){
            prev->Card->is_visible = true;
            turned = 2;
        }
        prev->next = NULL;
        toCol->node = currNode;
        return turned;
    }

    ListElement* lastElementInRow = toCol->node;

    while (lastElementInRow->next != NULL){
        lastElementInRow = lastElementInRow->next;
    }

    int checkerNumberLast = convertFrokLetter(lastElementInRow->Card->num);

    if(checkerNumberLast == checkerNumberFirst + 1 && lastElementInRow->Card->type != currNode->Card->type){
        int turned = 1;
        lastElementInRow->next = currNode;
        if(!prev->Card->is_visible){
            prev->Card->is_visible = true;
            turned = 2;
        }
        prev->next = NULL;

        return turned;
    }
    else{
        return 0;
    }
}


int legalPileMove(column* col, int colStart, int colEnd){

    column* fromCol;
    column* toCol;

    fromCol = col;
    toCol = col;

    ListElement* currNode;
    ListElement* prev;
    ListElement* pileNode;

    for (int i = 0; i < colStart-1; ++i) {

        fromCol = fromCol->next;

    }

    if(fromCol->node == NULL){
        return 0;
    }

    currNode = fromCol->node;

    bool firstCard = true;
    while (currNode->next != NULL){
        prev = currNode;
        currNode = currNode->next;
        firstCard = false;
    }

    for (int i = 0; i < colEnd+6; ++i) {

        toCol = toCol->next;

    }
    int cardFrom = convertFrokLetter(currNode->Card->num);

    if(toCol->node == NULL && cardFrom == 1){

        int turned = 1;

        if(firstCard){
            fromCol->node = NULL;
        }
        else{
            if(!prev->Card->is_visible){
                prev->Card->is_visible = true;
                turned = 2;
            }
            prev->next = NULL;
        }

        toCol->node = currNode;
        return turned;

    }

    int cardPile;

    if(toCol->node != NULL){
        pileNode = toCol->node;
        while (pileNode->next != NULL){
            pileNode = pileNode->next;
        }
        cardPile = convertFrokLetter(pileNode->Card->num);
    }


    if(toCol->node != NULL && cardPile + 1 == cardFrom && currNode->Card->type == pileNode->Card->type){
        int turned = 1;

        if(firstCard){
            fromCol->node = NULL;
        }
        else{
            if(!prev->Card->is_visible){
                prev->Card->is_visible = true;
                turned = 2;
            }
            prev->next = NULL;
        }
        pileNode->next = currNode;
        return turned;
    }
    else{
        return 0;
    }




}

bool moveFromPileToC(column* col, int colStart, int colEnd){
    column* fromCol;
    column* toCol;

    fromCol = col;
    toCol = col;

    ListElement* currNode;
    ListElement* prev;
    ListElement* columnNode;

    for (int i = 0; i < colStart+6; ++i) {

        fromCol = fromCol->next;

    }

    if(fromCol->node == NULL){
        return false;
    }

    currNode = fromCol->node;

    bool firstCard = true;
    while (currNode->next != NULL){
        prev = currNode;
        currNode = currNode->next;
        firstCard = false;
    }

    for (int i = 0; i < colEnd-1; ++i) {

        toCol = toCol->next;

    }



    int cardFrom = convertFrokLetter(currNode->Card->num);

    if(toCol->node == NULL && cardFrom == 13){

        if(firstCard){
            fromCol->node = NULL;
        }
        else{
            prev->next = NULL;
        }
        toCol->node = currNode;
        return true;

    }

    if(toCol->node == NULL){
        return false;
    }

    columnNode = toCol->node;
    while (columnNode->next != NULL){
        columnNode = columnNode->next;
    }
    int columnNodeNumber = convertFrokLetter(columnNode->Card->num);

    if(columnNodeNumber == cardFrom +1 && columnNode->Card->type != currNode->Card->type){

        if(firstCard){
            fromCol->node = NULL;
        }
        else{
            prev->next = NULL;
        }
        columnNode->next = currNode;
        return true;

    } else{
        return false;
    }


}
