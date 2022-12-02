#include "simples.h"
/**
 * main - open a new bash
 * Return: 0
 */

int main(void)
{
	pid_t pid;
	char *bf;
	size_t bufsize = 1;
	int i = 0;
	char *av[10];
	char *tok;
	char delim[] = " ";
	char *argenv[] = {"Home=/root",
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
		"TZ=America/Los_Angeles",
		"_=/usr/bin/env",
		NULL
	};


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
			getline(&bf, &bufsize, stdin);
			tok = strtok(bf, delim);
			while (tok)
			{
				av[i] = tok;
				tok = strtok(NULL, delim);
				i++;
			}
			if (!(bf[0] == 'e' && bf[1] == 'x' && bf[2] == 'i' && bf[3] == 't'))
				execve(av[0], av, argenv);
			else
			{
				free(bf);
				exit(0);
			}
		}
	}
	else /* if parent */
	{
		wait(NULL); /* wait for the child to end */
	}
	free(bf);
	return (0);
}
