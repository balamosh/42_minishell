/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:13:34 by sotherys          #+#    #+#             */
/*   Updated: 2022/08/01 23:04:38 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/btree.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	(*applyf)(root -> item);
	btree_apply_prefix(root -> left, applyf);
	btree_apply_prefix(root -> right, applyf);
}
