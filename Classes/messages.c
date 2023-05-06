//
// Created by kk199 on 06/05/2023.
//


#include <stdlib.h>
#include <string.h>


char* messageHandler(char* message, char* str){

    message = (char*) malloc((strlen(str) + 1) * sizeof(char));

    strcpy(message, str);

    return message;

}

void freeItUp(char** message) {
    free(*message);
    *message = NULL;
}
