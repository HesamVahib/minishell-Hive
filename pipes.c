#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
# include <sys/wait.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			printf("prev: %d, fd[0]: %d, fd[1]: %d\n", fdd, fd[0], fd[1]);
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-l", "../", NULL};
	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {ls, rev, nl, cat, NULL};

	pipeline(cmd);
	return (0);
}
