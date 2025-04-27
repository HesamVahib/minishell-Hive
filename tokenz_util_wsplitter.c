#include "./include/minishell.h"


static int skip_spaces(char *line, int i)
{
    while (line[i] == ' ')
        i++;
    return (i);
}

static int handle_double_operator(char **splitted_line, char *line, int i, int *j)
{
    splitted_line[*j] = ft_strndup(&line[i], 2);
    if (splitted_line[*j])
        *j = *j + 1;
    return (i + 2);
}

static int handle_single_operator(char **splitted_line, char *line, int i, int *j)
{
    splitted_line[*j] = ft_strndup(&line[i], 1);
    if (splitted_line[*j])
        *j = *j + 1;
    return (i + 1);
}

static int handle_regular_word(char **splitted_line, char *line, int i, int *j)
{
    int start;
    char quote;

    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|')
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            quote = line[i];
            i++;
            while (line[i] && line[i] != quote)
                i++;
            if (line[i] == quote)
                i++;
        }
        else
            i++;
    }
    splitted_line[*j] = ft_strndup(&line[start], i - start);
    if (splitted_line[*j])
        *j = *j + 1;
    return (i);
}

char **word_splitter(char *line)
{
    int size;
    char **splitted_line;
    int i;
    int j;

    size = ft_cmdlen(line);
    splitted_line = (char **)malloc((size + 1) * sizeof(char *));
    if (!splitted_line)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        i = skip_spaces(line, i);
        if (!line[i])
            break;
        if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
            i = handle_double_operator(splitted_line, line, i, &j);
        else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
            i = handle_single_operator(splitted_line, line, i, &j);
        else
            i = handle_regular_word(splitted_line, line, i, &j);
    }
    splitted_line[j] = NULL;
    return (splitted_line);
}
