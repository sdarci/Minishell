/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:10:59 by sdarci            #+#    #+#             */
/*   Updated: 2021/10/19 18:27:29 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;

	s2 = (char *) malloc(ft_strlen(s) + 1);
	if (!(s2))
		return (0);
	ft_memcpy(s2, s, ft_strlen(s) + 1);
	return (s2);
}
