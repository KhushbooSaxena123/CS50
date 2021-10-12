#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
int f(string text);
int g(string text);
int h(string text);
int main()
{
    string txt = get_string("Text: ");
    // printf("%i, %i, %i\n", f(txt), g(txt), h(txt));
    float L = f(txt) * 100 / (float) g(txt);         // Average number of letters per 100 words.
    float S = h(txt) * 100 / (float) g(txt) ;          // Average number of sentences per 100 words.
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //printf("%f\n", 0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)                    // For grade lower than 1.
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= index && index <= 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index > 16)            // For grade greater than 16.
    {
        printf("Grade 16+\n");
    }

}


int f(string text)       // function for print out number of latters in thse text.
{
    int i, n, letters = 0;
    n = strlen(text);
    for (i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}


int g(string text)      // function will calculate number of words in text
{
    int i, n, count = 0, words;
    n = strlen(text);
    for (i = 0; i < n; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    words = count + 1;
    return words;
}


int h(string text)    // function for finding number of sentences
{
    int i, n, count = 0;
    n = strlen(text);
    for (i = 0; i < n; i++)
    {
        if ((text[i]) == '!' || text[i] == '?' || text[i] == '.')
        {
            count++;
        }
    }
    return count;
}
