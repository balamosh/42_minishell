/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/21 22:23:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ast_create_node(t_ast_type type, void *data)
{
	t_ast_node	*node;

	if (!data)
		return (NULL);
	node = (t_ast_node *) malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->data = data;
	return (node);
}

void	ast_node_lst_push_bottom(t_ast_node **head, t_ast_type type)
{
	t_ast_node	*new;
	t_ast_node	*last_node;
	t_ast_cmd	*cmd;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_ast_node(*head);
	last_node->next = new;
}


void	ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int *i, t_ast_type type, t_msh *msh_ctx)
{
	t_ast_node	*new;
	t_ast_node	*last_node;
	t_ast_cmd	*cmd;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	if (type == MSH_CMD)
	{
		cmd = (t_ast_cmd *)malloc(sizeof(t_ast_cmd));
		cmd->cmd_name = ft_strdup(tokens[*i]);
		new->data = cmd;
		new->fd_in = STDIN_FILENO;
		new->fd_out = STDOUT_FILENO;
		
		cmd->argv = get_cmd_node_argv(tokens, i, msh_ctx);
		print_string_array(cmd->argv, 0);
	}
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_ast_node(*head);
	last_node->next = new;
	return ;
}

char	**get_cmd_node_argv(char **tokens, int *token_i, t_msh *msh_ctx)
{
	char	**argv;
	int		tokens_count;
	int		argv_count;
	int		tmp_i;

	argv_count = 0;
	argv = NULL; //?
	tmp_i = *token_i;
	tokens_count = get_tokens_count(tokens);
	// printf("[get_cmd_node_argv] *token_i = %d, tokens_count = %d\n", *token_i, tokens_count);
	while (++(*token_i) < tokens_count) //с токена-команды переходим на токен-0-аргумент
	{
		if (is_special_token(tokens, *token_i, msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n))
			break;
		argv_count++;
	}
	(*token_i)--;
	// printf("[get_cmd_node_argv] *token_i to return = %d\n", *token_i);
	// printf("[get_cmd_node_argv] argv_count = %d\n", argv_count);
	
	argv = (char **)malloc(sizeof(char *) * (argv_count + 1));
	if (!argv)
		exit (STACK_OVERFLOW);
	
	int i = -1;
	while (++i < argv_count)
	{
		argv[i] = strdup(tokens[++tmp_i]);
		printf("[get_cmd_node_argv] argv[%d]=%s\n", i, argv[i]);
	}
	argv[i] = NULL;
	printf("[get_cmd_node_argv] END\n");
	return (argv);
}

//токен является специальным, если он один из (|<><<>>) И token_n нет в exeption_indexes
int	is_special_token(char **tokens, int token_i, int *exeption_indexes, int exeption_indexes_n) 
{
	int is_special;

	is_special = 0;
	if (!is_real_token(exeption_indexes, exeption_indexes_n, token_i))
		return (0);
	if (is_special_symbols(tokens[token_i]))
		is_special = 1;
	return (is_special);
}

int	is_special_symbols(char *token)
{
	int is_special;

	is_special = 0;
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 \
							|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
		is_special = 1;
	return (is_special);
}

t_ast_node	*get_last_ast_node(t_ast_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	print_nodes_list(t_ast_node *ast_nodes)
{	
	t_ast_cmd *cmd;
	
	if (ast_nodes == NULL)
	{
		printf("[print_nodes_list NO_LIST]\n");
		return ;
	}
	printf("[print_nodes_list]\n");
	while (ast_nodes)
	{
		printf("type: %u ", ast_nodes->type);
		if (ast_nodes->type == MSH_PIPE)
			printf("PIPE\n");
		if (ast_nodes->type == MSH_REDIRECT_L)
			printf("MSH_REDIRECT_L: < \n");
		if (ast_nodes->type == MSH_REDIRECT_LL)
			printf("MSH_REDIRECT_LL: << \n");
		if (ast_nodes->type == MSH_REDIRECT_R)
			printf("MSH_REDIRECT_R: > \n");
		if (ast_nodes->type == MSH_REDIRECT_RR)
			printf("MSH_REDIRECT_RR: >> \n");
		if (ast_nodes->type == MSH_CMD)
		{
			if (ast_nodes->data)
			{
				cmd = ast_nodes->data;
				printf("CMD->NAME: %s\n", cmd->cmd_name);
				// printf("CMD->ARGV: ");
				// while (*(cmd->argv) != NULL)
				// {
				// 	printf("%s ", *(cmd->argv));
				// 	(cmd->argv)++;
				// }
			}
		}
		ast_nodes = ast_nodes->next;
	}
	printf("[print_nodes_list END]\n\n");
}
