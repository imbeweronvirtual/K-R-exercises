#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int cmp(const void *a, const void *b);
bool find_path(int current, int target);

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
    voter_count = get_int("Number of voters: ");

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
    for (size_t i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
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
    /*
    Alice = 2
    Bob = 0
    Charlie = 1
    j == 2

    preferences[2][0] += 1;
    preferences[2][1] += 1;

    preferences[0][1] += 1;
    ranks = {Alice, Bob, Charlie}
    */

    for (size_t i = 0; i < candidate_count - 1; i++)
    {
        for (size_t j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (size_t i = 0; i < candidate_count; i++)
    {
        for (size_t j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count++].loser = j;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), cmp);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (size_t i = 0; i < pair_count; i++)
    {
        if (!find_path(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (size_t i = 0; i < candidate_count; i++)
    {
        for (size_t j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }
            if (j + 1 == candidate_count)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }

    return;
}

// Compare function for qsort() stdlib function
int cmp(const void *a, const void *b)
{
    const pair *a_struct_ptr = (const pair *)a;
    const pair *b_struct_ptr = (const pair *)b;

    unsigned int a_diff = preferences[a_struct_ptr->winner][a_struct_ptr->loser];
    unsigned int b_diff = preferences[b_struct_ptr->winner][b_struct_ptr->loser];

    return (a_diff < b_diff) - (a_diff > b_diff);
}

// Returns true if a path creates a cycle between current and target
bool find_path(int current, int target)
{
    if (current == target)
    {
        return true;
    }

    for (size_t i = 0; i < candidate_count; i++)
    {
        if (locked[current][i])
        {
            if (find_path(i, target))
            {
                return true;
            }
        }
    }

    return false;
}
