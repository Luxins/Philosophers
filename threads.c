#include "costume.h"

static int	check_death(t_philo *philo)
{
	if (philo->global->dead.var)
		return (1);
	return (0);
}

static int	eating(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->id;
	second = (philo->id + 1) % philo->total;
	if (philo->id % 2 == 0)
	{
		usleep(1500);
		first = (philo->id + 1) % philo->total;
		second = philo->id;
	}
	printf("%llu %d is thinking\n", _time() - philo->start_of_exec, philo->id);
	pthread_mutex_lock(&philo->global->forks[first]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->global->forks[first]);
		return (1);
	}
	printf("%llu %d has taken a fork\n", _time() - philo->start_of_exec, philo->id);
	pthread_mutex_lock(&philo->global->forks[second]);
	printf("%llu %d has taken a fork\n", _time() - philo->start_of_exec, philo->id);
	printf("%llu %d is eating\n", _time() - philo->start_of_exec, philo->id);
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

void	*surpressor(void *arg)
{
	t_philo				*philo;
	unsigned long long	temp;

	philo = (t_philo *)arg;
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
			printf("%llu %d is sleeping\n", _time() - philo->start_of_exec, philo->id);
			philo->last_sleep = _time();
			while(_time() - philo->last_sleep - temp < philo->advs.tts)
			{
				if (check_death(philo))
					return (NULL);
			}
		}
	}
}
