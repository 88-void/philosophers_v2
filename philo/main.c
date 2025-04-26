/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:15:00 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/26 21:19:26 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//./philo 5 400 300 500 {5}
//./philo philo_n time_to_die time_to_eat time_to_sleep nbr_of_eating_repetition(not mandatory)

int main(int ac, char **av)
{
	t_table	table;
	
	if (ac == 5 || ac == 6)
		parser(ac, av, &table);
	else
		ft_error("wrong number of arguments");
	dinner_start(&table);
}
