/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:16:55 by sotherys          #+#    #+#             */
/*   Updated: 2022/07/09 02:16:56 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < size)
	{
		if (s1[i] != s2[i])
			break ;
		i += 1;
	}
	if (i < size)
		res = (unsigned char) s1[i] - (unsigned char) s2[i];
	return (res);
}
