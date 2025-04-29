#include "./include/minishell.h"

 /*
    Tokenization Start
 */
static char *prepare_line(char *line)
{
    char *new_line;

    new_line = double_backslash_remover(line);
    if (!new_line)
        printf("double_backslash_remover does not work\n");
    return (new_line);
}

static char **tokenize_and_check(char *new_line)
{
    char **cmd_line;

    cmd_line = word_splitter(new_line);
    if (!cmd_line || !*cmd_line)
        return (printf("it is not splitted properly\n"), NULL);
    cmd_line = quotes_chkr(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("the quotes are not closed\n"), NULL);
    cmd_line = syntax_analyzer(cmd_line);
    return (cmd_line);
}

static char **expand_variables(char **cmd_line, t_env *env)
{
    cmd_line = dollar_expansion(cmd_line, env);
    if (!cmd_line)
        return (printf("Dollar Expansion failed\n"), NULL);
    cmd_line = surplus_dollar_remover(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("Surplus dollar remover failed\n"), NULL);
    return (cmd_line);
}

// void print_tokens(char **cmd)
// {
//     char **temp = cmd;

//     while (*temp)
//     {
//         printf("%s\n", *temp);
//         temp++;
//     }
// }

char **line_tokenized(char *line, t_env *env)
{
    char *new_line;
    char **cmd_line;

    new_line = prepare_line(line);
    if (!new_line)
        return (NULL);
    cmd_line = tokenize_and_check(new_line);
    if (!cmd_line)
        return (NULL);
    cmd_line = expand_variables(cmd_line, env);
    if (!cmd_line)
        return (NULL);
    cmd_line = adjacent_quotes(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("adjacent quotes handling failed\n"), NULL);
    // print_tokens(cmd_line);
    return (cmd_line);
}


// echo "$$$'HOME'"