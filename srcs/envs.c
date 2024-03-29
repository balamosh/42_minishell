/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:28:42 by heboni            #+#    #+#             */
/*   Updated: 2022/08/05 15:33:18 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	**get_envs(char **env)
{
	t_env	**envs_lst;
	int		env_count;

	env_count = get_env_count(env);
	envs_lst = (t_env **)malloc(sizeof(t_env *) * env_count + 1);
	if (envs_lst == NULL)
		exit(STACK_OVERFLOW);
	envs_lst[env_count + 1] = NULL;
	envs_saver(env, envs_lst);
	return (envs_lst);
}

void	envs_saver(char **env, t_env **envs_lst)
{
	t_env	*env_node;
	char 	*name;
	char	*value;
	int		i;
	int 	k;
	
	while (*env)
	{
		i = -1;
		while ((*env)[++i] != '=')	
		name = (char *)malloc(sizeof(char) * i + 1);
		if (name == NULL)
			exit(STACK_OVERFLOW);
		k = -1;
		while (++k < i)
			name[k] = (*env)[k];
		name[i] = '\0';
		k++; //после '='
		i++; //после '='
		while ((*env)[i++] != '\0')
		value = get_env_value_to_save(*env, i, k);
		env_node = env_lst_new(name, value);
		env_lst_add_back(envs_lst, env_node);
		env++;
	}
}

char	*get_env_value_to_save(char *env, int i, int k)
{
	char	*value;
	int		l;

	l = 0;
	value = (char *)malloc(sizeof(char) * (i - k) + 1);
	if (value == NULL)
		exit(STACK_OVERFLOW);
	while (l < (i - k))
	{
		value[l] = env[k + l];
		l++;
	}
	value[i - k] = '\0';
	return (value);
}
