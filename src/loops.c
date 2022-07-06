/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:20:25 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/06 16:20:26 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

void	loop_1(t_philo *philo, int ac, char **av, t_global *global)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i;
		init_states(&philo[i], ac, av, global);
		i++;
	}
}

void	loop_2(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&philo[i].thread, NULL, \
		&sit_at_table, (void *)&philo[i]);
		i++;
	}
}

void	loop_3(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	loop_4(t_philo *philo, t_global *global, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&global->forks[i]);
		pthread_detach(philo[i].thread);
		pthread_mutex_destroy(&philo[i].times_eaten_mut);
		pthread_mutex_destroy(&philo[i].last_eaten_mut);
		i++;
	}
}
