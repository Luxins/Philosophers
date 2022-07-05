#include "costume.h"

void	init_states(t_philo *philo, int ac, char **av, t_global *global)
{
	static int	testing = 0;

	testing++;
	philo->total = ft_atoi(av[1]);
	philo->global = global;
	philo->advs.tte = ft_atoi(av[3]);
	philo->advs.tts = ft_atoi(av[4]);
	philo->treshi.ttd = ft_atoi(av[2]);
	if (ac == 6)
		philo->treshi.tste = ft_atoi(av[5]);
	philo->eating = 0;
	philo->sleeping = 0;
	philo->dead = 0;
	philo->times_eaten = 0;
	philo->eat_end = 0;
}

void	main_death(t_philo *philo, int philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while(i < philos)
		{
			if (philo[i].treshi.ttd < _time() - philo[i].last_eaten)
			{
				philo[i].global->dead.var = 1;
				printf("%llu %d %llu died\n", _time() - philo[i].start_of_exec, philo[i].id, _time() - philo[i].last_eaten);
				return ;
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo		philo[200];
	pthread_t	thread[200];
	t_global	global;
	int			i;

	ft_bzero(philo, 200 * sizeof(t_philo));
	global.dead.var = 0;
	pthread_mutex_init(&global.dead.mut, NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&global.forks[i], NULL);
		i++;
	}
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
		philo[i].last_eaten = _time();
		philo[i].start_of_exec = _time();
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&thread[i], NULL, &surpressor, (void *)&philo[i]);
		i++;
	}
	main_death(philo, ft_atoi(av[1]));
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}
