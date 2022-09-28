/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:21:59 by heboni            #+#    #+#             */
/*   Updated: 2022/09/26 18:19:29 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include <stdio.h> //del
# include <unistd.h> //del
# include <stdlib.h> //del
# include <signal.h>

size_t	ft_strlen(const char *s) //del
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

void	ft_putstr_fd(char *s, int fd) //del
{
	int	len;

	if (fd < 0 || !s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	exit_builtin(pid_t ppid) //exit #include <stdlib.h> //завершает текущий процесс, переходит к родительскому
{
	ft_putstr_fd("exit\n", 1);
	//узнать pid родительского процесса и отправить сигнал kill 
	kill(ppid, SIGKILL);
	return (0);
}

int	main(void)
{
	pid_t ppid = getppid();
	exit_builtin(ppid);
	return (0);
}