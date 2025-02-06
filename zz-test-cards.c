#include <stdlib.h>
#include <stdbool.h>
#include "card.h"


void populateTestCardRows(card* cardA, card* cardB) {
    setCardRow(cardA, 0, 1, 1, 1);
    setCardRow(cardA, 1, 1, 0, 2);
    setCardRow(cardB, 0, 1, 1, 0);
    setCardRow(cardB, 1, 1, 1, 0);
}


int main(int argc, char* argv[]) {
    // Test Card functionality

    // Construct cards
    card* cardA = constructCard();
    card* cardB = constructCard();

    // Populate card rows
    populateTestCardRows(cardA, cardB);

    // Check card values
    printCard(1, cardA);
    printCard(1, cardB);

    // Destroy cards
    destroyCard(cardA);
    destroyCard(cardB);
}