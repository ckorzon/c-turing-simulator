#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cardsfile.h"

deck* readCardFile(char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Failed to read cards from file.\n");
        exit(1);
    }

    // Initialize Deck
    deck *deck = constructDeck(1);

    // Create slots for card values
    int cardValsArray[6];
    int currentSlot = 0;

    // Parse file into an array of turing machine cards
    while (!feof(file)) {

        // Character Codes:
        // 32 --> SPACE
        // 48 --> 0
        // 49 --> 1
        // 50 --> 2
        // 10 --> LF
        // -1 --> End of file?

        // Fill in the cardVals array. Once full, create a card with the values

        int characterInt = fgetc(file);

        // Filter down to integer chars only
        if (characterInt < 48 || characterInt > 57) {
            continue;
        }

        // Integer value for the current card slot is the character value offset by 48 based on ASCII definitions
        int slotVal = characterInt - 48;

        // If the next slot is not a card number (end of a row) require 0 or 1 value
        // Special Case: If the current slot is 3rd or 6th, we're looking at a card number and allow any positive integer (including multiple digits).
        if (currentSlot == 2 || currentSlot == 5) {
            while (!feof(file)) {
                characterInt = fgetc(file);
                if (characterInt <= 47 || characterInt >= 58) {
                    break;
                }
                slotVal = (slotVal * 10) + (characterInt - 48);
            }
        }

        // All slots besides 3rd and 6th must have a value of 0 or 1. Slots 3 & 6 are card numbers, and can be any positive integer.
        if (currentSlot != 2 && currentSlot != 5 && slotVal != 0 && slotVal != 1) {
            printf("Invalid card value read!\n");
            printf("Value = '%d', Card # %d Position %d.\n", slotVal, deck->size-1, currentSlot);
            exit(1);
        }

        // Base Case - put character val as int into array, offset by 48 based on Ascii chart.
        cardValsArray[currentSlot] = slotVal;
        currentSlot += 1;

        // Once we reach 6 slots, construct a card and reset slot to 0
        if (currentSlot == 6) {
            // Initialize Card
            card* c = constructCard();
            
            // Populate card rows
            setCardRow(c, 0, (bool) cardValsArray[0], (bool) cardValsArray[1], cardValsArray[2]);
            setCardRow(c, 1, (bool) cardValsArray[3], (bool) cardValsArray[4], cardValsArray[5]);

            // Add card to set
            addCard(deck, c);

            // Reset current card slot
            currentSlot = 0;
        }
        
    }
    fclose(file);
    return deck;    
}