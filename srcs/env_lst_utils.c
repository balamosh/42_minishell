/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 08:58:55 by heboni            #+#    #+#             */
/*   Updated: 2022/09/14 21:15:17 by heboni           ###   ########.fr       */
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

void	print_env_list(t_env **lst)
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