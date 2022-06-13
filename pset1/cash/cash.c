#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //prompting for a correct input
    float dollars;
    do
    {
        dollars = get_float("Change owed: "); //asking for the change
    }
    while (dollars < 0);

    //setting up all the main variables
    int cents = round(dollars * 100); //transforming the change from float to int
    int coins = 0; //initialization of the wanted variable

    //setting up the possible changes to be used in an array
    int all_possible[] =  {25, 10, 5, 1}; //initialization of array
    
    //setting up the for loop
    int i = 0; //loop regulator
    for (i = 0; i < 4; i++)
    {
        int coin = all_possible[i]; //getting the coin to be used in this loop round
        while (cents - coin >= 0)
        {
            cents -= coin;
            coins++; //adding a coin for each while round
        } //end of while loop
    } //end of for loop
    
    //printing the least possible amount of coins
    printf("%d\n", coins);
}