/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:49 by azarouil          #+#    #+#             */
/*   Updated: 2025/05/19 22:50:43 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = arg;
	while (i < table->nbr_of_philo && !get_end_simulation(table))
	{
		if (!get_end_simulation(table) && (get_time()
			- get_last_meal_time(&table->philo_arr[i])) > table->time_to_die)
		{
			write_state(table->philo_arr[i].philo_id, table, DEATH);
			set_end_simulation(table, true);
			break ;
		}
		i++;
		usleep(5);
		if (i == table->nbr_of_philo)
			i = 0;
	}
	return (NULL);
}

void	dinning_simulation(t_philo *philo)
{
	if (philo->philo_id % 2 && !philo->is_full
		&& !get_end_simulation(philo->table))
	{
		eating_simulation(philo);
		sleeping_simulation(philo);
	}
	else if (!(philo->philo_id % 2) && !philo->is_full
		&& !get_end_simulation(philo->table))
	{
		sleeping_simulation(philo);
		eating_simulation(philo);
	}
}

void	one_philo_simulation(t_philo *philo)
{
	eating_simulation(philo);
	precise_msleep(philo->table->time_to_die + 1);
}

void	*dinning_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (get_philo_count(philo) < philo->table->nbr_of_philo)
		;
	set_last_meal_time(philo, get_time());
	if (philo->table->nbr_of_philo == 1)
		return (one_philo_simulation(philo), NULL);
	if (get_nbr_of_meals(philo->table) == -1)
	{
		while (!get_end_simulation(philo->table))
			dinning_simulation(philo);
	}
	else
	{
		while (!philo->is_full && !get_end_simulation(philo->table))
		{
			dinning_simulation(philo);
			if (get_full_count(philo->table) == philo->table->nbr_of_philo)
				set_end_simulation(philo->table, true);
		}
	}
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
		increment_philo_init_count(table);
		i++;
	}
	i = 0;
	safe_ptcreate(&table->mintor, monitoring, &table->philo_arr);
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
