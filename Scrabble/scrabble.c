#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");


    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare the scores from both
    // of the integers returned and conclude the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Computing and returning score from string

    // Initializing two arrays from which to compare the values as we check the index and assign the value of the points from the letter
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int letters[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
    int wordSum = 0;

    // Looping each letter
    for (int i = 0; i < strlen(word); i++)
    {
        // Asigning it to a char variable
        char currentLetter = word[i];
        // Initializing an int variable to take the ASCII value of the lower case value of the given char
        int currentLetterToNum = tolower(currentLetter);
        // printf("%c\n", currentLetter);

        // Looping through each letter from the array letters[]
        for (int j = 0; j < letters[j]; j++)
        {
            // Once the letter number maches the current letter
            // it will add the value of the same index in the point array into wordSum
            if (currentLetterToNum  == letters[j])
            {
                wordSum = wordSum + points[j];
            }
        }
    }
    // After the total amount is calculated from iterating throw all the letters of the word, it will return the total int value
    return wordSum;
}
