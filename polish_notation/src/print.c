/*Copyright 2022 Tendyris Fredacha Vidamogo*/

#include <stdio.h>

#include "./print.h"

void printGraph(int* ordinates, int h, int w) {
    for (int i = h / 2; i > h / 2 - h; i--) {
        for (int j = 0; j < w; j++) {
            if (ordinates != NULL && -i == ordinates[j]) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
