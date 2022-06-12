/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:08:45 by sdarci            #+#    #+#             */
/*   Updated: 2021/10/18 19:30:59 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < n)
	{
		if (((char *)s)[i] == c)
		{
			tmp = &s[i];
			return ((char *)tmp);
		}
		i++;
	}
	return ((char *)tmp);
}
