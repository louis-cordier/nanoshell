#ifndef NANOSHELL_H
# define NANOSHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

int		is_builtin(char *cmd);
int		exec_builtin(char *cmd);
void	exec_cmd(char *cmd, char **envp);

// Fallback strchr equivalent for environments lacking the C standard one
char	*ns_strchr(const char *s, int c);

#endif
