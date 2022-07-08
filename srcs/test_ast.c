/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:34:56 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/09 00:44:38 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_ast()
{
	t_btree	*ast;
	//t_btree	*tmp;
	char	*argv1[] = {"push_swap", "8", "5", "4", "7", NULL};
	char	*argv2[] = {"cat", "-e", NULL};

	ast = btree_create_node((void *) ast_create_node(MSH_PIPE, (void *) malloc(sizeof(t_ast_pipe))));
	ast->left = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_cmd))));
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->path = "../42_push_swap/push_swap";
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->argv = argv1;
	ast->right = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_pipe))));
	((t_ast_cmd *) ((t_ast_node *) ast->right->item)->data)->path = "/usr/bin/cat";
	((t_ast_cmd *) ((t_ast_node *) ast->right->item)->data)->argv = argv2;
	//tmp = ast;
	ast = btree_create_node((void *) ast_create_node(MSH_REDIRECT_LL, (void *) malloc(sizeof(t_ast_redir))));
	((t_ast_redir *) ((t_ast_node *) ast->item)->data)->word = "123";
	ast->left = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_pipe))));
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->path = "/usr/bin/cat";
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->argv = argv2;
	//((t_ast_redir *) ((t_ast_node *) ast->item)->data)->word = "ast_test_>";
	//ast->left = tmp;

	ast_exec(ast);
}
