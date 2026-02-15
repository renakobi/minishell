/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:21:30 by kel-mada          #+#    #+#             */
/*   Updated: 2026/02/15 18:15:59 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
