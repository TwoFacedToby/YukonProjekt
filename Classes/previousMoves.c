//
// Created by kk199 on 05/05/2023.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "previousMoves.h"
#include "deck.h"

moves* createMove(int start, char num, char type, int end, bool wasVis) {

    moves* moves1 = (moves*)malloc(sizeof(moves));

    moves1->startCol = start;
    moves1->cardNum = num;
    moves1->cardType = type;
    moves1->endColumn = end;
    moves1->was_visible = wasVis;
    moves1->next = NULL;

    return moves1;
}


moves* instantiateMovesList(){

    moves* playerMoves = (moves*)malloc(sizeof(moves));

    playerMoves->startCol = -1;
    playerMoves->cardType = 0;
    playerMoves->cardNum = 0;
    playerMoves->was_visible = false;
    playerMoves->endColumn = -1;
    playerMoves->next = NULL;

    return playerMoves;


}

bool isInitialState(moves* move) {
    return move->startCol == -1 && move->cardType == 0 && move->cardNum == 0
           && move->was_visible == false && move->endColumn == -1 && move->next == NULL;
}


moves* addPreviousMoves(moves* playerMoves, int colStart, char cardNum, char cardType, int colEnd, bool wasVisible){

    moves* temp = playerMoves;


    if(playerMoves->startCol == NULL){
        playerMoves->startCol = colStart;
        if(cardNum != NULL){
            playerMoves->cardNum = cardNum;
        }
        else{
            playerMoves->cardNum = (char)NULL;
        }
        if(cardType != NULL){
            playerMoves->cardType = cardType;
        }
        else{
            playerMoves->cardType = (char) NULL;
        }
        playerMoves->endColumn = colEnd;
        playerMoves->was_visible = wasVisible;
        return playerMoves;
    }


    moves* currMove = createMove(colStart, cardNum,cardType,  colEnd, wasVisible);

    while (temp->next != NULL){
        temp = temp->next;
    }

    temp->next = currMove;

    return playerMoves;

}

moves* addRedoToUndo(moves* lastMoves, column* col, moves* undoMove){

    if(undoMove->was_visible){
        column * temp = col;
        ListElement* element;


        for (int i = 0; i < undoMove->startCol; ++i) {
            temp = temp->next;
        }
        element = temp->node;

        while (element->next->Card->type != undoMove->cardType && element->next->Card->num != undoMove->cardNum){
            element = element->next;
        }

        element->Card->is_visible = true;

    }

    addPreviousMoves(lastMoves, undoMove->startCol, undoMove->cardNum, undoMove->cardType, undoMove->endColumn, false);



    undoMove = NULL;
    free(undoMove);



}


moves* undoLastMove(moves* lastMoves, column* col, moves* undoMove){

    if(isInitialState(lastMoves)){
        return 0;
    }

    moves* temp = lastMoves;
    moves* prevTemp = lastMoves;

    column* first = col;
    column * second = col;
    ListElement* node1;
    ListElement* node2;
    ListElement* prev = NULL;

    while(temp->next != NULL){
        prevTemp = temp;
        temp = temp->next;

    }

    int startColumn = temp->startCol;
    int endColumn = temp->endColumn;

    for (int i = 0; i < endColumn-1; ++i) {

        first = first->next;
    }

    node1 = first->node;

    for (int i = 0; i < startColumn-1; ++i) {
        second = second->next;
    }

    node2 = second->node;

    if(temp->cardType != NULL){
        char cardNum = temp->cardNum;
        char cardType = temp->cardType;

        while(node1->Card->type != cardType || node1->Card->num != cardNum){
            prev = node1;
            node1 = node1->next;
        }

    }
    else{
        while (node1->next != NULL){
            prev = node1;
            node1 = node1->next;
        }

    }


    if(node2 != NULL){
        while(node2->next != NULL){
            node2 = node2->next;
        }

        if(temp->was_visible){
            node2->Card->is_visible = false;
        }

        node2->next = node1;
    }else{
        second->node = node1;
    }


    if(prev != NULL){
        prev->next = NULL;
    }
    else{
        first->node = NULL;
    }

    if(undoMove != NULL){
        undoMove = NULL;
        free(undoMove);
    }

    undoMove = (moves*)malloc(sizeof(moves));

    undoMove->startCol = temp->endColumn;
    undoMove->endColumn = temp->startCol;
    undoMove->was_visible = temp->was_visible;
    undoMove->cardNum = temp->cardNum;
    undoMove->cardType = temp->cardType;
    undoMove->next = NULL;



    prevTemp->next = NULL;




    free(temp);

    return undoMove;

}











