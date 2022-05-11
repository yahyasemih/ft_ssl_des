/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:30:18 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:14:54 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_OPERATIONS_H
# define STRING_OPERATIONS_H

# include "md5.h"

char	*fill_result(t_md5_context *ctx, char *str);
char	*prepare_input_string(const char *str);
void	md5_print_result(uint32_t flags, const char *s, const char *src,
			int src_len);
char	*md5_from_string(const char *str, uint64_t len);

#endif
