#include<stdio.h>
#include<cs50.h>
int main()
{
    int start_size, end_size, n, i;
    do                                  // This loop will ask to enter starting population size until starting population size is greater than 9.
    {
        start_size = get_int("Enter starting population size : \n");
    }
    while (start_size < 9);

    do                          // This loop will ask to enter ending population size until ending population size is greater than starting population size.
    {
        end_size = get_int("Enter ending population size : \n");
    }
    while (end_size < start_size);
    n = start_size;
    i = 0;
    if (n == end_size)             // For same starting and ending population size.
    {
        printf("Years: %i\n", i);  // Therefor here number of years is zero.
    }
    else
    {
        do
        {
            n += n / 3 - n / 4 ;  // n will calculate populatiion of next year.
            i++;                  // i is number of years.
        }
        while (n < end_size);
        printf("Years: %i\n", i);
    }
}
