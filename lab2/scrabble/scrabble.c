#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");


    //  calculating score both words.
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    //  Print the winner.
    if (score1 > score2)   // This is condition for player 1 to win.
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)  // This is condition for player 2 to win.
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n"); // If both players have same score then game ties.
    }


}

int compute_score(string word)   // This function Compute and return score for string
{
    int n, i, count = 0, sum = 0;
    char j;
    n = strlen(word);
    for (i = 0; i < n; i++)
    {
        for (j = 'a'; j <= 'z'; j++)
        {
            if (isupper(word[i]))
            {
                if (word[i] == toupper(j))
                {
                    sum += POINTS[count];
                }

            }
            else if (word[i] == j)
            {
                sum += POINTS[count];
            }
            count++;
        }
        count = 0;
    }
    return sum;

}
