#ifndef POLISH_H_
#define POLISH_H_

#include "./stack.h"
#include "./list.h"

/**
 * Converts infix polish notation to reverse polish notation.
 **/
struct node* rpn(struct node* ipn);

double evaluate(double x, struct node* lexemesRpn);

#endif    //POLISH_H_
