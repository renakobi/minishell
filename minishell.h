/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:22:46 by rkobeiss          #+#    #+#             */
/*   Updated: 2025/12/09 16:45:15 by rkobeiss         ###   ########.fr       */
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
	tok_dquot
}t_tok;

typedef struct s_token
{
	char			*value;
	t_tok			type;
	struct s_token	*next;
}t_token;

int		is_operator(char c);
int		is_quote(char c);
void	push_token(t_token **head, t_tok type, const char *value);
char	*appends(char *input, const char *new);
char	*read_operator(const char *input, int *i);
char	*read_word(char *input, int *i);
t_tok	classify(const char *s);
void	tokenize(char *input, t_token **head);
char	*read_one(const char *input, int *i);
char	*read_operator(const char *input, int *i);
int		ft_strlen(const char *str);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
int		ft_isspace(char a);

#endif
