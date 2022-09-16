/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_saver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:28:42 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 09:25:02 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
