#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void printHelp(){
    printf(" ____________________________________________ \n");
    printf("|              Commands for Yukon            |\n");
    printf("|____________________________________________|\n");
    printf("|                                            |\n");
    printf("|  command: move {xx} to {Cx}                |\n");
    printf("|  example: move 2H to C3                    |\n");
    printf("|  moves a card and cards below to a column. |\n");
    printf("|  You can only move a single card at a time |\n");
    printf("|  if it is to the column for solved cards.  |\n");
    printf("|  In the example it is the 2 of Hearts      |\n");
    printf("|  that is moved to column 3.                |\n");
    printf("|                                            |\n");
    printf("|  command: start                            |\n");
    printf("|  example: start                            |\n");
    printf("|  Starts the game, sets up all the cards.   |\n");
    printf("|                                            |\n");
    printf("|  command: reset                            |\n");
    printf("|  example: reset                            |\n");
    printf("|  Resets the game, you cannot undo this.    |\n");
    printf("|                                            |\n");
    printf("|  command: end                              |\n");
    printf("|  example: end                              |\n");
    printf("|  Ends the game, program stops.             |\n");
    printf("|                                            |\n");
    printf("|____________________________________________|\n");
    printf("|                    Rules                   |\n");
    printf("|____________________________________________|\n");
    printf("|                                            |\n");
    printf("|  You have to move all cards into the       |\n");
    printf("|  solved column (C8)                        |\n");
    printf("|  You can only move the lowest card         |\n");
    printf("|  possible, from the start it's an Ace.     |\n");
    printf("|  You can only move the bottom card onto    |\n");
    printf("|  the solved piles                          |\n");
    printf("|  There are four piles, one for each color  |\n");
    printf("|  Hearts(H) Spades(S) Diamonds(D) Clubs(C)  |\n");
    printf("|                                            |\n");
    printf("|  You can free cards by moving the card     |\n");
    printf("|  above or multiple cards above.            |\n");
    printf("|  They can be moved to another pile (C1-C7) |\n");
    printf("|  but only if the number of the card        |\n");
    printf("|  that you are moving is one below the card |\n");
    printf("|  that you are moving it to.                |\n");
    printf("|  It also requires that the color is not    |\n");
    printf("|  the same as the card you are moving       |\n");
    printf("|  meant as they cannot both be spades or    |\n");
    printf("|  or both be hearts but if one of them is   |\n");
    printf("|  spades then the other one can be clubs    |\n");
    printf("|                                            |\n");
    printf("|  Moving a card with cards below it also    |\n");
    printf("|  moves all the cards below regardless of   |\n");
    printf("|  their number or color                     |\n");
    printf("|  If you move cards away from a card that   |\n");
    printf("|  is face down ([]) then that card is       |\n");
    printf("|  flipped and is now in play as well        |\n");
    printf("|  There are one of each card and there are  |\n");
    printf("|  no duplicates.                            |\n");
    printf("|                                            |\n");
    printf("|  To win, all cards must be flipped and     |\n");
    printf("|  moved to the solved column.               |\n");
    printf("|____________________________________________|\n");
}