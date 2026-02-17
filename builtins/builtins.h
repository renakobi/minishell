/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:13:30 by kel-mada          #+#    #+#             */
/*   Updated: 2026/02/16 18:30:36 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTNS_H

# include "./minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen2(char **s);
t_env	*create_node(char *key, char *value);
t_env	*init_env(char **envp);

#endif