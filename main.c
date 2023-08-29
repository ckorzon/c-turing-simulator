#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_ITERATIONS = 1000;

typedef struct CardRow {
    bool writeVal;
    bool shiftRight;
    int nextCard;
} cardrow;

typedef struct Card {
    cardrow rows[2];
} card;

typedef struct TuringMachine {
    int currentCard;
    int tapeIndex;
    int numCards;
    int tapeLength;
    bool *tape;
    card *cards;
} turingmachine;

void constructTape(bool *tape, int tapeLength) {
    for (int i=0; i<tapeLength; i++) {
        tape[i] = 0;
    }
}

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

void printTape(turingmachine *tm) {
    for (int i=0; i<tm->tapeLength; i++) {
        printf("%d ", tm->tape[i]);
    }
}

void showExampleCards() {
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
}

card* getCurrentCard(turingmachine *tm) {
    return &(tm->cards[tm->currentCard]);
}

void initTuringMachine(turingmachine *tm, card *cards, int tapeLength) {
    bool tape[tapeLength];
    constructTape(tape, tapeLength);
    tm->tapeLength = tapeLength;
    tm->tape = tape;
    tm->numCards = sizeof(*cards) / sizeof(card);
    tm->cards = cards;
    tm->currentCard = 0;
    tm->tapeIndex = tapeLength / 2;
}

void doTuringStep(turingmachine *tm, cardrow *operation) {
    // Write the next value per card row instructions
    tm->tape[tm->tapeIndex] = operation->writeVal;
    printf("> Wrote %d at position %d. Moving %d (0=left, 1=right), next card = %d\n", operation->writeVal, tm->tapeIndex, operation->shiftRight, operation->nextCard);
    // Move the tape index left or right (branchlessly)
    tm->tapeIndex = tm->tapeIndex + (2 * (operation->shiftRight) - 1);
    // Determine if we halt, or move to next card
    tm->currentCard = operation->nextCard;
}

void turingIterate(turingmachine *tm) {
    card *currentCard = getCurrentCard(tm);
    bool readVal = tm->tape[tm->tapeIndex];
    // *Note: We're heavily taking advantage of C's bool type equivalence to 0/1
    // true => 1, false => 0
    doTuringStep(tm, &(currentCard->rows[readVal]));
}

void runTuringMachine(turingmachine *tm) {
    int iterations = 1;
    while (tm->currentCard > -1) {
        turingIterate(tm);
        if (tm->currentCard < 0) {
            printf("Success! Turing machine halted at iteration %d.\n", iterations);
            return;
        } 
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            printf("WARNING: Too many turing iterations, Aborting!\n");
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    // Simulate a Binary turing machine with N states
    // Components = tape, cards/states
    // Card Syntax:
    // 0 : 110 (if read 0: write 1, move right, halt)
    // 1 : 101 (if read 1: write 1, move left, go to card 1)

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

    //Placeholder single card until dynamic card loading is implemented
    cardrow zeroRow = { 1, 1, -1 };
    cardrow oneRow = { 0, 0, 0 };
    card firstcard = { { zeroRow, oneRow } };

    // Declare cards
    card cards[1];
    cards[0] = firstcard;

    // Construct the turing machine
    turingmachine tm;
    initTuringMachine(&tm, cards, tapeLength);

    // For now, just print the tape
    runTuringMachine(&tm);

    // TODO: Take a list of numbers from user and convert to set of cards.
    // TODO: OR read cards from a file
    
    return 0;
}