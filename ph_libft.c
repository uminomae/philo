/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:14:55 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 13:36:55 by uminomae         ###   ########.fr       */
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


static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ucp_dst;
	const unsigned char	*ucp_src;

	ucp_dst = (unsigned char *)dst;
	ucp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ucp_dst[i] = ucp_src[i];
		i++;
	}
	return (dst);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	if (dst == NULL)
		return (0);
	len_src = ft_strlen(src);
	if (len_src < dstsize)
		ft_memcpy(dst, src, len_src + 1);
	else if (0 < dstsize)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len_src);
}

char	*ft_strdup(const char *src)
{
	char	*p_cpy;
	size_t	len_src;

	if (src == NULL)
		return (NULL);
	len_src = ft_strlen(src);
	p_cpy = (char *) malloc(sizeof(char) * (len_src + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, src, len_src + 1);
	return (p_cpy);
}

char	*x_strdup(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (ret == NULL)
		return (NULL);
	return (ret);
}