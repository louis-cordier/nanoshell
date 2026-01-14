#include "nanoshell.h"

#define MAX_ARGS 64
#define MAX_LINE 1024

// lire une ligne depuis stdin
int read_line(char **line, size_t *n)
{
    if (*line == NULL)
        *line = malloc(MAX_LINE);
    if (fgets(*line, MAX_LINE, stdin) == NULL)
        return -1;
    *n = strlen(*line);
    return 0;
}

// découpe la ligne en mots
char **parse(char *line)
{
    char **argv = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0;

    argv[i] = strtok(line, " \n");
    while (argv[i])
        argv[++i] = strtok(NULL, " \n");

    return argv;
}

// builtins simples
int builtin(char **argv)
{
    char buf[1024];

    if (!strcmp(argv[0], "exit"))
        exit(0);

    if (!strcmp(argv[0], "pwd"))
    {
        getcwd(buf, sizeof(buf));
        printf("%s\n", buf);
        return 1;
    }

    if (!strcmp(argv[0], "env"))
    {
        for (int i = 0; environ[i]; i++)
            printf("%s\n", environ[i]);
        return 1;
    }

    if (!strcmp(argv[0], "cd"))
    {
        chdir(argv[1] ? argv[1] : getenv("HOME"));
        return 1;
    }

    return 0;
}

// cherche dans PATH
char *find_path(char *cmd)
{
    static char path[1024];
    char *p = strdup(getenv("PATH"));
    char *dir = strtok(p, ";");

    while (dir)
    {
        sprintf(path, "%s\\%s", dir, cmd);
        if (access(path, 0) == 0)
            return path;
        dir = strtok(NULL, ";");
    }
    return NULL;
}

int main(void)
{
    char *line = NULL;
    size_t n;
    char **argv;
    intptr_t pid;

    while (1)
    {
        write(1, "nanoshell> ", 11);

        if (read_line(&line, &n) == -1)
            break;

        argv = parse(line);
        if (!argv[0])
            continue;

        if (builtin(argv))
            continue;

        char *path = strchr(argv[0], '/') || strchr(argv[0], '\\') ?
            argv[0] : find_path(argv[0]);

        if (path)
        {
            pid = _spawnv(_P_WAIT, path, (const char * const *)argv);
            if (pid == -1)
                printf("nanoshell: weird, %s is not here… :/\n", argv[0]);
        }
        else
            printf("nanoshell: weird, %s is not here… :/\n", argv[0]);
    }
    return 0;
}
