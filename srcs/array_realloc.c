/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 07:45:13 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 07:46:45 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	**int_array_realloc(int **array, int *array_n)
{
	int	*tmp_array;
	int	i;

	i = -1;
	tmp_array = NULL;
	printf("[int_array_realloc] array_n: %d\n", *array_n);
	if (*array_n != 0)
	{
		tmp_array = (int *)malloc(sizeof(int) * *array_n); //выделить память под char **
		if (tmp_array == NULL)
			exit(STACK_OVERFLOW);
		while (++i < *array_n)
		{
			tmp_array[i] = (*array)[i];
			printf("[int_array_realloc] tmp_array[%d]=%d\n", i, tmp_array[i]);
		}
		free(*array);
	}
	*array_n += 1;
	*array = (int *)malloc(sizeof(int) * *array_n); //выделить память под char **
	if (*array == NULL)
		exit(STACK_OVERFLOW);
	
	if (tmp_array != NULL)
	{
		//из tmp_array перенести в переаллоцированный array
		i = -1;
		while (++i < (*array_n - 1))
			(*array)[i] = tmp_array[i];
		free(tmp_array);
	}
	return (array);
}

char	**tokens_realloc(char **tokens, int tokens_count)
{
	char	**tmp_tokens;
	int		token_len;
	int		i;
	
	i = -1;
	tmp_tokens = NULL;
	printf("[tokens_realloc] tokens_count: %d\n", tokens_count);
	if (tokens != NULL)
	{
		tmp_tokens = (char **)malloc(sizeof(char *) * tokens_count); //выделить память под char **
		if (tmp_tokens == NULL)
			exit(STACK_OVERFLOW);
		tmp_tokens[tokens_count - 1] = NULL; //почему tokens_count - 1
		while (++i < tokens_count - 1)
		{
			tmp_tokens[i] = ft_strdup(tokens[i]);
			free(tokens[i]); //освободить память каждого эл-та массива
			printf("[tokens_realloc] tmp_tokens[%d]: %s\n", i, tmp_tokens[i]);
			// token_len = ft_strlen(tokens[i]); printf("[tokens_realloc] %d token_len: %d\n", i, token_len);
			// tmp_tokens[i] = (char *)malloc(sizeof(char) * token_len + 1);
			// tmp_tokens[i][token_len] = '\0';
		}
		free(tokens);
	}
	tokens = (char **)malloc(sizeof(char *) * tokens_count + 1); //выделить память под char **
	if (tokens == NULL)
		exit(STACK_OVERFLOW);
	tokens[tokens_count] = NULL;
	
	if (tmp_tokens != NULL)
	{
		//из tmp_tokens перенести в переаллоцированный tokens
		i = -1;
		while (++i < tokens_count - 1)
		{
			tokens[i] = ft_strdup(tmp_tokens[i]);
			free(tmp_tokens[i]);
		}
		free(tmp_tokens);
	}
	return (tokens);
}
