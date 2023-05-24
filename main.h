#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int check_for_exit(char *line);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *get_command();
int check_for_bin(char *av);
void execute(char *argv[32], int a);
void env(void);
extern char **environ;
#endif

