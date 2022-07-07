/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:27 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/07 16:48:47 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_AST_H
# define MSH_AST_H

# include "btree.h"

typedef enum s_ast_type
{
	MSH_PIPE,
	MSH_CMD,
	MSH_REDIRECT_R,
	MSH_REDIRECT_RR,
	MSH_REDIRECT_L,
	MSH_REDIRECT_LL,
	MSH_FILE,
	MSH_AST_TYPE_END
}				t_ast_type;

# define MSH_AST_TYPE_CNT MSH_AST_TYPE_END

typedef struct s_ast_node
{
	t_ast_type	type;
	int			fd_in;
	int			fd_out;
	void		*data;
}				t_ast_node;

typedef struct s_ast_pipe
{
	int	pipefd[2];
}				t_ast_pipe;

typedef struct s_ast_cmd
{
	char	*name;
}				t_ast_cmd;

void		ast_exec(t_btree *root);
void		ast_exec_node(t_btree *node);
t_ast_node	*ast_create_node(t_ast_type type, void *data);

#endif
