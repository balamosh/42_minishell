/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_ast_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:32:22 by heboni            #+#    #+#             */
/*   Updated: 2022/09/21 22:23:04 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *tokens_to_ast_nodes(char **tokens, int tokens_count, t_msh *msh_ctx)
{
	int			token_i;
	t_ast_node	*ast_nodes;

	token_i = -1; //TO DO норм, что я не выделяю динамически память, при этом дальше в ф-ии передаю адрес лок. переменной этой ф-ии
	ast_nodes = NULL;
	while (++token_i < tokens_count)
	{
		// printf("%s\n", *tokens);
		//TO DO оптимизировать if else: вынести на уровень выше is_real_token
		if (ft_strcmp(tokens[token_i], "|") == 0 && is_real_token(msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_PIPE);
		else if (ft_strcmp(tokens[token_i], ">") == 0 && is_real_token(msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_R);
		else if (ft_strcmp(tokens[token_i], ">>") == 0 && is_real_token(msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_RR);
		else if (ft_strcmp(tokens[token_i], "<") == 0 && is_real_token(msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_L);
		else if (ft_strcmp(tokens[token_i], "<<") == 0 && is_real_token(msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_LL);
		else
			ast_cmd_node_lst_push_bottom(&ast_nodes, tokens, &token_i, MSH_CMD, msh_ctx); //в аргументы нужно сложить все токены до 1-го | <
		printf("tokens[%d]: %s\n", token_i, tokens[token_i]);
	}
	printf(" [tokens_to_ast_nodes] END\n");
	return (ast_nodes);
}

int	is_real_token(int *exeption_indexes, int exeption_indexes_n, int token_i)
{
	int	i;
	int	is_real_token;

	i = -1;
	is_real_token = 1;
	while (++i < exeption_indexes_n)
	{
		if (token_i == exeption_indexes[i])
		{
			is_real_token = 0;
			break;
		}
	}
	return (is_real_token);
}
