#include "../token/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static void print_redir(t_redir *r)
{
	while (r)
	{
		printf("  redir type=%d target=%s\n", r->type, r->target);
		r = r->next;
	}
}

static void print_argv(char **argv)
{
	int i = 0;
	if (!argv)
		return;
	while (argv[i])
	{
		printf("  argv[%d]=%s\n", i, argv[i]);
		i++;
	}
}

static void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	if (node->type == ast_pipe)
		printf("PIPE\n");
	else if (node->type == ast_cmd)
		printf("CMD\n");
	else if (node->type == ast_subshell)
		printf("SUBSHELL\n");
	if (node->argv)
		print_argv(node->argv);
	if (node->redir)
		print_redir(node->redir);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

static void print_tokens(t_token *t)
{
	printf("TOKENS:\n");
	while (t)
	{
		printf("type=%d val=%s\n", t->type,
			t->value ? t->value : "(null)");
		t = t->next;
	}
}

int main(void)
{
	char *line;
	t_token *tokens;
	t_token *curr;
	t_ast *tree;
	while (1)
	{
		line = readline(">>> ");
		if (!line)
			break;
    tokens = NULL;
    tokenize(line, &tokens);
    curr = tokens;	
	print_tokens(tokens);
		curr = tokens;
		tree = parse_input(curr);  // entry point
		printf("\nAST:\n");
		print_ast(tree, 0);
		printf("------------\n");
		free(line);
	}
	return 0;
}
