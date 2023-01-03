/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:14:55 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/03 13:27:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isblank(int c)
{
	if (c == ' ')
		return (1);
	if ('\t' <= c && c <= '\r')
		return (1);
	return (0);
}

static bool	is_overflow(ssize_t nega, ssize_t next, int rev_sign)
{
	if (rev_sign == -1 && nega * 10 - next < INT_MIN + 1)
		return (true);
	else if (rev_sign == 1 && nega * 10 - next < INT_MIN)
		return (true);
	return (false);
}

static int	to_i(const char *str)
{
	size_t	i;
	int		reverse_sign;
	int		ret_i;
	ssize_t	next;

	ret_i = 0;
	reverse_sign = -1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		reverse_sign = (str[i] - 44);
		i = 1;
	}
	while (ft_isdigit(str[i]) == 1 && str[i] != '\0')
	{
		next = (str[i] - '0');
		if (is_overflow(ret_i, next, reverse_sign) == true)
			return (-1);
		ret_i = ret_i * 10 - (str[i] - '0');
		i++;
	}
	return (reverse_sign * ret_i);
}

int	ph_atoi(const char *str)
{
	int			int_ret;
	size_t		i;

	int_ret = 0;
	i = 0;
	while (ft_isblank(str[i]) == 1)
		i++;
	int_ret = to_i(&str[i]);
	return (int_ret);
}
