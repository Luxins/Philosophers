/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:45:42 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/05 20:17:50 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

void	init_states(t_philo *philo, int ac, char **av, t_global *global)
{
	pthread_mutex_init(&philo->last_eaten_mut, NULL);
	pthread_mutex_init(&philo->times_eaten_mut, NULL);
	philo->total = ft_atoi(av[1]);
	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	if (ac == 6)
		philo->tste = ft_atoi(av[5]);
	else
		philo->tste = -1;
	philo->global = global;
	philo->eating = 1;
	philo->sleeping = 0;
	philo->dead = 0;
	philo->eat_end = 0;
	philo->start_of_exec = _time();
	access_last_eaten(philo, _time());
	access_times_eaten(philo, 69);
}

t_global	init_global(char **av)
{
	int			i;
	t_global	global;

	pthread_mutex_init(&global.dead_mut, NULL);
	pthread_mutex_init(&global.print_mut, NULL);
	global.dead_var = 0;
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&global.forks[i], NULL);
		i++;
	}
	return (global);
}

static int	track_death(t_philo *philo, int i)
{
	if (philo[i].ttd < _time() - access_last_eaten(&philo[i], 0))
	{
		access_dead(philo, 1);
		s_printf("%llu %d died\n", _time() - \
		philo[i].start_of_exec, philo[i].id + 1, philo);
		return (1);
	}
	return (0);
}

void	main_death(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->total)
		{
			if (philo[i].total == 1)
				return ;
			if (philo[1].tste == -1 || !(access_times_eaten(&philo[i], 0) \
			>= philo[i].tste))
			{
				if (track_death(philo, i))
					return ;
				i++;
			}
			else
				return ;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo		philo[400];
	t_global	global;

	if (check_philo(ac, av))
		return (1);
	ft_bzero(philo, 200 * sizeof(t_philo));
	global = init_global(av);
	loop_1(philo, ac, av, &global);
	loop_2(philo, av);
	main_death(philo);
	loop_3(philo, av);
	pthread_mutex_destroy(&global.dead_mut);
	pthread_mutex_destroy(&global.print_mut);
	loop_4(philo, &global, av);
	return (0);
}
