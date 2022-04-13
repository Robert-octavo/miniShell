#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 *
 * Return: Always 0.
 */
int main(void)
{
    //pid_t my_ppid;
    //pid_t my_pid;
 
    //my_ppid = getppid();
    /*my_pid = getpid();*/
    printf("%u : %u \n", getpid(), getppid());
    //printf("Este es el hijo : %u\n", getpid());
    return (0);
}