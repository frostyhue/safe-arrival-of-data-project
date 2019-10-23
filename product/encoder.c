//
// Created by blood on 10/12/2019.
//
#include "encoder.h"
#include <stdio.h>

//Pairs the 4 bits with 4 additional Parity bits into a whole byte, sored in an array
void BytePairing(int PairedByte[], int d1, int d2, int d3, int d4){
    int p2, p3, p4;
    PairedByte[1] = d1;
    PairedByte[2] = d2;
    PairedByte[3] = d3;
    PairedByte[4] = d4;

    p2 = PairedByte[5] = (d1+d3+d4)%2 != 0 ? 0 : 1;
    p3 = PairedByte[6] = (d1+d2+d4)%2 != 0 ? 0 : 1;
    p4 = PairedByte[7] = (d2+d3+d4)%2 != 0 ? 0 : 1;

    PairedByte[0] = (d1+d2+d3+d4+p2+p3+p4)%2 != 0 ? 0 : 1;
}