/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:58 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/21 22:54:14 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	increment_philo_init_count(t_table *table)
// {
// 	pthread_mutex_lock(&table->table_mtx);
// 	table->philo_init_count++;
// 	pthread_mutex_unlock(&table->table_mtx);
// }

void	set_end_simulation(t_table *table, bool value)
{
	pthread_mutex_lock(&table->table_mtx);
	table->end_simulation = value;
	pthread_mutex_unlock(&table->table_mtx);
}

// void	increment_full_count(t_table *table)
// {
// 	pthread_mutex_lock(&table->table_mtx);
// 	table->full_count++;
// 	pthread_mutex_unlock(&table->table_mtx);
// }

void	set_last_meal_time(t_philo *philo, long value)
{
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->last_meal_time = value;
	pthread_mutex_unlock(&philo->table->table_mtx);
}
