#include "shell.h"
/**Add the env buildint*/
int main(/*int argc, char *argv[], char *envp[]*/)
{
	pid_t hijo;
	char *comando[100], *token, *linea = NULL;
	char *path_com = NULL; /*PATH + comando*/
	size_t i, n; 
	int status;
  
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		fflush(stdin);
		if (getline(&linea, &n, stdin) == -1)
			break;
		if (*linea == '\n' || *linea == '\t') /*correct error - Permission denied when press enter*/
			continue;
		token = strtok(linea, " \t\n\r"); 
		for (i = 0; i < 100 && token != NULL; i++)
		{
			comando[i] = token;
			token = strtok(NULL, " \t\n\r");
		}
		comando[i] = NULL; 

		if (str_compare(comando[0], "exit", 4) == 0)
			return (0);
		else if (str_compare(comando[0], "env" , 3) == 0)
		{
			print_env();
			return (0);
		}

		path_com = findpath(comando[0]);
		
		hijo = fork();
		if (hijo == 0)
		{
			if (execve(path_com, comando, NULL))
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