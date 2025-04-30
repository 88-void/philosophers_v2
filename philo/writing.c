/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:46 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/30 17:03:00 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_state(long philo_id, t_table *table, t_wflag flag)
{
	safe_mutex_handle(LOCK, &table->print_mtx);
	if (THINK == flag && !get_end_simulation(table))
		printf("%ld %ld " M"is thinking\n"RST,
			(get_time() - table->start_time), philo_id);
	else if (DEATH == flag && !get_end_simulation(table))
		printf("%ld %ld "RD"died\n"RST,
			(get_time() - table->start_time), philo_id);
	else if (SLEEP == flag && !get_end_simulation(table))
		printf("%ld %ld "C"is sleeping\n"RST,
			(get_time() - table->start_time), philo_id);
	else if (FORK == flag && !get_end_simulation(table))
		printf("%ld %ld "G"has taken a fork\n"RST, 
			(get_time() - table->start_time), philo_id);
	else if (EAT == flag && !get_end_simulation(table))
		printf("%ld %ld "Y"is eating\n"RST,
			(get_time() - table->start_time), philo_id);
	safe_mutex_handle(UNLOCK, &table->print_mtx);
}
