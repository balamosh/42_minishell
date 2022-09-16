/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/16 09:27:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	ast_exec_pipe(t_btree *node)
{
	t_ast_pipe	*pipe_node;

	(void) node;
	pipe_node = (t_ast_pipe *) ((t_ast_node *) node->item)->data;
	pipe(pipe_node->pipefd);
	((t_ast_node *) node->left->item)->fd_in = ((t_ast_node *) node->item)->fd_in;
	((t_ast_node *) node->left->item)->fd_out = pipe_node->pipefd[1];
	((t_ast_node *) node->right->item)->fd_in = pipe_node->pipefd[0];
	//printf("%d >\n", ((t_ast_node *) node->item)->fd_in);
	//printf("executing pipe: %d -> %d\n", pipe_node->pipefd[0], pipe_node->pipefd[1]);
	//printf("> %d\n", ((t_ast_node *) node->item)->fd_out);
	//printf("\n");
}

void	dup_check(int fd, int oldfd)
{
	if (fd != 0 && fd != 1 && fd != 2)
		dup2(fd, oldfd);
}

void	close_check(int fd)
{
	if (fd != 0 && fd != 1 && fd != 2)
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
	//printf("%d >\n", ((t_ast_node *) node->item)->fd_in);
	//printf("executing cmd: %s\n", cmd_node->name);
	//printf("> %d\n", ((t_ast_node *) node->item)->fd_out);
	//printf("\n");
}

void	ast_exec_rr(t_btree *node)
{
	t_ast_pipe	*pipe_node;

	(void) node;
	pipe_node = (t_ast_pipe *) ((t_ast_node *) node->item)->data;
	pipe(pipe_node->pipefd);
	((t_ast_node *) node->left->item)->fd_in = ((t_ast_node *) node->item)->fd_in;
	((t_ast_node *) node->left->item)->fd_out = pipe_node->pipefd[1];
	((t_ast_node *) node->right->item)->fd_in = pipe_node->pipefd[0];
	//printf("%d >\n", ((t_ast_node *) node->item)->fd_in);
	//printf("executing > : %d -> %d\n", pipe_node->pipefd[0], pipe_node->pipefd[1]);
	//printf("> %d\n", ((t_ast_node *) node->item)->fd_out);
	//printf("\n");
}

void	ast_exec_rrr(t_btree *node)
{
	(void) node;
	printf("executing >>\n");
}

void	ast_exec_rl(t_btree *node)
{
	(void) node;
	printf("executing <\n");
}

void	ast_exec_rll(t_btree *node)
{
	(void) node;
	printf("executing <<\n");
}

void	ast_exec_file(t_btree *node)
{
	(void) node;
	printf("%d >\n", ((t_ast_node *) node->item)->fd_in);
	printf("executing file\n");
	printf("> %d\n", ((t_ast_node *) node->item)->fd_out);
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
