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
void	init_time(void);
int		_time(unsigned long long	*init);
int		ft_atoi(const char *str);

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

typedef struct s_philo
{
	int			eating;
	int			sleeping;
	int			dead;
	int			times_eaten;
	t_adv		advs;
	t_treshold	treshi;
}	t_philo;

#endif