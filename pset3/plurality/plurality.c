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
    bool c=false;
    for (int i=0; i<candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name)==0)
        {
            c=true;
            candidates[i].votes++;
            break;
        }
    }
    return c;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO

    int temp=0; // temprory variable to use in switching elments inside array
    for (int i=0; i<candidate_count; i++)
    {
        for (int j=i; j<candidate_count; j++)
        {
            if(candidates[i].votes<candidates[j].votes)
            {
                temp=candidates[i].votes;
                candidates[i].votes=candidates[j].votes;
                candidates[j].votes=temp;
            }
        }
    }

    // 2) take the largest item -the first- from votes array and copy it to another empty array


    printf ("%s\n",candidates[0].name);   // print the name associated with the largest vote

    for (int i=1; i<candidate_count; i++)    // iterate over the candidates arrays
    {
        if (candidates[0].votes==candidates[i].votes)   // determine if the following candidates votes is equal to the largest candidates
        {
            printf("%s\n",candidates[i].name);    // print the equal largest

        }
    }

    return;
}

