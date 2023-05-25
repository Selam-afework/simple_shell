#include "main.h"
#include "printf.h"

/**
 * get_command - gets command from command line, checks for EOF
 *		 and removes \n character
 * Return: pointer to command(line)
 */

char *get_command()
{
	char *line = NULL;
	int nread;
	size_t n = 10;

	if (isatty(STDIN_FILENO) == 1)
		_printf("($) ");
	
	nread = getline(&line, &n, stdin);

	/* Checks for EOF character*/
	if (nread == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (_strcmp(line, "\n") == 0)
	{
		free(line);
		get_command();
	}

	if (_strcmp(line, "exit\n") == 0)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	/* remove '\n' character */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * check_for_bin - checks if the command starts wiht /bin
 * @av: the command
 * Return: 5 if its a match, anything else if not
 */

/*
int check_for_bin(char *av)
{
	char cmd[1024] = "/bin/";
	int a = 0, j;

	for (j = 0; j < 5; j++)
	{
		if (cmd[j] == av[j])
			a++;
	}

	return (a);
} */

/**
 * env - prints the current environment
 *
 * Return: None
 */

void env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_printf("%s\n", environ[i]);
}

/**
 * execute - executes the given commands
 * @argv: takes in the command
 * @a: 5 if command starts with "/bin/"
 * return: None
 */

void execute(char *argv[32], int a)
{
	(void) a;
	/*char cmd[1024] = "/bin/";*/

	/* if (a == 5) if argv[0] starts with "/bin/" */
	
	if (((execve(argv[0], argv, environ)) == -1))		
	{
		_printf("./hsh: %s: command not found\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	/* else  if av[0] doesn't start with "/bin/" 
	{
		_strcat(cmd, argv[0]);
		if (((execve(cmd, argv, environ)) == -1))
		{
			_printf("./hsh: %s: command not found\n", argv[0]);
			exit(EXIT_SUCCESS);
		}
	} */
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main(void)
{
	while (1) /* Infinite loop */
	{
		char *line = {0};
		char *token, *delim = " \n\t\r";
		int status;
		char *av[32] = {0};
		pid_t pid;
		int i = 0, a = 0;

		line = get_command();

		token = strtok(line, delim);

		/* assignes the tokenized string to argv for execve to use */
		while (token && i < 31)
		{
			av[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		if (*av == NULL)
		{
			free(line);
			continue;
		}
		else {
			/* a = check_for_bin(av[0]); checks if command includes "/bin/" */

			pid = fork();
			if (pid == -1)
			{
				perror("fork: ");
				return (EXIT_SUCCESS);
			}

			if (pid == 0) /* run execve in a child process */
				execute(av, a);

			else {
				wait(&status);
				*av = NULL;
				line = NULL;
			}}}
	return (0);
}
