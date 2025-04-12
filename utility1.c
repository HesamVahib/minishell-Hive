#include "include/minishell.h"

char *find_value_from_env(t_env *env_list, char *key)
{
    t_env *temp;

    temp = env_list;
    while (temp)
    {
        if (is_same_value(temp->value, key))
            return(temp->value);
        temp = temp->next;
    }
    return (NULL);
}

int	arrlen(void **arr)
{
	int len;

	if (!arr || !*arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}
