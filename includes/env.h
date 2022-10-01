/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:35:30 by heboni            #+#    #+#             */
/*   Updated: 2022/09/29 22:06:15 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;

// envs_lst_saver
void	envs_saver(char **env, t_env **envs_lst);
char	*get_env_value_to_save(char *env, int i, int k);

// get_env
void	get_env_name_from_line(char **var_name, char *line, int tmp_i);
void	put_env_value_to_token(char *var_value, char **tokens, int token_n);

// envs_lst_utils
void	env_lst_push_bottom(t_env **head, char *name, char *value);
t_env	*get_last_node(t_env *head);
void	free_env_lst(t_env **lst);
void	print_env_list0(t_env **lst);
void	print_env_list(t_env *envs);
int		get_env_n_if_exists(t_env *envs, char *name);
int		env_lst_update_node(t_env *envs, char *name, char *value);
void	env_lst_remove_n_node(t_env **envs, int n);