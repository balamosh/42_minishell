/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:08:59 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/15 21:51:52 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	node = (t_btree *) malloc(sizeof(t_btree));
	if (!node)
		return (NULL);
	node -> left = NULL;
	node -> right = NULL;
	node -> item = item;
	return (node);
}
