#include <cs50.h>
#include <stdio.h>
#include <string.h>

int calculate_long(long number);

int main(void)
{
    long number = get_long("Number: ");
    int length = calculate_long(number);

    long exponent = 1;
    long remainder = 10;
    int checksum_odd = 0;
    int checksum_even = 0;
    for (int i = 0; i < length; i++)
    {
        int cur_num = (number % remainder) / exponent;
        int exponent_length = calculate_long(exponent);
        if (exponent_length % 2 == 1)
        {
            checksum_odd += cur_num * 2;
        }
        else
        {
            checksum_even += cur_num;
        }
        exponent *= 10;
        remainder *= 10;
        // printf("%i_\n", cur_num);
    }
    int final_check = checksum_odd + checksum_even;
    if (final_check % 10 == 0)
    {
        if (length == 15)
        {
            printf("AMEX\n");
        }
        else if (length == 16)
        {
            printf("MasterCard\n");
        }
        else if (length == 13 || length == 16)
        {
            printf("Visa\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int calculate_long(long number)
{
    int digit = 0;
    int count = 0;

    while (number >= 10)
    {
        number = number/10;
        count++;
    }
    digit = count + 1;
    return digit;
}