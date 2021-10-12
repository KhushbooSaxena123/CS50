#include<stdio.h>
#include<math.h>
#include<cs50.h>
int f(long x);
int g(int y, long z);
int h(int s, long t);
int main()
{
    long  num;
    int N, sum, star_dig;
    num = get_long("Enter card number: ");
    N = f(num);
    star_dig = num / (pow(10, N - 2)); // starting digit
    sum = g(N, num) + h(N, num);   //  Adding both the sum togather.
    if (sum % 10 == 0)     // Condition for checksum.
    {
        if ((star_dig == 34 || star_dig  == 37) && N == 15)   // Condition for American Express Card.
        {
            printf("AMEX\n");
        }
        else if ((star_dig == 51 || star_dig == 52 || star_dig == 53 || star_dig == 54 || star_dig == 55)
                 && N == 16)  // Condition for Master Card.
        {
            printf("MASTERCARD\n");
        }
        else if ((star_dig / 10) == 4 && (N == 13 || N == 16))  // Condition for VISA
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


int f(long x) // This function will calculate the number of digits in Card.
{
    int count = 0;
    do
    {
        x = x / 10;
        count ++ ;
    }
    while (x > 0);
    return count;
}


int g(int y, long z)
{
    // This function will  multiply every other digit by 2,
    //starting with number's second-to-last digit ,add those product's digit togather.
    int  i, sum1 = 0, ls, sec_ls, mul;
    for (i = 1 ; i <= y / 2 ; i++)
    {
        ls = z % 100;
        sec_ls = ls / 10;
        mul = 2 * sec_ls;
        sum1 += (mul / 10 + mul % 10);
        z = z / 100;
    }
    return sum1;
}

int h(int s, long t) //  This function will give ,sum of ther digit that were not multiplied by 2.
{
    int sum2 = 0, j;
    if (s % 2 == 0)
    {
        for (j = 1 ; j <= s / 2 ; j++)
        {
            sum2 += t % 10;
            t = t / 100;
        }
    }
    else
    {
        for (j = 1 ; j <= (s / 2) + 1 ; j++)
        {
            sum2 += t % 10;
            t = t / 100;
        }
    }
    return sum2;
}
