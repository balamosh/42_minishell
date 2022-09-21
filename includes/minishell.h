/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:04 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/13 11:39:59 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include "libft.h"
# include "btree.h"

typedef enum s_tok_type
{
	MSH_PIPE,
	MSH_CMD,
	MSH_REDIRECT_R,
	MSH_REDIRECT_RR,
	MSH_REDIRECT_L,
	MSH_REDIRECT_LL,
	MSH_AST_TYPE_END
}				t_tok_type;

typedef struct s_token
{
	void	*key;
	char	*value;
}				t_token;

# define MSH_AST_TYPE_CNT MSH_AST_TYPE_END

typedef struct s_ast_node
{
	t_tok_type	type;
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
	char	*path;
	char	**argv;
}				t_ast_cmd;

typedef struct s_ast_redir
{
	char	*word;
}				t_ast_redir;

typedef struct s_msh
{
	t_btree	*ast;
}				t_msh;

void		ast_exec(t_btree *root);
void		ast_exec_node(t_btree *node);
void		dup_check(int fd, int oldfd);
void		close_check(int fd);
t_ast_node	*ast_create_node(t_tok_type type, void *data);

char		*get_prompt(void);

#endif
