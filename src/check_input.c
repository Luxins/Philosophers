/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:42:42 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/06 19:42:43 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

int	out_of_range(char *num)
{
	if (ft_strlen(num) > 11)
		return (1);
	if (ft_strlen(num) == 11)
	{
		if (ft_strncmp(num, "-2147483648", 11) > 0)
			return (1);
	}
	if (ft_strlen(num) == 10)
	{
		if (ft_strncmp(num, "2147483647", 10) > 0)
			return (1);
	}
	return (0);
}

int	not_pos_num(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!(num[i] >= 48 && num[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int	check_philo(int ac, char **av)
{
	int	i;

	if (ac > 6 || ac < 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 1);
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (not_pos_num(av[i]))
		{
			ft_putstr_fd("Input is not a positve integer\n", 1);
			return (1);
		}
		if (out_of_range(av[i]))
		{
			ft_putstr_fd("Out of integer range\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}
