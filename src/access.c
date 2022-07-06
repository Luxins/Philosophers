#include "../includes/costume.h"

long long unsigned	access_last_eaten(t_philo *philo, unsigned long long new)
{
	unsigned long long	cpy;

	pthread_mutex_lock(&philo->last_eaten_mut);
	if (new != 0)
	{
		philo->last_eaten = new;
		pthread_mutex_unlock(&philo->last_eaten_mut);
		return (0);
	}
	cpy = philo->last_eaten;
	pthread_mutex_unlock(&philo->last_eaten_mut);
	return (cpy);
}

int	access_times_eaten(t_philo *philo, int inc)
{
	int	cpy;

	pthread_mutex_lock(&philo->times_eaten_mut);
	if (inc == 69)
	{
		philo->times_eaten = 0;
		pthread_mutex_unlock(&philo->times_eaten_mut);
		return (0);
	}
	if (inc != 0)
	{
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->times_eaten_mut);
		return (0);
	}
	cpy = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mut);
	return (cpy);
}

int	access_dead(t_philo *philo, int bool)
{
	int	cpy;

	pthread_mutex_lock(&philo->global->dead_mut);
	if (bool == 1)
	{
		philo->global->dead_var = 1;
		pthread_mutex_unlock(&philo->global->dead_mut);
		return (0);
	}
	cpy = philo->global->dead_var;
	pthread_mutex_unlock(&philo->global->dead_mut);
	return (cpy);
}
