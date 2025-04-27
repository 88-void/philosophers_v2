/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:13:29 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/27 10:59:22 by azarouil         ###   ########.fr       */
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
void	precise_msleep(long sleeping_time)
{
	long	current_time;
	long	start;

	start = get_time();
	current_time = get_time() - start;
	while (current_time < sleeping_time)
		current_time = get_time() - start;
}
