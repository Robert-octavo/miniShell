#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 * https://www.youtube.com/watch?v=cex9XrZCU14
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    printf("Before fork\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }
    printf("After fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    pid = fork();
    printf("Last fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", pid);
    return (0);
}