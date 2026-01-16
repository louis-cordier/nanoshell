#pragma once

#define BUFFER_SIZE 1024

int is_builtin(char *cmd);
void handle_builtin(char **args);
