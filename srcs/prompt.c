/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:53:53 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/09 02:07:15 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define SH_FG_RED "\033[31m"
# define SH_FG_GREEN "\033[32m"
# define SH_FG_RESET "\033[39m"
# define SH_FG_CYAN "\033[36m"

char	*get_prompt(void)
{
	char	*prompt;
	char	*username;
	char	*home;
	char	cwd[100];
	int		cwd_start;
	int		n;

	username = getenv("USER");
	home = getenv("HOME");
	getcwd(cwd, 100);
	cwd_start = 0;
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		cwd_start = ft_strlen(home) - 1;
		cwd[cwd_start] = '~';
	}
	n = 0;
	n += ft_strlen(SH_FG_GREEN);
	n += ft_strlen(username);
	n += ft_strlen(SH_FG_RESET);
	++n;
	n += ft_strlen(SH_FG_CYAN);
	n += ft_strlen(cwd);
	n += ft_strlen(SH_FG_RESET);
	n += 2;
	prompt = (char *) malloc((n + 1) * sizeof(char));
	n = 0;
	ft_strcpy(prompt + n, SH_FG_GREEN);
	n += ft_strlen(SH_FG_GREEN);
	ft_strcpy(prompt + n, username);
	n += ft_strlen(username);
	ft_strcpy(prompt + n, SH_FG_RESET);
	n += ft_strlen(SH_FG_RESET);
	ft_strcpy(prompt + n, ":");
	++n;
	ft_strcpy(prompt + n, SH_FG_CYAN);
	n += ft_strlen(SH_FG_CYAN);
	ft_strcpy(prompt + n, cwd + cwd_start);
	n += ft_strlen(cwd + cwd_start  );
	ft_strcpy(prompt + n, SH_FG_RESET);
	n += ft_strlen(SH_FG_RESET);
	ft_strcpy(prompt + n, "$ ");
	return (prompt);
}
