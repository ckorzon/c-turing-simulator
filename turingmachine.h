#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include "card.h"
#include "deck.h"

typedef struct TuringMachine {
    int maxIterations;
    int cardIndex;
    int tapeIndex;
    int tapeLength;
    bool halted;
    bool *tape;
    deck *deck;
} turingmachine;

void initializeTuringMachine(turingmachine *tm, deck *deck, int tapeLength, int maxIterations);

void destroyTuringMachine(turingmachine *tm);

void runTuringMachine(turingmachine *tm);

void turingIterate(turingmachine *tm);

void followCardInstructions(turingmachine *tm, cardrow *operation);

card* getCurrentCard(turingmachine *tm);

void printTape(turingmachine *tm);

#endif // TURINGMACHINE_H