#include "minishell.h"

void r_command_sighandler(int signal)
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
static int running_command(void)
{
    struct termios term;

    global_signal = 0;
    if (signal(SIGINT, &r_command_sighandler) == SIG_ERR) // replacing the default behaviour with out function. otherwise it quits from minishell cuz considers it as a regular program
        return (1);
    ft_bzero(&term, sizeof(term)); // clear termios of the last status of flags



}

int change_mode(int mode)
{
    if ((mode == RUNNING_COMMAND) && (running_command()))
        return (1);
    if ((mode == WAIT_FOR_COMMAND) && (wait_for_command()))
        return (1);
    if ((mode == HEREDOC) && (heredoc_mode()))
        return (1);
    return (0);
}