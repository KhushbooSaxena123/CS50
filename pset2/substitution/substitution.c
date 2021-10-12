#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
//command line argument to main function where 'argc' is argument count and 'argv' is argument vector.
int main(int argc, string argv[])
{
    int count = 0, count1 = 0;
    if (argc == 2)            // 2nd argument is KEY
    {
        int n = strlen(argv[1]);
        if (n == 26)                // checking if Key has 26 character long
        {
            for (int i = 0; i < n; i++)
            {

                if (isalpha(argv[1][i]))   // check if all the characters are alphabets
                {
                    for (int j = 0; j < i; j++)
                    {
                        if (argv[1][i] == argv[1][j])   //checking if any letter is repeating itself in the key
                        {
                            count++;
                        }
                    }

                }
                else if (isalnum(argv[1][i]))       // checking if there is a number in the key
                {
                    count1++;
                }

            }

            if (count > 0)
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }

            else if (count1 > 0)
            {
                printf("Key must only contain alphabetic characters\n ");
                return 1;
            }
            else
            {
                // If the key is valid, then this else condition will convert the plaintext into cyphertext.
                string text = get_string("plaintext: ");
                printf("\n");
                printf("ciphertext: ");
                int m = strlen(text);
                char cytext[m];
                for (int k = 0; k < m; k++)
                {
                    if (isalpha(text[k]))
                    {
                        if (islower(text[k]))
                        {
                            int count2 = 0;
                            for (char l = 'a'; l <= 'z'; l++)
                            {
                                if (text[k] == l)
                                {
                                    cytext[k] = tolower(argv[1][count2]);   // this will change case of key to according to plaintext to lower case.
                                }

                                count2++;
                            }
                        }
                        else
                        {
                            int count3 = 0;
                            for (char l = 'A'; l <= 'Z'; l++)
                            {
                                if (text[k] == l)
                                {
                                    cytext[k] = toupper(argv[1][count3]);    // this will change case of key to according to plaintext to upper case.
                                }

                                count3++;
                            }
                        }
                    }
                    else
                    {
                        cytext[k] = text[k];
                    }

                    printf("%c", cytext[k]);
                }
                printf("\n");

                return 0;
            }


        }
        else
        {
            printf("Key must contain 26 characters\n");            // if key is not 26 character long then the key is invalid
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");     // if user does not give to command line argument
        return 1;
    }
}





