#include <stdio.h>
#include<cs50.h>
int get_Height() ;
int main()
{
    int n = get_Height();
    int   i,  j, k, l;
    for (i = 1 ; i <= n ; i++)    // this for loop will create first stair pattern
    {
        for (k = n - i ; k >= 1 ; k--)
        {
            printf(" ");     // space before the #
        }
        for (j = 1 ; j <= i ; j++)
        {
            printf("#");
        }
        printf("  ");    // this space give space between two stair pattern
        for (l = 1 ; l <= i ; l++)    // this loop will creat second stair pattern
        {
            printf("#");
        }
        printf("\n");
    }

}


int get_Height()
{
    int n;
    do
    {
        n = get_int("Enter the Height: "); // input the height of stairs
    }
    while (n < 1 || n > 8);
    return n;
}
