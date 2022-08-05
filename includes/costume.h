/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costume.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:19:41 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/05 21:11:28 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COSTUME_H
# define COSTUME_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_global
{
	pthread_mutex_t	forks[400];
	int				dead_var;
	pthread_mutex_t	dead_mut;
	pthread_mutex_t	print_mut;
}	t_global;

typedef struct s_philo
{
	pthread_t			thread;
	int					first;
	int					second;
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

//			check_input.c
int					check_philo(int ac, char **av);

//			main.c
void				init_states(t_philo *philo, \
int ac, char **av,	t_global *global);

//			time.c
unsigned long long	_time(void);
int					ft_strlen(const char *c);
void				ft_putstr_fd(char *s, int fd);
int					ft_strncmp(char const *s1, char const *s2, unsigned int n);

//			utils.c
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);

//			threads.c
void				*sit_at_table(void *arg);

//			access.c
long long unsigned	access_last_eaten(t_philo *philo, unsigned long long new);
int					access_times_eaten(t_philo *philo, int inc);
int					access_dead(t_philo *philo, int bool);
void				s_printf(char *msg, long long unsigned time, \
					int philo_id, t_philo *philo);

//			thread_utils.c
int					check_death(t_philo *philo);
void				init_forks(t_philo *philo, int *iterations);

//			loops.c
void				loop_1(t_philo *philo, int ac, char **av, t_global *global);
void				loop_2(t_philo *philo, char **av);
void				loop_3(t_philo *philo, char **av);
void				loop_4(t_philo *philo, t_global *global, char **av);

//			memory.c
t_philo				*alloc_philos(void);
void				free_philos(t_philo *philo);

#endif