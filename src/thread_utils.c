/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:29:25 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/05 20:21:27 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

int	check_death(t_philo *philo)
{
	if (access_dead(philo, 0))
		return (1);
	return (0);
}

void	init_forks(t_philo *philo, int *iterations)
{
	philo->first = philo->id;
	philo->second = (philo->id + 1) % philo->total;
	if (philo->id % 2 == 0)
	{
		philo->first = (philo->id + 1) % philo->total;
		philo->second = philo->id;
	}
	s_printf("%llu %d is thinking\n", _time() \
	- philo->start_of_exec, philo->id + 1, philo);
	if (*iterations != 0)
	{
		if (philo->ttd - (_time() - access_last_eaten(philo, 0)) > philo->tte)
			usleep(philo->tte * 1000);
	}
	(*iterations)++;
}
