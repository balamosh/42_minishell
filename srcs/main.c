/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/09 02:21:22 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_ast();

int	main(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	while (TRUE)
	{
		line = readline(prompt);
		if (line && ft_strlen(line))
			add_history(line);
		if (!line)
			break ;
	}
	return (0);
}
