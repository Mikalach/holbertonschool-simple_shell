#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - open a new bash
 * Return: 0
 */

int main(void)
{
	pid_t pid;
	char *bf;
	size_t bufsize = 1;
	size_t characters;
	int i = 0;

	bf = (char *)malloc(bufsize * sizeof(char));
	if (bf == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	pid = fork();

	if (pid == -1) /* error */
		return (0);

	if (pid == 0) /* if child */
	{
		while (!feof(stdin))
		{
			printf("($) ");
			characters = getline(&bf, &bufsize, stdin);
			if (!(bf[0] == 'e' && bf[1] == 'x' && bf[2] == 'i' && bf[3] == 't'))
			{
				puts(environ[i]);
				i++;
			}
			else
			{
				free(bf);
				exit(0);
			}
		}
	}
	else /* if parent */
		wait(NULL); /* wait for the child to end */
	free(bf);
	return (0);
}
