/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: void <void@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:15:33 by azarouil          #+#    #+#             */
/*   Updated: 2025/09/21 22:08:25 by void             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

# define G "\033[1;32m"
# define RD "\033[1;31m"
# define Y "\033[1;33m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define RST "\033[0m"

typedef pthread_mutex_t	t_mutex;

typedef enum s_mtx_op
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}		t_mtx_op;

typedef enum s_wflag
{
	DEATH,
	SLEEP,
	FORK,
	THINK,
	EAT,
}t_wflag;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t	philo;
	long		philo_id;
	long		last_meal_time;
	bool		is_full;
	long		meals;
	t_mutex		meal_mtx;
	t_mutex		*right_fork;
	t_mutex		*left_fork;
	t_table		*table;
}t_philo;

typedef struct s_table
{
	t_philo		*philo_arr;
	t_mutex		*fork_arr;
	t_mutex		print_mtx;
	t_mutex		table_mtx;
	pthread_t	mintor;
	long		full_count;
	long		philo_init_count;
	long		nbr_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_of_meals;
	long		start_time;
	bool		end_simulation;
}		t_table;
//error
void	ft_putstr_err(const char *str);
void	ft_error(const char *err);
//safe handling operations
void	*safe_malloc(unsigned long bytes);
void	safe_ptcreate(pthread_t *thread, void *(f)(void *), void *arg);
void	safe_ptjoin(pthread_t thread);
void	safe_mutex_handle(t_mtx_op op, t_mutex *mutex);
//parsing
void	parser(int ac, char **av, t_table *table);
//init
void	table_init(t_table *table);
//time
long	get_time(void);
void	precise_msleep(long sleeping_time, t_table *table);
//writing state
void	write_state(long philo_id, t_table *table, t_wflag flag);
//setters and getters
void	increment_philo_init_count(t_table *table);
void	increment_full_count(t_table *table);
void	set_end_simulation(t_table *table, bool value);
void	set_last_meal_time(t_philo *philo, long value);
long	get_philo_count(t_philo *philo);
bool	get_end_simulation(t_table *table);
long	get_nbr_of_meals(t_table *table);
long	get_full_count(t_table *table);
long	get_last_meal_time(t_philo *philo);
//simulations
void	dinner_start(t_table *table);
void	eating_simulation(t_philo *philo);
void	sleeping_simulation(t_philo *philo);
//free
void	ft_clean(t_table *table);

#endif