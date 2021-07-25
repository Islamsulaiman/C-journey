#include <cs50.h>
#include <stdio.h>


// hello, is a program that greats you.


int main(void)
{
    string greating = get_string("type your name\n");
    printf("hello, %s\n", greating);
}
