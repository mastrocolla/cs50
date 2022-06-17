// #include "/home/ubuntu/libs/mylib.h"
#include <stdio.h>
#include <cs50.h>

int calcPopulation(int, int);


int main(void)
{
    int startSize = 0;
    int endSize = 0;
    int years = 0;

    // Asking data from user
    while (startSize < 9)
    {
        // startSize=getPosInt("Start size: ");     // When using mylib.h
        startSize = get_int("Start size: ");
    }
    while (endSize < startSize)
    {
        // endSize=getPosInt("End size: ");         // When using mylib.h
        endSize = get_int("End size: ");

    }

    years = calcPopulation(startSize, endSize);
    printf("\nYears: %d", years);



}


int calcPopulation(int start, int end)
{
    int years = 0;

    // Testing if population > end
    for (; start < end; years++)
    {
        start += (int)(start / 3) - (int)(start / 4);
    }
    return years;
}

