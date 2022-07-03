#include "costume.h"

int	check_death(t_philo *philo)
{
	if (philo->treshi.ttd < _time() - philo->last_eaten)
	{
		pthread_mutex_lock(&philo->global->dead.mut);
		philo->global->dead.var = 1;
		pthread_mutex_unlock(&philo->global->dead.mut);
	}
	if (philo->global->dead.var)
	{
		printf("%llu %llu %d died\n", _time() - philo->start_of_exec, _time() - philo->last_eaten, philo->id);
		return (1);
	}
	return (0);
}

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

static int	eating(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->id;
	second = (philo->id + 1) % philo->total;
	if (philo->id % 2 == 0)
	{
		first = (philo->id + 1) % philo->total;
		second = philo->id;
	}
	pthread_mutex_lock(&philo->global->forks[first]);
	if (check_death(philo))
	{
		printf("TIME BEFORE PICKING UP FORK: %llu %d\n", _time() - philo->last_eaten, philo->id);
		return (1);
	}
	printf("%llu %d Takeing left fork\n", _time() - philo->start_of_exec, philo->id);
	pthread_mutex_lock(&philo->global->forks[second]);
	printf("%llu %d Takeing right fork\n", _time() - philo->start_of_exec, philo->id);
	printf("%llu %d Eating\n", _time() - philo->start_of_exec, philo->id);
	philo->last_eaten = _time();
	philo->times_eaten++;
	if (philo->times_eaten >= philo->treshi.tste)
	{
		printf("%llu %d Ate often enough\n", _time() - philo->start_of_exec, philo->id);
		pthread_mutex_unlock(&philo->global->forks[first]);
		pthread_mutex_unlock(&philo->global->forks[second]);
		return (1);
	}
	while (_time() - philo->last_eaten <= philo->advs.tte)
	{
		if (check_death(philo))
		{
			pthread_mutex_unlock(&philo->global->forks[first]);
			pthread_mutex_unlock(&philo->global->forks[second]);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->global->forks[first]);
	pthread_mutex_unlock(&philo->global->forks[second]);
	return (0);
}

void	sleeping(t_philo *philo)
{

}

void	*surpressor(void *arg)
{
	t_philo				*philo;
	unsigned long long	temp;

	philo = (t_philo *)arg;
	philo->last_eaten = _time();
	philo->start_of_exec = _time();
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		if (!philo->eating && !philo->sleeping)
			philo->eating = 1;
		else if (philo->eating)
		{
			if (check_death(philo))
				return (NULL);
			philo->eating = 0;
			philo->sleeping = 1;
			if (eating(philo))
				return (NULL);
		}
		else if (philo->sleeping)
		{
			if (check_death(philo))
				return (NULL);
			philo->sleeping = 0;
			philo->eating = 1;
			printf("%llu %d Sleeping\n", _time() - philo->start_of_exec, philo->id);
			philo->last_sleep = _time();
			while(_time() - philo->last_sleep - temp < philo->advs.tts)
			{
				if (check_death(philo))
				{
					printf("DEATH UPON AWAKENING\n");
					return (NULL);
				}
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_philo		philo[200];
	pthread_t	thread[200];
	t_global	global;
	int			i;

	global.dead.var = 0;
	pthread_mutex_init(&global.dead.mut, NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&global.forks[i], NULL);
		i++;
	}
	i = 0;
	while(i < ft_atoi(av[1]))
	{
		philo[i].id = i;
		init_states(&philo[i], ac, av, &global);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&thread[i], NULL, &surpressor, (void *)&philo[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}
