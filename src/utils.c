/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:21:16 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/06 16:21:34 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s++, 1);
	}
}

int	ft_strncmp(char const *s1, char const *s2, unsigned int n)
{
	unsigned char	a;
	unsigned char	b;
	int				index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] && (s1[index] == s2[index]) && n - 1)
	{
		index++;
		n--;
	}
	a = (unsigned char) s1[index];
	b = (unsigned char) s2[index];
	return (a - b);
}

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\n'
		|| *str == '\f' || *str == '\r' || *str == '\t'
		|| *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_digit(*str))
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return (result * sign);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		n--;
		p[n] = 0;
	}
}
