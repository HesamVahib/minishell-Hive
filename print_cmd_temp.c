#include "./include/minishell.h"

void print_cmd_temp(t_cmd *cmd_args)
{
    int i = 0;

    while (cmd_args != NULL)
    {
        printf("=== Command %d ===\n", i);
        if (cmd_args->argv)
        {
            for (int j = 0; cmd_args->argv[j]; j++)
                printf("'%s' ", cmd_args->argv[j]);
            printf("\n");
        }
        if (cmd_args->infile)
            printf("infile1: '%s'\n", cmd_args->infile);
        if (cmd_args->outfile)
            printf("outfile: '%s' (append: %d)\n", cmd_args->outfile, cmd_args->append);
        if (cmd_args->is_heredoc)
            printf("heredoc limiter: '%s'\n", cmd_args->is_heredoc);
        printf("is_piped: %d\n", cmd_args->is_piped);

        cmd_args = cmd_args->next;
        i++;
    }
}