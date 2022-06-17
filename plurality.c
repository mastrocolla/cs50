#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sort_candidates(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}



// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    bool validation = false;
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare the name of the candidate in the array, return 0 if equal (true)
        validation = strcmp(name, candidates[i].name);  
        if (!validation)
        {
            // If candidate exists add a vote and exit the for loop.
            candidates[i].votes += 1;
            break;
        }
    }
    return !validation;
}



// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    sort_candidates();
    printf("%s\n", candidates[candidate_count].name);
    // Checking out if there's a tie
    // candidate_count - 1 is the second most voted.
    // Keep comparing until there's no tie.
    for (int i = candidate_count - 1; i > 0; i--)
    {
        if (candidates[i].votes == candidates[candidate_count].votes)
        {
            printf("%s\n", candidates[i].name);
        }
        else
        {
            break;
        }
    }
    return;
}



// Sorting candidates from less voted to the most one
void sort_candidates(void)
{
    int swap_count;
    candidate temporary;
    do
    {
        swap_count = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes > candidates[i + 1].votes)
            {
                temporary = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = temporary;
                swap_count++;
            }
        }
    }
    while (swap_count != 0);
    return;
}
