/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarouil <azarouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:13:44 by azarouil          #+#    #+#             */
/*   Updated: 2025/04/27 15:29:24 by azarouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(unsigned long bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		ft_error("allocation failed");
	return (ret);
}

void	safe_ptcreate(pthread_t *thread, void *(f)(void *), void *arg)
{
	int	err;

	err = pthread_create(thread, NULL, f, arg);
	if (err)
	{
		if (EAGAIN == err)
			ft_error("The system lacked the necessary resources to create"
				" another thread, or the system-imposed limit on the total "
				"number of threads in a process.");
		else if (EPERM == err)
			ft_error("The caller does not have appropriate permission to "
				"set the required scheduling parameters or scheduling policy.");
		else if (EINVAL == err)
			ft_error("The value specified by attr is invalid.");
	}
}

void	safe_ptjoin(pthread_t thread)
{
	int	err;

	err = pthread_join(thread, NULL);
	if (err)
	{
		if (EINVAL == err)
			ft_error("The implementation has detected that the value "
				"specified by thread does not refer to a joinable thread.");
		else if (ESRCH == err)
			ft_error("No thread could be found corresponding to that"
				" specified by the given thread ID, thread.");
		else if (EDEADLK == err)
			ft_error("A deadlock was detected or the value"
				" of thread specifies the calling thread.");
	}
}

void	mutex_err(int err, t_mtx_op op)
{
	if (err == EINVAL)
	{
		if (op == LOCK || op == UNLOCK || op == DESTROY)
			ft_error("The value specified by mutex is invalid.");
		else if (op == INIT)
			ft_error("The value specified by attr is invalid.");
	}
	else if (op == DESTROY && err == EBUSY)
		ft_error("Mutex is locked.");
	else if (op == INIT && err == ENOMEM)
		ft_error("The process cannot allocate enough memory to"
			" create another mutex.");
	else if (op == LOCK && err == EDEADLK)
		ft_error("A deadlock would occur if the thread"
			" blocked waiting for mutex.");
	else if (op == UNLOCK && err == EPERM)
		ft_error("The current thread does not hold a lock on mutex.");
}

void	safe_mutex_handle(t_mtx_op op, t_mutex *mutex)
{
	int	err;

	err = 0;
	if (op == LOCK)
		err = pthread_mutex_lock(mutex);
	else if (op == UNLOCK)
		err = pthread_mutex_unlock(mutex);
	else if (op == INIT)
		err = pthread_mutex_init(mutex, NULL);
	else if (op == DESTROY)
		err = pthread_mutex_destroy(mutex);
	if (err)
		mutex_err(err, op);
}
