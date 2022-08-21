/*Copyright 2022 Tendyris Fredacha Vidamogo*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./list.h"
#include "./lexer.h"
#include "./polish.h"
#include "./print.h"

#define PI_X4 12.566370
#define H 25
#define W 80

int main() {
    char* formula = scanFormula();

    int e = -1;
    struct node* lexemes = parseLexemes(formula, &e);

    if (e != -1) {
        printf("Parse error at input index: %d\n", e);

    } else if (lexemes == NULL) {
        printGraph(NULL, H, W);

    } else {
        struct node* lexemesRpn = rpn(lexemes);

        int ordinates[W];
        for (int j = 0; j < W; j++) {
            double jdb = j;
            double x = jdb / W * PI_X4;
            double y = evaluate(x, lexemesRpn);
            int yint = round(y * (H / 2));
            ordinates[j] = yint;
        }

        printGraph(ordinates, H, W);

        // cleanup
        struct node* pc = lexemes;
        while (pc != NULL) {
            if (pc->lex->s != NULL) {
                free(pc->lex->s);
            }
            free(pc->lex);
            pc = pc->next;
        }
        destroy_list(lexemesRpn);
        destroy_list(lexemes);
    }

    free(formula);
}
