/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:11 by rkobeiss          #+#    #+#             */
/*   Updated: 2025/11/22 18:50:26 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_one(const char *input, int *i)
{
	char	quote;
	int		start;
	int		len;
	char	*segment;

	quote = input[*i];
	start = ++(*i);
	len = 0;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	segment = malloc(len + 1);
	if (!segment)
		return (NULL);
	strncpy(segment, input + start, len);
	segment[len] = '\0';
	if (input[*i] == quote)
		(*i)++;
	return (segment);
}

char	*read_word(const char *input, int *i)
{
	char	*word;
	char	*seg;
	char	letter[2];

	word = malloc(1);
	while (input[*i] && !is_operator(input[*i]) && !is_quoted(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			seg = read_one(input, i);
			word = appends(input, seg);
		}
		else
		{
			letter[0] = input[*i];
			letter[1] = 0;
			word = appends(word, letter);
			*i++;
		}
	}
	return (word);
}

char	*read_operator(const char *input, int *i)
{
	char	*op;

	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		op = malloc(3);
		if (!op)
			return (NULL);
		op[0] = input[*i];
		op[1] = input[*i + 1];
		op[2] = '\0';
		*i += 2;
		return (op);
	}
	else
	{
		op = malloc(2);
		if (!op)
			return (NULL);
		op[0] = input[*i];
		op[1] = '\0';
		(*i)++;
		return (op);
	}
}
