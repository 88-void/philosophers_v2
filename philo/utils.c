/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:15:03 by azarouil          #+#    #+#             */
/*   Updated: 2025/05/20 13:48:17 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_err(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write (2, "\n", 1);
}

void	ft_clean(t_table *table)
{
	free(table->philo_arr);
	free(table->fork_arr);
}

void	philos_init(int i, t_table *table)
{
	table->philo_arr[i].philo_id = i + 1;
	table->philo_arr[i].last_meal_time = 0;
	table->philo_arr[i].is_full = false;
	table->philo_arr[i].table = table;
	table->philo_arr[i].right_fork = &table->fork_arr[i];
	if (i == 0 && table->nbr_of_philo != 1)
		table->philo_arr[i].left_fork
			= &table->fork_arr[table->nbr_of_philo - 1];
	else
		table->philo_arr[i].left_fork = &table->fork_arr[i - 1];
}

void	table_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo_arr = safe_malloc(sizeof(t_philo) * table->nbr_of_philo);
	table->fork_arr = safe_malloc(sizeof(t_mutex) * table->nbr_of_philo);
	table->end_simulation = false;
	table->philo_init_count = 0;
	table->full_count = 0;
	safe_mutex_handle(INIT, &table->table_mtx);
	safe_mutex_handle(INIT, &table->print_mtx);
	while (i < table->nbr_of_philo)
	{
		safe_mutex_handle(INIT, &table->fork_arr[i]);
		i++;
	}
	i = 0;
	while (i < table->nbr_of_philo)
	{
		philos_init(i, table);
		i++;
	}
}
