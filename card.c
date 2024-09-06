#include <stdio.h>
#include <stdbool.h>
#include "card.h"

void printCardRow(bool n, cardrow crdrow) {
    printf("|%d : %d %d %d|\n", n, crdrow.writeVal, crdrow.shiftRight, crdrow.nextCard);
}

void printCard(int crdNum, card * crd) {
    printf("===========\n");
    printf("|# Card%d #|\n", crdNum);
    printCardRow(0, crd->rows[0]);
    printCardRow(1, crd->rows[1]);
    printf("===========\n");
}