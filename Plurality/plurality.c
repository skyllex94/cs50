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
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

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
        bool voteResult = vote(name);

        // Check for invalid vote
        if (voteResult == false)
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
    for (int i = 0; i < candidate_count; i++)
    {
        string currentName = candidates[i].name;
        if (strcmp(currentName, name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winning_vote = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winning_vote)
        {
            winning_vote = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (winning_vote == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;

    // Bubbling up Sorting in an ascending order
    // for (int v = 0; v < candidate_count; v++)
    // {
    //     for (int i = 0; i < candidate_count - 1; i++)
    //     {
    //         if (candidates[i].votes > candidates[i + 1].votes)
    //         {
    //             string swap_name = candidates[i + 1].name;
    //             int swap_votes = candidates[i + 1].votes;

    //             candidates[i + 1] = candidates[i];
    //             candidates[i].name = swap_name;
    //             candidates[i].votes = swap_votes;
    //         }
    //     }
    // }
}
