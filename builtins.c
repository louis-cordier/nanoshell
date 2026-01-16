#include "nanoshell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;

void print_pwd(void);
void print_env(void);

int my_strcmp(char *s1, char *s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int is_builtin(char *cmd) {
    return my_strcmp(cmd, "exit") == 0 || my_strcmp(cmd, "cd") == 0 || 
           my_strcmp(cmd, "pwd") == 0 || my_strcmp(cmd, "env") == 0;
}

void handle_builtin(char **args) {
    if (my_strcmp(args[0], "exit") == 0)
        exit(0);
    if (my_strcmp(args[0], "cd") == 0)
        chdir(args[1] ? args[1] : getenv("HOME"));
    if (my_strcmp(args[0], "pwd") == 0)
        print_pwd();
    if (my_strcmp(args[0], "env") == 0)
        print_env();
}

void print_pwd(void) {
    char cwd[BUFFER_SIZE];
    getcwd(cwd, BUFFER_SIZE);
    printf("%s\n", cwd);
}

void print_env(void) {
    for (int i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
}


