/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:10:46 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/02/25 21:05:06 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/minishell.h"

/*
edge cases to handle:
| ls
ls |
ls | | wc
ls >
ls >>
ls <
ls <<
(ls
)
ls )
ls || wc
ls > |
ls >> (
ls (wc)
()
EOF after operator
*/
int	is_sym(t_token *curr)
{
	if (curr->type == tok_append || curr->type == tok_dquot
		|| curr->type == tok_heredoc || curr->type == tok_inredi
		|| curr->type == tok_lparan || curr->type == tok_outredi
		|| curr->type == tok_pipe || curr->type == tok_rparan
		|| curr->type == tok_squot)
		return (1);
	return (0);
}

int	is_redir(t_token *curr)
{
	if (curr->type == tok_append || curr->type == tok_heredoc
		|| curr->type == tok_inredi || curr->type == tok_outredi)
		return (1);
	return (0);
}
// add this outside
// if (t->next)
// 				printf("syntax error near unexpected token %s", t->next->value);
// 			else
// 				printf("syntax error near unexpected token 'newline");
// Problem 1 — This rule is WRONG for minishell
// if (t->next && t->type == tok_word
//     && t->next->type == tok_lparan)
//     return (1);

// This rejects:

// ls (echo hi)

// which is correct for minishell.

// But it also rejects this valid case:

// echo hello > out 
int	validate_1(t_token *t)
{
	while (t)
	{
		if (t->next && t->type == tok_word
			&& t->next->type == tok_lparan)
			return (1);
		if (t->type == tok_pipe && (!t->next || t->next->type == tok_pipe
				|| t->next->type == tok_rparan || t->next->type == tok_eof))
			return (1);
		if (is_redir(t) && (!t->next || t->next->type != tok_word))
			return (1);
		if (t->type == tok_lparan && (!t->next || t->next->type == tok_rparan
				|| t->next->type == tok_pipe || t->next->type == tok_eof))
			return (1);
		if (t->type == tok_rparan && t->next && (t->next->type == tok_lparan
				|| t->next->type == tok_word))
			return (1);
		t = t->next;
	}
	return (0);
}
