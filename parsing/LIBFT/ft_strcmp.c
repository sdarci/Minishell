/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:32:25 by eheike            #+#    #+#             */
/*   Updated: 2022/06/28 19:26:55 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		dif;

	i = 0;
	while ((((const unsigned char *)s1)[i] || ((const unsigned char *)s2)[i]))
	{
		dif = ((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i];
		if (dif != 0)
		{
			return (dif);
		}
		i++;
	}
	return (0);
}
