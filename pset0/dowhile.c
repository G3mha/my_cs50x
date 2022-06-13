#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // DoWhile will execute the code once, and THEN check for the requirements 
    int n;
    do
    {
        n = get_int("Type a positive number: ")
    }
    while (n < 1);
    return n;
}