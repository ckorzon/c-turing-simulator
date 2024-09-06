#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "turingmachine.h"

const int MAX_ITERATIONS = 1000;

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
    initializeTuringMachine(&tm, cards, tapeLength, MAX_ITERATIONS);

    // Run the turing machine
    runTuringMachine(&tm);

    // Deconstruct to free memory
    dismantleTuringMachine(&tm);

    // TODO: Take a list of numbers from user and convert to set of cards.
    // TODO: OR read cards from a file
    
    return 0;
}