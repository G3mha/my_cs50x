#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Early call for the function
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Possible turnouts
    string p1_win = "Player 1 wins!";
    string p2_win = "Player 2 wins!";
    string tie = "Tie!";

    // Evaluating the turnouts for a winner print
    if (score1 > score2)
    {
        printf("%s\n", p1_win);
    }
    else if (score2 > score1)
    {
        printf("%s\n", p2_win);
    }
    else 
    {
        printf("%s\n", tie);
    }

}

int compute_score(string word)
{
    int points = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {   
            // Getting the points for each letter and adding to the total points
            int letter_index = toupper(word[i]) - 'A';
            points += POINTS[letter_index];
        }
    }
    return points;
}