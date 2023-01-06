/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:34:14 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 22:31:59 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//TODO　最終時　エラー処理
size_t	check_valid_values(int argc, char **argv)
{
	size_t ret;

	if (argc < 5 || 6 < argc)
		return (1);
	ret = check_digit(argc, argv);
	if (ret == 1)
		return (1);
	return (0);
}
