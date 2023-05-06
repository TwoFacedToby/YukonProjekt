#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "reader.h"
#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileHandler.h"
#include "previousMoves.h"
#include "messages.h"

char input[20];

int main() {
    deckNode* startPhaseDeck = NULL;
    deckNode* deck = NULL;// = readDeckFromFile("Files/deck.txt");
    column* currentGame = NULL;
    moves* previousMoves = NULL;
    moves* redoMove = NULL;
    bool gameRunning = false;


    char* messages = NULL;
    messages = messageHandler(messages, "Something");

    column* col = instantiate_yukon_board(startPhaseDeck, false, false);
    //col = instantiate_yukon_board(deck);



    do {
        printer(col);



        getInput(input, messages);

        freeItUp(&messages);

        printf("%s%s", input, "\n");
        printf("%d%s", getFunctionOfInput(input), "\n\n\n");
        int columnFrom, columnTo, pileTo, pileFrom, splitNumber;
        char cardNum, cardSuit;
        char* substr = input + 3;




        switch (getFunctionOfInput(input)) {
            case 0:
                //Error in formatting or unknown command
                break;
            case 1:
                //P
                //Start Game with Current set of Cards


                if(currentGame != NULL){
                    col = currentGame;
                }
                else{
                    col = instantiate_yukon_board(deck, false, false);
                }
                gameRunning = true;
                previousMoves = instantiateMovesList();

                if(deck == NULL){
                    messages = messageHandler(messages, "Error: You need to load a deck before you start the game");
                }else{
                    messages = messageHandler(messages, "OK");
                }


                break;
            case 2:
                //Q



                currentGame = col;
                col = instantiate_yukon_board(startPhaseDeck, false, false);
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: there is no game running");
                } else{
                    messages = messageHandler(messages, "OK");
                }

                gameRunning = false;
                //Quit current game, still hold on to current deck

                break;
            case 3:
                //QQ
                printf("Closing program");
                return 0;
                //Close program

                break;

            case 4:
                //SD
                //Save Deck, saves the deck to a file, can include file name.
                if(deck != NULL){
                    save_deck_to_file(deck, substr);
                    messages = messageHandler(messages, "OK");
                }else{
                    messages = messageHandler(messages, "Error: You must have a deck to save it");
                }




                break;
            case 5:
                //SL
                splitNumber = atoi(&input[3]);
                if(deck != NULL){
                    deck = splitter(deck, splitNumber);
                    //Cahnge visible to true for testing
                    col = instantiate_yukon_board(deck, true, true);
                    //Shuffle deck as split, can have follow up number
                    messages = messageHandler(messages, "OK");
                }else{
                    messages = messageHandler(messages, "Error: You must have a deck to split it");
                }


                break;
            case 6:
                //SR
                //Shuffle deck at random
                if(deck != NULL){
                    deck = randomShuffle(deck);
                    col = instantiate_yukon_board(deck, true, true);
                    messages = messageHandler(messages, "OK");
                }else{
                    messages = messageHandler(messages, "Error: You must have a deck to shuffle it");
                }

                break;
            case 7:
                //SW
                //Show screen, show the full current deck on the screen, not as a game.
                if(deck != NULL){
                    col = instantiate_yukon_board(deck, true, true);
                    messages = messageHandler(messages, "OK");
                }else{
                    messages= messageHandler(messages, "Error: You must load a deck to show it");
                }


                break;
            case 8:
                //S
                //Save Game (extra assignment)

                break;

            case 9:
                //LD
                //Load Deck. Can contain filename.

                currentGame = NULL;
                deck = loader(input);
                col = instantiate_yukon_board(deck, true, false);

                break;
            case 10:
                //L
                //Load Game (extra assignment)

                break;
            case 11:
                //R
                //Redo (extra assignment)
                if(redoMove != NULL){

                    addRedoToUndo(previousMoves, col, redoMove);
                    redoMove = undoLastMove(previousMoves, col, redoMove);

                }

                break;
            case 12:
                //U
                //Undo (extra assignment)
                redoMove = undoLastMove(previousMoves, col, redoMove);


                break;
            case 13:
                //Move top card from column to another column
                columnFrom = atoi(&input[1]);
                columnTo = atoi(&input[5]);

                int moveOrNot = legalMove(col, columnFrom, 'F', 'F', columnTo);
                if(moveOrNot > 0){
                    bool wasVis = false;
                    if(moveOrNot == 2){
                           wasVis = true;
                    }
                    previousMoves = addPreviousMoves(previousMoves, columnFrom, (char)NULL, (char)NULL, columnTo, wasVis);

                }


                break;
            case 14:
                //Move top card from column to a finished pile

                columnFrom = atoi(&input[1]);
                pileTo = atoi(&input[5]);
                int legal = legalPileMove(col, columnFrom, pileTo);

                if(legal > 0){
                    bool wasVis = false;
                    if(legal == 2){
                        wasVis = true;
                    }
                    previousMoves = addPreviousMoves(previousMoves, columnFrom, (char)NULL, (char)NULL, pileTo+7, wasVis);
                }

                break;
            case 15:
                //Move a specific card from a column to another column


                columnFrom = atoi(&input[1]);
                columnTo = atoi(&input[8]);
                cardNum = input[3];
                cardSuit = input[4];
                int min = legalMove(col, columnFrom, cardSuit, cardNum, columnTo);
                printf("her er min bool %d", min);
                printf("\n");

                if(min> 0){
                    bool wasVis = false;
                    if(min == 2){
                        wasVis = true;
                    }
                    previousMoves = addPreviousMoves(previousMoves, columnFrom, cardNum, cardSuit, columnTo, wasVis);

                }



                break;
            case 16:
                //Move a specific card from a column to a finished pile
                columnFrom = atoi(&input[1]);
                pileTo = atoi(&input[8]);
                cardNum = input[3];
                cardSuit = input[4];

                break;
            case 17:
                //Move from top of a finished pile to another column
                pileFrom = atoi(&input[1]);
                columnTo = atoi(&input[5]);
                bool my = moveFromPileToC(col, pileFrom, columnTo);
                if(my){
                    previousMoves = addPreviousMoves(previousMoves, pileFrom+7, (char)NULL, (char)NULL,columnTo, false);
                }

                break;
        }
    } while (true);

}






