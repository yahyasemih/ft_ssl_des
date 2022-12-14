/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_password.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:04:45 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 15:19:57 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PASSWORD_H
# define GET_PASSWORD_H

# include <stddef.h>
# include <unistd.h>
# include "libc_utils.h"
# include "commands_utils.h"

int		get_password(const char *prompt, char *dst, size_t len);

#endif