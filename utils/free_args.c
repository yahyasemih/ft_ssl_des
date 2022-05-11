/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:21:00 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 18:22:09 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_args(int argc, char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (i < argc)
	{
		free(argv[i]);
		++i;
	}
	free(argv);
}
