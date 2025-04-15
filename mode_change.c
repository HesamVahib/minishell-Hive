#include "include/minishell.h"

static void sighandler(int signal)
{
    if (signal == SIGINT) // here automatically appears ^C since it is the default behaviour
    {
        write(STDOUT_FILENO, "\n", 1); // print out a newline
        rl_on_new_line(); // move the cursor to the new line
        rl_replace_line("", STDIN_FILENO); // earase everything from the previous user
        rl_redisplay(); // redisplay the input line
    }
    else if (signal == SIGQUIT)
        /// it should be ignored when it is in the main process
        printf("Quit: %d\n", signal);
}

static int running_command(void)
{
    // struct termios term;

    global_signal = 0;
    if (signal(SIGINT, &sighandler) == SIG_ERR) // replacing the default behaviour with out function. otherwise it quits from minishell cuz considers it as a regular program
        return (1);
    // ft_bzero(&term, sizeof(term)); // clear termios sstructure of the last status of flags
    // if (tcgetattr(STDIN_FILENO, &term) == -1) // get the attributes of termios here from stdin
    //     return (1);
    // term.c_lflag |= ECHOCTL; // changing the default of ctrl+something to echoing and writing something ^C, mimicing ^C (or any character) to mimic the behaviour of shell
    // if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) // apply the modifications on it
    //     return (1);
    return (0);

}

static int wait_for_command(void)
{
    // struct termios term;

    global_signal = 0;
    if (signal(SIGINT, &sighandler) == SIG_ERR)
        return (1);
     if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        return (1);
    // ft_bzero(&term, sizeof(term));
    // if (tcgetattr(STDIN_FILENO, &term) == -1)
    //     return (1);
    // term.c_lflag |= ECHOCTL; // turning of CTRL+C to show ^C.
    // if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
    //     return (1);
    return (0);

}

int change_mode(int mode)
{
    if ((mode == RUNNING_COMMAND) && (running_command()))
        return (1);
    else if ((mode == WAIT_FOR_COMMAND) && (wait_for_command()))
        return (1);
    // else if ((mode == HEREDOC) && (heredoc_mode()))
    //     return (1);
    return (0);
}