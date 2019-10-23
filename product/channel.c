//
// Created by RTinchev on 10/22/2019.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "encoder.h"
#define MAX_8_BIT_INT 256

int main(int argc, char *argv[]){
    //file pointer
    FILE *fp;
    //opening the fie and assigning the reference to the pointer
    fp = fopen(argv[1], "r");
    //holder for the text in the file with max size of MAX_SIZE_OF_FILE_LINE global variable
    int line = 0;
    char lines[MAX_SIZE_OF_FILE_LINE][MAX_SIZE_OF_FILE_LINE];
    //read the text of the file onto the file text using the pointer
    while(fgets(lines[line], MAX_SIZE_OF_FILE_LINE, fp))
    {
        lines[line][strlen(lines[line])] = '\0';
        line++;
    }
    //read the text of the file onto the file text using the pointer
    //close the file
    fclose(fp);
    int i, l;
    srand ( time(NULL) );
    printf("Characters after flipping: \n");
    printf("\t|Character: ");
    printf("\t|Character as ASCII number: ");
    printf("\t|Binary number: ");
    printf("|Saved to file: |\n ");
    for(l = 0; l<line; l++ ) {
        for (i = 0; i < MAX_SIZE_OF_FILE_LINE; i++) {
            //checks if the next array element is a null, if true, breaks the whole loop as there are no more characters in the array
            if (lines[l][i] == 0)
                break;
            //get the current number as a signed int
            int currentNum = (int)lines[l][i] + MAX_8_BIT_INT;
            //make a random number, even though it is limited, there are 8 powers of 2 corresponding to the 8 bits in the byte
            int randomNum = (int) pow(2, rand() % 8);
            //using XOR to flip one bit only
            currentNum ^= randomNum;
            if (lines[l][i] - 127 == 10 ||lines[l][i] == 10)
                printf("\t|LF");
            else if (lines[l][i] - 127 == 13 ||lines[l][i] == 13)
                printf("\t|CR");
            else
                printf("\t|%c", currentNum);
            printf("\t\t|%i", currentNum);
            int j, binary[MAX_ARRAY_SIZE];
            for (j = 7; j >= 0; j--) {
                binary[7 - j] = ((lines[l][i] + MAX_8_BIT_INT) & (1 << j)) ? 1 : 0;
            }
            printf("\t\t\t\t|%i", binary[0]);
            printf("%i", binary[1]);
            printf("%i", binary[2]);
            printf("%i", binary[3]);
            printf("%i", binary[4]);
            printf("%i", binary[5]);
            printf("%i", binary[6]);
            printf("%i", binary[7]);
            //saving encoded characters to a new file
            FILE *newFp;
            newFp = fopen(argv[2], "a");
            fprintf(newFp, "%c", currentNum);
            fclose(newFp);
            printf("\t|x\t\t|\n");
        }
    }
    return 0;
}