/*This is my version of casino slots*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RANDNUMLIM 3

typedef enum
{
    FALSE ,TRUE
}boolean;


//Function prototypes
void promptWelcomeScreen(float *startMoney);
void playingProcedure(float *totalMoney, float *moneyEarned, float *moneyLost, float *roundMoney,float *multiplier, int randNum[]);
boolean checkWin(int randNum[]);
void editMoney(float *totalMoney, float *moneyEarned, float *moneyLost, float roundMoney, float multiplier, boolean win);
void contPlay(char *decision);


int main()
{
    int randNum[RANDNUMLIM];
    float startMoney, roundMoney;
    float moneyEarned, totalMoney, multiplier, moneyLost;
    char decision;
    boolean win;


    moneyEarned = moneyLost = 0;

    while(1)
    {
        promptWelcomeScreen(&startMoney);
        totalMoney = startMoney;

        while(totalMoney > 0)
        {
            playingProcedure(&totalMoney, &moneyEarned, &moneyLost, &roundMoney, &multiplier, randNum);
            win = checkWin(randNum);
            editMoney(&totalMoney, &moneyEarned, &moneyLost, roundMoney, multiplier, win);

            printf("Total money until now: %.2f\n", totalMoney <= 0 ? 0 : totalMoney);
            printf("Money Earned until now: %.2f\n", moneyEarned);
            printf("Money Lost until now: %.2f\n", moneyLost);

            if(totalMoney <= 0)
            {
                printf("Unfortunately the total amount of money has ended...\nDo you want to insert more money?(Y/N)\n");
                contPlay(&decision);

                if(decision == 'n' || decision == 'N')
                {
                    printf("Thank you for playing!!!\n");
                    break;
                }
                else
                    break;
            }

            contPlay(&decision);
            if(decision == 'n' || decision == 'N')
            {
                printf("Thank you for playing!!!\n");
                break;
            }
        }

        if(decision == 'n' || decision == 'N')
            break;
    }

    printf("Total amount of money: %.2f\n", totalMoney <= 0 ? 0 : totalMoney);
    printf("Total money earned: %.2f\n", moneyEarned);
    printf("Total money lost: %.2f\n", moneyLost);

    return 0;
}


//Function definition
void promptWelcomeScreen(float *startMoney)
{
    printf("Welcome to Slots.\nPlease give the amount of money that you want to play with: ");
    do
    {
        scanf("%f", startMoney);
        if(*startMoney <= 0)
            printf("Please give valid data. You cannot play with negative amount of money...\nTry again.\nPlease give the amount of money that you want to play with: ");

    }while(*startMoney <= 0);
}


void playingProcedure(float *totalMoney, float *moneyEarned, float *moneyLost, float *roundMoney,float *multiplier, int randNum[])
{

    printf("Please enter the amount of money for this round: ");
    do
    {
        scanf("%f", roundMoney);
        if(*roundMoney <= 0 || *roundMoney > *totalMoney)
            printf("You cannot play with that amount of money...Try again.\nPlease enter the amount of money for this round: ");
    }while(*roundMoney <= 0 || *roundMoney > *totalMoney);


    printf("Please enter the multiplier for winning.\n(For example if you want to double your winning amount enter 2): ");
    do
    {
        scanf("%f", multiplier);
        if(*multiplier < 0)
            printf("You cannot play with negative multiplier...\nThe minimum multiplier value is 0 in order to win or lose"
                   ,"the same amount of money and not bigger...\nTry again\nPlease enter the multiplier for winning.\n"
                   ,"(For example if you want to double your winning amount enter 2): ");

    }while(*multiplier < 0);

    srand(time(NULL));

    for(int i = 0; i < RANDNUMLIM; i++)
    	randNum[i] = rand() % 8;

}


boolean checkWin(int randNum[])
{
    printf("The numbers are: ");
    for(int i = 0; i < RANDNUMLIM; i++)
        printf("%4d ", randNum[i]);
    printf("\n");

    if(randNum[0] == randNum[1] && randNum[0] == randNum[2] && randNum[1] == randNum[2])
        return TRUE;
    return FALSE;
}


void editMoney(float *totalMoney, float *moneyEarned, float *moneyLost, float roundMoney, float multiplier, boolean win)
{
     if(win)
        {
            printf("YOU WIN!!!\n");
            (*moneyEarned) += (roundMoney * (multiplier > 0 ? multiplier : 1));
            (*totalMoney) += (roundMoney * (multiplier > 0 ? multiplier : 1));
        }
        else
        {
            printf("Unfortunately you did not win this round...\n");
            (*moneyLost) += (roundMoney * (multiplier > 0 ? multiplier : 1));
            (*totalMoney) -= (roundMoney * (multiplier > 0 ? multiplier : 1));
        }
}


void contPlay(char *decision)
{
    printf("Continue playing?(Y/N): ");
        do
        {
            scanf(" %c", decision);
            while((getchar()) != '\n');

            if(*decision != 'Y' && *decision != 'y' && *decision != 'N' && *decision != 'n')
                printf("Please enter a valid answer.\nContinue playing?(Y/N): ");
        }while(*decision != 'Y' && *decision != 'y' && *decision != 'N' && *decision != 'n');
}
