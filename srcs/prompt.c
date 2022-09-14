/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:53:53 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/14 21:15:38 by heboni           ###   ########.fr       */
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
	if (strncmp(cwd, home, strlen(home)) == 0)
	{
		cwd_start = strlen(home) - 1;
		cwd[cwd_start] = '~';
	}
	n = 0;
	n += strlen(SH_FG_GREEN);
	n += strlen(username);
	n += strlen(SH_FG_RESET);
	++n;
	n += strlen(SH_FG_CYAN);
	n += strlen(cwd);
	n += strlen(SH_FG_RESET);
	n += 2;
	prompt = (char *) malloc((n + 1) * sizeof(char));
	n = 0;
	strcpy(prompt + n, SH_FG_GREEN);
	n += strlen(SH_FG_GREEN);
	strcpy(prompt + n, username);
	n += strlen(username);
	strcpy(prompt + n, SH_FG_RESET);
	n += strlen(SH_FG_RESET);
	strcpy(prompt + n, ":");
	++n;
	strcpy(prompt + n, SH_FG_CYAN);
	n += strlen(SH_FG_CYAN);
	strcpy(prompt + n, cwd + cwd_start);
	n += strlen(cwd + cwd_start  );
	strcpy(prompt + n, SH_FG_RESET);
	n += strlen(SH_FG_RESET);
	strcpy(prompt + n, "$ ");
	return (prompt);
}
