/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 09:49:28 by heboni            #+#    #+#             */
/*   Updated: 2022/09/24 11:56:15 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include <stdio.h> //del
# include <unistd.h> //del


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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	if (s1[i] == '\200' && s2[i] == '\0')
		return (1);
	if (s1[i] == '\0' && s2[i] == '\200')
		return (1);
	c1 = s1[i];
	c2 = s2[i];
	return (c1 - c2);
}

char	*get_echo_delimiter(char **argv, int n_flag)
{
	char	*c;

	if (*argv != NULL)
		c = " ";
	else
	{
		c = "\n";
		if (n_flag)
			c = "\0";
	}
	return (c);
}

int	echo(char **argv, int fd)
{
	int		len;
	int		returned_v;
	int		n_flag;
	char	*c;

	n_flag = 0;
	if (ft_strcmp("-n", *argv) == 0)
	{
		n_flag = 1;
		argv++;
	}
	while (*argv)
	{
		len = ft_strlen(*argv);
		returned_v = write(fd, *argv, len);
		if (returned_v == -1)
			return (1);
		argv++;
		c = get_echo_delimiter(argv, n_flag);
		returned_v = write(fd, c, 1);
		if (returned_v == -1)
			return (1);
	}
	return (0);
}

int	main(void)
{
	char	*argv[4] = {"-", "ab", NULL, NULL};

	echo(argv, 1);
	return (0);
}
