//
//  main.c
//  address_parsing
//
//  Created by Tejas Chavan on 11/19/18.
//  Copyright © 2018 tesla. All rights reserved.
//

#include <stdio.h>
#define DEBUG
int MD_BR_SHIFT = 3;
// This is the typedef for PC. similar to the one declared i simulator.
// Unsigned because PC is always pos.
typedef unsigned int word_t;

//structure of perceptron inputs
//creating it similar to the simulator

struct{
    int wt_entries;              // number of entries in weight table
    int wt_bits;                 // number of bits per slot
    int bhr_length;              // BHR lenghr
    signed int weight_table[1024][27]; // weight table structure
    int neural_output;                   // output of neural net
    signed int GBHR[27];                 // Global histry register
    int index;                           // Variable to store the index
}perceptron;




int EnterPC(word_t baddr)
{
    int index;
    #ifndef DEBUG
        printf("PROGRAM COUNTER FROM SIMULATOR TO BP  : %u\n", baddr);
    #endif
    
    index = (baddr >> MD_BR_SHIFT) % perceptron.wt_entries;
    printf("INDEX INTO THE TABLE : %u\n", index);
    
    return index;
}

void InitWeightGBHR()
{
    // Initialize all weights to 0
    for (int i = 0; i < perceptron.wt_entries; i++)
    {
        for (int j = 0; j < perceptron.bhr_length; j++)
        {
            perceptron.weight_table[i][j] = 0;
        }
    }
    
    // initialize all GBHR bits to 1(all taken)
    for (int i = 0; i < perceptron.bhr_length; i++)
    {
        perceptron.GBHR[i] = 1;
    }
}

int main()
{
    perceptron.wt_entries = 1024;
    perceptron.wt_bits = 9;
    perceptron.bhr_length = 27;
    
    InitWeightGBHR();
    perceptron.index = EnterPC(536870911);
    
    return 0;
}



