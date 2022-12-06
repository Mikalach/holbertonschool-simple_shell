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
 * @av: source buffer
 * @line: line we want to tokenize
 * Return: the Array of shorter strings
 */
void _strtok1(char **av, char *line)
{
	char *tok; /* string tokening */
	char delim[] = " \n\t"; /* delimiter */
	int i = 0;

	/*tokenizing into av*/
	while (tok)
	{
		tok = strtok(line, delim);
		av[i] = tok;
		line = NULL;
		i++;
	}
}

/**
 * frk - fork and execve
 * @av: array of string used to call a function with execve
 * @envp: environement variable
 * @filename: name of the shell
 */
void frk(char **av, char **envp, char *filename)
{
	pid_t pid;

	pid = fork();

	if (pid == 0) /* if child */
	{
		if (execve(av[0], av, envp) == -1)
			printf("%s: %s: command not found\n", filename, av[0]);
		exit(0);
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
int main(__attribute__((unused))int argc, char **argv, char **envp)
{
	char *bf, **av = NULL;
	size_t bufsize = 1024;
	int ext = 0;

	/* Array-Buffer creation */
	av = calloc(1024, sizeof(char *));
	if (av == NULL)
	{perror("Allocation failed (av)");
		exit(1); }
	bf = calloc(1024, sizeof(char *));
	if (bf == NULL)
	{perror("Allocation failed (bf)");
		exit(1); }
	/* The Simple Shell */
	while (1)
	{
		printf("($) ");
		getline(&bf, &bufsize, stdin);
		/* if we want to exit */
		if (feof(stdin) || strcmp(bf, "exit\n") == 0)
			ext = 1;
		else if (strcmp(bf, "env\n") == 0)
			printfullenv(envp);
		/* if we enter another command (+ options) */
		else
		{
			_strtok1(av, bf);
			frk(av, envp, argv[0]);
		}

		if (ext == 1)
			break;
	}
	free(bf);
	free(av);
	return (0);
}
