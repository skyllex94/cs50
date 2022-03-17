#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float get_num_of_letters(string text);
float get_num_of_words(string text);
float get_num_of_sentences(string text);

int main(void)
{

    string text = get_string("Enter text: ");
    float numOfLetters = get_num_of_letters(text);
    float numOfWords = get_num_of_words(text);
    float numOfSentences = get_num_of_sentences(text);

    float numLettertoNumWords = numOfLetters / numOfWords;
    float letterDividedByWords = 0.0588 * (numOfLetters / numOfWords * 100.00);

    float numSenToNumWords = numOfSentences / numOfWords;
    float equationSentence = 0.296 * (numOfSentences / numOfWords * 100.00);

    float index = (letterDividedByWords - equationSentence) - 15.8;

    // printf("Number of letters in the text: %.0f\n", numOfLetters);
    // printf("Number of words: %.0f\n", numOfWords);
    // printf("Number of sentences: %.0f\n", numOfSentences);

    int indexToInt = round(index);

    if (indexToInt < 0)
    {
        printf("Before Grade 1\n");
    } else if (indexToInt > 16)
    {
        printf("Grade 16+\n");
    } else
    {
        printf("Grade %i\n", indexToInt);
    }
}

// Get the number of letters from the text and return it
float get_num_of_letters(string text)
{
    int letterCount = 0;
    int numOfSpaces = 0; // the code can be optimized with pointers
    // of structures in order to minimaze the necessity of more than one loop
    // by returning the numOfSpaces to count the words like this.


    // Iterate throug the chars
    for (int i = 0; i < strlen(text); i++)
    {
        // Choose to add to letterCount only when a char
        // is of alphabethical value
        int toLowerCase = tolower(text[i]);
        if (isspace(text[i]) || !isalnum(text[i]))
        {
            numOfSpaces++;
        }
        else if (isalpha(toLowerCase))
        {
            letterCount++;
        }
    }
    return letterCount;
}


// Get the number of words from the text and return it
float get_num_of_words(string text)
{
    int wordCount = 0;
    // Determine when you see a char of space and word +1
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            wordCount++;
        }
    }
    return (wordCount + 1);
}

// Get the number of sentences from the text and return it
float get_num_of_sentences(string text)
{
    int sentenceCount = 0;
    // Iterate through all of the character and simply determine
    // if the char is a dot, question mark or exclamation mark
    for (int i = 0; i < strlen(text); i++)
    {
        int letterNum = tolower(text[i]);
        if (letterNum == 46 || letterNum == 33 || letterNum == 63)
        {
            sentenceCount++;
        }
    }

    return sentenceCount;
}