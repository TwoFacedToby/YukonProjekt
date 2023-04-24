#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "reader.h"

char lastInput[20]; //Creates a char array that has a max length of 20.

void clearInput(char *input, int maxLength){
    for(int i = 0; i < maxLength; i++){
        input[i] == ' ';
    }
}


void readInput(char *input, int maxLength) {
    clearInput(input, maxLength);
    fgets(input, maxLength, stdin); //Take Input
    input[strcspn(input, "\n")] = '\0'; // Remove newline character
}

void getInput(char *input){
    readInput(input, 20);
}

bool isNumber(char c){
    if(c == 'A'||c == '2'||c == '3'||c == '4'||c == '5'||c == '6'||c == '7'||c == '8'||c == '9'||c == 'T'||c == 'J'||c == 'Q'||c == 'K'){
        return true;
    }
    else return false;
}
bool isType(char c){
    if(c == 'C'||c == 'D'||c == 'H'||c == 'S'){
        return true;
    }
    else return false;
}
bool isPileNumber(char c){
    if(c == '1'|| c == '2'|| c == '3'|| c == '4'){
        return true;
    }
    else return false;
}
bool isColumnNumber(char c){
    if(c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'|| c == '7'){
        return true;
    }
    else return false;
}
bool last(char c){
    if(c == ' ') return true;
    if(c == NULL) return true;
    else return false;
}

/**Finds the function of the input, if there is an error or something else.
 * The Method returns 0 if there is an error in the formatting or if it isn't a command.
 * It also tests the possible ways of writing the move command, to make sure that the tests of future methods is only testing whether or not the move is possible.
 * @param input char array of the input
 * @return 0 = Error, 1 = P, 2 = Q, 3 = QQ, 4 = SD, 5 = SI, 6 = SR, 7 = SW, 8 = S, 9 = LD, 10 = L, 11 = R, 12 = U, 13 = Move C to C, 14 = Move C to F, 15 = Move Cc to C, 16 = Move Cc to F, 17 = Move F to C
 */

int getFunctionOfInput(char *input){
    if(input[0] == 'P'){
        //P
        //Player with current set of cards
        if(last(input[1])) return 1;
        else return 0;
    }
    else if(input[0] == 'Q'){
        if(input[1] == 'Q'){
            //QQ
            //Quit Program
            if(last(input[2])) return 3;
            else return 0;
        }
        else{
            //Q
            //Quit Current
            if(last(input[1])) return 2;
            else return 0;
        }
    }
    else if(input[0] == 'S'){
        if(input[1] == 'D'){
            //SD
            //Save Deck
            if(last(input[2])) return 4;
            else return 0;
        }
        else if(input[1] == 'I'){
            //SI
            //Shuffle by Split Deck
            if(last(input[2])) return 5;
            else return 0;
        }
        else if(input[1] == 'R'){
            //SR
            //Shuffle Deck at Random
            if(last(input[2])) return 6;
            else return 0;
        }
        else if(input[1] == 'W'){
            //SW
            //Show Deck
            if(last(input[2])) return 7;
            else return 0;
        }
        else{
            //S
            //Save Game (Extra Assignment)
            if(last(input[1])) return 8;
            else return 0;
        }
    }
    else if(input[0] == 'L'){
        if(input[1] == 'D'){
            //LD
            //Load Deck
            if(last(input[2])) return 9;
            else return 0;
        }
        else{
            //Load game (Extra Assignment)
            if(last(input[1])) return 10;
            else return 0;
        }
    }
    else if(input[0] == 'R'){
        //R
        //Redo
        if(last(input[1])) return 11;
        else return 0;
    }
    else if(input[0] == 'U'){
        //U
        //Undo
        if(last(input[1])) return 12;
        else return 0;
    } else if(input[0] == 'C'){
        if(isColumnNumber(input[1])){
            if(input[2] == '-' && input[3] == '>'){
                if(input[4] == 'C'){
                    if(isColumnNumber(input[5])){
                        if(last(input[6])) return 13;
                        else return 0;
                    }
                }
                else if(input[4] == 'F'){
                    if(isPileNumber(input[5])){
                        if(last(input[6])) return 14;
                        else return 0;
                    }
                }
            }
            else{
                if(input[2] == ':'){
                    if(isNumber(input[3])){
                        if(isType(input[4])){
                            if(input[5] == '-' && input[6] == '>'){
                                if(input[7] == 'C'){
                                    if(isColumnNumber(input[8])){
                                        if(last(input[9])) return 15;
                                        else return 0;
                                    }
                                }
                                else if(input[7] == 'F'){
                                    if(isPileNumber(input[8])){
                                        if(last(input[9])) return 16;
                                        else return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
    else if(input[0] == 'F'){
        if(isPileNumber(input[1])){
            if(input[2] == '-' && input[3] == '>'){
                if(input[4] == 'C'){
                    if(isColumnNumber(input[5])){
                        if(last(input[6])) return 17;
                        else return 0;
                    }
                }
            }
        }
        return 0;
    }
    else return 0;
}
