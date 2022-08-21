#ifndef STACK_H_
#define STACK_H_

#include "./list.h"

struct stack {
    struct node* top;
};

struct stack* init_stack();
void push_elem(struct stack *stack, struct lexeme* lex);
struct lexeme* pop_elem(struct stack *stack);
struct lexeme* peek_elem(struct stack *stack);
int isEmpty_stack(struct stack *stack);
void destroy_stack(struct stack *stack);

#endif    //STACK_H_