/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:20:52 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/06 16:20:53 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/costume.h"

unsigned long long	_time(void)
{
	struct timeval				struci;

	gettimeofday(&struci, NULL);
	return (struci.tv_usec / 1000 + struci.tv_sec * 1000);
}
