/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:27:27 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/14 22:24:23 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include "../utils/commands_utils.h"
# include "../utils/ft_read_block.h"
# include "../utils/ft_strjoin.h"

typedef struct s_base64_context
{
	int		input_fd;
	int		output_fd;
	char	mode;
}			t_base64_context;

static const char	*g_base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz0123456789+/";

char	*encode(t_base64_context *ctx);
char	*encode_str(const char *str);
char	*decode(t_base64_context *ctx);
int		base64(int argc, char *argv[]);

#endif
