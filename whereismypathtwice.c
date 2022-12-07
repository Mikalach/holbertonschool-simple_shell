#include "simples.h"

void _path1(char *impath, char **usrinpt)
{
	int x = 0;
	char *usep = NULL;
	char **tokenp = calloc(sizeof(char *), 100);
	char *path_tmp = NULL;
	struct stat st;

	if (!tokenp || !*usrinpt || !tokenp || !path_tmp)
	{
		free(tokenp);
		return;
	}
	path_tmp = strdup(impath);

	do{
		usep = strtok(path_tmp, ":=");
		tokenp[x] = usep;
		path_tmp = NULL;
		x++;
	}
	while(usep);

	x = x - 2;
	while (x > 0)
	{
		strcat(tokenp[x], "/");
		strcat(tokenp[x], *usrinpt);
		if (stat(tokenp[x], &st) == 0)
		{
			*usrinpt = tokenp[x];
			free(tokenp[x]);
			break;
		}
		free(tokenp[x]);
		x--;
	}
	free(usep);
	free(path_tmp);
	free(tokenp);
	return;
}
