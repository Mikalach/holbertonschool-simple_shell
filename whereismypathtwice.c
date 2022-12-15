#include "simples.h"

/**
 *_path1 - change the command without / into the good one
 *@impath: is the path where the command is stored
 *@usrinpt: is the input from the user
 *Return: void
*/
void _path1(char *impath, char **usrinpt)
{
	char *usep = NULL;
	char *copy_usep = NULL;
	char *path_tmp = NULL;
	struct stat st;

	copy_usep = malloc(sizeof(char) * 1024);

	if (!*usrinpt)
	{
	}

	path_tmp = strdup(impath);

	while (usep = strtok(path_tmp, ":="))
	{
		path_tmp = NULL;
		strcpy(copy_usep, usep);
		strcat(copy_usep, "/");
		strcat(copy_usep, *usrinpt);
		if (stat(copy_usep, &st) == 0)
		{
			*usrinpt = strdup(copy_usep);
			break;
		}
	}
	free(copy_usep);
	free(path_tmp);
}
