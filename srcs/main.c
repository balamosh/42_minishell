/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/04 21:38:01 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
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
		// print_tokens_array(tokens, 0);
		// free_tokens_array(tokens);

		ast_nodes = parser(line, &envs_lst);
		if (ast_nodes == NULL)
			continue;
		print_nodes_list(ast_nodes);
		free_nodes_lst(&ast_nodes);
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
		free(*ast_nodes);
		*ast_nodes = tmp;
		//зафришить t_ast_cmd
	}
	printf("[free_nodes_lst END]\n");
}

void	free_tokens_array(char **tokens)
{
	int	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}
