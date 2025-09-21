/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:14:57 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/21 22:55:34 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(const char *err)
{
	ft_putstr_err(err);
	exit(EXIT_FAILURE);
}

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
		ft_error("arguments passed int limit");
	return (res);
}

void	check_if_only_nbr(char **av)
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
				ft_error("arguments does not contain only numbers");
			j++;
		}
		i++;
	}
}

void	parser(int ac, char **av, t_table *table)
{
	check_if_only_nbr(av);
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
	if (!table->nbr_of_philo || table->nbr_of_philo > 200)
		ft_error("number of philosophers cant be 0 and should not pass 200");
	else if (!table->nbr_of_meals)
		ft_error("number of meals cant be 0");
	else if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		ft_error("time cant be under 60ms");
	table_init(table);
}
