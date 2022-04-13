#include <cs50.h>
#include <stdio.h>
#include <string.h>

int calculate_long(long number);
int calculate_int(int cur_num);

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
            checksum_odd += cur_num;
        }
        else
        {
            if (cur_num >= 5)
            {
                cur_num = cur_num * 2;
                int sum_num = calculate_int(cur_num);
                checksum_even += sum_num;
            }
            else
            {
                checksum_even += cur_num * 2;
            }
        }
        exponent *= 10;
        remainder *= 10;
        // printf("%i_\n", cur_num);
    }
    int final_check = checksum_odd + checksum_even;
    if (final_check % 10 == 0)
    {
        int first_num = (number % (remainder / 10)) / (exponent / 10);
        int second_num = (number % (remainder / 100)) / (exponent / 100);
        if (length == 15 && first_num == 3 && (second_num == 4 || second_num == 7))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && first_num == 5 && (second_num == 1 || second_num == 2 || second_num == 3 || second_num == 4 || second_num == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && first_num == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
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
        number = number / 10;
        count++;
    }
    digit = count + 1;
    return digit;
}

int calculate_int(int cur_num)
{
    int sum = (cur_num % 10) / 1;
    sum = sum + ((cur_num % 100) / 10);
    return sum;
}