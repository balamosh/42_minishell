/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/14 09:57:47 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	// t_msh	*msh_ctx;
	char	*line;
	char	*prompt;
	t_env	*envs_lst;
	char	**tokens;
	t_ast_node *ast_nodes;

	if (argc != 1)
		exit(INPUT_ERROR);
	envs_lst = NULL;
	envs_saver(env, &envs_lst);
	print_env_list(&envs_lst);
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);
	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		printf("[main] line: %s\n", line);
		if (line && strlen(line))
			add_history(line);
		if (!line)
			break ;

		// tokens = lexer(line, &envs_lst);
		// if (tokens == NULL)
		// 	continue;
		// printf("[main] ");
		// print_string_array(tokens, 0);
		// free_string_array(tokens);
		msh_ctx->not_closed_quote = 0;
		ast_nodes = parser(line, &envs_lst);
		if (ast_nodes == NULL || msh_ctx->not_closed_quote == 1)
			continue;
		printf("[main] "); print_nodes_list(ast_nodes);
		free_nodes_lst(&ast_nodes); //TO DO free (t_ast_cmd->argv, t_ast_cmd->name, t_ast_cmd->path и сам t_ast_cmd)
		free(line);
		
		// free_env_lst(&envs_lst); free(prompt); return(0); //to test leaks

	}
	free_env_lst(&envs_lst);
	free(prompt);
	return (0);
}

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
	while (argv[++i])
		free(argv[i]); //когда теряется argv[0], pointer being freed was not allocated
	free(argv);
}
