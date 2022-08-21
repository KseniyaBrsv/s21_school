#ifndef LEXER_H_
#define LEXER_H_

#include "./list.h"

#define MAX_INPUT 50

char* scanFormula();

/**
 * @param parseExceptionIndex -1 if OK, otherwise invalid symbol index
 **/ 
struct node* parseLexemes(char* in, int* parseExceptionIndex);

#endif    //LEXER_H_
