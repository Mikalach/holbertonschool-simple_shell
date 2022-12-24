#include "simples.h"

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
