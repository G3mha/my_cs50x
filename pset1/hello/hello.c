#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks the name of the person
    string name = get_string("What's your name?\n");
    
    // Prints greetings to the user
    printf("hello, %s\n", name);
}