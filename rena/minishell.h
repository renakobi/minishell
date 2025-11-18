/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:22:46 by rkobeiss          #+#    #+#             */
/*   Updated: 2025/11/18 19:48:05 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <ctype.h>

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
	char	*value;
	t_tok	type;
}t_token;

#endif
