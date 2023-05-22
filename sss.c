#include "main.h"
#include "printf.h"

/**
 *
 */

char *get_command()
{
    char *line = NULL;
    int nread;
    size_t n = 0;

     _printf("($) ");
     nread = getline(&line, &n, stdin);

     /* Checks for EOF character*/
     if (nread == -1)
     {
         _printf("See ya suckers\n");
         exit(-1);
     }

     /* remove '\n' character */
     if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    return(line);
}

/**
 *
 */

int check_for_bin(char *cmd, char *av)
{
    int a = 0, j;

     for (j = 0; j < 5; j++)
        {
            if (cmd[j] == av[j])
                a++;
        }

    return (a);
}

/**
 *
 */

void execute(char *argv[32], int a)
{
    char cmd[1024] = "/bin/";

    if (a == 5) /*if av[0] starts with "/bin/" */
        {
            if(((execve(argv[0], argv, NULL)) == -1))
            {
                perror("./hsh");
                exit(EXIT_FAILURE);
            }
        }
    else /* if av[0] doesn't start with "/bin/" */
        {
            _strcat(cmd, argv[0]);
            if(((execve(cmd, argv, NULL)) == -1))
            {
                perror("./hsh");
                exit(EXIT_FAILURE);
            }
        }
}

/**
 *
 */

int main (void)
{
    while (1)  /* Infinite loop */
    {
        char *line = NULL;
        char *token, *delim = " ";
        int status;
        pid_t pid;
        int i = 0, a;
        char cmd[1024] = "/bin/";
        char *av[32] = { NULL };

        line = get_command();

        token = strtok(line, delim);

        /* assignes the tokenized string to argv for execve to use */
        while(token && i < 31)
        {
            av[i] = token;
            token = strtok(NULL, delim);
            i++;
        }
        /*checks if command includes "/bin/"*/
        a = check_for_bin(cmd, av[0]);

        pid = fork();
        if (pid == -1)
        {
            perror("fork: ");
            return (1);
        }

        if (pid == 0) /* run execve in a child process */
            execute(av, a);

        else
        {
            wait(&status);
            i = 0; /* reset i for reuse */
        }
    }
    return 0;
}
