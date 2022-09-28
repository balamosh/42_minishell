/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 08:58:55 by heboni            #+#    #+#             */
/*   Updated: 2022/09/29 22:38:23 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_push_bottom(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*last_node;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	// new->var_name = name;
	// new->var_value = value;
	new->var_name = ft_strdup(name);
	if (value)
		new->var_value = ft_strdup(value);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_node(*head);
	last_node->next = new;
}

t_env	*get_last_node(t_env *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	free_env_lst(t_env **lst)
{
	t_env	*next;
	
	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->var_name);
		free((*lst)->var_value);
		free(((*lst)));
		*lst = next;
	}
}

int	get_env_n_if_exists(t_env *envs, char *name)
{
	int	n;

	n = 1;
	while (envs)
	{
		if (ft_strcmp(envs->var_name, name) == 0)
			return (n);
		n++;
		envs = envs->next;
	}
	return (0);
}

int	env_lst_update_node(t_env *envs, char *name, char *value)
{
	while (envs)
	{
		if (ft_strcmp(envs->var_name, name) == 0)
		{
			free(envs->var_value);
			envs->var_value = ft_strdup(value);
			return (1);
		}
		envs = envs->next;
	}
	return (0);
}

t_env	*get_n_env_node(t_env *envs, int n)
{
	int		i;
	t_env	*n_node;

	//номер ноды начинается с 1
	i = 0;
	while (++i < n)
		envs = envs->next;
	n_node = envs;
	return (n_node);
}

void	env_lst_remove_n_node(t_env **envs, int n)
{
	t_env	*prev;
	t_env	*n_node;

	if (!envs)
		return ;
	n_node = get_n_env_node(*envs, n);
	printf("[env_lst_remove_node] n_node %s, %s\n", n_node->var_name, n_node->var_value);
	
	if (n == 1) //prev_node нет
		*envs = n_node->next;
	else
	{
		prev = get_n_env_node(*envs, n - 1);
		prev->next = n_node->next;
	}
	free(n_node->var_name);
	free(n_node->var_value);
	free(n_node);
	print_env_list(*envs);
}

void	print_env_list0(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	printf("\n---------------print_env_list--------------\n");
	tmp = *lst;
	while (tmp)
	{
		printf("%s, ", (char *)tmp->var_name);
		printf("%s \n", (char *)tmp->var_value);
		tmp = tmp->next;
	}
	printf("\n");
}

void	print_env_list(t_env *envs)
{
	printf("\n---------------print_envs--------------\n");
	if (!envs)
		return ;
	while (envs)
	{
		printf("%s, ", (char *)envs->var_name);
		printf("%s \n", (char *)envs->var_value);
		// envs->var_value = "hacked :)";
		envs = envs->next;
	}
	printf("\n");
}