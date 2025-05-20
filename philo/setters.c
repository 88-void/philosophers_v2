/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:58 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/27 11:01:10 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_philo_init_count(t_table *table)
{
	safe_mutex_handle(LOCK, &table->table_mtx);
	table->philo_init_count++;
	safe_mutex_handle(UNLOCK, &table->table_mtx);
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

void	set_last_meal_time(t_philo *philo, long value)
{
	safe_mutex_handle(LOCK, &philo->table->table_mtx);
	philo->last_meal_time = value;
	safe_mutex_handle(UNLOCK, &philo->table->table_mtx);
}
