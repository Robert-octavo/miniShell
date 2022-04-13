#include <stdio.h>
/**
 * @brief Write a program that prints all the arguments,
 * without using ac
 * @param ac is the number of items in av
 * @param av is a NULL terminated array of strings
 * @return int 
 */
int main(__attribute__((unsed))int ac, char **av)
{
    int i;
    for (i = 0; av[i]; i++)
    {
        printf("%s\n", av[i]);
    }
    return (0);
}