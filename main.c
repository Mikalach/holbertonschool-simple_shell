#include "simples.h"
/**
 * main - open a new bash
 * Return: 0
 */
char **_strtok1(char *line)
{
	char *tok;
	char delim[] = " ";
	char **av;
	int i = 0;

	av = NULL;
	av = malloc(sizeof(char *) * 100);
	tok = strtok(line,delim);

	while (tok)
	{
		av[i] = tok;
		tok = strtok(NULL, delim);
		i++;
	}
	return (av);
}

void frk(char **av, char **argenv)
{
	pid_t pid;
	pid = fork();
	int status;

	if (pid == -1) /* error */
		return;
	if (pid == 0) /* if child */
		execve(av[0], av, argenv);
	else
		wait(&status); /* wait for the child to end */
}

int main(void)
{
	pid_t pid;
	char *bf;
	size_t bufsize = 10;
	int i = 0;
	char **av;
	char *tok;
	char delim[] = " ";
	char *argenv[] = {"Home=/root",
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
		"TZ=America/Los_Angeles",
		"_=/usr/bin/env",
		NULL};

	av = NULL;
	av = malloc(sizeof(char *) * 100);

	bf = (char *)malloc(bufsize * sizeof(char));
	if (bf == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		printf("($) ");
		getline(&bf, &bufsize, stdin);
		av = _strtok1(bf);
		if (feof(stdin) || strcmp(bf, "exit\n") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		else
			frk(av, argenv);
	}
	free(bf);
	return (0);
}
