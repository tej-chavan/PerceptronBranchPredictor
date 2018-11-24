//
//  PerceptronOut.c
//  address_parsing
//
//  Created by Tejas Chavan on 11/20/18.
//  Copyright © 2018 tesla. All rights reserved.
//

//#include "PerceptronOut.h"
#include <stdio.h>
#include <math.h>
#define DEBUG

static signed int SumOfProduct;
static signed int FinalSum;
static int WtEntryReg[54];
static int GBHR[54];
static float theta;

int bhr_length = 54;
static int TruePrediction;



// We dont need to integrate this into the code.
//Its already done in address_parsing
void InitializeReg()
{
    theta = (1.93*bhr_length) + 14;              // according to the paper
    for (int i=0; i<bhr_length; i++)
    {
        WtEntryReg[i] = 0;
        GBHR[i] = 1;
        #ifndef DEBUG
            printf("WtEntry[%d] : %d, GBHR[%d] : %d\n", i, WtEntryReg[i], i, GBHR[i]);
        #endif
    }
}

// This function simply does WtEntryReg[i] * GBHR[i] in a simpler way.
// GBHR is either gonna be 1 or -1. So if GBHR is 1, add the corresponding weight. If -1 subtract the corresponding weight.
int PerceptronOutput()
{
    SumOfProduct = 0;
    FinalSum = 0;
    for (int i = 1; i < bhr_length; i++)
    {
        if(GBHR[i] == 1)
            SumOfProduct = SumOfProduct + WtEntryReg[i];
        else if(GBHR[i] == -1)
            SumOfProduct = SumOfProduct - WtEntryReg[i];
        else
            printf("INVALID GBHR VALUE");

        #ifdef DEBUG
            printf("GBHR[%d] : %d, WtEntryReg[%d] : %d, SumOfProduct : %d\n",i,GBHR[i], i, WtEntryReg[i], SumOfProduct);
        #endif
    }

    FinalSum = WtEntryReg[0] + SumOfProduct;
    #ifdef DEBUG
        printf("FinalSum : %d\n", FinalSum);
    #endif
    return 0;
}

void TrainPerceptron()
{
    #ifdef DEBUG
      printf("THETA : %f\n", theta);
      printf("ABS : %d\n", abs(FinalSum));
    #endif
    if (FinalSum >= 0)
        printf("Predictor Outcome : 1\n");
    else
        printf("Predictor Outcome : -1\n");

    printf("True Prediction : %d\n", TruePrediction);
    if ((signbit(FinalSum) != signbit(TruePrediction)) || (abs(FinalSum) <= theta))
    {
        printf("INSIDE TRAINING LOOP\n");

        //for loop to increase or decrease the weights depending upon prediction of that particular branch
        for (int i = 0; i < bhr_length; i++)
        {
            if(TruePrediction == GBHR[i])
                WtEntryReg[i] = WtEntryReg[i] + 1;
            else
                WtEntryReg[i] = WtEntryReg[i] - 1;

            // limit the extremes of weight
            if (WtEntryReg[i] > 150)
                WtEntryReg[i] = 150;
            else if (WtEntryReg[i] < -150)
                WtEntryReg[i] = -150;

            printf("WtEntryReg[%d] : %d\n",i, WtEntryReg[i]);
        }
    }
}

void UpdateGBHR()
{
    printf("Updated GBHR : ");
    // simply left shigt the GBHR by 1 and append the outcome of the current predictor to GBHR[0]
    for(int i = bhr_length-1; i > 0; i--)
    {
        GBHR[i] = GBHR[i-1];
        printf("%d ",GBHR[i]);
    }
    GBHR[0] = TruePrediction;
    printf("%d\n",GBHR[0]);


}



int main()
{
    int count = 0;
    int correctPrediction=0;
    TruePrediction = 1;
    InitializeReg();
    while (count < 1000)
    {
        printf("****************** ITERATION %d **********************\n", count);
        PerceptronOutput();
        TrainPerceptron();
        UpdateGBHR();
        count++;

        if(signbit(FinalSum) == signbit(TruePrediction))
            correctPrediction++;

        if(count%11 == 0)
          TruePrediction = 1;
        else
          TruePrediction = -1;
        //TruePrediction = -TruePrediction;
    }
    printf("Number of Correct Predictions : %d", correctPrediction);

}
