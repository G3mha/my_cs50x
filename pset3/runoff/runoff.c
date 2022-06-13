#include <string.h>
#include <cs50.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // For each candidate, if his name isn't the given name, changes his preferences to `i`
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i].name, name))
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop inside the other, to go around all preferences
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if the candidate isn't eliminated, adds one to the count
            if (!candidates[preferences[i][j]].eliminated)
            {
                (candidates[preferences[i][j]].votes)++;
                break; // go another round on the `i` for
            }
        }
    }
    
    // We are in a void, so returns nothing
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Defining the value for the majority, that is half of the votes plus one
    int majority = (voter_count / 2) + 1;
    
    // Loop that check all the candidates, and if one received votes equal or more than majority, prints him as the winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    
    // Otherwise, prints nothing and returns False
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialiazing the minimum amount of votes
    int min = INT_MAX;
    
    // Loop that runs all remaining candidates and checks which has the minimum amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Setting up all the regulators
    int candidates_remaining = 0;
    int candidates_w_minimum_votes = 0;
    
    // Loop that counts the number of remaining candidates and the ones with the minimum amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            candidates_remaining++;
            if (candidates[i].votes == min)
            {
                candidates_w_minimum_votes++;
            }
        }
    }
    
    // if all the remaining candidates have the minimum amount of votes each, returns `True`, otherwise `False`
    return candidates_remaining == candidates_w_minimum_votes;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop that eliminates every candidate with the minimum number of votes among them all
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    
    // We are in a void, so returns nothing
    return;
}
