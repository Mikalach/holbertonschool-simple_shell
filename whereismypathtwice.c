#include "simples.h"

/**
 *_path1 - change the command without / into the good one
 *@impath: is the path where the command is stored
 *@usrinpt: is the input from the user
 *Return: void
*/
void _path1(char *impath, char **usrinpt)
{
	int x = 0;
	char *usep = NULL;
	char **tokenp = calloc(sizeof(char *), 100);
	char *path_tmp = NULL;
	struct stat st;

	if (!*usrinpt)
	{
		free(tokenp);
		return;
	}
	path_tmp = strdup(impath);

	do {
		usep = strtok(path_tmp, ":=");
		tokenp[x] = usep;
		path_tmp = NULL;
		x++;
	} while (usep);

	x = x - 2;
	while (x > 0)
	{
		strcat(tokenp[x], "/");
		strcat(tokenp[x], *usrinpt);
		if (stat(tokenp[x], &st) == 0)
		{
			*usrinpt = strdup(tokenp[x]);
			if (!tokenp[x])
				free(tokenp[x]);
			break;
		}
		if (!tokenp[x])
			free(tokenp[x]);
		x--;
	}
	free(usep);
	free(path_tmp);
	if (!tokenp)
		free(tokenp);
	return;
}
