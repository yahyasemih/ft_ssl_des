/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_password.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:06:34 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 15:32:34 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_password.h"

int	get_password(const char *prompt, char *dst, size_t len)
{
	char	*pass;
	char	*verify_pass;

	pass = getpass(prompt);
	if (pass == NULL)
		return (1);
	ft_memcpy(dst, pass, min(ft_strlen(pass), len) + 1);
	write(1, "Verifying - ", 12);
	verify_pass = getpass(prompt);
	if (verify_pass == NULL)
		return (1);
	if (ft_strcmp(dst, verify_pass) != 0)
	{
		ft_memset(dst, 0, len + 1);
		write(1, "Verify failure\n", 15);
		return (1);
	}
	if (*dst == '\0')
		return (1);
	return (0);
}
