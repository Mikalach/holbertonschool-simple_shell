#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#define ERR(s) {perror("Allocation failed ((s))"); exit((1));}
#define SETVAR {freeAvTest = 0; isOnlySpaces = 0;}
#define FREEALL {free(pathBuffer); free(bf); free(av);}

int _path1(char *impath, char **usrinpt);
int only_space(char *usrinpt);
void printfullenv(char **envp);
int getPath(char **envp);
int _strtok1(char **av, char *line);
int frk(char **av, char **envp, char *filename);
#endif
