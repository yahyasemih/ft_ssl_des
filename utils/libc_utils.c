/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:22:40 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 19:01:21 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc_utils.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*source;
	char	*dest;
	size_t	i;

	source = (char *)src;
	dest = (char *)dst;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		++i;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;
	size_t	i;

	if (b == NULL)
		return (NULL);
	s = (char *)b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		++i;
	}
	return (b);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		++i;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
