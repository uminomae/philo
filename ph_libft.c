/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:14:55 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 10:52:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len_s;

	if (s == NULL)
		return ;
	len_s = ft_strlen(s);
	write(fd, s, len_s);
}

int	ft_put_positivelong_fd(long n, int fd)
{
	char	c;
	
	if (n < 0)
		return (-1);
	if (0 <= n && n <= 9)
	{
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
	else
		ft_put_positivelong_fd(n / 10, fd);
	return (0);
}
