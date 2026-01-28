/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:17 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/01/28 18:24:29 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//fpr parse_pipe
	//while token 
	//take cmd = tokens while token != | 
	//if token = | take cmd2 = right side while next is not |
	// create pipe being left | right then continue loop
//for parse_unit & cmd
	//read through token,
	//if its a ( it is a subshell so call parse_pipe
	//aka recursion and put it in a subshell node till )
	//new left node would be the inner first node
	//then check for type of command, keep going forward
	//until you reach a redirection eof pipe or ) and add them to argv
static int	count_words(t_token *t)
{
	int	n;

	n = 0;
	while (t && t->type != tok_pipe && t->type != tok_rparan && t->type != tok_eof)
	{
		if (t->type == tok_word)
			n++;
		t = t->next;
	}
	return (n);
}

t_ast	*parse_redi(t_token **curr)
{
	if (!*curr || !curr)
		return (NULL);
	t_ast	*node;
	char	**redi;

	if ((*curr)->type == tok_heredoc || (*curr)->type == tok_inredi || (*curr)->type == tok_outredi || (*curr)->type == tok_append)
	{
		*curr = (*curr)->next;
		if ((*curr)->type != tok_word)
			return (NULL);
			
	}
}

t_ast	*parse_cmd(t_token **curr)
{
	if (!*curr || !curr)
		return (NULL);
	t_ast	*node;
	char	**cmd;
	int		i;
	int 	n;

	i = 0;
	n = count_words(*curr);
	if (n == 0)
		return (NULL);
	cmd = malloc((n + 1) * sizeof(char *));
	while (*curr && (*curr)->type != tok_pipe && (*curr)->type != tok_eof && (*curr)->type != tok_rparan)
	{	
		if ((*curr)->type == tok_word)
			cmd[i++] = ft_strdup((*curr)->value);
		*curr = (*curr)->next;
	}
	cmd[i] = NULL;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->type = ast_cmd;
	node->argv = cmd;
	node->redir = NULL;
	return (node);
}

t_ast	*parse_subshell(t_token **curr)
{
	if (!*curr || !curr)
		return (NULL);
	t_ast	*node;
	t_ast	*subshell;

		if (((*curr)->type == tok_lparan))
		{
			*curr = (*curr)->next;
			subshell = parse_pipe(curr);
			if (!subshell)
				return (NULL);
			if (!*curr || (*curr)->type != tok_rparan)
				return (printf("syntax error: missing )\n)", NULL));
				*curr = (*curr)->next;
			node = malloc(sizeof(t_ast));
			if (!node)
				return (NULL);
			node->left = subshell;
			node->right = NULL;
			node->type = ast_subshell;
			node->argv = NULL;
			node->redir = NULL;
			return (node);
		}
		return (parse_cmd(curr));
}
//left asssociative tree
t_ast	*parse_pipe(t_token **curr)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;

	left = parse_unit(curr);
	if (!left)
		return (NULL);
	while (*curr && (*curr)->type == tok_pipe)
	{
		*curr = (*curr)->next;
		right = parse_unit(curr);
		if (right == NULL)
			return (NULL);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->type = ast_pipe;
		node->argv = NULL;
		node->redir = NULL;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

 