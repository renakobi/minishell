/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:11 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/01/23 14:47:46 by rkobeiss         ###   ########.fr       */
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
	ft_strncpy(segment, input + start, len);
	segment[len] = '\0';
	if (input[*i] == quote)
	{
		(*i)++;
		return (segment);
	}
	return (printf("minishell: unclosed quote %c\n", quote), NULL);
}
//i might need to add a special case error
// for each kind of quotes (whether ' or ")
//done!

static int	append_quote(char **word, const char *input, int *i)
{
	char	*seg;

	seg = read_one(input, i);
	if (!seg)
		return (0);
	*word = appends(*word, seg);
	free(seg);
	return (1);
}

static void	append_char(char **word, char c)
{
	char	letter[2];

	letter[0] = c;
	letter[1] = '\0';
	*word = appends(*word, letter);
}

char	*read_word(char *input, int *i)
{
	char	*word;

	word = malloc(1);
	if (!word)
		return (NULL);
	word[0] = '\0';
	while (input[*i] && !is_operator(input[*i]) && !ft_isspace(input[*i]))
	{
		if (is_quote(input[*i]) && !append_quote(&word, input, i))
			return (word);
		else if (!is_quote(input[*i]))
		{
			append_char(&word, input[*i]);
			(*i)++;
		}
		else
			break ;
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
