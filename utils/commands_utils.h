/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:04:04 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 00:49:03 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_UTILS_H
# define COMMANDS_UTILS_H

# include <stdio.h>
# include <unistd.h>
# include "libc_utils.h"

int		invalid_option(const char *cmd, char o);
int		invalid_option_arg(const char *cmd, char o);
int		invalid_command(int argc, char *argv[]);
int		invalid_file(const char *cmd, const char *file);
int		min(int a, int b);

#endif
