#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(/*int argc, char *argv[], char *envp[]*/)
{
	pid_t hijo;
	char *comando[20], *token, *linea = NULL;
	size_t i, n; 
	int status;
  
	while (1)
	{
		printf("$ ");
		if (getline(&linea, &n, stdin) == -1)
			break;
		token = strtok(linea, " \t\n\r"); 
		for (i = 0; i < 20 && tok != NULL; i++)
		{
			comando[i] = token;
			token = strtok(NULL, " \t\n\r");
		}
		comando[i] = NULL; 
		hijo = fork();
		if (hijo == 0)
		{
			if (execve(comando[0], comando, NULL))
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		if (hijo > 0) 
			wait(&status);
	}
	putchar('\n');
	free(linea);
	exit(status);
}