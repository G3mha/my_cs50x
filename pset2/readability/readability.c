#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");
    
    // Getting the number of letters on the text
    int nLetters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            nLetters++; // always adds one count if the `char` happens to be a letter, through `isalpha`
        }
    }
    
    // Getting the number of words on the text
    int nWords = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            nWords++; // always adds one count after any word ends, because a blank space appears
        }
    }
    nWords++; // the loop will always leave the last word uncounted, so let's add one up
    
    // Getting the number of sentences on the text
    int nSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            nSentences++; // always adds one count after any sentence ends, because a sign of punctuation appears
        }
    }

    // Getting the value out of the Coleman-Liau index
    int Coleman_Liau = round(0.0588 * (nLetters * 100.0 / nWords) - 0.296 * (nSentences * 100.0 / nWords) - 15.8);

    // Deciding what should be the print correspondent to the Coleman-Liau index
    if (Coleman_Liau <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Coleman_Liau >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", Coleman_Liau);
    }
}