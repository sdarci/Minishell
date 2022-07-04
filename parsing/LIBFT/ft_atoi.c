/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:10:24 by sdarci            #+#    #+#             */
/*   Updated: 2021/10/18 18:43:31 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_maxvalue(char *str, int cnt)
{
	char	*max;
	int		i;
	int		x;

	x = cnt;
	i = 0;
	max = "9223372036854775807";
	while (str[cnt] >= '0' && str[cnt] <= '9' && cnt < 21)
		cnt++;
	if (cnt > 19)
		return (1);
	else if (i == 19)
	{
		while (str[x] >= '0' && str[x] <= '9')
		{
			if (str[x] > max[i])
				return (1);
			x++;
			i++;
		}
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	num;
	int	cnt;

	sign = 1;
	cnt = 0;
	num = 0;
	while ((str[cnt] == ' ') || (str[cnt] == '\t') || (str[cnt] == '\n') \
		|| (str[cnt] == '\v') || (str[cnt] == '\f') || (str[cnt] == '\r'))
		cnt++;
	if (str[cnt] == '-')
		sign = -1;
	if ((str[cnt] == '-') || (str[cnt] == '+'))
		cnt++;
	if (ft_maxvalue(str, cnt) && sign == 1)
		return (-1);
	if (ft_maxvalue(str, cnt) && sign == -1)
		return (0);
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		num = (num * 10) + ((int)str[cnt] - '0');
		cnt++;
	}
	return (num * sign);
}
