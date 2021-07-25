#include <stdio.h>
#include <cs50.h>
#include <unistd.h>


////////////////////////  mario program  (right or left justified)  ////////////////////////////////



int main(void)
{
    int number_of_rows ;
    do
    {
        number_of_rows = get_int ("insert the number of rows.\nfor your own safty and time, enter a number within (1-8) \n");
    }
    while (number_of_rows < 1 || number_of_rows >8);


    int y=1;
    for (int i=0; i<number_of_rows; i++)
    {

        int s = (number_of_rows-y);  // number of blank spaces before the # symbol in every line, because the block will start at the right side and there is some space before the # symbol.
        int d = (number_of_rows-s);  // number of # printed in each line after the spaces where printed .


         for (int space =0; space<s; space++)
        {
            printf(" ");
        }


        for (int hashes=0; hashes<y; hashes++)
        {
            printf("#");
        }

        y++;
        printf("\n");

    }

}
