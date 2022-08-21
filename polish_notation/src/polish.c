/*Copyright 2022 Tendyris Fredacha Vidamogo*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./polish.h"

struct node* rpn(struct node* ipn) {
    if (ipn == NULL) {
        return NULL;
    }
    struct node* result = NULL;
    struct stack* stack = init_stack();

    struct node* p = ipn;
    while (p != NULL) {
        if (p->lex->type == 'f' || p->lex->type == 'u') {
            // Если токен — функция, то поместить его в стек.
            push_elem(stack, p->lex);
        } else if (p->lex->type == 'o') {
            // Если токен — оператор op1, то:
            struct lexeme* op1 = p->lex;

// Пока присутствует на вершине стека токен оператор op2, чей приоритет
    // выше или равен приоритету op1, и при равенстве приоритетов op1
        // является левоассоциативным:
            // Переложить op2 из стека в выходную очередь;
            while (isEmpty_stack(stack) == 0) {
                struct lexeme* op2 = peek_elem(stack);
                if ((op2->type == 'o' || op2->type == 'u')
                        && (op1->c == '+' || op1->c == '-'
                        || op2->c == '*' || op2->c == '/'
                        || op2->type == 'u')) {
                    pop_elem(stack);
                    result = add_elem_to_tail(result, op2);
                } else {
                    break;
                }
            }

            // Положить op1 в стек
            push_elem(stack, op1);

        } else if (p->lex->type == '(') {
            // Если токен — открывающая скобка, то положить его в стек.
            push_elem(stack, p->lex);

        } else if (p->lex->type == ')') {
            // Если токен — закрывающая скобка:
            // Пока токен на вершине стека не открывающая скобка
            // Переложить оператор из стека в выходную очередь.
            while (isEmpty_stack(stack) == 0) {
                struct lexeme* op2 = peek_elem(stack);
                if (op2->type != '(') {
                    pop_elem(stack);
                    result = add_elem_to_tail(result, op2);
                } else {
// Выкинуть открывающую скобку из стека, но не добавлять в очередь вывода.
                    pop_elem(stack);
                    break;
                }
            }

// Если токен на вершине стека — функция, переложить её в выходную очередь.
            struct lexeme* op2 = peek_elem(stack);
            if (op2 != NULL && op2->type == 'f') {
                pop_elem(stack);
                result = add_elem_to_tail(result, op2);
            }
        } else {
            // Если токен — число, то добавить его в очередь вывода.
            result = add_elem_to_tail(result, p->lex);
        }

        p = p->next;
    }

    // Если больше не осталось токенов на входе:
    // Пока есть токены операторы в стеке:
    // Переложить оператор из стека в выходную очередь.
    while (isEmpty_stack(stack) == 0) {
        struct lexeme* op2 = peek_elem(stack);
        pop_elem(stack);
        result = add_elem_to_tail(result, op2);
    }

    destroy_stack(stack);
    return result;
}

double evaluate(double x, struct node* lexemesRpn) {
    struct stack* stack = init_stack();

    struct node* garbage = NULL;

    struct node* p = lexemesRpn;
    while (p != NULL) {
        if (p->lex->type == 'v' || p->lex->type == 'x') {
            push_elem(stack, p->lex);
        } else if (p->lex->type == 'o') {
            struct lexeme* op2 = pop_elem(stack);
            double v2 = op2->type == 'x' ? x : op2->v;

            struct lexeme* op1 = pop_elem(stack);
            double v1 = op1->type == 'x' ? x : op1->v;

            double res;
            if (p->lex->c == '+') {
                res = v1 + v2;
            } else if (p->lex->c == '-') {
                res = v1 - v2;
            } else if (p->lex->c == '*') {
                res = v1 * v2;
            } else {
                res = v1 / v2;
            }

            struct lexeme* resLex = malloc(sizeof(struct lexeme));
            resLex->type = 'v';
            resLex->v = res;
            garbage = add_elem_to_tail(garbage, resLex);
            push_elem(stack, resLex);

        } else if (p->lex->type == 'u') {
            struct lexeme* op1 = pop_elem(stack);
            double v1 = op1->type == 'x' ? x : op1->v;

            double res;
            if (p->lex->c == '-') {
                res = -v1;
            } else {
                res = v1;
            }

            struct lexeme* resLex = malloc(sizeof(struct lexeme));
            resLex->type = 'v';
            resLex->v = res;
            garbage = add_elem_to_tail(garbage, resLex);
            push_elem(stack, resLex);

        } else if (p->lex->type == 'f') {
            struct lexeme* op1 = pop_elem(stack);
            double v1 = op1->type == 'x' ? x : op1->v;

            double res;
            if (strcmp(p->lex->s, "sin") == 0) {
                res = sin(v1);
            } else if (strcmp(p->lex->s, "cos") == 0) {
                res = cos(v1);
            } else if (strcmp(p->lex->s, "tan") == 0) {
                res = tan(v1);
            } else if (strcmp(p->lex->s, "ctg") == 0) {
                res = 1.0 / tan(v1);
            } else if (strcmp(p->lex->s, "sqrt") == 0) {
                res = sqrt(v1);
            } else {
                res = log(v1);
            }

            struct lexeme* resLex = malloc(sizeof(struct lexeme));
            resLex->type = 'v';
            resLex->v = res;
            garbage = add_elem_to_tail(garbage, resLex);
            push_elem(stack, resLex);

        } else {
            // throw new IllegalStateException();
        }


        p = p->next;
    }

    struct lexeme* lex = pop_elem(stack);
    double v = lex->type == 'x' ? x : lex->v;

    // tOdO assert stack is empty

    // cleanup
    struct node* pc = garbage;
    while (pc != NULL) {
        free(pc->lex);
        pc = pc->next;
    }
    destroy_list(garbage);
    destroy_stack(stack);

    return v;
}
