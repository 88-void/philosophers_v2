/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:46 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 23:30:39 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_state(long philo_id, t_table *table, t_wflag flag)
{
	pthread_mutex_lock(&table->print_mtx);
	if (!get_end_simulation(table))
	{
		if (THINK == flag)
			printf("%ld %ld %sis thinking%s\n",
				(get_time() - table->start_time), philo_id, M, RST);
		else if (DEATH == flag)
			printf("%ld %ld %sdied%s\n",
				(get_time() - table->start_time), philo_id, RD, RST);
		else if (SLEEP == flag)
			printf("%ld %ld %sis sleeping%s\n",
				(get_time() - table->start_time), philo_id, C, RST);
		else if (FORK == flag)
			printf("%ld %ld %shas taken a fork%s\n",
				(get_time() - table->start_time), philo_id, G, RST);
		else if (EAT == flag)
			printf("%ld %ld %sis eating%s\n",
				(get_time() - table->start_time), philo_id, Y, RST);
	}
	pthread_mutex_unlock(&table->print_mtx);
}
