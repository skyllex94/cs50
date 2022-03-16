#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int getInt;
    do
    {
        getInt = get_int("Height: ");
    }
    while ((getInt < 1) || (getInt >= 9)) ;

    // Increment and decrement variables for keeping
    // for adding and subtacting the hashes and spaces
    int decrement = getInt - 1;
    int increment = 1;

    for(int i = 0; i < getInt; i++)
    {
        // Iterating the amount of empty spaces
        for(int j = 0; j < decrement; j++)
        {
            printf(" ");
        }
        // Iterating the hashes and middle empty space
        for (int v = 0; v < increment; v++)
        {
            printf("#");
            if (v == increment - 1)
            {
                printf("  ");
            }
        }
        // Iterating the amount of final needed pound signs to finish the pyramid
        for (int x = 0; x < increment; x++)
        {
            printf("#");
        }

        printf("\n");
        decrement--;
        increment++;
    }
}