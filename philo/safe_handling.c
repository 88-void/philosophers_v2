/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:13:44 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/22 23:08:52 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(unsigned long bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		return (ft_putstr_err("memory allocation failed"), NULL);
	return (ret);
}
