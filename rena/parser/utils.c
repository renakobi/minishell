/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:58:24 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/02/15 16:58:42 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/minishell.h"

int	count_words(t_token *t)
{
	int	n;

	n = 0;
	while (t && t->type != tok_pipe && t->type != tok_rparan
		&& t->type != tok_eof)
	{
		if (t->type == tok_word)
			n++;
		t = t->next;
	}
	return (n);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i ++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *) malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!temp)
		return (NULL);
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
