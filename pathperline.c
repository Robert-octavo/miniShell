#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *path;
	char *token;
	int i;

	path = getenv("PATH");
	token = strtok(path, "/");
	for (i = 0; token != NULL; i++)
	{
		printf("/%s\n", token);
		token= strtok(NULL, "/");
	}
	token = NULL;
	return (0);
}