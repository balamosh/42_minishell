/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_ast_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:32:22 by heboni            #+#    #+#             */
/*   Updated: 2022/09/21 07:38:23 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *tokens_to_ast_nodes(char **tokens, int tokens_count, int *exeption_indexes, int exeption_indexes_n)
{
	int			token_i;
	t_ast_node	*ast_nodes;

	token_i = -1; //TO DO норм, что я не выделяю динамически память, при этом дальше в ф-ии передаю адрес лок. переменной этой ф-ии
	ast_nodes = NULL;
	while (++token_i < tokens_count)
	{
		// printf("%s\n", *tokens);
		//TO DO оптимизировать if else: вынести на уровень выше is_real_token
		if (ft_strcmp(tokens[token_i], "|") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_PIPE);
		else if (ft_strcmp(tokens[token_i], ">") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_R);
		else if (ft_strcmp(tokens[token_i], ">>") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_RR);
		else if (ft_strcmp(tokens[token_i], "<") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_L);
		else if (ft_strcmp(tokens[token_i], "<<") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_LL);
		else
			ast_cmd_node_lst_push_bottom(&ast_nodes, tokens, &token_i, MSH_CMD); //в аргументы нужно сложить все токены до 1-го | <
		printf("tokens[%d]: %s\n", token_i, tokens[token_i]);
	}
	printf(" [tokens_to_ast_nodes] END\n");
	return (ast_nodes);
}

t_ast_node *tokens_to_ast_nodes0(char **tokens, int *exeption_indexes, int exeption_indexes_n)
{
	int	token_i;
	int	tmp_token_i;
	t_ast_node *ast_nodes;
	char **tokens_pntr = tokens;

	token_i = 0;
	ast_nodes = NULL;
	while (*tokens != NULL) //while (tokens[token_i] != NULL) //sega при разыменовании индекса token_i++
	{
		tmp_token_i = token_i;
		// printf("%s\n", *tokens);
		if (ft_strcmp(tokens_pntr[token_i], "|") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_PIPE);
		else if (ft_strcmp(tokens_pntr[token_i], ">") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_R);
		else if (ft_strcmp(tokens_pntr[token_i], ">>") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_RR);
		else if (ft_strcmp(tokens_pntr[token_i], "<") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_L);
		else if (ft_strcmp(tokens_pntr[token_i], "<<") == 0 && is_real_token(exeption_indexes, exeption_indexes_n, token_i))
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_LL);
		else
		{
			printf("no seg %s\n", tokens_pntr[token_i]);
			// ast_cmd_node_lst_push_bottom0(&ast_nodes, tokens_pntr, token_i, MSH_CMD); //в аргументы нужно сложить все токены до 1-го | <
			ast_cmd_node_lst_push_bottom(&ast_nodes, tokens_pntr, &token_i, MSH_CMD);
			printf("token_i = %d\n", token_i);
		}
		printf("tokens_pntr[%d]: %s\n", token_i, tokens_pntr[token_i]); // printf("%s\n", *tokens++);
		token_i++;
		int i = -1;
		while (++i < (token_i - tmp_token_i))
			*tokens++;
		printf("*tokens: %s\n", *tokens);
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