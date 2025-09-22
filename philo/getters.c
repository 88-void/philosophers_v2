/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:00:29 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 01:13:39 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_philo_count(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->table->table_mtx);
	ret = philo->table->philo_init_count;
	pthread_mutex_unlock(&philo->table->table_mtx);
	return (ret);
}

bool	get_end_simulation(t_table *table)
{
	bool	ret;

	pthread_mutex_lock(&table->table_mtx);
	ret = table->end_simulation;
	pthread_mutex_unlock(&table->table_mtx);
	return (ret);
}

// long	get_nbr_of_meals(t_table *table)
// {
// 	long	ret;

// 	pthread_mutex_lock(&table->table_mtx);
// 	ret = table->nbr_of_meals;
// 	pthread_mutex_unlock(&table->table_mtx);
// 	return (ret);
// }

long	get_full_count(t_table *table)
{
	long	ret;

	pthread_mutex_lock(&table->table_mtx);
	ret = table->full_count;
	pthread_mutex_unlock(&table->table_mtx);
	return (ret);
}

long	get_last_meal_time(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->table->table_mtx);
	ret = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->table_mtx);
	return (ret);
}
