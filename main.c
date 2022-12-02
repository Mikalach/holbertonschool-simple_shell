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
	av = malloc(sizeof(char *) * 1024);
	tok = strtok(line, delim);

	while (tok)
	{
		av[i] = tok;
		tok = strtok(NULL, delim);
		i++;
	}
	av[i] == NULL;
	return (av);
}

void frk(char **av, char **envp)
{
	pid_t pid;

	pid = fork();
	int status;

	if (pid == -1) /* error */
		exit(1);
	if (pid == 0) /* if child */
	{
		execve(av[0], av, envp);
		exit(1);
	}
	else
		wait(NULL); /* wait for the child to end */
}

int main(__attribute__ ((unused))int argc, __attribute__ ((unused))char **argv, char **envp)
{
	pid_t pid;
	char *bf;
	size_t bufsize = 1024;
	int i = 0;
	char **av;
	char *tok;

	av = NULL;
	av = malloc(sizeof(char *) * bufsize);
	/* malloc error handle */

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
		if (feof(stdin) || strcmp(bf, "exit\n") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
			av = _strtok1(bf);
			frk(av, envp);
		}
	}
	free(bf);
	return (0);
}
