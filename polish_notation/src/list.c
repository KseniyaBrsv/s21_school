/*Copyright 2022 Tendyris Fredacha Vidamogo*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "./list.h"

struct node* init_list(struct lexeme* lex) {
    struct node* list = malloc(sizeof(struct node));
    if (list != NULL) {
        list[0].lex = lex;
        list[0].next = NULL;
    }
    return list;
}

struct node* add_elem(struct node* elem, struct lexeme* lex) {
    if (elem != NULL) {
        struct node* afterNext = elem->next;
        struct node* newNode = init_list(lex);
        elem->next = newNode;
        newNode->next = afterNext;
        return newNode;
    } else {
        return NULL;
    }
}

struct node* remove_elem(struct node* elem, struct node* root) {
    if (elem == NULL || root == NULL) {
        // the root has not changed
        return root;
    } else {
        // find the previous for the removable node
        struct node* prev = NULL;
        struct node* p = root;
        while (p != NULL && prev == NULL) {
            if (p->next == elem) {
                prev = p;
            } else {
                p = p->next;
            }
        }
        if (prev == NULL) {
            // maybe remove the first node
            if (root == elem) {
                struct node* newRoot = root->next;
                free(elem);
                return newRoot;
            } else {
                // elem not found in the list
                return root;
            }
        } else {
            prev->next = elem->next;
            free(elem);
            // the root has not changed
            return root;
        }
    }
}

void destroy_list(struct node* root) {
    struct node* p = root;
    while (p != NULL) {
        struct node* currentNode = p;
        p = p->next;
        free(currentNode);
    }
}

struct node* add_elem_to_tail(struct node* root, struct lexeme* lex) {
    if (root == NULL) {
        root = init_list(lex);
    } else {
        struct node* p = root;
        while (p->next != NULL) {
            p = p->next;
        }
        add_elem(p, lex);
    }
    return root;
}

void printLexeme(struct lexeme* lex) {
    if (lex->type == 'f') {
        printf("%s", lex->s);
    } else if (lex->type == 'u') {
        if (lex->c == '-') {
            printf("M");
        } else {
            printf("P");
        }
    } else if (lex->type == 'o') {
        printf("%c", lex->c);
    } else if (lex->type == '(') {
        printf("(");
    } else if (lex->type == ')') {
        printf(")");
    } else if (lex->type == 'v') {
        printf("%lf", lex->v);
    } else if (lex->type == 'x') {
        printf("x");
    }
}
