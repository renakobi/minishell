/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:22:46 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/02/15 19:26:54 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>

typedef enum e_tokentype
{
	tok_word,
	tok_pipe,
	tok_inredi,
	tok_outredi,
	tok_heredoc,
	tok_append,
	tok_lparan,
	tok_rparan,
	tok_eof,
	tok_squot,
	tok_dquot,
	tok_command
}t_tok;

typedef struct s_token
{
	char			*value;
	t_tok			type;
	struct s_token	*next;
}t_token;

typedef enum e_data_ast
{
	ast_cmd,
	ast_pipe,
	ast_subshell
}t_data_ast;

typedef struct s_redir
{
	int				type;
	char			*target;
	struct s_redir	*next;
}t_redir;

typedef struct s_ast
{
	t_data_ast		type;
	struct s_ast	*right;
	struct s_ast	*left;
	char			**argv;
	t_redir			*redir;
}t_ast;

int			is_operator(char c);
int			is_quote(char c);
void		push_token(t_token **head, t_tok type, const char *value);
char		*appends(char *input, const char *new);
char		*read_operator(const char *input, int *i);
char		*read_word(char *input, int *i);
t_tok		classify(const char *s);
void		tokenize(char *input, t_token **head);
char		*read_one(const char *input, int *i);
char		*read_operator(const char *input, int *i);
int			ft_strlen(const char *str);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
int			ft_isspace(char a);
char		*ft_strdup(const char *s);
void		cmd_dup(t_token **curr, char **cmd, t_ast *node);
t_ast		*parse_pipe(t_token **curr);
int			parse_redi(t_ast *node, t_token **curr);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
int			ft_strcmp(const char *s1, const char *s2);
int			count_words(t_token *t);
int			redi_helper(t_token **curr, t_redir *redi, t_ast *node);
int			cmd_helper(t_ast *node, char **cmd, t_token **curr);
t_ast		*pipe_helper(t_ast *left, t_ast *right);
t_ast		*parse_subshell(t_token **curr);

// static int	append_quote(char **word, const char *input, int *i);
// static void	append_char(char **word, char c);

#endif
