/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/21 07:43:39 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_msh		*msh_ctx;
	char		*line;
	char		*prompt;
	t_env		*envs_lst;
	char		**tokens;
	t_ast_node	*ast_nodes;

	if (argc != 1)
		exit(INPUT_ERROR);
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);

	msh_ctx->env = NULL;
	envs_saver(env, &msh_ctx->env);
	print_env_list(msh_ctx->env); 

	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		printf("[main] line: %s\n", line);
		if (line && strlen(line))
			add_history(line);
		if (!line)
			break ;

		msh_ctx->not_closed_quote = 0;
		ast_nodes = parser(line, msh_ctx);
		if (ast_nodes == NULL || msh_ctx->not_closed_quote == 1)
			continue;
		printf("\n[main] "); print_nodes_list(ast_nodes);
		free_nodes_lst(&ast_nodes);
		free(line);
	}
	free_env_lst(&msh_ctx->env);
	free(prompt);
	free(msh_ctx);
	return (0);
}
