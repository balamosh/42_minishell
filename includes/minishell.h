/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:04 by sotherys          #+#    #+#             */
/*   Updated: 2022/08/14 11:41:13 by heboni           ###   ########.fr       */
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

typedef struct s_lst_elems
{
	t_ast_node			*elem;
	struct s_lst_elems	*next;
}					t_lst_elems;

char		*get_prompt(void);

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
void	print_tokens_array(char **tokens, int tokens_count);
void	print_int_array(int *array, int n);

#endif
