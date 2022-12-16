/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:43:42 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 19:15:12 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "block_operations.h"
#include "string_operations.h"

static char	*sha256_last_stream_block(t_sha256_context *ctx, char *buff,
	int r, uint64_t total_len)
{
	char		*s;
	uint32_t	new_len;
	uint64_t	bits_len;

	buff[r] = (char)128;
	bits_len = 8ULL * total_len;
	swap_bytes(&bits_len, sizeof(bits_len));
	new_len = ((((r + 8) / 64) + 1) * 64) - 8;
	ft_memcpy(buff + new_len, &bits_len, sizeof(uint64_t));
	sha256_process_block((uint32_t *)(buff), ctx);
	if (new_len + 8 > 64)
		sha256_process_block((uint32_t *)(buff + 64), ctx);
	s = malloc(33 * sizeof(char));
	if (s == NULL)
		return (NULL);
	sha256_fill_result(ctx, s, 8);
	return (s);
}

char	*sha256_from_stream(int fd)
{
	char				buff[128];
	int32_t				r;
	t_sha256_context	ctx;
	uint64_t			total_len;

	total_len = 0;
	sha256_init_ctx(&ctx);
	while (1)
	{
		r = ft_read_block(fd, buff, 64);
		if (r < 0)
			return (NULL);
		ft_memset(buff + r, 0, 128 - r);
		total_len += r;
		if (fd == 0)
			write(1, buff, r);
		if (r < 64)
			break ;
		sha256_process_block((uint32_t *)(buff), &ctx);
	}
	return (sha256_last_stream_block(&ctx, buff, r, total_len));
}

static int	handle_options(int argc, char *argv[], int i, uint32_t *flags)
{
	char	*s;

	s = NULL;
	if (argv[i][1] == 's' && i + 1 >= argc)
		return (argc + invalid_option_arg(argv[0], 's'));
	if (argv[i][1] == 'r')
		*flags |= F_REVERSE;
	else if (argv[i][1] == 'q')
		*flags |= F_QUIET;
	else if (argv[i][1] == 'p')
	{
		s = sha256_from_stream(0);
		sha256_print_result(F_QUIET, s, "", 0);
	}
	else if (argv[i][1] == 's')
	{
		s = sha256_from_string(argv[i + 1], ft_strlen(argv[i + 1]));
		sha256_print_result(*flags, s, argv[i + 1],
			(int)ft_strlen(argv[i + 1]));
		++i;
	}
	else
		return (argc + invalid_option(argv[0], argv[i][1]));
	free(s);
	return (i);
}

static int	handle_files(char *argv[], int i, uint32_t flags)
{
	int		fd;
	int		return_value;
	char	*s;
	char	*input;

	return_value = 0;
	if (argv == NULL)
		input = "/dev/stdin";
	else
		input = argv[i];
	fd = open(input, O_RDONLY);
	if (fd >= 0)
	{
		s = sha256_from_stream(fd);
		if (argv == NULL)
			flags |= F_QUIET;
		else
			flags |= F_IS_FILE;
		sha256_print_result(flags, s, input, (int)ft_strlen(input));
		free(s);
	}
	else
		return_value = invalid_file(argv[0], input);
	close(fd);
	return (return_value);
}

int	sha256(int argc, char *argv[])
{
	int			i;
	uint32_t	flags;
	int			return_value;

	i = 0;
	flags = 0;
	return_value = 0;
	if (argc == 1)
		handle_files(NULL, 0, F_IS_STDIN);
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			i = handle_options(argc, argv, i, &flags);
		else
			return_value = handle_files(argv, i, flags);
	}
	return (i > argc || return_value > 0);
}
