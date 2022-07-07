#include "minishell.h"

void	test_ast()
{
	t_btree	*ast;

	ast = btree_create_node((void *) ast_create_node(MSH_PIPE, (void *) malloc(sizeof(t_ast_pipe))));
	ast->left = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_cmd))));
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->name = "./push_swap 8 5 4 7";
	ast->right = btree_create_node((void *) ast_create_node(MSH_REDIRECT_R, (void *) malloc(sizeof(t_ast_pipe))));
	ast->right->left = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_pipe))));
	((t_ast_cmd *) ((t_ast_node *) ast->right->left->item)->data)->name = "wc -l";
	ast->right->right = btree_create_node((void *) ast_create_node(MSH_FILE,(void *) malloc(sizeof(t_ast_pipe))));

	ast_exec(ast);
}

int	main(void)
{
	char	*line;
	char	*prompt;

	test_ast();
	return (0);
	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		if (line && strlen(line))
			add_history(line);
		if (!line)
			break ;
	}
	return (0);
}
