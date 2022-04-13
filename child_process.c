#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int i;
    int status;
    /*The command that will be excecuted by execve*/
    char *path[] = {"/bin/ls", "-l", "/tmp", NULL};

    /*will be excetuted 5 times*/
    for (i = 0; i < 5; i++)
    {
        if(fork() == 0)
        {
            execve(path[0], path, NULL);
            printf("----------------------------------");
            /*printf("\n son pid [%d] from parent pid [%d] \n", getpid(), getppid());*/
            exit(0);
        }
    }
    for (i = 0; i < 5; i++)
        wait(&status);
    return (0);
}