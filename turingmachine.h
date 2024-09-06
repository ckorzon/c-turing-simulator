#include "card.h"

typedef struct TuringMachine {
    int maxIterations;
    int cardIndex;
    int tapeIndex;
    int numCards;
    int tapeLength;
    bool halted;
    bool *tape;
    card *cards;
} turingmachine;

void initializeTuringMachine(turingmachine *tm, card *cards, int tapeLength, int maxIterations);

void dismantleTuringMachine(turingmachine *tm);

void runTuringMachine(turingmachine *tm);

void turingIterate(turingmachine *tm);

void followCardInstructions(turingmachine *tm, cardrow *operation);

card* getCurrentCard(turingmachine *tm);

void printTape(turingmachine *tm);