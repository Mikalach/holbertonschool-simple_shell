#include "simples.h"

/**
 * printfullenv - Print the full environnement thingy, used for tests
 * @envp: environnement variable
 */
void printfullenv(char **envp)
{
	int i = 0;

	for (; envp[i] != NULL ; i++)
		printf("%s\n", envp[i]);
}

/**
 * _strtok1 - Tokenize a long string into multiple shorter strings
 * @line: line we want to tokenize
 * Return: the Array of shorter strings
 */
char **_strtok1(char *line)
{
	char *tok; /* string tokening */
	char delim[] = "\n"; /* delimiter */
	char **av; /* string tokenized */
	int i = 0;

	/* initiating tokenization*/
	av = NULL;
	av = malloc(sizeof(char *) * 1024);
	//tok = strtok(line, delim);

	/*tokenizing into av*/
	while (tok)
	{
		tok = strtok(line, delim);
		av[i] = tok;
		line = NULL;
		i++;
	}
	av[i] == NULL;

	return (av);
}

/**
 * frk - fork and execve
 * @av: array of string used to call a function with execve
 * @envp: environement variable
 */
void frk(char **av, char **envp)
{
	pid_t pid;
	char *cpy = av[0];

	pid = fork();

	if (pid == -1) /* error */
		exit(1);
	if (pid == 0) /* if child */
	{
		if (execve(cpy, av, envp) == -1)
			printf("\\%s isn't a valid command\n", cpy);
	}
	else
		wait(NULL); /* wait for the child to end */
}

/**
 * main - Simple Shell
 * @envp: environnement variable
 * @argv: unsused
 * @argc: unused
 * Return: 0
 */
int main(__attribute__ ((unused))int argc, char **argv, char *envp[])
{
	pid_t pid;
	char *bf, *tok, **av;
	size_t bufsize = 1024;
	int i = 0;

	/* Array-Buffer creation */
	av = NULL;
	av = calloc(bufsize, sizeof(char *));
	if (av == NULL)
	{
		perror("Allocation failed (av)");
		exit(1);
	}
	bf = calloc(bufsize, sizeof(char *));
	if (bf == NULL)
	{
		perror("Allocation failed (bf)");
		exit(1);
	}
	/* The Simple Shell */
	while (1)
	{
		printf("($) ");
		getline(&bf, &bufsize, stdin);
		/* if we want to exit */
		if (feof(stdin) || strcmp(bf, "exit\n") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		/* if we enter another command (+ options) */
		else
		{
			av = _strtok1(bf);
			frk(av, envp);
		}
	}
	/* Free everything when finished*/
	free(bf);
	return (0);
}
