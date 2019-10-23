//
// Created by RTinchev on 10/22/2019.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "encoder.h"
#include "converters.h"

void ErrorCheck(int PairedLeftByte[], int PairedRightByte[], int UnpairedFinal[]){
    int p1 = PairedLeftByte[0];
    int p2 = PairedLeftByte[5];
    int p3 = PairedLeftByte[6];
    int p4 = PairedLeftByte[7];
    int d1 = PairedLeftByte[1];
    int d2 = PairedLeftByte[2];
    int d3 = PairedLeftByte[3];
    int d4 = PairedLeftByte[4];
    /**
     * if 1 no errors if 0, error present
     */
    int c1 = (p2+d1+d3+d4)%2 != 0 ? 1 : 0;
    int c2 = (p3+d1+d2+d4)%2 != 0 ? 1 : 0;
    int c3 = (p4+d2+d3+d4)%2 != 0 ? 1 : 0;
    /**
     * check if the first parity bit is correct
     */
    if(3-(c1+c2+c3) == 0)
        p1 ^= 1;
    /**
     * check if only 1 circle is wrong
     */
    else if(3-(c1+c2+c3) == 1){
        if(!c1)
            p2 ^= 1;
        if(!c2)
            p3 ^= 1;
        if(!c3)
            p4 ^= 1;
    }
    /**
     * check if 2 circles are wrong
     */
    else if(3-(c1+c2+c3) == 2){
        if(!c2 && !c3)
            d2 ^= 1;
        if(!c1 && !c2)
            d1 ^= 1;
        if(!c3 && !c1)
            d3 ^= 1;
    }
    /**
     * check if 3 circles are wrong
     */
    else if(3-(c1+c2+c3) == 3)
        d4 ^= 1;
    /**
     * update the correctness of the circles
     */
    c1 = (d1+d3+d4+p2)%2 != 0 ? 1 : 0;
    c2 = (d1+d2+d4+p3)%2 != 0 ? 1 : 0;
    c3 = (d2+d3+d4+p4)%2 != 0 ? 1 : 0;
    /**
     * check if all of the circles are correct
     */
    if(c1 && c2 && c3){
        UnpairedFinal[0] = d1;
        UnpairedFinal[1] = d2;
        UnpairedFinal[2] = d3;
        UnpairedFinal[3] = d4;
    }
    /**
     * second half of the final byte
     */
    p1 = PairedRightByte[0];
    p2 = PairedRightByte[5];
    p3 = PairedRightByte[6];
    p4 = PairedRightByte[7];
    d1 = PairedRightByte[1];
    d2 = PairedRightByte[2];
    d3 = PairedRightByte[3];
    d4 = PairedRightByte[4];
    /**
     * if 1 no errors if 0, error present
     */
    c1 = (p2+d1+d3+d4)%2 != 0 ? 1 : 0;
    c2 = (p3+d1+d2+d4)%2 != 0 ? 1 : 0;
    c3 = (p4+d2+d3+d4)%2 != 0 ? 1 : 0;
    /**
     * checks if there are any issues with the 3 hamming code circles
     */
    if(3-(c1+c2+c3) == 0)
        p1 ^= 1;
    /**
     * check if only 1 circle is wrong
     */
    else if(3-(c1+c2+c3) == 1){
        if(!c1)
            p2 ^= 1;
        if(!c2)
            p3 ^= 1;
        if(!c3)
            p4 ^= 1;
    }
    /**
     * check if 2 circles are wrong
     */
    else if(3-(c1+c2+c3) == 2){
        if(!c2 && !c3)
            d2 ^= 1;
        if(!c1 && !c2)
            d1 ^= 1;
        if(!c3 && !c1)
            d3 ^= 1;
    }
    /**
     * check if 3 circles are wrong
     */
    else if(3-(c1+c2+c3) == 3)
        d4 ^= 1;
    /**
     * update the correctness of the circles
     */
    c1 = (d1+d3+d4+p2)%2 != 0 ? 1 : 0;
    c2 = (d1+d2+d4+p3)%2 != 0 ? 1 : 0;
    c3 = (d2+d3+d4+p4)%2 != 0 ? 1 : 0;
    /**
     * check if all of the circles are correct
     */
    if(c1 && c2 && c3){
        UnpairedFinal[4] = d1;
        UnpairedFinal[5] = d2;
        UnpairedFinal[6] = d3;
        UnpairedFinal[7] = d4;
    }
}

int main(int argc, char *argv[]){
    /**
     * file pointer
     */
    FILE *fp;
    /**
     * opening the fie and assigning the reference to the pointer
     */
    fp = fopen(argv[1], "r");
    /**
     * line counter and lines holding array declaration
     */
    int line = 0;
    char lines[MAX_SIZE_OF_FILE_LINE][MAX_SIZE_OF_FILE_LINE];
    /**
     * read the text of the file onto the file text using the pointer, line by line, until the end of the file is reached
     */
    while(fgets(lines[line], MAX_SIZE_OF_FILE_LINE, fp))
    {
        lines[line][strlen(lines[line])] = '\0';
        line++;
    }
    /**
     * close the file
     */
    fclose(fp);
    int l, k;
    printf("File %s is being decoded!\n", argv[1]);
    for(l = 0; l<line; l++ ) {
        for (k = 0; k < MAX_SIZE_OF_FILE_LINE; k++) {
            /**
             * checks if the next array element is a null, if true, breaks the whole loop as there are no more characters in the array
             */
            if (lines[l][k] == 0)
                break;
            /**
             * int array to hold each bit of the binary number
             */
            int j, binaryL[MAX_ARRAY_SIZE], binaryR[MAX_ARRAY_SIZE];
            for (j = 7; j >= 0; j--) {
                binaryL[7 - j] = (((lines[l][k] - 8) + MAX_ARRAY_SIZE) & (1 << j)) ? 1 : 0;
            }
            k++;
            for (j = 7; j >= 0; j--) {
                binaryR[7 - j] = (((lines[l][k] - 8) + MAX_ARRAY_SIZE) & (1 << j)) ? 1 : 0;
            }
            int final[MAX_ARRAY_SIZE];
            ErrorCheck(binaryL, binaryR, final);

            /**
             * saving encoded characters to a new file
             */
            FILE *newFp;
            newFp = fopen(argv[2], "a");
            fprintf(newFp, "%c", BinaryAsDecimal(NumberAsBinary(final)));
            fclose(newFp);
        }
    }
    printf("File decoded!\n");
    return 0;
}