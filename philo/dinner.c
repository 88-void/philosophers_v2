/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:49 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/18 23:31:46 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_philos_done(t_table *table)
{
	int idx;
	unsigned int count;

	idx = 0;
	count = 0;
	while (idx < table->nbr_of_philo)
	{
		safe_mutex_handle(LOCK, &table->philo_arr[idx].meal_mlx);
		if (table->philo_arr[idx].meals >= table->nbr_of_meals)
			count++;
		safe_mutex_handle(UNLOCK, &table->philo_arr[idx].meal_mlx);
		idx++;
	}
	return (count);
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;
	unsigned int full_count;

	i = 0;
	table = arg;
	while (!get_end_simulation(table))
	{
		full_count = get_philos_done(table);
		if (table->nbr_of_meals != -1 && full_count == table->nbr_of_philo)
		{
			set_end_simulation(table, true);
			break ;
		}
		if (get_time()
			- get_last_meal_time(&table->philo_arr[i]) >= table->time_to_die)
		{
			write_state(table->philo_arr[i].philo_id, table, DEATH);
			set_end_simulation(table, true);
			break ;
		}
		i = (i + 1) % table->nbr_of_philo;
		precise_msleep(1, table);
	}
	return (NULL);
}

void	dinning_simulation(t_philo *philo)
{
	eating_simulation(philo);
	sleeping_simulation(philo);
	// usleep(10);
}

void	one_philo_simulation(t_philo *philo)
{
	eating_simulation(philo);
	precise_msleep(philo->table->time_to_die, philo->table);
}

void	*dinning_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	set_last_meal_time(philo, get_time());
	if (philo->table->nbr_of_philo == 1)
		return (one_philo_simulation(philo), NULL);
	if (philo->philo_id % 2 == 0)
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
		safe_ptcreate(&table->philo_arr[i].philo,
			dinning_routine, &table->philo_arr[i]);
		i++;
	}
	usleep(100);
	safe_ptcreate(&table->mintor, monitoring, table);
	i = 0;
	while (i < table->nbr_of_philo)
	{
		safe_ptjoin(table->philo_arr[i].philo);
		i++;
	}
	safe_ptjoin(table->mintor);
	i = 0;
	while (i < table->nbr_of_philo)
		safe_mutex_handle(DESTROY, &table->fork_arr[i++]);
	safe_mutex_handle(DESTROY, &table->table_mtx);
	safe_mutex_handle(DESTROY, &table->print_mtx);
}
