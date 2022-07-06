#include "../includes/costume.h"

void	init_states(t_philo *philo, int ac, char **av, t_global *global)
{
	pthread_mutex_init(&philo->last_eaten_mut, NULL);
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
	philo->times_eaten = 0;
	philo->eat_end = 0;
	access_last_eaten(philo, _time());
	philo->start_of_exec = _time();
}

t_global	init_global(char **av)
{
	int			i;
	t_global	global;

	global.dead_var = 0;
	pthread_mutex_init(&global.dead_mut, NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&global.forks[i], NULL);
		i++;
	}
	return (global);
}

void	main_death(t_philo *philo, int philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while(i < philos)
		{
			if (philo[i].total == 1)
				return ;
			if (philo[1].tste == -1 || !(philo[i].times_eaten >= philo[i].tste))
			{
				if (philo[i].ttd < _time() - access_last_eaten(&philo[i], 0))
				{
					philo[i].global->dead_var = 1;
					printf("%llu %d %llu died\n", _time() - philo[i].start_of_exec, philo[i].id, _time() - access_last_eaten(&philo[i], 0));
					return ;
				}
				i++;
			}
			else
				return ;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo		philo[200];
	t_global	global;
	int			i;

	ft_bzero(philo, 200 * sizeof(t_philo));
	global = init_global(av);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i;
		init_states(&philo[i], ac, av, &global);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&philo[i].thread, NULL, &sit_at_table, (void *)&philo[i]);
		i++;
	}
	main_death(philo, ft_atoi(av[1]));
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
