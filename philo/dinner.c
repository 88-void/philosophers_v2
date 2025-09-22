/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:49 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 01:27:50 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_philos_done(t_table *table)
{
	int	idx;
	int	count;

	idx = 0;
	count = 0;
	while (idx < table->nbr_of_philo)
	{
		if ((get_time() - get_last_meal_time
				(&table->philo_arr[idx])) >= table->time_to_die)
		{
			write_state(table->philo_arr[idx].philo_id, table, DEATH);
			set_end_simulation(table, true);
			return (-1);
		}
		pthread_mutex_lock(&table->philo_arr[idx].meal_mtx);
		if (table->philo_arr[idx].meals >= table->nbr_of_meals)
			count++;
		pthread_mutex_unlock(&table->philo_arr[idx].meal_mtx);
		idx++;
	}
	return (count);
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		full_count;

	table = arg;
	while (!get_end_simulation(table))
	{
		full_count = get_philos_done(table);
		if (full_count == -1)
			return (NULL);
		if (table->nbr_of_meals != -1 && full_count == table->nbr_of_philo)
		{
			set_end_simulation(table, true);
			return (NULL);
		}
	}
	return (NULL);
}

void	dinning_simulation(t_philo *philo)
{
	eating_simulation(philo);
	sleeping_simulation(philo);
	// usleep(10);
}

void	*dinning_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (get_philo_count(philo) < philo->table->nbr_of_philo)
		usleep(2);
	set_last_meal_time(philo, get_time());
	if (philo->table->nbr_of_philo == 1)
	{
		eating_simulation(philo);
		precise_msleep(philo->table->time_to_die, philo->table);
		return (NULL);
	}
	if (philo->philo_id % 2 != 1)
		sleeping_simulation(philo);
	while (!get_end_simulation(philo->table))
		dinning_simulation(philo);
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nbr_of_philo)
	{
		pthread_create(&table->philo_arr[i].philo, NULL, dinning_routine,
			&table->philo_arr[i]);
		increment_philo_init_count(table);
		i++;
	}
	pthread_create(&table->mintor, NULL, monitoring, table);
	i = 0;
	while (i < table->nbr_of_philo)
	{
		pthread_join(table->philo_arr[i].philo, NULL);
		i++;
	}
	pthread_join(table->mintor, NULL);
	i = 0;
	while (i < table->nbr_of_philo)
		safe_mutex_handle(DESTROY, &table->fork_arr[i++]);
	safe_mutex_handle(DESTROY, &table->table_mtx);
	safe_mutex_handle(DESTROY, &table->print_mtx);
}
