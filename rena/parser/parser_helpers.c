/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:19:27 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/01/30 20:22:42 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_dup(t_token **curr, char **cmd, t_ast *node)
{
	int	i;

	i = 0;
	while (*curr && (*curr)->type != tok_pipe && (*curr)->type != tok_eof
		&& (*curr)->type != tok_rparan)
	{	
		if (((*curr)->type == tok_inredi || (*curr)->type == tok_outredi
				|| (*curr)->type == tok_append || (*curr)->type == tok_heredoc))
			cmd[i++] = parse_redi(node, curr);
		else if ((*curr)->type == tok_word)
			cmd[i++] = ft_strdup((*curr)->value);
		*curr = (*curr)->next;
	}
	cmd[i] = NULL;
}

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
