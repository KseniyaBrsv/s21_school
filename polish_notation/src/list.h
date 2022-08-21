#ifndef LIST_H_
#define LIST_H_

struct lexeme {
    /**
     * f: function
     * u: unary - or +
     * o: operation + - * /
     * (: literal (
     * ): literal )
     * v: value
     * x: literal x
     **/ 
    char type;
    char c;
    char* s;
    double v;
};

void printLexeme(struct lexeme* lex);

struct node {
    struct lexeme* lex;
    struct node* next;
};

struct node* init_list(struct lexeme* lex);
/**
 * @param elem the node after which to insert
 * @return the new (inserted) node
 **/
struct node* add_elem(struct node* elem, struct lexeme* lex);
/**
 * Frees memory of the removed node
 * @return the new root
 **/
struct node* remove_elem(struct node* elem, struct node* root);
void destroy_list(struct node* root);

/**
 * @param root nullable
 * @return the new root
 **/
struct node* add_elem_to_tail(struct node* root, struct lexeme* lex);

#endif    //LIST_H_
