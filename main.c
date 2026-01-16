#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "nanoshell.h"

extern char **environ;


int my_strlen(char *str) {
    int i = 0;
    for (i=0; str[i]; i++) {}
    return i;
}

char **strplit(char *str, char delim) {
    static char *args[64];
    static char buf[BUFFER_SIZE];
    int i = 0;
    int k = 0;
    
    for (i = 0; str[i] && i < BUFFER_SIZE - 1; i++)
        buf[i] = str[i];
    buf[i] = '\0';
    
    args[0] = &buf[0];
    k = 1;
    for (i = 0; buf[i] && k < 63; i++) {
        if (buf[i] == delim) {
            buf[i] = '\0';
            if (buf[i+1])
                args[k++] = &buf[i+1];
        }
    }
    args[k] = NULL;
    return args;
}

char *find_path(char *cmd) {
    static char path[BUFFER_SIZE];
    static char copy[BUFFER_SIZE];
    char *env_path = getenv("PATH");
    int i = 0;
    int j = 0;
    
    for (i = 0; env_path[i] && i < BUFFER_SIZE - 1; i++)
        copy[i] = env_path[i];
    copy[i] = '\0';
    
    i = 0;
    while (copy[i]) {
        j = 0;
        while (copy[i] && copy[i] != ':' && j < BUFFER_SIZE - 1)
            path[j++] = copy[i++];
        if (j < BUFFER_SIZE - 1)
            path[j++] = '/';
        for (int k = 0; cmd[k] && j < BUFFER_SIZE - 1; k++)
            path[j++] = cmd[k];
        path[j] = '\0';
        if (access(path, X_OK) == 0)
            return path;
        if (copy[i] == ':')
            i++;
    }
    return cmd;
}


int main(void) {
    char line[BUFFER_SIZE] = {0};
    char **args;
    int pid = 0;

    while(1) {
        printf("?> ");
        fgets(line, BUFFER_SIZE, stdin);
        line[my_strlen(line) - 1] = 0;

        if (my_strlen(line) == 0)
            continue;

        args = strplit(line, ' ');

        if (is_builtin(args[0])) {
            handle_builtin(args);
        } else {
            pid = fork();
            if (pid == 0) {
                execve(find_path(args[0]), args, environ);
                printf("Error: command not found\n");
                exit(-1);
            }
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}




