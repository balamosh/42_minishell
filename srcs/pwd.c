/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:58:04 by heboni            #+#    #+#             */
/*   Updated: 2022/09/24 13:20:23 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include <stdio.h> //del
# include <unistd.h> //del
# include <stdlib.h> //del

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

int	pwd(int fd)
{
	char	*dir;

	dir = getcwd(NULL, 0); //dir и buf указывают на один и тот же кусок памяти
	if (dir == NULL)
		return (1);
	ft_putstr_fd(dir, fd);
	write(fd, "\n", 1);
	free(dir);
	return (0);
}

int	main(void)
{
	pwd(1);
	return (0);
}