/*
 * linkedlist.h
 *
 * This header file contains examples of how to:
 *
 * a) Dynamically allocate memory in a function
 * b) Free memory used by a linked list
 * c) Print the contents of a linked list 
 * d) Apply a function to a linked list
 *
 * All the linked lists are set to void*.  You may replace them
 * with your own struct typedefs.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define INVAILD_ARGUMENTS_ERROR_CODE 1
#define FILE_OPEN_ERROR_CODE 2
#define MEMORY_ALLOCATION_ERROR_CODE 3

/* Dynamically allocate memory of size_t n and return the 
 * pointer to the memory address
 *
 * exit with return code on allocation error 
 */


typedef struct node_t {
    int             count;
    int             length;
    char*           word;
    struct node_t   *next;
} node_t; 


node_t *new_node(char* word, int length);
void *emalloc(size_t n);
void cleanup_list(node_t *list);
void print_list(node_t* list);
void apply(node_t *list, void (*fn)(void *list, void *), void *arg);

node_t *new_node(char* word, int length) {
    assert(word != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    temp->word = (char *) emalloc(sizeof(char) * (strlen(word)+1));
    strcpy(temp->word, word);
    temp->length = length;
    temp->count = 1;
    temp->next = NULL;
    return temp;
}

node_t *add_ascending_order(node_t *list, node_t *new) {
    if (list == NULL) return new;
    node_t *curr = NULL;
    node_t *prev = NULL;

    curr = list;

    for( ; curr != NULL; curr = curr->next) {
        if (curr->length < new->length) {
            prev = curr;
        } else if ((curr->length == new->length) && (strcmp(new->word, curr->word) < 0)) {
            prev = curr;
        } else if ((curr->length == new->length) && (strcmp(new->word, curr->word) == 0)) {
            curr->count += 1;
            free(new->word);
            free(new);
            return list;
        } else {
            break;
        }
    }

    new->next = curr;
    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return list;
    }
}

node_t *add_descending_order(node_t *list, node_t *new) {
    if (list == NULL) return new;
    node_t *curr = NULL;
    node_t *prev = NULL;

    curr = list;

    for( ; curr != NULL; curr = curr->next) {
        if (curr->length < new->length) {
            prev = curr;
        } else if ((curr->length == new->length) && (strcmp(new->word, curr->word) > 0)) {
            prev = curr;
        } else if ((curr->length == new->length) && (strcmp(new->word, curr->word) == 0)) {
            curr->count += 1;
            free(new->word);
            free(new);
            return list;
        } else {
            break;
        }
    }

    new->next = curr;
    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return list;
    }
}

void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(MEMORY_ALLOCATION_ERROR_CODE);
    }

    return p;
}

/* Example of how to free memory used by a double-linked list
 */
void cleanup_list(node_t *list) {
    if(list == NULL)
       return;
    free(list->word);
    cleanup_list(list->next);
    free(list);
}

/* Example of how to print a linked list
 
void print_list(node_t* list)
{    
    if (list == NULL) {
        return;
    }
    while (list->next != NULL) { 
       fprintf(stderr, "%s", list->word); 
    } 
    print_list(list->next);
}


 Example of how to apply a function to a each node in a linked list.  This is made so that different functions/arguments can be used.
 *
 * void *list : head of linked list to apply function
 * void (*fn)(void *list, void*) : function that takes in two arguments.
 * void *arg : second argument to pass to argument
 
void apply(node_t *list,
           void (*fn)(void *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
*/


