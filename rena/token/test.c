/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobeiss <rkobeiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:22:34 by rkobeiss          #+#    #+#             */
/*   Updated: 2026/01/21 15:22:35 by rkobeiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *head)
{
    while (head)
    {
        printf("type=%d | value=\"%s\"\n", head->type, head->value);
        head = head->next;
    }
}

static void	free_tokens(t_token *head)
{
    t_token *next;

    while (head)
    {
        next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

int main(void)
{
    char        input[512];
    t_token     *tokens;

    while (1)
    {
        printf(">>> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        // Remove newline
        size_t i = 0;
        while (input[i] && input[i] != '\n')
            i++;
        input[i] = '\0';

        if (input[0] == '\0')
            continue;

        tokens = NULL;
        tokenize(input, &tokens);

        printf("TOKENS:\n");
        print_tokens(tokens);

        free_tokens(tokens);
    }
    return 0;
}
