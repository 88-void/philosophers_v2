/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:58 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/26 22:17:56 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_philo_init_count(t_table *table)
{
	safe_mutex_handle(LOCK, &table->table_mtx);
	table->philo_init_count++;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
}

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

void	set_end_simulation(t_table *table, bool value)
{
	safe_mutex_handle(LOCK, &table->table_mtx);
	table->end_simulation = value;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
}

void	increment_full_count(t_table *table)
{
	safe_mutex_handle(LOCK, &table->table_mtx);
	table->full_count++;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
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

void	set_last_meal_time(t_philo *philo, long value)
{
	safe_mutex_handle(LOCK, &philo->table->table_mtx);
	philo->last_meal_time = value;
	safe_mutex_handle(UNLOCK, &philo->table->table_mtx);
}
