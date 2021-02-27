#ifndef A1_H
#define A1_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define FILE_NOT_FOUND  1
#define BAD_ARGS        2
#define MAX_FILESIZE    5000
#define MAX_WORD_CNT    750
#define MAX_WORD_LEN    35 //Supercalifragilisticexpialidocious
#define TRUE 1
#define FALSE 0

/* 
 * Debugging print function that can has the same 
 * format as `printf`.  If `-D DEBUG` is passed to
 * the compiler then the print code is compiled, 
 * otherwise, it's an empty function.
 *
 */
void debug(const char* format, ... );
void debug(const char* format, ... ) {
#ifdef DEBUG 
	va_list args;
	
	fprintf(stdout, "  -->  ");
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);

	fprintf(stdout, "\n");
	fflush(stdout);
#endif	
}

typedef struct word_t
{
    //TODO
    char word[MAX_WORD_LEN];
    int count;

} word_t;

size_t read_file(char* filepath, char* buffer);
int tokenize_string(char* buffer, size_t bytes, word_t* freq);
void print_histogram(word_t* buckets, int print_words);
void print_median(word_t* bucket, int number_of_buckets);

int by_freq( const void* a, const void* b);
int by_len( const void* a, const void* b);
int by_alphanum( const void* a, const void* b);

int
tokenize_string(char *buffer, size_t bytes, word_t* bucket) {
    /* char* buffer: Input string to tokenize
     * size_t bytes: size of buffer in bytes
     * word_t* bucket: pointer to struct word array that holds the word histogram
     *
     * Function tokenizes the buffer and update the appropriate word_t buckets 
     *
     * Returns: number of buckets 
     */
    
    return 0;
}

void
print_histogram(word_t* bucket,  int print_words)
{
    /* word_t* bucket: pointer to struct word array that holds the word histogram
     * print_words: flag to print words (Part C) or not
     *
     * Function prints out the word histogram 
     */
}

void
print_median(word_t* bucket, int number_of_buckets)
{
    /* word_t* bucket: pointer to struct word array that holds the word histogram
     * int number_of_buckets: Number of buckets (unique word lengths) 
     *
     * Function prints out the word length median value 
     */
}

size_t
read_file(char* filepath, char* buffer) {
    /* char* filepath: path to the input word file (i.e. t01.txt) 
     * char* buffer: buffer to save the contents of the file to 
     *
     * Function that reads the contents of a file into the array buffer
     *
     * Returns: the size of the array in bytes 
     */

    return 0;
}

/* Functions to be used by `qsort`
 *
 * These functions should sort by these rules:
 *      a left of b   return positive value
 *      a equals b    return 0
 *      b right of a  return negative value
 *
 * In you function, you need to cast your pointer
 * to the correct pointer type:
 *     
 *     const char *ai = (const char*) a;  
 */

int by_freq( const void* a, const void* b)
{
    //Sort by word count/frequency (--sort flag)
    //In the case of a tie, sort by word length
    return 0;
}

int by_len( const void* a, const void* b)
{
    //Sort by word length
    return 0;
}

int by_alphanum( const void* a, const void* b)
{
    //Sort alphaphetically
    //Remember that upper should come before lowercase
    return 0;
}


#endif
