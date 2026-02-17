/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:42:19 by kel-mada          #+#    #+#             */
/*   Updated: 2026/02/15 18:26:13 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*create_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

//need to shorten this
t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*tmp;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equal = strchr(envp[i], '=');
		if (equal)
		{
			*equal = '\0';
			tmp = create_node(strdup(envp[i]), strdup(equal + 1));
			*equal = '=';
		}
		if (!head)
			head = tmp;
		else
		{
			last = head;
			while (last->next)
				last = last->next;
			last->next = tmp;
		}
		i++;
	}
	return (head);
}
