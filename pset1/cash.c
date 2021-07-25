#include <stdio.h>
#include <cs50.h>
#include <unistd.h> // to use sleep function
#include <math.h>  // so I can use round function


/////////////////////////// this is a program that count the number of coins remaining//////////////////////////


int main(void)
{

    float change;

    do
    {
        change = get_float("change owned: ");   // ask the user for change remaining
    }
    while (change < 0);



    float change_in_cents = round(change * 100);   // to round the user input

    // printf("cents= %i\n" ,change_in_cents);

    int number_of_coins = 0;  // the number of coins needed, this value is just to initialize the variable

    while (change_in_cents > 0)
    {
        if (change_in_cents >= 25)  // first step, finesh the quarter statge
        {
            change_in_cents -= 25;

            number_of_coins++;
        }

        else if (change_in_cents >= 10)  //  finesh the dime (10 cents) stip
        {
            change_in_cents -= 10;

            number_of_coins++;
        }

        else if (change_in_cents >= 5)   //  finesh the nikkle (5 cents) stip
        {
            change_in_cents -= 5;

            number_of_coins++;
        }

        else if (change_in_cents >= 1)   //  finesh the pinny (1 cent) stip
        {
            change_in_cents -= 1;

            number_of_coins++;
        }


    }

    printf("change in cents= %f  , no of coins= %i \n", change_in_cents, number_of_coins);
}
