#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int target_candidate, int loser);

// Main
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    bool valid = false;

    for (int i = 0; i < candidate_count; i++)
    {
        // strcmp return 0 if comparison is true
        valid = !strcmp(name, candidates[i]);
        if (valid == true)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // Catenate ranks[], the first position is the prefered over the
    // others for this voter, then the second is prefered...
    for (int i = 0; i < candidate_count; i++)
    {
        // Complete the matrix preferences[][]  (j = i + 1 to avoid
        // preferences[i][i] and to pass to the next line)
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Avoid to compare a candidate with himself
            if (i == j)     
            {
                j++;
            }
            int test = preferences[i][j] - preferences[j][i];
            if (test > 0)
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Variables to help the comparison
    pair swap_pair;
    int swap_count, compare_1, compare_2;

    do
    {
        swap_count = 0;
        for (int i = 0; i < pair_count; i++)
        {
            // Making the comparison between pair[i] over pair[i + 1] more readable
            compare_1 = preferences[pairs[i].winner][pairs[i].loser];
            compare_2 = preferences[pairs[i + 1].winner][pairs[i + 1].loser];
            if (compare_1 < compare_2)
            {
                swap_count++;
                swap_pair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = swap_pair;
            }
        }
    }
    while (swap_count != 0);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO 
    // Catenate the vector pairs[] looking for cycles. If none, lock the pair.
    // For readability:
    int winner = 0;
    int loser = 0;

    for (int i = 0; i < pair_count; i++)
    {
        // For readability
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        // Call a function to test if there will be a cycle
        if (!is_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // The winner is the candidate who lose to none
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // The winner is the candidate in the locked[j][i] ith COLUMN that have
            // only FALSE. To make it faster and easier we look for a column at
            // a time, if we reach the last line and find no TRUE, this ith column
            // is the winner.
            // ATTENTION!!! i represent the column and j the line
            if (locked[j][i])
            {
                break;
            }
            else if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]); 
            }
        }
    }
    return;
}

// is_cycle will recursively look for each candidate on locked[][]
bool is_cycle(int target_candidate, int loser)
{
    // To look for cycles, we need to search through the matrix locked[][] before lock a
    // target_candidate on it.
    // If the loser wins the target_candidate, there's a cycle.
    // If anyone who loses to the loser wins the target, there's a cycle.
    // So we need to catenate every loser and every loser's loser looking for cycles.
    // Look for cycles on lock_pairs matrix: 
    // - the target_candidate is a candidate we want to lock
    // - the loser is a variable candidate, depending if locked[winner][loser] is true
    // - if it is true the function will call itself and look for cycles with the new loser
    // - return true if there's a cycle

    bool cycle = false;

    for (int i = 0; i < candidate_count; i++)
    {
        // Avoiding to test a candidate with himself
        if (i == loser)
        {
            i++;
        }

        // If there's a candidate i who wins the loser (locked[loser][i] is true)
        // - If i is the target_candidate, don't lock return true, it's a cycle
        // - Else call is_cycle to look for cycles recursively
        if (locked[loser][i])
        {
            if (i == target_candidate)
            {
                cycle = true;
                break;
            }
            else if (is_cycle(target_candidate, i))
            {
                cycle = true;
                break;
            }
        }
    }
    return cycle;
}
