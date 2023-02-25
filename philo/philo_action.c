/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:20:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/25 16:17:44 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int philo, int type)
{
	if (data->status == DIED)
		return (1);
	pthread_mutex_lock(&(data->writing));
	printf("%lld ", (timeinmilliseconds() - data->init_time));
	data->init_time = data->init_time;
	printf("%d ", philo);
	
	if (type == HIS)
		printf("has %d fork\n", philo);
	if (type == NEXT)
	{
		if (philo == data->philosophers)
			printf("has %d fork\n",1);
		else
			printf("has %d fork\n", philo + 1);
	}
	
	if (type == FORK)
		printf("has taken a fork\n");
	else if (type == EATING)
		printf("is eating\n");
	else if (type == SLEEPING)
		printf("is sleeping\n");
	else if (type == THINKING)
		printf("is thinking\n");
	else if (type == DIED)
	{
		printf("died\n");
		data->status = DIED;
	}
	pthread_mutex_unlock(&(data->writing));
	return (0);
}


void	seek_fork(t_data *data, int philo)
{
	if (data->status == DIED)
		return ;
	if (data->philosophers == 1)
	{
		print_action(data, philo, FORK);
		wait(data, data->t_die);
		print_action(data, philo, DIED);
		data->status = DIED;
		return ;
	}
	usleep(50);
	if (philo == data->philosophers)
		pthread_mutex_lock(&(data->fork[0]));
	else
		pthread_mutex_lock(&(data->fork[philo]));
	print_action(data, philo, NEXT);
	pthread_mutex_lock(&(data->fork[philo - 1]));
	print_action(data, philo, HIS);
}

void	put_fork_back(t_data *data, int philo)
{
	if (data->status == DIED)
		return ;
	usleep(50);
	if (philo == data->philosophers)
		pthread_mutex_unlock(&(data->fork[0]));
	else
		pthread_mutex_unlock(&(data->fork[philo]));
	pthread_mutex_unlock(&(data->fork[philo - 1]));
}
