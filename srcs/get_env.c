/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:23:29 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 09:25:13 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO чем отличается get_env_var_value_to_saver от get_env_var_value_to_lexer?
//оптимизировать
int	get_env_var_value_to_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;
	int		k;

	k = ft_strlen(tokens[token_n]) - 1; printf("\n[get_env_var_value_to_saver] k=%d\n", k);
	var_len = 0;
	tmp_i = i;
	while (line[i] != ' ')
	{
		if (line[i] == '\0' || line[i] == '$' || line[i] == '\"' || line[i] == '\'') //добавить другие пробелы
			break ;
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		exit(STACK_OVERFLOW);
	get_env_name_from_line(&var_name, line, tmp_i); // printf("\nvar_len %d, var_name: %s\n", var_len, var_name);
	var_value = get_env_value_by_name_from_envs(var_name, envs);
	if (var_value) //если env_var не существует, текущий аргумент - null
	{
		while (*var_value)
		{
			tokens[token_n][++k] = *var_value;
			printf("%c", tokens[token_n][k]);
			var_value++;
		}
	}
	free(var_name);
	printf("\n[get_env_var_value_to_saver] END\n");
	return (i - 1);
}

//чтобы узнать сколько памяти выделять при сохранении нужно прочитать env_var и запомнить value_len
int	get_env_var_value_to_lexer(char *line, int i, t_env **envs)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;

	var_len = 0;
	tmp_i = i;
	while (line[i] != ' ')
	{
		if (line[i] == '\0' || line[i] == '$' || line[i] == '\"' || line[i] == '\'') //добавить другие пробелы
			break ;
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		exit(STACK_OVERFLOW);
	get_env_name_from_line(&var_name, line, tmp_i);
	// printf("\nvar_len %d\n", var_len); printf("var_name: %s\n", var_name); printf("var_value: "); //print_env_list(envs); 
	var_value = get_env_value_by_name_from_envs(var_name, envs);
	printf("%s", var_value);
	free(var_name);
	return (i - 1);
}

// вызывается и в get_env_var_value_to_lexer, и в get_env_var_value_to_saver
void	get_env_name_from_line(char **var_name, char *line, int tmp_i)
{
	int	j;

	j = 0;
	while (line[tmp_i] != ' ')
	{
		// printf("\nsave var_name\n%c", line[tmp_i]);
		if (line[tmp_i] == '\0' || line[tmp_i] == '$' || line[tmp_i] == '\'' || line[tmp_i] == '\"') //добавить другие пробелы
			break ;
		(*var_name)[j] = line[tmp_i];
		tmp_i++;
		j++;
	}
	(*var_name)[j] = '\0';
}

char	*get_env_value_by_name_from_envs(void *name, t_env **envs)
{
	t_env	*tmp;

	if (!envs)
		return NULL;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp((char *)name, (char *)tmp->var_name) == 0)
		{
			cur_env_vars_len += ft_strlen((char *)tmp->var_value);
			return((char *)tmp->var_value);
		}
		tmp = tmp->next;
	}
	return NULL;
}
