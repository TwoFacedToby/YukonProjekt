#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "reader.h"

char input[20];

int main() {
    deckNode* deck = readDeckFromFile("Files/deck.txt");





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

    // Test print
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
    }

    return 0;
}


