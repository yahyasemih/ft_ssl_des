/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:22:58 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 11:31:12 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_OPERATIONS_H
# define STRING_OPERATIONS_H

# include "sha256.h"

char	*sha256_prepare_input_string(const char *str, uint64_t len);

void	sha256_print_result(uint32_t flags, const char *s, const char *src,
			int src_len);

char	*sha256_fill_result(t_sha256_context *ctx, char *str,
			int hash_nbr);

char	*sha256_from_string(const char *str, uint64_t len);

#endif
