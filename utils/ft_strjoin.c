/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:19 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/14 22:06:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strjoin.h"
#include "libc_utils.h"

char	*ft_strjoin(const char *s1, const char *s2, int n, int free_first)
{
	char	*res;
	int		len;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = n;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	len = len1 + len2;
	res = malloc(sizeof(char) *(len + 1));
	if (res == NULL)
	{
		if (free_first)
			free((char *)s1);
		return (NULL);
	}
	res[len] = '\0';
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	if (free_first)
		free((char *)s1);
	return (res);
}
