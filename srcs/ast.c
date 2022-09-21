/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/13 11:38:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ast_create_node(t_tok_type type, void *data)
{
	t_ast_node	*node;

	if (!data)
		return (NULL);
	node = (t_ast_node *) malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->data = data;
	return (node);
}
