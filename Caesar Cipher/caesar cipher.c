#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string argument);
char rotate(char currentLetter, int positionsToMove);

int main(int argc, string argv[])
{
    bool varifyDigit = false;

    // exit status if there no input of argument needed for the cipher
    if (argc > 1)
    {
        // functions to return the bool value if the value of the argument is numeric
        varifyDigit = only_digits(argv[1]);
    }

    // If everything good, proceed to cheking if there are no more than 1 argument
    if (varifyDigit == true && argc == 2)
    {
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        // Iterate each character from the text
        for (int i = 0; i < strlen(plaintext); i++)
        {
            // If the char is alphabethical, take the char and cipher it.
            // if not print the non-alphabethical value as the same
            if (isalpha(plaintext[i]))
            {
                // Instantiate a function to take both the current char and position to move
                char currentLetterToChar = rotate(plaintext[i], atoi(argv[1]));
                // Print the ciphered char
                printf("%c", currentLetterToChar);
            }
            else
            {
                char currentNonAlphaValue = plaintext[i];
                printf("%c", currentNonAlphaValue);
            }
        }
        printf("\n");
        return 0;
    }
    // Exit status for any type of error
    printf("Usage: ./caesar key\n");
    return 1;
}

// Functions for checking if there argument is only numerical
bool only_digits(string argument)
{
    bool result = false;
    // Iterate through each char of the acgv[1] string
    for (int i = 0; i < argument[i]; i++)
    {
        if (isdigit(argument[i]))
        {
            result = true;
        }
        else result = false;
    }
    return result;
}

// take input char and return the ciphered char
char rotate(char currentLetter, int positionsToMove)
{
    if (isupper(currentLetter))
    {
        // Zero down the value of the current char
        int zeroDownChar = (int) currentLetter - 'A';
        // Create a new char to add the adjusted char and the positions to move
        int newChar = zeroDownChar + positionsToMove;
        // If the position to move is larger than the end of the alphabet
        // Take the remainder, so you can loop back around and give the cipher char
        if (newChar >= 26)
        {
            newChar = newChar % 26;
        }

        // After getting the char, adding it to the begining value of char
        // so it gives back the correct letter in ASCII
        char adjustedChar = newChar + 'A';
        return adjustedChar;
    }
    else
    {
        // Exact same process for lowercase letter
        int zeroDownChar = (int) currentLetter - 'a';
        int newChar = zeroDownChar + positionsToMove;

        if (newChar >= 26)
        {
            newChar = newChar % 26;
        }

        char adjustedChar = newChar + 'a';
        return adjustedChar;
    }
}