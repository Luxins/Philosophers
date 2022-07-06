#ifndef COSTUME_H
# define COSTUME_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>


typedef struct s_global
{
	pthread_mutex_t	forks[200];
	int				dead_var;
	pthread_mutex_t	dead_mut;
}	t_global;

typedef struct s_philo
{
	pthread_t			thread;
	int					total;
	int					id;
	int					eating;
	int					sleeping;
	int					dead;
	int					eat_end;
	int					times_eaten;
	pthread_mutex_t		times_eaten_mut;
	unsigned long long	last_eaten;
	pthread_mutex_t		last_eaten_mut;
	unsigned long long	start_of_exec;
	unsigned long long	last_sleep;
	unsigned int		ttd;
	unsigned int		tte;
	unsigned int		tts;
	int					tste;
	t_global			*global;
}	t_philo;

//			time.c
unsigned long long	_time(void);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);

//			threads.c
void				*sit_at_table(void *arg);

//			access.c
long long unsigned	access_last_eaten(t_philo *philo, unsigned long long new);
int	access_times_eaten(t_philo *philo, int inc);

#endif