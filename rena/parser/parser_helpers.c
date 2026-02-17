/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:19:27 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/02/17 15:19:58 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/minishell.h"

void	cmd_dup(t_token **curr, char **cmd, t_ast *node)
{
	int	i;

	i = 0;
	while (*curr && (*curr)->type != tok_pipe && (*curr)->type != tok_eof
		&& (*curr)->type != tok_rparan)
	{	
		if (((*curr)->type == tok_inredi || (*curr)->type == tok_outredi
				|| (*curr)->type == tok_append || (*curr)->type == tok_heredoc))
			parse_redi(node, curr);
		else if ((*curr)->type == tok_word)
			cmd[i++] = ft_strdup((*curr)->value);
		*curr = (*curr)->next;
	}
	cmd[i] = NULL;
}

int	redi_helper(t_token **curr, t_redir *redi, t_ast *node)
{
	int	temp;

	temp = (*curr)->type;
	*curr = (*curr)->next;
	if (!(*curr) || (*curr)->type != tok_word)
		return (0);
	if (!redi)
		return (0);
	redi->type = temp;
	redi->target = ft_strdup((*curr)->value);
	redi->next = NULL;
	if (!node)
		return (0);
	return (1);
}

t_ast	*cmd_helper(t_ast *node, char **cmd, t_token **curr)
{
	int	i;

	node->type = ast_cmd;
	node->left = NULL;
	node->right = NULL;
	node->redir = NULL;
	i = 0;
	while (*curr && (*curr)->type != tok_pipe
		&& (*curr)->type != tok_rparan && (*curr)->type != tok_eof)
	{
		if ((*curr)->type == tok_word)
		{
			cmd[i++] = ft_strdup((*curr)->value);
			*curr = (*curr)->next;
		}
		else if ((*curr)->type == tok_inredi || (*curr)->type == tok_outredi
			|| (*curr)->type == tok_append || (*curr)->type == tok_heredoc)
		{
			if (!parse_redi(node, curr))
				return (0);
		}
		else
			break ;
	}
	cmd[i] = NULL;
	node->argv = cmd;
	return (node);
}
// int cmd_helper(t_ast *node, char **cmd, t_token **curr)
// {
//     int i = 0;

//     node->type = ast_cmd;
//     node->left = NULL;
//     node->right = NULL;
//     node->redir = NULL;

//     while (*curr
//         && (*curr)->type != tok_pipe
//         && (*curr)->type != tok_rparan
//         && (*curr)->type != tok_eof)
//     {
//         if ((*curr)->type == tok_word)
//         {
//             cmd[i++] = ft_strdup((*curr)->value);
//             *curr = (*curr)->next;
//         }
//         else if ((*curr)->type == tok_lparan)
//         {
//             t_ast *sub = parse_subshell(curr);
//             if (!sub)
//                 return 0;

//             // store subshell as argv marker
//             cmd[i++] = ft_strdup("__SUBSHELL__");
//             node->left = sub; 
//         }
//         else if (is_redirection((*curr)->type))
//         {
//             if (!parse_redi(node, curr))
//                 return 0;
//         }
//         else
//             *curr = (*curr)->next;
//     }

//     cmd[i] = NULL;
//     node->argv = cmd;
//     return 1;
// }

t_ast	*pipe_helper(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ast_pipe;
	node->left = left;
	node->right = right;
	node->argv = NULL;
	node->redir = NULL;
	return (node);
}
