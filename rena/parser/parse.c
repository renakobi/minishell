/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:17 by rkobeiss          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/30 20:18:57 by rkobeiss         ###   ########.fr       */
=======
/*   Updated: 2026/01/28 18:24:29 by rkobeiss         ###   ########.fr       */
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//fpr parse_pipe
<<<<<<< HEAD
////left asssociative tree
=======
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
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
<<<<<<< HEAD

int	parse_redi(t_ast *node, t_token **curr)
{
	t_redir	*redi;
	int		temp;

	if (!*curr || !curr)
		return (0);
	while ((*curr)->type == tok_heredoc || (*curr)->type == tok_inredi
		|| (*curr)->type == tok_outredi || (*curr)->type == tok_append)
	{
		temp = (*curr)->type;
		*curr = (*curr)->next;
		if ((*curr)->type != tok_word)
			return (0);
		redi = malloc(sizeof(t_redir));
		if (!redi)
			return (0);
		redi->type = temp;
		redi->target = ft_strdup((*curr)->value);
		if (!node)
			return (0);
		node->redir = redi;
		redi = redi->next;
		*curr = (*curr)->next;
	}
	redi->next = NULL;
	return (1);
=======
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
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
}

t_ast	*parse_cmd(t_token **curr)
{
<<<<<<< HEAD
	t_ast	*node;
	char	**cmd;
	int		i;
	int		n;

	if (!*curr || !curr)
		return (NULL);
=======
	if (!*curr || !curr)
		return (NULL);
	t_ast	*node;
	char	**cmd;
	int		i;
	int 	n;

>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
	i = 0;
	n = count_words(*curr);
	if (n == 0)
		return (NULL);
	cmd = malloc((n + 1) * sizeof(char *));
<<<<<<< HEAD
	cmd_dup(*curr, **cmd);
=======
	while (*curr && (*curr)->type != tok_pipe && (*curr)->type != tok_eof && (*curr)->type != tok_rparan)
	{	
		if ((*curr)->type == tok_word)
			cmd[i++] = ft_strdup((*curr)->value);
		*curr = (*curr)->next;
	}
	cmd[i] = NULL;
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
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

<<<<<<< HEAD
t_ast	*parse_unit(t_token **curr)
{
	t_ast	*node;
	t_ast	*subshell;

	if (!*curr || !curr)
		return (NULL);
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

=======
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
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
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

<<<<<<< HEAD
void	parse_main(t_token **curr)
{
	t_ast	*node;

	if (!(*curr) || !curr)
		return (NULL);
	while ((*curr) && (*curr)->next)
	{
		if ((*curr)->type == tok_pipe)
		{
			node = malloc(sizeof(t_ast));
			node = parse_pipe(curr);
		}
		(*curr) = (*curr)->next;
	}
	if ((*curr)->type != tok_eof && (*curr)->type != tok_rparan)
		return (NULL);
}
=======
 
>>>>>>> df227a8b5814963f7ec73ee9c87ced4b92dfd4bb
