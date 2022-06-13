#include <cs50.h>
#include <stdio.h>

// Prototype
void meow(int n);

int main(void)
{
    meow(3);
}

void meow(int n)
{
    // define the condition, then check the condition, enter the loop, than make the following modification and check again.
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}