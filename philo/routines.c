/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:13:51 by azarouil          #+#    #+#             */
/*   Updated: 2025/05/19 11:10:13 by azarouil         ###   ########.fr       */
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
		safe_mutex_handle(LOCK, philo->right_fork);
		write_state(philo->philo_id, philo->table, FORK);
		if (philo->table->nbr_of_philo == 1)
			return (safe_mutex_handle(UNLOCK, philo->right_fork));
		safe_mutex_handle(LOCK, philo->left_fork);
		write_state(philo->philo_id, philo->table, FORK);
		write_state(philo->philo_id, philo->table, EAT);
		precise_msleep(philo->table->time_to_eat);
		if (get_nbr_of_meals(philo->table) != -1)
			philo->meals++;
		if (get_nbr_of_meals(philo->table) != -1
			&& philo->meals >= get_nbr_of_meals(philo->table))
		{
			philo->is_full = true;
			increment_full_count(philo->table);
		}
		set_last_meal_time(philo, get_time());
		safe_mutex_handle(UNLOCK, philo->right_fork);
		safe_mutex_handle(UNLOCK, philo->left_fork);
	}
}

void	sleeping_simulation(t_philo *philo)
{
	if (!get_end_simulation(philo->table) && philo->table->nbr_of_philo != 1)
	{
		write_state(philo->philo_id, philo->table, SLEEP);
		precise_msleep(philo->table->time_to_sleep);
	}
}
