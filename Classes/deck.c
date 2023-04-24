#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "deck.h"
#define DECK

#define MAX_LINE_LENGTH 3




deckNode* createDeckNode(char num, char type) {
    deckNode* newNode = (deckNode*)malloc(sizeof(deckNode));
    newNode->Card.num = num;
    newNode->Card.type = type;
    newNode->next = NULL;
    return newNode;
}

deckNode* readDeckFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    deckNode* head = NULL;
    deckNode* tail = NULL;
    char line[3];

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) >= 2) {
            char num = line[0];
            char type = line[1];

            deckNode* newNode = createDeckNode(num, type);

            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }



    fclose(file);
    return head;
}


/*
int addToList(){

}
int removeFromList(){

}
struct ListElement * getCards(){

}
 */

ListElement* create_list_element(deckNode** current) {
    ListElement* newNode = (ListElement*)malloc(sizeof(ListElement));
    newNode->Card = &(*current)->Card;
    newNode->next = NULL;
    *current = (*current)->next;
    return newNode;
}




column* instantiate_yukon_board(deckNode* deck){

    column *head = NULL, *prev = NULL;

    for (int col = 1; col <= 7; col++) {
        column* newColumn = (column*)malloc(sizeof(column));
        newColumn->column = col;
        newColumn->node = create_list_element(&deck);
        newColumn->next = NULL;

        if(col > 1){
            newColumn->node->Card->is_visible = false;
        }

        if (head == NULL) {
            head = newColumn;
        } else {
            prev->next = newColumn;
        }
        prev = newColumn;

        int cards_in_column = 0;

        if(col == 1){
            cards_in_column = 1;
        }else{
            cards_in_column = 4 + col;
        }

        ListElement* current_node = newColumn->node;

        for (int i = 1; i < cards_in_column; i++) {
            ListElement* newNode = create_list_element(&deck);
            newNode->Card->is_visible = (i < -1 + col) ? false : true;
            current_node->next = newNode;
            current_node = newNode;
        }
    }
    return head;
}

void printer(column* col){

    column* currentCol = col;
    column* firstCol = col;


    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");
    for (int j = 0; j < 11; j++) {




        currentCol = firstCol;






        for(int i = 0; i < 7; i++){

            ListElement* currentCard = currentCol->node;

            for (int k = 0; k < j; k++) {


                if(currentCard->next != NULL) {
                    currentCard = currentCard->next;
                }
                else{
                    printf("\t");
                    currentCard = NULL;
                    break;
                }
            }

            if(currentCard != NULL){
                if(currentCard->Card->is_visible){
                    printf("%c%c \t", currentCard->Card->num, currentCard->Card->type);
                } else{
                    printf("%c%c \t",'[',']');
                }
            }

            currentCol = currentCol->next;
        }
        printf("\n");
        
    }

}


void print_yukon_board(ColumnStartNode *column_start_head) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    bool cards_remaining = true;

    while (cards_remaining) {
        cards_remaining = false;
        ColumnStartNode *current_column_node = column_start_head;

        while (current_column_node != NULL) {
            ListElement *current = current_column_node->col_start->node;

            if (current != NULL) {
                card *c = current->Card;
                printf("%c%c\t", c->num, c->type);
                current_column_node->col_start->node = current->next;
                cards_remaining = true;
            } else {
                printf("\t");
            }

            current_column_node = current_column_node->next;
        }
        printf("\n");
    }
}


