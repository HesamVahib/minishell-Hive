#include "include/minishell.h"

int	is_same_value(char *s1, char *s2)
{
	if ((ft_strlen(s1) == ft_strlen(s2))
	&& (!ft_strncmp(s1, s2,	ft_strlen(s1))))
		return (1);
	return (0);
}

t_env	*remove_node(t_env *head, t_env *node)
		// to remove a node from PATH list.
{
	t_env *temp;
	t_env *temp_head;
	t_env *previous_node;

	temp_head = head;
	if (head == node)
	{
		head = head->next;
		free(node->key);
		free(node->value);
		free(node->index);
		free(node);
		return (head);
	}
	temp = head;
	while (temp && temp != node)
	{
		previous_node = temp;
		temp = temp->next;
	}
	previous_node->next = node->next;
	free(node->key);
	free(node->value);
	free(node->index);
	free(node);
	return (temp_head);
}

t_env	*set_start(t_env *env_list)
		//  when a shell creates a new shell it inherits env variables from the parents including OLDPWD
{
	t_env *temp_env;

	if (find_value_from_env(env_list, "SHLVL"))
		custom_export(env_list, "SHLVL", "2");
	else
		custom_export(env_list, "SHLVL", "1");
	temp_env = env_list;
	while (temp_env && !is_same_value(temp_env->key, "OLDPWD"))
		// clear Old Present Working Directory (OLDPWD) not to mix up with previous shell level.
		temp_env = temp_env->next;
	if (temp_env) // if it is found rmeove this node
		env_list = remove_node(env_list, temp_env);
	return (env_list);
}
