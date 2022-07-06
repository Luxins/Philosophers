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
