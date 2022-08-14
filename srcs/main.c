/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/08/14 11:54:44 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt;
	t_env	**envs;
	char	**tokens;

	if (argc != 1)
		exit(INPUT_ERROR);
	envs = get_envs(env);
	// print_env_list(envs);
	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		printf("[main] line: %s\n", line);
		if (line && strlen(line))
			add_history(line);
		if (!line)
			break ;
		tokens = lexer(line, envs);
		printf("[main] ");
		print_tokens_array(tokens, 0);
		free(line);
		while (*tokens)
		{
			free(*tokens);
			tokens++;
		}
	// 	free(tokens); //почему с этой строкой abort: pointer being freed was not allocated?
	}
	free_env_lst(envs);
	return (0);
}
