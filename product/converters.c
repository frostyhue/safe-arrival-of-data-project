//
// Created by blood on 10/22/2019.
//
#include <math.h>
#include "converters.h"

//Converts the binary input number to a decimal number that will be used for ASCII characters
int BinaryAsDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0) {
        remainder = n % 10;
        n /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }
    return decimalNumber;
}

//Converts the numbers in the array to a binary number
int NumberAsBinary(int *BinaryArrayPtr){
    int result = 0;
    int i;
    int multiplier = 1;

    for(i = 7; i>=0; i--){
        result += (multiplier * BinaryArrayPtr[i]);
        multiplier *= 10;
    }
    return result;
}
