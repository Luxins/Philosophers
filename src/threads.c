/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:49:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/05 20:27:26 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

static int	takeing_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->forks[philo->first]);
	if (check_death(philo))
		return (1);
	s_printf("%llu %d has taken a fork\n", _time() \
	- philo->start_of_exec, philo->id + 1, philo);
	pthread_mutex_lock(&philo->global->forks[philo->second]);
	if (check_death(philo))
		return (2);
	s_printf("%llu %d has taken a fork\n", _time() \
	- philo->start_of_exec, philo->id + 1, philo);
	s_printf("%llu %d is eating\n", _time() - \
	philo->start_of_exec, philo->id + 1, philo);
	access_last_eaten(philo, _time());
	return (0);
}

static int	eating(t_philo *philo, int	*iterations)
{
	int	ret;

	init_forks(philo, iterations);
	ret = takeing_forks(philo);
	if (ret)
		return (ret);
	if (philo->tste != -1)
	{
		access_times_eaten(philo, 1);
		if (access_times_eaten(philo, 0) >= philo->tste)
		{
			s_printf("%llu %d Ate often enough\n", _time() \
			- philo->start_of_exec, philo->id + 1, philo);
			return (2);
		}
	}
	while (_time() - access_last_eaten(philo, 0) <= philo->tte)
	{
		if (check_death(philo))
			return (2);
	}
	pthread_mutex_unlock(&philo->global->forks[philo->first]);
	pthread_mutex_unlock(&philo->global->forks[philo->second]);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	s_printf("%llu %d is sleeping\n", _time() \
	- philo->start_of_exec, philo->id + 1, philo);
	philo->last_sleep = _time();
	while (_time() - philo->last_sleep < philo->tts)
	{
		if (check_death(philo))
			return (1);
	}
	return (0);
}

int	one_philo(t_philo *philo)
{
	if (philo->total == 1)
	{
		usleep(philo->ttd * 1000);
		s_printf("%llu %d died\n", _time() \
		- philo->start_of_exec, philo->id + 1, philo);
		return (1);
	}
	return (0);
}

void	*sit_at_table(void *arg)
{
	t_philo				*philo;
	int					iterations;
	int					eat_ret;

	iterations = 0;
	philo = (t_philo *)arg;
	if (one_philo(philo))
		return (NULL);
	while (1)
	{
		eat_ret = eating(philo, &iterations);
		if (eat_ret)
		{
			pthread_mutex_unlock(&philo->global->forks[philo->first]);
			if (eat_ret == 2)
				pthread_mutex_unlock(&philo->global->forks[philo->second]);
			return (NULL);
		}
		if (sleeping(philo))
			return (NULL);
	}
}
