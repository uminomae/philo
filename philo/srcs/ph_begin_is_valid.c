/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_is_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:34:14 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 18:03:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit_argv(int argc, char **argv);
static bool	argv_to_int(t_philo_main *ph, int argc, char **argv);

bool	is_valid_values(t_philo_main *ph, int argc, char **argv)
{
	if (argc < 5 || 6 < argc)
		return (false);
	if (argv == NULL)
		return (false);
	if (!is_digit_argv(argc, argv))
	{
		get_err_num_ph(ph, ERR_IS_DIGIT);
		return (false);
	}
	if (!memset(ph, 0, sizeof(t_philo_main)))
		return (false);
	if (!argv_to_int(ph, argc, argv))
		return (false);
	if (ph->argv[1] == 0)
		return (false);
	return (true);
}

static bool	is_digit_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			// argv[i][j] = 0;
			if (ft_isdigit(argv[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	argv_to_int(t_philo_main *ph, int argc, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	while (i < argc)
	{
		// argv[i] = NULL;
		if (argv[i] == NULL)
		{
			get_err_num_ph(ph, ERR_ARGV_NULL);
			return (false);
		}
		ret = ph_atoi(argv[i]);
		// ret = -1;
		if (ret < 0)
		{		
			get_err_num_ph(ph, ERR_ATOI);
			return (false);
		}
		ph->argv[i] = (size_t)ret;
		i++;
	}
	return (true);
}
