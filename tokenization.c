#include "./include/minishell.h"

#include <stdlib.h>

int ft_cmdlen(char *line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i] == ' ')
        i++;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            j++;
            char quote = line[i];
            i++;
            while (line[i] != quote && line[i] != '\0')
                i++;
            if (line[i] == quote)
                i++;
        }
        else if ((line[i] == '<' || line[i] == '>') && (line[i + 1] == line[i]))
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
            while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|')
                i++;
        }
        else
            i++;
        while (line[i] == ' ')
            i++;
    }
    return j;
}

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i;

    i = 0;
    dup = malloc(n + 1);
    if (!dup)
        return NULL;
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[n] = '\0';
    return dup;
}

char **word_splitter(char *line)
{
    int size;
    char **splitted_line;
    int i;
    int j;
    int start;

    size = ft_cmdlen(line);
    splitted_line = (char **)malloc((size + 1) * sizeof(char *));
    i = 0;
    j = 0;
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (!line[i])
            break;
        if (line[i] == '\'' || line[i] == '"')
        {
            start = i;
            char quote = line[i];
            i++;
            while (line[i] != quote && line[i] != '\0')
                i++;
            if (line[i] == quote)
                i++;
            splitted_line[j++] = ft_strndup(&line[start], i - start);
        }
        else if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
        {
            splitted_line[j++] = ft_strndup(&line[i], 2);
            i += 2;
        }
        else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
        {
            splitted_line[j++] = ft_strndup(&line[i], 1);
            i++;
        }
        else
        {
            start = i;
            while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|')
                i++;
            splitted_line[j++] = ft_strndup(&line[start], i - start);
        }
    }
    splitted_line[j] = NULL;
    return splitted_line;
}

char **quotes_chkr(char **cmd_line)
{
    int i = 0;
    int in_single;
    int in_double;
    int j;

    in_single = 0;
    in_double = 0;
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

char **adjacent_quotes(char **cmd_line) // "hesam""wahib" is handled
{
    int i;
    int j;
    int k;
    char buffer[10000];


    i = 0;
    while (cmd_line[i])
    {   
        j = 0;
        k = 0;
        if (cmd_line[i][j] == '"')
        {
            while (cmd_line[i][j])
            {
                if (cmd_line[i][j + 1] == '"' && j != 0 && cmd_line[i][j + 2])
                    j += 2;
                else
                    buffer[k] = cmd_line[i][j];
                j++;
                k++;
            }
            cmd_line[i] = ft_strndup(buffer, k);
            if (!cmd_line[i])
                return (NULL);
        }
        i++;
    }
    return (cmd_line);
}

char **quote_remover(char **cmd_line) // removing single quote
{
    int count;
    int i;
    size_t len;
    char *token;
    char **new_cmd;

    if (!cmd_line)
        return NULL;
    count = arrlen(cmd_line);
    new_cmd = malloc((count + 1) * sizeof(char *));
    if (!new_cmd)
        return NULL;
    i = 0;
    while (i < count)
    {
        token = cmd_line[i];
        len = strlen(token);
        if (len >= 2 && (token[0] == '\'' || token[0] == '"')
            && token[0] == token[len - 1])
            new_cmd[i] = ft_strndup(token + 1, len - 2);
        else
            new_cmd[i] = ft_strndup(token, len);
        if (!new_cmd[i]) // failure should be handled sophisticatedly
            return NULL;
        i++;
    }
    new_cmd[count] = NULL;
    free_array(&cmd_line);
    return new_cmd;
}

char **line_tokenized(char *line)
{
    char **cmd_line;

    cmd_line = word_splitter(line);
    if (!cmd_line || !*cmd_line)
        return (printf("it is not splitted properly\n"), NULL); // for now it is not clear, just to make sure we are handling the possibilities
    cmd_line = quotes_chkr(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("the quotes are not closed\n"), NULL); // for now it is not clear, just to make sure we are handling the possibilities
    // the only things should be handled are <, >, <<, >>, |, '
    cmd_line = adjacent_quotes(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("ajacent does not work\n"), NULL);
    cmd_line = quote_remover(cmd_line);
    if (!cmd_line || !*cmd_line)
        return (printf("qoute remover failed\n"), NULL);
    return(cmd_line);
}