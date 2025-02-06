#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "turingmachine.h"
#include "deck.h"
#include "cardsfile.h"

const int MAX_ITERATIONS = 1000;
const int DEFAULT_TAPE_LENGTH = 500;


int main(int argc, char* argv[]) {
    // Simulate a Binary turing machine with N states
    // Components = tape, cards/states
    // Card Syntax:
    // 0 : 110 (if read 0: write 1, move right, halt)
    // 1 : 101 (if read 1: write 1, move left, go to card 1)

    int tapeLength;
    deck* turingDeck;
    switch(argc) {
        case 1:
            printf("ERROR: Must provide path to cards file.\n");
            return 1;
        case 2:
            // program.exe [cards_file]
            turingDeck = readCardFile(argv[1]);
            break;
        case 3 :
            // program.exe [cards_file] [tape_length]
            turingDeck = readCardFile(argv[1]);
            tapeLength = atoi(argv[2]);
            break;            
        default:
            printf("ERROR: Invalid number of arguments.\n");
            return 1;
    }
    printf("Using tape with length: %d \n", tapeLength);
    printf("Using Deck with %d cards.\n", turingDeck->size);

    printCard(0, &turingDeck->cards[0]);
    printCard(1, &turingDeck->cards[1]);


    // // Construct the turing machine
    // turingmachine tm;
    // initializeTuringMachine(&tm, turingDeck, tapeLength, MAX_ITERATIONS);

    // // Run the turing machine
    // runTuringMachine(&tm);

    // Deconstruct to free memory
    // destroyTuringMachine(&tm);
    destroyDeck(turingDeck);

    return 0;
}