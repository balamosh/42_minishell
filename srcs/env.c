/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:15:23 by heboni            #+#    #+#             */
/*   Updated: 2022/09/30 18:13:46 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin_print(t_env *envs, int fd)
{
	while (envs)
	{
		if (envs->var_value)
		{
			ft_putstr_fd(envs->var_name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(envs->var_value, fd);
			ft_putstr_fd("\n", fd);
		}
		envs = envs->next;
	}
}

int	is_equal_symbol(char *argv)
{
	while(*argv != '\0')
	{
		if (*argv == '=')
			return (1);
		argv++;
	}
	return (0);
}

void	add_var_from_env(t_env *envs, char *argv)
{
	
}

//env должен распечатывать переменные как в случае добавления новой, так и в случае вызова без аргументов
// TO DO env TEST=test
int	env_builtin(t_env *envs, char **argv, int fd)
{
	char	**tmp_argv;
	char	*name;
	char	*value;
	int		i;
	int		k;
	
	if (!envs)
		return (-1);
	if (!argv)
	{
		env_builtin_print(envs, fd);
		return (0);
	}
	tmp_argv = argv;
	//сперва проверить, что все переменные без значений есть //?
	while (*tmp_argv != NULL)
	{
		name = get_env_name_to_buildin(*tmp_argv, &i, &k);
		if (!get_env_n_if_exists(envs, name) && !is_equal_symbol(*tmp_argv))
		{
			ft_putstr_fd("env: ", fd);
			ft_putstr_fd(*tmp_argv, fd);
			ft_putstr_fd(": No such file or directory\n", fd);
			free(name);
			return (1); //в такой случае какой статус команды?
		}
		free(name);
		tmp_argv++;
	}
	while (*argv != NULL)
	{
		//уже есть такая переменная
		
		// add_var_from_env(envs, *argv);
		argv++;
	}
	env_builtin_print(envs, fd);
	return (0);
}
