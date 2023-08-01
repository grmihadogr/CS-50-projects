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
} pair;

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
bool isThereALinkFromLoserToWinner(int loser, int winner);

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

        // printf("%i %i %i ", ranks[0], ranks[1], ranks[2]);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - i - 1; j++)
        {
            preferences[ranks[i]][ranks[i + j + 1]]++;
            // printf("preference [%i][%i] updated tp %i \n", ranks[i], ranks[i+j+1], preferences[ranks[i]][ranks[i+j+1]]);
        }
    }

    // THIS IS MY TEST TO PROVE THE RECORD PREFERENCE IS WORKING
    // for (int k=0; k< candidate_count; k++)
    // {
    //     for (int l=0; l< candidate_count; l++)
    //     {
    //         printf("%i ", preferences[k][l]);
    //     }
    //     printf("\n");
    // }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // printf("winner is %i, loser is %i\n",pairs[pair_count].winner,pairs[pair_count].loser);
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                // printf("winner is %i, loser is %i\n",pairs[pair_count].winner,pairs[pair_count].loser);
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    // To print before sorted pair[];
    //  for(int l=0; l<pair_count; l++)
    //  {
    //      printf("pair %i, winer %i, loser %i, strength %i\n", l, pairs[l].winner, pairs[l].loser, preferences[pairs[l].winner][pairs[l].loser]);
    //  }

    pair tmp;
    for (int j = 0; j < pair_count - 1; j++)
    {
        for (int i = 0; i < pair_count - 1 - j; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                tmp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = tmp;
            }
        }
    }

    // To print after sorted pair[];
    // for(int k=0; k<pair_count; k++)
    // {
    //     printf("pair [%i]: winer %i, loser %i, strength %i\n", k, pairs[k].winner, pairs[k].loser, preferences[pairs[k].winner][pairs[k].loser]);
    // }

    return;
}

// bool hasCircle(int loser, int winner)

// so called hasCircle, the truth is, it is not testing of we have a circle. We just name it this way to make some logic meaning for human.

// the true logic of this has circle is to test , when given a winner and a loser, meaning we want to connect an arrow from winner to loser.
// hence, we need to test if there exist a direct path of indirect path form loser to winner! if there is a path from loser to winner, we return true.

// SO, I propose better call this function
bool isThereALinkFromLoserToWinner(int loser, int winner)
{
    // 1. test direct
    if (locked[loser][winner] == true)
    {
        return true;
    }
    // 2. test indirect connection: i propose, maybe another candidate, we call it point M1 (we will use iteration to go through all the points).
    // if there is a link form loser to M1, then we need to test if there is a link (direct or indirect) from M1 to winner.
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && isThereALinkFromLoserToWinner(i, winner))
        {
            return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!isThereALinkFromLoserToWinner(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // if locked[i][j]== true, this means there is an arrow from i to j; which means j is not the answer.
    // So answer is the col that has no false in locked[candidate_count][candidate_count] array.
    // I need to find the col that are all false.
    for (int col = 0; col < candidate_count; col++)
    {
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == true)
            {
                break;
            }
            else if (row == candidate_count - 1)
            {
                printf("winner is %s\n", candidates[col]);
                return;
            }
        }
    }
    return;
}

//    //this is the index of candidates what has arrow point at them
//     int wronglist[candidate_count];
//     //this is the number of candidates
//     int k=0;
//     for (int i=0; i<candidate_count; i++)
//     {
//         for (int j=0; j<candidate_count; j++)
//         {
//             if (locked[i][j] == true)
//             {
//                 wrongIndexList[k] = j;
//                 k++;
//             }
//         }

//     }
//     for(int l=0; l<candidate_count; l++)
//     {
//         for (int m=0; m<k; m++)
//         if (l != wronglist[m])
//         {
//             printf("winner is %s\n",candidates[l]);
//         }
//     }