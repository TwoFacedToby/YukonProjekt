//
// Created by kk199 on 30/04/2023.
//



#include <mbstring.h>
#include <stdio.h>
#include "deck.h"
#include <string.h>



void save_deck_to_file(deckNode* head, char* filename) {
    char file_path[100];
    sprintf(file_path, "Files/%s", filename);

    FILE* fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Error: unable to open file.\n");
        return;
    }

    deckNode* current = head;
    while (current != NULL) {
        fprintf(fp, "%c%c\n", current->Card.num, current->Card.type);
        current = current->next;
    }

    fclose(fp);
}
