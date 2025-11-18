/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:22:26 by rkobeiss          #+#    #+#             */
/*   Updated: 2025/11/18 19:39:36 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_operator(char c)
{
    return c == '|' || c == '<' || c == '>' || c == '(' || c == ')';
}

char *read_one(const char *input, int *i)
{
    char quote = input[*i];
    int start = ++(*i);
    int len = 0;

    while (input[*i] && input[*i] != quote) {
        (*i)++;
        len++;
    }

    char *segment = malloc(len + 1);
    if (!segment)
		return NULL;
    strncpy(segment, input + start, len);
    segment[len] = '\0';
    if (input[*i] == quote)
		(*i)++;
    return segment;
}
