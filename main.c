#include "simples.h"

/**
 * printfullenv - Print the full environnement thingy, used for tests
 * @envp: environnement variable
 *Return: void
*/
void printfullenv(char **envp)
{
	int i = 0;

	for (; envp[i] != NULL ; i++)
		printf("%s\n", envp[i]);
}

/**
 * getPath - get the path throught envp
 * @envp: environnement
 * Return: path
 */
int getPath(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if ((envp[i][0] == 'P') && (envp[i][1] == 'A') &&
			(envp[i][2] == 'T') && (envp[i][3] == 'H') &&
			(envp[i][4] == '='))
			return (i);
		i++;
	}
	return (100);
}
/**
 * _strtok1 - Tokenize a long string into multiple shorter strings
 * @av: source buffer
 * @line: line we want to tokenize
 * Return: void
 */
int _strtok1(char **av, char *line)
{
	char *tok = NULL; /* string tokening */
	char delim[] = " \n\t"; /* delimiter */
	int i = 0;

	/*tokenizing into av*/
	if (line)
	{
		do {
			tok = strtok(line, delim);
			av[i] = tok;
			line = NULL;
			i++;
			if (tok == NULL && i == 1)
				return (1);
		} while (tok);
	}
	return (0);
}

/**
 * frk - fork and execve
 * @av: array of string used to call a function with execve
 * @envp: environement variable
 * @filename: name of the shell
 *Return: void
 */
int frk(char **av, char **envp, char *filename)
{
	pid_t pid;
	int test = 1, status = 0;

	pid = fork();

	if (pid == 0) /* if child */
	{
		if (av && *av)
		{
			test = execve(av[0], av, envp);
			if (test == -1)
			{
				printf("%s: %s: command not found\n", filename, av[0]);
				exit(2);
			}
		}
		exit(1);
	}
	else
		wait(&status); /* wait for the child to end */
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (status);
}

/**
 * main - Simple Shell
 * @envp: environnement variable
 * @argv: unsused
 * @argc: unused
 * Return: 0
 */
int main(__attribute__((unused))int argc, char **argv, char **envp)
{char *bf = NULL, **av = NULL, *pathBuffer = NULL;
	size_t bufsize = 1024;
	int ext = 0, path = 100, freeAvTest, isOnlySpaces, wifeexit = 0;
	struct stat st;

	av = calloc(1024, sizeof(char *));
	if (av == NULL)
		ERR(av);
	bf = calloc(1024, sizeof(char));
	if (bf == NULL)
		ERR(bf);
	pathBuffer = calloc(1000, sizeof(char));
	if (pathBuffer == NULL)
		ERR(pathBuffer);
	path = getPath(envp);
	while (1)
	{	SETVAR;
		if (path != 100)
			strcpy(pathBuffer, envp[path]);
		getline(&bf, &bufsize, stdin);
		if (feof(stdin) || strcmp(bf, "exit\n") == 0)
			ext = 1;
		else if (strcmp(bf, "env\n") == 0)
			printfullenv(envp);
		else
		{	isOnlySpaces = _strtok1(av, bf);
			if (isOnlySpaces == 0)
			{
				freeAvTest = _path1(pathBuffer, &av[0]);
				if (stat(av[0], &st) == 0)
					wifeexit = frk(av, envp, argv[0]);
				else
					dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", av[0]);
				if (wifeexit != 0)
				{
					FREEALL;
					exit(wifeexit);
				}
			}
		}
		if (ext == 1)
			break;
	if (freeAvTest == 1)
		free(av[0]); }
	FREEALL;
	return (0);
}
