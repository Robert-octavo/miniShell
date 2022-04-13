#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;
	extern char **environ;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i++]);
	}
	return (0);
}