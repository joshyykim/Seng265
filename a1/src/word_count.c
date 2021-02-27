
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define FILE_NOT_FOUND  1
#define MAX_FILESIZE    5000
#define MAX_WORD_CNT    750
#define MAX_WORD_LEN    35 //Supercalifragilisticexpialidocious

typedef struct word_t
{
    char word[MAX_WORD_LEN];
    int count;
} word_t;

FILE* openText (int argc, char *argv[], char *typ);             // text file open
int sameWord(word_t bucket[], char *t);                         // searching same word included in bucket
int tokenizeText (char *buffer, word_t bucket[], FILE* text);   // tokenize text file to look single word
void printCount (word_t bucket[], int wordCount, char type);    // take type of result needed and print it out

int mostFrequent (int num[]);                                   // Find highest number of frequency of words
double findMedian (int num[], int total, int unique);           // Calculate the median word length
void sortByAlpha (word_t bucket[], int total);                  // Sort word in bucket alphabetically

FILE* openText (int argc, char *argv[], char *typ) {
    FILE* text = NULL;
    char temp;
    int i;
    int j;
    for (i=0; i < argc; i++) {              //type C check
        if (strcmp(argv[i], "--print-words") == 0) {
            temp = 'c';
            for (j = 2; j<argc; j++) {
                if (access(argv[j], F_OK) == 0) {
                    text = fopen(argv[j], "r");
                    *typ = temp;
                    return text;
                }
            }
        }
    }
    for (i = 0; i < argc; i++) {            //type B check
        if (strcmp(argv[i], "--sort") == 0) {
            temp = 'b';
            for (j = 2; j < argc; j++) {
                if (access(argv[j], F_OK) == 0) {
                    text = fopen(argv[j], "r");
                    *typ = temp;
                    return text; 
                }
            }
        }
    }
    if (access(argv[2], F_OK) == -1) {      //check vaild file open
        if (argv[2] == 0) {
            printf("program: missing '--infile <filename> [--sort] [--print-words]'\n");
            return text;
        }
        printf("unable to open 'badfile.txt' for reading\n");
        return text;
    }
    temp = 'a';                             //rest is type A
    text = fopen(argv[2], "r");
    *typ = temp;
    return text;
}

int sameWord(word_t bucket[], char *t) {
    int i;
    for (i = 0; i<MAX_WORD_CNT; i++) {
        if (strcmp(bucket[i].word, t) == 0) {
            // printf("%s,%s same word found\n", bucket[i].word, t);
            return i;
        }
    }
    return -1;
}

int tokenizeText (char *buffer, word_t bucket[], FILE* text) {
    char* t;
    char sep[] = " ,.();\n";
    int i;
    int count = 0;

    while (fgets(buffer, MAX_FILESIZE, text)) {
        t = strtok(buffer, sep);
        while (t != NULL) {
            i = sameWord(bucket, t);
            if (i == -1) {
                strncpy(bucket[count].word,t,MAX_WORD_LEN-1);
                bucket[count].count = 1;
                count++;
            } else {
                // printf("%s already exists\n", bucket[i].word);
                bucket[i].count++;
            }
            t = strtok(NULL, sep);
        }
    }
    return count;
}

void printCount (word_t bucket[], int wordCount, char type) {
    int i;
    int total = 0;
    int unique = 0;
    int count = 0;
    int num[MAX_WORD_LEN] = {0};

    while (total < wordCount) {
        for (i = 0; i<wordCount; i++) {
            // printf("%s length is %lu\n", bucket[i].word, strlen(bucket[i].word));
            num[strlen(bucket[i].word)] += bucket[i].count;
            total++;
        }
    }
    if (type == 'a'){                           //PART A result, frequency of each length
        int j = 0;
        while (j<MAX_WORD_LEN) {
            if (num[j] != 0){
                printf("Count[%02d]=%02d;\n", j, num[j]);
            }
            j++;
        }
    } else if (type == 'b') {                   //PART B result, sorted by frequency
        int max = mostFrequent(num);
        while (max > 0) {
            for (int j=0; j<MAX_WORD_LEN; j++) {
                if (num[j] == max) {
                    printf("Count[%02d]=%02d;\n", j, num[j]);
                    unique++;
                }
            }
            max--;
        }
        double median = findMedian(num, total, unique);
        printf("Median word length: %.1f\n", median);
        // printf("%d\n", mostFrequent(num));
    } else {                                    //PART C result, sorted by frequency w/ words
        int max = mostFrequent(num);
        sortByAlpha(bucket, total);
        while (max > 0) {
            for (int j=0; j<MAX_WORD_LEN; j++) {
                if (num[j] == max) {
                    printf("Count[%02d]=%02d; (words: ", j, num[j]);
                    int k = 0;
                    while (bucket[k].count != 0) {
                        if (count == num[j]-bucket[k].count && strlen(bucket[k].word) == j) break;
                        if (strlen(bucket[k].word) == j) {
                            if (count != 0 ) {
                                printf(", ");
                            }
                            printf("\"%s\"",bucket[k].word);
                            count += bucket[k].count;
                        }
                        k++;
                    }
                    if (count == 0) {
                        printf("\"%s\")\n",bucket[k].word);
                    } else {
                        printf(" and \"%s\")\n", bucket[k].word);
                    }
                    count = 0;
                }
            }
            max--;
        }
    }
}

int mostFrequent (int num[]) {
    int max = 0;
    for (int i=0; i<MAX_WORD_LEN; i++) {
        if (num[i] > max) {
            max = num[i];
        }
    }
    return max;
}

double findMedian (int num[], int total, int unique) {
    double median;
    int temp[MAX_WORD_LEN] = {0};
    int i;
    int count = 0;
    for(i = 0; i<MAX_WORD_LEN; i++) {
        if (num[i] != 0) {
            temp[count] = i;
            count++;
        }
    }
    if (count == 0) return 0;
    if (count % 2 == 0) {
        median = (temp[(count/2) - 1] + temp[(count/2)]) / 2.0;
    } else {
        median = (temp[(count-1)/2]);
    }
    // printf("%d %f\n", count, median);
    return median;
}

void sortByAlpha (word_t bucket[], int total) {
    word_t temp;
    int i;
    int j;
    for (i=0; i<total; i++) {
        for (j=0; j<total; j++) {
            if (strlen(bucket[i].word) == strlen(bucket[j].word)) {
                if (strcmp(bucket[i].word,bucket[j].word) < 0) {
                    // printf("before: %s %s\n", bucket[i].word, bucket[j].word);
                    // strcpy(tempWord,bucket[i].word);
                    // strcpy(bucket[i].word, bucket[j].word);
                    // strcpy(bucket[j].word, tempWord);
                    temp = bucket[i];
                    bucket[i] = bucket[j];
                    bucket[j] = temp;
                    // printf("after: %s %s\n", bucket[i].word, bucket[j].word);
                }
            }
        }
    }
}

int
real_main(int argc, char *argv[]) {
    //TODO
    FILE* text;
    char buffer[MAX_FILESIZE];
    struct word_t bucket[MAX_WORD_CNT] = {};
    char type;
    int count;

    if (argc < 2) {
        printf("program: missing '--infile <filename> [--sort] [--print-words]'\n");
        return FILE_NOT_FOUND;
    } else {
        text = openText(argc, argv, &type);
        if (text == NULL) {
            return FILE_NOT_FOUND;
        }
    }

    count = tokenizeText(buffer, bucket, text);
    printCount(bucket, count, type);
    fclose(text);

    return 0;
}


#ifndef TEST
int
main(int argc, char *argv[]) {
    return real_main(argc, argv);
}
#endif
