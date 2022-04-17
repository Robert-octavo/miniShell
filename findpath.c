#include "shell.h"

/**
 * findpath -Funtion that find the PATH where the command is save
 * @comando: Pointer - Command to find the path
 * Return: the PATH with the command to execute*
 */

char *findpath(char *comando)
{
	char *path = NULL, *ctoprint = NULL;
	struct stat stats;
	char *token = NULL;
	int i = 0;
	/*char *c_source;*/

	if (stat(comando, &stats) == 0)
		return (comando);
	path = _getenv("PATH");
	token = strtok(path, ":");
	comando = str_concat("/", comando);
	/*printf("desde el findpath [%s]",comando);*/
	/*
	*stat() return 0 on successful
	*returns -1 if its unable to get file
	*properties
	*/
	while (token != NULL)
	{
		//printf("entro al ciclo en findpath [%d]\n",i);
		ctoprint = str_concat(token, comando);
		printf("Cadena a buscar[%s]\n", ctoprint);
		if (stat(ctoprint, &stats) == 0)
		{
			//printf("//[path][%s]", ctoprint);
			free(comando);
			return (ctoprint);
		}
		free(ctoprint);
		token = strtok(NULL, ":");
		printf("\ntoken : [%s]--\n", token);
		i++;
	}
	/*printf("\nComando a ejecutar: %s", ctoprint);*/
	return (NULL);
}
