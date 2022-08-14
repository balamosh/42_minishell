/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:04 by sotherys          #+#    #+#             */
/*   Updated: 2022/09/04 22:32:16 by heboni           ###   ########.fr       */
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

int	cur_env_vars_len;

typedef struct s_msh
{
	t_btree	*ast;
	t_env	*env;
}				t_msh;

typedef struct s_lst_elems //нужна ли это структура, можно просто добавить в t_ast_node *next
{
	t_ast_node			*elem;
	struct s_lst_elems	*next;
}					s_lst_elems;

char	*get_prompt(void);

//main
void	free_tokens_array(char **tokens);

//lexer + parser
char	**lexer(char *line, t_env **envs);
char	**get_tokens(char *line, t_env **envs, int **special_indexes, int *special_indexes_n);
char	**tokens_realloc(char **tokens, int tokens_count);
int		**int_array_realloc(int **array, int *array_n);
int		single_quote_lexer(char *line, int i, t_env **envs);
int		double_quotes_lexer(char *line, int i, t_env **envs);
int		regular_char_lexer(char *line, int i, t_env **envs);
int		special_chars_lexer(char *line, int i);
int		is_exeption_token(char *line, int tmp_i, char c);
void	single_quote_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs);
void	double_quotes_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs);
void	regular_char_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs);
void	special_chars_token_saver(char **tokens, int token_n, char *line, int i);
int		get_env_var_value_to_saver(char **tokens, int token_n, char *line, int i, t_env **envs);
int		get_env_var_value(char *line, int i, t_env **envs);
void	get_env_name_from_line(char **var_name, char *line, int tmp_i);
// int		get_env_var_value(char *line, int i, int quotes_handler, t_env **envs);
// void	get_env_name_from_line(char **var_name, char *line, int tmp_i, int quotes_handler);
int 	get_tokens_count(char **tokens);
void	print_tokens_array(char **tokens, int tokens_count);
void	print_int_array(int *array, int n);

// t_ast_node **parser(char *line, t_env **envs);
t_ast_node *parser(char *line, t_env **envs);
// t_ast_node **tokens_to_ast_nodes(char **tokens, int tokens_count, int *special_indexes, int special_indexes_n);
t_ast_node *tokens_to_ast_nodes(char **tokens, int *special_indexes, int special_indexes_n);
// void	print_nodes_list(t_ast_node **ast_nodes);
void	print_nodes_list(t_ast_node *ast_nodes);
t_ast_node	*get_last_node0(t_ast_node *head);
void	ast_node_lst_push_bottom(t_ast_node **head, t_ast_type type);
// int		ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int i, t_ast_type type);
// void	ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int *i, t_ast_type type);
void	ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int i, t_ast_type type);

void	free_nodes_lst(t_ast_node **ast_nodes);

#endif
