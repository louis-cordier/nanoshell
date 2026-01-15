#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "nanoshell.h"


int my_strlen(char *str) {
    int i = 0;
    for (i=0; str[i]; i++) {}
    return i;
}




int main(void) {
    char line[BUFFER_SIZE] = {0};
    char *av[] = {"ls", NULL};
    char *env[] = {NULL};
    int pid = 0;

    // char **args = strplit(line, ' ');

    while(1) {
    printf("?> ");
    fgets(line, BUFFER_SIZE, stdin);
    line[my_strlen(line) - 1] = 0; 


    if (strcmp(line, "exit") == 0) {
        exit(0);
    }
    pid = fork();
    if (pid == 0) {
        // only child see this
        execve(line, av, env);
        printf("Error: command not found\n");
        exit(-1);
    }
    waitpid(pid, NULL, 0);
}

    return 0;
}