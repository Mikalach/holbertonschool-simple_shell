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
	char *tok = NULL; /* string tokening */
	char delim[] = " \n\t"; /* delimiter */
	int i = 0;

	/*tokenizing into av*/
	if (line)
	{
		do{
			tok = strtok(line, delim);
			av[i] = tok;
			line = NULL;
			i++;
		}while(tok);
	}
}

/**
 * frk - fork and execve
 * @av: array of string used to call a function with execve
 * @envp: environement variable
 * @filename: name of the shell
 */
int frk(char **av, char **envp, char *filename)
{
	pid_t pid;
	int test = 1;
	int status = 0;
	int exit_status = 0;

	pid = fork();

	if (pid == 0) /* if child */
	{
		if (av && *av)
		{
			test = execve(av[0], av, envp);
			if (test == -1)
			{
				printf("%s: %s: command not found\n", filename, av[0]);
			}
		}
		exit(1);
	}
	else
	{
		wait(&status); /* wait for the child to end */
		if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				return(exit_status);
			}
	}
	return(1);
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
	char *bf = NULL, **av = NULL;
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
		/* printf("($) "); */
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
			_path1(envp[12], &av[0]);
			frk(av, envp, argv[0]);
		}

		if (ext == 1)
			break;
	}
	free(bf);
	free(av);
	return (0);
}
