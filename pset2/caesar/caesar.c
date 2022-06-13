#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // Checking if there are only 2 parameters passed
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n"); // Showing the correct format for the input
        return 1; // Ending the program with great style
    }

    // Checking if there is no alphabetic chars on the key
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n"); // Showing the correct format for the input
            return 1; // Ending the program with great style
        }
    }
    
    // if the remainder is less than 1, k will be `atoi(argv[1])`
    // if the remainder is greater or equal than 1, k will be the remainder
    int key = atoi(argv[1]) % 26;
    
    // asks for the decripted text and prints, after, the beggining of the encripted
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // Running down each char on the plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // if it's not a alphabetic char, prints it without modification
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }

        // for an alphabetic char, establishes a mechanism that shift the char using the key
        else
        {
            int offset = isupper(plaintext[i]) ? 65 : 97;
            int ci = ((plaintext[i] - offset) + key) % 26;
            int ciphered_position = ci + offset ;
            printf("%c", ciphered_position);
        }
    }

    // Finishing the function
    printf("\n");
    return 0;
}