#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "reader.h"
#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[20];

int main() {
    deckNode* startPhaseDeck = NULL;
    deckNode* deck = NULL;// = readDeckFromFile("Files/deck.txt");
    column* currentGame = NULL;

    column* col = instantiate_yukon_board(startPhaseDeck, false, false);
    //col = instantiate_yukon_board(deck);



    do {
        printer(col);

        getInput(input);
        printf("%s%s", input, "\n");
        printf("%d%s", getFunctionOfInput(input), "\n\n\n");
        int columnFrom, columnTo, pileTo, pileFrom;
        char cardNum, cardSuit;


        switch (getFunctionOfInput(input)) {
            case 0:
                //Error in formatting or unknown command
                break;
            case 1:
                //P
                //Start Game with Current set of Cards
                if(currentGame != NULL){
                    printf("hej");
                    col = currentGame;
                }
                else{
                    col = instantiate_yukon_board(deck, false, false);
                }


                break;
            case 2:
                //Q
                currentGame = col;
                col = instantiate_yukon_board(startPhaseDeck, false, false);

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

                break;
            case 5:
                //SI
                //Shuffle deck as split, can have follow up number

                break;
            case 6:
                //SR
                //Shuffle deck at random

                break;
            case 7:
                //SW
                //Show screen, show the full current deck on the screen, not as a game.

                col = instantiate_yukon_board(deck, true, true);

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
                printf("her");

                break;
            case 10:
                //L
                //Load Game (extra assignment)

                break;
            case 11:
                //R
                //Redo (extra assignment)

                break;
            case 12:
                //U
                //Undo (extra assignment)

                break;
            case 13:
                //Move top card from column to another column
                columnFrom = atoi(&input[1]);
                columnTo = atoi(&input[5]);

                legalMove(col, columnFrom, 'F', 'F', columnTo);


                break;
            case 14:
                //Move top card from column to a finished pile

                columnFrom = atoi(&input[1]);
                pileTo = atoi(&input[5]);
                legalPileMove(col, columnFrom, pileTo);
                break;
            case 15:
                //Move a specific card from a column to another column


                columnFrom = atoi(&input[1]);
                columnTo = atoi(&input[8]);
                cardNum = input[3];
                cardSuit = input[4];
                bool min =legalMove(col, columnFrom, cardSuit, cardNum, columnTo);
                printf("her er min bool %d", min);
                printf("\n");



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
                moveFromPileToC(col, pileFrom, columnTo);


                break;
        }
    } while (true);


    //Game do while loop
    //Print Layout
    //Ask for input
    getInput(input);
    printf("%s%s", input, "\n");
    printf("%d%s", getFunctionOfInput(input), "\n\n\n");
    int columnFrom, columnTo, pileTo, pileFrom;
    char cardNum, cardSuit;

    switch (getFunctionOfInput(input)) {
        case 0:
            //Error in formatting or unknown command
            break;
        case 1:
            //P
            //Start Game with Current set of Cards

            break;
        case 2:
            //Q
            //Quit current game, still hold on to current deck

            break;
        case 3:
            //QQ
            //Close program

            break;
        case 4:
            //SD
            //Save Deck, saves the deck to a file, can include file name.

            break;
        case 5:
            //SI
            //Shuffle deck as split, can have follow up number

            break;
        case 6:
            //SR
            //Shuffle deck at random

            break;
        case 7:
            //SW
            //Show screen, show the full current deck on the screen, not as a game.

            break;
        case 8:
            //S
            //Save Game (extra assignment)

            break;
        case 9:
            //LD
            //Load Deck. Can contain filename.

            break;
        case 10:
            //L
            //Load Game (extra assignment)

            break;
        case 11:
            //R
            //Redo (extra assignment)

            break;
        case 12:
            //U
            //Undo (extra assignment)

            break;
        case 13:
            //Move top card from column to another column
            columnFrom = atoi(&input[1]);
            columnTo = atoi(&input[5]);


            break;
        case 14:
            //Move top card from column to a finished pile
            columnFrom = atoi(&input[1]);
            pileTo = atoi(&input[5]);

            break;
        case 15:
            //Move a specific card from a column to another column
            columnFrom = atoi(&input[1]);
            columnTo = atoi(&input[8]);
            cardNum = input[3];
            cardSuit = input[4];

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

            break;
    }

    /*// Test print
    deckNode* current = deck;
    while (current != NULL) {
        printf("%c%c\n", current->Card.num, current->Card.type);
        current = current->next;
    }

    // Free the allocated memory and set the pointers to NULL
    while (deck != NULL) {
        deckNode* temp = deck;
        deck = deck->next;
        free(temp);
        temp = NULL;
    }*/

    return 0;
}


