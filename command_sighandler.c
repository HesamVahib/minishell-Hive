#include "minishell.h"

void running_command_sighandler(int signal)
{
    if (signal == SIGINT) // here automatically appears ^C since it is the default behaviour
    {
        write(STDOUT_FILENO, "\n", 1); // print out a newline
        rl_on_new_line(); // move the cursor to the new line
        rl_replace_line("", STDIN_FILENO); // earase everything from the previous user
    }
    else if (signal == SIGQUIT)
        printf("Quit: %d\n", signal);
}