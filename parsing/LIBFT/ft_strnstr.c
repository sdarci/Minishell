/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:09:43 by sdarci            #+#    #+#             */
/*   Updated: 2021/10/18 19:57:00 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		cnt = 0;
		while (haystack[i + cnt] == needle[cnt] && (i + cnt) < len)
		{
			if (haystack[i + cnt] == '\0' && needle[cnt] == '\0')
				return ((char *)&haystack[i]);
			cnt++;
		}
		if (needle[cnt] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
