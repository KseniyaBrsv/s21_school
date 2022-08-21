/*Copyright 2022 Tendyris Fredacha Vidamogo*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lexer.h"

char* scanFormula() {
    char formula[MAX_INPUT];

    fgets(formula, sizeof(formula), stdin);

    char* s = malloc(strlen(formula) * sizeof(char));

    // copy string and remove trailing '\n'
    unsigned int i = 0;
    for (; i < strlen(formula) - 1; i++) {
        s[i] = formula[i];
    }
    s[i] = '\0';

    return s;
}

/**
 * converts unary + and - to special lexemes
 */
void processUnary(struct node* lexemes) {
    struct lexeme* prevLexeme = NULL;
    struct node* p = lexemes;
    while (p != NULL) {
// Если предыдущая лексема оператор или откр.скобка либо предыдущей лексемы нет,
// а текущая лексема - или +, то текущая лексема унарная
        if (prevLexeme == NULL
                || prevLexeme->type == 'o'
                || prevLexeme->type == 'u'
                || prevLexeme->type == '(') {
            if (p->lex->c == '-' || p->lex->c == '+') {
                p->lex->type = 'u';
            }
        }

        prevLexeme = p->lex;
        p = p->next;
    }
}

struct node* parseLexemes(char* in, int* parseExceptionIndex) {
    *parseExceptionIndex = -1;
    struct node* lexemes = NULL;

    int bytesNow;
    int bytesRead = 0;

    double num;
    char buf[MAX_INPUT];

    int loop = 1;
    while (loop) {
        int f;
// scanning sequence is important: first spaces, then signs, then numbers
        f = sscanf(in + bytesRead, "%[ ]%n", buf, &bytesNow);
        if (f == EOF) {
            loop = 0;
        } else if (f == 1) {
            bytesRead += bytesNow;
        } else {
            f = sscanf(in + bytesRead, "%1[+-*/()]%n", buf, &bytesNow);
            if (f == EOF) {
                loop = 0;
            } else if (f == 1) {
                bytesRead += bytesNow;

                struct lexeme* lex = malloc(sizeof(struct lexeme));
                char c = buf[0];
                if (c == '(') {
                    lex->type = '(';
                } else if (c == ')') {
                    lex->type = ')';
                } else {
                    lex->type = 'o';
                    lex->c = c;
                }
                lex->s = NULL;   // for further free() control
                lexemes = add_elem_to_tail(lexemes, lex);

            } else {
                f = sscanf(in + bytesRead, "%lf%n", &num, &bytesNow);
                if (f == EOF) {
                    loop = 0;
                } else if (f == 1) {
                    bytesRead += bytesNow;

                    struct lexeme* lex = malloc(sizeof(struct lexeme));
                    lex->type = 'v';
                    lex->v = num;
                    lex->s = NULL;  // for further free() control
                    lexemes = add_elem_to_tail(lexemes, lex);

                } else {
                    f = sscanf(in + bytesRead, "%[sincotagqrlx]%n",
                    buf, &bytesNow);
                    if (f == EOF) {
                        loop = 0;
                    } else if (f == 1) {
                        bytesRead += bytesNow;

                        if (strcmp(buf, "sin") == 0
                                || strcmp(buf, "cos") == 0
                                || strcmp(buf, "tan") == 0
                                || strcmp(buf, "ctg") == 0
                                || strcmp(buf, "sqrt") == 0
                                || strcmp(buf, "ln") == 0) {
                            struct lexeme* lex = malloc(sizeof(struct lexeme));
                            lex->type = 'f';
                            lex->s = malloc(strlen(buf) * sizeof(char) + 1);
                            strcpy(lex->s, buf);
                            lexemes = add_elem_to_tail(lexemes, lex);
                        } else if (strcmp(buf, "x") == 0) {
                            struct lexeme* lex = malloc(sizeof(struct lexeme));
                            lex->type = 'x';
                            lex->s = NULL;  // for further free() control
                            lexemes = add_elem_to_tail(lexemes, lex);
                        } else {
                            // parse exception
                            *parseExceptionIndex = bytesRead - strlen(buf);
                            loop = 0;
                        }
                    } else {
                        *parseExceptionIndex = bytesRead;
                        loop = 0;
                    }
                }
            }
        }
    }

    if (lexemes != NULL) {
        processUnary(lexemes);
    }

    return lexemes;
}
