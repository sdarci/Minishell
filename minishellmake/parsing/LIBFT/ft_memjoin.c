#include "libft.h"

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