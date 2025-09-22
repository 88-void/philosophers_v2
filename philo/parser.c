/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:14:57 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 23:24:31 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	if (res > INT_MAX || res < INT_MIN)
		return (-2);
	return (res);
}

bool	check_if_only_nbr(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				ft_putstr_err("arguments does not contain only numbers");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_int_limits(t_table *table)
{
	return (table->nbr_of_philo != -2 && table->time_to_die != -2
		&& table->time_to_eat != -2 && table->time_to_sleep != -2
		&& table->nbr_of_meals != -2);
}

bool	check_args_limits(t_table *table)
{
	if (!table->nbr_of_philo || table->nbr_of_philo > 200)
	{
		ft_putstr_err(
			"number of philosophers cant be 0 and should not pass 200");
		return (false);
	}
	else if (!table->nbr_of_meals)
	{
		ft_putstr_err("number of meals cant be 0");
		return (false);
	}
	else if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		ft_putstr_err("time can't be under 60ms");
		return (false);
	}
	return (true);
}

bool	parser(int ac, char **av, t_table *table)
{
	if (!check_if_only_nbr(av))
		return (false);
	table->nbr_of_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->full_count = 0;
	table->end_simulation = false;
	if (ac == 5)
		table->nbr_of_meals = -1;
	else
		table->nbr_of_meals = ft_atol(av[5]);
	if (!check_int_limits(table) || !check_args_limits(table))
		return (false);
	if (!table_init(table))
		return (false);
	return (true);
}
