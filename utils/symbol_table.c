#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 0.75
#define BLOCK_SIZE 64

unsigned int current_scope;

typedef struct node_t{
    struct node_t * next;
    unsigned long long prehash;
    variable var;
}node_t;


node_t ** hash_table;

unsigned int size;
unsigned int num_blocks;

void init_table(){
    current_scope = 0;
    size = BLOCK_SIZE;
    hash_table = calloc(BLOCK_SIZE,sizeof(node_t *));


}
unsigned long long hash(char * name)
{
    unsigned long prehash = 5381;
    int c;

    while (c = *name++)
        prehash = ((prehash << 5) + hash) + c; 

    return prehash;
}

int insert(char * name, var_type type){
    unsigned long long pre = hash(name);
    unsigned int key_index = pre%size;
    node_t * node = hash_table[key_index];
    
    
    while(node != NULL && node->prehash != pre) node = node->next;

    if (node == NULL){
        node = (node_t *) malloc(sizeof(node_t));
        strcpy(node->var.name, name);
        node->var.type = type;
        node->var.scope = current_scope;
        node->next = hash_table[key_index];
        hash_table[key_index] = node;
        size++;
    }else{
        if(node->var.scope == current_scope){
            printf("Multiple declaration of variable %s", name);
            return MULTIPLE_DECLARATION;       
        }else{
            node = (node_t *) malloc(sizeof(node_t));
             strcpy(node->var.name, name);
            node->var.type = type;
            node->var.scope = current_scope;
            size++;

        }
    }

    if((size*1.0) / num_blocks*BLOCK_SIZE >= THRESHOLD ){
  
        num_blocks ++;
        hash_table = realloc(hash_table, sizeof(node_t *)*num_blocks * BLOCK_SIZE);
        memset(hash_table + size, 0, (num_blocks*BLOCK_SIZE - size)*sizeof(node_t *));
      
    }
    
}

void expand_table(){

}

variable * lookup(char * name){
    unsigned long long pre = hash(name);
    unsigned int index = pre % size;
    node_t * node = hash_table[index];
    while(node != NULL && node->prehash == pre) node = node->next;
    if(node->var.scope <= current_scope)
        return &node->var;
    else
        return NULL;
}

variable * lookup_in_scope(char * name, int scope){
    unsigned long long pre = hash(name);
    unsigned int index = pre % size;
    node_t * node = hash_table[index];
    while(node != NULL && node->prehash == pre) node = node->next;
    if(node->var.scope <= scope)
        return &node->var;
    else
        return NULL;
}

void next_scope(){
    current_scope++;
}


void prev_scope(){
    node_t * node;
    
    for(int i = 0; i < size ; i++){
        if(hash_table[i] != NULL){
            node = hash_table[i];
            while(node != NULL && node->var.scope == current_scope){
                node = node->next;
            }
            hash_table[i] = node; 
        }
    }
    if(current_scope > 0){
        current_scope--;
    }
}
