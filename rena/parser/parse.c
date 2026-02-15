/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:17 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/02/15 19:28:49 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/minishell.h"
//fpr parse_pipe
//left asssociative tree
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

int	parse_redi(t_ast *node, t_token **curr)
{
	t_redir	*redi;
	t_redir	*last;

	if (!node || !curr || !*curr)
		return (0);
	while ((*curr)->type == tok_heredoc || (*curr)->type == tok_inredi
		|| (*curr)->type == tok_outredi || (*curr)->type == tok_append)
	{
		redi = malloc(sizeof(t_redir));
		if (!redi_helper(curr, redi, node))
			return (0);
		if (!node->redir)
			node->redir = redi;
		else
		{
			last = node->redir;
			while (last->next)
				last = last->next;
			last->next = redi;
		}
		*curr = (*curr)->next;
	}
	redi->next = NULL;
	return (1);
}

t_ast	*parse_cmd(t_token **curr)
{
	t_ast	*node;
	char	**cmd;
	t_token	*tmp;
	int		n;

	if (!curr || !*curr)
		return (NULL);
	n = 0;
	tmp = *curr;
	while (tmp && tmp->type == tok_word)
	{
		n++;
		tmp = tmp->next;
	}
	if (n == 0)
		return (NULL);
	cmd = malloc(sizeof(char *) * (n + 1));
	if (!cmd)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node = cmd_helper(node, cmd, curr);
	return (node);
}

t_ast	*parse_subshell(t_token **curr)
{
	t_ast	*node;
	t_ast	*subshell;

	if (!curr || !*curr)
		return (NULL);
	if ((*curr)->type == tok_lparan)
	{
		*curr = (*curr)->next;
		subshell = parse_pipe(curr);
		if (!subshell)
			return (NULL);
		if (!*curr || (*curr)->type != tok_rparan)
			return (printf("syntax error: missing )\n)"), NULL);
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

t_ast	*parse_unit(t_token **curr)
{
	t_ast	*node;

	if (!curr || !*curr)
		return (NULL);
	if ((*curr)->type == tok_lparan)
	{
		node = parse_subshell(curr);
		if (!node)
			return (NULL);
	}
	else
	{
		node = parse_cmd(curr);
		if (!node)
			return (NULL);
	}
	parse_redi(node, curr);
	return (node);
}

	//
	//
	//
	//
	//
	//
	//
	//ADD SYNTAX ERROR HANDLING IN PARSE_PIPE!!!!!!!!!
	//// if (!*curr || ((*curr)->type != tok_word
		// 		&& (*curr)->type != tok_lparan))
		// 	return (printf("syntax error near pipe\n"), NULL);
	//
	//
	//

t_ast	*parse_pipe(t_token **curr)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_unit(curr);
	if (!left)
		return (NULL);
	while (*curr && (*curr)->type == tok_pipe)
	{
		*curr = (*curr)->next;
		right = parse_unit(curr);
		if (!right)
			return (NULL);
		node = pipe_helper(left, right);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}
