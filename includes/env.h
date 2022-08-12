/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:35:30 by heboni            #+#    #+#             */
/*   Updated: 2022/08/10 22:53:13 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	void			*var_name;
	void			*var_value;
	struct s_env	*next;
}					t_env;

//envs
t_env	**get_envs(char **env);
void	envs_saver(char **env, t_env **envs_lst);
char	*get_env_value_to_save(char *env, int i, int k);
// void	get_env_value_to_save(char *env, int i, int k);

//env_utils.c
char	*get_env_value_by_name(void *name, t_env **envs);
int		get_env_count(char **env);
t_env	*env_lst_new(void *var_name, void *var_value);
void	env_lst_add_back(t_env **lst, t_env *new);
void	free_env_lst(t_env **lst);
void	print_env_list(t_env **lst);