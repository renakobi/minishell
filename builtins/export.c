/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:36:18 by kel-mada          #+#    #+#             */
/*   Updated: 2026/02/15 18:23:14 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*existing = find_env(*env, key);
	t_env	*new;

	if (existing)
	{
		free(existing->value);
		existing->value = value ? strdup(value) : NULL;
		return ;
	}
	new = create_node(strdup(key), value ? strdup(value) : NULL);
	new->next = *env;
	*env = new;
}

void	ft_export(t_env **env, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = strchr(arg, '=');
	if (!equal)
	{
		add_or_update_env(env, arg, NULL);
		return ;
	}
	key = strndup(arg, equal - arg);
	value = strdup(equal + 1);
	add_or_update_env(env, key, value);
	free(key);
	free(value);
}
