/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:44:50 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 09:19:14 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes_lst(t_ast_node **ast_nodes)
{
	t_ast_node *tmp;
	
	printf("[free_nodes_lst]\n");
	if (!ast_nodes)
	{
		printf("[free_nodes_lst END NO AST_NODES]\n");
		return ;
	}
	while (*ast_nodes)
	{
		tmp = (*ast_nodes)->next;
		if ((*ast_nodes)->data)
		{
			if ((*ast_nodes)->type == MSH_CMD)
			{
				t_ast_cmd *cmd = (t_ast_cmd *)(*ast_nodes)->data;
				free(cmd->cmd_name); printf("free cmd_name\n");
				// free(cmd->path); printf("free cmd->path\n");
				free_string_array(cmd->argv); printf("free cmd->argv\n");
			}
			free((*ast_nodes)->data);
		}
		free(*ast_nodes);
		*ast_nodes = tmp;
	}
	printf("[free_nodes_lst END]\n");
}

void	free_string_array(char **argv)
{
	int	i = -1;

	if (!argv)
		return ;
	if (argv[0])
		printf("FREE: argv[0] != NULL !!!!! \n");
	while (argv[++i])
	{
		// argv[0] != NULL, при этом pointer being freed was not allocated WTF???
		free(argv[i]); //когда теряется argv[0], pointer being freed was not allocated
	}
	free(argv);
}
