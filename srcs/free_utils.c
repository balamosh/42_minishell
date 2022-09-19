/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:44:50 by heboni            #+#    #+#             */
/*   Updated: 2022/09/19 20:25:59 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes_lst(t_ast_node **ast_nodes)
{
	t_ast_node *next;
	
	printf("[free_nodes_lst]\n");
	if (!ast_nodes)
	{
		printf("[free_nodes_lst END NO AST_NODES]\n");
		return ;
	}
	while (*ast_nodes)
	{
		next = (*ast_nodes)->next;
		if ((*ast_nodes)->data)
		{
		// 	if ((*ast_nodes)->type == MSH_CMD)
		// 	{
		// 		printf("CMD FREE START\n");
		// 		t_ast_cmd *cmd = (t_ast_cmd *)(*ast_nodes)->data;
		// 		free(cmd->cmd_name); printf("free cmd_name\n");
		// 		// free(cmd->path); printf("free cmd->path\n");
		// 		if (cmd->argv)
		// 		{
		// 			printf("cmd->argv = %p\n", cmd->argv);
		// 			free_string_array(cmd->argv); 
		// 			printf("free cmd->argv\n");
		// 		}
		// 	}
			free((*ast_nodes)->data); printf("free (*ast_nodes)->data\n");
		}
		free(*ast_nodes); printf("free *ast_nodes\n");
		*ast_nodes = next;
	}
	printf("[free_nodes_lst END]\n");
}

void	lstclear(t_ast_node **lst)
{
	t_ast_node	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free(((*lst)));
		*lst = next;
	}
}

void	free_string_array(char **argv)
{
	int	i = -1;

	if (!argv)
		return ;
	while (argv[++i]) //TO DO в get_cmd_node_argv выделила память на элемент (char *)==NULL в конце, тут, получается не фришу этот указатель, утечек при этом нет
		free(argv[i]);
	free(argv);
}
