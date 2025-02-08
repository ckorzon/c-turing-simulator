#include <stdlib.h>
#include <stdbool.h>
#include "card.h"

// gcc card.c zz-test-cards.c -o cards-test.exe


void populateTestCardRows(card* cardA, card* cardB) {
    setCardRow(cardA, 0, 1, 1, 1);
    setCardRow(cardA, 1, 1, 0, 2);
    int cardBArray[6] = {1, 1, 0, 1, 1, 0};
    setCardRow(cardB, 0, cardBArray[0], cardBArray[1], cardBArray[2]);
    setCardRow(cardB, 1, cardBArray[3], cardBArray[4], cardBArray[5]);
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
    printCard(2, cardB);

    // Destroy cards
    destroyCard(cardA);
    destroyCard(cardB);
}