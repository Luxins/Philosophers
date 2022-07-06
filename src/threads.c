#include "../includes/costume.h"

static int	check_death(t_philo *philo)
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
	printf("%llu %d is thinking\n", _time() - philo->start_of_exec, philo->id);
	if (*iterations != 0)
	{
		if (philo->ttd - (_time() - access_last_eaten(philo, 0)) > philo->tte)
			usleep(philo->tte * 1000);
	}
	(*iterations)++;
}

static int	takeing_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->forks[philo->first]);
	if (check_death(philo))
		return (1);
	printf("%llu %d has taken a fork\n", _time() - philo->start_of_exec, philo->id);
	pthread_mutex_lock(&philo->global->forks[philo->second]);
	if (check_death(philo))
		return (2);
	printf("%llu %d has taken a fork\n", _time() - philo->start_of_exec, philo->id);
	printf("%llu %d is eating\n", _time() - philo->start_of_exec, philo->id);
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
			printf("%llu %d Ate often enough\n", _time() - philo->start_of_exec, philo->id);
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
	printf("%llu %d is sleeping\n", _time() - philo->start_of_exec, philo->id);
	philo->last_sleep = _time();
	while(_time() - philo->last_sleep < philo->tts)
	{
		if (check_death(philo))
			return (1);
	}
	return (0);
}

void	*sit_at_table(void *arg)
{
	t_philo				*philo;
	int 				iterations;
	int					eat_ret;

	iterations = 0;
	philo = (t_philo *)arg;
	if (philo->total == 1)
	{
		usleep(philo->ttd * 1000);
		printf("%llu %d died\n", _time() - philo->start_of_exec, philo->id);
		return (NULL);
	}
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
