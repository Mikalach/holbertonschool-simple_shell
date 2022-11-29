#include <stdio.h>
#include <stdlib.h>

/**
 * main - open a new bash
 * Return: 0
 */

int main(void)
{
	char *bf;
	size_t bufsize = 1;
	size_t characters;

	bf = (char *)malloc(bufsize * sizeof(char));
	if (bf == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (!feof(stdin))
	{
		printf("($) ");
		characters = getline(&bf, &bufsize, stdin);
		if (!(bf[0] == 'e' && bf[1] == 'x' && bf[2] == 'i' && bf[3] == 't'))
			printf("%s\n", bf);
		else
			exit(0);
	}
	return (0);
}
