#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv [])
{
    // step 1) get the key as command line arg. and convert the argument from string format to int format


    if (argc != 2 )
    {
        printf ("./caesar key\n");
        return 1;
    }

    for (int i =0, n=strlen(argv[1]); i<n; i++)
    {

        if (isalpha(argv[1][i]) != 0) // if key is alphapetical, loop over each carechter in the insertwd key to check if theres alpha

        {
            printf("./caesar key (the key is alpha)\n"); // if the caracter is alpha
            return 1;
        }
    }

    int k = atoi(argv[1]);  // and convert the argument from string format to int format


    // step 2) get the plaintext from user

    string plaintext = get_string("inter your plain text\n");


    // step 3) Encypher text using key value

    int n = strlen(plaintext);  // no. of charechter in plaintext

    char cypher[n];           // array of chars to save the cyphered text with the no. of element equal to no of character in plaintext

    for (int i=0; i<n; i++)
    {
        if (isalpha(plaintext[i]) == 0 )  // if the charechter not alpha, do the folowing
        {
            cypher[i] = plaintext[i];    // add the charachter direct to the array without  cyphring
        }
        else if (isalpha(plaintext[i]) != 0 )   // if the charechter is alpha
        {
            if (isupper(plaintext[i]) !=0)  // check if upper case
            {
                cypher[i]= (((plaintext[i]-65) + k) % 26) + 65 ;   // 1) convert to alpha index 2) apply the formula 3)convert back to ASCII indexing
            }
            else if (islower(plaintext[i]) !=0)  // check if lower case
            {
                cypher[i]= (((plaintext[i]-97) + k) % 26) + 97 ;   // 1) convert to alpha index 2) apply the formula 3)convert back to ASCII indexing
            }
        }
    }

    printf ("ciphertext: ");
    for (int i=0; i<n; i++)
    {
        printf("%c",cypher[i]);
    }
    printf("\n");
    return 0;
}
