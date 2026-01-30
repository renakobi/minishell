/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:54:42 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/01/23 14:47:14 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*appends(char *input, const char *new)
{
	int		len;
	char	*temp;

	if (!new || !input)
		return (NULL);
	len = ft_strlen(input) + ft_strlen(new);
	temp = malloc(1 + len);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, input);
	ft_strcat(temp, new);
	free(input);
	return (temp);
}

t_tok	classify(const char *s)
{
	if (!ft_strcmp(s, "|"))
		return (tok_pipe);
	if (!strcmp(s, "<"))
		return (tok_inredi);
	if (!strcmp(s, ">"))
		return (tok_outredi);
	if (!strcmp(s, ">>"))
		return (tok_append);
	if (!strcmp(s, "<<"))
		return (tok_heredoc);
	if (!strcmp(s, "("))
		return (tok_lparan);
	if (!strcmp(s, ")"))
		return (tok_rparan);
	return (tok_word);
}

void	push_token(t_token **head, t_tok type, const char *value)
{
	t_token	*new;
	t_token	*tmp;

	if (!head)
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	tokenize(char *input, t_token **head)
{
	int		i;
	char	*op;
	char	*word;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator(input[i]))
		{
			op = read_operator(input, &i);
			push_token(head, classify(op), op);
			free(op);
		}
		else
		{
			word = read_word(input, &i);
			push_token(head, tok_word, word);
			free(word);
		}
	}
	push_token(head, tok_eof, NULL);
}
