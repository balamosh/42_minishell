/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:46:03 by heboni            #+#    #+#             */
/*   Updated: 2022/08/10 09:35:29 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == ((void *)0))
		return (((void *)0));
	while (++i < len)
		dup[i] = s1[i];
	dup[len] = '\0';
	return (dup);
}
