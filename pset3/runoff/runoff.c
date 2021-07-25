#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    // 1) check if the vote is valid
    for(int i=0; i<candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name)==0)
        {

            preferences[voter][rank]= i;     // create the 2d array according to the cadidates indexes.
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
int ite;    //to store the iteration we are in
void tabulate(void)
{
    // TODO
    if(ite==0)  //this is the first iteration, take voters with no eleminated
    {
        for(int i=0; i<voter_count; i++)    // i= location in voters (rows of 2d array)
        {
            int pref_value=preferences[i][0];   // get the candidate index at this place, the column will always be zero at the first iteration because we will take the first vote for each candidate

            if(candidates[pref_value].eliminated==false)

                candidates[pref_value].votes++;
        }
        ite++;  //to increment the iteration round
    }
    else if(ite>0)  //try remove if statment ////////////////////////////////////////////////////
    {
        for(int i=0; i<voter_count; i++)    // i= location in voters (rows of 2d array)
        {
            for(int j=0; j<candidate_count; j++)
            {
                int pref_value=preferences[i][j];   // get the candidate index at this place, the column will always be zero at the first iteration because we will take the first vote for each candidate

                if(candidates[pref_value].eliminated== false)
                    break;

                if(candidates[pref_value].eliminated==true)
                {
                    for(int k=j; k<candidate_count-j; k++)
                    {
                        int pref_value2=preferences [i][k];

                        if(candidates[pref_value2].eliminated == true)
                            continue;

                        if(candidates[pref_value2].eliminated == false)
                        {
                            candidates[pref_value2].votes ++;
                            break;
                        }
                    }
                }
            }

        }
        ite++;
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int if_last_two=0;

    // 1)check if there's any winner by two scenarios

    // 1.1) if candidates have more than half of the total voter counts
    for (int i=0; i<candidate_count; i++)
    {
        if(candidates[i].votes>voter_count/2)
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
        if(candidates[i].eliminated==false)
            if_last_two++;

    }
    // 2) if there's only two candidates
    if(if_last_two==2)
    {
        int biggest=0;  //initialize two variables to hold 1) no. of votes for the winer 2) name of winner
        string winner;
        for(int i=0; i<candidate_count; i++)    //loop over candidates
        {
            if(candidates[i].eliminated==false)     //if the candidate not eleminated
            {
                if(biggest==candidates[i].votes)    // if the two remaining candidates are tied
                {
                    printf("%s\n%s",winner,candidates[i].name);  //print remaining two tied candidates as winners
                    return true;
                }
                if(biggest<candidates[i].votes)     // if vote no. is bigger than the current biggest
                {
                    biggest=candidates[i].votes;   // assign votes and name of the biggest
                    winner=candidates[i].name;
                }

            }
        }
        printf("%s\n",winner);
        return true;

    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min=MAX_VOTERS;
    for(int i=0; i<candidate_count; i++)
    {
        if(candidates[i].eliminated==false)
        {
            if(min>candidates[i].votes)
            {
                min=candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for(int i=0; i<candidate_count; i++)
    {
        if(candidates[i].eliminated==false)
        {
            if(candidates[i].votes!=min)
            {
                return false;
            }
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for(int i=0; i<candidate_count; i++)
    {
        if(candidates[i].eliminated==false)
        {
            if(candidates[i].votes==min)
            {
                candidates[i].eliminated=true;
            }
        }

    }
    return;
}
