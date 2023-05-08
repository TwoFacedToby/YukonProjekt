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
        srand(time(NULL));

        random_num = rand() % 51 + 1;

        splitCard = random_num;

    }




    for (int i = 1; i < splitCard; ++i) {
        prev = prev->next;

        if(secondHalf){
            secondHalf = secondHalf->next;
        }
    }

    if(prev){
        prev->next = NULL;
    }


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


column* instantiate_yukon_board(deckNode* deck, bool showCards, bool visible) {

    column *head = NULL, *prev = NULL;
    column* columns[11] = {NULL};

    for (int col = 1; col <= 11; col++) {
        column* newColumn = (column*)malloc(sizeof(column));
        newColumn->column = col;
        newColumn->next = NULL;
        newColumn->node = NULL;

        if (head == NULL) {
            head = newColumn;
        } else {
            prev->next = newColumn;
        }
        prev = newColumn;
        columns[col - 1] = newColumn;
    }

    int current_col = 0;
    int cards_in_column[7] = {1, 6, 7, 8, 9, 10, 11};

    if (showCards) {
        for (int i = 0; i < 7; i++) {
            cards_in_column[i] = (i < 3) ? 8 : 7;
        }
    }

    int assigned_cards[7] = {0};
    while (deck != NULL && current_col < 7) {
        if (assigned_cards[current_col] < cards_in_column[current_col]) {
            ListElement* newNode = create_list_element(&deck);

            if (columns[current_col]->node == NULL) {
                columns[current_col]->node = newNode;
                newNode->Card->is_visible = (current_col == 0) ? true : false;
            } else {
                ListElement* current_node = columns[current_col]->node;
                int intervals = 1;
                while (current_node->next != NULL) {
                    current_node = current_node->next;
                    intervals++;
                }
                current_node->next = newNode;
                if(intervals < current_col){
                    newNode->Card->is_visible = false;
                }
                else{
                    newNode->Card->is_visible = true;
                }
            }
            assigned_cards[current_col]++;
            current_col = (current_col + 1) % 7;
        } else {
            current_col = (current_col + 1) % 7;
        }
    }

    if (showCards) {
        for (int col = 0; col < 7; col++) {
            ListElement* current_node = columns[col]->node;
            while (current_node != NULL) {
                current_node->Card->is_visible = visible;
                current_node = current_node->next;
            }
        }
    }

    return head;
}

void printer(column* col) {

    column *currentCol;
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

    char* newStr = (char*)malloc(sizeof(char) * (length - 2));

    int i, j = 0;
    for (i = 3; i < length; i++) {
        newStr[j++] = inputArr[i];
    }
    newStr[j] = '\0';
    char* buffer = (char*)malloc(sizeof(char) * (strlen(newStr) + 7));

    strcpy(buffer, "Files/");

    strcat(buffer, newStr);

    deckNode* node = readDeckFromFile(buffer);


    free(newStr);
    return node;

}

int length(deckNode* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

deckNode* randomShuffle(deckNode* deck){
    if (deck == NULL) {
        return NULL;
    }

    deckNode* unshuffledPile = deck;
    deckNode* shuffledPile = NULL;

    srand(time(NULL));

    for (int i = 1; i <= 52; i++) {
        int random_num = rand() % i + 1;

        deckNode* curr = unshuffledPile;

        unshuffledPile = unshuffledPile->next;

        if (shuffledPile == NULL) {
            shuffledPile = curr;
            curr->next = NULL;
        } else if (random_num == 1) {
            curr->next = shuffledPile;
            shuffledPile = curr;

        } else if(random_num == i) {
            deckNode* t = shuffledPile;
            for (int j = 2; j < i; ++j) {
                t = t->next;
            }

            t->next = curr;
            curr->next = NULL;

        }else {
                deckNode* temp = shuffledPile;
                deckNode* prevShuffled = NULL;

                for (int j = 2; j <= random_num; j++) {
                    prevShuffled = temp;
                    temp = temp->next;
                }

                prevShuffled->next = curr;
                curr->next = temp;
            }
        }
    return shuffledPile;
}





