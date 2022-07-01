#include "costume.h"

void	check_death(t_philo *philo)
{
	if (philo->treshi.ttd < _time(NULL))
		philo->dead = 1;
	if (philo->dead)
	{
		printf("%d died\n", _time(NULL));
		exit(0);
	}
}

void	init_philo(t_philo *philo, int ac, char **av)
{
	philo->advs.tte = ft_atoi(av[3]);
	philo->advs.tts = ft_atoi(av[4]);
	philo->treshi.ttd = ft_atoi(av[2]);
	if (ac == 6)
		philo->treshi.tste = ft_atoi(av[5]);
	philo->eating = 0;
	philo->sleeping = 0;
	philo->dead = 0;
	philo->times_eaten = 0;
}

void	do_action(t_philo *philo)
{
	unsigned long long	temp;

	check_death(philo);
	if (!philo->eating && !philo->sleeping)
	{
		_time(NULL);
		philo->eating = 1;
	}
	else if (philo->eating)
	{
		check_death(philo);
		philo->eating = 0;
		philo->sleeping = 1;
		printf("%d Thinking\n", _time(NULL));
		printf("%d Eating\n", _time(NULL));
		init_time();
		philo->times_eaten++;
		if (philo->times_eaten >= philo->treshi.tste)
		{
			printf("%d Ate often enough\n", _time(NULL));
			exit(0);
		}
		while (_time(NULL) < philo->advs.tte)
			check_death(philo);
	}
	else if (philo->sleeping)
	{
		check_death(philo);
		philo->sleeping = 0;
		philo->eating = 1;
		printf("%d Sleeping\n", _time(NULL));
		temp = _time(NULL);
		while(_time(NULL) - temp < _time(NULL))
			check_death(philo);
	}
}

void	*surpressor(void *arg)
{
	while (1)
		do_action((t_philo *)arg);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	pthread_t	thread[200];
	int			i;

	init_philo(&philo, ac, av);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&thread[i], NULL, &surpressor, (void *)&philo);
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
