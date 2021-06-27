#include "symbol_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define THRESHOLD 0.75
#define BLOCK_SIZE 64

unsigned int current_scope;

typedef struct node_t {
    struct node_t *next;
    unsigned long long prehash;
    variable *var;
    unsigned int scope;
} node_t;

node_t **hash_table;

unsigned int size;
unsigned int num_blocks;

void insert_function(var_type return_type, char *name, int qty, ...) {
    va_list types;
    function *function = calloc(1, sizeof(function));
    function->name = name;
    function->param_qty = qty;
    function->return_type = return_type;
    if (qty > 0) {
        va_start(types, qty);
        param_type_node * param = calloc(1, sizeof(param_type_node));
        param->type = va_arg(types, var_type);
        param_type_node *aux = param;       
        for (int i = 1; i < qty; i++) {
            aux->next = calloc(1, sizeof(param_type_node));
            aux->next->type = va_arg(types, var_type);
            aux = aux -> next;
        }
        function->first = param;
        va_end(types);
    }
    insert((variable *)function);
}

void insert_lib_functions() {
    insert_function(tRECTANGLE, "rect_init", 4, tINT, tINT, tINT, tINT);
    insert_function(tCIRCLE, "circ_init", 3, tINT, tINT, tINT);
    insert_function(tLINE, "line_init", 4, tINT, tINT, tINT, tINT);
    insert_function(tDOT, "dot_init", 2, tINT, tINT);
    insert_function(tFIGURE, "join", 2 , tFIGURE, tFIGURE);
    insert_function(tVOID, "draw", 1, tFIGURE);
    insert_function(tVOID, "move", 2, tINT, tINT);
    insert_function(tVOID, "DESTROY", 1, tFIGURE);
    insert_function(tVOID, "set_interval", 2, tINT, tFUNCTION); // estan todas al reves por alguna razon
    insert_function(tVOID, "on_key", 2,  tINT, tFUNCTION);
    insert_function(tVOID, "loop", 0);
}

void init_table() {
    current_scope = 0;
    size = 0;
    num_blocks = 1;
    hash_table = calloc(BLOCK_SIZE, sizeof(node_t *));
    insert_lib_functions();
}

unsigned long long hash(char *name) {
    unsigned long long prehash = 5381;
    int c;

    while (c = *name++)
        prehash = ((prehash << 5) + prehash) + c;

    return prehash;
}

int insert(variable *var) {
    unsigned long long pre = hash(var->name);
    unsigned int key_index = pre % (num_blocks * BLOCK_SIZE);
    node_t *node = hash_table[key_index];

    while (node != NULL && node->prehash != pre) node = node->next;

    if (node == NULL) {
        node = (node_t *)malloc(sizeof(node_t));
        node->var = var;
        node->scope = current_scope;
        node->next = hash_table[key_index];
        node->prehash = pre;
        hash_table[key_index] = node;
        size++;
    } else {
        if (node->scope == current_scope) {
            printf("Multiple declaration of variable %s", var->name);
            return MULTIPLE_DECLARATION;
        } else {
            node = (node_t *)malloc(sizeof(node_t));
            node->var = var;
            node->scope = current_scope;
            node->next = hash_table[key_index];
            node->prehash = pre;
            hash_table[key_index] = node;

            size++;
        }
    }

    if ((size * 1.0) / (num_blocks * BLOCK_SIZE) >= THRESHOLD) {
        num_blocks++;
        hash_table = realloc(hash_table, sizeof(node_t *) * num_blocks * BLOCK_SIZE);
        memset(hash_table + size, 0, (num_blocks * BLOCK_SIZE - size) * sizeof(node_t *));
    }
}

void expand_table() {
}

variable *lookup(char *name) {
    variable *aux;
    for (int scope = current_scope; scope >= 0; scope--) {
        aux = lookup_in_scope(name, scope);
        if (aux != NULL) return aux;
    }
    return NULL;
}

variable *lookup_in_scope(char *name, int scope) {
    unsigned long long pre = hash(name);
    unsigned int index = pre % (num_blocks * BLOCK_SIZE);
    node_t *node = hash_table[index];
    while (node != NULL && node->prehash != pre &&  node->scope != scope) node = node->next;
    if (node != NULL)
        return node->var;
    else
        return NULL;
}

void next_scope() {
    current_scope++;
}

void prev_scope() {
    node_t *node;
    node_t *prev;

    for (int i = 0; i < size; i++) {
        if (hash_table[i] != NULL) {
            node = hash_table[i];
            while (node != NULL && node->scope == current_scope) {
                prev = node;
                node = node->next;
                free(prev);
            }
            hash_table[i] = node;
        }
    }
    if (current_scope > 0) {
        current_scope--;
    }
}
