//
//  huff.c
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

struct Node
{
    int Info;
    int weight;
    struct Node *Right_Ptr;
    struct Node *Left_Ptr;
};

int Empty (struct Node *BT_Ptr){
    return (BT_Ptr == NULL);
}

struct Node *Create (int Info, int weight, struct Node *Left_Ptr, struct Node *Right_Ptr){
    struct Node *New_Node = NULL;
    New_Node = malloc (sizeof (struct Node));
    New_Node->Info = Info;
    New_Node->weight = weight;
    New_Node->Left_Ptr = Left_Ptr;
    New_Node->Right_Ptr = Right_Ptr;
    return New_Node;
}

int Info (struct Node *Node_Ptr){
    return (Node_Ptr->Info);
}

struct Node *Left_Child (struct Node *Node_Ptr){
    return Node_Ptr->Left_Ptr;
}

struct Node *Right_Child(struct Node *Node_Ptr){
    return Node_Ptr->Right_Ptr;
}

struct Node *BT_Delete (struct Node *BT_Ptr){
    if (BT_Ptr == NULL)
        return NULL;
    BT_Delete (BT_Ptr->Left_Ptr);
    BT_Delete (BT_Ptr->Right_Ptr);
    free (BT_Ptr);
    return NULL;
}

void PrintPreorderTree (struct Node *BT_Ptr)
{
    if (BT_Ptr != NULL){
        PrintPreorderTree(BT_Ptr->Left_Ptr);
        PrintPreorderTree(BT_Ptr->Right_Ptr);
    }
}

int CodeBookj = -1;

int **Preorder (struct Node *BT_Ptr, int path, int** CodeBook){//print the encode table
    if (BT_Ptr != NULL)
    {
        if (BT_Ptr->Info != 0)
        {
            CodeBookj++;
            CodeBook[0][CodeBookj] = BT_Ptr->Info;
            CodeBook[1][CodeBookj] = path;
            
            fprintf(ptrprintFile, "%d ", CodeBook[0][CodeBookj]);
            fprintf(ptrprintFile, "%d ", CodeBook[1][CodeBookj]);
        }
        Preorder(BT_Ptr->Left_Ptr, (path << 1) & ~(1 << 0), CodeBook);
        Preorder(BT_Ptr->Right_Ptr, (path << 1) | 1, CodeBook);
    }
    return CodeBook;
}

int Byteprinted = 0;
long long CountByte = 0;
void printBinaryCode(int num){//shift bit to buffer, output a byte when there are 8 bits shift in
    int trigger = 1;
    int i = 0;
    for(i = sizeof(num)*4-1; i >= 0; i--){
        if(((num>>i) & 1) == 0){
            if(trigger){
                
            }else{
                Byteprinted = (Byteprinted << 1) & ~(1 << 0);
                CountByte++;
                if(CountByte == 8){
                    fwrite(&Byteprinted, 1, 1, ptrprintFile);
                    Byteprinted = 0;
                    CountByte = 0;
                }
            }
        }else{
            if(trigger){
                
            }else{
                Byteprinted = (Byteprinted << 1)|1;
                CountByte++;
                if(CountByte == 8){
                    fwrite(&Byteprinted, 1, 1, ptrprintFile);
                    Byteprinted = 0;
                    CountByte = 0;
                }
            }
            trigger = 0;
        }
        
    }
}

int main(int argc, char *argv[])
{
    
    /////////////****** Read The File ******////////////
    FILE *pFile;
    pFile = fopen(argv[1], "r");
    char *IntFileArr = (char *) malloc(sizeof(char) * 100000000);
    int Size = 0;
    while(1){
        int breakflag = fscanf(pFile, "%c", &IntFileArr[Size]);
        if(breakflag == EOF){
            break;
        }
        Size++;
    }
    fclose(pFile);
    /////////////****** Read The File ******////////////
    
    ////////////****** create character weight table ******////////////
    int asciiWeightTable[257];
    int i = 0;
    for(i = 0; i < 256; i++){
        asciiWeightTable[i] = 0;
    }
    for(i = 0; i < Size; i++){
        asciiWeightTable[(int)IntFileArr[i]]++;
    }
    asciiWeightTable[256] = 1;//EOF appear one time
    
    struct Node *NodeList[512];

    for(i = 0; i <= 512; i++){
        NodeList[i] = Create(i, asciiWeightTable[i], NULL, NULL);
    }
    ////////////****** create character weight table ******////////////
    
    int topIndex = 0;
    int trigger = 1;
    while(trigger == 1){
        
        /////////////****** Find two min value ******////////////
        int minValue1 = 10000000;
        int minValue1Index = 0;
        for(i = 0; i <= 256 + topIndex; i++){
            if(NodeList[i]->weight == 0){
                
            }else{
                if(NodeList[i]->weight < minValue1){
                    minValue1 = NodeList[i]->weight;
                    minValue1Index = i;
                }
            }
        }
        
        int minValue2 = 10000000;
        int minValue2Index = 0;
        for(i = 0; i <= 256 + topIndex; i++){
            if(NodeList[i]->weight == 0 || i == minValue1Index){
                
            }else{
                if(NodeList[i]->weight < minValue2){
                    minValue2 = NodeList[i]->weight;
                    minValue2Index = i;
                }
            }
        }
        if(minValue2 == 10000000){
            trigger = 0;
            break;
        }
        /////////////****** Find two min value ******////////////
        
        /////////////****** Combine two nodes into a tree ******////////////
        topIndex++;
        struct Node *NewNode = Create (0, NodeList[minValue1Index]->weight + NodeList[minValue2Index]->weight, NodeList[minValue1Index], NodeList[minValue2Index]);
        NodeList[minValue1Index]->weight = 0;
        NodeList[minValue2Index]->weight = 0;
        NodeList[256+topIndex] = NewNode;
        /////////////****** Combine two nodes into a tree ******////////////
    }
    
    int **CodeBook = malloc(2 * sizeof(int *));
    for (i = 0; i < 2; i++)
        CodeBook[i] = malloc((topIndex+1) * sizeof(int));
    
    int **NewCodeBook = malloc(2 * sizeof(int *));
    for (i = 0; i < 2; i++)
        CodeBook[i] = malloc((topIndex+1) * sizeof(int));
    
    /////////////****** Create new file with name .huff.txt ******////////////
    const char * prefix = ".huff";
    int needed = (int)strlen( argv[ 1 ] ) + (int)strlen( prefix );
    char storeFileName[needed];
    strcpy( storeFileName, argv[ 1 ] );
    strcat( storeFileName, prefix );
    ptrprintFile = fopen(storeFileName,"w");
    /////////////****** Create new file with name .huff.txt ******////////////
    
    PrintPreorderTree (NodeList[256+topIndex]);//print Coding Book
    
    NewCodeBook = Preorder (NodeList[256+topIndex], 1, CodeBook);
    fprintf(ptrprintFile, "300");//print the stop reading sign for reading coding book
    
    /////////////****** Serach for coding book, convert each character and print ******////////////
    int eofSign = 0;
    for(i = 0; i < topIndex; i++){
        if(NewCodeBook[0][i] == 256){
            eofSign = i;
            break;
        }
    }
    int j = 0;
    for(i = 0; i < Size; i++){
        for(j = 0; j <= topIndex; j++){
            if(IntFileArr[i] == NewCodeBook[0][j]){
                printBinaryCode(NewCodeBook[1][j]);
                break;
            }
        }
    }
    printBinaryCode(NewCodeBook[1][eofSign]);//print EOF
    printBinaryCode(NewCodeBook[1][eofSign]);
    printBinaryCode(NewCodeBook[1][eofSign]);
    /////////////****** Serach for coding book, convert each character and print ******////////////
    fclose(ptrprintFile);
    
    for (i = 0; i < 2; i++)
        free(CodeBook[i]);
    free(CodeBook);
    return 0;
}
