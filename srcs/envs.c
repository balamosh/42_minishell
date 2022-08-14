/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:28:42 by heboni            #+#    #+#             */
/*   Updated: 2022/09/03 19:54:10 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envs_saver(char **env, t_env **envs_lst)
{
	char 	*name;
	char	*value;
	int		i;
	int 	k;
	
	while (*env)
	{
		i = -1;
		while ((*env)[++i] != '=') {}
		name = (char *)malloc(sizeof(char) * i + 1); 
		if (name == NULL)
			exit(STACK_OVERFLOW);
		k = -1;
		while (++k < i)
			name[k] = (*env)[k];
		name[k] = '\0';
		k++; //после '='
		i++; //после '='
		while ((*env)[i++] != '\0') {}
		value = get_env_value_to_save(*env, i, k);
		env_lst_push_bottom(envs_lst, name, value);
		free(name);
		free(value);
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
	value[l] = '\0';
	return (value);
}

char	*get_env_value_by_name(void *name, t_env **envs)
{
	t_env	*tmp;

	if (!envs)
		return NULL;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp((char *)name, (char *)tmp->var_name) == 0)
		{
			cur_env_vars_len += ft_strlen((char *)tmp->var_value);
			return((char *)tmp->var_value);
		}
		tmp = tmp->next;
	}
	return NULL;
}
