/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:35:30 by heboni            #+#    #+#             */
/*   Updated: 2022/08/14 15:37:26 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;

//envs
void	envs_saver(char **env, t_env **envs_lst);
char	*get_env_value_to_save(char *env, int i, int k);
char	*get_env_value_by_name(void *name, t_env **envs);

//env_utils.c
void	env_lst_push_bottom(t_env **head, char *name, char *value);
t_env	*get_last_node(t_env *head);
void	free_env_lst(t_env **lst);
void	print_env_list(t_env **lst);