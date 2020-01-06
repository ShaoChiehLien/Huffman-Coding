//
//  unhuff.c
//  ece368_P1
//
//  Created by Jack on 2019/9/15.
//  Copyright © 2019 Jack. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


FILE *ptrprintFile;

int main(int argc, char *argv[])
{
    /////////////****** Read The Encode Book ******////////////
    FILE *pFile;
    pFile = fopen(argv[1], "r");
    int CodeBook[2][256];
    int Size = 0;
    int i = 0;
    int CodeBookLength = 0;
    while(1){
        fscanf(pFile, "%d", &CodeBook[0][i]);
        if(CodeBook[0][i] == 300)
            break;
        fscanf(pFile, "%d", &CodeBook[1][i]);
        CodeBookLength++;
        i++;
        Size++;
    }
    /////////////****** Read The Encode Book ******////////////
    
    /////////////****** Convert The Encode Book into Proper Way******////////////
    i = 0;
    int ch = getc(pFile);
    int *IntFileArrBit = (int *) malloc(sizeof(int) * 800000000);
    int FileLength = 0;
    while (ch != EOF)
    {
        int ShiftAmount = 7;
        for(i = FileLength; i < FileLength + 8; i++){
            int xxx = (ch>>ShiftAmount) & 1;
            IntFileArrBit[i] = xxx;
            ShiftAmount--;
        }
        FileLength = FileLength + 8;
        ch = getc(pFile);
    }
    
    int eofSign = 0;
    for(i = 0; i < CodeBookLength; i++){
        if(CodeBook[0][i] == 256){
            eofSign = CodeBook[1][i];
        }
    }
    /////////////****** Convert The Encode Book into Proper Way******////////////
    
    const char * prefix = ".unhuff";
    int needed = (int)strlen( argv[ 1 ] ) + (int)strlen( prefix );
    char storeFileName[needed];
    strcpy( storeFileName, argv[ 1 ] );
    strcat( storeFileName, prefix );
    ptrprintFile = fopen(storeFileName,"w");
    
    /////////////****** Based on Encode Book, print out the original file ******////////////
    long long buffer = 0;
    int countBit = 0;
    int trigger = 1;
    buffer = (buffer << 1) | 1;
    while(trigger){
        if(IntFileArrBit[countBit] == 0){
            buffer = (buffer << 1);
        }else{
            buffer = (buffer << 1) | 1;
        }
        for(i = 0; i < CodeBookLength; i++){
            if(buffer == eofSign){
                trigger = 0;
                break;
            }
            if(buffer == CodeBook[1][i] && trigger){
                fprintf(ptrprintFile, "%c", CodeBook[0][i]);
                buffer = 0;
                buffer = (buffer << 1) | 1;
                break;
            }
        }
        countBit++;
    }
    /////////////****** Based on Encode Book, print out the original file ******////////////
    
    fclose(pFile);
    
    return 0;
}
