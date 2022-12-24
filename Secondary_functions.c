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
			test = execve(av[0], av, envp); /* run it */
			if (test == -1) /* if run fail: error + exit*/
			{
				printf("%s: %s: command not found\n", filename, av[0]);
				exit(EXIT_FAILURE);
			}
		}
		exit(EXIT_FAILURE);
	}
	else /* if parent */
		wait(&status); /* wait for the child to end */
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (status);
}
