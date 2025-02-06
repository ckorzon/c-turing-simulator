#include <stdio.h>
#include "card.h"
#include "deck.h"
#include "cardsfile.h"

int main(int argc, char* argv[]) {
    deck* testDeck = readCardFile("ExampleCards.txt");

    printf("Deck Size: %d\n", testDeck->size);
    printf("Deck Capacity: %d\n", testDeck->capacity);

    for (int i = 0; i < testDeck->size; i++) {
        printCard(i, &testDeck->cards[i]);
    }

    destroyDeck(testDeck);
}