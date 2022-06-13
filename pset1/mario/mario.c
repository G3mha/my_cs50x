#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int height;
    do 
    {
        height = get_int("Height: "); //prompting for the block height
    }
    while (!(height >= 1 && height <= 8)); //restricting the height from 1 up to 8, inclusive
    
    //creating a "nest" loop
    for (int i = 1; i <= height; i++) //each loop represents a blockline
    {
        for (int j = 0; j < height - i; j++) //each loop  represents the amount of spacessdaajnhgk in a line
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++) //each loop  represents the amount of blocks in a line
        {
            printf("#");
        }
        printf("\n");
    }
}