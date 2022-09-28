/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:17:49 by heboni            #+#    #+#             */
/*   Updated: 2022/09/29 21:30:24 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print_env_list(t_env *envs, int fd)
{
	printf("\n---------------export_print_env_list--------------\n");
	if (!envs)
		return ;
	while (envs)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(envs->var_name, fd);
		if (envs->var_value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(envs->var_value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		envs = envs->next;
	}
	printf("\n");
}

int	get_envs_count(t_env *envs)
{
	int	envs_count;
	
	envs_count = 0;
	while (envs)
	{
		envs_count++;
		envs = envs->next;
	}
	printf("[get_envs_count] %d\n", envs_count);
	return (envs_count);
}

void	alphabetical_envs_print(t_env *envs, int fd)
{
	t_env	*tmp_envs;
	int		envs_count;
	int		i;
	
	i = -1;
	envs_count = get_envs_count(envs);
	while (++i < envs_count)
	{
		tmp_envs = envs;
		while (tmp_envs)
		{
			if (tmp_envs->next)
			{
				// printf("\n%s, %s: ", (tmp_envs->var_name), ((tmp_envs->next)->var_name));
				if (tmp_envs->var_name[0] > (tmp_envs->next)->var_name[0])
				{
					char *tmp_name = tmp_envs->var_name;
					char *tmp_value = tmp_envs->var_value;
					tmp_envs->var_name = (tmp_envs->next)->var_name;
					tmp_envs->var_value = (tmp_envs->next)->var_value;
					(tmp_envs->next)->var_name = tmp_name;
					(tmp_envs->next)->var_value = tmp_value;
				}
			}
			tmp_envs = tmp_envs->next;
		}
	}
	export_print_env_list(envs, fd);
}

char	*get_env_name_to_buildin(char *argv, int *i, int *k)
{
	char	*name;
	
	*i = -1;
	while (argv[++(*i)] != '=' && argv[(*i)] != '\0' && !(argv[(*i)] == '\"' && argv[(*i) + 1] == '=') \
													 && !(argv[(*i)] == '\'' && argv[(*i) + 1] == '=')) {}
	name = (char *)malloc(sizeof(char) * (*i) + 1); 
	if (name == NULL)
		exit(STACK_OVERFLOW);
	*k = -1;
	while (++(*k) < *i)
		name[*k] = argv[*k];
	name[*k] = '\0';
	return (name);
}

int	export_builtin(t_env *envs, char **argv, int fd)
{
	char	*name;
	char	*value;
	int		i;
	int		k;

	if (!envs)
		return (-1);
	if (!argv)
		alphabetical_envs_print(envs, fd);
	else
	{
		while (*argv != NULL)
		{
			name = get_env_name_to_buildin(*argv, &i, &k);
			// printf("%s\n", *argv); printf("[export] i=%d, k=%d\n", i, k); printf("[export] name: %s\n", name);
			int j = is_not_valid(name);
			if (j || (j == 0 && ft_isdigit(name[0])))
			{
				printf("bash: export: '%s' '%c': not a valid identifier\n", name, (*argv)[j]);
			}
			else
			{
				if ((*argv)[i] != '\0')
				{
					if ((*argv)[i] == '\'' || (*argv)[i] == '\"')
					{
						k = k + 3; //после '=' "="
						i = i + 3;
					}
					else
					{
						k++; //после =
						i++;
					}
					while ((*argv)[i++] != '\0') {}
					value = get_env_value_to_save(*argv, i, k); // printf("[export] value: %s\n", value);
					if (!env_lst_update_node(envs, name, value))
						env_lst_push_bottom(&envs, name, value);
					free(value);
				}
				else
					env_lst_push_bottom(&envs, name, NULL);
			}
			free(name);
			argv++;
		}
	}
	return (0);
}
