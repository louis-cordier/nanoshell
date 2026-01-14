#include "../include/nanoshell.h"
#include <stdbool.h>

int main(void)
{
	char	line[4096];
	pid_t	pid;

	while (true)
	{
		printf("?> ");
		if (fgets(line, sizeof(line), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = 0;

		if (line[0] == '\0')
			continue;

		if (is_builtin(line))
		{
			exec_builtin(line);
			continue;
		}

		/* commandes externes */
		pid = fork();
		if (pid == 0)
		{
			execlp(line, line, NULL);
			perror("commande inconnue");
			exit(1);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
		else
			perror("fork");
	}
	return 0;
}

