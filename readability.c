#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int calc_readability(float, float, float);

// Main function
int main(void)
{
    int numberOfWords = 1; // Number of words is the number of spaces +1
    int numberOfLetters = 0;
    int numberOfSentences = 0;
    int index = 0;

    string text = get_string("Text: ");

    for (int i = 0; text[i] != '\0'; i++)
    {
        char charToTest = text[i];

        // Is it a letter?
        if (isalpha(charToTest))
        {
            numberOfLetters++;
        }
        // Is it a space?
        else if (charToTest == 32) // If charToTest is space there's a word ahead.
        {
            numberOfWords++;
        }
        // Is it punctuation?
        else if ((charToTest == 46) || (charToTest == 33) || (charToTest == 63))
        {
            numberOfSentences++;
        }
    }

    index = calc_readability(numberOfLetters, numberOfWords, numberOfSentences);

    // Printing the result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %i\n", (int)index);
    }
    else
    {
        printf("Grade 16+\n");
    }

    return 0;
}

// Function declarations

int calc_readability(float letters, float words, float sentences)
{
    float l = 0.00, s = 0.00, index = 0.00;

    l = 100 * (letters / words);

    s = 100 * (sentences / words);

    // Calculating the Coleman-Liau formula
    index = 0.0588 * l - 0.296 * s - 15.8;

    // Rounding the index
    //if ((index - (int)index) < 0.5)
    // {
    //     index = floor(index);
    // }
    // else
    // {
    //     index = ceil(index);
    // }
    return round(index);
}
