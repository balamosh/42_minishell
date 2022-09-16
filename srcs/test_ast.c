/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:34:56 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/15 21:50:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_ast()
{
	t_btree	*ast;
	char	*argv1[] = {"push_swap", "8", "5", "4", "7", NULL};
	char	*argv2[] = {"cat", "-e", NULL};

	ast = btree_create_node((void *) ast_create_node(MSH_PIPE, (void *) malloc(sizeof(t_ast_pipe))));
	ast->left = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_cmd))));
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->path = "../42_push_swap/push_swap";
	((t_ast_cmd *) ((t_ast_node *) ast->left->item)->data)->argv = argv1;
	//ast->right = btree_create_node((void *) ast_create_node(MSH_REDIRECT_R, (void *) malloc(sizeof(t_ast_pipe))));
	ast->right = btree_create_node((void *) ast_create_node(MSH_CMD, (void *) malloc(sizeof(t_ast_pipe))));
	((t_ast_cmd *) ((t_ast_node *) ast->right->item)->data)->path = "/usr/bin/cat";
	((t_ast_cmd *) ((t_ast_node *) ast->right->item)->data)->argv = argv2;
	//ast->right->right = btree_create_node((void *) ast_create_node(MSH_FILE,(void *) malloc(sizeof(t_ast_pipe))));

	ast_exec(ast);
}
