/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:17:05 by heboni            #+#    #+#             */
/*   Updated: 2022/09/15 22:34:36 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_string_array(char **argv, int count)
{
	int i = -1;
	
	printf("print_string_array\n");
	if (count == 0)
	{
		while (*argv != NULL)
		{
			printf("%s\n", *argv);
			argv++;
		}
			
	} else 
	{
		while (++i < count)
			printf("%s\n", argv[i]);
	}
	printf("print_string_array END\n\n");
}

void	print_int_array(int *array, int n)
{
	int	i;

	i = -1;
	printf(" [print_special_indexes_int_array]\n");
	while (++i < n)
		printf("%d ", array[i]);
	printf(" [print_special_indexes_int_array] END\n");
}

int get_tokens_count(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens != NULL)
	{
		count++;
		tokens++;
	}
	return (count);
}