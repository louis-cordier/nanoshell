#include "../include/nanoshell.h"

extern char **environ;

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strncmp(cmd, "cd", 2) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char *cmd)
{
	char	cwd[4096];

	if (strcmp(cmd, "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(cmd, "pwd") == 0)
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
	else if (strcmp(cmd, "env") == 0)
	{
		for (int i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
	}
	else if (strncmp(cmd, "cd", 2) == 0)
	{
		if (cmd[2] == '\0')
			chdir(getenv("HOME"));
		else
			chdir(cmd + 3);
	}
	return (0);
}
