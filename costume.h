#ifndef COSTUME_H
# define COSTUME_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

// # define TTE 30
// # define TTS 30
// # define TTD 1800
// # define TSTE 5

//			time.c
void				init_time(void);
unsigned long long	_time(unsigned long long	*init);
int					ft_atoi(const char *str);
void				init_entire_time(void);
unsigned long long	entire_time(unsigned long long	*init);

typedef struct s_treshold
{
	int	ttd;
	int	tste;
}	t_treshold;

typedef struct s_adv
{
	int	tte;
	int	tts;
}	t_adv;

typedef struct s_var_mut
{
	int		var;
	pthread_mutex_t mut;
}	t_var_mut;

typedef struct s_global
{
	pthread_mutex_t	forks[200];
	t_var_mut		dead;
}	t_global;

typedef struct s_philo
{
	int			total;
	int			id;
	int			eating;
	int			sleeping;
	int			dead;
	int			eat_end;
	int			times_eaten;
	t_adv		advs;
	t_treshold	treshi;
	t_global	*global;
}	t_philo;

#endif