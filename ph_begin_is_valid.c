/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_is_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:34:14 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 23:19:32 by uminomae         ###   ########.fr       */
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

static void	init_struct_philo(t_philo *ph)
{
	memset(ph, 0, sizeof(t_philo));
}

static void	argv_to_int(t_philo *ph, int argc, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	while (i < argc)
	{
		if (argv[i] == NULL)
		{
			get_err_flag(ph);
			return ;
		}
		ret = ph_atoi(argv[i]);
		if (ret < 0)
			get_err_flag(ph);
		ph->argv[i] = (size_t)ret;
		i++;
	}
}

bool	is_valid_values(t_philo *ph, int argc, char **argv)
{
	size_t	ret;

	if (argc < 5 || 6 < argc)
		return (false);
	if (argv == NULL)
		return (false);
	ret = check_digit(argc, argv);
	if (ret == 1)
		return (false);
	init_struct_philo(ph);
	argv_to_int(ph, argc, argv);
	if (ph->flag_err)
		return (false);
	if (ph->argv[1] == 0)
		return (false);
	return (true);
}
