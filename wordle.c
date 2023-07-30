#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    // TODO #1 START
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }
    // TODO #1 END
    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
    // TODO #2 START
    int inputArg;

    if (argv[1][1] != 0) // if input 52, because 52 is a string , 52 => 5 2 null then argv[1][1] == (char) '2' or (dec) 50.
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }
    // if (0){}
    else
    {
        inputArg = argv[1][0] - 48;
    }

    if (inputArg != 5 && inputArg != 6 && inputArg != 7 && inputArg != 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    else
    {
        // printf("%i", EXACT);
        wordsize = inputArg;
    }
    // TODO #2 END
    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        // TODO #4 START
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
            // printf("%i",status[j]);
        }
        // TODO #4 END

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won)
    {
        printf("you won!\n");
        printf("answer is: %s\n", choice);
    }
    else
    {
        printf("sucker!\n");
        printf("answer is: %s\n", choice);
    }
    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    // TODO #3 START

    // do
    // {
    //     guess = get_string("Input a %i-letter word: ", wordsize);
    // }
    // while (strlen(guess) != wordsize);

    guess = get_string("Input a %i-letter word: ", wordsize);
    while (strlen(guess) != wordsize)
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }

    // TODO #3 END

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    // TODO #5 START
    for (int i = 0; i < wordsize; i++) // iterate over each letter of the guess
    {
        for (int j = 0; j < wordsize; j++) // iterate over each letter of the choice
            if (guess[i] == choice[j] && i == j)
            {
                status[i] = EXACT;
                break;
            }
            else if (guess[i] == choice[j] && i != j)
            {
                status[i] = CLOSE;
            }

        score = score + status[i];
    }

    // HINTS
    // iterate over each letter of the guess
    // iterate over each letter of the choice
    // compare the current guess letter to the current choice letter
    // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
    // if it's in the word, but not the right spot, score CLOSE point (yellow)
    // keep track of the total score by adding each individual letter's score from above

    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    // TODO #6 START
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN "%c" RESET, guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW "%c" RESET, guess[i]);
        }
        else
        {
            printf(RED "%c" RESET, guess[i]);
        }
    }
    // TODO #6 END
    printf("\n");
    return;
}
