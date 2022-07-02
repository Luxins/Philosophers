#include "costume.h"

int	check_death(t_philo *philo)
{
	if (philo->treshi.ttd < _time(NULL))
	{
		pthread_mutex_lock(&philo->global->dead.mut);
		philo->global->dead.var = 1;
		pthread_mutex_unlock(&philo->global->dead.mut);
	}
	if (philo->global->dead.var)
	{
		printf("%llu died\n", entire_time(NULL));
		return (1);
	}
	return (0);
}

int	check_stomach(t_philo *philo)
{
	if (philo->global->eat_end.var)
	{
		printf("TEST: EAT END\n");
		return (1);
	}
	pthread_mutex_unlock(&philo->global->eat_end.mut);
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

void	*surpressor(void *arg)
{
	t_philo				*philo;
	unsigned long long	temp;

	philo = (t_philo *)arg;
	init_entire_time();
	init_time();
	while (1)
	{
		if (check_death(philo) || check_stomach(philo))
			return (NULL);
		if (!philo->eating && !philo->sleeping)
			philo->eating = 1;
		else if (philo->eating)
		{
			if (check_death(philo) || check_stomach(philo))
				return (NULL);
			philo->eating = 0;
			philo->sleeping = 1;
			printf("%llu %d Thinking\n", entire_time(NULL), philo->id);
			if (philo->id % 2 == 0)
			{
				pthread_mutex_lock(&philo->global->forks[philo->id]);
				printf("%llu %d Takeing left fork\n", entire_time(NULL), philo->id);
				pthread_mutex_lock(&philo->global->forks[(philo->id + 1) % philo->total]);
				printf("%llu %d Takeing right fork\n", entire_time(NULL), philo->id);
				printf("%llu %d Eating\n", entire_time(NULL), philo->id);
				init_time();
				philo->times_eaten++;
				if (philo->times_eaten >= philo->treshi.tste)
				{
					printf("%llu %d Ate often enough\n", entire_time(NULL), philo->id);
					pthread_mutex_lock(&philo->global->eat_end.mut);
					philo->global->eat_end.var = 1;
					pthread_mutex_unlock(&philo->global->eat_end.mut);
					return (NULL);
				}
				while (_time(NULL) <= philo->advs.tte)
				{
					if (check_death(philo) || check_stomach(philo))
						return (NULL);
				}
				pthread_mutex_unlock(&philo->global->forks[philo->id]);
				pthread_mutex_unlock(&philo->global->forks[(philo->id + 1) % philo->total]);
			}
			else
			{
				pthread_mutex_lock(&philo->global->forks[(philo->id + 1) % philo->total]);
				printf("%llu %d Takeing right fork\n", entire_time(NULL), philo->id);
				pthread_mutex_lock(&philo->global->forks[philo->id]);
				printf("%llu %d Takeing left fork\n", entire_time(NULL), philo->id);
				printf("%llu %d Eating\n", entire_time(NULL), philo->id);
				init_time();
				philo->times_eaten++;
				if (philo->times_eaten >= philo->treshi.tste)
				{
					printf("%llu %d Ate often enough\n", entire_time(NULL), philo->id);
					pthread_mutex_lock(&philo->global->eat_end.mut);
					philo->global->eat_end.var = 1;
					pthread_mutex_unlock(&philo->global->eat_end.mut);
					return (NULL);
				}
				while (_time(NULL) <= philo->advs.tte)
				{
					if (check_death(philo) || check_stomach(philo))
						return (NULL);
				}
				pthread_mutex_unlock(&philo->global->forks[philo->id]);
				pthread_mutex_unlock(&philo->global->forks[(philo->id + 1) % philo->total]);
			}
		}
		else if (philo->sleeping)
		{
			if (check_death(philo) || check_stomach(philo))
				return (NULL);
			philo->sleeping = 0;
			philo->eating = 1;
			printf("%llu %d Sleeping\n", entire_time(NULL), philo->id);
			temp = _time(NULL);
			while(_time(NULL) - temp < philo->advs.tts)
			{
				if (check_death(philo) || check_stomach(philo))
					return (NULL);
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
	global.eat_end.var = 0;
	pthread_mutex_init(&global.eat_end.mut, NULL);
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
