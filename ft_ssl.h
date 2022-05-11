/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:20:04 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 18:22:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "base64/base64.h"
# include "des/des.h"
# include "md5/md5.h"
# include "sha256/sha256.h"
# include "utils/commands_utils.h"
# include "utils/libc_utils.h"

# define NUM_COMMANDS 4

typedef int						(*t_command_function)(int argc, char *argv[]);

static const t_command_function	g_command_functions[NUM_COMMANDS + 1] = {
	md5,
	sha256,
	base64,
	des,
	invalid_command
};

static const char				*g_commands[NUM_COMMANDS] = {
	"md5",
	"sha256",
	"base64",
	"des"
};

int								get_command_index(const char *cmd);

void							parse_commands(void);

void							free_args(int argc, char **argv);
#endif
