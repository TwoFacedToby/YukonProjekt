#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "deck.h"
#include <time.h>
#define DECK

#define MAX_LINE_LENGTH 3




deckNode* createDeckNode(char num, char type) {
    deckNode* newNode = (deckNode*)malloc(sizeof(deckNode));
    newNode->Card.num = num;
    newNode->Card.type = type;
    newNode->next = NULL;
    return newNode;
}

//Checks if file is valid
bool checkForSuitsAndNumber(deckNode* deck) {

    int card_count = 1;
    for (deckNode* node = deck->next; node != NULL; node = node->next) {
        card_count++;
    }

    if (card_count != 52) {
        printf("There are not 52 cards in file");
        return false;
    }

    int suit_counts[4] = {0};
    bool unique_cards[52] = {0};
    for (deckNode* node = deck; node != NULL; node = node->next) {
        char suit = node->Card.type;
        int card_index;
        switch (suit) {
            case 'C':
                suit_counts[0]++;
                card_index = 0;
                break;
            case 'D':
                suit_counts[1]++;
                card_index = 13;
                break;
            case 'H':
                suit_counts[2]++;
                card_index = 26;
                break;
            case 'S':
                suit_counts[3]++;
                card_index = 39;
                break;
            default:
                printf("Error: invalid suit %c\n", suit);
                return false;
        }

        int card_number;
        if (node->Card.num == 'A') {
            card_number = 1;
        } else if (node->Card.num == 'K') {
            card_number = 13;
        } else if (node->Card.num == 'Q') {
            card_number = 12;
        } else if (node->Card.num == 'J') {
            card_number = 11;
        } else if (node->Card.num == 'T') {
            card_number = 10;
        } else {
            card_number = node->Card.num - '0';
        }
        card_index += card_number - 1;

        if (unique_cards[card_index]) {
            printf("Error: duplicate card %c%c\n", suit, node->Card.num);
            return false;
        } else {
            unique_cards[card_index] = true;
        }
    }

    for (int j = 0; j < 4; j++) {
        if (suit_counts[j] != 13) {
            printf("Error: %d cards of suit %c\n", suit_counts[j], "CDHS"[j]);
            return false;
        }
    }


    return true;




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

    checkForSuitsAndNumber(head);

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

deckNode* splitter (deckNode* deck, int splitCard){

    deckNode* firstHalf;
    deckNode* secondHalf;
    deckNode* prev;
    deckNode* current;

    firstHalf = deck;
    secondHalf = deck;
    prev = firstHalf;

    secondHalf = secondHalf->next;

    if(splitCard == 0){
        int random_num;
        srand(time(NULL)); // seed the random number generator with current time

        random_num = rand() % 51 + 1; // generates a random number between 1 and 51

        printf("myRanom number: %d", random_num);

        splitCard = random_num;

    }




    for (int i = 1; i < splitCard; ++i) {
        prev = prev->next;

        if(secondHalf){
            secondHalf = secondHalf->next;
        }



    }
    printf("hej");
    if(prev){
        prev->next = NULL;
    }




     // Store the first node's address in firstNode

    current = firstHalf;
    deckNode* firstNode = current;
    firstHalf = firstHalf->next;

    while (firstHalf && secondHalf) {
        current->next = secondHalf;
        secondHalf = secondHalf->next;
        current = current->next;

        if (firstHalf) {
            current->next = firstHalf;
            firstHalf = firstHalf->next;
            current = current->next;
        }
    }

    if(firstHalf){
        current->next = firstHalf;
    }

    if(secondHalf){
        current->next = secondHalf;
    }

    return firstNode;

}


column* instantiate_yukon_board(deckNode* deck, bool showCards, bool visible){

    column *head = NULL, *prev = NULL;

    for (int col = 1; col <= 11; col++) {
        column* newColumn = (column*)malloc(sizeof(column));
        newColumn->column = col;
        newColumn->next = NULL;

        int cards_in_column;

        if(col < 8 && deck != NULL && !showCards){
            newColumn->node = create_list_element(&deck);

            if(col > 1){
                printf("Watch this");
                newColumn->node->Card->is_visible = false;
            }
            else{
                newColumn->node->Card->is_visible = true;
            }

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

        }else if(showCards && col < 8){

            newColumn->node = create_list_element(&deck);

            if(col < 4){
                cards_in_column = 8;
            }
            else{
                cards_in_column = 7;
            }

            ListElement* current_node = newColumn->node;
            current_node->Card->is_visible = (!visible) ? false : true;

            for (int i = 1; i < cards_in_column; ++i) {
                ListElement* newNode = create_list_element(&deck);
                newNode->Card->is_visible = (!visible) ? false : true;
                current_node->next = newNode;
                current_node = newNode;
            }




        } else{
            newColumn->node = NULL;
        }

        if (head == NULL) {
            head = newColumn;
        } else {
            prev->next = newColumn;
        }
        prev = newColumn;






    }

    return head;
}

void printer(column* col) {

    column *currentCol = col;
    column *firstCol = col;


    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");


    int j = 0;
    while (true) {

        currentCol = firstCol;
        bool allCardsNull = true;

        for (int i = 0; i < 8; i++) {

            if (i < 7) {

                ListElement *currentCard = currentCol->node;

                if(currentCol->node == NULL){
                    printf("\t");
                    currentCard = NULL;
                }else{
                    for (int k = 0; k < j; k++) {

                        if (currentCard->next != NULL) {
                            currentCard = currentCard->next;
                        } else {
                            printf("\t");
                            currentCard = NULL;
                            break;
                        }
                    }
                }




                if (currentCard != NULL) {
                    allCardsNull = false;
                    if (currentCard->Card->is_visible) {
                        printf("%c%c \t", currentCard->Card->num, currentCard->Card->type);
                    } else {
                        printf("%c%c \t", '[', ']');
                    }
                }

                currentCol = currentCol->next;
            } else {
                if (j == 0 || j == 2 || j == 4 || j == 6) {
                    int m = j / 2;
                    for (int q = 0; q < m; q++) {
                        currentCol = currentCol->next;
                    }
                    if (currentCol->node != NULL) {
                        ListElement* listElement = currentCol->node;
                        while (listElement->next != NULL){
                            listElement = listElement->next;
                        }

                        printf("\t %c%c ", listElement->Card->num, listElement->Card->type);
                        printf("\t %c%d", 'F', currentCol->column - 7);
                    } else {
                        printf(" \t %c%c \t %c%d", '[', ']', 'F', currentCol->column - 7);
                    }
                }
            }
        }

        printf("\n");

        if (allCardsNull && j > 6) {
            break;
        }

        j++;

    }


}

deckNode* loader(char inputArr[]){
    int length = strlen(inputArr);
    // Allocate memory for a new string, making sure to account for the
    // fact that the string starts at index 3
    char* newStr = (char*)malloc(sizeof(char) * (length - 2));
    // Copy the characters from inputArr starting at index 3 into the new string
    int i, j = 0;
    for (i = 3; i < length; i++) {
        newStr[j++] = inputArr[i];
    }
    newStr[j] = '\0';
    char* buffer = (char*)malloc(sizeof(char) * (strlen(newStr) + 7));
    // Copy "Files/" to the beginning of the buffer
    strcpy(buffer, "Files/");
    // Concatenate newStr to the end of the buffer
    strcat(buffer, newStr);
    // Create a new deckNode object and set its properties based on the new string
    deckNode* node = readDeckFromFile(buffer);
    // set node properties here based on newStr
    // ...
    // Free the memory allocated for the new string
    free(newStr);
    return node;

}
