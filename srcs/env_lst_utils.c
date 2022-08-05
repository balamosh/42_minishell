/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 08:58:55 by heboni            #+#    #+#             */
/*   Updated: 2022/08/05 14:25:23 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_count(char **env)
{
	int	env_count;

	env_count = 0;
	while (*env)
	{
		env_count++;
		env++;
	}
	return (env_count);
}

t_env	*env_lst_new(void *var_name, void *var_value)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (((void *)0));
	list->var_name = var_name;
	list->var_value = var_value;
	list->next = ((void *)0);
	return (list);
}

void	env_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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

void	free_env_lst(t_env **lst)
{
	if (!lst)
		return ;
	while (*lst)
	{
		free((*lst)->var_name);
		free((*lst)->var_value);
		*lst = (*lst)->next;
	}
	free(lst);
}

void	print_env_list(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	printf("\n---------------print_env_list--------------\n");
	tmp = *lst;
	while (tmp)
	{
		printf("%s ,", (char *)tmp->var_name);
		printf("%s \n", (char *)tmp->var_value);
		tmp = tmp->next;
	}
	printf("\n");
}