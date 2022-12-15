#include "simples.h"

/**
 *_path1 - change the command without / into the good one
 *@impath: is the path where the command is stored
 *@usrinpt: is the input from the user
 *Return: void
*/
int _path1(char *impath, char **usrinpt)
{
	char *usep = NULL;
	char *copy_usep = NULL;
	char *path_tmp = NULL;
	struct stat st;

	if (!*usrinpt)
		return (0);
	if (stat(*usrinpt, &st) == 0)
		return (0);

	copy_usep = malloc(sizeof(char) * 1024);

	while (usep = strtok(impath, ":="))
	{
		impath = NULL;
		strcpy(copy_usep, usep);
		strcat(copy_usep, "/");
		strcat(copy_usep, *usrinpt);
		if (stat(copy_usep, &st) == 0)
		{
			*usrinpt = strdup(copy_usep);
			free(copy_usep);
			return (1);
		}
	}
	free(copy_usep);
	return (0);
}
