/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/09 02:21:04 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_exec_pipe(t_btree *node)
{
	t_ast_pipe	*pipe_node;

	pipe_node = (t_ast_pipe *) ((t_ast_node *) node->item)->data;
	pipe(pipe_node->pipefd);
	((t_ast_node *) node->left->item)->fd_in = ((t_ast_node *) node->item)->fd_in;
	((t_ast_node *) node->left->item)->fd_out = pipe_node->pipefd[1];
	((t_ast_node *) node->right->item)->fd_out = ((t_ast_node *) node->item)->fd_out;
	((t_ast_node *) node->right->item)->fd_in = pipe_node->pipefd[0];
}

void	dup_check(int fd, int oldfd)
{
	if (!isatty(fd))
		dup2(fd, oldfd);
}

void	close_check(int fd)
{
	if (!isatty(fd))
		close(fd);
}

void	ast_exec_cmd(t_btree *node)
{
	pid_t		pid;
	t_ast_node	*ast_node;
	t_ast_cmd	*cmd_node;

	ast_node = (t_ast_node *) node->item;
	cmd_node = (t_ast_cmd *) ast_node->data;
	pid = fork();
	if (pid == 0)
	{
		dup_check(ast_node->fd_in, STDIN_FILENO);
		dup_check(ast_node->fd_out, STDOUT_FILENO);
		close_check(ast_node->fd_in);
		close_check(ast_node->fd_out);
		execve(cmd_node->path, cmd_node->argv, NULL);
	}
	else
	{
		close_check(ast_node->fd_in);
		close_check(ast_node->fd_out);
		waitpid(pid, NULL, 0);
	}
}

void	ast_exec_rr(t_btree *node)
{
	t_ast_node	*ast_node;
	t_ast_redir	*redir_node;
	int			fd;

	ast_node = (t_ast_node *) node->item;
	redir_node = (t_ast_redir *) ast_node->data;
	fd = open(redir_node->word, O_WRONLY | O_CREAT, S_IRWXU);
	((t_ast_node *) node->left->item)->fd_out = fd;
}

void	ast_exec_rrr(t_btree *node)
{
	t_ast_node	*ast_node;
	t_ast_redir	*redir_node;
	int			fd;

	ast_node = (t_ast_node *) node->item;
	redir_node = (t_ast_redir *) ast_node->data;
	fd = open(redir_node->word, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	((t_ast_node *) node->left->item)->fd_out = fd;
}

void	ast_exec_rl(t_btree *node)
{
	t_ast_node	*ast_node;
	t_ast_redir	*redir_node;
	int			fd;

	ast_node = (t_ast_node *) node->item;
	redir_node = (t_ast_redir *) ast_node->data;
	fd = open(redir_node->word, O_RDONLY);
	((t_ast_node *) node->left->item)->fd_in = fd;
}

void	ast_exec_rll(t_btree *node)
{
	t_ast_node	*ast_node;
	t_ast_redir	*redir_node;
	int			pipefd[2];
	char		*line;

	ast_node = (t_ast_node *) node->item;
	redir_node = (t_ast_redir *) ast_node->data;
	pipe(pipefd);
	while (TRUE)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir_node->word) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
	}
	close(pipefd[1]);
	((t_ast_node *) node->left->item)->fd_in = pipefd[0];
}

void	ast_exec_node(t_btree *node)
{
	t_ast_node	*ast_node;
	static void	(*exec[MSH_AST_TYPE_CNT])(t_btree *) = \
	{ast_exec_pipe, ast_exec_cmd, \
	ast_exec_rr, ast_exec_rrr, ast_exec_rl, ast_exec_rll};

	ast_node = (t_ast_node *) node->item;
	exec[ast_node->type]((void *) node);
}

void	ast_exec(t_btree *root)
{
	if (!root)
		return ;
	ast_exec_node(root);
	ast_exec(root->left);
	ast_exec(root->right);
}
