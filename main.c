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

/**
 * main - Simple Shell
 * @envp: environnement variable
 * @argv: unsused
 * @argc: unused
 * Return: 0
 */
int main(__attribute__((unused))int argc, char **argv, char **envp)
{
	char *bf = NULL**av = NULL, *pathBuffer = NULL;
	size_t bufsize = 1024;
	int ext = 0, path = 100, freeAvTest, isOnlySpaces, wifeexit = 0;
	struct stat st;


	/* Array-Buffer creation */
	av = calloc(1024, sizeof(char *));
	if (av == NULL)
		ERR(av); /* free + print stderr + exit */
	bf = calloc(1024, sizeof(char));
	if (bf == NULL)
		ERR(bf); /* free + print stderr + exit */
	pathBuffer = calloc(1000, sizeof(char));
	if (pathBuffer == NULL)
		ERR(pathBuffer); /* free + print stderr + exit */


	/* get the path of built-in function using environment */
	path = getPath(envp);


	/* The Simple Shell */
	while (1)
	{
		SETVAR; /* set all necessary test variables to 0 */

		if (path != 100) /* if environment/built-in path is found*/
			strcpy(pathBuffer, envp[path]);

		getline(&bf, &bufsize, stdin); /* get user input */

		if (feof(stdin) || strcmp(bf, "exit\n") == 0) /* launch 'exit' command to stop the program */
			ext = 1;

		else if (strcmp(bf, "env\n") == 0) /* launch 'env' command */
			printfullenv(envp);

		else /* launch any built-in command if existing */
		{
			isOnlySpaces = _strtok1(av, bf); /* get the user input + handle the special case : no character other than ' ', '\n' or '\t' input */
			if (isOnlySpaces == 0) /* if user input isn't '\0', '\n', '\t', ' ' */
			{
				freeAvTest = _path1(pathBuffer, &av[0]); /* get the absolute path of command to run it */
				if (stat(av[0], &st) == 0)
				{
					/* run the command if existing */
					wifeexit = frk(av, envp, argv[0]);
					if (wifeexit != 0) /* if error encountered, free + exit */
					{
						FREEALL;
						exit(wifeexit);
					}
				}
				else
					dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", av[0]);
			}
		}
		
		/* stop the program loop */
		if (ext == 1)
			break;
	if (freeAvTest == 1)
		free(av[0]); 
	}
	/* end of the shell programm (and end of the loop in the prog)*/

	FREEALL; /* free every buffer */
	return (0);
}
