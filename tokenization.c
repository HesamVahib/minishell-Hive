#include "./include/minishell.h"

int ft_cmdlen(char *line)
{
    int i;
    int j;

    i = 0;
    while (line[i] == ' ')
        i++;
    j = 0;
    while (line[i])
    {
        if ((line[i] == '<' || line[i] == '>') &&
            (line[i + 1] == line[i]))
        {
            j++;
            i += 2;
        }
        else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
        {
            j++;
            i++;
        }
        else if (line[i] != ' ')
        {
            j++;
            while (line[i] && line[i] != ' ' && line[i] != '<' &&
                   line[i] != '>' && line[i] != '|')
                i++;
        }
        else
            i++;
    }
    return j;
}

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i;

    dup = malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[n] = '\0';
    return dup;
}

char **line_splitter(char *line)
{
    int size;
    int i;
    int j;
    int start;
    char **splitted_line;

    size = ft_cmdlen(line);
    splitted_line = (char **)malloc((size + 1) * (sizeof(char *)));

    i = 0;
    j = 0;
    while (line[i])
    {
        while (line[i] == ' ')
            i++;

        if (!line[i])
            break;
        if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i]) // << or >>
        {
            splitted_line[j++] = ft_strndup(&line[i], 2);
            i += 2;
        }
        else if (line[i] == '<' || line[i] == '>' || line[i] == '|') // < or > or |
        {
            splitted_line[j++] = ft_strndup(&line[i], 1);
            i++;
        }
        else
        {
            start = i;
            while (line[i] && line[i] != ' ' &&
                   line[i] != '<' && line[i] != '>' && line[i] != '|')
                i++;
            splitted_line[j++] = ft_strndup(&line[start], i - start);
        }
    }

    splitted_line[j] = NULL;
    return (splitted_line);
}

char **quotes_chkr(char **cmd_line)
{
    int i = 0;
    int in_single = 0;
    int in_double = 0;
    int j;

    while (cmd_line[i])
    {
        j = 0;
        while (cmd_line[i][j])
        {
            if (cmd_line[i][j] == '\'' && !in_double)
                in_single = !in_single;
            else if (cmd_line[i][j] == '\"' && !in_single)
                in_double = !in_double;
            j++;
        }
        i++;
    }

    if (in_single || in_double)
        return NULL;
    return cmd_line;
}

char **line_tokenized(char *line)
{
    char **cmd_line;

    cmd_line = line_splitter(line);
    if (!cmd_line || !*cmd_line)
        return (NULL); // for now it is not clear, just to make sure we are handling the possibilities
    cmd_line = quotes_chkr(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (NULL); // for now it is not clear, just to make sure we are handling the possibilities
    // the only things should be handled are <, >, <<, >>, |, '
    return(cmd_line);
}