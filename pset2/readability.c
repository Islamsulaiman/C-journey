#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    // formula is, ( index = 0.0588 * L - 0.296 * S - 15.8 ) , (grade = index to the nearest integer )

    string paragraph = get_string ("insert your paragraph please \n"); // get the paragraph from the user


    //  1) get the number of letters in all the paragraph

    double exact_L =0; // the exact no. of letters in the whole program

    for (int i =0, n=strlen(paragraph); i<n; i++)  // to loop over all the character, count only the letters
    {
        if ((int) paragraph[i] <=90 && (int) paragraph[i] >=65)  // to get the uppercase letters
        {
            exact_L++;                                           // increase the counter
        }
        else if ((int) paragraph[i] <=122 && (int) paragraph[i] >=97)  // to get the lowercase letters
        {
            exact_L++;
        }
    }
    printf("%f letter(s)\n",exact_L);


    //  2) get the no of words in the paragraph to find how many letters in 100 words.

    double exact_W =0; // the exact no. of words in the whole program

    for (int i =0, n=strlen(paragraph); i<n; i++)  // to loop over all the character, count only the whitespaces to count the number of words
    {
        if ((int) paragraph[i] ==32)  // to get the whitespace character
        {
            exact_W++;                                           // increase the no of words
        }
    }

    exact_W++;                                                  // to add the last word

    printf("%f word(s)\n",exact_W);

    // 3) get L (its no of letters in 100 words),  L = (exact_L*100)/exact_W

    double L = (exact_L*100)/exact_W ;
    printf("L = %f\n",L);


    // 4) get the no sentances, every sequence of characters that ends with a (.) or a (!) or a (?) to be a sentence.

    double sentances =0; // the exact no. of words in the whole program

    for (int i =0, n=strlen(paragraph); i<n; i++)  // to loop over all the character, count only the whitespaces to count the number of words
    {
        if ((int) paragraph[i] == 33|| (int) paragraph[i]==46|| (int) paragraph[i] ==63)  // to get (.)or(!) or (?) characters
        {
            sentances++;                                           // increase the no of sentances
        }

    }

    printf("%f sentance(s)\n",sentances);



    // 5) get the avarage no of sentences per 100 words.

    double S = (sentances*100)/exact_W ;
    printf("S = %f\n",S);


    // 6) apply the formula to get index and round to the nearest integer to get grade:

    // float grade =round((0.0588*L)-(0.296*S)-15.8);
    float grade =(0.0588*L)-(0.296*S)-15.8;
    printf("Grade %f\n", grade);


    // 7) conditions for output the grade

    if (grade>16)
    {
        printf ("Grade 16+\n");
    }
    else if (grade<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n",grade);
    }

}
