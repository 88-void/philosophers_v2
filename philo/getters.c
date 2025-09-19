/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:00:29 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/18 23:29:50 by sel-mlil         ###   ########.fr get_philo_count      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_philo_count(t_philo *philo)
{
	long	ret;

	safe_mutex_handle(LOCK, &philo->table->table_mtx);
	ret = philo->table->philo_init_count;
	safe_mutex_handle(UNLOCK, &philo->table->table_mtx);
	return (ret);
}

bool	get_end_simulation(t_table *table)
{
	bool	ret;

	safe_mutex_handle(LOCK, &table->table_mtx);
	ret = table->end_simulation;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
	return (ret);
}

long	get_nbr_of_meals(t_table *table)
{
	long	ret;

	safe_mutex_handle(LOCK, &table->table_mtx);
	ret = table->nbr_of_meals;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
	return (ret);
}

long	get_full_count(t_table *table)
{
	long	ret;

	safe_mutex_handle(LOCK, &table->table_mtx);
	ret = table->full_count;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
	return (ret);
}

long	get_last_meal_time(t_philo *philo)
{
	long	ret;

	safe_mutex_handle(LOCK, &philo->table->table_mtx);
	ret = philo->last_meal_time;
	safe_mutex_handle(UNLOCK, &philo->table->table_mtx);
	return (ret);
}
