// Dynamic memory allocation for an array of strings.
// In this implementation, we dynamically allocate an array of arrays.
// First, we allocate a pointer for each word read in from the file.
// Then we allocate space for each word individually.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h" //immediately after including all the header files
#define MAX_STRING_LENGTH 256

// function prototypes
char** readList(char* fileName, int* wordsCount);
void printList(char** pList, int length);
void freeList(char** pList, int length);

int main(void) {
  atexit(report_mem_leak); //add this line to your code
  char fileName[50];
  char** pList;
  int numWords;

  // get the file name
  printf("Enter the file name.\n");
  scanf("%s", fileName);

  // read in the list storing it in pList
  // numWords will store the number of words in the file 
  pList = readList(fileName, &numWords);

  // print these words to check that our read worked and free the memory
  printList(pList, numWords);
  freeList(pList, numWords);
  return 0;
}

char** readList(char *fileName, int *wordsCount){
  char ** pList = NULL;
  char word[MAX_STRING_LENGTH];
  int i, wordLength;

  FILE *pFile = fopen(fileName, "r"); // opens a file

  if(pFile != NULL){
    // read the 1st line, get to know how many words in the dictionary
    fscanf(pFile, "%d", wordsCount);

    // here we allocate space for a pointer for each word in the list. Note that the spcae for words themselves is NOT allocated here
    pList = malloc(*wordsCount*sizeof(char*));

    for(i = 0; i<*wordsCount; i++){
      // read in this word
      fscanf(pFile, "%s", word);
      // allocate one extra spot for the null char
      wordLength = strlen(word) +1;
      //allocate space for this individual word
      pList[i] = malloc(wordLength*sizeof(char));
      // copy the word to the memory block
      strcpy(pList[i], word);
    }
    fclose(pFile); // closes the file
  }
  return pList;
}

// Pre-condition: pList is a pointer to an array of pointers, each of which
//                already stores a string. length is the number of strings
//                stored in the structure.
// Post-condition: All of the strings stored in pList will be printed.
void printList(char** pList, int length) {
     int i;
     // Just loop through each pointer and print the appropriate string.
     for (i=0; i<length; i++)
                printf("%s\n", pList[i]);
}

// Pre-condition: pList is a pointer to an array of pointers, each of which
//                already stores a string. length is the number of strings
//                stored in the structure.
// Post-condition: The memory for the structure pointed to by pList will be
//                 freed.
void freeList(char** pList, int length) {
     int i;
     // Free the memory for each individual word.
     for (i=0; i<length; i++)
         free(pList[i]);
     // Free the pointers to each word.
     free(pList);
}