#include "../includes/costume.h"

int	access_times_eaten(t_philo *philo, int inc)
{
	int	cpy;

	pthread_mutex_lock(&philo->times_eaten_mut);
	if (inc == 1)
	{
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->times_eaten_mut);
		return (0);
	}
	cpy = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mut);
	return (cpy);
}

long long unsigned	access_last_eaten(t_philo *philo, unsigned long long new)
{
	unsigned long long	cpy;

	pthread_mutex_lock(&philo->last_eaten_mut);
	if (new)
	{
		philo->last_eaten = new;
		pthread_mutex_unlock(&philo->last_eaten_mut);
		return (0);
	}
	cpy = philo->last_eaten;
	printf("CPYYYYY: %llu\n", philo->last_eaten);
	pthread_mutex_unlock(&philo->last_eaten_mut);
	return (cpy);
}
