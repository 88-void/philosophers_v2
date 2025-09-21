/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:13:51 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/21 23:08:53 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// eating routine
/*
	1_ grab forks, write the grabing forks.
	2_ eat(usleep), write eating, update the philo last meal time, meals counter.
	3_ release forks.
*/
void	eating_simulation(t_philo *philo)
{
	if (!get_end_simulation(philo->table))
		write_state(philo->philo_id, philo->table, THINK);
	if (!get_end_simulation(philo->table))
	{
		pthread_mutex_lock(philo->right_fork);
		write_state(philo->philo_id, philo->table, FORK);
		if (philo->table->nbr_of_philo == 1)
			return (safe_mutex_handle(UNLOCK, philo->right_fork));
		pthread_mutex_lock(philo->left_fork);
		write_state(philo->philo_id, philo->table, FORK);
		write_state(philo->philo_id, philo->table, EAT);
		precise_msleep(philo->table->time_to_eat, philo->table);
		set_last_meal_time(philo, get_time());
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->meal_mtx);
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mtx);
	}
}

void	sleeping_simulation(t_philo *philo)
{
	if (!get_end_simulation(philo->table))
	{
		write_state(philo->philo_id, philo->table, SLEEP);
		precise_msleep(philo->table->time_to_sleep, philo->table);
	}
}
