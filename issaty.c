#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    if(isatty(0))
    {
        printf("the standar input its from a terminal: \n");
    }
    else
        printf("The stantar input is not from the terminal: \n");

    exit(0);
}