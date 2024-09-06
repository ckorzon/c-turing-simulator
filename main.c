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
    int cardIndex;
    int tapeIndex;
    int numCards;
    int tapeLength;
    bool *tape;
    card *cards;
} turingmachine;

bool* constructTape(int tapeLength) {
    bool * tape = (bool *) malloc(tapeLength * sizeof(bool));
    if (tape == NULL) {
        printf("Memory allocation failed for Turing Machine tape!\n");
        exit(1);
    }
    for (int i=0; i<tapeLength; i++) {
        tape[i] = 0;
    }
    return tape;
}

void printCardRow(bool n, cardrow crdrow) {
    printf("|%d : %d %d %d|\n", n, crdrow.writeVal, crdrow.shiftRight, crdrow.nextCard);
}

void printCard(int crdNum, card * crd) {
    printf("===========\n");
    printf("|# Card%d #|\n", crdNum);
    printCardRow(0, crd->rows[0]);
    printCardRow(1, crd->rows[1]);
    printf("===========\n");
}

void printTape(turingmachine *tm) {
    for (int i=0; i < tm->tapeLength; i++) {
        printf("%d ", tm->tape[i]);
    }
}

card* getCurrentCard(turingmachine *tm) {
    return &(tm->cards[tm->cardIndex]);
}

void initializeTuringMachine(turingmachine *tm, card *cards, int tapeLength) {
    // The tape is an array of 0's and 1's, represented here as booleans.
    tm->tapeLength = tapeLength;
    tm->tape = constructTape(tm->tapeLength);
    tm->numCards = sizeof(*cards) / sizeof(card);
    tm->cards = cards;
    tm->cardIndex = 0;
    tm->tapeIndex = tapeLength / 2;
}

void dismantleTuringMachine(turingmachine *tm) {
    free(tm->tape);
}

void followCardInstructions(turingmachine *tm, cardrow *operation) {
    // Write the next value per card row instructions
    tm->tape[tm->tapeIndex] = operation->writeVal;
    int nextPosition = tm->tapeIndex + (2 * (operation->shiftRight) - 1);
    printf("> Wrote %d at position %d. Next position = %d, next card = %d.\n", operation->writeVal, tm->tapeIndex, nextPosition, operation->nextCard);
    // Move the tape index left or right (branchlessly)
    tm->tapeIndex = nextPosition;
    // Find next card index. Offset by -1 since 0 represents halt and 1 represents first card (index 0).
    tm->cardIndex = operation->nextCard - 1;
}

void turingIterate(turingmachine *tm) {
    bool readVal = tm->tape[tm->tapeIndex];
    printf("> Read value: %d.\n", readVal);
    if (!(readVal == 0 || readVal == 1)) {
        printf("INVALID VALUE READ FROM TAPE: %d.\n", readVal);
        EXIT_FAILURE;
    }
    card *currentCard = getCurrentCard(tm);
    // *Note: We're heavily taking advantage of C's bool type equivalence to 0/1
    // true => 1, false => 0
    followCardInstructions(tm, &(currentCard->rows[readVal]));
}

void runTuringMachine(turingmachine *tm) {
    printf("### RUNNING TURING MACHINE ###\n");
    int iterations = 1;
    bool run = true;
    while (run) {
        turingIterate(tm);
        // Check if our card told us to halt
        if (tm->cardIndex < 0) {
            printf("SUCCESS: Turing machine halted at iteration %d.\n", iterations);
            run = false;
        }
        // Check if we've run out of tape
        if (tm->tapeIndex >= tm->tapeLength || tm->tapeIndex < 0) {
            printf("ABORT: Next position %d is not on the tape, cannot continue.\n", tm->tapeIndex);
            run = false;
        }
        // Check if we've hit maximum iterations
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            printf("ABORT: Too many turing iterations.\n");
            run = false;
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

    // Declare cards
    cardrow zeroRow = { 1, 0, 2 };
    cardrow oneRow = { 0, 0, 2 };
    card firstCard = { { zeroRow, oneRow } };

    cardrow zeroRowB = { 1, 1, 1 };
    cardrow oneRowB = { 0, 1, 0 };
    card secondCard = { { zeroRowB, oneRowB } };

    card cards[] = { firstCard, secondCard };

    // Construct the turing machine
    turingmachine tm;
    initializeTuringMachine(&tm, cards, tapeLength);

    // Run the turing machine
    runTuringMachine(&tm);

    // Deconstruct to free memory
    dismantleTuringMachine(&tm);

    // TODO: Take a list of numbers from user and convert to set of cards.
    // TODO: OR read cards from a file
    
    return 0;
}