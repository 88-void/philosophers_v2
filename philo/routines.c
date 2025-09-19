/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:13:51 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/18 23:07:17 by sel-mlil         ###   ########.fr       */
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
		set_last_meal_time(philo, get_time());
		
		write_state(philo->philo_id, philo->table, EAT);
		precise_msleep(philo->table->time_to_eat, philo->table);
		
		safe_mutex_handle(LOCK,  &philo->meal_mlx);
		philo->meals++;
		safe_mutex_handle(UNLOCK, &philo->meal_mlx);
		
		safe_mutex_handle(UNLOCK, philo->left_fork);
		safe_mutex_handle(UNLOCK, philo->right_fork);
	}
}

void	sleeping_simulation(t_philo *philo)
{
	if (!get_end_simulation(philo->table) && philo->table->nbr_of_philo != 1)
	{
		write_state(philo->philo_id, philo->table, SLEEP);
		precise_msleep(philo->table->time_to_sleep, philo->table);
	}
}
