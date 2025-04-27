#include "include/minishell.h"


static int running_command(void)
{
    global_signal = 0;
    if (signal(SIGINT, &sighandler) == SIG_ERR) // replacing the default behaviour with out function. otherwise it quits from minishell cuz considers it as a regular program
        return (1);
    return (0);
}


static int wait_for_command(void)
{
    global_signal = 0;
    if (signal(SIGINT, &sighandler) == SIG_ERR)
        return (1);
     if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) // ignore ctrl+\ in the main process as it is in bash
        return (1);
    return (0);

}


// static int heredoc_mode(void)
// {
//     global_signal = 0;
//     if (signal(SIGINT, &sig_handler_heredoc) == SIG_ERR)
//         return (1);
//     return (0);

// }

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