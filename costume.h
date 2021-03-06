#ifndef COSTUME_H
# define COSTUME_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

//			time.c
unsigned long long	_time(void);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);

//			threads.c
void				*sit_at_table(void *arg);

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
	unsigned long long	last_eaten;
	unsigned long long	start_of_exec;
	unsigned long long	last_sleep;
	int					ttd;
	int					tte;
	int					tts;
	int					tste;
	t_global			*global;
}	t_philo;

#endif