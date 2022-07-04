/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:27:19 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memjoin(void *dst, const void *src)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if ((dst == src) || src_len == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		((unsigned char *)dst)[dst_len + i] = ((const unsigned char *)src)[i];
		i++;
	}
	((unsigned char *)dst)[dst_len + i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			count_byte;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
		count_byte = 1;
	else if (ft_strlen(s) - start >= len)
		count_byte = (len + 1) * sizeof(char);
	else
		count_byte = (ft_strlen(s) - start + 1) * sizeof(char);
	p = malloc(count_byte);
	if (p == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && ft_strlen(s) >= start)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_puterror(t_shell *shell, int code, char *name)
{
	ft_putstr("Error: ", 2);
	if (code == 1)
		ft_putstr("Programmu neobhodimo zapuskat bez parametrov\n", 2);
	if (code == 2)
	{
		g_lobal_status = 1;
		ft_putstr("Ne udalos vydelit pamyat. ", 2);
		ft_putstr(name, 2);
	}
	if (code == 3)
	{
		ft_putstr("excve\n", 2);
	}
	ms_shell_destroy(shell);
	exit (127);
}
