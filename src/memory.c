/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:52:49 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/05 21:28:51 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

t_philo	*alloc_philos(int ph_num)
{
	t_philo	*philo;

	philo = malloc(ph_num * sizeof(t_philo));
	return (philo);
}

// void	free_philos(t_philo *philo);
// {
// 	int	i;

// 	i = 0;
// 	while (i < 400)
// 	{
// 		free(philo[1]);
// 		i++;
// 	}
// }
