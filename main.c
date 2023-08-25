#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CardRow {
    bool writeVal;
    bool shiftRight;
    int nextCard;
} cardrow;

typedef struct Card {
    cardrow rows[2];
} card;

void printCardRow(bool n, cardrow crdrow) {
    printf("|%d : %d %d %d|\n", n, crdrow.writeVal, crdrow.shiftRight, crdrow.nextCard);
}

void printCard(int crdNum, card crd) {
    printf("===========\n");
    printf("|# Card%d #|\n", crdNum);
    printCardRow(0, crd.rows[0]);
    printCardRow(1, crd.rows[1]);
    printf("===========\n");

}

int main(int argc, char* argv[]) {
    // Simulate a Binary turing machine with N states
    // Components = tape, cards/states, 

    int tapeLength;
    switch(argc) {
        case 1 :
            tapeLength = 500;
            break;
        case 2 :
            tapeLength = atoi(argv[1]);
            printf("Using tape with length: %d \n", tapeLength);
            break;
        default:
            printf("ERROR: Invalid number of arguments.\n");
            return 1;
    }

    bool tape[tapeLength];

    // Card Syntax:
    // 0 : 110 (if read 0: write 1, move right, halt)
    // 1 : 101 (if read 1: write 1, move left, go to card 1)

    // TODO: Take a list of numbers from user and convert to set of cards.
    // TODO: OR read cards from a file

    // Example Cards:
    cardrow zeroRow = { 1, 1, 2 };
    cardrow oneRow = { 0, 0, 0 };
    card firstcard = { { zeroRow, oneRow } };

    cardrow zeroRowTwo = { 1, 0, 1 };
    cardrow oneRowTwo = { 0, 1, 2 };
    card secondcard = { { zeroRowTwo, oneRowTwo } };

    card cards[2] = { firstcard, secondcard };

    printf("<> CARDS: <>\n");
    printCard(0, cards[0]);
    printCard(1, cards[1]);
    
    return 0;
}