/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:04 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/29 21:58:31 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include <string.h>

# include "libft.h"
# include "msh_ast.h"
# include "env.h"

# define STACK_OVERFLOW -1
# define INPUT_ERROR	-2

// struct s_msh	*msh_ctx;

typedef struct s_msh
{
	t_btree	*ast;
	t_env	*env;
	int		*exeption_indexes;
	int		exeption_indexes_n;
	int		not_closed_quote;
	int		cur_env_vars_len; //если $USER$TERM, то токен 1, token_len = len_env1_val + len_env2_val
}				t_msh;


char		*get_prompt(void);

// parser
t_ast_node	*parser(char *line, t_msh *msh_ctx);
char		**get_tokens(char *line, t_msh *msh_ctx, int **special_indexes, int *special_indexes_n);
int			is_exeption_token(char *line, int tmp_i, char c);

// array_realloc
char		**tokens_realloc(char **tokens, int tokens_count);
int			**int_array_realloc(int **array, int *array_n);

// lexer
int			single_quote_lexer(char *line, int i, t_msh *msh_ctx);
int			double_quotes_lexer(char *line, int i, t_msh *msh_ctx);
int			regular_char_lexer(char *line, int i, t_msh *msh_ctx);
int			special_chars_lexer(char *line, int i);

// token_saver
void		single_quote_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx);
void		double_quotes_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx);
void		regular_char_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx);
void		special_chars_token_saver(char **tokens, int token_n, char *line, int i);

// tokens_to_ast_nodes
t_ast_node 	*tokens_to_ast_nodes(char **tokens, int tokens_count, t_msh *msh_ctx);
int			is_real_token(int *special_indexes, int special_indexes_n, int token_i);

// ast.c
void		print_nodes_list(t_ast_node *ast_nodes);
int			is_special_token(char **tokens, int token_i, int *exeption_indexes, int exeption_indexes_n);
int			is_special_symbols(char *token);
void		ast_node_lst_push_bottom(t_ast_node **head, t_ast_type type);
void		ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int *i, t_ast_type type, t_msh *msh_ctx);
t_ast_node	*get_last_ast_node(t_ast_node *head);
char		**get_cmd_node_argv(char **tokens, int *token_i, t_msh *msh_ctx);

// free_utils.c
void		free_nodes_lst(t_ast_node **ast_nodes);
void		free_string_array(char **argv);

// utils
int 		get_tokens_count(char **tokens);
void		print_string_array(char **argv, int count);
void		print_int_array(int *array, int n);


// get_env
int		get_env_var_value_to_saver(char **tokens, int token_n, char *line, int i, t_env **envs, t_msh *msh_ctx);
int		get_env_var_value_to_lexer(char *line, int i, t_env **envs, t_msh *msh_ctx);
char	*get_env_value_by_name_from_envs(void *name, t_env *envs, t_msh *msh_ctx);
// char	*get_env_value_by_name_from_envs(void *name, t_env **envs, t_msh *msh_ctx);

// buildins
int		env_builtin(t_env *envs, char **argv, int fd);
int		export_builtin(t_env *envs, char **argv, int fd);
char	*get_env_name_to_buildin(char *argv, int *i, int *k);
int		unset(t_env **envs, char **argv, int fd);
int		is_not_valid(char *argv);

#endif
