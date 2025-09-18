/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:13:29 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/18 18:50:47 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//time in miliseconds
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((uint64_t)(tv.tv_sec) * 1e3) + (tv.tv_usec) / 1e3);
}

// sleeping time in MILISECONDS
void	precise_msleep(long sleeping_time, t_table *table)
{
	long	target;

	target = get_time() + sleeping_time;
	while (!get_end_simulation(table) && get_time() < target)
		usleep(100);
}
