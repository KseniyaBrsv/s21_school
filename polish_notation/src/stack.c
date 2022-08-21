/*Copyright 2022 Tendyris Fredacha Vidamogo*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./stack.h"

struct stack* init_stack() {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->top = init_list(NULL);
    return stack;
}

void push_elem(struct stack *stack, struct lexeme* lex) {
    add_elem(stack->top, lex);
}

struct lexeme* pop_elem(struct stack *stack) {
    struct node* elemNode = stack->top->next;
    if (elemNode == NULL) {
        return NULL;
    } else {
        struct lexeme* lex = elemNode->lex;
        stack->top = remove_elem(elemNode, stack->top);
        return lex;
    }
}

struct lexeme* peek_elem(struct stack *stack) {
    struct node* elemNode = stack->top->next;
    if (elemNode == NULL) {
        return NULL;
    } else {
        return elemNode->lex;
    }
}

int isEmpty_stack(struct stack *stack) {
    if (stack->top->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void destroy_stack(struct stack *stack) {
    if (stack != NULL) {
        if (stack->top != NULL) {
            destroy_list(stack->top);
        }
        free(stack);
    }
}
