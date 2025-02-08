#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

deck* constructDeck(int initialCapacity) {

    printf("Constructing deck...\n");

    // Allocate memory for the deck itself
    deck* newDeck = malloc(sizeof(deck));
    if (initialCapacity < 0) {
        printf("Invalid Deck initial capacity! Value must be greater than 0.\n");
        return NULL;
    }

    // Allocate memory for the cards
    newDeck->capacity = initialCapacity;
    newDeck->cards = malloc(initialCapacity * sizeof(card*));

    newDeck->size = 0;
    return newDeck;
}

void addCard(deck* deck, card* newCard) {

    printf("Adding card to deck...\n");

    // Calculate new deck length
    int newLength = deck->size + 1;
    
    // Update deck capacity if necessary
    if (newLength > deck->capacity) {
        expandDeckCapacity(deck, 2);
    }

    // Add card to deck and update size
    deck->cards[newLength-1] = newCard;
    deck->size = newLength;
}

void expandDeckCapacity(deck* deck, int capacityFactor) {

    printf("Expanding deck capacity...\n");
    deck->capacity = deck->capacity * capacityFactor;
    card** newCardsList = (card**) realloc(deck->cards, deck->capacity * sizeof(card*));
    printf("Deck capacity expanded to %d.\n", deck->capacity);

    if (newCardsList == NULL) {
        // Memory allocation failed, abort mission.
        printf("Failed to resize Cards array! Exiting program.\n");
        free(deck);
        exit(1);
    }

    deck->cards = newCardsList;
}

void destroyDeck(deck* deck) {
    printf("Releasing deck from memory...\n");
    free(deck->cards);
    free(deck);
}
