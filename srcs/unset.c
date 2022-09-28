/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:18:25 by heboni            #+#    #+#             */
/*   Updated: 2022/09/29 22:40:39 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_valid(char *argv)
{
	int	len;
	int	i;
	
	i = -1;
	len = ft_strlen(argv);
	while (++i < len)
	{
		if (!(ft_isalpha(argv[i]) || argv[i] == '_' || (ft_isdigit(argv[i]) && i != 0)))
			return (i);
			
	}
	return (0);
}


int	unset(t_env **envs, char **argv, int fd)
{
	int	n;
	
	if (!envs)
		return (-1);
	if (!argv)
		return (0);
	while (*argv != NULL)
	{
		if (is_not_valid(*argv))
		{
			ft_putstr_fd("bash: unset: '", fd);
			ft_putstr_fd(*argv, fd);
			ft_putstr_fd("': not a valid identifier\n", fd);
		}
		else
		{
			n = get_env_n_if_exists(*envs, *argv);
			printf("[unset1] %d\n", n);
			if (n != 0)
				env_lst_remove_n_node(envs, n);
		}
			
		argv++;
	}
	return (0);
}
