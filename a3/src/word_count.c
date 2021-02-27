#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "word_count.h"



FILE* openText (int argc, char *argv[], char *type);
int file_size (FILE *text);
node_t* tokenize (char* buffer, node_t* list, char type);
int counter (node_t *curr, int length);
void print_result (node_t *list);

FILE* openText (int argc, char *argv[], char *type) {
    FILE *text = NULL;
    for (int i=0; i<argc; i++) {
        if (strcmp(argv[i], "--infile") == 0) {
            if (access(argv[i+1], F_OK) == -1) {
                fprintf(stderr, "Unable to open file\n");
                exit(FILE_OPEN_ERROR_CODE);
            }
        } 
        if(strcmp(argv[i], "--sort") == 0 && argc == 4) {
            for (int j=1; j < argc; j++) {
                if(access(argv[j], F_OK) == 0 && strcmp(argv[j-1],"--infile") == 0) {
                    text = fopen(argv[j], "r");
                    *type = 'a';
                    return text;
                }
            }
        }    
    }
    if ((strcmp(argv[1],"--infile") == 0) && access(argv[2], F_OK) == 0 && argc == 3) {
        text = fopen(argv[2], "r");
        *type = 'b';
        return text;
    } 
    return text;
}

int file_size (FILE *text) {
    int size;
    fseek(text, 0, SEEK_END);
    size = ftell(text);
    rewind(text);
    return size;
} 

node_t* tokenize (char* buffer, node_t* list, char type) {
    char *sep = " ,.();:\n";
    char *p = strtok(buffer, sep);
    if (type == 'a') {
        while (p != NULL) {
            //printf("%s, %d\n", p, strlen(p));
            list = add_ascending_order(list, new_node(p, strlen(p)));
            p = strtok(NULL, sep);
        }
        return list;
    } else {
        while (p != NULL) {
            list = add_descending_order(list, new_node(p, strlen(p)));
            p = strtok(NULL, sep);
        }
        return list;
    }
}

void print_result (node_t *list) {
    node_t *curr = list;
    int len = 0;
    int count;

    for (; curr != NULL; curr = curr->next) {
        if (len != curr->length) {
            count = counter(curr, curr->length);
            printf("Count[%02d]=%02d; ", curr->length, count);
            len = curr->length;
        }
        printf("(words: ");
        for (; curr->length == len; curr = curr->next) {
            if (count == 1) {
                printf("\"%s\"", curr->word);
                break;
            }
            if (curr->next == NULL) {
                if (curr->length != len) {
                    printf("(words \"%s\"", curr->word);
                } else {
                    printf(" and \"%s\"", curr->word);
                }
                break;
            }
            if (curr->next->length != len) {
                printf(" and \"%s\"", curr->word);
                break;
            }
            printf("\"%s\"", curr->word);
            if (curr->next != NULL) {
                if (curr->next->next != NULL) {
                    if (curr->next->next->length == len) {
                        printf(", ");
                    }
                }
            }
        }
        printf(")\n");
    }
}

int counter (node_t *curr, int length) {
    node_t *temp = curr;
    int count = 0;
    for (; temp->length == length; temp = temp->next) {
        count += temp->count;
        if (temp->next == NULL) {
            break;
        }
    }
    return count;
}

int 
main(int argc, char *argv[]) {
    FILE *text;
    node_t *list = NULL;
    char *buffer;
    char type;

    if ( argc < 2) {
        return 0;
    } else {
        text = openText(argc, argv, &type);
        if (text == NULL) {
            fprintf(stderr, "Invalid command line arguments\n");
            exit(INVAILD_ARGUMENTS_ERROR_CODE);
        }
    }
    
    int text_size = file_size(text);
    buffer = (char *) emalloc (sizeof(char) * (text_size+1));    
    fread(buffer, sizeof(char), text_size, text);
    buffer[text_size] = '\0';
    list = tokenize(buffer, list, type);

    free(buffer); 
    fclose(text);

    print_result(list); 

    cleanup_list(list);

    return 0;
}

