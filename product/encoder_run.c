#include <stdio.h>
#include <string.h>
#include "encoder.h"
#include "converters.h"

void PrintTableLine(){
    printf("\t________________________________________________________________________________________________________________\n");
}

int main(int argc, char *argv[]) {
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
    //close the file
    fclose(fp);
    //ints used for loops
    printf("Characters read: \n");
    int i,k,l;
    PrintTableLine();
    //main loop going through every single character of the file
    printf("\t|Character: ");
    printf("\t|Character as ASCII number: ");
    printf("\t|Binary number: ");
    printf("|MSB: ");
    printf("\t\t|LSB: ");
    printf("\t\t|Saved to file: |\n ");
    PrintTableLine();
    for(l = 0; l<line; l++ ) {
        for (k = 0; k < MAX_SIZE_OF_FILE_LINE; k++) {
            //checks if the next array element is a null, if true, breaks the whole loop as there are no more characters in the array
            if (lines[l][k] == 0)
                break;
            //nice descriptive text reporting the values of the current character
            if (lines[l][k] == 10)
                printf("\t|LF");
            else if (lines[l][k] == 13)
                printf("\t|CR");
            else
                printf("\t|%c", lines[l][k]);
            printf("\t\t|%i", lines[l][k]);
            //int array to hold each bit of the number
            int j, binary[MAX_ARRAY_SIZE];
            for (j = 7; j >= 0; j--) {
                binary[7 - j] = (lines[l][k] & (1 << j)) ? 1 : 0;
            }
            printf("\t\t\t\t|%i", binary[0]);
            printf("%i", binary[1]);
            printf("%i", binary[2]);
            printf("%i", binary[3]);
            printf("%i", binary[4]);
            printf("%i", binary[5]);
            printf("%i", binary[6]);
            printf("%i", binary[7]);
            //declaration of the MSB and LSB arrays
            int MSB[MAX_ARRAY_SIZE], LSB[MAX_ARRAY_SIZE];
            //MSG block logic of the application
            BytePairing(MSB, binary[0], binary[1], binary[2], binary[3]);
            printf("\t|");
            for (i = 0; i < MAX_ARRAY_SIZE; i++) {
                printf("%i", MSB[i] == 1 || MSB[i] == 0 ? MSB[i] : 2);
            }
            //LSB block logic of the application
            BytePairing(LSB, binary[4], binary[5], binary[6], binary[7]);
            printf("\t|");
            for (i = 0; i < MAX_ARRAY_SIZE; i++) {
                printf("%i", LSB[i] == 1 || LSB[i] == 0 ? LSB[i] : 2);
            }
            //saving encoded characters to a new file
            FILE *newFp;
            newFp = fopen(argv[2], "a");
            fprintf(newFp, "%c", BinaryAsDecimal(NumberAsBinary(MSB)));
            fprintf(newFp, "%c", BinaryAsDecimal(NumberAsBinary(LSB)));
            fclose(newFp);
            printf("\t|x\t\t|\n");
        }
    }
    PrintTableLine();
    printf("Task complete\n");
    return 0;
}