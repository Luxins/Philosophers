/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:20:52 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/06 16:36:42 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

int	ft_strlen(const char *c)
{
	int	count;

	count = 0;
	while (*c)
	{
		count++;
		c++;
	}
	return (count);
}

unsigned long long	_time(void)
{
	struct timeval				struci;

	gettimeofday(&struci, NULL);
	return (struci.tv_usec / 1000 + struci.tv_sec * 1000);
}
