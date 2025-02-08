#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "turingmachine.h"

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

void printTape(turingmachine *tm) {
    for (int i=0; i < tm->tapeLength; i++) {
        printf("%d ", tm->tape[i]);
    }
}

card* getCurrentCard(turingmachine *tm) {
    return &(tm->deck->cards[tm->cardIndex]);
}

void initializeTuringMachine(turingmachine *tm, deck *deck, int tapeLength, int maxIterations) {
    // The tape is an array of 0's and 1's, represented here as booleans.
    tm->tapeLength = tapeLength;
    tm->tape = constructTape(tm->tapeLength);
    tm->maxIterations = maxIterations;
    tm->deck = deck;
    tm->halted = false;
    tm->cardIndex = 0;
    tm->tapeIndex = tapeLength / 2;
}

void destroyTuringMachine(turingmachine *tm) {
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
        exit(1);
    }
    // Collect the current card, throw error if it can't be retrieved
    card *currentCard = getCurrentCard(tm);
    if (currentCard == NULL) {
        printf("ERROR: Card index %d is out of bounds.\n", tm->cardIndex);
        exit(1);
    }
    // * Note: We're heavily taking advantage of C's bool type equivalence to 0/1
    // * true => 1, false => 0
    // Collect the current card instruction row, throw error if it can't be retrieved
    cardrow instructionRow = currentCard->rows[readVal];
    if (&instructionRow == NULL) {
        printf("ERROR: Card Row %d is empty for card %d.\n", readVal, tm->cardIndex);
        exit(1);
    }
    // Perform the operation per the card's instructions
    followCardInstructions(tm, &instructionRow);
}

void runTuringMachine(turingmachine *tm) {
    printf("### RUNNING TURING MACHINE ###\n");
    int iterations = 1;
    while (!tm->halted) {
        turingIterate(tm);
        // Check if our card told us to halt
        if (tm->cardIndex < 0) {
            printf("SUCCESS: Turing machine halted at iteration %d.\n", iterations);
            tm->halted = true;
        }
        // Check if we've run out of tape
        if (tm->tapeIndex >= tm->tapeLength || tm->tapeIndex < 0) {
            printf("ABORT: Next position %d is not on the tape, cannot continue.\n", tm->tapeIndex);
            tm->halted = true;
        }
        // Check if we've hit maximum iterations
        iterations++;
        if (iterations > tm->maxIterations) {
            printf("ABORT: Too many turing iterations.\n");
            tm->halted = true;
        }
    }
}