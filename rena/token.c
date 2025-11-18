/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:54:42 by rkobeiss          #+#    #+#             */
/*   Updated: 2025/11/18 21:34:42 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*buffer(const char *input)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(ft_strlen(input) + 1);
	while (input[i] != '|' && input[i] != '<'
		&& input[i] != '>' && input[i] != ')' && input[i] != '(' && input[i])
	{
		temp[j] = input[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
//might have memory leak since malloc-ing more than needed if so malloc(i + 1)

char	*quoted(const char *input, int *i)
{
    char *result;
	
	result = malloc(1);
    if (!result)
		return NULL;
    result[0] = '\0';
    while (input[*i] && (input[*i] == '"' || input[*i] == '\'')) {
        char *segment = read_one(input, i);
        if (!segment)
		{
            free(result);
            return NULL;
        }
        char *tmp = malloc(strlen(result) + strlen(segment) + 1);
        ft_strcpy(tmp, result);
        ft_strcat(tmp, segment);
        free(segment);
        free(result);
        result = tmp;
    }

    return result;
}

char	*append(const char *input, char *new)
{
	int		len;
	char	*temp;

	if (!new)
		return (NULL);
	len = ft_strlen(input) + ft_strlen(new);
	temp = malloc(sizeof(char) * 1 + len);
	ft_strcpy(temp, input);
	ft_strcat(temp, input);
	free(input);
	return (temp);
	
}

t_tok  classify(const char *s)
{
    if (!strcmp(s, "|"))
	    return tok_pipe;
    if (!strcmp(s, "<"))
	    return tok_inredi;
    if (!strcmp(s, ">"))
	    return tok_outredi;
    if (!strcmp(s, ">>"))
	    return tok_append;
    if (!strcmp(s, "<<"))
	    return tok_heredoc;
    if (!strcmp(s, "("))
	    return tok_lparan;
    if (!strcmp(s, ")"))
	    return tok_lparan;
    return tok_word;
}
