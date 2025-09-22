/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:15:00 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 23:16:54 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (!parser(ac, av, &table))
			return (1);
	}
	else
	{
		ft_putstr_err("wrong number of arguments");
		return (1);
	}
	dinner_start(&table);
	ft_clean(&table);
}
