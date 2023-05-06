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
#include "help.h"

char input[20];

int main() {
    deckNode* startPhaseDeck = NULL;
    deckNode* deck = NULL;// = readDeckFromFile("Files/deck.txt");
    column* currentGame = NULL;
    moves* previousMoves = NULL;
    moves* redoMove = NULL;
    bool gameRunning = false;
    bool deckLoadingPhase = false;


    char* messages = NULL;
    messages = messageHandler(messages, "Something");

    column* col = instantiate_yukon_board(startPhaseDeck, false, false);
    //col = instantiate_yukon_board(deck);



    do {
        printer(col);



        getInput(input, messages);

        freeItUp(&messages);


        int columnFrom, columnTo, pileTo, pileFrom, splitNumber;
        char cardNum, cardSuit;
        char* substr = input + 3;




        switch (getFunctionOfInput(input)) {
            case 0:
                //Error in formatting or unknown command
                messages = messageHandler(messages, "Error: Unknown command");
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
                if(deck == NULL){
                    messages = messageHandler(messages, "Error: You need to load a deck before you start the game");
                }
                else if(gameRunning) {
                    messages = messageHandler(messages, "Error: Game is already running");
                }
                else{
                    messages = messageHandler(messages, "OK");
                    gameRunning = true;
                    previousMoves = instantiateMovesList();
                }







                break;
            case 2:
                //Q



                currentGame = col;
                col = instantiate_yukon_board(startPhaseDeck, false, false);
                if(!gameRunning && !deckLoadingPhase){
                    messages = messageHandler(messages, "Error: there is no game running");
                } else{
                    messages = messageHandler(messages, "OK");
                    gameRunning = false;
                    deckLoadingPhase = false;
                }


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
                if(gameRunning){
                    messages = messageHandler(messages, "Error: You can not split the deck when the game is running");
                    break;
                }

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
                if(gameRunning){
                    messages = messageHandler(messages, "Error: You can not shuffle the deck when the game is running");
                    break;
                }

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
                if(gameRunning){
                    messages = messageHandler(messages, "Error: You can now show cards when a game is running");
                    break;
                }

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
                if(gameRunning){
                    messages = messageHandler(messages, "Error: You need to quit the game before loading a new deck");
                    break;
                }

                currentGame = NULL;

                if(strcmp(input, "LD") == 0){
                    strcpy(input, input);
                    strcat(input, " deck.txt");
                }

                deck = loader(input);
                if(deck != NULL){
                    col = instantiate_yukon_board(deck, true, false);
                    messages = messageHandler(messages, "OK");
                    deckLoadingPhase = true;
                }else{
                    messages = messageHandler(messages, "Error: No file found with that name");
                }


                break;
            case 10:
                //L
                //Load Game (extra assignment)

                break;
            case 11:
                //R
                //Redo (extra assignment)
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to do a redo");
                    break;
                }

                if(redoMove != NULL){

                    addRedoToUndo(previousMoves, col, redoMove);
                    redoMove = undoLastMove(previousMoves, col, redoMove);
                    messages = messageHandler(messages, "OK");
                    free(redoMove);
                    redoMove = NULL;


                } else{
                    messages = messageHandler(messages, "Error: Redo must be done the turn after undo");
                }


                break;
            case 12:
                //U
                //Undo (extra assignment)
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to an unoo");
                    break;
                }

                redoMove = undoLastMove(previousMoves, col, redoMove);

                if(redoMove != NULL){
                    messages = messageHandler(messages, "OK");
                }else{
                    messages = messageHandler(messages, "Error: no more undoes");
                }


                break;
            case 13:
                //Move top card from column to another column
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to move a card");
                    break;
                }


                columnFrom = atoi(&input[1]);
                columnTo = atoi(&input[5]);

                int moveOrNot = legalMove(col, columnFrom, 'F', 'F', columnTo);
                if(moveOrNot > 0){
                    bool wasVis = false;
                    if(moveOrNot == 2){
                           wasVis = true;
                    }
                    previousMoves = addPreviousMoves(previousMoves, columnFrom, (char)NULL, (char)NULL, columnTo, wasVis);

                    messages = messageHandler(messages, "OK");

                }else{
                    messages = messageHandler(messages, "Error: Not a legal move");
                }


                break;
            case 14:
                //Move top card from column to a finished pile
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to move a card");
                    break;
                }

                columnFrom = atoi(&input[1]);
                pileTo = atoi(&input[5]);
                int legal = legalPileMove(col, columnFrom, pileTo);

                if(legal > 0){
                    bool wasVis = false;
                    if(legal == 2){
                        wasVis = true;
                    }
                    previousMoves = addPreviousMoves(previousMoves, columnFrom, (char)NULL, (char)NULL, pileTo+7, wasVis);
                    messages = messageHandler(messages, "OK");

                }else{
                    messages = messageHandler(messages, "Error: Not a legal move");
                }

                break;
            case 15:
                //Move a specific card from a column to another column
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to move a card");
                    break;
                }

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

                    messages = messageHandler(messages, "OK");

                }else{
                    messages = messageHandler(messages, "Error: Not a legal move");
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
                if(!gameRunning){
                    messages = messageHandler(messages, "Error: You need to start again to move a card");
                    break;
                }

                pileFrom = atoi(&input[1]);
                columnTo = atoi(&input[5]);
                bool my = moveFromPileToC(col, pileFrom, columnTo);
                if(my){
                    previousMoves = addPreviousMoves(previousMoves, pileFrom+7, (char)NULL, (char)NULL,columnTo, false);
                    messages = messageHandler(messages, "OK");

                }else{
                    messages = messageHandler(messages, "Error: Not a legal move");
                }
                break;
            case 18:
                //Help for the player
                printHelp();

                break;

        }
    } while (true);

}






