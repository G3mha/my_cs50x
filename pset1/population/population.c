#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int initial = get_int("Start size: ");
    while (initial < 9)
    {
        initial = get_int("Start size: ");
    }

    // Prompt for end size
    int final = get_int("End size: ");
    while (initial > final)
    {
        final = get_int("End size: ");
    }
    
    // Calculate number of years until we reach threshold
    int current = initial;
    int years = 0;
    while (current < final)
    {
        current = current - current / 4 + current / 3;
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}